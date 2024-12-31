#include "Graph.h"

/**
 * @brief Constructor de la clase Graph
 * 
 * @param n Número de vértices
 * 
 */
Graph::Graph(int n) : vertices(n), superSource(-1), superSink(-1) {
    resize(n);
}

/**
 * @brief Redimensiona el grafo
 * 
 * @param newSize Nuevo tamaño del grafo
 * 
 */
void Graph::resize(int newSize) {
        vertices = newSize;
        capacity.resize(vertices, std::vector<int>(vertices, 0));
        adj.resize(vertices);
}

/**
 * @brief Limpia el grafo
 * 
 */
void Graph::clear() {
    capacity.clear();
    adj.clear();
    sources.clear();
    sinks.clear();
    vertices = 0;
}

/**
 * @brief Obtiene las fuentes del grafo
 * 
 * @return vector<int> Fuentes
 * 
 */
const vector<int>& Graph::getSources() const {
    return sources;
}

/**
 * @brief Obtiene los sumideros del grafo
 * 
 * @return vector<int> Sumideros
 * 
 */
const vector<int>& Graph::getSinks() const {
    return sinks;
}

/**
 * @brief Agrega una arista al grafo
 * 
 * @param u Vértice origen
 * @param v Vértice destino
 * @param cap Capacidad de la arista
 * 
 */
void Graph::addEdge(int u, int v, int cap) {
    if (u >= vertices || v >= vertices) {
        int maxVertex = std::max(u, v);
        resize(maxVertex + 1);
    }

    capacity[u][v] = cap;

    if (capacity[v][u] == 0) {
        capacity[v][u] = 0;
    }

    if (std::find(adj[u].begin(), adj[u].end(), v) == adj[u].end()) {
        adj[u].push_back(v);
    }
    if (std::find(adj[v].begin(), adj[v].end(), u) == adj[v].end()) {
        adj[v].push_back(u);
    }
}   

/**
 * @brief Obtiene la capacidad de una arista
 * 
 * @param u Vértice origen
 * @param v Vértice destino
 * 
 * @return int Capacidad de la arista
 * 
 */
int Graph::getCapacity(int u, int v) const {
    return capacity[u][v];
}

/**
 * @brief Obtiene la lista de adyacencia de un vértice
 * 
 * @param u Vértice
 * 
 * @return vector<int> Lista de adyacencia
 * 
 */
const std::vector<int>& Graph::getAdj(int u) const {
    return adj[u];
}

/**
 * @brief Actualiza la capacidad de una arista
 * 
 * @param u Vértice origen
 * @param v Vértice destino
 * @param flow Flujo
 * 
 */
void Graph::updateCapacity(int u, int v, int flow) {
    capacity[u][v] -= flow;
    capacity[v][u] += flow;
}

/**
 * @brief Obtiene el tamaño del grafo
 * 
 * @return int Tamaño del grafo
 * 
 */
int Graph::size() const {
    return vertices;
}

/**
 * @brief Agrega la superfuente y supersumidero al grafo
 * 
 * @param superSource Superfuente
 * @param superSink Supersumidero
 * 
 */
void Graph::addSuperSourceAndSink(int& outSuperSource, int& outSuperSink) {
        superSource = vertices;
        superSink = vertices + 1;
        resize(vertices + 2);
        
        for (int src : sources) {
            int totalCap = 0;
            for (int v : adj[src]) {
                totalCap += capacity[src][v];
            }
            if (totalCap > 0) {
                addEdge(superSource, src, totalCap);
            }
        }
        
        for (int snk : sinks) {
            int totalCap = 0;
            for (int u : adj[snk]) {
                totalCap += capacity[u][snk];
            }
            if (totalCap > 0) {
                addEdge(snk, superSink, totalCap);
            }
        }

        outSuperSource = superSource;
        outSuperSink = superSink;
}

/**
 * @brief Carga un grafo desde un archivo
 * 
 * @param filename Nombre del archivo
 * 
 * @return bool true si se pudo cargar el grafo, false en caso contrario
 * 
 */
bool Graph::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
        return false;
    }

    // Limpiar el grafo actual
    clear();
    
    std::string line;
    
    // Leer fuentes
    if (!std::getline(file, line)) {
        std::cerr << "Error leyendo fuentes" << std::endl;
        return false;
    }
    
    std::istringstream iss(line);
    int node;
    while (iss >> node) {
        sources.push_back(node);
    }
    
    // Leer sumideros
    if (!std::getline(file, line)) {
        std::cerr << "Error leyendo sumideros" << std::endl;
        return false;
    }
    
    iss.clear();
    iss.str(line);
    while (iss >> node) {
        sinks.push_back(node);
    }
    
    // Primera pasada para encontrar el tamaño necesario
    int u, v, cap;
    int maxVertex = -1;
    while (file >> u >> v >> cap) {
        maxVertex = std::max(maxVertex, std::max(u, v));
    }
    
    if (maxVertex < 0) {
        std::cerr << "No se encontraron aristas en el archivo" << std::endl;
        return false;
    }
    
    // Redimensionar el grafo
    resize(maxVertex + 1);
    
    // Volver al inicio para leer las aristas
    file.clear();
    file.seekg(0);
    std::getline(file, line); // Saltar línea de fuentes
    std::getline(file, line); // Saltar línea de sumideros
    
    // Leer y agregar las aristas
    while (file >> u >> v >> cap) {
        addEdge(u, v, cap);
    }
  
    return true;
}

/**
 * @brief Constructor de copia de la clase Graph
 * 
 * @param other Grafo a copiar
 * 
 */
Graph::Graph(const Graph& other) : 
    vertices(other.vertices),
    capacity(other.capacity),
    adj(other.adj),
    sources(other.sources),
    sinks(other.sinks) {}

