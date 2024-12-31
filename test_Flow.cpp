#include "Flow.h"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "Iniciando pruebas de la clase Flow...\n\n";

    // Test 1: Constructor y tamaño inicial
    std::cout << "Probando constructor... ";
    {
        Flow flow(5);  // Crear flow con 5 vértices
        assert(flow.getCurrentFlow(0, 1) == 0);  // Verificar flujo inicial
        assert(flow.getOutgoingFlow(0) == 0);    // Verificar flujo saliente
        assert(flow.getIncomingFlow(0) == 0);    // Verificar flujo entrante
    }
    std::cout << "OK\n";

    // Test 2: Actualización de flujo
    std::cout << "Probando updateFlow... ";
    {
        Flow flow(3);
        
        // Añadir flujo positivo
        flow.updateFlow(0, 1, 10);
        assert(flow.getCurrentFlow(0, 1) == 10);
        assert(flow.getCurrentFlow(1, 0) == -10);  // Flujo inverso
        
        // Verificar flujos totales
        assert(flow.getOutgoingFlow(0) == 10);
        assert(flow.getIncomingFlow(1) == 10);
    }
    std::cout << "OK\n";

    // Test 3: Resize
    std::cout << "Probando resize... ";
    {
        Flow flow(2);
        flow.updateFlow(0, 1, 5);
        
        flow.resize(4);  // Aumentar tamaño
        assert(flow.getCurrentFlow(0, 1) == 5);  // Verificar que se mantiene el flujo
        assert(flow.getCurrentFlow(2, 3) == 0);  // Verificar nuevos vértices
    }
    std::cout << "OK\n";

    // Test 4: Clear
    std::cout << "Probando clear... ";
    {
        Flow flow(3);
        flow.updateFlow(0, 1, 5);
        flow.clear();
        
        flow.resize(2);  // Nuevo tamaño después de clear
        assert(flow.getCurrentFlow(0, 1) == 0);
    }
    std::cout << "OK\n";

    std::cout << "\nTodas las pruebas de Flow pasaron exitosamente!\n";
    return 0;
}