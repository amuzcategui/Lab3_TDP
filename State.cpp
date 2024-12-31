#include <queue>
#include <vector>
#include <limits>
#include "State.h"

/**
 * @brief Calcula la distancia mínima estimada entre dos nodos (heurística optimizada).
 * 
 * @param u Nodo actual.
 * @param sink Nodo destino.
 * 
 * @return int Heurística (distancia estimada).
 */
inline int State::calculateHeuristic(int u, int sink) const {
    return abs(u - sink); // Penaliza caminos de baja capacidad, evitando división por cero
}

/**
 * @brief BFS optimizado para encontrar niveles y caminos disponibles.
 * 
 * @param graph Grafo de entrada.
 * @param source Nodo origen.
 * @param sink Nodo destino.
 * 
 * @return bool Verdadero si se encuentra un camino, falso en caso contrario.
 */
bool State::bfs(const Graph& graph, int source, int sink) {
    std::fill(level.begin(), level.end(), -1);
    level[source] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    pq.emplace(0, source);

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v : graph.getAdj(u)) {
            int residual = graph.getCapacity(u, v) - flow.getCurrentFlow(u, v);
            if (level[v] == -1 && residual > 0) {
                level[v] = level[u] + 1;

                if (v == sink) {
                    return true; // Termina cuando alcanzamos el destino
                }

                int heuristic = calculateHeuristic(v, sink);
                pq.emplace(heuristic, v);
            }
        }
    }

    return false; // No se encontró un camino
}

/**
 * @brief DFS optimizado para buscar el flujo máximo.
 * 
 * @param graph Grafo de entrada.
 * @param u Nodo actual.
 * @param sink Nodo destino.
 * @param flow_limit Flujo máximo permitido.
 * 
 * @return int Flujo encontrado.
 */
int State::dfs(Graph& graph, int u, int sink, int flow_limit) {
    if (u == sink) return flow_limit;

    for (; next[u] < graph.getAdj(u).size(); ++next[u]) {
        int v = graph.getAdj(u)[next[u]];
        int residual = graph.getCapacity(u, v) - flow.getCurrentFlow(u, v);

        if (level[v] == level[u] + 1 && residual > 0) {
            int bottleneck = dfs(graph, v, sink, std::min(flow_limit, residual));
            if (bottleneck > 0) {
                flow.updateFlow(u, v, bottleneck);
                return bottleneck;
            }
        }
    }

    return 0;
}


