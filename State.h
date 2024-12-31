// State.h
#ifndef STATE_H
#define STATE_H

#include <vector>
#include <queue>
#include "Graph.h"

class State {
private:
    std::vector<int> level; // Niveles de los vértices
    std::vector<size_t> next; // Siguiente vértice a visitar
    int n; // Número de vértices

public:
    // Constructor
    State(int vertices) : level(vertices, -1), next(vertices, 0), n(vertices) {}
    
    // Métodos para resetear el estado
    void reset() {
        std::fill(level.begin(), level.end(), -1);
        std::fill(next.begin(), next.end(), 0);
    }
    
    // Métodos para BFS y DFS
    bool bfs(const Graph& graph, int source, int sink);
    int dfs(Graph& graph, int vertex, int sink, int flow);
    
    // Métodos para acceder a level
    int getLevel(int vertex) const { return level[vertex]; }
    void setLevel(int vertex, int l) { level[vertex] = l; }
    
    // Métodos para acceder a next
    size_t getNext(int vertex) const { return next[vertex]; }
    void setNext(int vertex, size_t n) { next[vertex] = n; }
    std::vector<size_t>& getNextArray() { return next; }
    const std::vector<size_t>& getNextArray() const { return next; }
};

#endif // STATE_H