// Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>

class Graph {
private:
    std::unordered_map<int, std::unordered_map<int, int>> adjacencyList;
    std::unordered_map<int, std::unordered_map<int, int>> flowList;  // Add this to track flows separately
    int superSource;
    int superSink;

public:

    int numVertices;
    // Constructor
    Graph();

    int getNumVertices() const;

    // Add an edge to the graph
    void addEdge(int from, int to, int capacity);

    // Get the residual capacity of an edge
    int getResidualCapacity(int from, int to) const;

    // Update the flow on an edge
    void updateFlow(int from, int to, int flow);

    // Add a super source and super sink to handle multiple sources and sinks
    void addSuperSourceAndSink(const std::vector<int>& sources, const std::vector<int>& sinks);

    // Get neighbors of a vertex
    std::vector<int> getNeighbors(int vertex) const;

    // Print the graph (for debugging)
    void print() const;

    // Accessor for super source and sink
    int getSuperSource() const;
    int getSuperSink() const;

    // Load graph from file
    void loadFromFile(const std::string& filename, std::vector<int>& sources, std::vector<int>& sinks);
    int getCurrentFlow(int from, int to) const;


    void resetFlows();

};

#endif // GRAPH_H
