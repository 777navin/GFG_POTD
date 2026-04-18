/**
 * Question Brief:
 * - Given an array arr[] of 0s and 1s.
 * - A flip operation involves changing all 0s to 1s and 1s to 0s in a contiguous subarray.
 * - Goal: Find the maximum number of 1s possible after performing at most one flip.
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxOnes(vector<int>& arr) {
        int n = arr.size();
        int totalOnes = 0;
        int currentGain = 0;
        int maxGain = 0;

        for (int i = 0; i < n; i++) {
            // Count original 1s to add back later
            if (arr[i] == 1) {
                totalOnes++;
            }

            /* Kadane's logic:
               - If we flip a '0', we gain a '1' (+1 gain)
               - If we flip a '1', we lose a '1' (-1 gain)
            */
            int val = (arr[i] == 0) ? 1 : -1;

            currentGain += val;
            
            // Update maxGain found so far
            if (currentGain > maxGain) {
                maxGain = currentGain;
            }

            // If current gain becomes negative, reset it (Kadane's)
            if (currentGain < 0) {
                currentGain = 0;
            }
        }

        // Final answer = original 1s + best gain from flipping
        return totalOnes + maxGain;
    }
};

/**
 * Intuition:
 * The problem asks for the maximum 1s after one flip. Instead of brute-forcing 
 * every subarray, we treat this as a Maximum Subarray Sum problem. 
 * By assigning 0 -> +1 and 1 -> -1, the subarray with the maximum sum 
 * represents the range where flipping provides the most benefit.
 *
 * Time Complexity: O(n)
 * - We traverse the array exactly once.
 *
 * Space Complexity: O(1)
 * - We only use a few variables for tracking gains and counts.
 */
