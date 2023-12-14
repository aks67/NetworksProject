#include "GraphGeneration.h"



ErdosRenyiGraph::ErdosRenyiGraph(int numNodes, double probability) 
    : Graph(numNodes), probability(probability) {
    
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < numNodes; ++i) {
        for (int j = i + 1; j < numNodes; ++j) {
            if (static_cast<double>(rand()) / RAND_MAX < probability) {
                this->addEdges(i, j);
            }
        }
    }


}
