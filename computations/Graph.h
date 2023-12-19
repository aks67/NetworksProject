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

        //Create a compressed pixel image with grouped nodes, it would still give an approximate picture
        void generateCompressedBpm(const std::string& filename); 


        //Get the adjacency matrix
        std::vector<std::vector<bool>> get_matrix();
        
        // output the current adjaceny matrix into a txt file
        void output_adjaceny_matrix(const std::string& filename);


        //serialse
        void serialse(const std::string& filename);

        //Deserialise 
        void deserialise(const std::string& filename);

        //Run Length Encoding
        void serialseRle(const std::string& filename);

        //Run length Decoding
        void deserialiseRLE(const std::string& filename);


    protected:
        int numNodes;
        std::vector<std::vector<bool>> adjacencyMatrix;
};


#endif