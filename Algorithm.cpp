#include "Algorithm.h"

Algorithm::Algorithm(Graph& g) : graph(g), flowManager() {}

bool Algorithm::findAugmentingPath(std::vector<int>& path) {
    int numVertices = graph.getNumVertices();
    std::vector<bool> visited(numVertices, false);
    std::vector<int> parent(numVertices, -1);
    std::queue<int> q;

    int source = graph.getSuperSource();
    int sink = graph.getSuperSink();

    q.push(source);
    visited[source] = true;

    // BFS para encontrar camino aumentante
    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Verificar todos los vecinos posibles
        for (int next = 0; next < numVertices; next++) {
            // Si no está visitado y hay capacidad residual positiva
            if (!visited[next] && graph.getResidualCapacity(current, next) > 0) {
                parent[next] = current;
                visited[next] = true;
                q.push(next);

                // Si llegamos al sink, reconstruir el camino
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

int Algorithm::updateFlow(const std::vector<int>& path) {
    if (path.empty()) return 0;
    
    // Encontrar la capacidad residual mínima en el camino
    int minFlow = std::numeric_limits<int>::max();
    for (size_t i = 0; i < path.size() - 1; i++) {
        int u = path[i];
        int v = path[i + 1];
        int residualCap = graph.getResidualCapacity(u, v);
        minFlow = std::min(minFlow, residualCap);
    }

    // Actualizar los flujos a lo largo del camino
    for (size_t i = 0; i < path.size() - 1; i++) {
        int u = path[i];
        int v = path[i + 1];
        graph.updateFlow(u, v, minFlow);
    }

    return minFlow;
}

int Algorithm::solve() {
    std::vector<int> path;
    int totalFlow = 0;
    
    // Asegurarse de que empezamos con flujos en cero
    graph.resetFlows();
    
    // Mientras exista un camino aumentante
    while (findAugmentingPath(path)) {
        // Actualizar el flujo a lo largo del camino
        int pathFlow = updateFlow(path);
        totalFlow += pathFlow;
    }
    
    return totalFlow;
}

double Algorithm::getExecutionTime() const {
    return executionTime.count() * 1000.0;
}
