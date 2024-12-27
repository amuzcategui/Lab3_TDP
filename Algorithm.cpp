#include "Algorithm.h"

/**
 * Constructor de la clase Algorithm.
 * 
 * @param g Referencia al grafo sobre el que se ejecutará el algoritmo.
 * 
 * @return Instancia de Algorithm.
 * 
 */
Algorithm::Algorithm(Graph& g) : graph(g), flowManager() {}

/**
 * Método que busca un camino aumentante en el grafo.
 * 
 * @param path Vector donde se almacenará el camino aumentante.
 * 
 * @return true si se encontró un camino aumentante, false en caso contrario.
 * 
 */
bool Algorithm::findAugmentingPath(std::vector<int>& path) {
    int numVertices = graph.getNumVertices();
    std::vector<bool> visited(numVertices, false);
    std::vector<int> parent(numVertices, -1);
    std::queue<int> q;

    int source = graph.getSuperSource();
    int sink = graph.getSuperSink();

    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int next = 0; next < numVertices; next++) {
            if (!visited[next] && graph.getResidualCapacity(current, next) > 0) {
                parent[next] = current;
                visited[next] = true;
                q.push(next);

                if (next == sink) {
                    path.clear();
                    for (int v = sink; v != -1; v = parent[v]) {
                        path.insert(path.begin(), v);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Método que actualiza el flujo en el grafo siguiendo un camino aumentante.
 * 
 * @param path Vector que contiene el camino aumentante.
 * 
 * @return Flujo total del camino aumentante.
 * 
 */
int Algorithm::updateFlow(const std::vector<int>& path) {
    if (path.empty()) return 0;
    
    int minFlow = std::numeric_limits<int>::max();
    for (size_t i = 0; i < path.size() - 1; i++) {
        int u = path[i];
        int v = path[i + 1];
        int residualCap = graph.getResidualCapacity(u, v);
        minFlow = std::min(minFlow, residualCap);
    }

    for (size_t i = 0; i < path.size() - 1; i++) {
        int u = path[i];
        int v = path[i + 1];
        graph.updateFlow(u, v, minFlow);
    }

    return minFlow;
}

/**
 * Método que resuelve el problema de flujo máximo en el grafo.
 * 
 * @return Flujo total máximo que se puede enviar desde las fuentes a los sumideros.
 * 
 */
int Algorithm::solve() {
    std::vector<int> path;
    int totalFlow = 0;
    
    graph.resetFlows();
    
    while (findAugmentingPath(path)) {
        int pathFlow = updateFlow(path);
        totalFlow += pathFlow;
    }
    
    return totalFlow;
}

/**
 * Método que devuelve el tiempo de ejecución del algoritmo.
 * 
 * @return Tiempo de ejecución en milisegundos.
 * 
 */
double Algorithm::getExecutionTime() const {
    return executionTime.count() * 1000.0;
}
