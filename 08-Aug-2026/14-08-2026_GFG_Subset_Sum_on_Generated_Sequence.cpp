/*
=========================================================
Date        : 14-08-2026
Problem Name: Subset Sum on Generated Sequence (Tricky Subset Problem)
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Greedy, Array, Prefix Sum

Problem Summary:
- An initial number S is written on paper.
- Each child in sequence adds the sum of all existing numbers on the paper plus arr[i] to the paper.
- Determine if a target sum X can be formed using a subset of the generated numbers.

Key Observation:
- Since each newly generated number is strictly greater than the sum of all preceding numbers, the sequence grows exponentially (super-increasing sequence).
- This property guarantees that a greedy approach from the largest to smallest element yields the optimal subset sum.
=========================================================
*/

/*
=========================================================
APPROACH 1: Exponential Generation + Greedy Selection
=========================================================

• Intuition:
  - Generate the sequence by maintaining a running prefix sum of numbers on the paper.
  - Since sequence elements grow faster than powers of 2, if a number is <= X, it must be included greedily.

• Approach:
  - Start with `seq = [S]` and running sum `curr_sum = S`.
  - Iterate through `arr`, at each step create `val = curr_sum + arr[i]`.
  - If `val > X`, we can stop generating further elements as all subsequent elements will also exceed X.
  - Traverse the generated sequence backwards; if `seq[i] <= X`, subtract `seq[i]` from `X`.
  - If `X` reaches 0, return true; otherwise, return false.

• Why it Works:
  - The sequence is super-increasing ($seq[k] > \sum_{j=0}^{k-1} seq[j]$).
  - In a super-increasing sequence, the subset sum problem can be solved in linear time using a standard greedy algorithm.

• Time Complexity (TC):
  - $O(N)$ to generate the sequence and $O(N)$ for the reverse traversal.
  - Total TC: $O(\min(N, \log X))$ due to exponential growth.

• Space Complexity (SC):
  - $O(\min(N, \log X))$ to store the generated sequence numbers up to $X$.
=========================================================
*/

/*
=========================================================
FINAL APPROACH:
- We use the Greedy approach on the generated super-increasing sequence.
- It is chosen because standard dynamic programming subset sum is $O(X)$, which is too slow for $X \le 10^9$.
- The super-increasing nature reduces subset sum to a fast $O(\log X)$ greedy solution.
=========================================================
*/

#include <vector>

class Solution {
public:
    bool isSubsetSumPossible(std::vector<long long>& arr, long long s, long long x) {
        std::vector<long long> seq;
        seq.push_back(s);
        
        long long current_sum = s;
        
        // Generate sequence elements while they do not exceed x
        for (int i = 0; i < (int)arr.size(); ++i) {
            long long next_val = current_sum + arr[i];
            if (next_val > x) {
                seq.push_back(next_val);
                break;
            }
            seq.push_back(next_val);
            current_sum += next_val;
        }
        
        // Greedily pick from the largest to smallest element
        for (int i = (int)seq.size() - 1; i >= 0; --i) {
            if (x >= seq[i]) {
                x -= seq[i];
            }
        }
        
        return x == 0;
    }
};
