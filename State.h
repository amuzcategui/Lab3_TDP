// State.h
#ifndef STATE_H
#define STATE_H

#include <vector>
#include <queue>
#include "Graph.h"
#include "Flow.h"

class State {
private:
    std::vector<int> level; // Niveles de los vértices
    std::vector<size_t> next; // Siguiente vértice a visitar
    Flow& flow; // Flujo
    int n; // Número de vértices}
    inline int calculateHeuristic(int u, int sink) const;
    int getDistance(const Graph& graph, int source, int sink) const;


public:
    // Constructor
    State(int vertices, Flow& f) : level(vertices, -1), next(vertices, 0), flow(f), n(vertices) {}

    // Métodos para BFS y DFS
    bool bfs(const Graph& graph, int source, int sink);
    int dfs(Graph& graph, int vertex, int sink, int flow);
    
    // Métodos para acceder a next
    std::vector<size_t>& getNextArray() { return next; }
    const std::vector<size_t>& getNextArray() const { return next; }
};

#endif // STATE_H