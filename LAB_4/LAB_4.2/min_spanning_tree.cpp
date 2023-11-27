#include "min_spanning_tree.h"
using namespace std;

struct Edge {
    int from, to;
    double weight;

    Edge(int f, int t, double w) : from(f), to(t), weight(w) {}

    bool operator<(const Edge& other) const {
        return weight > other.weight;
    }
};

vector<pair<int, int>> min_spanning_tree(const Graph& graph) {
    
    vector<pair<int, int>> result;
    priority_queue<Edge> min_heap;
    set<int> visited;

    if (!graph.get_vertices().empty()) {
        int start_vertex = graph.get_vertices()[0];
        visited.insert(start_vertex);

        for (const auto& adj_edge : graph.get_adjacent_edges(start_vertex)) {
            int to_vertex = adj_edge.first;
            double weight = adj_edge.second;
            min_heap.push(Edge(start_vertex, to_vertex, weight));
        }

        while (!min_heap.empty()) {
            Edge current_edge = min_heap.top();
            min_heap.pop();
            int from_vertex = current_edge.from;
            int to_vertex = current_edge.to;

            if (visited.count(to_vertex) > 0)
                continue;

            result.push_back(make_pair(from_vertex, to_vertex));
            visited.insert(to_vertex);

            for (const auto& adj_edge : graph.get_adjacent_edges(to_vertex)) {
                int next_vertex = adj_edge.first;
                double weight = adj_edge.second;
                min_heap.push(Edge(to_vertex, next_vertex, weight));
            }
        }
    }

    return result;
}
