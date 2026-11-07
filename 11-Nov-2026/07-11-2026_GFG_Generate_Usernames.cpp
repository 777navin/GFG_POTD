/*
=========================================================
Date        : 07-11-2026
Problem Name: Generate Usernames
Platform    : GeeksforGeeks
Difficulty  : Easy
Tags        : Strings, Hashing, Unordered Set

Problem Summary:
Generate unique usernames while maintaining the original
username for its first occurrence.
For duplicates, append the smallest available positive
integer suffix without conflicting with reserved names.

Key Observation:
All original usernames are reserved initially.
Generated usernames must not conflict with reserved
or previously assigned usernames.
=========================================================

APPROACH 1: BRUTE FORCE

- Intuition:
  Check every possible suffix starting from 1.

- Approach:
  For each duplicate, generate name1, name2, name3, etc.
  Check whether the candidate is already reserved or used.

- Why it Works:
  The first available candidate is the smallest valid suffix.

- TC: O(n * k * m)
- SC: O(n * m)

APPROACH 2: OPTIMIZED HASHING

- Intuition:
  Use hash sets for quick username lookup.

- Approach:
  1. Store all original usernames in a reserved set.
  2. Maintain another set for assigned usernames.
  3. Keep the first occurrence unchanged.
  4. For duplicates, find the smallest valid suffix.
  5. Maintain the next suffix for each username to avoid
     checking previously tested suffixes repeatedly.

- Why it Works:
  Reserved prevents conflicts with future original names,
  while assigned prevents conflicts with generated names.
  Processing from left to right preserves the first occurrence.

- TC: O(n * k * m) worst case, with efficient hashing.
- SC: O(n * m)

FINAL APPROACH: OPTIMIZED HASHING

- Chosen because unordered_set provides efficient lookups.
- Maintaining nextSuffix avoids restarting suffix searches.
- Separate reserved and assigned sets handle future original
  usernames and previously generated usernames correctly.
- This is efficient for the given constraints.

=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> generateUsernames(vector<string> arr) {

        // Store all initially reserved usernames.
        unordered_set<string> reserved(arr.begin(), arr.end());

        // Store usernames already assigned.
        unordered_set<string> assigned;

        // Store the next suffix to check for each username.
        unordered_map<string, int> nextSuffix;

        vector<string> ans;

        for (const string& name : arr) {

            // First occurrence retains its original username.
            if (assigned.insert(name).second) {
                ans.push_back(name);
                continue;
            }

            // Generate the smallest available username.
            int& suffix = nextSuffix[name];

            if (suffix == 0) {
                suffix = 1;
            }

            string candidate;

            while (true) {

                candidate = name + to_string(suffix);

                if (!reserved.count(candidate) &&
                    !assigned.count(candidate)) {
                    break;
                }

                suffix++;
            }

            // Assign and reserve the generated username.
            assigned.insert(candidate);
            ans.push_back(candidate);

            suffix++;
        }

        return ans;
    }
};

/*
=========================================================
Filename:
07-11-2026_GFG_Generate_Usernames.cpp
=========================================================
*/
