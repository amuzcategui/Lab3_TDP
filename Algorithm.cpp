#include "Algorithm.h"
#include <tuple> // Para std::priority_queue con tuplas
/**
 * Constructor de la clase Algorithm.
 * 
 * @param g Grafo sobre el que se ejecutará el algoritmo.
 * 
 */
Algorithm::Algorithm(Graph& g) : graph(g), flowManager() {}

/**
 * Construye el grafo de niveles usando BFS.
 * 
 * @param level Vector que almacenará los niveles de cada vértice.
 * 
 * @return true si existe un camino al sumidero, false en caso contrario.
 */


bool Algorithm::buildLevelGraph(std::vector<int>& level) {
    int numVertices = graph.getNumVertices();
    level.assign(numVertices, -1);
    
    using NodeCapacity = std::pair<int, int>; // (capacidad, nodo)
    std::priority_queue<NodeCapacity> pq;

    int source = graph.getSuperSource();
    int sink = graph.getSuperSink();
    
    level[source] = 0;
    pq.emplace(std::numeric_limits<int>::max(), source); // Mayor capacidad primero

    while (!pq.empty()) {
        auto [capacity, current] = pq.top();
        pq.pop();

        for (int next : graph.getNeighbors(current)) {
            int residualCapacity = graph.getResidualCapacity(current, next);
            if (level[next] < 0 && residualCapacity > 0) {
                level[next] = level[current] + 1;
                pq.emplace(residualCapacity, next);
            }
        }
    }
    
    return level[sink] >= 0;
}

/**
 * Encuentra un flujo bloqueante usando DFS.
 * 
 * @param vertex Vértice actual.
 * @param flow Flujo actual.
 * @param level Vector de niveles.
 * @param start Vector de índices de inicio para cada vértice.
 * 
 * @return Flujo bloqueante encontrado.
 */
int Algorithm::findBlockingFlow(int vertex, int flow, std::vector<int>& level, std::vector<int>& start) {
    if (vertex == graph.getSuperSink()) {
        return flow;
    }

    const auto& neighbors = graph.getNeighbors(vertex); // Guardar vecinos una vez
    for (; start[vertex] < static_cast<int>(neighbors.size()); start[vertex]++) {
        int next = neighbors[start[vertex]];

        if (level[next] == level[vertex] + 1 && graph.getResidualCapacity(vertex, next) > 0) {
            int currFlow = std::min(flow, graph.getResidualCapacity(vertex, next));
            int tempFlow = findBlockingFlow(next, currFlow, level, start);

            if (tempFlow > 0) {
                graph.updateFlow(vertex, next, tempFlow);
                return tempFlow;
            }
        }
    }

    return 0;
}


/**
 * Implementa el algoritmo de Dinic para encontrar el flujo máximo.
 * 
 * @return Flujo máximo encontrado.
 */
int Algorithm::solve() {
    auto start = std::chrono::high_resolution_clock::now();
    
    int totalFlow = 0;
    std::vector<int> level;
    
    graph.resetFlows();
    
    // Mientras exista un camino válido en el grafo de niveles
    while (buildLevelGraph(level)) {
        std::vector<int> start(graph.getNumVertices(), 0);
        
        // Encuentra flujos bloqueantes hasta saturar el grafo de niveles
        int flow;
        while ((flow = findBlockingFlow(graph.getSuperSource(), 
                                      std::numeric_limits<int>::max(), 
                                      level, 
                                      start)) != 0) {
            totalFlow += flow;
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    executionTime = end - start;
    
    return totalFlow;
}

/**
 * Devuelve el tiempo de ejecución del algoritmo en milisegundos.
 * 
 * @return Tiempo de ejecución del algoritmo.
 */
double Algorithm::getExecutionTime() const {
    return executionTime.count() * 1000.0;
}