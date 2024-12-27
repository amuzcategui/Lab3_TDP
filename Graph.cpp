#include "Graph.h"

/**
 * Constructor de la clase Graph.
 * 
 * @return Instancia de Graph.
 * 
 */
Graph::Graph() {}

/**
 * Método para añadir una arista al grafo.
 * 
 * @param from Nodo de origen.
 * @param to Nodo de destino.
 * @param capacity Capacidad de la arista.
 * 
 */
void Graph::addEdge(int from, int to, int capacity) {
    state.addEdge(from, to, capacity);
    
    int maxVertex = std::max(from, to);
    if (maxVertex >= state.getNumVertices()) {
        state.setNumVertices(maxVertex + 1);
    }
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
int Graph::getResidualCapacity(int from, int to) const {
    return state.getResidualCapacity(from, to);
}

/**
 * Método para actualizar el flujo de una arista.
 * 
 * @param from Nodo de origen.
 * @param to Nodo de destino.
 * @param flow Flujo adicional.
 * 
 */
void Graph::updateFlow(int from, int to, int flow) {
    state.updateFlow(from, to, flow);
}

/**
 * Método para reiniciar los flujos del grafo.
 * 
 */
void Graph::resetFlows() {
    state.resetFlows();
}

/**
 * Método para obtener el número de vértices del grafo.
 * 
 * @return Número de vértices del grafo.
 * 
 */
int Graph::getNumVertices() const {
    return state.getNumVertices();
}

/**
 * Método para obtener el nodo fuente del grafo.
 * 
 * @return Nodo fuente del grafo.
 * 
 */
int Graph::getSuperSource() const {
    return state.getSuperSource();
}

/**
 * Método para obtener el nodo sumidero del grafo.
 * 
 * @return Nodo sumidero del grafo.
 * 
 */
int Graph::getSuperSink() const {
    return state.getSuperSink();
}

/**
 * Método para obtener el flujo actual de una arista.
 * 
 * @param from Nodo de origen.
 * @param to Nodo de destino.
 * 
 * @return Flujo actual de la arista.
 * 
 */
int Graph::getCurrentFlow(int from, int to) const {
    return state.getFlow(from, to);
}

/**
 * Método para obtener los vecinos de un nodo.
 * 
 * @param vertex Nodo del que se desean obtener los vecinos.
 * 
 * @return Vector con los nodos vecinos.
 * 
 */
std::vector<int> Graph::getNeighbors(int vertex) const {
    return state.getNeighbors(vertex);
}

/**
 * Método para añadir un nodo fuente y un nodo sumidero al grafo.
 * 
 * @param sources Vector con los nodos fuente.
 * @param sinks Vector con los nodos sumidero.
 * 
 */
void Graph::addSuperSourceAndSink(const std::vector<int>& sources, const std::vector<int>& sinks) {
    int newSuperSource = state.getNumVertices();
    int newSuperSink = newSuperSource + 1;
    
    state.setSuperSource(newSuperSource);
    state.setSuperSink(newSuperSink);
    state.setNumVertices(newSuperSink + 1);

    // Conectar fuentes
    for (int source : sources) {
        int sourceCapacity = 0;
        for (int neighbor : getNeighbors(source)) {
            sourceCapacity += state.getCapacity(source, neighbor);
        }
        addEdge(newSuperSource, source, sourceCapacity);
    }

    // Conectar sumideros
    for (int sink : sinks) {
        int sinkCapacity = 0;
        for (int vertex = 0; vertex < newSuperSource; vertex++) {
            if (state.hasEdge(vertex, sink)) {
                sinkCapacity += state.getCapacity(vertex, sink);
            }
        }
        addEdge(sink, newSuperSink, sinkCapacity);
    }
}

/**
 * Método para cargar un grafo desde un archivo.
 * 
 * @param filename Nombre del archivo.
 * @param sources Vector donde se almacenarán los nodos fuente.
 * @param sinks Vector donde se almacenarán los nodos sumidero.
 * 
 */
void Graph::loadFromFile(const std::string& filename, std::vector<int>& sources, std::vector<int>& sinks) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Error al abrir el archivo: " + filename);
    }

    std::string line;
    int vertex;

    if (std::getline(file, line)) {
        std::istringstream iss(line);
        while (iss >> vertex) {
            if (vertex < 0) {
                throw std::runtime_error("Error: Nodo fuente negativo: " + std::to_string(vertex));
            }
            sources.push_back(vertex);
        }
    }

    if (std::getline(file, line)) {
        std::istringstream iss(line);
        while (iss >> vertex) {
            if (vertex < 0) {
                throw std::runtime_error("Error: Nodo sumidero negativo: " + std::to_string(vertex));
            }
            sinks.push_back(vertex);
        }
    }

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
