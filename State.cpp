#include "State.h"

/**
 * Constructor de la clase State.
 * 
 */
State::State() : superSource(-1), superSink(-1), numVertices(0) {}

/**
 * Método para establecer el número de vértices.
 * 
 * @param num Número de vértices.
 * 
 */
void State::setNumVertices(int num) {
    numVertices = num;
}

/**
 * Método para obtener el número de vértices.
 * 
 * @return Número de vértices.
 * 
 */
int State::getNumVertices() const {
    return numVertices;
}

/**
 * Método para establecer el nodo fuente.
 * 
 * @param source Nodo fuente.
 * 
 */
void State::setSuperSource(int source) {
    superSource = source;
}

/**
 * Método para establecer el nodo sumidero.
 * 
 * @param sink Nodo sumidero.
 * 
 */
void State::setSuperSink(int sink) {
    superSink = sink;
}

/**
 * Método para obtener el nodo fuente.
 * 
 * @return Nodo fuente.
 * 
 */
int State::getSuperSource() const {
    return superSource;
}

/**
 * Método para obtener el nodo sumidero.
 * 
 * @return Nodo sumidero.
 * 
 */
int State::getSuperSink() const {
    return superSink;
}

/**
 * Método para añadir una arista al grafo.
 * 
 * @param from Nodo de origen.
 * @param to Nodo de destino.
 * @param capacity Capacidad de la arista.
 * 
 */
void State::addEdge(int from, int to, int capacity) {
    adjacencyList[from][to] = capacity;
    flowList[from][to] = 0;
    
    // Añadir arista residual
    adjacencyList[to][from] = 0;
    flowList[to][from] = 0;
}

/**
 * Método para obtener la capacidad de una arista.
 * 
 * @param from Nodo de origen.
 * @param to Nodo de destino.
 * 
 * @return Capacidad de la arista.
 * 
 */
int State::getCapacity(int from, int to) const {
    if (adjacencyList.count(from) && adjacencyList.at(from).count(to)) {
        return adjacencyList.at(from).at(to);
    }
    return 0;
}

/**
 * Método para obtener el flujo de una arista.
 * 
 * @param from Nodo de origen.
 * @param to Nodo de destino.
 * 
 * @return Flujo de la arista.
 * 
 */
int State::getFlow(int from, int to) const {
    if (flowList.count(from) && flowList.at(from).count(to)) {
        return flowList.at(from).at(to);
    }
    return 0;
}

/**
 * Método para actualizar el flujo de una arista.
 * 
 * @param from Nodo de origen.
 * @param to Nodo de destino.
 * @param additionalFlow Flujo adicional.
 * 
 */
void State::updateFlow(int from, int to, int additionalFlow) {
    if (additionalFlow <= 0) return;
    
    flowList[from][to] += additionalFlow;
    flowList[to][from] -= additionalFlow;
}

/**
 * Método para obtener la capacidad residual de una arista.
 * 
 * @param from Nodo de origen.
 * @param to Nodo de destino.
 * 
 * @return Capacidad residual de la arista.
 * 
 */
int State::getResidualCapacity(int from, int to) const {
    return getCapacity(from, to) - getFlow(from, to);
}

/**
 * Método para reiniciar los flujos del grafo.
 * 
 */
void State::resetFlows() {
    flowList.clear();
    for (const auto& fromNode : adjacencyList) {
        for (const auto& toNode : fromNode.second) {
            flowList[fromNode.first][toNode.first] = 0;
        }
    }
}

/**
 * Método para obtener los vecinos de un nodo.
 * 
 * @param vertex Nodo del que se desean obtener los vecinos.
 * 
 * @return Vector con los nodos vecinos.
 * 
 */
std::vector<int> State::getNeighbors(int vertex) const {
    std::vector<int> neighbors;
    if (adjacencyList.count(vertex)) {
        for (const auto& pair : adjacencyList.at(vertex)) {
            neighbors.push_back(pair.first);
        }
    }
    return neighbors;
}

/**
 * Método para verificar si existe una arista entre dos nodos.
 * 
 * @param from Nodo de origen.
 * @param to Nodo de destino.
 * 
 * @return true si existe la arista, false en caso contrario.
 * 
 */
bool State::hasEdge(int from, int to) const {
    return adjacencyList.count(from) && adjacencyList.at(from).count(to);
}