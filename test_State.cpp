// test_State.cpp
#include "State.h"
#include "Graph.h"
#include <cassert>
#include <iostream>
#include <climits>

int main() {
    std::cout << "Iniciando pruebas de la clase State...\n\n";

    // Test 1: Constructor y estado inicial
    std::cout << "Probando constructor y estado inicial... ";
    {
        Flow flow(5);
        State state(5, flow);
        assert(state.getNextArray().size() == 5);
        for (size_t i = 0; i < 5; ++i) {
            assert(state.getNextArray()[i] == 0);
        }
    }
    std::cout << "OK\n";

    // Test 2: BFS y DFS
    std::cout << "Probando BFS y DFS... ";
    {
        Graph graph(4);
        graph.addEdge(0, 1, 10);
        graph.addEdge(1, 2, 5);
        graph.addEdge(2, 3, 8);

        Flow flow(4);
        State state(4, flow);

        bool hasPath = state.bfs(graph, 0, 3);
        assert(hasPath == true);

        int found_flow = state.dfs(graph, 0, 3, INT_MAX);
        assert(found_flow > 0);
        assert(found_flow <= 5);  // Debería ser el mínimo de las capacidades
    }
    std::cout << "OK\n";

    // Test 3: Flujo múltiple
    std::cout << "Probando flujo múltiple... ";
    {
        Graph graph(4);
        graph.addEdge(0, 1, 10);
        graph.addEdge(0, 2, 10);
        graph.addEdge(1, 3, 10);
        graph.addEdge(2, 3, 10);

        Flow flow(4);
        State state(4, flow);

        bool hasPath = state.bfs(graph, 0, 3);
        assert(hasPath == true);

        int total_flow = 0;
        int path_flow;
        std::fill(state.getNextArray().begin(), state.getNextArray().end(), 0);
        
        while ((path_flow = state.dfs(graph, 0, 3, INT_MAX)) > 0) {
            total_flow += path_flow;
        }
        
        assert(total_flow == 20);
    }
    std::cout << "OK\n";

    std::cout << "\nTodas las pruebas de State pasaron exitosamente!\n";
    return 0;
}