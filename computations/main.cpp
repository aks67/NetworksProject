#include "GraphGeneration.h"
#include <chrono>


int main(void) {

    double prob = 1;
    int numNodes = 20000;
    int numEdges = 120000;
    int k = 10;
    double beta = 0.1;

    auto startTime = std::chrono::high_resolution_clock::now();
    // ErdosRenyiGraph erG(numNodes, prob);
    // NewmanConfigModel nG(numNodes, numEdges);
    WattsStrogatzGraph wG(numNodes, k, beta);
    // wG.generateBpm("../wgOut.pbm");
    wG.generateCompressedBpm("../wgOutCompressed.pbm");
    // nG.generateBpm("../Nout.pbm");


    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    std::cout << "Time taken: " << duration.count() << " seconds" << "for " << numNodes << " nodes " << std::endl;
}