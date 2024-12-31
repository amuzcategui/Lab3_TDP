#include "State.h"

/**
 * @brief Método para realizar una búsqueda en amplitud
 * 
 * @param graph Grafo de entrada
 * @param source Vértice origen
 * @param sink Vértice destino
 * 
 * @return bool Verdadero si se encontró un camino, falso en caso contrario
 */
bool State::bfs(const Graph& graph, int source, int sink) {
    std::fill(level.begin(), level.end(), -1);
    level[source] = 0;
    
    std::queue<int> q;
    q.push(source);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : graph.getAdj(u)) {
            if (level[v] < 0 && graph.getCapacity(u, v) > 0) {
                level[v] = level[u] + 1;
                q.push(v);
            }
        }
    }
    
    return level[sink] >= 0;
}

/**
 * @brief Método para realizar una búsqueda en profundidad
 * 
 * @param graph Grafo de entrada
 * @param u Vértice actual
 * @param sink Vértice destino
 * @param flow Flujo actual
 * 
 * @return int Flujo encontrado
 */
int State::dfs(Graph& graph, int u, int sink, int flow) {
    if (u == sink) return flow;
    
    for (; next[u] < graph.getAdj(u).size(); next[u]++) {
        int v = graph.getAdj(u)[next[u]];
        
        if (level[v] == level[u] + 1 && graph.getCapacity(u, v) > 0) {
            int curr_flow = std::min(flow, graph.getCapacity(u, v));
            int temp_flow = dfs(graph, v, sink, curr_flow);
            
            if (temp_flow > 0) {
                graph.updateCapacity(u, v, temp_flow);
                graph.updateFlow(u, v, temp_flow);  
                return temp_flow;
            }
        }
    }
    
    return 0;
}