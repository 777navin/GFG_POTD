/*
Date: 13-05-2026
Problem Name: Mother Vertex
Platform: GeeksforGeeks (GFG)
Difficulty: Medium
Tags: Graph, DFS, Strongly Connected Components (SCC), Kosaraju's Algorithm

Problem Summary:
Given a directed graph with V vertices and E edges, find a "Mother Vertex". 
A Mother Vertex is a vertex from which every other vertex in the graph is reachable.
- If multiple mother vertices exist, return the one with the smallest index.
- If no mother vertex exists, return -1.

Methods to Solve:

1. Brute Force (DFS/BFS from every vertex):
- Intuition: Check reachability for every single vertex independently.
- Approach: For each vertex i from 0 to V-1, perform a DFS. If the count of visited nodes equals V, i is a mother vertex. Since we check in increasing order, the first one found is the smallest.
- Time Complexity: O(V * (V + E))
- Space Complexity: O(V) for the visited array and recursion stack.
- Why better than previous method: N/A (Baseline).
- When to use: Only when V and E are very small (e.g., V < 1000).

2. Optimal Approach (DFS Finish Time Logic - Kosaraju's Idea):
- Intuition: In a Directed Acyclic Graph (DAG), the mother vertex must be in the source node (in-degree 0). In a general directed graph, if a mother vertex exists, it must be part of a "source" Strongly Connected Component (SCC). The vertex that finishes last in a standard DFS traversal is guaranteed to be in such a source SCC.
- Approach:
    a) Perform a DFS traversal of the graph and keep track of the last finished vertex (v).
    b) After the first pass, 'v' is the only potential candidate for a mother vertex.
    c) Reset the visited array and perform a second DFS starting only from 'v' to verify if it can reach all nodes.
    d) To handle the "smallest index" requirement: If 'v' is a mother vertex, all nodes in the same SCC as 'v' are also mother vertices. We find all nodes that can reach 'v' (using the transpose graph) and are reachable from 'v', then pick the minimum index.
- Time Complexity: O(V + E)
- Space Complexity: O(V + E) to store the adjacency list and transpose graph.
- Why better than previous method: It reduces the complexity from quadratic to linear, making it suitable for V = 10^5.
- When to use: Standard competitive programming approach for reachability problems in large graphs.

Comparison Table:
Method       | TC          | SC       | Best Use Case
-----------------------------------------------------------
Brute Force  | O(V(V+E))   | O(V)     | Small constraints
Optimal DFS  | O(V+E)      | O(V+E)   | Large graphs (V=10^5)

Final Recommended Solution:
The Optimal Approach using DFS finish time and SCC verification to ensure the smallest index is returned.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

class Solution {
private:
    // Standard DFS to track finish order
    void dfs(int u, const vector<int> adj[], vector<bool>& visited, int& lastFinished) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs(v, adj, visited, lastFinished);
            }
        }
        lastFinished = u;
    }

    // Simple DFS for reachability check
    void checkReachability(int u, const vector<int> adj[], vector<bool>& visited, int& count) {
        visited[u] = true;
        count++;
        for (int v : adj[u]) {
            if (!visited[v]) {
                checkReachability(v, adj, visited, count);
            }
        }
    }

    // DFS on transpose graph to find nodes in the same SCC
    void findSCCNodes(int u, const vector<int> revAdj[], vector<bool>& visited, vector<int>& scc) {
        visited[u] = true;
        scc.push_back(u);
        for (int v : revAdj[u]) {
            if (!visited[v]) {
                findSCCNodes(v, revAdj, visited, scc);
            }
        }
    }

public:
    /**
     * @brief Finds the smallest Mother Vertex in a directed graph.
     * @param V Number of vertices.
     * @param edges Vector of edges [u, v].
     * @return Smallest Mother Vertex index or -1 if none exists.
     */
    int findMotherVertex(int V, vector<vector<int>>& edges) {
        vector<int> adj[V];
        vector<int> revAdj[V];
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            revAdj[edge[1]].push_back(edge[0]); // For SCC verification
        }

        vector<bool> visited(V, false);
        int candidate = -1;

        // Step 1: Find the last finished vertex
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs(i, adj, visited, candidate);
            }
        }

        // Step 2: Verify if the candidate is actually a mother vertex
        fill(visited.begin(), visited.end(), false);
        int reachableCount = 0;
        checkReachability(candidate, adj, visited, reachableCount);

        if (reachableCount != V) {
            return -1;
        }

        // Step 3: Find the smallest index in the same SCC as the candidate
        // All vertices in the candidate's SCC are also mother vertices.
        // A node u is in candidate's SCC if candidate reaches u AND u reaches candidate.
        // We already know candidate reaches all u. Now find all u that reach candidate.
        vector<int> motherVertices;
        vector<bool> visitedRev(V, false);
        findSCCNodes(candidate, revAdj, visitedRev, motherVertices);

        // The smallest index among those that can reach 'candidate' 
        // (and are reachable from it, which is everyone here) will be our answer.
        int minMother = motherVertices[0];
        for (int v : motherVertices) {
            if (v < minMother) minMother = v;
        }

        return minMother;
    }
};

// --- Driver Code for GFG Compatibility ---
int main() {
    int V = 5;
    vector<vector<int>> edges = {{0, 2}, {0, 3}, {1, 0}, {2, 1}, {3, 4}};
    
    Solution ob;
    int ans = ob.findMotherVertex(V, edges);
    cout << "Mother Vertex: " << ans << endl; // Expected Output: 0

    return 0;
}
