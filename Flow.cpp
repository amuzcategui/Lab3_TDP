// Flow.cpp
#include "Flow.h"

// Constructor
Flow::Flow() : totalFlow(0) {}

// Incrementar flujo total
void Flow::addFlow(int flow) {
    totalFlow += flow;
}

// Obtener el flujo total
int Flow::getTotalFlow() const {
    return totalFlow;
}

// Reiniciar flujo total
void Flow::resetFlow() {
    totalFlow = 0;
}