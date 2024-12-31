#include "Algorithm.h"

/**
 * @brief Método para calcular el flujo máximo con el algoritmo de Dinic
 * 
 * @param graph Grafo de entrada
 * 
 * @return Result Estructura con los resultados del algoritmo
 */
Algorithm::Result Algorithm::solve(Graph& graph) {
    Result result;
    auto start = std::chrono::high_resolution_clock::now();
    
    int superSource, superSink;
    graph.addSuperSourceAndSink(superSource, superSink);
    
    result.total_flow = maxFlow(graph, superSource, superSink);
    
    for (int source : graph.getSources()) {
        int flow = 0;
        for (int v : graph.getAdj(source)) {
            flow += std::max(0, graph.getCurrentFlow(source, v));
        }
        result.source_flows.push_back({source, flow});
    }
    
    for (int sink : graph.getSinks()) {
        int flow = 0;
        for (int u : graph.getAdj(sink)) {
            flow += std::max(0, graph.getCurrentFlow(u, sink));
        }
        result.sink_flows.push_back({sink, flow});
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    result.time_ms = std::chrono::duration<double, std::milli>(end - start).count();
    
    return result;
}


/**
 * @brief Método para calcular el flujo máximo con el algoritmo de Edmonds-Karp
 * 
 * @param graph Grafo de entrada
 * 
 * @return Result Estructura con los resultados del algoritmo
 */
int Algorithm::maxFlow(Graph& graph, int source, int sink) {
    State state(graph.size());
    int total_flow = 0;
    
    while (state.bfs(graph, source, sink)) {
        std::fill(state.getNextArray().begin(), state.getNextArray().end(), 0);
        
        while (int flow = state.dfs(graph, source, sink, INT_MAX)) {
            total_flow += flow;
        }
    }
    
    return total_flow;
}
