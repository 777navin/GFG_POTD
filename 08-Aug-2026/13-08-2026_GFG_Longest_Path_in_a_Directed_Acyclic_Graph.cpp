/*
=========================================================
Date        : 13-08-2026
Problem Name: Longest Path in a Directed Acyclic Graph
Platform    : GeeksforGeeks (GFG)
Difficulty  : Hard
Tags        : Graph, DAG, Topological Sort, Dynamic Programming

Problem Summary:
Given a weighted Directed Acyclic Graph (DAG) with V vertices and a source vertex src,
find the longest distance from src to all other vertices.
If a vertex is unreachable from src, set its distance to INT_MIN.

Key Observation:
Since the graph is acyclic (DAG), we can process vertices in Topological Order.
This ensures that when we process a node, all incoming paths to it have already been computed.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH EXPLANATION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Approach 1: Topological Sort + Dynamic Programming (Most Optimal)

• Intuition:
  In a DAG, linear ordering (Topological Sort) guarantees that for every directed edge u -> v,
  vertex u comes before vertex v. Thus, distances to u are finalized before resolving v.

• Approach:
  1. Build adjacency list from given edge list.
  2. Compute in-degrees for Topological Sort (Kahn's Algorithm using Queue).
  3. Obtain the Topological Ordering of all vertices.
  4. Initialize dist array with INT_MIN and set dist[src] = 0.
  5. Process vertices in topological order; for each reachable vertex u, update dist[v] = max(dist[v], dist[u] + weight).

• Why it Works:
  Processing nodes in topological order prevents cycles and re-computations, strictly respecting edge directions and computing optimal max paths in a single pass.

• Time Complexity (TC):
  O(V + E) - Building adjacency list, running Kahn's algorithm, and edge relaxation each take O(V + E) time.

• Space Complexity (SC):
  O(V + E) - Auxiliary memory for adjacency list, topological queue, in-degree array, and distance array.
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

Why this approach is chosen:
• It solves the longest path problem on DAGs in linear O(V + E) time without exponential search overhead.
• Longest path on general graphs is NP-Hard, but acyclic property makes single-pass DP via Topological Sort optimal.
*/

class Solution {
public:
    vector<int> maxDistance(int V, int src, vector<vector<int>>& edges) {
        // Build adjacency list: adj[u] = {{v, weight}, ...}
        vector<vector<pair<int, int>>> adj(V);
        vector<int> inDegree(V, 0);

        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            adj[u].push_back({v, w});
            inDegree[v]++;
        }

        // Kahn's Algorithm for Topological Sort
        queue<int> q;
        for (int i = 0; i < V; ++i) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> topoOrder;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            topoOrder.push_back(node);

            for (const auto& neighbor : adj[node]) {
                int v = neighbor.first;
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        // Distance array initialized to INT_MIN
        vector<int> dist(V, INT_MIN);
        dist[src] = 0;

        // Relax edges in Topological Order
        for (int u : topoOrder) {
            if (dist[u] != INT_MIN) {
                for (const auto& neighbor : adj[u]) {
                    int v = neighbor.first;
                    int weight = neighbor.second;
                    if (dist[u] + weight > dist[v]) {
                        dist[v] = dist[u] + weight;
                    }
                }
            }
        }

        return dist;
    }
};
