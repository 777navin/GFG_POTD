/*
=========================================================
Date        : 17-09-2026
Problem Name: Min Edge Reversals for Path
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Graph, Breadth-First Search, Depth-First Search, Shortest Path

Problem Summary:
- Given a directed graph with n vertices and a list of directed edges.
- Find the minimum number of edge reversals needed to create at least one valid path from a given source `src` to destination `dst`.
- Return -1 if no such path is possible.

Key Observation:
- We can transform the directed graph into an unweighted graph where moving along an original edge has a cost of 0, and moving along a reversed edge has a cost of 1.
- Finding the minimum edge reversals becomes the shortest path problem (0-1 BFS or Dijkstra's algorithm) from `src` to `dst`.
=========================================================
*/

/*
=========================================================
APPROACH EXPLANATION: 0-1 BFS / Dijkstra's Algorithm

1. Intuition:
   - Every edge in the given graph can be traversed in its original direction with 0 cost, or reversed with 1 cost.
   - We want to find the path from `src` to `dst` with the minimum total reversal cost.

2. Approach:
   - Build an adjacency list where each node stores its neighbors along with the weight of the edge (0 for original directed edge, 1 for reverse edge).
   - Use a 0-1 BFS (using a `deque`) or Priority Queue (Dijkstra's) since edge weights are only 0 and 1.
   - Push `src` into the deque with a distance of 0 and keep track of minimum distances to each node using a distance array initialized to infinity.

3. Why it Works:
   - Standard BFS explores level by level, but with 0-1 edge weights, adding 0-weight edges to the front of the deque and 1-weight edges to the back ensures we always process nodes with the minimum cost first.
   - This guarantees the first time we pop `dst`, we have found the minimum edge reversals required.

4. Time Complexity (TC):
   - O(V + E) where V is the number of vertices (`n`) and E is the number of edges (`edges.size()`).

5. Space Complexity (SC):
   - O(V + E) for storing the adjacency list and distance vector.
=========================================================
*/

/*
=========================================================
FINAL APPROACH:
- We use 0-1 BFS because the edge weights are strictly 0 (original direction) and 1 (reversed direction).
- This is much more efficient than general Dijkstra's algorithm and simpler to implement while guaranteeing optimal time complexity.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumEdgeReversal(vector<vector<int>> &edges, int n, int src, int dst) {
        // Adjacency list: stores {neighbor, weight}
        vector<vector<pair<int, int>>> adj(n + 1);
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back({v, 0}); // Original edge: cost 0
            adj[v].push_back({u, 1}); // Reversed edge: cost 1
        }

        // Distance array initialized to infinity
        vector<int> dist(n + 1, 1e9);
        deque<int> dq;

        dist[src] = 0;
        dq.push_front(src);

        while (!dq.empty()) {
            int u = dq.front();
            dq.pop_front();

            if (u == dst) {
                return dist[dst];
            }

            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    if (weight == 0) {
                        dq.push_front(v);
                    } else {
                        dq.push_back(v);
                    }
                }
            }
        }

        // If destination is unreachable
        return dist[dst] == 1e9 ? -1 : dist[dst];
    }
};
