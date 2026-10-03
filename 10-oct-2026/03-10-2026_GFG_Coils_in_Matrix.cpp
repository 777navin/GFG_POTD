/*
=========================================================
Date        : 03-10-2026
Problem Name: Coils in Matrix
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Matrix, Pattern Searching, Data Structures

Problem Summary:
Given an integer n, consider a (4n x 4n) matrix filled with 1 to (4n)^2 in row-major order.
Form two coils: Coil 1 starts from top-left (0, 0) and spirals inward; Coil 2 starts from 
bottom-right (4n-1, 4n-1) and spirals inward in the opposite direction.
Return both coils as a 2D vector.

Key Observation:
Total elements per coil is 8n^2. The movement lengths follow a strictly decreasing sequence 
of L, L-2, L-2, L-4 for directions Down, Right, Up, and Left respectively, where L starts at 4n.
=========================================================
*/

#include <vector>

using namespace std;

/*
---------------------------------------------------------
APPROACH 1: Corrected Pattern Simulation & Complement Mapping
---------------------------------------------------------
• Intuition:
  Tracing the spiral step sizes reveals a perfect geometric pattern. For any cycle starting 
  with length L = 4n, the path moves Down L steps, Right L-2 steps, Up L-2 steps, and Left L-4 steps.
  
• Approach:
  1. Start with L = 4 * n, initial row r = -1, and col c = 0.
  2. In a loop while L >= 4, simulate moving Down (L), Right (L-2), Up (L-2), and Left (L-4).
  3. Decrease L by 4 in each iteration until the coil is fully traced.
  4. Construct Coil 2 using the symmetric complement property: Coil2[i] = 16*n*n + 1 - Coil1[i].

• Why it Works:
  This correctly traces the exact spiraling length requirements sequentially. Because the matrix 
  is rotationally symmetric, Coil 2 is just the exact mathematical inverse of Coil 1.

• Time Complexity (TC):
  O(n^2) - Iterates exactly 8n^2 times to construct each coil.

• Space Complexity (SC):
  O(1) - Auxiliary space, excluding the O(n^2) memory required to return the output vectors.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH
---------------------------------------------------------
This optimal approach is selected because it completely bypasses the need for creating a full
O(n^2) 2D array matrix and accurately resolves the step-length pattern directly mapping 1D coordinates.
---------------------------------------------------------
*/

class Solution {
public:
    vector<vector<int>> formCoils(int n) {
        vector<int> coil1;
        int L = 4 * n;
        int r = -1; // Start at -1 so the first Down step lands on row 0
        int c = 0;
        
        // Generate Coil 1 traversing exactly along the pattern
        while (L >= 4) {
            // Move Down L steps
            for (int i = 0; i < L; ++i) {
                r++;
                coil1.push_back(r * 4 * n + c + 1);
            }
            // Move Right L - 2 steps
            for (int i = 0; i < L - 2; ++i) {
                c++;
                coil1.push_back(r * 4 * n + c + 1);
            }
            // Move Up L - 2 steps
            for (int i = 0; i < L - 2; ++i) {
                r--;
                coil1.push_back(r * 4 * n + c + 1);
            }
            // Move Left L - 4 steps
            for (int i = 0; i < L - 4; ++i) {
                c--;
                coil1.push_back(r * 4 * n + c + 1);
            }
            // Move to inner coil cycle
            L -= 4;
        }
        
        // Generate Coil 2 as the exact matrix complement
        vector<int> coil2;
        int total_val = 16 * n * n + 1;
        for (int val : coil1) {
            coil2.push_back(total_val - val);
        }
        
        return {coil1, coil2};
    }
};
