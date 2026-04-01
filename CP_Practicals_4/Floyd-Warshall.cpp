#include <bits/stdc++.h>
using namespace std;
 
const int INF = 1e9;
 
struct Edge { int u, v, w; };

 
void floydWarshall(int V, vector<vector<int>>& adj,
                   vector<vector<int>>& dist,
                   vector<vector<int>>& nxt)
{
    dist = adj;
    nxt.assign(V, vector<int>(V, -1));
 
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            if (i != j && adj[i][j] != INF)
                nxt[i][j] = j;
 
    for (int k = 0; k < V; ++k)
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j)
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nxt[i][j]  = nxt[i][k];
                }
}
 
 
vector<int> floydPath(int src, int dst, const vector<vector<int>>& nxt)
{
    if (nxt[src][dst] == -1) return {};
    vector<int> path = {src};
    while (src != dst) {
        src = nxt[src][dst];
        path.push_back(src);
    }
    return path;
}
 

 
void printMatrix(int V, const vector<vector<int>>& dist)
{
    cout << "     ";
    for (int j = 0; j < V; ++j)
        cout << setw(6) << j;
    cout << "\n     ";
    for (int j = 0; j < V; ++j)
        cout << "------";
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
    vector<vector<int>> adj(V, vector<int>(V, INF));
 
    for (int i = 0; i < V; ++i) adj[i][i] = 0;
 
    adj[0][1] = 3;
    adj[0][3] = 7;
    adj[1][0] = 8;
    adj[1][2] = 2;
    adj[2][0] = 5;
    adj[2][3] = 1;
    adj[3][0] = 2;
 
    vector<vector<int>> dist, nxt;
    floydWarshall(V, adj, dist, nxt);
 
    cout << "=== Floyd-Warshall: All-Pairs Shortest Distances ===\n\n";
    printMatrix(V, dist);
 
    cout << "\nNegative cycle check: ";
    bool negCycle = false;
    for (int i = 0; i < V; ++i)
        if (dist[i][i] < 0) { negCycle = true; break; }
    cout << (negCycle ? "DETECTED (results invalid)" : "None found") << "\n";
 
    cout << "\n=== Shortest Paths ===\n";
    for (int src = 0; src < V; ++src) {
        for (int dst = 0; dst < V; ++dst) {
            if (src == dst) continue;
            cout << "  " << src << " -> " << dst << " : ";
            if (dist[src][dst] == INF) {
                cout << "No path\n";
                continue;
            }
            cout << "(dist=" << dist[src][dst] << ")  route: ";
            for (int v : floydPath(src, dst, nxt))
                cout << v << " ";
            cout << "\n";
        }
    }
 
    return 0;
}
 