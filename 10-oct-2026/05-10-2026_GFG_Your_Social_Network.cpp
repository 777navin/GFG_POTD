/*
=========================================================
Date        : 05-10-2026
Problem Name: Your Social Network
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Graph, DFS, BFS, Array

Problem Summary:
Given an array `arr` of size n - 1 representing one-way links where `arr[i - 2]` is the direct friend 
of user `i` (2 <= i <= n), find all reachable users `j` (1 <= j < i) for each user `i`.
For every reachable pair, determine the number of links `k` required to reach `j` from `i`.
Return the results ordered by user `i`, then by user `j` in increasing order.

Key Observation:
Since each user `i` (2 <= i <= n) points to a strictly smaller user number, traversing backwards 
from `i` to `1` follows a directed acyclic chain (tree structure). We can compute path lengths on the fly or 
use dynamic programming/traversal to collect all reachable ancestors and their distances.
=========================================================
*/

#include <vector>

using namespace std;

/*
---------------------------------------------------------
APPROACH 1: Direct Chain Traversal (Iterative Path Following)
---------------------------------------------------------
• Intuition:
  Since each user `i` has a unique outgoing link to a smaller user, following links from `i` forms a unique path towards user 1.
  We can explicitly walk down the path starting from each user `i`.

• Approach:
  For each user `i` from 2 to n, maintain a step counter `k` initialized to 1 and a current pointer starting at `arr[i - 2]`.
  Traverse until no further links exist, recording `[i, current_user, k]` at each step.
  Sort/organize the pairs for user `i` by target user `j` in increasing order.

• Why it Works:
  Every user has at most one parent with a smaller ID, making the reachability graph a set of paths directed toward user 1 with no cycles.

• Time Complexity (TC):
  O(n^2) in the worst case (e.g., a linear chain like 5 -> 4 -> 3 -> 2 -> 1 where path length for user i is O(i)).

• Space Complexity (SC):
  O(1) auxiliary space (excluding the space needed to store the output).
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH SELECTION:
We choose the Direct Chain Traversal approach because the constraints (n <= 500) make an O(n^2) time complexity extremely fast and optimal.
It avoids extra overhead, memory allocation for graph adjacency lists, and complex DP state management while directly producing the result.
---------------------------------------------------------
*/

class Solution {
public:
    vector<vector<int>> socialNetwork(vector<int>& arr) {
        vector<vector<int>> result;
        int n = arr.size() + 1;

        // Process users i from 2 to n
        for (int i = 2; i <= n; ++i) {
            // Collect reachable pairs (j, k) for user i
            vector<pair<int, int>> reachable;
            
            int curr = arr[i - 2];
            int dist = 1;
            
            // Follow parent links to collect all reachable ancestors
            while (curr >= 1) {
                reachable.push_back({curr, dist});
                if (curr == 1) break; // User 1 has no friends
                curr = arr[curr - 2];
                dist++;
            }
            
            // Re-order by target user j in increasing order (j from 1 to i - 1)
            // Since we traversed backwards (i -> parent -> grandparent...),
            // we can sort or place them directly into the output.
            // Using a simple array insertion or sorting by j:
            vector<vector<int>> temp;
            for (int j = 1; j < i; ++j) {
                for (auto& p : reachable) {
                    if (p.first == j) {
                        result.push_back({i, j, p.second});
                        break;
                    }
                }
            }
        }

        return result;
    }
};
