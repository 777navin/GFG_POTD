/*
Date: 17-06-2026
Problem Name: Cut rope to maximise product
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Math, Dynamic Programming, Greedy

Problem Summary:
Given a rope of length n meters, cut it into multiple smaller ropes such that the product of their lengths is maximized. 
At least one cut is mandatory.

Methods to Solve:
1. Recursive Approach (Brute Force)
2. Dynamic Programming (Top-Down / Memoization)
3. Dynamic Programming (Bottom-Up)
4. Greedy Approach (Optimal)

For each method:
- Greedy/Math Intuition: 
  To maximize the product, we want to break the rope into pieces of length 3 as much as possible. 
  - If n % 3 == 0, max product is 3^(n/3).
  - If n % 3 == 1, we replace a 3 and 1 with two 2s (since 2*2 > 3*1), resulting in 3^((n/3)-1) * 4.
  - If n % 3 == 2, max product is 3^(n/3) * 2.

Comparison Table:
Method             | TC      | SC      | Best Use Case
-------------------|---------|---------|-------------------------
Brute Force        | O(2^n)  | O(n)    | Not recommended
DP (Memo/Tab)      | O(n^2)  | O(n)    | General understanding
Greedy (Math)      | O(1)    | O(1)    | Optimal, production ready

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class Solution {
public:
    /**
     * Optimal Approach: Mathematical/Greedy
     * Since we need at least one cut, we handle small n as base cases.
     * For n > 4, we repeatedly take out 3s.
     */
    long long maxProduct(int n) {
        // Base cases as per problem constraints and requirement of at least 1 cut
        if (n == 2) return 1; // 1*1
        if (n == 3) return 2; // 1*2
        
        long long product = 1;
        
        // Strategy: Break into as many 3s as possible
        while (n > 4) {
            product *= 3;
            n -= 3;
        }
        
        // Multiply by the remaining part (2 or 4)
        return product * n;
    }
};

// Driver code to match GFG expectations
int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    Solution sol;
    int n;
    
    // Example test case
    n = 5;
    std::cout << "Max product for " << n << " is: " << sol.maxProduct(n) << std::endl;

    n = 10;
    std::cout << "Max product for " << n << " is: " << sol.maxProduct(n) << std::endl;

    return 0;
}
