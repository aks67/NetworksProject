#include "GraphGeneration.h"
#include <random>
#include <thread>

/*
    A better way to handle ask and config set up:
    move base graph setup up the ladder, and pass down the number
 */

ErdosRenyiGraph::ErdosRenyiGraph(int numNodes, double probability, bool multithreaded)
        : Graph(numNodes), probability(probability) {
        
        if (!multithreaded) {
            generateGraph(numNodes, probability);
            return;
        }
        generateMultiThreadedGraph(numNodes, probability);
    }


void ErdosRenyiGraph::generateGraph(int numNodes, double probability) {

    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < numNodes; ++i) {
        for (int j = i + 1; j < numNodes; ++j) {
            if (static_cast<double>(rand()) / RAND_MAX < probability) {
                this->addEdges(i, j);
            }
        }
    }
}

void ErdosRenyiGraph::generateMultiThreadedGraph(int numNodes, double probability) {


    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);

    int numThreads = std::thread::hardware_concurrency();
   
    if (!numThreads) {
        numThreads = 4;
    }
    int rowsPerThread = numNodes/numThreads;
    std::vector<std::thread> threads;
    std::cout << "number of threads: " << numThreads << " Rows per thread: " << rowsPerThread << std::endl;
    int totalEdges = numNodes * (numNodes - 1) / 2;
    
    for (int t = 0; t < numThreads; t++) {
        int startRow = t * rowsPerThread;
        int endRow = (t == numThreads - 1) ? numNodes : startRow + rowsPerThread;
        
        threads.emplace_back([this,t, totalEdges, numThreads, startRow, endRow, probability, &generator, numNodes, seed]() {
            std::mt19937 generator(seed + startRow);
            std::uniform_real_distribution<double> distribution(0.0, 1.0);
            int startEdge = t * totalEdges / numThreads;
            int endEdge = (t + 1) * totalEdges / numThreads;

            for (int i = startRow; i < endRow; i++) {
                for (int j = i + 1; j < numNodes; j++) {
                    if (distribution(generator) < probability) {
                        this->addEdges(i, j);
                    }
                }
            }
                      
        });
    }


    for (auto& thread : threads) {
        thread.join();
    }

}

Graph* ErdosRenyiGraph::askGraphConfig() {
    Graph* G = Graph::askGraphConfig();
    double probability = 0.0;
    bool multiThreaded = false;
    std::cout << "Enter the probability: ";
    std::cin >> probability;
    std::cout << "selected  "<< probability << std::endl;
    std::cout << "Multi-threaded?";
    std::cin >> multiThreaded;
    std::cout << "now building: " << "erdosRenyi graph with " << G->getNumNodes() << " multi-threaded: " << multiThreaded << "\n";
    Graph* builtGraph =  new ErdosRenyiGraph(G->getNumNodes(), probability, multiThreaded);
    delete G;
    return builtGraph;
}

NewmanConfigModel::NewmanConfigModel(int numNodes, int numEdges)
    : Graph(numNodes), numEdges(numEdges) {
        
        this->numEdges = numEdges;
        this->createEdges();
}

Graph* NewmanConfigModel::askGraphConfig() {
    Graph* G = Graph::askGraphConfig();
    int numEdges = 0;
    std::cout << "Enter the number of Edges: ";
    std::cin >> numEdges;
    Graph* builtGraph = new NewmanConfigModel(G->getNumNodes(), numEdges);
    delete G;
    return builtGraph;
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

Graph* WattsStrogatzGraph::askGraphConfig() {
    Graph* G = Graph::askGraphConfig();
    int k = 0; 
    double beta = 0;
    std::cout << "Enter the mean degree: ";
    std::cin >> k;
    std::cout << "Enter a parameter Beta (0 < beta < 1): ";
    std::cin >> beta;

    if (beta > 1 || beta < 0) {
        beta = 0.5;
    }

    Graph* builtGraph = new WattsStrogatzGraph(G->getNumNodes(), k, beta);
    delete G;
    return builtGraph;
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

BarabasiAlbertGraph::BarabasiAlbertGraph(int numNodes, int m)
    : Graph(numNodes), m(m) {

        for (int i = 1; i <= m; i++) {
            addEdges(0, i);
        }

        for (int i = m + 1; i < numNodes; i++) {
            attachNode(i);
        }
}

void BarabasiAlbertGraph::attachNode(int newNode) {
    std::vector<int> nodes;
    
    for (int i = 0; i < numNodes; i++) {
        for (int degree = 0; degree < getDegree(i); i++) {
            nodes.push_back(i);
        }
    }


    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(nodes.begin(), nodes.end(), g);

    for (int i = 0; i < m; i++) {
        int targetNode = nodes[i];
        addEdges(newNode, targetNode);
    }
}

Graph* BarabasiAlbertGraph::askGraphConfig() {
    Graph* G = Graph::askGraphConfig();
    int m = 0; 
    std::cout << "Enter the paramter m: ";
    std::cin >> m;
    Graph* builtGraph = new BarabasiAlbertGraph(G->getNumNodes(), m);
    delete G;
    return builtGraph;
}

Graph* Graph::createGraph(const std::string& graphType) {
    if (graphType == "erG") {
        return ErdosRenyiGraph::askGraphConfig();
    } 
    else if (graphType == "nG") {
        return  NewmanConfigModel::askGraphConfig();
    }
    else if (graphType == "baG") {
        return BarabasiAlbertGraph::askGraphConfig();
    }
    else if (graphType == "wG") {
        return WattsStrogatzGraph::askGraphConfig();
    } else {
        std::cout << "Invalid graph type selected." << std::endl;
        return nullptr;
    }
}

