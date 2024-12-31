// main.cpp
#include <iostream>
#include <string>
#include "Graph.h"
#include "Algorithm.h"

int main() {
    auto printResult = [](const Algorithm::Result& result) {
        std::cout << "\nFuentes:\n";
        for (const auto& [source, flow] : result.source_flows) {
            std::cout << source << " " << flow << "\n";
        }
        
        std::cout << "\nSumideros:\n";
        for (const auto& [sink, flow] : result.sink_flows) {
            std::cout << sink << " " << flow << "\n";
        }
        
        std::cout << "\nFlujo Total: " << result.total_flow << "\n";
        std::cout << "Tiempo: " << result.time_ms << " [ms]\n";
    };

    std::string filename;
    Graph graph;
    
    while (true) {
        std::cout << "\n=== Menú Principal ===\n";
        std::cout << "1. Resolver nuevo problema\n";
        std::cout << "2. Salir\n";
        std::cout << "Seleccione una opción: ";
        
        int option;
        std::cin >> option;
        
        if (option == 2) {
            std::cout << "¡Gracias por usar el programa!\n";
            break;}
        
        if (option == 1) {
            std::cout << "Ingrese nombre del archivo: ";
            std::cin >> filename;
            
            if (graph.loadFromFile(filename)) {
                Algorithm::Result result = Algorithm::solve(graph);
                printResult(result);
            }
        }

        if (option != 1 && option != 2) {
            std::cout << "Opción inválida\n";
        }
    }
    
    return 0;
}
