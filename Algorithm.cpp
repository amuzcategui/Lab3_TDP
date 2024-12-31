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
    
    Flow flow(graph.size());
    
    // Calcular el flujo máximo usando Dinic
    result.total_flow = maxFlow(graph, flow, superSource, superSink);
    
    // Calcular flujos de fuentes
    for (int source : graph.getSources()) {
        result.source_flows.push_back({source, flow.getOutgoingFlow(source)});
    }
    
    // Calcular flujos de sumideros
    for (int sink : graph.getSinks()) {
        result.sink_flows.push_back({sink, flow.getIncomingFlow(sink)});
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
 * @param flow Flujo actual
 * 
 * @param source Vértice origen
 * 
 * @param sink Vértice destino
 * 
 * @return Result Estructura con los resultados del algoritmo
 */
int Algorithm::maxFlow(Graph& graph, Flow& flow, int source, int sink) {
    State state(graph.size(), flow);
    int total_flow = 0;
    
    while (state.bfs(graph, source, sink)) {
        std::fill(state.getNextArray().begin(), state.getNextArray().end(), 0);
        
        // Optimización: Buscar múltiples flujos bloqueantes en el mismo grafo de niveles
        int blocking_flow;
        do {
            blocking_flow = state.dfs(graph, source, sink, INT_MAX);
            total_flow += blocking_flow;
        } while (blocking_flow > 0);
    }
    
    return total_flow;
}

