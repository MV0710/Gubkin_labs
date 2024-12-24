#pragma once

#include <unordered_map>
#include <unordered_set>
#include <queue>
#include "Pipe.h"
#include "CompressorStation.h"

class Graph {
public:
    std::unordered_map<int, std::unordered_set<int>> adjList;

    void addEdge(int src, int dest);
};

Graph buildGraph(std::unordered_map<int, Pipe> pipes, std::unordered_map<int, CompressorStation> stations);

std::vector<int> topologicalSort(Graph& graph);