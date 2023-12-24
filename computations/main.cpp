#include "GraphGeneration.h"
#include <chrono>


int main(void) {

    double prob = 0.01;
    int numNodes = 50;
    int numEdges = 1;
    int k = 20;
    double beta = 1 ;
    int m = 1;

    auto startTime = std::chrono::high_resolution_clock::now();
    
    // ErdosRenyiGraph erG(numNodes, prob);
    // NewmanConfigModel nG(numNodes, numEdges);
    // WattsStrogatzGraph wG(numNodes, k, beta);
    BarabasiAlbertGraph baG(numNodes, m);
    baG.generateBpm("../out.pbm");
    baG.output_adjaceny_matrix("../outP.txt");

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    std::cout << "Time taken: " << duration.count() << " seconds" << "for " << numNodes << " nodes " << std::endl;
}