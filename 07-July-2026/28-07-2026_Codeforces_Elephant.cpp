/*
=========================================================
Date        : 28-07-2026
Problem Name: Shortest Path in 1-2 Graph
Platform    : GeeksforGeeks
Difficulty  : Hard
Tags        : Graph, Shortest Path, Dijkstra, BFS

Problem Summary:
Given an undirected graph where edge weights are strictly 1 or 2.
Find the shortest path distance from a source vertex to a destination vertex.
Return -1 if the destination is unreachable.

Key Observation:
Since weights are positive, standard shortest path algorithms apply. 
Because the weights are strictly 1 and 2, we can use a priority queue 
or a modified BFS to find the shortest path efficiently.
=========================================================

=========================================================
APPROACHES
=========================================================

1. Brute Force (DFS / Backtracking)
• Intuition: Explore all possible paths from source to destination.
• Approach: Keep a track of the minimum path sum seen so far across all paths.
• Why it Works: Exhaustively searches the state space.
• Time Complexity (TC): O(V!) in the worst case for dense graphs.
• Space Complexity (SC): O(V) for recursion stack.

2. Better (Standard Dijkstra's Algorithm)
• Intuition: Use a min-heap to greedily expand the closest reachable node.
• Approach: Maintain a distance array and a priority queue. Always process the node with the current minimum distance.
• Why it Works: Standard property of Dijkstra ensures the first time a node is popped, its shortest path is found.
• Time Complexity (TC): O(E log V) due to priority queue operations.
• Space Complexity (SC): O(V + E) for adjacency list and priority queue.

3. Most Optimal (Modified BFS / 0-1-2 Graph BFS)
• Intuition: Avoid the O(log V) overhead of the priority queue by exploiting the fact that weights are strictly 1 or 2.
• Approach: Can either use Dial's Algorithm (array of queues) or insert dummy nodes on edges of weight 2 to reduce it to a simple unweighted BFS. 
• Why it Works: Normal BFS correctly finds shortest paths in unweighted graphs.
• Time Complexity (TC): O(V + E)
• Space Complexity (SC): O(V + E)
=========================================================

=========================================================
FINAL APPROACH CHOSEN: Standard Dijkstra's Algorithm
• Why this approach is chosen: It perfectly balances simplicity, robustness, and speed. It avoids the memory overhead of creating dummy nodes required for the unweighted BFS conversion.
• Why it is better than previous ones: E log V easily passes the constraint (E <= 2*10^5) without generating excessive states or complex queue management arrays.
=========================================================
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int shortestPath(int V, int src, int dest, vector<vector<int>>& edges) {
        // Create adjacency list
        vector<vector<pair<int, int>>> adj(V);
        for (const auto& edge : edges) {
            adj[edge[0]].push_back({edge[1], edge[2]});
            adj[edge[1]].push_back({edge[0], edge[2]});
        }

        // Min-heap for Dijkstra's algorithm: {distance, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        // Distance array initialized to infinity
        vector<int> dist(V, 1e9);

        // Start from the source node
        pq.push({0, src});
        dist[src] = 0;

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            // Early exit if we reached the destination
            if (u == dest) return d;

            // Skip if we already found a shorter path to 'u'
            if (d > dist[u]) continue;

            // Traverse adjacent nodes
            for (const auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                // Relaxation step
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        // If destination is unreachable
        return dist[dest] == 1e9 ? -1 : dist[dest];
    }
};
