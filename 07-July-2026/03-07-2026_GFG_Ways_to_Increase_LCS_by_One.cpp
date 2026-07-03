/*
=========================================================
Date        : 03-07-2026
Problem Name: Ways to Increase LCS by One
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Dynamic Programming, Longest Common Subsequence, Strings

Problem Summary:
Given two strings s1 and s2, find the number of ways to insert exactly one 
character into string s1 such that the length of their Longest Common Subsequence 
(LCS) increases by exactly 1. 

Constraints:
1 <= n1, n2 <= 100
s1 and s2 consist of lowercase English letters.

Key Observation:
Instead of recomputing the LCS for every possible insertion, we can precompute 
the prefix LCS and suffix LCS of the two strings. If we insert a character 'c' 
at index 'i' in s1, and it matches the character at index 'j' in s2, the new 
LCS formed will be: pref[i][j] + 1 + suff[i][j+1]. If this combination equals 
the original LCS + 1, it is a valid insertion.
=========================================================
*/
1. Brute ForceIntuition: The most straightforward approach is to try inserting every possible lowercase English letter ('a' to 'z') at every possible position in s1 (from index 0 to n1). For each newly formed string, we calculate the LCS with s2 and check if it increases by exactly 1.Idea: Iterate through all positions 0 to n1. Iterate through 'a' to 'z'. Construct a temporary string, run standard $O(n_1 \times n_2)$ LCS, and count successes.Approach:Calculate the initial LCS of s1 and s2.Loop i from 0 to n1.Loop ch from a to z.Form string temp by inserting ch at position i in s1.Find LCS of temp and s2. If it equals initial LCS + 1, increment the answer.Why it works: It exhaustively checks every possible valid insertion state.Time Complexity: $O(n_1 \cdot 26 \cdot (n_1 \cdot n_2))$ which is roughly $O(26 \cdot n_1^2 \cdot n_2)$. For $N=100$, operations $\approx 2.6 \times 10^7$.Space Complexity: $O(n_1 \cdot n_2)$ for the LCS table in each check.Advantages: Simple to implement and conceptually easy to understand.Disadvantages: Too slow. Will likely lead to a Time Limit Exceeded (TLE) error for larger constraints.When to use: During an interview to explain the basic thought process before optimizing.Why next approach is better: Recomputing the entire LCS for a 1-character difference is redundant. We can precompute prefix and suffix LCS arrays to answer queries in $O(1)$ time.2. Optimized Approach (Prefix & Suffix DP)Intuition: When we insert a character c at position i in s1, it divides s1 into a left prefix and a right suffix. If c matches a character at position j in s2, we can combine the maximum LCS of the prefixes (s1[0...i-1] and s2[0...j-1]) with the maximum LCS of the suffixes (s1[i...n1-1] and s2[j+1...n2-1]).Idea: Precompute two 2D DP arrays: pref[i][j] (LCS of prefixes) and suff[i][j] (LCS of suffixes). Then, for any insertion (i, c), check if there exists a position j in s2 such that s2[j] == c and pref[i][j] + suff[i][j+1] == original_LCS.Approach:Fill pref DP table of size (n1+1) x (n2+1) from left to right.Fill suff DP table of size (n1+1) x (n2+1) from right to left.The base LCS length L is pref[n1][n2].Iterate i from 0 to n1 (insertion point in s1).Iterate ch from 'a' to 'z' (character to insert).For a fixed i and ch, iterate j from 0 to n2-1. If s2[j] == ch and pref[i][j] + suff[i][j+1] == L, it means matching this character guarantees an LCS of L + 1. Break early and increment the answer.Dry Run:Let s1 = "abab", s2 = "abc". Initial LCS = 2.Insert 'c' at the very end (i=4). s2 has 'c' at j=2.pref[4][2] (LCS of "abab", "ab") = 2.suff[4][3] (LCS of "", "") = 0.pref[4][2] + suff[4][3] = 2, which equals our original LCS. Therefore, inserting 'c' here creates a match that increases the LCS to 3 (2 + 1 + 0). Valid configuration found.Why it works: By saving the states of the LCS from both directions, we can calculate the impact of a single character insertion in constant time relative to the DP table.Time Complexity: $O(n_1 \cdot n_2 + n_1 \cdot 26 \cdot n_2) \approx O(n_1 \cdot n_2)$. For $N=100$, operations $\approx 2.6 \times 10^5$, which is well within the 1-second limit.Space Complexity: $O(n_1 \cdot n_2)$ to store the pref and suff 2D vectors.Advantages: Highly optimized and avoids redundant LCS recalculations.Disadvantages: Requires $O(N^2)$ space, though acceptable for $N=100$.When to use: Whenever querying modifications of strings in DP problems.Comparison TableMethodIdeaTimeSpaceDifficultyRecommendedBrute ForceTry inserting all chars everywhere and recalculate LCS.$O(N^2 \cdot M \cdot 26)$$O(N \cdot M)$EasyNoPrefix/Suffix DPPrecompute LCS states from both ends, match in $O(N \cdot M)$.$O(N \cdot M \cdot 26)$$O(N \cdot M)$MediumYesFinal Recommended ApproachThe Prefix & Suffix DP (Optimized Approach) is the recommended solution. Re-evaluating the LCS from scratch for every single possible character insertion is incredibly wasteful. By precomputing the prefix and suffix LCS values, we can evaluate the outcome of an insertion simply by adding the left boundary score to the right boundary score in $O(1)$ lookup time, cleanly satisfying the expected time complexities on GeeksforGeeks.C++ Source CodeC++#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int waysToIncreaseLCSBy1(string &s1, string &s2) {
        int n1 = s1.length();
        int n2 = s2.length();

        // pref[i][j] stores the LCS of s1[0..i-1] and s2[0..j-1]
        vector<vector<int>> pref(n1 + 1, vector<int>(n2 + 1, 0));
        // suff[i][j] stores the LCS of s1[i..n1-1] and s2[j..n2-1]
        vector<vector<int>> suff(n1 + 2, vector<int>(n2 + 2, 0));

        // 1. Build Prefix LCS DP Table
        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
                if (s1[i - 1] == s2[j - 1]) {
                    pref[i][j] = 1 + pref[i - 1][j - 1];
                } else {
                    pref[i][j] = max(pref[i - 1][j], pref[i][j - 1]);
                }
            }
        }

        // 2. Build Suffix LCS DP Table
        for (int i = n1; i >= 1; --i) {
            for (int j = n2; j >= 1; --j) {
                if (s1[i - 1] == s2[j - 1]) {
                    suff[i][j] = 1 + suff[i + 1][j + 1];
                } else {
                    suff[i][j] = max(suff[i + 1][j], suff[i][j + 1]);
                }
            }
        }

        int original_lcs = pref[n1][n2];
        int total_ways = 0;

        // 3. Try inserting every character at every possible position in s1
        for (int i = 0; i <= n1; ++i) {
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                bool can_increase = false;
                
                for (int j = 1; j <= n2; ++j) {
                    if (s2[j - 1] == ch) {
                        // If we match 'ch' with s2[j-1], the new LCS length will be:
                        // LCS of left parts + 1 (for the matched char) + LCS of right parts
                        // For this to strictly increase the overall LCS by 1, 
                        // the left and right parts must sum to the original LCS.
                        if (pref[i][j - 1] + suff[i + 1][j + 1] == original_lcs) {
                            can_increase = true;
                            break; 
                        }
                    }
                }
                
                if (can_increase) {
                    total_ways++;
                }
            }
        }

        return total_ways;
    }
};

// Driver code setup to verify standalone compilation
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            string s1, s2;
            cin >> s1 >> s2;
            Solution obj;
            cout << obj.waysToIncreaseLCSBy1(s1, s2) << "\n";
        }
    }
    return 0;
}
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
