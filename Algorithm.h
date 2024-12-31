// Algorithm.h
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Graph.h"
#include "State.h"
#include "Flow.h"
#include <chrono>
#include <climits>

class Algorithm {
public:
    struct Result {
        std::vector<std::pair<int, int>> source_flows; // vector de pares de enteros de fuentes y flujos
        std::vector<std::pair<int, int>> sink_flows; // vector de pares de enteros de sumideros y flujos
        int total_flow; // flujo total
        double time_ms; // tiempo en milisegundos
    };
    
    static Result solve(Graph& graph); // método para obtener el resultado

private:
    static int maxFlow(Graph& graph, int source, int sink); // método para calcular el flujo máximo
};

#endif // ALGORITHM_H