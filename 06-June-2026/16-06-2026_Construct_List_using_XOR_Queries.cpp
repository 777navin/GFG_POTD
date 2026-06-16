/*
Date: 16-06-2026
Problem Name: Construct List using XOR Queries
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Array, Bit Manipulation, XOR, Data Structures

Problem Summary:
We start with an array containing a single value '0'. 
We are given 'q' queries:
- Type 0: Insert value 'x' into the list.
- Type 1: XOR every element in the list with 'x'.
Finally, return the list in sorted order.

Methods to Solve:
1. Brute Force (Simulation)
2. Optimal Approach (Deferred XOR/Mathematical)

For EACH method include:

- Method 1: Brute Force
  - Intuition: Directly simulate the operations as described.
  - Approach: Use a vector, perform push_back for type 0, and iterate over the vector for type 1.
  - Time Complexity: O(q^2) - Too slow given constraints (q <= 10^5).
  - Space Complexity: O(q)

- Method 2: Optimal Approach
  - Intuition: Instead of XORing every element at each query (Type 1), we maintain a running XOR value ('current_xor').
    When a number 'x' is added (Type 0), we store 'x ^ current_xor'. When Type 1 occurs, we just update the global 'current_xor'. 
    At the end, every element 'val' in our storage is actually 'val ^ current_xor'.
  - Approach: 
    1. Maintain a list 'res' with initial value '0'.
    2. Maintain 'current_xor' initialized to 0.
    3. For Type 0 (x): res.push_back(x ^ current_xor).
    4. For Type 1 (x): current_xor ^= x.
    5. Finalize: For every element in 'res', XOR it with 'current_xor'.
    6. Sort and return.
  - Time Complexity: O(q log q) due to sorting.
  - Space Complexity: O(q)
  - Why better: Avoids O(q) updates per query, reducing total complexity to log-linear.
  - When to use: When handling bulk XOR updates on an entire collection.

Comparison Table:
Method | TC | SC | Best Use Case
-------|----|----|--------------
Brute  | O(q^2)| O(q)| Small constraints
Optimal| O(q log q)| O(q)| Large constraints

Final Recommended Solution: Optimal Approach
*/

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    /**
     * @brief Constructs the list by deferring XOR operations.
     * * @param queries A vector of queries where queries[i][0] is type, queries[i][1] is value.
     * @return vector<int> Sorted list of elements after all queries.
     */
    std::vector<int> constructList(std::vector<std::vector<int>>& queries) {
        std::vector<int> result;
        result.push_back(0); // Initial value in the list
        
        int current_xor = 0;
        
        // Process queries in reverse or maintain running XOR
        // Using the logic: storing (x ^ current_xor) allows 
        // batch application of XOR later.
        for (const auto& q : queries) {
            if (q[0] == 0) {
                // Insert x: store it XORed with current running XOR
                result.push_back(q[1] ^ current_xor);
            } else {
                // XOR all: update the running XOR
                current_xor ^= q[1];
            }
        }
        
        // Finalize: apply the cumulative XOR to all elements
        for (int &val : result) {
            val ^= current_xor;
        }
        
        // Result must be sorted
        std::sort(result.begin(), result.end());
        
        return result;
    }
};
