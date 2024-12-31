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
        assert(g.getCurrentFlow(0, 1) == 0);
        
        // Verificar que la arista residual se creó
        assert(g.getCapacity(1, 0) == 0);
        
        // Verificar lista de adyacencia
        const auto& adj = g.getAdj(0);
        assert(!adj.empty() && adj[0] == 1);
    }
    std::cout << "OK\n";

    // Test 2: Load from file
    std::cout << "Probando loadFromFile... ";
    {
        // Crear archivo temporal de prueba
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
        
        // Verificar estructura
        assert(g.getCapacity(0, 2) == 10);
        assert(g.getCapacity(2, 3) == 5);
        assert(g.getCapacity(2, 4) == 8);
        
        std::remove("test_graph.txt");
    }
    std::cout << "OK\n";

    // Test 3: Getters
    std::cout << "Probando getters... ";
    {
        // Crear archivo temporal para probar getters
        std::ofstream file("test_getters.txt");
        file << "0 1\n";      // sources
        file << "3 4\n";      // sinks
        file << "0 2 10\n";   // edges
        file << "1 2 8\n";
        file.close();

        Graph g;
        g.loadFromFile("test_getters.txt");
        
        // Verificar getSources y getSinks
        const auto& sources = g.getSources();
        const auto& sinks = g.getSinks();
        
        assert(sources.size() == 2);
        assert(sources[0] == 0 && sources[1] == 1);
        assert(sinks.size() == 2);
        assert(sinks[0] == 3 && sinks[1] == 4);
        
        std::remove("test_getters.txt");
    }
    std::cout << "OK\n";

    std::cout << "\nTodas las pruebas de Graph pasaron exitosamente!\n";
    return 0;
}