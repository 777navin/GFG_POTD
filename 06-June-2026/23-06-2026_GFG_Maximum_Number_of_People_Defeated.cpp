// 23-06-2026_GFG_Maximum_Number_of_People_Defeated.cpp

/*
Date: 23-06-2026
Problem Name: Maximum Number of People Defeated
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Math, Binary Search, Simulation

Problem Summary: 
There are infinitely many people standing in a row where the i-th person has a strength of i * i. 
Given an initial strength 'p', you need to find the maximum number of people you can defeat. 
Every time you defeat a person, your strength 'p' decreases by their strength (i * i).

Methods to Solve:
1. Brute Force (Linear Simulation)
2. Optimal Approach (Binary Search with Math Formula)

-------------------------------------------------------------------
Method 1: Brute Force (Linear Simulation)
-------------------------------------------------------------------
- Intuition: 
  The simplest way is to greedily simulate the process. Since we must defeat people in order 
  starting from index 1, we can just keep subtracting the required strength until our current 
  strength drops below the strength of the next person.
- Approach: 
  Initialize a counter. Loop starting from i = 1, check if `p >= i * i`. 
  If it is, subtract `i * i` from `p`, increment the counter, and increment `i`.
- Dry Run (p = 14):
  i=1: p >= 1? Yes. p = 14 - 1 = 13. Count = 1.
  i=2: p >= 4? Yes. p = 13 - 4 = 9. Count = 2.
  i=3: p >= 9? Yes. p = 9 - 9 = 0. Count = 3.
  i=4: p >= 16? No. Loop ends. Output: 3.
- Time Complexity: O(p^(1/3))
  The sum of squares of the first 'n' natural numbers is approximately n^3 / 3. 
  For p = 3 * 10^8, max loop iterations will be around 1000.
- Space Complexity: O(1)
- When to use: 
  When 'p' is relatively small or if you want a simple, bug-free implementation.

-------------------------------------------------------------------
Method 2: Optimal Approach (Binary Search + Math Formula)
-------------------------------------------------------------------
- Intuition: 
  We are searching for the maximum number of people 'n' such that the sum of the squares 
  of the first 'n' people is less than or equal to 'p'. Since the sum of squares is monotonically 
  increasing, we can use Binary Search.
- Approach: 
  The sum of squares of the first 'n' natural numbers is given by the formula: 
  S = (n * (n + 1) * (2n + 1)) / 6
  We can binary search the answer 'n'. For p = 3*10^8, the maximum possible answer is less 
  than 1000. We set low = 0, high = 1000, and binary search for the maximum 'mid' where 
  the formula yields a result <= p.
- Dry Run (p = 14):
  low = 0, high = 1000
  mid = 500, sum = (500*501*1001)/6 (Too large). high = 499.
  ... eventually narrows down to:
  mid = 3, sum = (3 * 4 * 7) / 6 = 14. 14 <= 14. ans = 3. low = 4.
  mid = 4, sum = (4 * 5 * 9) / 6 = 30. 30 > 14. high = 3.
  Loop ends. Output: 3.
- Time Complexity: O(log(min(p, 1000))) -> O(1) effectively.
- Space Complexity: O(1)
- Why better than previous method: 
  It guarantees logarithmic time regardless of how large 'p' gets, making it extremely scalable.
- When to use: 
  When 'p' constraints are massive (e.g., up to 10^18) where O(p^(1/3)) might TLE.

Comparison Table:
Method       | TC          | SC   | Best Use Case
---------------------------------------------------
Brute Force  | O(p^(1/3))  | O(1) | Small to medium 'p', simple interviews.
Binary Search| O(log N)    | O(1) | Extremely large 'p', optimal performance.

Final Recommended Solution: Optimal Approach (Binary Search)
*/

#include <iostream>

using namespace std;

class Solution {
public:
    int maxPeopleDefeated(int p) {
        // Optimal Approach using Binary Search
        
        // Given constraints p <= 3*10^8, maximum answer will not exceed 1000.
        // n^3 / 3 = 3*10^8  => n^3 = 9*10^8 => n is slightly less than 1000.
        long long low = 0;
        long long high = 1000; 
        long long max_defeated = 0;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            
            // Formula for sum of squares of first 'mid' natural numbers
            long long sum_of_squares = (mid * (mid + 1) * (2 * mid + 1)) / 6;

            if (sum_of_squares <= p) {
                // We can defeat 'mid' people, let's see if we can defeat more
                max_defeated = mid;
                low = mid + 1;
            } else {
                // 'mid' is too large, we don't have enough strength
                high = mid - 1;
            }
        }

        return max_defeated;
    }
};

// ================== Driver Code ==================
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            int p;
            cin >> p;
            Solution ob;
            cout << ob.maxPeopleDefeated(p) << "\n";
        }
    }
    return 0;
}
