/*
    The graph generation returns a random graph built on certain paramters
    - Erdos Renyi Model
*/

// Imports 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Graph.h"
#include <random>
//Graph structure


class ErdosRenyiGraph : public Graph {
    
    public:
        ErdosRenyiGraph(int numNodes, double probability);
    
    private:
        double probability = 0;
};


class NewmanConfigModel : public Graph {
    
    public:
        NewmanConfigModel(int numNodes, int numEdges);

    private:
        int numEdges;
        void createEdges();
        void setNumEdges(int numEdges);
};