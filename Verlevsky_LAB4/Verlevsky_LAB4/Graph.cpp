#include "Graph.h"

void Graph::addEdge(int src, int dest, double weight, double capacity) {
    adjList[src][dest] = std::make_pair(weight, capacity);
}

Graph buildGraph(std::unordered_map<int, Pipe> pipes, std::unordered_map<int, CompressorStation> stations) {
    Graph graph;

    for (const auto& [id, pipe] : pipes) {
        int entranceID = pipe.getIdCSOfTheEntrance();
        int exitID = pipe.getIdCSOfTheExit();
        double weight;
        double capacity;

        if (pipe.under_repair == 0) {
            weight = 0.5 * pipe.length / (1.0 / (pipe.diameter * pipe.diameter));
            capacity = (pipe.diameter * pipe.diameter) / pipe.length * 2.0;
        }
        else {
            weight = INFINITY;
            capacity = 0;
        }

        if (entranceID != 0 && exitID != 0) {
            graph.addEdge(entranceID, exitID, weight, capacity);
        }
    }

    for (const auto& [id, station] : stations) {
        graph.adjList[id];
    }

    return graph;
}

std::vector<int> topologicalSort(Graph& graph) {
    std::unordered_map<int, int> inDegree;

    for (const auto& [vertex, neighbors] : graph.adjList) {
        inDegree[vertex] = 0;
    }

    for (const auto& [_, neighbors] : graph.adjList) {
        for (const auto& [neighbor, _] : neighbors) {
            inDegree[neighbor]++;
        }
    }

    std::queue<int> q;

    for (const auto& [vertex, _] : inDegree) {
        if (inDegree[vertex] == 0) {
            q.push(vertex);
        }
    }

    std::vector<int> result;
    while (!q.empty()) {
        int currVertex = q.front();
        q.pop();
        result.push_back(currVertex);

        for (const auto& [neighbor, _] : graph.adjList[currVertex]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    return result;
}

bool bfs(Graph& graph, int sourceID, int sinkID, std::vector<int>& parent) {
    std::queue<int> q;
    std::unordered_set<int> visited;
    q.push(sourceID);
    visited.insert(sourceID);
    bool foundPath = false;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (const auto& [v, edge] : graph.adjList[u]) {
            double capacity = edge.second;
            if (!visited.count(v) && capacity > 0) {
                q.push(v);
                parent[v] = u;
                visited.insert(v);
                if (v == sinkID) {
                    foundPath = true;
                    break;
                }
            }
        }
    }

    return foundPath;
}

double fordFulkerson(Graph& graph, int sourceID, int sinkID) {
    std::vector<int> parent(graph.adjList.size(), -1);
    double maxFlow = 0.0;

    while (bfs(graph, sourceID, sinkID, parent)) {
        double pathFlow = INFINITY;

        for (int v = sinkID; v != sourceID; v = parent[v]) {
            int u = parent[v];
            pathFlow = std::min(pathFlow, graph.adjList[u][v].second);
        }

        for (int v = sinkID; v != sourceID; v = parent[v]) {
            int u = parent[v];
            graph.adjList[u][v].second -= pathFlow;
            graph.adjList[v][u].second += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

std::vector<int> shortestPath(Graph& graph, int start, int end) {
    std::unordered_map<int, double> distance;
    std::unordered_map<int, int> parent;
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;

    for (const auto& [vertex, _] : graph.adjList) {
        distance[vertex] = INFINITY;
    }
    distance[start] = 0;

    pq.push({ 0, start });

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const auto& [v, edge] : graph.adjList[u]) {
            double weight = edge.first;
            double capacity = edge.second;
            if (capacity > 0 && distance[v] > distance[u] + weight) {
                distance[v] = distance[u] + weight;
                pq.push({ distance[v], v });
                parent[v] = u;
            }
        }
    }

    std::vector<int> path;
    if (distance[end] != INFINITY) {
        for (int v = end; v != start; v = parent[v]) {
            path.push_back(v);
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());
    }

    return path;
}