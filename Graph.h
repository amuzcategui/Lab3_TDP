#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm> 
#include "Flow.h"
using namespace std;

class Graph {
private:
    int vertices; //Número de vértices
    vector<vector<int>> capacity; //Capacidad de las aristas
    vector<vector<int>> adj; //Lista de adyacencia
    vector<int> sources; //Fuentes
    vector<int> sinks; //Sumideros
    int superSource; //Super fuente
    int superSink; //Super sumidero
    Flow flow; //Flujo
    
    void resize(int newSize); //Redimensionar el grafo
    void clear(); //Limpiar el grafo

public:
    int getSuperSource() const { return superSource; } //Obtener super fuente
    int getSuperSink() const { return superSink; } //Obtener super sumidero

    // Actualizar constructor para inicializar flujo
    Graph(int n = 0);
    
    // Constructor de copia
    Graph(const Graph& other);

    // Métodos para flujo
    int getCurrentFlow(int u, int v) const;
    void updateFlow(int u, int v, int f);

    // Métodos para manejar la estructura del grafo
    void addEdge(int u, int v, int cap);
    int getCapacity(int u, int v) const;
    const vector<int>& getAdj(int u) const;
    void updateCapacity(int u, int v, int flow);
    int size() const;
    void addSuperSourceAndSink(int& superSource, int& superSink);

    // Carga desde archivo
    bool loadFromFile(const std::string& filename);

    // Obtener fuentes y sumideros
    const vector<int>& getSources() const;
    const vector<int>& getSinks() const;

};
#endif // GRAPH_H
