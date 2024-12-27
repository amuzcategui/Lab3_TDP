// Flow.h
#ifndef FLOW_H
#define FLOW_H

class Flow {
private:
    int totalFlow;  // Almacena el flujo total en el sistema

public:
    // Constructor
    Flow();

    // Incrementar flujo total
    void addFlow(int flow);

    // Obtener el flujo total
    int getTotalFlow() const;

    // Reiniciar flujo total
    void resetFlow();
};

#endif // FLOW_H