/*
    Separating out the performance capture module to enable outputs,
    naivce at this point
*/
#include <chrono>
#include <string>
#include <functional>
#include <iostream>

#if defined(__APPLE__) && defined(__MACH__)
    #include <mach/mach.h>
#elif defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #include <psapi.h>
#else
    #include <sys/resource.h>
#endif


inline void printMemoryUsage() {

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

template <typename Func, typename... Args>
auto printProcessTimeTaken(const std::string& processName, Func&& func, Args&&... args) {
    auto startTime = std::chrono::high_resolution_clock::now();

    if constexpr (std::is_void_v<std::invoke_result_t<Func, Args...>>) {
        std::forward<Func>(func)(std::forward<Args>(args)...);
    } else {
        auto result = std::forward<Func>(func)(std::forward<Args>(args)...);
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = endTime - startTime;
        std::cout << processName << ": " << duration.count() << " seconds\n";
        return result;
    }

    std::forward<Func>(func)(std::forward<Args>(args)...);
        auto endTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = endTime - startTime;
        std::cout << processName << ": " << duration.count() << " seconds\n";
}

class Timer {
public:
    Timer(const std::string& name) : processName(name) {
        startTime = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
        std::cout << processName << " took " << duration.count() << " microseconds.\n";
    }

private:
    std::string processName;
    std::chrono::high_resolution_clock::time_point startTime;
};

template <typename Func, typename ReturnType>
ReturnType measureTime(const std::string& processName, Func&& func) {
    Timer timer(processName); 
    return std::forward<Func>(func)();  
}

template <typename ReturnType>
class PerformanceClass {
    public:
        PerformanceClass(std::vector<std::function<ReturnType()>> functions) : functions(functions) {
            executeFunctions();
        }

    private:
        std::vector<std::function<void()>> functions;
        void executeFunctions() {
            for (size_t i = 0; i < functions.size(); ++i) {
                std::string processName = "Task " + std::to_string(i + 1);
                measureTime(processName, functions[i]); 
            }
        }
};