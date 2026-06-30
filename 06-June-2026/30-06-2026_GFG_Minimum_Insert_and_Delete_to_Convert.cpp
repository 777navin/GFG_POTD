/*
=========================================================
Date        : 30-06-2026
Problem Name: Minimum Insert and Delete to Convert
Platform    : GeeksforGeeks
Difficulty  : Hard
Tags        : Dynamic Programming, Binary Search, Longest Increasing Subsequence

Problem Summary:
Given two arrays `a[]` and `b[]` of sizes `n` and `m`, find the minimum number of insertions and deletions on array `a[]` to make it identical to `b[]`. 
Note: Array `b[]` is sorted, and all its elements are distinct. 

Constraints:
1 <= n, m <= 10^5
1 <= a[i], b[i] <= 10^5

Key Observation:
The minimum operations required to convert `a[]` to `b[]` is equal to:
(n - LCS) + (m - LCS)
where LCS is the Longest Common Subsequence between `a[]` and `b[]`. 
Since elements in `b[]` are distinct and sorted, the standard $O(N \times M)$ LCS problem can be reduced to an $O(N \log N)$ Longest Increasing Subsequence (LIS) problem.
=========================================================

-------------------------------------------------------
APPROACH 1: Standard LCS (Dynamic Programming) - Brute Force
-------------------------------------------------------
Intuition      : The operations required depend entirely on the elements both arrays have in common in the same relative order (LCS). The elements to delete from `a` are `n - LCS`, and the elements to insert from `b` are `m - LCS`.
Idea           : Use a classic 2D DP table to find the LCS of `a[]` and `b[]`.
Approach       : 
                 1. Create a DP table of size (n+1) x (m+1).
                 2. If a[i-1] == b[j-1], dp[i][j] = 1 + dp[i-1][j-1].
                 3. Else, dp[i][j] = max(dp[i-1][j], dp[i][j-1]).
                 4. Result is (n - dp[n][m]) + (m - dp[n][m]).
Dry Run        : a = [1, 4], b = [1, 4]. LCS is 2. Ops = (2 - 2) + (2 - 2) = 0.
Why it works   : LCS correctly identifies the longest sequence of elements we do not need to delete or insert.
Time Complexity: $O(N \times M)$
Space Complex. : $O(N \times M)$ or $O(M)$ using space optimization.
Advantages     : Easy to think of and implement.
Disadvantages  : Will cause Time Limit Exceeded (TLE) given constraints $N, M \le 10^5$.
When to use    : When N, M <= 1000.
Why next better: We need an approach that runs in $O(N \log N)$ to pass constraints.

-------------------------------------------------------
APPROACH 2: Longest Increasing Subsequence (LIS) with Binary Search - Optimal
-------------------------------------------------------
Intuition      : Since elements in `b[]` are distinct and sorted, we can map each element in `a[]` to its corresponding index in `b[]`. Any common subsequence between `a[]` and `b[]` will appear as an strictly increasing sequence of these mapped indices.
Idea           : Filter `a[]` by keeping only elements present in `b[]`. Since `b[]` is sorted, we can use Binary Search to quickly find if an element in `a[]` exists in `b[]` and get its index. Then, find the LIS of these valid indices.
Approach       : 
                 1. Create an empty list `lis`.
                 2. Iterate through each element `x` in `a[]`.
                 3. Use binary search (`std::lower_bound`) to find `x` in `b[]`.
                 4. If found, let its index be `idx`. We perform standard LIS $O(N \log N)$ logic:
                    - Use `std::lower_bound` on `lis` to find the correct position of `idx`.
                    - If it's greater than all elements, `push_back(idx)`.
                    - Otherwise, replace the element at the found position.
                 5. LCS length = `lis.size()`.
                 6. Return `(a.size() + b.size() - 2 * LCS)`.
Dry Run        : a = [1, 2, 5, 3, 1], b = [1, 3, 5]
                 - x=1: found at b[0]. lis=[0]
                 - x=2: not found in b.
                 - x=5: found at b[2]. lis=[0, 2]
                 - x=3: found at b[1]. `lower_bound` in lis for 1 replaces 2. lis=[0, 1]
                 - x=1: found at b[0]. `lower_bound` in lis for 0 replaces 0. lis=[0, 1]
                 - LCS length = 2. Ops = (5+3) - 2*2 = 4.
Why it works   : By mapping `a[]` to indices of `b[]` and finding the LIS, we are effectively finding the longest sequence of elements in `a[]` that appear in `b[]` in the exact same sorted order.
Time Complexity: $O(N \log M + N \log N)$, where $N \log M$ is for searching in `b` and $N \log N$ is for LIS.
Space Complex. : $O(N)$ for the `lis` array.
Advantages     : Passes all constraints smoothly. Extremely fast execution.
Disadvantages  : Requires understanding of the DP to LIS reduction technique.
When to use    : Standard trick when finding LCS of two arrays where one has distinct elements.

-------------------------------------------------------
COMPARISON TABLE
-------------------------------------------------------
Method          | Idea                                   | Time        | Space       | Difficulty | Recommended
----------------|----------------------------------------|-------------|-------------|------------|------------
1. DP (LCS)     | Standard 2D DP for LCS                 | $O(N \times M)$  | $O(M)$      | Medium     | No (TLE)
2. LIS + BS     | Map elements to indices, find LIS      | $O(N \log N)$    | $O(N)$      | Hard       | Yes

=========================================================
FINAL RECOMMENDED APPROACH
=========================================================
Approach 2 (LIS with Binary Search) is the best and only viable solution. Given the maximum constraints of $10^5$, an $O(N \times M)$ solution will result in roughly $10^{10}$ operations, strictly leading to TLE. By leveraging the fact that `b[]` has distinct and sorted elements, we gracefully transform the LCS problem into an $O(N \log N)$ LIS problem using `std::lower_bound`, which executes well within the time limits.
*/

class Solution {
public:
    int minInsAndDel(vector<int> &a, vector<int> &b) {
        vector<int> lis;
        
        for (int x : a) {
            // Since b is sorted, use binary search to check if x exists in b
            auto it = lower_bound(b.begin(), b.end(), x);
            
            // If x is present in b
            if (it != b.end() && *it == x) {
                int target_idx = distance(b.begin(), it);
                
                // Perform Longest Increasing Subsequence (LIS) on the matched indices
                auto pos = lower_bound(lis.begin(), lis.end(), target_idx);
                if (pos == lis.end()) {
                    lis.push_back(target_idx); // Extend the sequence
                } else {
                    *pos = target_idx; // Replace to maintain the smallest ending values
                }
            }
        }
        
        int lcs_length = lis.size();
        
        // Minimum operations = (deletions from a) + (insertions from b)
        return a.size() + b.size() - (2 * lcs_length);
    }
};
