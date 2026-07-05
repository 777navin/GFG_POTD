/*
Date        : 05-07-2026
Problem Name: Max Gap Between Two Same
Platform    : GeeksforGeeks (GFG)
Difficulty  : Easy
Tags        : String, Hashing, Two Pointer

Problem Summary
Given a string s, find the maximum number of characters between any two identical characters. If no character repeats, return -1.

Constraints
1 <= |s| <= 10^5

Key Observation We need to track the first occurrence of each character. For any subsequent occurrence of the same character, the number of characters between them is (current_index - first_occurrence_index - 1). We maintain the maximum of these values.
*/

/*
APPROACHES
Hashing (Optimal)

Intuition: Store the index of the first occurrence of each character in an array of size 26.

Idea: Iterate through the string. If a character is seen for the first time, store its index. If seen again, calculate the gap and update the maximum.

Time Complexity: O(N), where N is the length of the string.

Space Complexity: O(1), as the hash array size is fixed (26).
*/

/*
COMPARISON TABLE
Method      | Idea        | Time | Space | Difficulty | Recommended
Hashing     | Fixed Array | O(N) | O(1)  | Easy       | Yes
*/

/*
FINAL RECOMMENDED APPROACH
The Hashing approach is optimal because it processes the string in a single pass and uses constant extra space, handling the constraints (10^5) efficiently.
*/

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
int maxCharGap(string &s) {
// Array to store the first occurrence of each of the 26 lowercase letters
// Initialize with -1 to indicate character has not been seen yet
vector<int> firstOccurrence(26, -1);
int maxGap = -1;

    for (int i = 0; i < s.length(); ++i) {
        int charIdx = s[i] - 'a';
        
        if (firstOccurrence[charIdx] == -1) {
            // First time seeing this character
            firstOccurrence[charIdx] = i;
        } else {
            // Character seen before, calculate gap
            int currentGap = i - firstOccurrence[charIdx] - 1;
            maxGap = max(maxGap, currentGap);
        }
    }

    return maxGap;
}
};
