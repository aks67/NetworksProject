#include "GraphGeneration.h"
#include <chrono>


int main(void) {

    double prob = 0.01;
    int numNodes = 10000;
    int numEdges = 1;
    int k = 20;
    double beta = 1;

    auto startTime = std::chrono::high_resolution_clock::now();
    ErdosRenyiGraph erG(numNodes, prob);
    // NewmanConfigModel nG(numNodes, numEdges);
    WattsStrogatzGraph wG(numNodes, k, beta);
    wG.generateBpm("../wgOut.pbm");
    // wG.generateCompressedBpm("../wgOutCompressed.pbm");
    // nG.generateBpm("../Nout.pbm");
    // erG.printMatrixToTerminal();
    std::cout << wG.getDegree(9) << std::endl;
    std::cout << wG.getDegree(99) << std::endl;
    std::cout << wG.getDegree(999) << std::endl;
    std::cout << wG.getDegree(9999) << std::endl;
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    std::cout << "Time taken: " << duration.count() << " seconds" << "for " << numNodes << " nodes " << std::endl;
}