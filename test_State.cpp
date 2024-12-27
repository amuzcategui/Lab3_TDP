#include "State.h"
#include <cassert>
#include <iostream>
#include <sstream>

int main() {
    std::cout << "Iniciando pruebas de la clase State...\n\n";

    // Prueba del constructor
    std::cout << "Probando constructor... ";
    {
        State state;
        assert(state.getNumVertices() == 0);
        assert(state.getSuperSource() == -1);
        assert(state.getSuperSink() == -1);
    }
    std::cout << "OK\n";

    // Prueba de setters y getters
    std::cout << "Probando setters y getters... ";
    {
        State state;

        // Probar setNumVertices y getNumVertices
        state.setNumVertices(5);
        assert(state.getNumVertices() == 5);

        // Probar setSuperSource y getSuperSource
        state.setSuperSource(0);
        assert(state.getSuperSource() == 0);

        // Probar setSuperSink y getSuperSink
        state.setSuperSink(4);
        assert(state.getSuperSink() == 4);
    }
    std::cout << "OK\n";

    // Prueba de operaciones con aristas
    std::cout << "Probando operaciones con aristas... ";
    {
        State state;

        // Añadir arista y verificar capacidad
        state.addEdge(0, 1, 10);
        assert(state.getCapacity(0, 1) == 10);
        assert(state.getCapacity(1, 0) == 0); // Arista residual

        // Verificar flujo inicial
        assert(state.getFlow(0, 1) == 0);
        assert(state.getFlow(1, 0) == 0);

        // Verificar capacidad residual inicial
        assert(state.getResidualCapacity(0, 1) == 10);
        assert(state.getResidualCapacity(1, 0) == 0);

        // Verificar existencia de arista
        assert(state.hasEdge(0, 1) == true);
        assert(state.hasEdge(2, 3) == false);
    }
    std::cout << "OK\n";

    // Prueba de operaciones de flujo
    std::cout << "Probando operaciones de flujo... ";
    {
        State state;

        // Configurar arista
        state.addEdge(0, 1, 10);

        // Actualizar flujo
        state.updateFlow(0, 1, 5);
        assert(state.getFlow(0, 1) == 5);
        assert(state.getFlow(1, 0) == -5); // Flujo residual

        // Verificar capacidad residual después del flujo
        assert(state.getResidualCapacity(0, 1) == 5);
        assert(state.getResidualCapacity(1, 0) == 5);

        // Probar resetFlows
        state.resetFlows();
        assert(state.getFlow(0, 1) == 0);
        assert(state.getFlow(1, 0) == 0);
    }
    std::cout << "OK\n";

    // Prueba de obtención de vecinos
    std::cout << "Probando obtención de vecinos... ";
    {
        State state;

        // Añadir varias aristas desde el nodo 0
        state.addEdge(0, 1, 10);
        state.addEdge(0, 2, 15);
        state.addEdge(0, 3, 20);

        // Obtener vecinos del nodo 0
        std::vector<int> neighbors = state.getNeighbors(0);
        assert(neighbors.size() == 3);

        // Verificar que todos los vecinos esperados estén presentes
        bool found1 = false, found2 = false, found3 = false;
        for (int neighbor : neighbors) {
            if (neighbor == 1) found1 = true;
            if (neighbor == 2) found2 = true;
            if (neighbor == 3) found3 = true;
        }
        assert(found1 && found2 && found3);

        // Verificar vecinos de un nodo sin aristas
        neighbors = state.getNeighbors(4);
        assert(neighbors.empty());
    }
    std::cout << "OK\n";

    std::cout << "\nTodas las pruebas pasaron exitosamente!\n";
    return 0;
}
