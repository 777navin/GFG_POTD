/*
=========================================================
Date        : 03-11-2026
Problem Name: Count Tree Paths With Limited Max Edge Weight
Platform    : GeeksforGeeks
Difficulty  : Hard
Tags        : Tree, DSU, Sorting, Union Find

Problem Summary:
Given a weighted tree and multiple queries, count the
number of distinct paths whose maximum edge weight is
less than or equal to the given query value.

Key Observation:
When two disconnected components are merged, every node
in one component forms a new valid path with every node
in the other component.

New Paths = sizeA * sizeB
=========================================================

1. Brute Force
   - For every query, traverse the tree and count valid paths.
   - TC: O(Q * N^2)
   - SC: O(N)

2. Optimized: Sorting + DSU
   - Sort edges and queries by weight.
   - Merge components using DSU as query limits increase.
   - Each merge contributes sizeA * sizeB new paths.
   - TC: O(N log N + Q log Q + N * α(N))
   - SC: O(N + Q)

Why This Approach?
- Avoids repeatedly traversing the tree for every query.
- DSU efficiently maintains connected components.
- Sorting allows each edge to be processed only once.
- Union by size and path compression optimize DSU operations.
=========================================================
*/

class Solution {
public:

    vector<int> parent, sz;

    // Find representative with path compression.
    int find(int x) {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    // Merge two components and return newly formed paths.
    long long unite(int u, int v) {

        u = find(u);
        v = find(v);

        if (u == v)
            return 0;

        // Union by size.
        if (sz[u] < sz[v])
            swap(u, v);

        // Every cross-component pair forms one new path.
        long long newPaths = 1LL * sz[u] * sz[v];

        parent[v] = u;
        sz[u] += sz[v];

        return newPaths;
    }

    vector<int> maximumWeight(int n,
                              vector<vector<int>> edges,
                              vector<int>& queries) {

        // Sort edges by increasing weight.
        sort(edges.begin(), edges.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[2] < b[2];
             });

        int q = queries.size();

        // Store queries with their original indices.
        vector<pair<int, int>> sortedQueries;

        for (int i = 0; i < q; i++) {
            sortedQueries.push_back({queries[i], i});
        }

        sort(sortedQueries.begin(), sortedQueries.end());

        // Initialize DSU.
        parent.resize(n + 1);
        sz.assign(n + 1, 1);

        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }

        vector<int> ans(q);

        int edgeIndex = 0;
        long long totalPaths = 0;

        // Process queries in increasing order.
        for (auto& [limit, originalIndex] : sortedQueries) {

            // Include every edge satisfying weight <= limit.
            while (edgeIndex < (int)edges.size() &&
                   edges[edgeIndex][2] <= limit) {

                int u = edges[edgeIndex][0];
                int v = edges[edgeIndex][1];

                totalPaths += unite(u, v);

                edgeIndex++;
            }

            // Restore original query order.
            ans[originalIndex] = (int)totalPaths;
        }

        return ans;
    }
};

/*
=========================================================
Time Complexity  : O(N log N + Q log Q + N * α(N))
Space Complexity : O(N + Q)
=========================================================
*/
