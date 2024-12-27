// Edge.cpp
#include "Edge.h"

// Constructor
Edge::Edge(int src, int dest, int cap) : source(src), destination(dest), capacity(cap), flow(0) {}

// Getters
int Edge::getSource() const {
    return source;
}

int Edge::getDestination() const {
    return destination;
}

int Edge::getCapacity() const {
    return capacity;
}

int Edge::getFlow() const {
    return flow;
}

// Setters
void Edge::setFlow(int newFlow) {
    flow = newFlow;
}

// Métodos útiles
int Edge::getResidualCapacity() const {
    return capacity - flow;
}

void Edge::addFlow(int additionalFlow) {
    flow += additionalFlow;
}
