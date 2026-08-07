/*
=========================================================
Date        : 07-08-2026
Problem Name: Friends Pairing Problem
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Dynamic Programming, Combinatorics

Problem Summary:
Given n friends, each can either remain single or pair up with 
exactly one other friend. Find the total number of ways this can 
be done. 

Key Observation:
For the n-th friend, there are two choices: 
1. Remain single (leaving n-1 friends to pair).
2. Pair up with any of the remaining (n-1) friends (leaving n-2 friends to pair).
=========================================================

=========================================================
APPROACH EXPLANATION
=========================================================

1. Recursion with Memoization (Better)
   • Intuition: The problem breaks down into overlapping subproblems based on the choices of the n-th person.
   • Approach: Use a recursive function f(n) = f(n-1) + (n-1) * f(n-2) and cache the results in an array.
   • Why it Works: Caching prevents recalculation of the same states, pruning the recursive tree.
   • Time Complexity (TC): O(N)
   • Space Complexity (SC): O(N) for memoization array + O(N) auxiliary stack space.

2. Space Optimized Tabulation (Most Optimal)
   • Intuition: The result for 'n' only depends on the results of 'n-1' and 'n-2'.
   • Approach: Use three variables to keep track of the previous two states iteratively instead of an entire array.
   • Why it Works: Eliminates both the recursion stack and the DP array, computing the sequence bottom-up.
   • Time Complexity (TC): O(N)
   • Space Complexity (SC): O(1)

=========================================================
FINAL APPROACH
=========================================================
The Space Optimized Tabulation approach is chosen. 
It is better because it reduces the space complexity from O(N) 
to O(1) by discarding historical data that is no longer needed, 
while maintaining the optimal O(N) time complexity.
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int countFriendsPairings(int n) {
        // Base cases
        if (n <= 2) return n;
        
        long long prev2 = 1; // f(1)
        long long prev1 = 2; // f(2)
        long long curr = 0;
        
        // Modulo is standard for this DP problem on GFG to prevent overflow 
        long long MOD = 1e9 + 7;
        
        for (int i = 3; i <= n; i++) {
            // Formula: f(i) = f(i-1) + (i-1) * f(i-2)
            curr = (prev1 + (i - 1) * prev2) % MOD;
            
            // Shift variables for the next iteration
            prev2 = prev1;
            prev1 = curr;
        }
        
        return curr;
    }
};

// Driver code to ensure the file is fully standalone and runnable
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            Solution ob;
            cout << ob.countFriendsPairings(n) << "\n";
        }
    } else {
        // Fallback local testing if no standard input is provided
        Solution ob;
        cout << ob.countFriendsPairings(3) << "\n"; // Expected: 4
        cout << ob.countFriendsPairings(2) << "\n"; // Expected: 2
    }
    
    return 0;
}
