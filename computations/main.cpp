#include "GraphGeneration.h"
#include <chrono>
#include <unordered_set>

#include "utils/performanceCapture.cpp"
using namespace std;

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
    auto startTime = std::chrono::high_resolution_clock::now();

    // selectedGraph = printProcessTimeTaken("Graph generation ", Graph::createGraph(inputGraphSelected));
    selectedGraph = printProcessTimeTaken("Graph generation", [&]() {
        return Graph::createGraph(inputGraphSelected);
    });
    if (selectedGraph == nullptr) {
        cout << "Failed to create a Graph";
        return 0;
    }
    numNodes = selectedGraph->getNumNodes();
    printProcessTimeTaken("Compressing graph", [&]() {
        selectedGraph->generateCompressedBpm("../outCompressed.pbm");
    });
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;
    cout << "Time taken: " << duration.count() << " seconds" << "for " << numNodes << " nodes " << endl;
    printMemoryUsage();
    cout << "----|| ------ || ---\n";
}