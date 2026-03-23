#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    cout << "Enter N (routers) and M (cables): " << flush;
    cin >> N >> M;
    
    vector<vector<pair<int, ll>>> graph(N + 1);
    
    cout << "Enter " << M << " edges (u v w):\n" << flush;
    for (int i = 0; i < M; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); 
    }
    
    vector<ll> dist(N + 1, LLONG_MAX);
    dist[1] = 0;
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.push({0, 1});
    
    while (!pq.empty()) {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto& edge : graph[u]) {
            int v = edge.first;
            ll w = edge.second;
            
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    
    cout << "\nMinimum latency from router 1 to " << N << ": ";
    if (dist[N] == LLONG_MAX) {
        cout << "-1 (no path exists)\n";
    } else {
        cout << dist[N] << "\n";
    }
    
    return 0;
}