#include "Graph.h"
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_set>

Graph::Graph() : superSource(-1), superSink(-1) {
    numVertices = 0;
}

void Graph::addEdge(int from, int to, int capacity) {
    // Añade la arista al grafo
    adjacencyList[from][to] = capacity;
    flowList[from][to] = 0;

    adjacencyList[to][from] = 0;
    flowList[to][from] = 0;

    
    if (adjacencyList.count(from) == 1 && adjacencyList[from].size() == 1) numVertices++;
    if (adjacencyList.count(to) == 1 && adjacencyList[to].size() == 1) numVertices++;
}

int Graph::getNumVertices() const {
    return numVertices;
}

int Graph::getResidualCapacity(int from, int to) const {
    int capacity = 0;
    int flow = 0;

    // Obtener capacidad
    if (adjacencyList.find(from) != adjacencyList.end() &&
        adjacencyList.at(from).find(to) != adjacencyList.at(from).end()) {
        capacity = adjacencyList.at(from).at(to);
    }

    // Obtener flujo
    if (flowList.find(from) != flowList.end() &&
        flowList.at(from).find(to) != flowList.at(from).end()) {
        flow = flowList.at(from).at(to);
    }

    return capacity - flow;
}

void Graph::updateFlow(int from, int to, int additionalFlow) {
    if (additionalFlow <= 0) return;
    
    // Actualizar flujo directo
    if (flowList[from].find(to) == flowList[from].end()) {
        flowList[from][to] = 0;
    }
    flowList[from][to] += additionalFlow;

    // Actualizar flujo inverso
    if (flowList[to].find(from) == flowList[to].end()) {
        flowList[to][from] = 0;
    }
    flowList[to][from] -= additionalFlow;
}


void Graph::addSuperSourceAndSink(const std::vector<int>& sources, const std::vector<int>& sinks) {
    superSource = numVertices++;
    superSink = numVertices++;

    // Para cada fuente, conectar con super source usando la suma de sus capacidades salientes
    for (int source : sources) {
        int sourceCapacity = 0;
        if (adjacencyList.find(source) != adjacencyList.end()) {
            for (const auto& edge : adjacencyList[source]) {
                sourceCapacity += edge.second;
            }
        }
        addEdge(superSource, source, sourceCapacity);
    }

    // Para cada sumidero, conectar al super sink usando la suma de sus capacidades entrantes
    for (int sink : sinks) {
        int sinkCapacity = 0;
        for (const auto& edges : adjacencyList) {
            if (edges.second.find(sink) != edges.second.end()) {
                sinkCapacity += edges.second.at(sink);
            }
        }
        addEdge(sink, superSink, sinkCapacity);
    }
}


std::vector<int> Graph::getNeighbors(int vertex) const {
    std::vector<int> neighbors;
    if (adjacencyList.find(vertex) != adjacencyList.end()) {
        for (const auto& pair : adjacencyList.at(vertex)) {
            neighbors.push_back(pair.first);
        }
    }
    return neighbors;
}

void Graph::print() const {
    for (const auto& node : adjacencyList) {
        std::cout << "Node " << node.first << ":\n";
        for (const auto& edge : node.second) {
            std::cout << "  -> " << edge.first << " (capacity: " << edge.second << ")\n";
        }
    }
}

int Graph::getSuperSource() const {
    return superSource;
}

int Graph::getSuperSink() const {
    return superSink;
}

void Graph::loadFromFile(const std::string& filename, std::vector<int>& sources, std::vector<int>& sinks) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error al abrir el archivo: " + filename);
    }

    std::string line;
    int vertex;

    // Leer fuentes
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        while (iss >> vertex) {
            if (vertex < 0) {
                throw std::runtime_error("Error: Nodo fuente negativo: " + std::to_string(vertex));
            }
            sources.push_back(vertex);
        }
    }

    // Leer sumideros
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        while (iss >> vertex) {
            if (vertex < 0) {
                throw std::runtime_error("Error: Nodo sumidero negativo: " + std::to_string(vertex));
            }
            sinks.push_back(vertex);
        }
    }

    // Leer arcos
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int from, to, capacity;
        if (iss >> from >> to >> capacity) {
            if (capacity < 0) {
                std::cerr << "Advertencia: Capacidad negativa en el arco (" << from << " -> " << to << ")\n";
                continue;
            }
            addEdge(from, to, capacity);
        }
    }

    file.close();
}

int Graph::getCurrentFlow(int from, int to) const {
    if (flowList.count(from) && flowList.at(from).count(to)) {
        return flowList.at(from).at(to);
    }
    return 0;
}

void Graph::resetFlows() {
    flowList.clear();
}
