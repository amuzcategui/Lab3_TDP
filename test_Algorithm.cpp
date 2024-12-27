#include "Flow.h"
#include "Algorithm.h"
#include "Graph.h"
#include <cassert>
#include <iostream>
#include <sstream>

int main() {
    std::cout << "Iniciando pruebas de Algorithm..." << std::endl;

    try {
        // Test 1: Grafo simple
        {
            std::cout << "\nProbando grafo simple..." << std::endl;
            Graph g;
            std::vector<int> sources = {0};
            std::vector<int> sinks = {3};

            // Crear un grafo simple:
            // 0 -> 1 -> 2 -> 3
            // Capacidades: 5 en todas las aristas
            g.addEdge(0, 1, 5);
            g.addEdge(1, 2, 5);
            g.addEdge(2, 3, 5);

            g.addSuperSourceAndSink(sources, sinks);

            Algorithm alg(g);
            int maxFlow = alg.solve();

            assert(maxFlow == 5 && "El flujo máximo debería ser 5");
            std::cout << "Test de grafo simple: PASO" << std::endl;
        }

        // Test 2: Grafo con múltiples caminos
        {
            std::cout << "\nProbando grafo con múltiples caminos..." << std::endl;
            Graph g;
            std::vector<int> sources = {0};
            std::vector<int> sinks = {3};

            // Crear un grafo con múltiples caminos:
            // 0 -> 1 -> 3
            // 0 -> 2 -> 3
            g.addEdge(0, 1, 10);
            g.addEdge(1, 3, 10);
            g.addEdge(0, 2, 10);
            g.addEdge(2, 3, 10);

            g.addSuperSourceAndSink(sources, sinks);

            Algorithm alg(g);
            int maxFlow = alg.solve();

            assert(maxFlow == 20 && "El flujo máximo debería ser 20");
            std::cout << "Test de grafo con múltiples caminos: PASO" << std::endl;
        }

        // Test 3: Grafo con múltiples fuentes y sumideros
        {
            std::cout << "\nProbando grafo con múltiples fuentes y sumideros..." << std::endl;
            Graph g;
            std::vector<int> sources = {0, 1};
            std::vector<int> sinks = {4, 5};

            // Crear grafo con múltiples fuentes y sumideros
            g.addEdge(0, 2, 10);
            g.addEdge(1, 2, 10);
            g.addEdge(2, 3, 15);
            g.addEdge(3, 4, 10);
            g.addEdge(3, 5, 10);

            g.addSuperSourceAndSink(sources, sinks);

            Algorithm alg(g);
            int maxFlow = alg.solve();

            assert(maxFlow == 15 && "El flujo máximo debería ser 15");
            std::cout << "Test de grafo con múltiples fuentes y sumideros: PASO" << std::endl;
        }

        // Test 4: Grafo sin camino
        {
            std::cout << "\nProbando grafo sin camino..." << std::endl;
            Graph g;
            std::vector<int> sources = {0};
            std::vector<int> sinks = {1};

            // Crear grafo sin camino entre fuente y sumidero
            g.addEdge(0, 2, 10);
            g.addEdge(3, 1, 10);

            g.addSuperSourceAndSink(sources, sinks);

            Algorithm alg(g);
            int maxFlow = alg.solve();

            assert(maxFlow == 0 && "El flujo máximo debería ser 0");
            std::cout << "Test de grafo sin camino: PASO" << std::endl;
        }

        // Test 5: Tiempo de ejecución
        {
            std::cout << "\nProbando tiempo de ejecución..." << std::endl;
            Graph g;
            std::vector<int> sources = {0};
            std::vector<int> sinks = {1};

            g.addEdge(0, 1, 10);
            g.addSuperSourceAndSink(sources, sinks);

            Algorithm alg(g);
            alg.solve();

            double time = alg.getExecutionTime();
            assert(time >= 0 && "El tiempo de ejecución debe ser no negativo");
            std::cout << "Test de tiempo de ejecución: PASO" << std::endl;
        }

        std::cout << "\nTodas las pruebas pasaron exitosamente!" << std::endl;
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error durante las pruebas: " << e.what() << std::endl;
        return 1;
    }
}
