#include "Flow.h"

/**
 * @brief Constructor de la clase Flow
 * 
 * @param vertices Número de vértices
 * 
 */
Flow::Flow(int vertices) : num_vertices(vertices) {
    resize(vertices);
}

/**
 * @brief Constructor de copia de la clase Flow
 * 
 * @param other Flujo a copiar
 * 
 */
Flow::Flow(const Flow& other) : 
    flow_matrix(other.flow_matrix),
    num_vertices(other.num_vertices) {}

/**
 * @brief Actualiza el flujo entre dos vértices
 * 
 * @param u Vértice origen
 * @param v Vértice destino
 * @param flow Flujo
 * 
 */
void Flow::updateFlow(int u, int v, int flow) {
    flow_matrix[u][v] += flow;
    flow_matrix[v][u] -= flow;
}

/**
 * @brief Obtiene el flujo actual entre dos vértices
 * 
 * @param u Vértice origen
 * @param v Vértice destino
 * 
 * @return int Flujo actual
 * 
 */
int Flow::getCurrentFlow(int u, int v) const {
    return flow_matrix[u][v];
}

/**
 * @brief Redimensiona la matriz de flujo
 * 
 * @param newSize Nuevo tamaño de la matriz
 * 
 */
void Flow::resize(int newSize) {
    num_vertices = newSize;
    flow_matrix.resize(num_vertices, std::vector<int>(num_vertices, 0));
}

/**
 * @brief Limpia la matriz de flujo
 * 
 */
void Flow::clear() {
    flow_matrix.clear();
    num_vertices = 0;
}

/**
 * @brief Obtiene el flujo total que sale de un vértice
 * 
 * @param vertex Vértice
 * 
 * @return int Flujo total
 * 
 */
int Flow::getOutgoingFlow(int vertex) const {
    int total = 0;
    for (int v = 0; v < num_vertices; ++v) {
        if (flow_matrix[vertex][v] > 0) {
            total += flow_matrix[vertex][v];
        }
    }
    return total;
}

/**
 * @brief Obtiene el flujo total que entra a un vértice
 * 
 * @param vertex Vértice
 * 
 * @return int Flujo total
 * 
 */
int Flow::getIncomingFlow(int vertex) const {
    int total = 0;
    for (int u = 0; u < num_vertices; ++u) {
        if (flow_matrix[u][vertex] > 0) {
            total += flow_matrix[u][vertex];
        }
    }
    return total;
}

/**
 * @brief Obtiene la capacidad residual máxima de un vértice
 * 
 * @param u Vértice
 * 
 * @return int Capacidad residual máxima
 * 
 */
int Flow::getMaxResidual(int u) {
    int total = 0;
    for (int v = 0; v < num_vertices; ++v) {
        total += flow_matrix[u][v];
    }
    return total;
}   