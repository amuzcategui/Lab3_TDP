// Edge.h
#ifndef EDGE_H
#define EDGE_H
//NO SE UTILIZA
class Edge {
private:
    int source;  // Nodo origen de la arista
    int destination;  // Nodo destino de la arista
    int capacity;  // Capacidad de la arista
    int flow;  // Flujo actual de la arista

public:
    // Constructor
    Edge(int src, int dest, int cap);

    // Getters
    int getSource() const;
    int getDestination() const;
    int getCapacity() const;
    int getFlow() const;

    // Setters
    void setFlow(int newFlow);

    // Métodos útiles
    int getResidualCapacity() const; // Retorna la capacidad residual
    void addFlow(int additionalFlow); // Incrementa el flujo por la arista
};

#endif // EDGE_H
