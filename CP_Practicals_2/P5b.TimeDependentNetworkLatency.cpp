#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <climits>
using namespace std;

typedef long long ll;
typedef pair<double, int> pdi;

struct Edge {
    int to;
    ll a, b;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    cout << "Enter N (intersections) and M (roads): " << flush;
    cin >> N >> M;
    
    vector<vector<Edge>> graph(N + 1);
    
    cout << "Enter " << M << " roads (u v a b):\n" << flush;
    for (int i = 0; i < M; i++) {
        int u, v;
        ll a, b;
        cin >> u >> v >> a >> b;
        graph[u].push_back({v, a, b});
    }
    
    // Modified Dijkstra: arrival time is cumulative
    // If you arrive at u at time t, travel time to v is a*t + b
    // So you arrive at v at time: t + (a*t + b) = (a+1)*t + b
    vector<double> arrivalTime(N + 1, 1e18);
    arrivalTime[1] = 0.0;
    priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
    pq.push({0.0, 1});
    
    while (!pq.empty()) {
        double time = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        // Skip if we found a better path already
        if (time > arrivalTime[u] + 1e-9) continue;
        
        for (const Edge& e : graph[u]) {
            // Travel time = a * time + b
            double travelTime = e.a * time + e.b;
            double newArrival = time + travelTime;
            
            if (newArrival < arrivalTime[e.to] - 1e-9) {
                arrivalTime[e.to] = newArrival;
                pq.push({newArrival, e.to});
            }
        }
    }
    
    cout << fixed << setprecision(2);
    cout << "\nEarliest arrival time at intersection " << N << ": ";
    if (arrivalTime[N] > 1e17) {
        cout << "-1 (unreachable)\n";
    } else {
        cout << arrivalTime[N] << "\n";
    }
    
    return 0;
}