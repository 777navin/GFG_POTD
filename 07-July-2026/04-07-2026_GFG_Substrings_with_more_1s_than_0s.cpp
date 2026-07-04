/*
Date        : 04-07-2026
Problem Name: Substrings with more 1's than 0's
Platform    : GeeksforGeeks
Difficulty  : Hard
Tags        : String, Prefix Sum, Hashing, Combinatorics

Problem Summary:
Given a binary string 's', calculate the total number of substrings that contain more 1's than 0's.

Constraints:
1 <= |S| <= 6 * 10^4

Key Observation: Let count(1) be the number of 1's and count(0) be the number of 0's in a substring. We need substrings where count(1) > count(0). If we map '1' to 1 and '0' to -1, a substring has more 1's than 0's if the sum of its elements is > 0. This transforms the problem into finding the number of subarrays with a sum > 0.
*/

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

/*

Optimized Approach: Prefix Sum + Fenwick Tree / Balanced BST
Intuition:
Convert 0 to -1 and 1 to 1. Let P[i] be the prefix sum up to index i.
A subarray s[j...i] (where j <= i) has a sum > 0 if P[i] - P[j-1] > 0,
or P[i] > P[j-1].
We need to count pairs (j-1, i) such that j-1 < i and P[j-1] < P[i].
This is equivalent to counting inversions or using a Fenwick tree to count
elements smaller than current prefix sum.

Approach:

Maintain a running prefix sum.

Since prefix sums can range from -N to N, use an offset to map them to positive indices.

Use a Fenwick tree (Binary Indexed Tree) to store the frequencies of prefix sums encountered so far.

For each prefix sum, query the BIT for the count of all prefix sums smaller than the current one.

Update the BIT with the current prefix sum.

Time Complexity: O(N log N)
Space Complexity: O(N)
*/

class Solution {
private:
void update(vector<int>& bit, int idx, int val) {
for (; idx < bit.size(); idx += idx & -idx)
bit[idx] += val;
}

int query(vector<int>& bit, int idx) {
    int sum = 0;
    for (; idx > 0; idx -= idx & -idx)
        sum += bit[idx];
    return sum;
}
public:
int countSubstring(string& s) {
int n = s.length();
int offset = n + 1;
// BIT size covers range -n to n
vector<int> bit(2 * n + 2, 0);

    long long count = 0;
    int current_sum = 0;
    
    // Initial prefix sum of 0 exists at index -1
    update(bit, 0 + offset, 1);
    
    for (char c : s) {
        current_sum += (c == '1' ? 1 : -1);
        
        // Count prefix sums < current_sum
        count += query(bit, current_sum + offset - 1);
        
        // Add current prefix sum to BIT
        update(bit, current_sum + offset, 1);
    }
    
    return (int)count;
}
};

Method          | Idea                | Time     | Space    | Difficulty | Recommended
Brute Force     | Check all subarrays | O(N^2)   | O(1)     | Easy       | No Prefix Sum + BIT| Count smaller sums  | O(N log N)| O(N)    | Hard       | Yes
Final Recommended Approach:
The O(N log N) approach using a Fenwick Tree is the most optimal for the given constraints (N = 6*10^4).
It efficiently counts the number of valid starting points for every ending position by leveraging the
prefix sum property and dynamic frequency updates.
