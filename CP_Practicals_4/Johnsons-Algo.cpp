#include <bits/stdc++.h>   
using namespace std;       
 
const int INF = 1e9;
 
struct Edge { int u, v, w; };
 


bool bellmanFord(int src, int V, const vector<Edge>& edges, vector<int>& h)
{
    h.assign(V + 1, INF);
    h[src] = 0;
    for (int iter = 0; iter < V; ++iter)
        for (auto& [u, v, w] : edges)
            if (h[u] != INF && h[u] + w < h[v]) {
                if (iter == V - 1) return false;   // negative cycle
                h[v] = h[u] + w;
            }
    return true;
}
 

vector<int> dijkstra(int src, int V, const vector<vector<pair<int,int>>>& adj)
{
    vector<int> dist(V, INF);
    dist[src] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u])
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
    }
    return dist;
}
 

bool johnsons(int V, vector<Edge>& edges, vector<vector<int>>& allDist)
{
    vector<Edge> aug = edges;
    for (int v = 0; v < V; ++v) aug.push_back({V, v, 0});
 
    vector<int> h;
    if (!bellmanFord(V, V, aug, h)) return false;
 
    vector<vector<pair<int,int>>> adj(V);
    for (auto& [u, v, w] : edges)
        adj[u].push_back({v, w + h[u] - h[v]});
 
    allDist.assign(V, vector<int>(V, INF));
    for (int u = 0; u < V; ++u) {
        auto d = dijkstra(u, V, adj);
        for (int v = 0; v < V; ++v)
            if (d[v] != INF)
                allDist[u][v] = d[v] - h[u] + h[v];
    }
    return true;
}
 

void printMatrix(int V, const vector<vector<int>>& dist)
{
    cout << "     ";
    for (int j = 0; j < V; ++j) cout << setw(6) << j;
    cout << "\n     ";
    for (int j = 0; j < V; ++j) cout << "------";
    cout << "\n";
    for (int i = 0; i < V; ++i) {
        cout << "  " << i << " |";
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF) cout << setw(6) << "INF";
            else                   cout << setw(6) << dist[i][j];
        }
        cout << "\n";
    }
}
 

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int V = 4;
    vector<Edge> edges = {
        {0, 1,  3},
        {0, 3,  7},
        {1, 0,  8},
        {1, 2,  2},
        {2, 0,  5},
        {2, 3,  1},
        {3, 0,  2}
    };
 
    vector<vector<int>> allDist;
    if (!johnsons(V, edges, allDist)) {
        cout << "Negative cycle detected — no solution.\n";
        return 1;
    }
 
    cout << "=== Johnson's Algorithm: All-Pairs Shortest Distances ===\n\n";
    printMatrix(V, allDist);
 
    cout << "\n=== All Shortest Distances ===\n";
    for (int u = 0; u < V; ++u)
        for (int v = 0; v < V; ++v)
            if (u != v)
                cout << "  " << u << " -> " << v << " : "
                     << (allDist[u][v] == INF ? -1 : allDist[u][v]) << "\n";
 
    cout << "\n=== Demo with Negative Weight Edge ===\n";
    int V2 = 3;
    vector<Edge> edges2 = {
        {0, 1,  4},
        {0, 2,  5},
        {1, 2, -3}   
    };
    vector<vector<int>> allDist2;
    if (johnsons(V2, edges2, allDist2)) {
        printMatrix(V2, allDist2);
    } else {
        cout << "Negative cycle detected.\n";
    }
 
    return 0;
}
 