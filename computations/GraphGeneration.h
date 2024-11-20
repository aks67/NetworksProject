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
#include <algorithm>
//Graph structure


class ErdosRenyiGraph : public Graph {
    
    public:
        ErdosRenyiGraph(int numNodes, double probability);
        static Graph* askGraphConfig();
    private:
        double probability = 0;
};

class NewmanConfigModel : public Graph {
    
    public:
        NewmanConfigModel(int numNodes, int numEdges);
        static Graph* askGraphConfig();

    private:
        int numEdges;
        void createEdges();
};

class WattsStrogatzGraph : public Graph {

    public:
        WattsStrogatzGraph(int numNodes, int k, double beta);
       static Graph* askGraphConfig();
    private:
        int k;
        double beta;
        void createRingLattice();
        void rewireEdges();


};

class BarabasiAlbertGraph : public Graph {
    
    public:
        BarabasiAlbertGraph(int numNodes, int m);
       static Graph* askGraphConfig();
    private:
        int m;
        void attachNode(int newNode);

};