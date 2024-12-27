#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <queue>
#include <chrono>
#include "Graph.h"
#include "Flow.h"

class Algorithm {
private:
    Graph& graph; // Referencia al grafo sobre el que se ejecutará el algoritmo
    Flow flowManager; // Administrador de flujo
    std::chrono::duration<double> executionTime; // Tiempo de ejecución del algoritmo

public:
    Algorithm(Graph& g); // Constructor

    bool findAugmentingPath(std::vector<int>& path); // Buscar camino aumentante
    int updateFlow(const std::vector<int>& path); // Actualizar flujo
    int solve(); // Resolver el problema de flujo máximo
    double getExecutionTime() const; // Obtener el tiempo de ejecución
};

#endif // ALGORITHM_H
