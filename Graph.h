// Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include "State.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

class Graph {
private:
    State state; // Estado del grafo

public:
    Graph(); // Constructor

    void addEdge(int from, int to, int capacity); // Añadir arista
    int getResidualCapacity(int from, int to) const; // Obtener capacidad residual
    void updateFlow(int from, int to, int flow); // Actualizar flujo
    void resetFlows(); // Reiniciar flujos

    int getNumVertices() const; // Obtener número de vértices
    int getSuperSource() const; // Obtener nodo fuente
    int getSuperSink() const; // Obtener nodo sumidero
    int getCurrentFlow(int from, int to) const; // Obtener flujo actual
    std::vector<int> getNeighbors(int vertex) const; // Obtener vecinos de un nodo

    // Añadir nodo fuente y sumidero
    void addSuperSourceAndSink(const std::vector<int>& sources, const std::vector<int>& sinks);
    
    // Cargar grafo desde archivo
    void loadFromFile(const std::string& filename, std::vector<int>& sources, std::vector<int>& sinks);
};
#endif