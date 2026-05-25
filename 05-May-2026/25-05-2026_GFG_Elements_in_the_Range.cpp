// 25-05-2026_GFG_Elements_in_the_Range.cpp

/*
Date: 25-05-2026
Problem Name: Elements in the Range
Platform: GeeksforGeeks
Difficulty: Basic
Tags: Array, Searching, Hash Table

Problem Summary:
Given an array of distinct positive integers and a range defined by [start, end], 
determine if the array contains all the elements within this inclusive range.

Methods to Solve:
1. Brute Force (Linear Search)
2. Better Approach (Hashing)
3. Optimal Approach (Range Counting)

---------------------------------------------------------
1. Brute Force (Linear Search)
- Intuition: Check for the presence of every single number in the range [start, end] by scanning the entire array.
- Approach: Use a nested loop. The outer loop iterates from 'start' to 'end'. The inner loop iterates through the array to find the current number.
- Dry Run: start=2, end=5, arr=[1, 4, 5, 2, 7]. 
  Check 2 -> found. Check 3 -> not found. Return false.
- Time Complexity: O(N * K) where N is array size and K is (end - start + 1).
- Space Complexity: O(1)
- Why better than previous method: N/A (Baseline).
- When to use: Never recommended for large constraints.

---------------------------------------------------------
2. Better Approach (Hashing)
- Intuition: Lookup operations can be optimized to O(1) using a Hash Set.
- Approach: Insert all elements of the array into an `unordered_set`. Then, iterate from 'start' to 'end' and check if each element exists in the set.
- Dry Run: start=2, end=5, arr=[1, 4, 5, 2, 7, 3]. 
  Set = {1, 4, 5, 2, 7, 3}. 
  Check 2 (O(1)) -> found. Check 3 -> found. Check 4 -> found. Check 5 -> found. Return true.
- Time Complexity: O(N + K) to insert N elements and check K elements.
- Space Complexity: O(N) to store elements in the set.
- Why better than previous method: Reduces search time from O(N) to O(1) on average for each element.
- When to use: When the array doesn't guarantee distinct elements, or when memory is not a strict bottleneck.

---------------------------------------------------------
3. Optimal Approach (Range Counting)
- Intuition: The problem explicitly states the array contains *distinct* positive integers. If we simply count how many elements in the array fall strictly within the [start, end] bounds, that count must equal the total number of elements required in the range.
- Approach: Iterate through the array once. If `arr[i] >= start` and `arr[i] <= end`, increment a counter. Finally, check if the counter equals `end - start + 1`.
- Dry Run: start=2, end=5, arr=[1, 4, 5, 2, 7, 8, 3]. Required count = 5 - 2 + 1 = 4.
  arr[0]=1 (ignore), arr[1]=4 (count=1), arr[2]=5 (count=2), arr[3]=2 (count=3), arr[6]=3 (count=4).
  count == required count (4 == 4). Return true.
- Time Complexity: O(N) - single pass through the array.
- Space Complexity: O(1) - purely counter variables used.
- Why better than previous method: Achieves O(N) time without requiring auxiliary space for a Hash Set.
- When to use: Always best when the array is guaranteed to have distinct elements.

---------------------------------------------------------
Comparison Table:
Method         | TC         | SC   | Best Use Case
---------------|------------|------|---------------------------------------
Brute Force    | O(N * K)   | O(1) | Small arrays where K is very small
Hashing        | O(N + K)   | O(N) | Large arrays with duplicate elements
Range Counting | O(N)       | O(1) | Optimal for distinct element arrays

Final Recommended Solution: Optimal Approach (Range Counting)
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    // Optimal Approach: Range Counting
    // Time Complexity: O(N), Space Complexity: O(1)
    bool checkElements(int start, int end, vector<int>& arr) {
        int requiredElements = end - start + 1;
        int foundElements = 0;
        
        for (int num : arr) {
            if (num >= start && num <= end) {
                foundElements++;
            }
        }
        
        // Since array has distinct elements, the count should exactly match
        return foundElements == requiredElements;
    }

    // Better Approach: Hashing (Included for completeness/alternative scenario)
    // Time Complexity: O(N + K), Space Complexity: O(N)
    bool checkElementsHashing(int start, int end, vector<int>& arr) {
        unordered_set<int> st(arr.begin(), arr.end());
        
        for (int i = start; i <= end; i++) {
            if (st.find(i) == st.end()) {
                return false;
            }
        }
        return true;
    }
};

// Driver Code
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    // Uncomment below lines for full competitive programming input
    // cin >> t;
    // while(t--) {
    //     int n, start, end;
    //     cin >> n >> start >> end;
    //     vector<int> arr(n);
    //     for(int i = 0; i < n; i++) cin >> arr[i];
    //     Solution obj;
    //     cout << (obj.checkElements(start, end, arr) ? "true" : "false") << "\n";
    // }

    // Dry Run Testing Example 1
    int start1 = 2, end1 = 5;
    vector<int> arr1 = {1, 4, 5, 2, 7, 8, 3};
    Solution obj;
    
    cout << "Test Case 1 Output: " 
         << (obj.checkElements(start1, end1, arr1) ? "true" : "false") << "\n"; 
         // Expected: true

    // Dry Run Testing Example 2
    int start2 = 2, end2 = 6;
    vector<int> arr2 = {1, 4, 5, 2, 7, 8, 3};
    
    cout << "Test Case 2 Output: " 
         << (obj.checkElements(start2, end2, arr2) ? "true" : "false") << "\n"; 
         // Expected: false

    return 0;
}
