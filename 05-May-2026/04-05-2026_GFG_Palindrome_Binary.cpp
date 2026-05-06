/*
Date: 04-05-2026
Problem Name: Palindrome Binary
Platform: GeeksforGeeks
Difficulty: Easy
Tags: Bit Magic, Strings, Two Pointers

Problem Summary:
Given an integer n, determine whether its binary representation forms a palindrome. Return true if the binary representation reads the same forward and backward; otherwise, return false.

Methods to Solve:
1. Brute Force (String/Vector Conversion)
2. Optimal Approach (Bit Extraction using Two Pointers)

=========================================================
Method 1: Brute Force (String/Vector Conversion)
=========================================================
- Intuition: 
  The simplest way to check for a palindrome is to convert the binary representation into a string or vector, then use the classic two-pointer approach to verify if it reads the same forward and backward.
- Approach:
  1. Continuously modulo the number by 2 to extract the Least Significant Bit (LSB).
  2. Push the bit to a vector (this essentially builds the binary string in reverse, but a palindrome is identical reversed, so order doesn't disrupt the check).
  3. Divide the number by 2 to shift right.
  4. Once the number becomes 0, use two pointers (left and right) to check if the vector is a palindrome.
- Dry Run (small example): n = 17 (10001 in binary)
  - 17 % 2 = 1 (push 1), n = 8
  - 8 % 2 = 0 (push 0), n = 4
  - 4 % 2 = 0 (push 0), n = 2
  - 2 % 2 = 0 (push 0), n = 1
  - 1 % 2 = 1 (push 1), n = 0
  - Vector: [1, 0, 0, 0, 1]
  - left = 0, right = 4 -> match (1 == 1)
  - left = 1, right = 3 -> match (0 == 0)
  - Palindrome confirmed.
- Time Complexity: O(log n) - Processing each bit of n.
- Space Complexity: O(log n) - To store the binary representation in a vector.
- Why better than previous method: N/A (Baseline approach).
- When to use: When space complexity is not a strict constraint and code simplicity is prioritized.

=========================================================
Method 2: Optimal Approach (Bit Extraction using Two Pointers)
=========================================================
- Intuition: 
  Instead of consuming extra memory to store the bits, we can directly compare the i-th bit from the left and the i-th bit from the right using bitwise operations, allowing us to achieve O(1) auxiliary space.
- Approach:
  1. Find the length of the binary representation (total number of bits) by shifting right until the temp variable is 0.
  2. Set two pointers: `left` at (length - 1) and `right` at 0.
  3. While `left` > `right`, extract the bit at the `left` position and the `right` position.
     - A bit at position `k` can be extracted using: `(n >> k) & 1`.
  4. If the extracted bits differ, return false immediately.
  5. Decrement `left` and increment `right`.
  6. Return true if the loop completes without any mismatches.
- Dry Run (small example): n = 16 (10000 in binary)
  - Length of binary representation for 16 is 5.
  - left = 4, right = 0
  - Bit at pos 4: (16 >> 4) & 1 = 1
  - Bit at pos 0: (16 >> 0) & 1 = 0
  - Bits differ (1 != 0) -> Return false.
- Time Complexity: O(log n) - We check each bit pair once.
- Space Complexity: O(1) - No extra space utilized; only integer variables.
- Why better than previous method: Eliminates the O(log n) auxiliary space requirement.
- When to use: Best for memory-constrained environments, competitive programming, and demonstrating deep bit-manipulation knowledge in interviews.

Comparison Table:
Method         | TC       | SC       | Best Use Case
---------------------------------------------------------
Brute Force    | O(log n) | O(log n) | Simple logic, quick implementation
Optimal        | O(log n) | O(1)     | Optimized space, technical interviews

Final Recommended Solution: Optimal Approach (Method 2)
*/

#include <iostream>
#include <vector>

using namespace std;

// GeeksforGeeks Expected Format wrapped in standalone script
class Solution {
public:
    // Method 1: Brute Force Approach (Commented out for reference)
    /*
    bool isBinaryPalindromeBruteForce(int n) {
        vector<int> binary;
        while (n > 0) {
            binary.push_back(n % 2);
            n /= 2;
        }
        
        int left = 0, right = binary.size() - 1;
        while (left < right) {
            if (binary[left] != binary[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
    */

    // Method 2: Optimal Approach
    bool isBinaryPalindrome(int n) {
        if (n == 0) return true;

        // Step 1: Find the total number of bits in n
        int numBits = 0;
        int temp = n;
        while (temp > 0) {
            numBits++;
            temp >>= 1;
        }
        
        // Step 2: Use two pointers to compare bits from both ends
        int left = numBits - 1;
        int right = 0;
        
        while (left > right) {
            // Extract the 'left' bit and 'right' bit
            int leftBit = (n >> left) & 1;
            int rightBit = (n >> right) & 1;
            
            // If bits do not match, it is not a palindrome
            if (leftBit != rightBit) {
                return false;
            }
            left--;
            right++;
        }
        
        return true;
    }
};

// Driver Code for Full Standalone Execution
int main() {
    // Fast I/O for competitive programming standards
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution obj;
    
    // Test Case 1
    int n1 = 17;
    cout << "Input: n = " << n1 << "\n";
    cout << "Output: " << (obj.isBinaryPalindrome(n1) ? "true" : "false") << "\n";
    cout << "Expected: true\n\n";

    // Test Case 2
    int n2 = 16;
    cout << "Input: n = " << n2 << "\n";
    cout << "Output: " << (obj.isBinaryPalindrome(n2) ? "true" : "false") << "\n";
    cout << "Expected: false\n";

    return 0;
}
