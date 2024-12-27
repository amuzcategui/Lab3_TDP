// Vertex.h
#ifndef VERTEX_H
#define VERTEX_H
//NO SE UTILIZA
#include <vector>

class Vertex {
private:
    int id;  // Identificador único del vértice
    std::vector<int> neighbors;  // Lista de vecinos

public:
    // Constructor
    Vertex(int id);

    Vertex() : id(-1) {}

    // Añadir vecino
    void addNeighbor(int vertex);

    // Obtener ID del vértice
    int getId() const;

    // Obtener lista de vecinos
    std::vector<int> getNeighbors() const;
};

#endif // VERTEX_H
