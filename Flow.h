#ifndef FLOW_H
#define FLOW_H

// TENGO QUE INTEGRARLO BIEN EN ALGORITHM Y EN STATE
#include <vector>

class Flow {
private:
    std::vector<std::vector<int>> flow_matrix; // Matriz de flujo
    int num_vertices; // Número de vértices

public:
    // Constructor
    Flow(int vertices = 0);

    // Constructor de copia
    Flow(const Flow& other);

    // Métodos principales
    void updateFlow(int u, int v, int flow);
    int getCurrentFlow(int u, int v) const;
    void resize(int newSize);
    void clear();

    // Método para obtener el flujo total que sale de un vértice
    int getOutgoingFlow(int vertex) const;

    // Método para obtener el flujo total que entra a un vértice
    int getIncomingFlow(int vertex) const;
};

#endif // FLOW_H
