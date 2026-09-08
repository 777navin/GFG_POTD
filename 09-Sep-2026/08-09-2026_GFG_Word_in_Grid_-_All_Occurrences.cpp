/*
=========================================================
Date        : 08-09-2026
Problem Name: Word in Grid - All Occurrences
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Arrays, Matrix, String, Searching

Problem Summary:
Given an n x m 2D grid of characters and a target word, find all unique 
starting coordinates (r, c) where the word can be formed in any of the 8 
directions in a straight line without changing direction. Return the starting
coordinates in lexicographically smallest order.

Key Observation:
Once a starting cell matches the first character of the word, we only need
to check straight-line continuations in each of the 8 predefined directions.
Iterating row-by-row and column-by-column naturally yields coordinates in 
lexicographically sorted order.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Directional Linear Search (Optimal)
---------------------------------------------------------
• Intuition:
  Check every cell in the grid. If it matches the first character of the word,
  explore all 8 directional vectors to see if the full word exists along any straight ray.

• Approach:
  - Traverse all coordinates (r, c) in row-major order.
  - Define 8 directional offset pairs: (-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1).
  - For each starting cell, if `mat[r][c] == word[0]`, iterate through each direction.
  - Traverse step-by-step up to the length of `word`, checking bounds and character matches.
  - If a full match is found in any direction, record `{r, c}` and break immediately to prevent duplicate entries for the same cell.

• Why it Works:
  The problem restricts movement to fixed, straight directions (no turns/branching),
  so simple line-of-sight ray casting from each cell accurately finds all valid words.

• Time Complexity (TC):
  O(n * m * 8 * L) = O(n * m * L), where n is rows, m is columns, and L is the length of the word.
  With n, m <= 50 and L <= 20, operations are at most ~50 * 50 * 8 * 20 = 400,000, which runs comfortably within milliseconds.

• Space Complexity (SC):
  O(1) auxiliary space (excluding the returned result array).
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH:
---------------------------------------------------------
• Why this approach is chosen:
  A direct 8-direction straight-line simulation checks only potential word paths
  with zero recursive overhead. Traversal in row-major order guarantees that coordinates
  are naturally discovered in lexicographically sorted order without needing an extra sort.
---------------------------------------------------------
*/

#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    // 8 movement directions: Up, Down, Left, Right, and 4 Diagonals
    const int dRow[8] = {-1, -1, -1,  0, 0,  1, 1, 1};
    const int dCol[8] = {-1,  0,  1, -1, 1, -1, 0, 1};

    bool searchInDirection(const vector<vector<char>> &mat, const string &word, int r, int c, int dir) {
        int n = mat.size();
        int m = mat[0].size();
        int len = word.length();

        for (int k = 1; k < len; ++k) {
            int newR = r + k * dRow[dir];
            int newC = c + k * dCol[dir];

            // Boundary and character match check
            if (newR < 0 || newR >= n || newC < 0 || newC >= m || mat[newR][newC] != word[k]) {
                return false;
            }
        }
        return true;
    }

public:
    vector<vector<int>> searchWord(vector<vector<char>> &mat, string &word) {
        vector<vector<int>> result;
        int n = mat.size();
        if (n == 0) return result;
        int m = mat[0].size();
        int len = word.length();

        // Row-major traversal ensures coordinates are gathered in lexicographical order
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (mat[r][c] == word[0]) {
                    // Single character word match
                    if (len == 1) {
                        result.push_back({r, c});
                        continue;
                    }

                    // Check all 8 directions
                    for (int dir = 0; dir < 8; ++dir) {
                        if (searchInDirection(mat, word, r, c, dir)) {
                            result.push_back({r, c});
                            break; // Avoid adding duplicate entries for the same starting cell
                        }
                    }
                }
            }
        }

        return result;
    }
};
