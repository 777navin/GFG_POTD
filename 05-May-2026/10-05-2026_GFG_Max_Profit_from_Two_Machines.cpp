/*
Date: 10-05-2026
Problem Name: Max Profit from Two Machines
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Greedy, Sorting, Prefix Sum, Optimization

Problem Summary:
Given two machines, A and B, and a set of 'n' tasks. You earn a[i] profit if Machine A 
performs the i-th task, and b[i] profit if Machine B performs it. Machine A can process 
at most 'x' tasks, and Machine B can process at most 'y' tasks. With x + y >= n, ensure 
every task is assigned to maximize the total profit.

Methods to Solve:
1. Dynamic Programming (Memoization) - Brute Force
2. Greedy with Sorting and Sliding Window - Optimal Approach

For EACH method include:

Method 1: Dynamic Programming (Memoization)
- Intuition: At each task 'i', we have a choice: assign it to Machine A (if capacity allows) 
  or Machine B (if capacity allows). We can explore all valid combinations to find the max profit.
- Approach: Maintain the current task index and the number of tasks assigned to Machine A. 
  The number of tasks assigned to B is implicitly (index - countA). Recursively take the 
  maximum of taking A or taking B.
- Dry Run: For x=3, y=3, a=[1...], b=[5...], it explores AABB..., ABAB... branching recursively.
- Time Complexity: O(n * x) 
- Space Complexity: O(n * x) for the memoization table.
- Why better than previous method: N/A (Base approach).
- When to use: Only when n and x are very small (e.g., <= 1000). For constraints up to 10^5, 
  this results in Memory Limit Exceeded and Time Limit Exceeded.

Method 2: Greedy with Sorting (Optimal)
- Intuition: If we shift a task from Machine B to Machine A, our profit changes by (a[i] - b[i]). 
  To maximize total profit, we should heavily prioritize assigning tasks to Machine A that have 
  the largest positive difference (a[i] - b[i]).
- Approach: 
  1. Calculate the difference (a[i] - b[i]) for all tasks.
  2. Sort the tasks in descending order based on this difference.
  3. The optimal solution will always involve giving the first 'k' tasks (a prefix) to Machine A, 
     and the remaining 'n - k' tasks to Machine B.
  4. The valid range for 'k' is determined by capacities: k >= max(0, n - y) and k <= min(n, x).
  5. Calculate the profit for the minimum valid 'k'. Then, iterate 'k' up to its maximum limit, 
     adding the pre-calculated difference at each step to find the absolute maximum profit.
- Dry Run: 
  x=3, y=3, a=[1,2,3,4,5], b=[5,4,3,2,1]. n = 5.
  Differences (a-b): [-4, -2, 0, 2, 4].
  Sorted diffs descending: [4, 2, 0, -2, -4]. (Correspond to tasks 4, 3, 2, 1, 0)
  Valid k range: max(0, 5-3) to min(5, 3) -> 2 to 3.
  k = 2: Machine A gets first 2 (profits 5+4=9), Machine B gets rest (profits 3+4+5=12). Total = 21.
  k = 3: Machine A gets first 3 (profits 5+4+3=12), Machine B gets rest (profits 4+5=9). Total = 21.
  Max profit = 21.
- Time Complexity: O(N log N) dominated by the sorting step.
- Space Complexity: O(N) to store the differences and original profits alongside each other.
- Why better than previous method: Avoids exponential recursion and heavy 2D array memory allocations, 
  easily handling N = 10^5.
- When to use: Always for this problem due to constraints.

Comparison Table:
Method         | TC         | SC         | Best Use Case
-------------------------------------------------------------------------
1. DP          | O(n * x)   | O(n * x)   | Small inputs, verifying logic
2. Greedy      | O(n log n) | O(n)       | Large inputs (production/competitive)

Final Recommended Solution: Greedy with Sorting
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

class Solution {
public:
    int maxProfit(int x, int y, vector<int>& a, vector<int>& b) {
        int n = a.size();
        
        // Store as {difference, profit_A, profit_B}
        // difference = a[i] - b[i]
        vector<tuple<int, int, int>> tasks(n);
        for(int i = 0; i < n; i++) {
            tasks[i] = {a[i] - b[i], a[i], b[i]};
        }
        
        // Sort descending by (a[i] - b[i])
        // This ensures tasks most profitable for Machine A relative to B come first
        sort(tasks.rbegin(), tasks.rend());
        
        // Determine the valid range of 'k' (tasks assigned to Machine A)
        // Machine B can take at most 'y' tasks, so A must take at least n - y
        int min_k = max(0, n - y);
        // Machine A can take at most 'x' tasks
        int max_k = min(n, x);
        
        // Compute base profit for k = min_k
        long long current_profit = 0;
        
        // First min_k tasks go to Machine A
        for(int i = 0; i < min_k; i++) {
            current_profit += get<1>(tasks[i]); 
        }
        // Remaining tasks go to Machine B
        for(int i = min_k; i < n; i++) {
            current_profit += get<2>(tasks[i]); 
        }
        
        long long max_total_profit = current_profit;
        
        // Try increasing 'k' (shifting tasks from B to A) to see if profit increases
        for(int k = min_k + 1; k <= max_k; k++) {
            // Shifting the (k-1)th task from B to A adds a[k-1] and subtracts b[k-1]
            // This net change is exactly the difference stored in get<0>
            current_profit += get<0>(tasks[k - 1]);
            max_total_profit = max(max_total_profit, current_profit);
        }
        
        return static_cast<int>(max_total_profit);
    }
};

// Driver Code for Local Run
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution sol;
    
    // Test Case 1
    int x1 = 3, y1 = 3;
    vector<int> a1 = {1, 2, 3, 4, 5};
    vector<int> b1 = {5, 4, 3, 2, 1};
    cout << "Test Case 1 Output: " << sol.maxProfit(x1, y1, a1, b1) << "\n";
    // Expected: 21
    
    // Test Case 2
    int x2 = 4, y2 = 4;
    vector<int> a2 = {1, 4, 3, 2, 7, 5, 9, 6};
    vector<int> b2 = {1, 2, 3, 6, 5, 4, 9, 8};
    cout << "Test Case 2 Output: " << sol.maxProfit(x2, y2, a2, b2) << "\n";
    // Expected: 43
    
    // Test Case 3
    int x3 = 3, y3 = 4;
    vector<int> a3 = {8, 7, 15, 19, 16, 16, 18};
    vector<int> b3 = {1, 7, 15, 11, 12, 31, 9};
    cout << "Test Case 3 Output: " << sol.maxProfit(x3, y3, a3, b3) << "\n";
    // Expected: 110

    return 0;
}
