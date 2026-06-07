#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

struct Edge {
    int to;
    int weight;
};

void printPath(const vector<int>& parent, int v, const vector<string>& name) {
    if (v == -1) return;

    if (parent[v] == -1) {
        cout << name[v];
        return;
    }

    printPath(parent, parent[v], name);
    cout << " -> " << name[v];
}

void shortestPathDP(const vector<vector<Edge>>& graph,
                    const vector<int>& topo,
                    int source,
                    int target,
                    const vector<string>& name) {
    const int INF = numeric_limits<int>::max() / 2;
    int n = graph.size();

    vector<int> dist(n, INF);
    vector<int> parent(n, -1);

    dist[source] = 0;

    for (int u : topo) {
        if (dist[u] == INF) continue;

        for (Edge e : graph[u]) {
            int v = e.to;
            int w = e.weight;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    cout << "Shortest Path DP\n";
    cout << "Distance = ";

    if (dist[target] >= INF / 2) {
        cout << "INF\n";
        cout << "Path: No path\n\n";
    } else {
        cout << dist[target] << "\n";
        cout << "Path: ";
        printPath(parent, target, name);
        cout << "\n\n";
    }
}

void longestPathDP(const vector<vector<Edge>>& graph,
                   const vector<int>& topo,
                   int source,
                   int target,
                   const vector<string>& name) {
    const int NEG_INF = numeric_limits<int>::min() / 2;
    int n = graph.size();

    vector<int> dist(n, NEG_INF);
    vector<int> parent(n, -1);

    dist[source] = 0;

    for (int u : topo) {
        if (dist[u] == NEG_INF) continue;

        for (Edge e : graph[u]) {
            int v = e.to;
            int w = e.weight;

            if (dist[u] + w > dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
            }
        }
    }

    cout << "Longest Path DP\n";
    cout << "Distance = ";

    if (dist[target] <= NEG_INF / 2) {
        cout << "-INF\n";
        cout << "Path: No path\n\n";
    } else {
        cout << dist[target] << "\n";
        cout << "Path: ";
        printPath(parent, target, name);
        cout << "\n\n";
    }
}

void maxProductPathDP(const vector<vector<Edge>>& graph,
                      const vector<int>& topo,
                      int source,
                      int target,
                      const vector<string>& name) {
    int n = graph.size();

    vector<long long> prod(n, 0);
    vector<int> parent(n, -1);

    prod[source] = 1;

    for (int u : topo) {
        if (prod[u] == 0) continue;

        for (Edge e : graph[u]) {
            int v = e.to;
            int w = e.weight;

            long long candidate = prod[u] * w;

            if (candidate > prod[v]) {
                prod[v] = candidate;
                parent[v] = u;
            }
        }
    }

    cout << "Maximum Product Path DP\n";
    cout << "Product = ";

    if (prod[target] == 0) {
        cout << "0\n";
        cout << "Path: No path\n\n";
    } else {
        cout << prod[target] << "\n";
        cout << "Path: ";
        printPath(parent, target, name);
        cout << "\n\n";
    }
}

int main() {
    vector<string> name = {"S", "A", "B", "C", "D", "E", "F", "G", "T"};
    int n = 9;

    vector<vector<Edge>> graph(n);

    graph[0].push_back({1, 6});
    graph[0].push_back({2, 5});
    graph[0].push_back({3, 7});
    graph[0].push_back({4, 4});

    graph[1].push_back({5, 3});
    graph[1].push_back({6, 10});

    graph[2].push_back({5, 2});
    graph[2].push_back({7, 2});

    graph[3].push_back({6, 1});
    graph[4].push_back({7, 3});

    graph[5].push_back({8, 2});
    graph[6].push_back({8, 9});
    graph[7].push_back({8, 5});

    vector<int> topo = {
        0,
        1, 2, 3, 4,
        5, 6, 7,
        8
    };

    int source = 0;
    int target = 8;

    shortestPathDP(graph, topo, source, target, name);
    longestPathDP(graph, topo, source, target, name);
    maxProductPathDP(graph, topo, source, target, name);

    return 0;
}
