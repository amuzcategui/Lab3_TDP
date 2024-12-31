#include "State.h"
#include <cassert>
#include <iostream>
#include <climits>

int main() {
    std::cout << "Iniciando pruebas de la clase State...\n\n";

    // Test constructor and initial state
    std::cout << "Probando constructor y estado inicial... ";
    {
        State state(5);  // Create state with 5 vertices
        assert(state.getLevel(0) == -1);  // Initial level should be -1
        assert(state.getNext(0) == 0);    // Initial next should be 0
    }
    std::cout << "OK\n";

    // Test BFS
    std::cout << "Probando BFS... ";
    {
        Graph graph(4);  // Create a simple graph with 4 vertices
        graph.addEdge(0, 1, 10);
        graph.addEdge(1, 2, 5);
        graph.addEdge(2, 3, 8);

        State state(4);
        
        // Test BFS from source 0 to sink 3
        bool hasPath = state.bfs(graph, 0, 3);
        assert(hasPath == true);
        
        // Verify levels are set correctly
        assert(state.getLevel(0) == 0);  // Source level should be 0
        assert(state.getLevel(1) == 1);  // First vertex after source
        assert(state.getLevel(2) == 2);  // Second vertex
        assert(state.getLevel(3) == 3);  // Sink level should be 3
    }
    std::cout << "OK\n";

    // Test DFS
    std::cout << "Probando DFS... ";
    {
        Graph graph(4);
        // Crear un grafo simple con un solo camino posible
        graph.addEdge(0, 1, 5);
        graph.addEdge(1, 2, 5);
        graph.addEdge(2, 3, 5);

        State state(4);
        // Configurar los niveles manualmente para simular un BFS previo
        state.setLevel(0, 0);
        state.setLevel(1, 1);
        state.setLevel(2, 2);
        state.setLevel(3, 3);
        
        // Realizar el DFS
        int flow = state.dfs(graph, 0, 3, INT_MAX);
        
        // Verificar que encontró el flujo correcto
        assert(flow == 5);  // El flujo debería ser el mínimo de las capacidades
        
        // Verificar que el camino fue explorado
        assert(state.getNextArray()[0] <= graph.getAdj(0).size());
    }
    std::cout << "OK\n";

    // Test reset functionality
    std::cout << "Probando reset... ";
    {
        State state(4);
        
        // Set some levels
        state.setLevel(0, 1);
        state.setLevel(1, 2);
        state.setLevel(2, 3);
        
        // Set some next values
        state.setNext(0, 1);
        state.setNext(1, 2);
        
        // Reset state
        state.reset();
        
        // Verify everything is reset
        assert(state.getLevel(0) == -1);
        assert(state.getLevel(1) == -1);
        assert(state.getLevel(2) == -1);
        assert(state.getNext(0) == 0);
        assert(state.getNext(1) == 0);
    }
    std::cout << "OK\n";

    std::cout << "\nTodas las pruebas pasaron exitosamente!\n";
    return 0;
}