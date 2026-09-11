/*
=========================================================
Date        : 11-09-2026
Problem Name: Values with Equal Array Remainders
Platform    : GeeksforGeeks (GFG)
Difficulty  : Easy
Tags        : Arrays, Mathematics

Problem Summary:
Given an integer array arr[], count the number of positive 
integers k such that all elements leave the same remainder 
when divided by k. If there are infinitely many such values 
of k, return -1.

Key Observation:
If arr[i] % k == arr[j] % k, then k must divide |arr[i] - arr[j]|. 
Hence, k must be a divisor of the greatest common divisor (GCD) 
of all differences |arr[i] - arr[0]|.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: Brute Force
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Iterate through all possible values of k up to max(arr) and 
  verify if all elements leave the identical remainder.
• Approach:
  - Check if all elements are already equal (infinite answers -> return -1).
  - Loop k from 1 to max(arr) and check if arr[i] % k == arr[0] % k for all i.
• Why it Works:
  Directly simulates the problem condition for every possible candidate k.
• Time Complexity (TC): O(max(arr) * n)
• Space Complexity (SC): O(1)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 2: Optimized (GCD of Differences & Divisor Counting)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Two numbers have the same remainder modulo k if and only if 
  their difference is a multiple of k. Extending this to the entire 
  array, k must divide the GCD of differences between every element 
  and arr[0].
• Approach:
  - Compute g = gcd(|arr[i] - arr[0]|) for all 1 <= i < n.
  - If g == 0, all elements are identical, so return -1.
  - Otherwise, count all positive divisors of g in O(sqrt(g)) time.
• Why it Works:
  Any integer k satisfies the condition if and only if k divides g. 
  Thus, the number of valid k is precisely the number of divisors of g.
• Time Complexity (TC): O(n + sqrt(g))
• Space Complexity (SC): O(1)
*/

/*
=========================================================
FINAL APPROACH:
The GCD approach reduces an exhaustive check of all potential moduli 
to a single GCD calculation across array differences followed by 
O(sqrt(g)) divisor enumeration. It operates strictly within O(n + sqrt(g)) 
time and O(1) auxiliary space, effortlessly handling constraints up to 10^5.
=========================================================
*/

#include <vector>
#include <numeric>
#include <cmath>

class Solution {
  public:
    int sameMod(std::vector<int> &arr) {
        int n = arr.size();
        if (n <= 1) {
            return -1;
        }

        int g = 0;
        for (int i = 1; i < n; ++i) {
            g = std::gcd(g, std::abs(arr[i] - arr[0]));
        }

        // If g == 0, all elements are identical, yielding infinitely many k
        if (g == 0) {
            return -1;
        }

        // Count the number of positive divisors of g
        int divisorCount = 0;
        for (int d = 1; 1LL * d * d <= g; ++d) {
            if (g % d == 0) {
                divisorCount++;
                if (d != g / d) {
                    divisorCount++;
                }
            }
        }

        return divisorCount;
    }
};
