/*
=========================================================
Date        : 23-08-2026
Problem Name: Geek in a Maze
Platform    : GeeksforGeeks
Difficulty  : Hard
Tags        : Graph, BFS, Shortest Path, Queue / 0-1 BFS

Problem Summary:
Given an n x m maze with empty cells '.' and obstacles '#', find the number of distinct cells 
visitable starting from (r, c). Movement is allowed in 4 directions, but limited to at most 
'u' up moves and 'd' down moves, while left and right moves are unlimited.

Key Observation:
Since moving left or right has 0 vertical cost, minimizing the total vertical moves (up + down) 
to reach any cell gives the best chance of visiting more cells. This is equivalent to finding the 
shortest path in a graph where horizontal moves have weight 0 and vertical moves have weight 1.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH EXPLANATION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

1. 0-1 BFS / Dijkstra Approach
• Intuition:
  - Moving left/right costs 0 vertical moves; moving up/down costs 1 vertical move.
  - Using a deque (0-1 BFS) allows reaching each reachable cell with the minimum possible up and down moves.

• Approach:
  - Maintain a 2D array storing the minimum `(up_moves, down_moves)` used to reach each cell.
  - Push the starting state `(r, c, 0, 0)` into a double-ended queue (`std::deque`).
  - For horizontal moves (left/right), push to the front of the deque (weight 0).
  - For vertical moves (up/down), increment respective counter and push to the back (weight 1) if within bounds `u` and `d`.
  - Count unique cells popped/visited.

• Why it Works:
  - 0-1 BFS guarantees optimal edge weight exploration in linear time without the $O(\log V)$ overhead of Dijkstra.

• Time Complexity (TC):
  - O(n * m), since each cell is processed a constant number of times.

• Space Complexity (SC):
  - O(n * m) to store the visited state/costs and the deque.
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• 0-1 BFS via `std::deque` is chosen because it directly solves the shortest path problem with edge weights 0 and 1.
• It visits cells with the minimal resource consumption (up/down moves) in optimal $O(n \times m)$ time without priority queue overhead.
*/

#include <vector>
#include <deque>

using namespace std;

class Solution {
    struct State {
        int r, c, up, down;
    };

public:
    int numberOfCells(int r, int c, int u, int d, vector<vector<char>> &mat) {
        int n = mat.size();
        if (n == 0) return 0;
        int m = mat[0].size();

        // If start cell is an obstacle, cannot visit any cell
        if (mat[r][c] == '#') return 0;

        // dist[i][j] stores the minimum (up + down) moves used to reach cell (i, j)
        vector<vector<int>> min_up(n, vector<int>(m, 1e9));
        vector<vector<int>> min_down(n, vector<int>(m, 1e9));

        deque<State> dq;
        dq.push_back({r, c, 0, 0});
        min_up[r][c] = 0;
        min_down[r][c] = 0;

        int visited_count = 0;
        vector<vector<bool>> visited(n, vector<bool>(m, false));

        while (!dq.empty()) {
            State curr = dq.front();
            dq.pop_front();

            if (!visited[curr.r][curr.c]) {
                visited[curr.r][curr.c] = true;
                visited_count++;
            }

            // Move Left (weight 0)
            if (curr.c - 1 >= 0 && mat[curr.r][curr.c - 1] != '#') {
                if (curr.up < min_up[curr.r][curr.c - 1] || curr.down < min_down[curr.r][curr.c - 1]) {
                    min_up[curr.r][curr.c - 1] = min(min_up[curr.r][curr.c - 1], curr.up);
                    min_down[curr.r][curr.c - 1] = min(min_down[curr.r][curr.c - 1], curr.down);
                    dq.push_front({curr.r, curr.c - 1, curr.up, curr.down});
                }
            }

            // Move Right (weight 0)
            if (curr.c + 1 < m && mat[curr.r][curr.c + 1] != '#') {
                if (curr.up < min_up[curr.r][curr.c + 1] || curr.down < min_down[curr.r][curr.c + 1]) {
                    min_up[curr.r][curr.c + 1] = min(min_up[curr.r][curr.c + 1], curr.up);
                    min_down[curr.r][curr.c + 1] = min(min_down[curr.r][curr.c + 1], curr.down);
                    dq.push_front({curr.r, curr.c + 1, curr.up, curr.down});
                }
            }

            // Move Up (weight 1)
            if (curr.r - 1 >= 0 && mat[curr.r - 1][curr.c] != '#' && curr.up + 1 <= u) {
                if (curr.up + 1 < min_up[curr.r - 1][curr.c] || curr.down < min_down[curr.r - 1][curr.c]) {
                    min_up[curr.r - 1][curr.c] = min(min_up[curr.r - 1][curr.c], curr.up + 1);
                    min_down[curr.r - 1][curr.c] = min(min_down[curr.r - 1][curr.c], curr.down);
                    dq.push_back({curr.r - 1, curr.c, curr.up + 1, curr.down});
                }
            }

            // Move Down (weight 1)
            if (curr.r + 1 < n && mat[curr.r + 1][curr.c] != '#' && curr.down + 1 <= d) {
                if (curr.up < min_up[curr.r + 1][curr.c] || curr.down + 1 < min_down[curr.r + 1][curr.c]) {
                    min_up[curr.r + 1][curr.c] = min(min_up[curr.r + 1][curr.c], curr.up);
                    min_down[curr.r + 1][curr.c] = min(min_down[curr.r + 1][curr.c], curr.down + 1);
                    dq.push_back({curr.r + 1, curr.c, curr.up, curr.down + 1});
                }
            }
        }

        return visited_count;
    }
};
