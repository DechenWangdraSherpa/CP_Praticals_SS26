# Algorithm Analysis
## Floyd-Warshall · Johnson's · Borůvka's

---

## Table of Contents

1. [Overview & Comparison](#1-overview--comparison)
2. [Floyd-Warshall](#2-floyd-warshall)
3. [Johnson's Algorithm](#3-johnsons-algorithm)
4. [Borůvka's Algorithm](#4-borůvkas-algorithm)
5. [Head-to-Head Comparisons](#5-head-to-head-comparisons)
6. [When to Use Which](#6-when-to-use-which)

---

## 1. Overview & Comparison

| Property | Floyd-Warshall | Johnson's | Borůvka's |
|---|---|---|---|
| **Problem** | All-Pairs Shortest Path | All-Pairs Shortest Path | Minimum Spanning Tree |
| **Time Complexity** | O(V³) | O(V · E · log V) | O(E · log V) |
| **Space Complexity** | O(V²) | O(V² + E) | O(V + E) |
| **Negative Weights** | ✅ Yes | ✅ Yes | N/A |
| **Negative Cycles** | ❌ No | ❌ No | N/A |
| **Graph Type** | Dense preferred | Sparse preferred | Undirected |
| **Graph Density** | Dense (E ≈ V²) | Sparse (E ≪ V²) | Any |
| **Parallelisable** | Partially | Highly (Dijkstra) | Highly (per component) |

---

## 2. Floyd-Warshall

### 2.1 Algorithm Summary

Floyd-Warshall computes the shortest path between **every pair of vertices** using dynamic programming.
It iterates over every possible intermediate vertex `k` and asks:
_"Is the path from `i` to `j` shorter if we route through `k`?"_

```
dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
```

This recurrence runs for all (i, j, k) combinations, giving the characteristic triple nested loop.

### 2.2 Complexity Analysis

#### Time Complexity: **O(V³)**

| Loop | Iterations |
|------|-----------|
| Outer (k) | V |
| Middle (i) | V |
| Inner (j) | V |
| **Total** | **V³** |

Each iteration does O(1) work (one comparison + one possible assignment).
There are no data-structure overheads — just raw array access.

**Constant factor:** Very low. Cache-friendly sequential array access makes practical performance excellent despite O(V³) asymptotic cost.

#### Space Complexity: **O(V²)**

Two V×V matrices are stored:
- `dist[V][V]` — shortest distances
- `next[V][V]` — path reconstruction

For V = 1000, this is 2 × 10⁶ integers ≈ **8 MB** (manageable).
For V = 10 000, it becomes 2 × 10⁸ integers ≈ **800 MB** (prohibitive).

### 2.3 Correctness & Invariants

**Loop invariant:** After the k-th outer iteration, `dist[i][j]` holds the shortest path from `i` to `j` using only vertices `{0, 1, …, k}` as intermediates.

**Negative weight support:** The algorithm tolerates negative edge weights.
After the algorithm completes, if `dist[i][i] < 0` for any `i`, a **negative cycle** was detected (the algorithm gives no correctness guarantees in that case).

**Convergence:** The DP always terminates in exactly V³ steps regardless of graph structure.

### 2.4 Path Reconstruction

The `next[i][j]` matrix records the first hop toward `j` from `i`.
Reconstruction follows next pointers: O(path length) ≤ O(V) per query.

### 2.5 Strengths & Weaknesses

| Strengths | Weaknesses |
|-----------|------------|
| Extremely simple to implement | Cubic time — infeasible for V > ~3000 |
| Handles negative weights | Quadratic space |
| Low constant factor (cache friendly) | Overkill if only one source is needed |
| Path reconstruction built-in | Cannot detect all negative cycles gracefully |
| No priority queue needed | Does not parallelise well across k iterations |

### 2.6 Optimisations in the Implementation

- Early exit: if `dist[i][k] == INF`, skip inner loop (prunes unreachable pairs)
- The `next` matrix is initialised only for edges that exist, keeping reconstruction sparse

---

## 3. Johnson's Algorithm

### 3.1 Algorithm Summary

Johnson's solves all-pairs shortest paths by combining two classic algorithms:

```
Step 1  Add a super-source q; run Bellman-Ford from q → potentials h[]
Step 2  Re-weight every edge:  w'(u,v) = w(u,v) + h[u] − h[v]
Step 3  Run Dijkstra from every vertex using re-weighted edges
Step 4  Recover true distances:  d(u,v) = dijkstra(u,v) − h[u] + h[v]
```

The re-weighting is the key insight: it eliminates negative edges without changing which paths are shortest, enabling Dijkstra (which requires non-negative weights) to be used.

### 3.2 Complexity Analysis

#### Time Complexity: **O(V · E · log V)**

| Phase | Cost |
|-------|------|
| Bellman-Ford (one run) | O(V · E) |
| Re-weighting all edges | O(E) |
| Dijkstra × V runs | O(V · (E + V) log V) |
| **Total (dominates)** | **O(V · E · log V)** |

With a Fibonacci heap, Dijkstra improves to O(E + V log V), giving Johnson's a total of O(V·E + V²·log V). In practice, binary heaps (as in our implementation) are faster due to better cache behaviour.

#### Space Complexity: **O(V² + E)**

| Structure | Size |
|-----------|------|
| `allDist[V][V]` output matrix | O(V²) |
| `h[]` potential array | O(V) |
| Re-weighted adjacency list | O(E) |
| Dijkstra distance arrays (reused) | O(V) |

### 3.3 When Johnson's Beats Floyd-Warshall

The crossover occurs when:

```
V · E · log V  <  V³
E · log V      <  V²
E              <  V² / log V
```

For a graph with V = 1000, log V ≈ 10, so Johnson's wins when E < 100 000 (i.e., average degree < 100).
Sparse graphs (roads, social networks, dependency graphs) almost always satisfy this condition.

### 3.4 Correctness of Re-weighting

**Claim:** `w'(u,v) = w(u,v) + h[u] − h[v] ≥ 0` for all edges.

**Proof sketch:** Bellman-Ford from the super-source gives `h[v]` = shortest distance from q to v.
By the triangle inequality: `h[v] ≤ h[u] + w(u,v)`, which rearranges to `w(u,v) + h[u] − h[v] ≥ 0`. ∎

**Claim:** Re-weighting preserves which path is shortest.

**Proof:** For any path P = v₀ → v₁ → … → vₖ, the re-weighted total is:
```
Σ w'(vᵢ, vᵢ₊₁) = Σ w(vᵢ, vᵢ₊₁) + h[v₀] − h[vₖ]
```
The h terms telescope; only the source and destination potentials remain.
Since every path from u to v adds the same constant (h[u] − h[v]), relative ordering is preserved. ∎

### 3.5 Strengths & Weaknesses

| Strengths | Weaknesses |
|-----------|------------|
| Faster than Floyd-Warshall on sparse graphs | More complex to implement |
| Handles negative weights | Requires Bellman-Ford overhead (one full pass) |
| Memory efficient (stores adjacency list) | Fails entirely on negative cycles |
| Dijkstra runs are parallelisable | O(V²) output still required |
| Scales to millions of edges | Two-pass design increases implementation risk |

### 3.6 Implementation Notes

Our implementation uses a **binary min-heap** (std::priority_queue) for Dijkstra.
- Heap push/pop: O(log V)
- Stale entries are filtered by comparing `d > dist[u]`
- The super-source (vertex V) is implicit — it is only present in the Bellman-Ford edge list

---

## 4. Borůvka's Algorithm

### 4.1 Algorithm Summary

Borůvka's finds the **Minimum Spanning Tree (MST)** of an undirected weighted graph.
It is a greedy algorithm that works in **phases**:

```
Phase 1  Find the cheapest outgoing edge for each component
Phase 2  Add those edges; merge the components they connect
Repeat until only one component remains
```

Each phase at least halves the number of components, so at most log V phases are needed.

### 4.2 Complexity Analysis

#### Time Complexity: **O(E · log V)**

| Per Phase | Cost |
|-----------|------|
| Scan all edges for cheapest per component | O(E) |
| Merge components via DSU | O(E · α(V)) ≈ O(E) |
| **Phases** | O(log V) (components halve each phase) |
| **Total** | **O(E · log V)** |

α(V) is the inverse Ackermann function — essentially constant for any practical V.

#### Space Complexity: **O(V + E)**

| Structure | Size |
|-----------|------|
| DSU arrays (parent, rank) | O(V) |
| `cheapEdge[]` per phase | O(V) |
| Edge list | O(E) |
| MST output | O(V − 1) |

### 4.3 Correctness (Cut Property)

**Theorem (Cut Property):** The minimum-weight edge crossing any cut of the graph belongs to some MST.

**Borůvka's invariant:** At each phase, the cheapest outgoing edge of every component is safe to add to the MST (it is the minimum edge crossing the cut defined by that component vs. the rest of the graph).

Since all cheapest edges are safe additions and at least one per component is added per phase, the algorithm constructs a valid MST.

**Tie-breaking note:** If multiple edges share the same minimum weight, any consistent choice yields a valid MST (though not necessarily the unique MST if one exists).

### 4.4 Union-Find (DSU) Detail

Our DSU uses two optimisations:

**Path compression:** `find(x)` flattens the tree on every lookup.
```cpp
int find(int x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}
```

**Union by rank:** Always attach the shorter tree under the taller one, keeping trees flat.

Combined, these give amortised O(α(V)) per operation — effectively O(1).

### 4.5 Parallelism Potential

Borůvka's is the **most parallelisable MST algorithm**:
- The "find cheapest edge per component" step is embarrassingly parallel
- Each component scans its own edge subset independently
- This is why Borůvka's is used as the foundation of parallel MST algorithms (e.g., in distributed graph processing systems like Apache Spark GraphX)

### 4.6 Comparison with Prim's and Kruskal's

| Property | Borůvka's | Prim's | Kruskal's |
|----------|-----------|--------|-----------|
| **Time** | O(E log V) | O(E log V) with heap | O(E log E) |
| **Strategy** | Multi-component parallel growth | Single-tree growth | Sort edges globally |
| **Parallelism** | Excellent | Poor (sequential) | Moderate (sort step) |
| **Best for** | Parallel/dense graphs | Dense graphs (Fibonacci heap) | Sparse graphs |
| **Requires sorted edges** | No | No | Yes |

### 4.7 Strengths & Weaknesses

| Strengths | Weaknesses |
|-----------|------------|
| Naturally parallelisable | Slightly more complex than Kruskal's |
| No sorting required | Repeated edge scans (O(E) per phase) |
| Works on disconnected graphs (returns forest) | Edge list must be stored in full |
| Same asymptotic cost as Prim's/Kruskal's | Not intuitive to implement correctly |
| Memory efficient | Race conditions must be handled in parallel versions |

---

## 5. Head-to-Head Comparisons

### 5.1 Floyd-Warshall vs. Johnson's (All-Pairs SP)

Both solve the same problem. The choice depends entirely on graph density.

```
Graph density (E/V²):   0%       25%       50%      75%      100%
                        |---------|---------|---------|---------|
Use Johnson's:          ████████████████
Use Floyd-Warshall:                      ████████████████████
```

**Rule of thumb:** If `E < V² / log V`, prefer Johnson's. Otherwise, Floyd-Warshall's simplicity wins.

**Concrete example with V = 500:**

| Metric | Floyd-Warshall | Johnson's (sparse, E = 2000) |
|--------|----------------|-------------------------------|
| Operations | 125 000 000 | ~11 000 000 |
| Speedup | 1× | ~11× |

| Metric | Floyd-Warshall | Johnson's (dense, E = 250 000) |
|--------|----------------|--------------------------------|
| Operations | 125 000 000 | ~1 120 000 000 |
| Slowdown | 1× | ~9× slower |

### 5.2 Dijkstra (Single Source) vs. Johnson's (All-Pairs)

If you only need shortest paths **from one source**, Dijkstra alone is O(E log V) — skip Johnson's.
Johnson's is essentially V repeated Dijkstra runs with the overhead of one Bellman-Ford.

### 5.3 Scalability at a Glance

| V | Floyd-Warshall | Johnson's (E = 10V) | Borůvka's (E = 10V) |
|---|---------------|---------------------|---------------------|
| 100 | 1 M ops | 7 K ops | 7 K ops |
| 1 000 | 1 B ops | 100 K ops | 100 K ops |
| 10 000 | 1 T ops | 1.3 M ops | 1.3 M ops |
| 100 000 | Infeasible | 17 M ops | 17 M ops |

---

## 6. When to Use Which

### Decision Tree

```
Are you finding shortest paths?
├── Yes
│   ├── Only one source?
│   │   └── → Use Dijkstra (no negatives) or Bellman-Ford (negatives)
│   └── All pairs?
│       ├── Dense graph (E ≈ V²) or V < 500?
│       │   └── → Floyd-Warshall  (simple, fast in practice)
│       └── Sparse graph (E ≪ V²)?
│           ├── No negative weights?
│           │   └── → V × Dijkstra
│           └── Negative weights (no negative cycles)?
│               └── → Johnson's Algorithm
└── Are you finding a Minimum Spanning Tree?
    ├── Need parallelism or working in distributed system?
    │   └── → Borůvka's
    ├── Dense graph?
    │   └── → Prim's (with Fibonacci heap)
    └── Sparse graph or edges already sorted?
        └── → Kruskal's or Borůvka's
```

### Quick Reference Card

| Situation | Best Choice | Reason |
|-----------|-------------|--------|
| Dense graph, all-pairs SP | Floyd-Warshall | Simple O(V³), low constant |
| Sparse graph, all-pairs SP, neg. weights | Johnson's | O(VE log V) beats O(V³) |
| Sparse graph, all-pairs SP, no neg. weights | V × Dijkstra | Skip Bellman-Ford overhead |
| Single source SP, no neg. weights | Dijkstra | O(E log V) |
| Single source SP, neg. weights | Bellman-Ford | O(VE) |
| MST, parallel environment | Borůvka's | Embarrassingly parallel phases |
| MST, sequential, sparse | Kruskal's | Simple, O(E log E) |
| MST, sequential, dense | Prim's | O(V²) with adjacency matrix |

---

## Appendix: Notation Reference

| Symbol | Meaning |
|--------|---------|
| V | Number of vertices |
| E | Number of edges |
| O(·) | Asymptotic upper bound (worst case) |
| Ω(·) | Asymptotic lower bound (best case) |
| Θ(·) | Tight asymptotic bound |
| α(V) | Inverse Ackermann function (≈ 5 for all practical V) |
| INF | Sentinel value representing "no path" (10⁹ in implementation) |
| h[v] | Johnson's potential for vertex v (from Bellman-Ford) |
| w'(u,v) | Re-weighted edge cost in Johnson's algorithm |

---

*Analysis corresponds to the C++ implementation in `graph_algorithms.cpp`.*