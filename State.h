// State.h
#ifndef STATE_H
#define STATE_H

#include <unordered_map>
#include <vector>

class State {
private:
    // Lista de adyacencia
    std::unordered_map<int, std::unordered_map<int, int>> adjacencyList;
    
    // Lista de flujos
    std::unordered_map<int, std::unordered_map<int, int>> flowList;
    
    // Nodos fuente y sumidero
    int superSource;
    int superSink;
    
    // Número de vértices
    int numVertices;

public:
    State();

    // Métodos de acceso básicos
    void setNumVertices(int num);
    int getNumVertices() const;
    void setSuperSource(int source);
    void setSuperSink(int sink);
    int getSuperSource() const;
    int getSuperSink() const;

    // Métodos para manejar aristas y flujos
    void addEdge(int from, int to, int capacity);
    int getCapacity(int from, int to) const;
    int getFlow(int from, int to) const;
    void updateFlow(int from, int to, int additionalFlow);
    int getResidualCapacity(int from, int to) const;
    void resetFlows();

    // Métodos auxiliares
    std::vector<int> getNeighbors(int vertex) const;
    bool hasEdge(int from, int to) const;
};
#endif