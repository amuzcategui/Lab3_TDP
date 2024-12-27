#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <queue>
#include <chrono>
#include "Graph.h"
#include "Flow.h"

class Algorithm {
private:
    Graph& graph;
    Flow flowManager;
    std::chrono::duration<double> executionTime;

public:
    Algorithm(Graph& g);

    bool findAugmentingPath(std::vector<int>& path);
    int updateFlow(const std::vector<int>& path);
    int solve();
    double getExecutionTime() const;
};

#endif // ALGORITHM_H
