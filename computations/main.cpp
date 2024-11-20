#include "GraphGeneration.h"
#include <chrono>
#include <unordered_set>

#if defined(__APPLE__) && defined(__MACH__)
    #include <mach/mach.h>
#elif defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #include <psapi.h>
#else
    #include <sys/resource.h>
#endif


using namespace std;

void printMemoryUsage() {

    #if defined(__APPLE__) && defined(__MACH__)
        // macOS
        mach_task_basic_info_data_t info;
        mach_msg_type_number_t infoCount = MACH_TASK_BASIC_INFO_COUNT;
        kern_return_t kr = task_info(mach_task_self(), MACH_TASK_BASIC_INFO, (task_info_t)&info, &infoCount);

        if (kr != KERN_SUCCESS) {
            std::cerr << "Failed to get task info" << std::endl;
            return;
        }
        long long memoryBytes = info.resident_size;
        long long memoryKB = memoryBytes / 1024;
        long long memoryMB = memoryKB / 1024;
        long long memoryGB = memoryMB / 1024;

        std::cout << "Memory used: " << memoryKB << " KB" << std::endl;
        std::cout << "Memory used: " << memoryMB << " MB" << std::endl;
        std::cout << "Memory used: " << memoryGB << " GB" << std::endl;

    #elif defined(_WIN32) || defined(_WIN64)
        PROCESS_MEMORY_COUNTERS_EX memoryCounters;
        if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&memoryCounters, sizeof(memoryCounters))) {
            long long memoryBytes = memoryCounters.WorkingSetSize;

            long long memoryKB = memoryBytes / 1024;
            long long memoryMB = memoryKB / 1024;
            long long memoryGB = memoryMB / 1024;

            std::cout << "Memory used: " << memoryKB << " KB" << std::endl;
            std::cout << "Memory used: " << memoryMB << " MB" << std::endl;
            std::cout << "Memory used: " << memoryGB << " GB" << std::endl;
        } else {
            std::cerr << "Failed to get process memory info" << std::endl;
        }
    #else
        // Linux
        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        long memoryBytes = usage.ru_maxrss; 
        long memoryKB = memoryBytes;
        long memoryMB = memoryKB / 1024;
        long memoryGB = memoryMB / 1024;

        std::cout << "Memory used: " << memoryKB << " KB" << std::endl;
        std::cout << "Memory used: " << memoryMB << " MB" << std::endl;
        std::cout << "Memory used: " << memoryGB << " GB" << std::endl;
    #endif

}

int main(void) {

    int numNodes = 0;
    unordered_set<string> validGraphConfigurations = {"erG", "nG", "baG", "wG"};
    string inputGraphSelected;
    cout << "Enter Graph needed: \n"
         << "Graph Options:\n"
         << "erG - Erdos Renyi graph\n"
         << "nG - Newman Configuration Model\n"
         << "baG - Barabasi Albert Graph\n"
         << "wG - Watts Strogatz Graph\n" 
         << "----------------------\n";
    
    getline(cin, inputGraphSelected);
    
    Graph* selectedGraph = nullptr;
    if (validGraphConfigurations.find(inputGraphSelected) != validGraphConfigurations.end()) {
            cout << "Selected: " << inputGraphSelected << endl;
            cout << "----------------------\n";
            cout << "builidng Graph\n";
        } else {
            cout << "Invalid input. Please enter one of the following: erG, nG, baG, wG." << endl;
        }
   
    auto startTime = chrono::high_resolution_clock::now();
    selectedGraph = Graph::createGraph(inputGraphSelected);
    auto buildEndTime = chrono::high_resolution_clock::now();
    auto buildDuration = chrono::duration_cast<std::chrono::seconds>(buildEndTime - startTime);
    
    if (selectedGraph == nullptr) {
        cout << "Failed to create a Graph";
        return 0;
    } else {
        cout << "Built Graph, time taken = " << buildDuration.count() << " " << endl;
    }
    numNodes = selectedGraph->getNumNodes();
    auto startTextTime = chrono::high_resolution_clock::now();
    selectedGraph->output_adjaceny_matrix("../outP.txt");
    auto endTextTime = chrono::high_resolution_clock::now();
    auto buildTextDuration = chrono::duration_cast<std::chrono::seconds>(endTextTime - startTextTime);
    cout << "Output Naive text Graph, time taken = " << buildTextDuration.count() << " " << endl;
    cout << "----------------------\n";
    auto startPBMTime = chrono::high_resolution_clock::now();
    selectedGraph->generateBpm("../outP.pbm");
    auto endPBMTime = chrono::high_resolution_clock::now();
    auto buildPBMDuration = chrono::duration_cast<std::chrono::seconds>(endPBMTime - startPBMTime);
    cout << "Output Naive PBM Graph, time taken = " << buildPBMDuration.count() << " " << endl;
    cout << "----------------------\n";
    auto startCompressedPBMTime = chrono::high_resolution_clock::now();
    selectedGraph->generateCompressedBpm("../outCompressed.pbm");
    auto endCompressedPBMTime = chrono::high_resolution_clock::now();
    auto buildCompressedPBMDuration = chrono::duration_cast<std::chrono::seconds>(endCompressedPBMTime - startCompressedPBMTime);
    cout << "Output Compressed PBM Graph, time taken = " << buildCompressedPBMDuration.count() << " " << endl;
    cout << "----------------------\n";

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    cout << "----||--------------||---\n";  

    cout << "Time taken: " << duration.count() << " seconds" << "for " << numNodes << " nodes " << endl;
    printMemoryUsage();
    cout << "----|| ------ || ---\n";
}