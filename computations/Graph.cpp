#include "Graph.h" 
#include <iostream>
#include <string>
#include <thread>

Graph::Graph(int numNodes) : numNodes(numNodes),  node_degrees(new int[numNodes]()) {
    adjacencyMatrix.resize(numNodes, std::vector<bool>(numNodes, false));
}

Graph* Graph::askGraphConfig() {
    int numNodes = 0;
    std::cout << "Enter the number of nodes: ";
    std::cin >> numNodes;
    return new Graph(numNodes);

}

bool Graph::addEdges(int u, int v) {
    if (( u >= 0 && u < numNodes) && (v >= 0 && v < numNodes)) {
        adjacencyMatrix[u][v] = true;
        adjacencyMatrix[v][u] = true;
        node_degrees[u]++;
        node_degrees[v]++;
        return true;
    }

    return false;
}

bool Graph::addEdgesThreadSafe(int u, int v) {
    /*
        A thread safe version of add edges, lock the graph 
    */
    std::unique_lock<std::mutex> lock(graphMutex);
    if (( u >= 0 && u < numNodes) && (v >= 0 && v < numNodes)) {
        adjacencyMatrix[u][v] = true;
        adjacencyMatrix[v][u] = true;
        node_degrees[u]++;
        node_degrees[v]++;
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

int Graph::getDegree(int node) {
    return this->node_degrees[node];
}

int Graph::getNumNodes() {
    return this->numNodes;
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
            pbmFile << (adjacencyMatrix[i][j] ? "1 " : "0");
        }
        pbmFile << "\n";
    }

    pbmFile.close();
}

void Graph::generateCompressedBpm(const std::string& filename) {

    std::ofstream pbmFile(filename);

    if (!pbmFile.is_open()) {
        std::cout << "Error in openening the file" << std::endl;
    }

    pbmFile << "P4\n";
    pbmFile << this->numNodes << " " << this->numNodes << "\n";

    for (int i = 0; i < this->numNodes; i++) {
        unsigned char byte = 0;
        unsigned char bitPos = 0;
        // rle serialised
        for (int j = 0; j < this->numNodes; j++) {
            if (this->adjacencyMatrix[i][j]) {
                byte |= (1 << (7 - bitPos));
            } 
            bitPos++;

            if (bitPos == 8) {
                pbmFile.put(byte);
                byte = 0;
                bitPos = 0;
            }
        }

        if (bitPos != 0) {
            pbmFile.put(byte);
        }
    }

    std::cout << "Compressed PBM (P4 format) file generated: " << filename << std::endl;

    pbmFile.close();

}

std::vector<std::vector<bool> > Graph::get_matrix() {

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

void Graph::serialse(const std::string& filename) {
    
    std::ofstream file(filename, std::ios::binary | std::ios::out);
    file.write(reinterpret_cast<char*>(&this->numNodes), sizeof(this->numNodes));


    for (int i = 0; i < this->numNodes; i++) {
        for (int j = 0; j < this->numNodes; j++) {
            char value = this->adjacencyMatrix[i][j] ? 1 : 0;
            file.write(&value, sizeof(char));
        }
    }


    file.close();
}

void Graph::serialseRle(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary | std::ios::out);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    file.write(reinterpret_cast<char*>(&this->numNodes), sizeof(this->numNodes));

    char current = this->adjacencyMatrix[0][0] ? 1 : 0;

    int count = 1;

    for (int i = 0; i < this->numNodes; i++) {
        for (int j = 0;  j < this->numNodes; j++) {
            char value = this->adjacencyMatrix[i][j] ? 1 : 0;
            if (value == current) {
                count++;
            } else {
                file.write(reinterpret_cast<char*>(&count), sizeof(count));
                file.write(&current, sizeof(char));
                current = value;
                count = 1;
            }
        }
    }

    file.write(reinterpret_cast<char*>(&count), sizeof(count));
    file.write(&current, sizeof(char));

    file.close();

}

void Graph::deserialise(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::in);

    if (!file.is_open()) {
        std::cerr << "Error opening: " << filename << std::endl;
        return;
    }


    file.read(reinterpret_cast<char*>(&this->numNodes), sizeof(this->numNodes));

    this->adjacencyMatrix.resize(this->numNodes, std::vector<bool>(numNodes, false));


    for (int i = 0; i < this->numNodes; i++) {
        for (int j = 0; j < this->numNodes; j++) {
            char value; 
            file.read(&value, sizeof(char));
            this->adjacencyMatrix[i][j] = (value == 1);
        }
    }

    file.close();
}

void Graph::deserialiseRLE(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::in);

    if (!file.is_open()) {
        std::cerr << "Error in opening file: " << filename << std::endl;
        return;
    }

    file.read(reinterpret_cast<char*>(&this->numNodes), sizeof(this->numNodes));

    this->adjacencyMatrix.resize(this->numNodes, std::vector<bool>(this->numNodes, false));

    char value;
    int count;

    for (int i = 0; i < this->numNodes; i++) {
        for (int j = 0; j < this->numNodes;) {
            file.read(reinterpret_cast<char*>(&count), sizeof(count));
            file.read(&value, sizeof(char));

            for (int k = 0; k < count; k++) {
                this->adjacencyMatrix[i][j] = (value == 1);
                j++;
                if (j >= this->numNodes) {
                    j = 0;
                    i++;
                }
            }
        }
    }

    file.close();
}

