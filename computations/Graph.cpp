#include "Graph.h" 
#include <iostream>
#include <thread>

Graph::Graph(int numNodes) : numNodes(numNodes) {
    adjacencyMatrix.resize(numNodes, std::vector<bool>(numNodes, false));
}


bool Graph::addEdges(int u, int v) {
    
    if (( u >= 0 && u < numNodes) && (v >= 0 && v < numNodes)) {
        adjacencyMatrix[u][v] = true;
        adjacencyMatrix[v][u] = true;
        return true;
    }

    return false;
}


bool Graph::removeEdges(int u, int v) {

    if (( u >= 0 && u < numNodes) && (v >= 0 && v < numNodes)) {
        adjacencyMatrix[u][v] = false;
        adjacencyMatrix[v][u] = false;
        return true;
    }

    return false;
}


void Graph::printMatrixToTerminal() {
    
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            std::cout << adjacencyMatrix[i][j] << " ";
        }
        std::cout << '\n';
    }
}

bool Graph::check_edge(int u, int v) {
    
    if (( u >= 0 && u < numNodes) && (v >= 0 && v < numNodes)) {
        
        if (adjacencyMatrix[u][v] == true) {
            return true;
        } 
    }

    return false;
}

void Graph::generateBpm(const std::string& filename) {
    
    std::ofstream pbmFile(filename);

    if(!pbmFile.is_open()) {
        std::cout << "Error in opening the file" << std::endl;
        return;
    }

    pbmFile << "P1\n";
    pbmFile << numNodes << " " << numNodes << "\n";

    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            pbmFile << (adjacencyMatrix[i][j] ? "1 " : "0 ");
        }
        pbmFile << "\n";
    }

    pbmFile.close();
}


std::vector<std::vector<bool>> Graph::get_matrix() {

    return this->adjacencyMatrix;
}

void Graph::output_adjaceny_matrix(const std::string& filename) {
    std::ofstream txtfile(filename);

    if (!txtfile.is_open()) {
        std::cerr << "Error in opening the file: " << filename << std::endl;
        return;
    }


    for (const auto& row : this->adjacencyMatrix) {
        for (bool value : row) {
           
            txtfile << value << " ";
        }
        txtfile << "\n";  
    }

    txtfile.close();
    std::cout << "Adjacency matrix written to " << filename << std::endl;
}