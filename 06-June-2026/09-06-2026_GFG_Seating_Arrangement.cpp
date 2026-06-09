/*
Date: 09-06-2026
Problem Name: Seating Arrangement
Platform: GeeksforGeeks
Difficulty: Easy
Tags: Array, Greedy

Problem Summary:
Determine if it is possible to seat 'k' additional people in an array of 'seats' (0: empty, 1: occupied) 
such that no two occupied seats are adjacent. Note: We must also validate the initial state.

Methods to Solve:
1. Greedy Approach (Optimal)

For the Optimal Method:
- Intuition: 
  1. First, check if the initial array already violates the condition (two 1s adjacent). If yes, return false.
  2. Then, traverse and place people where seats are empty and neighbors are free.
- Approach:
  - Check for existing adjacent 1s in the input array.
  - Iterate and place people greedily.
- Time Complexity: O(n)
- Space Complexity: O(1)

Comparison Table:
Method | TC | SC | Best Use Case
Greedy | O(n) | O(1) | General constraint satisfaction

Final Recommended Solution: Greedy Approach
*/

#include <vector>
using namespace std;

class Solution {
public:
    /**
     * @param k Number of people to seat.
     * @param seats Current seating arrangement.
     * @return true if all k people can be seated, false otherwise.
     */
    bool canSeatAllPeople(int k, vector<int>& seats) {
        int n = seats.size();

        // 1. Validate initial state: check for existing adjacent 1s
        for (int i = 0; i < n - 1; ++i) {
            if (seats[i] == 1 && seats[i + 1] == 1) {
                return false;
            }
        }

        // 2. Try to place k people
        for (int i = 0; i < n && k > 0; ++i) {
            if (seats[i] == 0) {
                bool leftClear = (i == 0 || seats[i - 1] == 0);
                bool rightClear = (i == n - 1 || seats[i + 1] == 0);
                
                if (leftClear && rightClear) {
                    seats[i] = 1; 
                    k--;
                }
            }
        }
        
        return k == 0;
    }
};
