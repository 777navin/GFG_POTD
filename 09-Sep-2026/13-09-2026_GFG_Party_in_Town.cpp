/*
=========================================================
Date        : 13-09-2026
Problem Name: Party in Town
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Tree, Graph, BFS, DFS

Problem Summary:
Geek Town has n houses numbered from 1 to n connected by n - 1 bidirectional roads forming a tree.
Choose a house to host a party such that the maximum distance from that house to its farthest house is minimized.
Return this minimum possible distance (the tree's radius).

Key Observation:
The minimum possible maximum distance from any vertex in a tree is precisely its radius, which equals ceil(diameter / 2).
Alternatively, running BFS/DFS from each node or finding the tree diameter via two standard BFS passes directly yields the answer.
=========================================================
*/

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/*
---------------------------------------------------------
APPROACH 1: BFS / DFS from Every Node (Brute Force / All-Pairs)
---------------------------------------------------------
• Intuition:
  Compute the maximum distance to any other node for every single house, then take the minimum of these values.

• Approach:
  Iterate from house 1 to n. For each house, run a standard BFS or DFS traversal to find the maximum depth reached.
  Track the overall minimum over all starting houses.

• Why it Works:
  Directly simulates the problem statement by testing every candidate host house.

• Time Complexity (TC):
  O(V * (V + E)) = O(N^2), as running BFS on an N-node tree takes O(N), repeated N times.

• Space Complexity (SC):
  O(N) auxiliary space for the BFS queue and visited array.

---------------------------------------------------------
APPROACH 2: Tree Center via Diameter (Most Optimal)
---------------------------------------------------------
• Intuition:
  The problem asks for the radius of the tree. The radius of any tree is always exactly ceil(Diameter / 2),
  which is (Diameter + 1) / 2.

• Approach:
  1. Pick an arbitrary node (e.g., node 1) and run BFS to find the farthest node, u.
  2. Run a second BFS from node u to find the farthest node, v.
  3. The distance between u and v is the tree diameter (D).
  4. Return (D + 1) / 2.

• Why it Works:
  In any tree, the node that minimizes the maximum distance to all other nodes is the tree center.
  The maximum distance from the tree center to any leaf is exactly ceil(Diameter / 2).

• Time Complexity (TC):
  O(N), as it only requires two linear BFS traversals over N nodes and N - 1 edges.

• Space Complexity (SC):
  O(N) for queue and distance tracking.
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH:
Approach 2 (Tree Diameter) is chosen.
It improves the time complexity from O(N^2) to O(N), making it optimal and well-suited
even when N scales up to 10^5, requiring only two simple BFS passes.
=========================================================
*/

class Solution {
private:
    // Helper function to perform BFS and return {farthest_node, max_distance}
    pair<int, int> bfs(int startNode, int n, const vector<vector<int>> &adj) {
        vector<int> dist(n + 1, -1);
        queue<int> q;

        dist[startNode] = 0;
        q.push(startNode);

        int farthestNode = startNode;
        int maxDist = 0;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            if (dist[curr] > maxDist) {
                maxDist = dist[curr];
                farthestNode = curr;
            }

            // adj is 0-indexed where adj[i] holds neighbors of house (i + 1)
            for (int neighbor : adj[curr - 1]) {
                if (dist[neighbor] == -1) {
                    dist[neighbor] = dist[curr] + 1;
                    q.push(neighbor);
                }
            }
        }

        return {farthestNode, maxDist};
    }

public:
    int partyHouse(vector<vector<int>> &adj) {
        int n = adj.size();
        if (n <= 1) return 0;

        // Step 1: Find one endpoint of the diameter from an arbitrary node (1)
        pair<int, int> firstPass = bfs(1, n, adj);

        // Step 2: Find the other endpoint of the diameter and the diameter length
        pair<int, int> secondPass = bfs(firstPass.first, n, adj);

        int diameter = secondPass.second;

        // The radius of a tree is ceil(diameter / 2)
        return (diameter + 1) / 2;
    }
};
