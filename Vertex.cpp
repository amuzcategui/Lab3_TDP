// Vertex.cpp
#include "Vertex.h"

// Constructor
Vertex::Vertex(int id) : id(id) {}

// Añadir vecino
void Vertex::addNeighbor(int vertex) {
    neighbors.push_back(vertex);
}

// Obtener ID del vértice
int Vertex::getId() const {
    return id;
}

// Obtener lista de vecinos
std::vector<int> Vertex::getNeighbors() const {
    return neighbors;
}
