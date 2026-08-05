/*
=========================================================
Date        : 05-08-2026
Problem Name: Subarrays with Sum in Range
Platform    : GeeksforGeeks
Difficulty  : Hard
Tags        : Array, Sliding Window, Two Pointers

Problem Summary:
Given an array of positive integers and a range [l, r], find
the total number of contiguous subarrays whose sum falls
exactly within this inclusive range.

Key Observation:
The number of subarrays with a sum in the range [l, r] is equal
to (Subarrays with sum <= r) minus (Subarrays with sum <= l - 1).
Since all elements are positive, the sum is monotonically increasing,
allowing us to use the Sliding Window technique to count them efficiently.
=========================================================
*/

/*
=========================================================
APPROACH EXPLANATION
=========================================================

1. Brute Force
• Intuition: Check every possible subarray and calculate its sum.
• Approach: Use two nested loops to generate all subarrays, calculating the sum on the fly, and count those within [l, r].
• Why it Works: It exhaustively searches the entire solution space.
• Time Complexity (TC): O(N^2)
• Space Complexity (SC): O(1)

2. Most Optimal (Sliding Window)
• Intuition: Instead of calculating bounds directly, compute for 'at most R' and subtract 'at most L-1'.
• Approach: Maintain a window [left, right]. If the sum exceeds K, shrink the window from the left until sum <= K. Count valid subarrays by adding (right - left + 1).
• Why it Works: Since all array elements are positive, expanding the window increases the sum and shrinking it decreases the sum (monotonic property).
• Time Complexity (TC): O(N) because each element is added and removed at most once.
• Space Complexity (SC): O(1) as we only use a few tracking variables.

=========================================================
FINAL APPROACH
=========================================================
• The Most Optimal (Sliding Window) approach is chosen.
• It is strictly better than the Brute Force method because it reduces the time complexity from O(N^2) to O(N).
• This ensures the solution will comfortably pass within the strict time limits for array sizes up to 10^5.
*/

#include <vector>
using namespace std;

class Solution {
private:
    // Helper function to count subarrays with sum at most 'k'
    long long countAtMost(vector<int>& arr, long long k) {
        if (k < 0) return 0;
        
        long long count = 0;
        long long currentSum = 0;
        int left = 0;
        
        for (int right = 0; right < arr.size(); right++) {
            currentSum += arr[right];
            
            // Shrink the window if the sum exceeds k
            while (currentSum > k && left <= right) {
                currentSum -= arr[left];
                left++;
            }
            
            // Add the number of valid subarrays ending at 'right'
            count += (right - left + 1);
        }
        
        return count;
    }

public:
    // Using 'long long' as the return type since total valid subarrays can exceed 32-bit int limit for large N
    long long countSubarray(vector<int>& arr, int l, int r) {
        // Count subarrays in range [l, r] = (Count <= r) - (Count <= l - 1)
        return countAtMost(arr, r) - countAtMost(arr, l - 1);
    }
};
