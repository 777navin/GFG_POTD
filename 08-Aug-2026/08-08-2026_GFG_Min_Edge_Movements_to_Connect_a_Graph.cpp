/*
=========================================================
Date        : 08-08-2026
Problem Name: Min Edge Movements to Connect a Graph
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Graph, DFS, Disjoint Set Union

Problem Summary:
Given 'n' vertices and 'm' edges, find the minimum operations to make the graph connected by moving edges. Return -1 if it is impossible to connect the graph.

Key Observation:
To connect 'C' components, we need exactly 'C - 1' edges. We just need to check if the total number of edges is at least 'n - 1' and then find the number of isolated connected components.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
1. Approach 1: Depth First Search (DFS)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition: A graph can only be fully connected if it has at least n-1 edges. The operations needed equal the number of extra connected components minus 1.
• Approach: Build an adjacency list. Traverse unvisited nodes using DFS to count the total number of connected components.
• Why it Works: DFS explores the entirety of each component. Counting the DFS triggers gives the exact number of disjoint components.
• Time Complexity (TC): O(V + E) to build the graph and traverse it.
• Space Complexity (SC): O(V + E) for the adjacency list and O(V) for the visited array.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
2. Approach 2: Disjoint Set Union (DSU) (Most Optimal)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition: DSU is highly efficient for dynamic connectivity. We can count components on the fly without building a full adjacency list.
• Approach: Initialize 'n' components. For each edge, union the two nodes. If they belong to different sets, decrement the component count.
• Why it Works: Each successful union operation merges two components into one. The final count minus one gives the required operations.
• Time Complexity (TC): O(E * α(V)), where α is the inverse Ackermann function (effectively O(1)).
• Space Complexity (SC): O(V) for the parent and size arrays in the DSU structure.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• We choose the Disjoint Set Union (DSU) approach.
• It is better because it avoids the O(V + E) space overhead of an adjacency list, replacing it with an O(V) space requirement, and runs efficiently in near-linear time while keeping the code clean.
*/

#include <iostream>
#include <vector>

using namespace std;

// Disjoint Set Union Data Structure
class DSU {
    vector<int> parent, size;
public:
    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int findUPar(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findUPar(parent[node]);
    }

    bool unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        
        if (ulp_u == ulp_v) return false;
        
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
        return true;
    }
};

class Solution {
public:
    int minEdgesReq(int n, vector<vector<int>>& edges) {
        // If total edges are less than n-1, it's impossible to connect all nodes.
        if (edges.size() < n - 1) {
            return -1;
        }
        
        DSU dsu(n);
        int components = n;
        
        for (auto& edge : edges) {
            // If they belong to different components, merge them and reduce component count
            if (dsu.unionBySize(edge[0], edge[1])) {
                components--;
            }
        }
        
        // We need components - 1 edges to connect all remaining disjoint components
        return components - 1;
    }
};

// Driver code for standalone execution and testing
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = 6;
    vector<vector<int>> edges = {{0,1}, {0,2}, {0,3}, {1,2}, {1,3}};
    
    Solution obj;
    int ans = obj.minEdgesReq(n, edges);
    
    cout << "Minimum Operations: " << ans << "\n";
    
    return 0;
}
