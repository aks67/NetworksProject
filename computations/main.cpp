#include "GraphGeneration.h"
#include <chrono>


int main(void) {

    double prob = 0.4;
    int numNodes = 50000;
    auto startTime = std::chrono::high_resolution_clock::now();
    ErdosRenyiGraph erG(numNodes, prob);
    std::string out = "../out.pbm";
    // erG.generateBpm(out);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    std::cout << "Time taken: " << duration.count() << " seconds" << "for " << numNodes << " nodes " << std::endl;
}