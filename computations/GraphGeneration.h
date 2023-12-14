/*
    The graph generation returns a random graph built on certain paramters
    - Erdos Renyi Model
*/

// Imports 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Graph.h"

//Graph structure


class ErdosRenyiGraph : public Graph {
    
    public:
        ErdosRenyiGraph(int numNodes, double probability);
    
    private:
        double probability = 0;
};