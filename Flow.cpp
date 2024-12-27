#include "Flow.h"

/**
 * Constructor de la clase Flow.
 * 
 * @return Instancia de Flow.
 */
Flow::Flow() : totalFlow(0) {}

/**
 * Incrementar flujo total.
 * 
 * @param flow Flujo a incrementar.
 * 
 */
void Flow::addFlow(int flow) {
    totalFlow += flow;
}

/**
 * Obtener el flujo total.
 * 
 * @return Flujo total.
 * 
 */
int Flow::getTotalFlow() const {
    return totalFlow;
}

/**
 * Reiniciar flujo total.
 * 
 */
void Flow::resetFlow() {
    totalFlow = 0;
}