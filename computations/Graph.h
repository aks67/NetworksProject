#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <fstream>

class Graph {
    
    public:
        
        //Constructor
        Graph(int numNodes);

        //Adding Edges
        bool addEdges(int u, int v) ;

        //Remove Edges
        bool removeEdges(int u, int v);

        //Printing Matrix
        void printMatrixToTerminal();

        //Check connections
        bool check_edge(int u, int v);

        //Create a pixel image
        void generateBpm(const std::string& filename);

    protected:
        int numNodes;
        std::vector<std::vector<bool>> adjacencyMatrix;
};


#endif