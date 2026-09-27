/*
=========================================================
Date        : 27-09-2026
Problem Name: Longest Colored Path
Platform    : GeeksforGeeks
Difficulty  : Hard
Tags        : Trees, Depth First Search, Dynamic Programming on Trees

Problem Summary:
- Given a tree with n nodes colored either Red (R) or Blue (B) and n-1 undirected edges.
- A path is valid if no Red node appears after a Blue node on the path.
- Find the maximum number of nodes in any valid path.

Key Observation:
- A valid path consists of zero or more Red nodes followed by zero or more Blue nodes (R*B*).
- We can use tree DP/DFS to compute the longest valid path passing through each node by tracking valid sequences of nodes.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
APPROACH: Optimized Tree DP using DFS

• Intuition: 
  Every valid path looks like some number of 'R' nodes followed by some number of 'B' nodes. For any node, we can compute the longest path starting or ending with specific color patterns using DFS.
• Approach:
  1. Build an adjacency list for the tree.
  2. Perform a DFS traversal to compute for each subtree:
     - maxR: max length of a path consisting entirely of 'R' nodes ending at the current node.
     - maxB: max length of a path consisting entirely of 'B' nodes ending at the current node.
     - maxRB: max length of a valid path starting with 'R' nodes and ending with 'B' nodes.
  3. Combine results from children to update the global maximum valid path length.
• Why it Works:
  Since the graph is a tree (undirected acyclic graph), DFS allows us to aggregate path lengths from all child subtrees efficiently in linear time.
• Time Complexity (TC): O(n)
• Space Complexity (SC): O(n)
=========================================================
*/

class Solution {
private:
    int maxPathLength = 0;

    // Returns a tuple/vector containing: {count_R, count_B, count_RB} for the subtree rooted at u
    // 0: max 'R' path ending at u
    // 1: max 'B' path ending at u
    // 2: max 'R' followed by 'B' path ending at u
    vector<int> dfs(int u, int p, const string &s, const vector<vector<int>> &adj) {
        int r = 0, b = 0, rb = 0;
        
        if (s[u - 1] == 'R') {
            r = 1;
            rb = 1;
        } else {
            b = 1;
            rb = 1;
        }

        int best_r = r;
        int best_b = b;
        int best_rb = rb;

        for (int v : adj[u]) {
            if (v == p) continue;
            vector<int> child = dfs(v, u, s, adj);
            int c_r = child[0];
            int c_b = child[1];
            int c_rb = child[2];

            // If current is R and child is R
            if (s[u - 1] == 'R' && s[v - 1] == 'R') {
                maxPathLength = max(maxPathLength, best_r + c_r);
                best_r = max(best_r, r + c_r);
                best_rb = max(best_rb, r + c_r);
            }
            // If current is B and child is B
            else if (s[u - 1] == 'B' && s[v - 1] == 'B') {
                maxPathLength = max(maxPathLength, best_b + c_b);
                maxPathLength = max(maxPathLength, best_rb + c_b); // R* followed by B*
                best_b = max(best_b, b + c_b);
                best_rb = max(best_rb, rb + c_b);
            }
            // If current is B and child is R (Invalid transition from B to R on path)
            else if (s[u - 1] == 'B' && s[v - 1] == 'R') {
                // Cannot combine R after B
            }
            // If current is R and child is B (Valid transition from R to B)
            else if (s[u - 1] == 'R' && s[v - 1] == 'B') {
                maxPathLength = max(maxPathLength, best_r + c_rb);
                best_rb = max(best_rb, r + c_rb);
            }
        }

        maxPathLength = max({maxPathLength, best_r, best_b, best_rb});
        return {best_r, best_b, best_rb};
    }

public:
    int longestPath(string &s, vector<vector<int>> &edges) {
        int n = s.size();
        vector<vector<int>> adj(n + 1);
        for (const auto &edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        maxPathLength = 0;
        dfs(1, 0, s, adj);
        return maxPathLength;
    }
};
