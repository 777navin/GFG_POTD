/*
Date: 26-04-2026
Problem Name: Common in 3 Sorted Arrays
Platform: GeeksforGeeks (GFG)
Difficulty: Easy
Tags: Arrays, Two-pointers, Searching

Problem Summary:
Given three arrays sorted in non-decreasing order, return all common elements 
across these three arrays in non-decreasing order. Ignore duplicates and 
include each common element only once in the output.

Methods to Solve:
1. Brute Force (Nested Loops): Check every element of A in B and C.
2. Binary Search: For each element in A, binary search in B and C.
3. Three-Pointer Approach: Optimal approach taking advantage of sorted arrays.

---------------------------------------------------------------------------
Method 3: Three-Pointer Approach [Optimal Approach]

- Intuition:
  Since all arrays are sorted, we can use three pointers (i, j, k) starting at index 0.
  We move the pointers of the smaller elements to catch up with the largest one.

- Approach:
  1. Initialize i = 0, j = 0, k = 0.
  2. While i < n1, j < n2, and k < n3:
     - If A[i] == B[j] == C[k]:
       - Add to result (if not a duplicate).
       - Increment all three pointers.
     - Else if A[i] < B[j]: increment i.
     - Else if B[j] < C[k]: increment j.
     - Else: increment k.
  3. To handle duplicates: check if the current common element is the same as the last 
     element added to the result vector.

- Dry Run:
  A = [1, 5, 10], B = [5, 10, 15], C = [5, 10, 20]
  i=0, j=0, k=0 -> A[0]=1, B[0]=5, C[0]=5. A[0] is smallest, i++.
  i=1, j=0, k=0 -> A[1]=5, B[0]=5, C[0]=5. Equal! Add 5, i++, j++, k++.
  i=2, j=1, k=1 -> A[2]=10, B[1]=10, C[1]=10. Equal! Add 10, i++, j++, k++.
  Loop ends. Result: [5, 10].

- Time Complexity: O(n1 + n2 + n3) - Linear scan of all arrays.
- Space Complexity: O(1) auxiliary space (excluding result vector).
- Why better: Much faster than Binary Search (O(n1 * log(n2*n3))) and doesn't require extra 
  memory like a Hash Map (O(n1+n2+n3) space).
- When to use: When arrays are already sorted.

---------------------------------------------------------------------------
Comparison Table:
Method         | TC               | SC             | Best Use Case
Brute Force    | O(n1 * n2 * n3)  | O(1)           | Never (Inefficient)
Binary Search  | O(n1 * log(n2*n3))| O(1)          | When one array is much smaller than others.
Three-Pointer  | O(n1 + n2 + n3)  | O(1)           | Standard optimal choice for sorted arrays.

Final Recommended Solution: Three-Pointer Approach
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief Finds common elements in three sorted arrays.
     * * @param a First sorted array
     * @param b Second sorted array
     * @param c Third sorted array
     * @return vector<int> List of unique common elements
     */
    vector<int> commonElements(vector<int> &a, vector<int> &b, vector<int> &c) {
        int i = 0, j = 0, k = 0;
        int n1 = a.size();
        int n2 = b.size();
        int n3 = c.size();
        
        vector<int> result;

        while (i < n1 && j < n2 && k < n3) {
            // Case 1: All three elements are equal
            if (a[i] == b[j] && b[j] == c[k]) {
                // To ignore duplicates, check if it's the first element or different from previous
                if (result.empty() || result.back() != a[i]) {
                    result.push_back(a[i]);
                }
                i++;
                j++;
                k++;
            }
            // Case 2: a[i] is the smallest, move i
            else if (a[i] < b[j]) {
                i++;
            }
            // Case 3: b[j] is the smallest, move j
            else if (b[j] < c[k]) {
                j++;
            }
            // Case 4: c[k] is the smallest, move k
            else {
                k++;
            }
        }
        
        return result;
    }
};

// GFG Driver Code compatible section (if testing locally)
/*
int main() {
    Solution sol;
    vector<int> a = {1, 5, 10, 20, 40, 80};
    vector<int> b = {6, 7, 20, 80, 100};
    vector<int> c = {3, 4, 15, 20, 30, 70, 80, 120};
    
    vector<int> res = sol.commonElements(a, b, c);
    for(int x : res) cout << x << " "; // Output: 20 80
    return 0;
}
*/
