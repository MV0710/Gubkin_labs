#include "Graph.h"

void Graph::addEdge(int src, int dest) {
    adjList[src].insert(dest);
}

Graph buildGraph(std::unordered_map<int, Pipe> pipes, std::unordered_map<int, CompressorStation> stations) {
    Graph graph;

    // ���������� ���� � ���� �� ������ ����
    for (const auto& [id, pipe] : pipes) {
        int entranceID = pipe.getIdCSOfTheEntrance();
        int exitID = pipe.getIdCSOfTheExit();
        if (entranceID != 0 && exitID != 0) {
            graph.addEdge(entranceID, exitID);
        }
    }

    // ���������� ������ � ���� �� ������ ������������� �������
    for (const auto& [id, station] : stations) {
        graph.adjList[id]; // ��������� �������, ���� ���� ��� ������
    }

    return graph;
}

std::vector<int> topologicalSort(Graph& graph) {
    std::unordered_map<int, int> inDegree;

    // ��������� �������� ������� ��� ������
    for (const auto& [vertex, neighbors] : graph.adjList) {
        inDegree[vertex] = 0;
    }

    for (const auto& [_, neighbors] : graph.adjList) {
        for (int neighbor : neighbors) {
            inDegree[neighbor]++;
        }
    }

    std::queue<int> q;

    // ��������� ������� � ������� �������� �������� � �������
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

        // ��������� �������� ������� ������� ������
        for (int neighbor : graph.adjList[currVertex]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    return result;
}