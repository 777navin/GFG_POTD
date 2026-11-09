/*
=========================================================
Date        : 09-11-2026
Problem Name: Count Group Occurrences
Platform    : GeeksforGeeks
Difficulty  : Easy
Tags        : Strings, Frequency Counting

Problem Summary:
Count distinct characters that appear in exactly k groups.
A group consists of consecutive occurrences of the same character.

Key Observation:
A new group starts when the current character differs
from the previous character.
=========================================================

APPROACH 1: Brute Force

- Intuition:
  Count consecutive groups for every distinct character.

- Approach:
  Traverse the string and separately count groups
  for each character.

- Why it Works:
  Every consecutive block contributes exactly one group.

- TC: O(26 * n)
- SC: O(1)


APPROACH 2: Optimized (Single Traversal)

- Intuition:
  A new group starts whenever s[i] != s[i-1].

- Approach:
  1. Create an array of size 26 initialized with zero.
  2. Traverse the string.
  3. Increment the character's count when i == 0
     or s[i] != s[i-1].
  4. Count characters whose group frequency equals k.

- Why it Works:
  Each character's group is counted exactly once.

- TC: O(n + 26) = O(n)
- SC: O(26) = O(1)


FINAL APPROACH:
The optimized single-traversal approach is chosen.
It counts all groups in one pass and uses a fixed-size
frequency array, making it efficient in both time and space.
=========================================================
*/

class Solution {
public:
    int getCount(string &s, int k) {

        int cnt[26] = {0};
        int n = s.size();

        // Count consecutive groups for each character.
        for (int i = 0; i < n; i++) {

            if (i == 0 || s[i] != s[i - 1]) {
                cnt[s[i] - 'a']++;
            }
        }

        // Count characters appearing in exactly k groups.
        int ans = 0;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] == k) {
                ans++;
            }
        }

        return ans;
    }
};
