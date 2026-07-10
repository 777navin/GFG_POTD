/*
=========================================================
Date        : 10-07-2026
Problem Name: Ways to Express as Sum of Consecutives
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Math, Number Theory, Logic

Problem Summary:
Given a number n, find the number of ways to represent 
it as a sum of 2 or more consecutive natural numbers.

Key Observation:
A sequence of k consecutive numbers starting from 'a' 
sums to k * a + k * (k - 1) / 2. We can use this to find 
valid lengths 'k'.
=========================================================
*/

/*
=========================================================
APPROACH 1: Brute Force (Iterating all possible starting points)
=========================================================
* Intuition : Try every number as a starting point and keep adding consecutive numbers until it matches or exceeds n.
* Approach  : Use nested loops. Outer loop picks starting number 'i' from 1 to n/2. Inner loop adds consecutive numbers.
* Why Works : Exhaustively searches all possible consecutive sequences.
* TC        : O(N^2) in worst case, will give Time Limit Exceeded (TLE) for N = 10^8.
* SC        : O(1) auxiliary space.

=========================================================
APPROACH 2: Mathematical / Arithmetic Progression (Most Optimal)
=========================================================
* Intuition : Use the sum formula of an Arithmetic Progression (AP). 
              Sum = a + (a+1) + ... + (a+k-1) = k*a + [k*(k-1)] / 2.
* Approach  : 
    - Let sum_k = k * (k - 1) / 2.
    - So, n = k * a + sum_k.
    - Rearranging: a = (n - sum_k) / k.
    - Iterate through possible lengths k starting from 2.
    - If (n - sum_k) is positive and perfectly divisible by k, then 'a' is a valid starting natural number.
    - Stop when (n - sum_k) <= 0.
* Why Works : By iterating over the length 'k', we skip redundant additions. We only mathematically check if a valid starting point 'a' exists for length 'k'.
* TC        : O(sqrt(N)) because k(k-1)/2 < n roughly translates to k^2 < 2n.
* SC        : O(1) auxiliary space.

=========================================================
FINAL APPROACH EXPLANATION
=========================================================
Approach 2 (Math/AP) is chosen because it optimizes the time 
complexity from O(N^2) to O(sqrt(N)). This is absolutely necessary 
to pass the given constraint of N <= 10^8 within the time limit.
=========================================================
*/

class Solution {
public:
    int getCount(int n) {
        int ways = 0;
        
        // k represents the number of consecutive terms
        // We need 2 or more consecutive natural numbers, so k starts at 2
        for (long long k = 2; ; k++) {
            
            // Calculate k * (k - 1) / 2
            long long sum_k_minus_1 = (k * (k - 1)) / 2;
            
            // numerator is n - (k * (k - 1) / 2)
            long long numerator = n - sum_k_minus_1;
            
            // If the numerator becomes <= 0, 'a' can no longer be a natural number (>= 1)
            if (numerator <= 0) {
                break;
            }
            
            // If numerator is perfectly divisible by k, a valid starting natural number 'a' exists
            if (numerator % k == 0) {
                ways++;
            }
        }
        
        return ways;
    }
};
