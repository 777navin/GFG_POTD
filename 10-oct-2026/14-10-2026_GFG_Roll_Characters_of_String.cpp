/*
=========================================================
Date        : 14-10-2026
Problem Name: Roll Characters of String
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : String, Prefix Sum, Array

Problem Summary:
Given a string s and an array roll[], each roll[i] increments the first roll[i] characters of the string by 1. 
Return the final modified string after applying all roll operations.

Key Observation:
A prefix roll of length k affects all indices from 0 to k-1. We can use a difference array or frequency count to accumulate the number of rolls for each index efficiently.
=========================================================
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string findRollOut(string &s, vector<int>& roll) {
        /*
        Intuition:
        Instead of modifying the prefix for each query in O(N), which takes O(N * Q) time and leads to TLE, 
        we can count how many times each character position needs to be rolled using a frequency or difference array.

        Approach:
        1. Create a frequency/diff array `diff` of size s.size() + 1 initialized to 0.
        2. For each query `r` in `roll`, increment `diff[0]` by 1 and decrement `diff[r]` by 1.
        3. Compute the prefix sums of the `diff` array to get the total number of rolls applied to each character.
        4. Add the total roll count modulo 26 to each character of the string `s`.

        Why it Works:
        The difference array technique allows us to perform range increment updates in O(1) time per query and 
        compute the final accumulated increments in O(N) time.

        Time Complexity (TC): O(N + Q), where N is the string length and Q is the number of roll operations.
        Space Complexity (SC): O(N) for the difference array.
        */
        
        int n = s.size();
        vector<int> diff(n + 1, 0);

        for (int r : roll) {
            diff[0]++;
            if (r < n) {
                diff[r]--;
            }
        }

        int currentRolls = 0;
        for (int i = 0; i < n; i++) {
            currentRolls += diff[i];
            int shifts = currentRolls % 26;
            s[i] = 'a' + (s[i] - 'a' + shifts) % 26;
        }

        return s;
    }
};

/*
Final Approach Chosen:
We use the difference array (prefix sum) technique because the constraints on s.size() and roll.size() can be up to 10^5. 
A naive simulation would take O(N * Q) time, whereas the prefix sum approach solves it in optimal O(N + Q) time.
*/
