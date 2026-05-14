/*
Date: 14-05-2026
Problem Name: Search for Subarray
Platform: GeeksforGeeks
Difficulty: Hard
Tags: KMP Algorithm, String Matching, Pattern Searching, Arrays

Problem Summary:
Given two integer arrays 'a[]' and 'b[]', the task is to find all starting indices 
where array 'b[]' occurs as a contiguous subarray within array 'a[]'.

Methods to Solve:
1. Brute Force (Naive Pattern Searching)
2. Optimal Approach (KMP Algorithm for Integer Arrays)

--------------------------------------------------------------------------------
1. Brute Force
- Intuition: Check every possible starting position in 'a[]' to see if 'b[]' matches.
- Approach: Iterate from i = 0 to (n - m). For each i, run a nested loop to compare 
  a[i...i+m-1] with b[0...m-1].
- Dry Run: a=[2,4,1,0,4,1], b=[4,1]. 
           i=0: [2,4]!=b. 
           i=1: [4,1]==b (Match at 1).
- Time Complexity: O(N * M)
- Space Complexity: O(1) (excluding output)
- When to use: Small constraints or when M is very small.

2. Optimal Approach (KMP Algorithm)
- Intuition: Use the Knuth-Morris-Pratt logic to avoid redundant comparisons by 
  pre-processing the pattern 'b[]' to create a Longest Prefix Suffix (LPS) array.
- Approach: 
    a) Build LPS array for 'b[]'. LPS[i] stores the length of the longest proper 
       prefix of b[0...i] that is also a suffix of b[0...i].
    b) Use two pointers (i for 'a', j for 'b'). If a[i] == b[j], increment both.
    c) If a mismatch occurs after some matches, use LPS[j-1] to skip unnecessary 
       re-evaluations of 'a[]'.
- Dry Run: a=[2,4,1,0,4,1], b=[4,1]. LPS=[0,0]. 
           i=1, j=0 match. i=2, j=1 match -> Found index (2-2) = 1.
- Time Complexity: O(N + M)
- Space Complexity: O(M) for the LPS array.
- Why better than previous method: It ensures each element in the main array is 
  processed effectively once, leading to linear time.
- When to use: Large constraints (N, M up to 10^6).

Comparison Table:
Method       | TC      | SC   | Best Use Case
             |         |      |
Brute Force  | O(N*M)  | O(1) | Small arrays
KMP (Optimal)| O(N+M)  | O(M) | Large arrays / Competitive Programming

Final Recommended Solution: KMP Algorithm
*/

#include <iostream>
#include <vector>

using namespace std;

/**
 * Class Solution provides a method to find all occurrences of 
 * a pattern subarray 'b' within a target array 'a'.
 */
class Solution {
public:
    /**
     * Uses KMP algorithm to find all starting indices of b[] in a[].
     * @param a Target array
     * @param b Pattern array
     * @return Vector of starting indices
     */
    vector<int> search(vector<int>& a, vector<int>& b) {
        int n = a.size();
        int m = b.size();
        vector<int> result;

        if (m == 0) return result;

        // Step 1: Precompute the LPS (Longest Prefix Suffix) array for b
        vector<int> lps(m, 0);
        computeLPS(b, m, lps);

        int i = 0; // index for a[]
        int j = 0; // index for b[]

        while (i < n) {
            if (a[i] == b[j]) {
                i++;
                j++;
            }

            if (j == m) {
                // Found a match, store starting index
                result.push_back(i - j);
                j = lps[j - 1];
            } else if (i < n && a[i] != b[j]) {
                // Mismatch after j matches
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }

        return result;
    }

private:
    /**
     * Helper function to build the LPS array.
     */
    void computeLPS(const vector<int>& b, int m, vector<int>& lps) {
        int len = 0;
        lps[0] = 0; // lps[0] is always 0
        int i = 1;

        while (i < m) {
            if (b[i] == b[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }
};

// Driver code compatible with GFG standard
int main() {
    // Fast I/O for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Sample Input Handling
    // a[] = [2, 4, 1, 0, 4, 1, 1], b[] = [4, 1]
    vector<int> a = {2, 4, 1, 0, 4, 1, 1};
    vector<int> b = {4, 1};

    Solution obj;
    vector<int> indices = obj.search(a, b);

    for (int idx : indices) {
        cout << idx << " ";
    }
    cout << endl;

    return 0;
}
