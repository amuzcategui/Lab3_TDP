// test_Graph.cpp
#include "Graph.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::cout << "Iniciando pruebas de la clase Graph...\n\n";

    // Test 1: Constructor y addEdge
    std::cout << "Probando constructor y addEdge... ";
    {
        Graph g(3);
        g.addEdge(0, 1, 10);
        assert(g.getCapacity(0, 1) == 10);
        assert(g.getCapacity(1, 0) == 0);
        
        const auto& adj = g.getAdj(0);
        assert(!adj.empty() && adj[0] == 1);
    }
    std::cout << "OK\n";

    // Test 2: Load from file
    std::cout << "Probando loadFromFile... ";
    {
        std::ofstream file("test_graph.txt");
        file << "0 1\n";      // sources
        file << "3 4\n";      // sinks
        file << "0 2 10\n";   // edges
        file << "2 3 5\n";
        file << "2 4 8\n";
        file.close();

        Graph g;
        bool loaded = g.loadFromFile("test_graph.txt");
        assert(loaded);
        assert(g.getCapacity(0, 2) == 10);
        assert(g.getCapacity(2, 3) == 5);
        assert(g.getCapacity(2, 4) == 8);
        
        std::remove("test_graph.txt");
    }
    std::cout << "OK\n";

    // Test 3: Constructor de copia
    std::cout << "Probando constructor de copia... ";
    {
        Graph g1(3);
        g1.addEdge(0, 1, 10);
        g1.addEdge(1, 2, 5);
        
        Graph g2(g1);
        assert(g2.getCapacity(0, 1) == 10);
        assert(g2.getCapacity(1, 2) == 5);
        assert(g2.size() == g1.size());
    }
    std::cout << "OK\n";

    std::cout << "\nTodas las pruebas de Graph pasaron exitosamente!\n";
    return 0;
}