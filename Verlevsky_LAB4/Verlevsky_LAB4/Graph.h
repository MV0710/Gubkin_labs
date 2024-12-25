#pragma once
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include "Pipe.h"
#include "CompressorStation.h"

struct  Graph {
    std::unordered_map<int, std::unordered_map<int, std::pair<int, double>>> adjList;

    void addEdge(int src, int dest, double weight, double capacity);
};

Graph buildGraph(std::unordered_map<int, Pipe> pipes, std::unordered_map<int, CompressorStation> stations);

std::vector<int> topologicalSort(Graph& graph);

bool bfs(Graph& graph, int sourceID, int sinkID, std::vector<int>& parent);

double fordFulkerson(Graph& graph, int sourceID, int sinkID);

std::vector<int> shortestPath(Graph& graph, int start, int end);