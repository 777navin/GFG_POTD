/*
=========================================================
Date        : 02-11-2026
Problem Name: Largest Sum Cycle
Platform    : GeeksforGeeks
Difficulty  : Hard
Tags        : Graph, Cycle Detection, Topological Sort

Problem Summary:
- Given a directed graph where each node has at most one outgoing edge.
- Find the maximum sum of node indices belonging to a cycle.
- Return -1 if no cycle exists.

Key Observation:
- Nodes with indegree 0 cannot belong to a cycle.
- Repeatedly remove these nodes using Kahn's Algorithm.
- All remaining nodes belong to cycles.
=========================================================

APPROACH 1: DFS (Cycle Detection)

- Intuition:
  Detect cycles using visited and recursion-path arrays.

- Approach:
  Traverse each unvisited node and detect back edges.
  Calculate the sum of nodes whenever a cycle is found.

- Why it Works:
  A back edge to a node in the current DFS path identifies a cycle.

- Time Complexity: O(N)
- Space Complexity: O(N)


APPROACH 2: KAHN'S ALGORITHM (OPTIMIZED)

- Intuition:
  Nodes outside cycles can be eliminated by removing indegree-zero nodes.

- Approach:
  1. Calculate the indegree of every node.
  2. Push all indegree-zero nodes into a queue.
  3. Remove them and decrease the indegree of their outgoing neighbors.
  4. Remaining nodes belong to cycles.
  5. Traverse each remaining cycle and calculate its sum.

- Why it Works:
  Every node in a directed cycle has at least one incoming edge
  from another node in that cycle. Removing non-cycle nodes
  leaves only cycle nodes.

- Time Complexity: O(N)
- Space Complexity: O(N)


FINAL APPROACH:
- Kahn's Algorithm is selected because it avoids recursion.
- It efficiently removes all non-cycle nodes.
- Each node and edge is processed at most a constant number of times.
- Therefore, it achieves O(N) time and O(N) auxiliary space.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestSumCycle(vector<int>& edge) {

        int n = edge.size();

        // Step 1: Calculate indegree of every node.
        vector<int> indegree(n, 0);

        for (int i = 0; i < n; i++) {
            if (edge[i] != -1) {
                indegree[edge[i]]++;
            }
        }

        // Step 2: Add all nodes having indegree 0.
        queue<int> q;
        vector<bool> removed(n, false);

        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
                removed[i] = true;
            }
        }

        // Step 3: Remove non-cycle nodes.
        while (!q.empty()) {

            int node = q.front();
            q.pop();

            int next = edge[node];

            if (next != -1) {

                indegree[next]--;

                if (indegree[next] == 0) {
                    q.push(next);
                    removed[next] = true;
                }
            }
        }

        // Step 4: Find maximum cycle sum.
        long long ans = -1;

        for (int i = 0; i < n; i++) {

            if (!removed[i]) {

                long long sum = 0;
                int curr = i;

                // Traverse the complete cycle.
                while (!removed[curr]) {

                    removed[curr] = true;
                    sum += curr;

                    curr = edge[curr];
                }

                ans = max(ans, sum);
            }
        }

        return static_cast<int>(ans);
    }
};

/*
=========================================================
Time Complexity  : O(N)
Space Complexity : O(N)

=========================================================
*/
