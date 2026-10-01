/*
=========================================================
Date        : 01-10-2026
Problem Name: Minimum Time to Finish Project
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Graph, Topological Sort, Dynamic Programming, Kahn's Algorithm

Problem Summary:
Given 'n' modules with specified execution durations and dependency pairs [u, v]
(where module v depends on module u), find the minimum total time required to
complete all modules when independent modules can run in parallel. Return -1
if a cyclic dependency prevents completion.

Key Observation:
The problem models a Directed Acyclic Graph (DAG) where the minimum time to start 
a module is determined by the maximum completion time among all its dependencies.
=========================================================
*/

/*
=========================================================
APPROACH EXPLANATION
=========================================================

Approach 1: Topological Sort via Kahn's Algorithm + Dynamic Programming
------------------------------------------------------------------------
• Intuition:
  To start a module, all prerequisite modules must finish first. Processing nodes 
  in topological order ensures that when we compute the completion time for a module,
  all its prerequisite times are already finalized.

• Approach:
  1. Build an adjacency list and compute in-degrees for all nodes.
  2. Maintain a DP array `completionTime` where `completionTime[i]` stores the minimum 
     time required to complete module `i` (initialized to `duration[i]`).
  3. Push all nodes with an in-degree of 0 into a queue.
  4. While processing node `u` from the queue, for each dependent node `v`:
     - Update `completionTime[v] = max(completionTime[v], completionTime[u] + duration[v])`.
     - Decrement in-degree of `v`. If in-degree becomes 0, push `v` into the queue.
  5. Count visited nodes; if visited nodes < n, a cycle exists (return -1).
  6. Return the maximum value in `completionTime`.

• Why it Works:
  Kahn's algorithm resolves dependencies layer by layer while detecting cycles.
  Taking the maximum completion time among dependencies guarantees that all parallel
  prerequisites finish before dependent tasks begin.

• Time Complexity (TC) : O(V + E) where V is duration.size() and E is dependencies.size().
• Space Complexity (SC): O(V + E) for the adjacency list, in-degree array, and DP array.
=========================================================
*/

/*
=========================================================
FINAL APPROACH SELECTION
=========================================================
The Topological Sort with Dynamic Programming approach using Kahn's Algorithm is chosen
because it simultaneously computes the critical path (longest path in the DAG) and
detects dependency cycles in optimal linear time O(V + E).
=========================================================
*/

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minTime(vector<int> &duration, vector<vector<int>> &dependencies) {
        int n = duration.size();
        vector<vector<int>> adj(n);
        vector<int> inDegree(n, 0);

        // Build the dependency graph
        for (const auto &dep : dependencies) {
            int u = dep[0];
            int v = dep[1];
            adj[u].push_back(v);
            inDegree[v]++;
        }

        queue<int> q;
        vector<int> completionTime(n, 0);

        // Initialize queue with modules having no dependencies
        for (int i = 0; i < n; ++i) {
            completionTime[i] = duration[i];
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        int processedNodes = 0;

        // Process nodes in topological order
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            processedNodes++;

            for (int v : adj[u]) {
                // The start time of v depends on the max completion time of its prerequisites
                completionTime[v] = max(completionTime[v], completionTime[u] + duration[v]);
                inDegree[v]--;
                
                if (inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        // If not all nodes are processed, a cycle exists
        if (processedNodes < n) {
            return -1;
        }

        // The minimum time to finish the project is the maximum completion time across all modules
        int maxTotalTime = 0;
        for (int i = 0; i < n; ++i) {
            maxTotalTime = max(maxTotalTime, completionTime[i]);
        }

        return maxTotalTime;
    }
};
