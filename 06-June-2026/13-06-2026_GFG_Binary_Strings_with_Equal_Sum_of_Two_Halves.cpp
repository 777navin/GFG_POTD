// 13-06-2026_GFG_Binary_Strings_with_Equal_Sum_of_Two_Halves.cpp

/*
Date: 13-06-2026
Problem Name: Binary Strings with Equal Sum of Two Halves
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Combinatorics, Math, Dynamic Programming

Problem Summary:
Given a number n, find the count of all binary sequences of length 2n such that 
the sum of the first n bits is equal to the sum of the last n bits. 
Return the answer modulo 10^9 + 7.

Methods to Solve:
1. Combinatorial Approach (Optimal)

Method 1: Combinatorial Approach
- Intuition: 
  Let the sum of the first n bits be 'k' and the sum of the last n bits be 'k'.
  The number of ways to choose k bits to be 1 in the first half is given by nCk.
  Similarly, the number of ways to choose k bits to be 1 in the second half is nCk.
  Since the choices are independent, for a fixed sum k, there are (nCk) * (nCk) = (nCk)^2 ways.
  We need to sum this for all possible values of k from 0 to n:
  Result = sum_{k=0}^{n} (nCk)^2.
  By Vandermonde's Identity, sum_{k=0}^{n} (nCk)^2 = (2n)Cn.

- Approach: 
  Calculate (2n)Cn modulo 10^9 + 7.
  (2n)Cn = (2n)! / (n! * n!).
  We can compute this using modular inverse for division under modulo.

- Dry Run: 
  n = 2: (2*2)C2 = 4C2 = 6. Matches example.
  n = 1: (2*1)C1 = 2C1 = 2. Matches example.

- Time Complexity: O(n) or O(log MOD) depending on power implementation.
- Space Complexity: O(1) (excluding precomputed factorials if used).

Comparison Table:
Method | TC | SC | Best Use Case
Combinatorial | O(n) | O(1) | All cases (Optimal)

Final Recommended Solution: Combinatorial Method using (2n)Cn.
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    long long power(long long base, long long exp) {
        long long res = 1;
        base %= 1000000007;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % 1000000007;
            base = (base * base) % 1000000007;
            exp /= 2;
        }
        return res;
    }

    long long modInverse(long long n) {
        return power(n, 1000000007 - 2);
    }

public:
    int computeValue(int n) {
        if (n == 0) return 1;
        
        int N = 2 * n;
        vector<long long> fact(N + 1);
        fact[0] = 1;
        for (int i = 1; i <= N; i++) {
            fact[i] = (fact[i - 1] * i) % 1000000007;
        }

        // Formula: (2n)! / (n! * n!)
        long long num = fact[N];
        long long den = (fact[n] * fact[n]) % 1000000007;
        
        return (num * modInverse(den)) % 1000000007;
    }
};

// Driver Code
int main() {
    int n;
    if (!(cin >> n)) return 0;
    Solution sol;
    cout << sol.computeValue(n) << endl;
    return 0;
}
