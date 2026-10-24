/*
=========================================================
Date        : 24-10-2026
Problem Name: Trace Path
Platform    : GeeksforGeeks
Difficulty  : Easy
Tags        : Matrix, Simulation, Geometry

Problem Summary:
- Geek starts from any cell in an n x m grid.
- Given a string of L, R, U, and D movements, determine
  whether any starting cell keeps the entire path inside
  the grid.

Key Observation:
- The starting cell is flexible, so we only need to find
  the minimum grid dimensions required to fit the path.
- Track the minimum and maximum row and column offsets.
=========================================================

APPROACH 1: BRUTE FORCE
---------------------------------------------------------
Intuition:
- Try every possible starting cell in the grid.

Approach:
- Simulate all commands from each starting cell.
- Return true if any starting cell completes the path
  without leaving the grid.

Why it Works:
- Every possible starting cell is checked.

Time Complexity (TC): O(n * m * |s|)
Space Complexity (SC): O(1)

APPROACH 2: OPTIMIZED — TRACK PATH BOUNDARIES
---------------------------------------------------------
Intuition:
- The entire path can fit if its vertical and horizontal
  spans do not exceed the grid dimensions.

Approach:
- Start at relative position (0, 0).
- Update row and column offsets for every command.
- Maintain minimum and maximum offsets in both directions.
- Check whether both spans fit inside the grid.

Why it Works:
- Translating the path changes its starting position but
  not its overall dimensions.
- If both spans fit, a suitable starting cell exists.

Time Complexity (TC): O(|s|)
Space Complexity (SC): O(1)

FINAL APPROACH:
- Use boundary tracking because it processes each command
  exactly once, avoiding repeated path simulations.
- The path fits if maxRow - minRow < n and
  maxCol - minCol < m.
- This meets the expected O(|s|) time and O(1) space.
=========================================================
*/

class Solution {
public:
    bool isPossible(int n, int m, string& s) {
        int row = 0, col = 0;

        int minRow = 0, maxRow = 0;
        int minCol = 0, maxCol = 0;

        for (char command : s) {
            if (command == 'L') {
                col--;
            } else if (command == 'R') {
                col++;
            } else if (command == 'D') {
                row--;
            } else if (command == 'U') {
                row++;
            }

            minRow = min(minRow, row);
            maxRow = max(maxRow, row);

            minCol = min(minCol, col);
            maxCol = max(maxCol, col);
        }

        return (maxRow - minRow < n) &&
               (maxCol - minCol < m);
    }
};
