#include "Flow.h"
#include <cassert>
#include <iostream>
#include <sstream>

int main() {
    std::cout << "Iniciando pruebas de la clase Flow...\n\n";

    // Prueba del constructor
    std::cout << "Probando constructor... ";
    {
        Flow flow;
        assert(flow.getTotalFlow() == 0);
    }
    std::cout << "OK\n";

    // Prueba de addFlow
    std::cout << "Probando addFlow... ";
    {
        Flow flow;

        // Añadir flujo positivo
        flow.addFlow(10);
        assert(flow.getTotalFlow() == 10);

        // Añadir más flujo
        flow.addFlow(5);
        assert(flow.getTotalFlow() == 15);

        // Añadir flujo cero
        flow.addFlow(0);
        assert(flow.getTotalFlow() == 15);
    }
    std::cout << "OK\n";

    // Prueba de resetFlow
    std::cout << "Probando resetFlow... ";
    {
        Flow flow;

        // Añadir algo de flujo
        flow.addFlow(10);
        flow.addFlow(5);
        assert(flow.getTotalFlow() == 15);

        // Resetear el flujo
        flow.resetFlow();
        assert(flow.getTotalFlow() == 0);

        // Verificar que se puede añadir flujo después del reset
        flow.addFlow(7);
        assert(flow.getTotalFlow() == 7);
    }
    std::cout << "OK\n";

    // Prueba de secuencia de operaciones
    std::cout << "Probando secuencia de operaciones... ";
    {
        Flow flow;

        // Secuencia de operaciones
        flow.addFlow(10);      // Total: 10
        flow.addFlow(5);       // Total: 15
        flow.resetFlow();      // Total: 0
        flow.addFlow(7);       // Total: 7
        flow.addFlow(3);       // Total: 10
        assert(flow.getTotalFlow() == 10);

        // Reset y verificar
        flow.resetFlow();
        assert(flow.getTotalFlow() == 0);
    }
    std::cout << "OK\n";

    // Prueba de casos límite
    std::cout << "Probando casos límite... ";
    {
        Flow flow;

        // Añadir flujos muy grandes
        flow.addFlow(1000000);
        flow.addFlow(2000000);
        assert(flow.getTotalFlow() == 3000000);

        // Reset y añadir flujos pequeños
        flow.resetFlow();
        flow.addFlow(1);
        flow.addFlow(2);
        assert(flow.getTotalFlow() == 3);
    }
    std::cout << "OK\n";

    std::cout << "\nTodas las pruebas pasaron exitosamente!\n";
    return 0;
}
