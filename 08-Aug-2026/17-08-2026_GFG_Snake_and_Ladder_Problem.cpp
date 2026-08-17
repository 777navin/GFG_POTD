/*
=========================================================
Date        : 17-08-2026
Problem Name: Snake and Ladder Problem
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Graph, BFS, Shortest Path

Problem Summary:
Find the minimum number of dice throws required to reach cell n*n from cell 1 
on an n x n Snakes and Ladders board. Landing on the base of a ladder or the 
mouth of a snake immediately transports the player to its destination.

Key Observation:
Since every dice throw has an unweighted cost of 1, the problem models finding 
the shortest path in an unweighted directed graph, which can be solved optimally via BFS.
=========================================================
*/

#include <vector>
#include <queue>

using namespace std;

/*
---------------------------------------------------------
APPROACH 1: Breadth-First Search (BFS) [Most Optimal]
---------------------------------------------------------
• Intuition:
  - Each board cell represents a node, and each valid dice throw (1 to 6) represents a directed edge of weight 1.
  - Standard BFS explores all reachable nodes layer by layer, guaranteeing the shortest path in unweighted graphs.

• Approach:
  - Map snakes and ladders to a lookup array `board` of size (n*n + 1), initialized such that board[i] = i.
  - For each ladder (u, v) and snake (u, v), set board[u] = v.
  - Maintain a queue storing pairs of `{current_cell, moves}` and a `visited` array to avoid cycles.
  - Start BFS from cell 1. For each state, try all 6 dice throws, move to the mapped destination, and push to the queue.

• Why it Works:
  - The first time destination n*n is dequeued/reached, it is guaranteed to have taken the minimal number of throws.

• Time Complexity (TC):
  - O(N^2), where total cells = N^2. Each cell is visited at most once, and each state explores up to 6 transitions.

• Space Complexity (SC):
  - O(N^2) to store the board mappings, visited array, and BFS queue.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH CHOICE:
BFS is chosen because finding the minimum number of steps in an unweighted graph 
is optimally done in linear time relative to the number of vertices and edges (O(V + E)). 
It avoids deep recursion, redundant subproblem evaluations, and cycle issues inherent in DFS.
---------------------------------------------------------
*/

class Solution {
public:
    int minThrows(int n, vector<int>& lad, vector<int>& sn) {
        int totalCells = n * n;
        
        // board[i] stores destination cell from cell i (accounts for snakes and ladders)
        vector<int> board(totalCells + 1);
        for (int i = 1; i <= totalCells; ++i) {
            board[i] = i;
        }

        // Add ladders
        for (int i = 0; i < (int)lad.size(); i += 2) {
            board[lad[i]] = lad[i + 1];
        }

        // Add snakes
        for (int i = 0; i < (int)sn.size(); i += 2) {
            board[sn[i]] = sn[i + 1];
        }

        // BFS setup: {current_cell, throws_count}
        queue<pair<int, int>> q;
        vector<bool> visited(totalCells + 1, false);

        q.push({1, 0});
        visited[1] = true;

        while (!q.empty()) {
            auto [curr, moves] = q.front();
            q.pop();

            if (curr == totalCells) {
                return moves;
            }

            // Try all possible dice throws from 1 to 6
            for (int dice = 1; dice <= 6; ++dice) {
                int nextCell = curr + dice;

                if (nextCell <= totalCells) {
                    int dest = board[nextCell];

                    if (!visited[dest]) {
                        visited[dest] = true;
                        q.push({dest, moves + 1});
                    }
                }
            }
        }

        return -1; // If destination is unreachable
    }
};
