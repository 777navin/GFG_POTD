/*
=========================================================
Date        : 02-09-2026
Problem Name: Unoccupied Computers
Platform    : GeeksforGeeks (GFG)
Difficulty  : Easy
Tags        : Hash, Strings, Data Structures

Problem Summary:
A cafe has n computers. Given a sequence of customer arrivals and departures
where each customer appears twice, determine how many customers walk away
without being assigned a computer because all were occupied at arrival.

Key Observation:
A customer only acquires a computer on their first visit if current occupied count < n.
If no computer is available on first appearance, they are marked as rejected and ignore capacity on departure.
=========================================================
*/

/*
=========================================================
APPROACH 1: State Tracking with Hash Map / Arrays (Optimal)
=========================================================
• Intuition:
  Maintain the status of each customer (not seen, assigned a computer, or rejected)
  along with a count of currently occupied computers.

• Approach:
  - Use a state array of size 26 initialized to 0 (0 = not seen, 1 = using computer, 2 = rejected).
  - Iterate through the string character by character:
    - If seen for the first time (state 0):
      - If occupied computers < n, assign a computer (state = 1) and increment occupied count.
      - Else, customer cannot get a computer (state = 2), increment rejected count.
    - If seen for the second time:
      - If state was 1, they release the computer: decrement occupied count.
      - If state was 2, they just leave without freeing any computer.
  - Return the total rejected count.

• Why it Works:
  Each character appears exactly twice denoting entry and exit. Tracking state prevents 
  rejected customers from incorrectly releasing computers upon departure.

• Time Complexity (TC):
  O(|s|) - Single pass over the input string of length up to 52.

• Space Complexity (SC):
  O(1) - Fixed-size array of 26 integers for uppercase English letters.
=========================================================
*/

/*
=========================================================
FINAL APPROACH CHOICE:
The single-pass state tracking approach using a fixed-size frequency/state array
runs in optimal O(|s|) time and O(1) auxiliary space, perfectly adhering to the 
constraints without unnecessary dynamic memory overhead.
=========================================================
*/

#include <string>
#include <vector>

class Solution {
public:
    int solve(int n, std::string s) {
        // State representation:
        // 0 -> Customer has not arrived yet
        // 1 -> Customer is currently allocated a computer
        // 2 -> Customer arrived but was turned away (rejected)
        std::vector<int> customerState(26, 0);
        
        int occupied = 0;
        int rejectedCount = 0;
        
        for (char ch : s) {
            int idx = ch - 'A';
            
            if (customerState[idx] == 0) {
                // First occurrence: Arrival
                if (occupied < n) {
                    customerState[idx] = 1;
                    occupied++;
                } else {
                    customerState[idx] = 2;
                    rejectedCount++;
                }
            } else if (customerState[idx] == 1) {
                // Second occurrence: Departure of a customer who had a computer
                customerState[idx] = 0;
                occupied--;
            }
            // If customerState[idx] == 2, the customer is departing after being rejected;
            // no computer was occupied, so no capacity change is needed.
        }
        
        return rejectedCount;
    }
};
