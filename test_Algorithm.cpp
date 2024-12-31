#include "Algorithm.h"
#include "Graph.h"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Iniciando pruebas de Algorithm...\n\n";

    // Test 1: Flujo simple
    std::cout << "Probando flujo simple... ";
    {
        Graph g(3);
        // Definir fuentes y sumideros antes de agregar aristas
        std::ofstream file("temp_test.txt");
        file << "0\n";      // source
        file << "2\n";      // sink
        file << "0 1 5\n";  // edges
        file << "1 2 5\n";
        file.close();
        
        g.loadFromFile("temp_test.txt");
        std::remove("temp_test.txt");
        
        Algorithm::Result result = Algorithm::solve(g);
        assert(result.total_flow == 5);
    }
    std::cout << "OK\n";

    // Test 2: Múltiples caminos
    std::cout << "Probando múltiples caminos... ";
    {
        Graph g(4);
        // Crear archivo temporal con múltiples caminos
        std::ofstream file("temp_test.txt");
        file << "0\n";        // source
        file << "3\n";        // sink
        file << "0 1 10\n";   // edges
        file << "1 3 10\n";
        file << "0 2 10\n";
        file << "2 3 10\n";
        file.close();
        
        g.loadFromFile("temp_test.txt");
        std::remove("temp_test.txt");
        
        Algorithm::Result result = Algorithm::solve(g);
        assert(result.total_flow == 20);
    }
    std::cout << "OK\n";

    std::cout << "\nTodas las pruebas de Algorithm pasaron exitosamente!\n";
    return 0;
}