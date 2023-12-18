#include "GraphGeneration.h"
#include <chrono>


int main(void) {

    double prob = 1;
    int numNodes = 30000;
    int numEdges = 150000;
    auto startTime = std::chrono::high_resolution_clock::now();
    // ErdosRenyiGraph erG(numNodes, prob);
    NewmanConfigModel nG(numNodes, numEdges);
    nG.generateBpm("../Nout.pbm");
    // erG.generateBpm("../erG.pbm");
    nG.output_adjaceny_matrix("../input.txt");
    nG.serialse("../inS.bin");

    Graph emp(numNodes);
    emp.deserialise("../inS.bin");
    std::cout << "AA" << std::endl;
    emp.generateBpm("../outSr.pbm");
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
    std::cout << "Time taken: " << duration.count() << " seconds" << "for " << numNodes << " nodes " << std::endl;
}