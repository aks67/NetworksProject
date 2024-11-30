#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <fstream>
class Graph {
    
    public:
        
        Graph(int numNodes);

        static Graph* createGraph(const std::string& graphType);

        bool addEdges(int u, int v);

        bool addEdgesThreadSafe(int u, int v);

        bool removeEdges(int u, int v);

        void printMatrixToTerminal();

        bool check_edge(int u, int v);

        void generateBpm(const std::string& filename);

        void generateCompressedBpm(const std::string& filename); 

        std::vector<std::vector<bool> > get_matrix();
        
        void output_adjaceny_matrix(const std::string& filename);

        void serialse(const std::string& filename);

        void deserialise(const std::string& filename);

        void serialseRle(const std::string& filename);

        void deserialiseRLE(const std::string& filename);

        int getDegree(int node);
        
        int getNumNodes();

        static Graph* askGraphConfig();

        ~Graph() {
            delete[] node_degrees;
        }
        
    protected:
        int numNodes;
        int* node_degrees;
        std::mutex graphMutex; 
        std::vector<std::vector<bool> > adjacencyMatrix;
};

#endif