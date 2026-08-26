/*
=========================================================
Date        : 26-08-2026
Problem Name: Negative Weight Cycle
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Graph, Bellman-Ford, Shortest Path

Problem Summary:
Given a weighted directed graph with V vertices and E edges,
determine whether the graph contains any negative weight cycle.
A negative weight cycle is a cycle whose edge weights sum to a negative value.

Key Observation:
In a graph with V vertices and no negative cycle, the shortest path between any
pair of vertices contains at most V - 1 edges. If relaxing edges on the V-th
iteration still decreases any distance, a negative weight cycle exists.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Bellman-Ford Algorithm (Optimal)
---------------------------------------------------------
• Intuition:
  - Repeatedly relax all edges up to V - 1 times.
  - To detect cycles across disconnected components without adding a dummy node,
    initialize all vertex distances to 0.

• Approach:
  - Initialize distance array `dist` of size V with 0s.
  - Relax every directed edge (u -> v with weight w) V - 1 times:
    if dist[u] + w < dist[v], update dist[v] = dist[u] + w.
  - Perform a V-th relaxation check over all edges.
  - If any distance can still be reduced, return true (negative cycle exists); else return false.

• Why it Works:
  - Initializing all distances to 0 simulates a super source connected to all vertices with 0-weight edges,
    allowing detection of reachable negative cycles from any component.
  - Any relaxation possible after V - 1 iterations indicates an infinitely decreasing path (cycle).

• Time Complexity (TC): O(V * E)
• Space Complexity (SC): O(V)
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH:
---------------------------------------------------------
• The Bellman-Ford algorithm is the standard and optimal approach for detecting
  negative weight cycles in general directed graphs with potential disconnected components.
• Setting initial distances to 0 ensures all components are evaluated in a single pass without extra graph modifications.
*/

#include <vector>

class Solution {
public:
    bool isNegativeWeightCycle(int V, std::vector<std::vector<int>>& edges) {
        // Distance array initialized to 0 to cover disconnected components
        std::vector<int> dist(V, 0);

        // Relax all edges V - 1 times
        for (int i = 1; i <= V - 1; ++i) {
            for (const auto& edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int w = edge[2];

                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }

        // Check for negative weight cycle on the V-th iteration
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            if (dist[u] + w < dist[v]) {
                return true;
            }
        }

        return false;
    }
};
