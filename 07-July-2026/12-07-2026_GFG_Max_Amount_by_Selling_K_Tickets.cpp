/*
=========================================================
Date        : 12-07-2026
Problem Name: Max Amount by Selling K Tickets
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Greedy, Heap, Data Structures

Problem Summary:
Given an array arr[] representing the number of tickets available with each seller. 
The price of a ticket equals the remaining tickets that seller has, and after a sale, 
that seller's ticket count decreases by 1. Find the maximum amount earned by selling 
at most k tickets, returned modulo 10^9 + 7.

Key Observation:
To maximize profit, we must always greedily sell a ticket from the seller who currently 
has the maximum number of tickets available.
=========================================================
*/

#include <vector>
#include <queue>

using namespace std;

/*
=========================================================
APPROACH 1: Max-Heap (Greedy Strategy)
=========================================================
• Intuition:
  To get the maximum revenue, we should always pick the highest available ticket price 
  at any given step. A max-heap efficiently tracks the largest element.

• Approach:
  1. Push all elements of the array into a max-heap.
  2. Perform a loop k times to sell k tickets.
  3. In each iteration, extract the top element (max current price), add it to the total profit, 
     decrement it by 1, and push it back into the heap if it remains greater than 0.
  4. Return the total profit modulo 10^9 + 7.

• Why it Works:
  Extracting the maximum element ensures that we always make the locally optimal choice, 
  which leads to a globally maximum total profit over k steps.

• Time Complexity (TC) : O(N + K log N), where N is the size of the array.
• Space Complexity (SC): O(N) to store elements in the priority queue.
*/

/*
=========================================================
FINAL APPROACH CHOICE
=========================================================
The Max-Heap approach is chosen because the constraints on k (k <= 10^6) and the array 
size (N <= 10^5) allow an O(N + K log N) solution to pass comfortably within standard 
time limits. It directly simulates the greedy choice rule cleanly using standard STL containers.
*/

class Solution {
public:
    int maxAmount(vector<int>& arr, int k) {
        long long totalAmount = 0;
        long long MOD = 1e9 + 7;
        
        // Max-heap to store ticket counts
        priority_queue<int> pq(arr.begin(), arr.end());
        
        // Sell at most k tickets
        while (k > 0 && !pq.empty()) {
            int currentMax = pq.top();
            pq.pop();
            
            totalAmount = (totalAmount + currentMax) % MOD;
            k--;
            
            // Re-insert if there are remaining tickets for this seller
            if (currentMax - 1 > 0) {
                pq.push(currentMax - 1);
            }
        }
        
        return totalAmount;
    }
};
