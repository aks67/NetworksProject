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



WattsStrogatzGraph::WattsStrogatzGraph(int numNodes, int k, double beta) 
    : Graph(numNodes), k(k), beta(beta) {
        
        this->createRingLattice();
        this->rewireEdges();
    }


void WattsStrogatzGraph::createRingLattice() {

    int numNodes = this->numNodes;
    int k = this->k;

    for (int i = 0; i < numNodes; i++) {
        for (int j = 1; j < k /2; j++) {
            int neighbour = (i + j) % numNodes;
            this->addEdges(i, neighbour);
        }
    }
}


void WattsStrogatzGraph::rewireEdges() {
    double beta = this->beta;
    int numNodes = this->numNodes;
    int k = this->k;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);


    for (int i = 0; i < numNodes; i++) {
        for (int j = 1; j < i + 1  + k/2; j++) {
            if (dis(gen) < beta) {
                int newNeighbour = j % numNodes;
                this->removeEdges(i, (i + j) % numNodes);
                this->addEdges(i, newNeighbour);
            }
        }
    }

}