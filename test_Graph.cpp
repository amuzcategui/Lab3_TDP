#include "Graph.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    std::cout << "Iniciando pruebas de la clase Graph...\n\n";

    // Crear archivo temporal de prueba
    std::string testFile = "test_graph.txt";
    {
        std::ofstream file(testFile);
        file << "0 6\n";        // sources
        file << "5 7\n";        // sinks
        file << "0 1 10\n";     // edges
        file << "0 2 10\n";
        file << "1 3 15\n";
        file << "2 4 25\n";
        file << "3 2 6\n";
        file << "3 5 10\n";
        file << "3 7 5\n";
        file << "4 5 10\n";
        file << "6 1 5\n";
    }

    // Prueba del constructor
    std::cout << "Probando constructor... ";
    {
        Graph graph;
        assert(graph.getNumVertices() == 0);
    }
    std::cout << "OK\n";

    // Prueba de addEdge
    std::cout << "Probando addEdge... ";
    {
        Graph graph;

        // Añadir una arista y verificar
        graph.addEdge(0, 1, 10);
        assert(graph.getResidualCapacity(0, 1) == 10);
        assert(graph.getCurrentFlow(0, 1) == 0);

        // Verificar que el número de vértices se actualiza
        assert(graph.getNumVertices() >= 2);

        // Añadir más aristas
        graph.addEdge(1, 2, 15);
        graph.addEdge(0, 2, 20);

        // Verificar vecinos
        std::vector<int> neighbors = graph.getNeighbors(0);
        assert(neighbors.size() == 2); // Debe tener dos vecinos
    }
    std::cout << "OK\n";

    // Prueba de operaciones de flujo
    std::cout << "Probando operaciones de flujo... ";
    {
        Graph graph;

        // Configurar un pequeño grafo
        graph.addEdge(0, 1, 10);
        graph.addEdge(1, 2, 8);

        // Actualizar flujo
        graph.updateFlow(0, 1, 5);
        assert(graph.getCurrentFlow(0, 1) == 5);
        assert(graph.getResidualCapacity(0, 1) == 5);

        // Resetear flujos
        graph.resetFlows();
        assert(graph.getCurrentFlow(0, 1) == 0);
        assert(graph.getResidualCapacity(0, 1) == 10);
    }
    std::cout << "OK\n";

    // Prueba de super source y sink
    std::cout << "Probando super source y sink... ";
    {
        Graph graph;

        // Configurar grafo base
        graph.addEdge(0, 1, 10);
        graph.addEdge(1, 2, 8);
        graph.addEdge(2, 3, 12);

        std::vector<int> sources = {0};
        std::vector<int> sinks = {3};

        // Añadir super source y sink
        graph.addSuperSourceAndSink(sources, sinks);

        // Verificar que se crearon los nuevos nodos
        int superSource = graph.getSuperSource();
        int superSink = graph.getSuperSink();

        assert(superSource >= 0);
        assert(superSink > superSource);

        // Verificar que hay conexiones desde super source y hacia super sink
        assert(graph.getResidualCapacity(superSource, 0) > 0);
        assert(graph.getResidualCapacity(3, superSink) > 0);
    }
    std::cout << "OK\n";

    // Prueba de carga desde archivo
    std::cout << "Probando carga desde archivo... ";
    {
        Graph graph;
        std::vector<int> sources, sinks;

        try {
            // Cargar grafo desde archivo
            graph.loadFromFile(testFile, sources, sinks);

            // Verificar fuentes y sumideros
            assert(sources.size() == 2);
            assert(sinks.size() == 2);
            assert(sources[0] == 0);
            assert(sources[1] == 6);
            assert(sinks[0] == 5);
            assert(sinks[1] == 7);

            // Verificar algunas aristas
            assert(graph.getResidualCapacity(0, 1) == 10);
            assert(graph.getResidualCapacity(0, 2) == 10);
            assert(graph.getResidualCapacity(1, 3) == 15);

            // Limpiar archivo temporal
            std::remove(testFile.c_str());

        } catch (const std::exception& e) {
            std::remove(testFile.c_str());
            std::cerr << "Error en la prueba de carga de archivo: " << e.what() << std::endl;
            assert(false);
        }
    }
    std::cout << "OK\n";

    std::cout << "\nTodas las pruebas pasaron exitosamente!\n";
    return 0;
}
