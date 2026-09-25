/*
=========================================================
Date        : 25-09-2026
Problem Name: Box Stacking
Platform    : GeeksforGeeks (GFG)
Difficulty  : Hard
Tags        : Dynamic Programming, Sorting

Problem Summary:
Given n boxes with height, width, and length, find the maximum height 
of a stack formed by stacking them. A box can be placed atop another 
only if both base dimensions are strictly smaller, and each box can be rotated.

Key Observation:
Each box yields 3 unique base orientations (ensuring length >= width). 
Sorting all generated orientations by base area reduces the problem to 
the Longest Increasing Subsequence (LIS) variant.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Recursive / Brute Force (Backtracking)
---------------------------------------------------------
• Intuition:
  Generate all 3 rotations per box, then recursively explore every valid 
  stacking combination to find the maximum possible height.

• Approach:
  - Generate all 3 rotations for each box such that length >= width.
  - At each step, try placing every eligible rotation on top of the current box.
  - Recurse and track the maximum cumulative height.

• Why it Works:
  Explores all valid stacking sequences exhaustively.

• Time Complexity (TC) : O(3^n) or exponential - re-evaluates overlapping subproblems.
• Space Complexity (SC): O(n) - recursion call stack depth.
---------------------------------------------------------

---------------------------------------------------------
APPROACH 2: Dynamic Programming (LIS Variation) [Optimal]
---------------------------------------------------------
• Intuition:
  A box can only sit on a box with strictly larger base dimensions (length and width).
  Sorting by base area ensures that any valid base below a box must appear earlier in the array.

• Approach:
  - Generate all 3 rotations for each box:
      (h, max(w, l), min(w, l))
      (w, max(h, l), min(h, l))
      (l, max(h, w), min(h, w))
  - Sort all 3*n rotations descending by base area (length * width).
  - Apply DP similar to LIS where dp[i] represents the maximum stack height ending with box i as the top box.
  - dp[i] = height[i] + max({0, dp[j]}) for all j < i where length[i] < length[j] and width[i] < width[j].
  - Return the maximum value in dp[].

• Why it Works:
  Sorting establishes a topological order via base area, eliminating cyclic dependencies 
  and allowing optimal substructure caching.

• Time Complexity (TC) : O(N^2) where N = 3 * n boxes, so O(n^2) operations.
• Space Complexity (SC): O(n) - stores all rotations and DP array.
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH: Dynamic Programming (LIS Variation)
=========================================================
• Why this approach is chosen:
  The constraint n <= 100 makes an O(n^2) DP approach execute in milliseconds,
  fitting well within time limits without recursion overhead.
• Why it is better:
  Avoids exponential time complexity of backtracking by sorting 
  and memoizing the best stack heights.
=========================================================
*/

#include <vector>
#include <algorithm>

using namespace std;

struct Box {
    int h, w, l;
};

class Solution {
public:
    int maxHeight(vector<int>& height, vector<int>& width, vector<int>& length) {
        int n = height.size();
        vector<Box> boxes;
        boxes.reserve(3 * n);

        // Generate all 3 orientations for each box
        // Convention: length >= width for consistent comparison
        for (int i = 0; i < n; i++) {
            // Orientation 1: height[i] as height
            boxes.push_back({height[i], min(width[i], length[i]), max(width[i], length[i])});

            // Orientation 2: width[i] as height
            boxes.push_back({width[i], min(height[i], length[i]), max(height[i], length[i])});

            // Orientation 3: length[i] as height
            boxes.push_back({length[i], min(height[i], width[i]), max(height[i], width[i])});
        }

        // Sort boxes descending by base area (l * w)
        sort(boxes.begin(), boxes.end(), [](const Box& a, const Box& b) {
            long long areaA = 1LL * a.l * a.w;
            long long areaB = 1LL * b.l * b.w;
            return areaA > areaB;
        });

        int totalBoxes = boxes.size();
        vector<int> dp(totalBoxes);
        int maxStackHeight = 0;

        for (int i = 0; i < totalBoxes; i++) {
            dp[i] = boxes[i].h;
            for (int j = 0; j < i; j++) {
                // Check if box i can be placed on top of box j
                if (boxes[i].w < boxes[j].w && boxes[i].l < boxes[j].l) {
                    dp[i] = max(dp[i], dp[j] + boxes[i].h);
                }
            }
            maxStackHeight = max(maxStackHeight, dp[i]);
        }

        return maxStackHeight;
    }
};
