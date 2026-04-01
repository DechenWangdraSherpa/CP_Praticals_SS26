#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Edge { int u, v, w; };


struct DSU {
    vector<int> parent, rank_;
    DSU(int n) : parent(n), rank_(n, 0) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (rank_[x] < rank_[y]) swap(x, y);
        parent[y] = x;
        if (rank_[x] == rank_[y]) ++rank_[x];
        return true;
    }
};


long long boruvka(int V, const vector<Edge>& edges, vector<Edge>& mstEdges)
{
    DSU dsu(V);
    long long total = 0;
    int components = V;
    mstEdges.clear();

    while (components > 1) {
        vector<int> cheapEdge(V, -1);
        for (int i = 0; i < (int)edges.size(); ++i) {
            int cu = dsu.find(edges[i].u), cv = dsu.find(edges[i].v);
            if (cu == cv) continue;
            if (cheapEdge[cu] == -1 || edges[i].w < edges[cheapEdge[cu]].w) cheapEdge[cu] = i;
            if (cheapEdge[cv] == -1 || edges[i].w < edges[cheapEdge[cv]].w) cheapEdge[cv] = i;
        }
        for (int c = 0; c < V; ++c) {
            if (cheapEdge[c] == -1) continue;
            int i = cheapEdge[c];
            if (!dsu.unite(edges[i].u, edges[i].v)) continue;
            mstEdges.push_back(edges[i]);
            total += edges[i].w;
            --components;
        }
    }
    return (components > 1) ? -1 : total;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Boruvka's Algorithm (MST) ===\n\n";

    int V = 5;
    vector<Edge> edges = {
        {0,1,2},{0,3,6},{1,2,3},{1,3,8},
        {1,4,5},{2,4,7},{3,4,9}
    };

    vector<Edge> mst;
    long long total = boruvka(V, edges, mst);

    if (total == -1) {
        cout << "Graph is disconnected -- no spanning tree exists.\n";
        return 1;
    }

    cout << "MST edges:\n";
    for (auto& [u, v, w] : mst)
        cout << "  " << u << " -- " << v << "  (w=" << w << ")\n";
    cout << "\nTotal MST weight: " << total << "\n";

    return 0;
}