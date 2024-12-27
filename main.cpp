#include "Graph.h"
#include "Algorithm.h"
#include "Flow.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>


int main() {
    bool running = true;

    while (running) {
        std::cout << "\n=== Menú Principal ===\n";
        std::cout << "1. Resolver nuevo problema\n";
        std::cout << "2. Salir\n";
        std::cout << "Seleccione una opción: ";
        int option;
        std::cin >> option;

        switch (option) {
            case 1: {
                // Resolver nuevo problema
                std::cout << "Ingrese el nombre del archivo de entrada: ";
                std::string filename;
                std::cin >> filename;

                try {
                    Graph graph;
                    std::vector<int> sources, sinks;

                    // Cargar datos del archivo
                    graph.loadFromFile(filename, sources, sinks);

                    // Crear fuente y sumidero artificiales
                    graph.addSuperSourceAndSink(sources, sinks);

                    // Resolver el problema con el algoritmo
                    Algorithm algorithm(graph);

                    auto start = std::chrono::high_resolution_clock::now();
                    int totalFlow = algorithm.solve();
                    auto end = std::chrono::high_resolution_clock::now();
                    double duration = std::chrono::duration<double, std::milli>(end - start).count();

                    // Formato de salida
                    std::cout << "\nFuentes:\n";
                    for (int source : sources) {
                        // Mostrar el flujo actual desde super source a cada fuente
                        int sourceFlow = graph.getCurrentFlow(graph.getSuperSource(), source);
                        std::cout << source << " " << sourceFlow << "\n";
                    }

                    std::cout << "\nSumideros:\n";
                    for (int sink : sinks) {
                        // Mostrar el flujo actual desde cada sumidero al super sink
                        int sinkFlow = graph.getCurrentFlow(sink, graph.getSuperSink());
                        std::cout << sink << " " << sinkFlow << "\n";
                    }

                    std::cout << "\nFlujo Total: " << totalFlow << "\n";
                    std::cout << "Tiempo: " << std::fixed << std::setprecision(1) << duration << " [ms]\n";

                } catch (const std::exception& ex) {
                    std::cerr << "Error: " << ex.what() << "\n";
                }
                break;
            }

            case 2:
                running = false;
                std::cout << "\n¡Gracias por usar el programa!\n";
                break;

            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    }

    return 0;
}
