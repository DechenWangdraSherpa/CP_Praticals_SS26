# Algorithm Analysis
## Floyd-Warshall · Johnson's · Borůvka's

---

## Quick Comparison

| | Floyd-Warshall | Johnson's | Borůvka's |
|---|---|---|---|
| **What it does** | Shortest path between all pairs | Shortest path between all pairs | Minimum spanning tree |
| **Time** | O(V³) | O(V · E · log V) | O(E · log V) |
| **Space** | O(V²) | O(V² + E) | O(V + E) |
| **Negative weights?** | yes | yes | N/A |
| **Best for** | Dense graphs | Sparse graphs | Any graph |

---

## Floyd-Warshall

**What it does:** Finds the shortest path between every pair of vertices.

**How it works:** For every possible "middle stop" vertex `k`, it checks:
> *"Is going from A → k → B shorter than going directly A → B?"*

It does this for all combinations of A, B, and k — hence the three nested loops.

**Time: O(V³)** — three loops, each running V times. Simple, no fancy data structures needed.

**Space: O(V²)** — just two V×V grids (distances + paths).

**When to use it:**
- You need distances between *all* pairs of vertices
- Your graph is dense (lots of edges)
- You want the simplest possible code

**Watch out:** Falls apart with negative cycles. Gets very slow/memory-heavy past ~3000 vertices.

---

## Johnson's Algorithm

**What it does:** Also finds shortest paths between all pairs — but smarter for sparse graphs.

**How it works in plain English:**
1. Add a fake "super node" connected to every vertex with cost 0
2. Run Bellman-Ford from that fake node to get a "price tag" `h[v]` for each vertex
3. Use those price tags to shift all edge weights to be non-negative
4. Now run Dijkstra from every vertex (safe now that weights are positive)
5. Undo the shift to get the real distances back

**Time: O(V · E · log V)** — one Bellman-Ford + V Dijkstra runs.

**Space: O(V² + E)** — stores the full result matrix plus the edge list.

**When to use it:**
- Sparse graph (few edges relative to vertices)
- You have negative edge weights but no negative cycles
- Floyd-Warshall is too slow

**Watch out:** More code to write. If there's a negative cycle, it refuses to run entirely.

---

## Borůvka's Algorithm

**What it does:** Builds a Minimum Spanning Tree — the cheapest set of edges that connects all vertices.

**How it works in plain English:**
1. Start with every vertex as its own island
2. Each island finds the single cheapest bridge to any other island
3. Connect all those bridges, merging islands together
4. Repeat until everything is one connected landmass

Each round at least halves the number of islands, so it finishes in O(log V) rounds.

**Time: O(E · log V)** — scan all edges once per round, O(log V) rounds.

**Space: O(V + E)** — just the edge list and a Union-Find structure.

**When to use it:**
- You want a minimum spanning tree
- You want something that can be parallelised easily (each island works independently)

**Watch out:** Only works on undirected graphs. Slightly trickier to implement than Kruskal's.

---

## Which one should I use?

```
Need shortest paths?
├── Between ALL pairs + dense graph  →  Floyd-Warshall
├── Between ALL pairs + sparse graph →  Johnson's
└── From ONE source only             →  Dijkstra (or Bellman-Ford if negative weights)

Need minimum spanning tree?          →  Borůvka's (or Kruskal's for simplicity)
```

---

## The summary of each

- **Floyd-Warshall** — brute force all pairs, simple but slow on big graphs
- **Johnson's** — clever re-weighting trick to run Dijkstra on graphs with negative edges
- **Borůvka's** — keep merging components by their cheapest exit edge until one remains