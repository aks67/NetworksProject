#include "GraphGeneration.h"
#include <chrono>


int main(void) {

    double prob = 0.8;
    int numNodes = 5000;
    int numEdges = 250000;
    auto startTime = std::chrono::high_resolution_clock::now();
    ErdosRenyiGraph erG(numNodes, prob);
    NewmanConfigModel nG(numNodes, numEdges);
    nG.generateBpm("../Nout.pbm");
    erG.generateBpm("../erG.pbm");
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    std::cout << "Time taken: " << duration.count() << " seconds" << "for " << numNodes << " nodes " << std::endl;
}