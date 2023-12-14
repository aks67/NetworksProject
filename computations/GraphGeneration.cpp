#include "GraphGeneration.h"
#include <random>

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



NewmanConfigModel::NewmanConfigModel(int numNodes, int numEdges)
    : Graph(numNodes), numEdges(numEdges) {
        
        this->setNumEdges(numEdges);
        this->createEdges();

}

void NewmanConfigModel::setNumEdges(int numEdges) {
    this->numEdges = numEdges;
}

void NewmanConfigModel::createEdges() {
    std::random_device rd;
    std::mt19937 gen(rd());

    while (numEdges > 0) {
        std::uniform_int_distribution<int> distNode(0, numNodes - 1);
        int u = distNode(gen);
        int v = distNode(gen);

        if (u != v && !this->adjacencyMatrix[u][v]) {
            this->adjacencyMatrix[u][v] = true;
            this->adjacencyMatrix[v][u] = true;
            numEdges--;
        }
    } 
}