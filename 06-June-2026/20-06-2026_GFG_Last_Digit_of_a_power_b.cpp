/*
Date: 20-06-2026
Problem Name: Last Digit of a^b
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Math, Strings, Modular Arithmetic

Problem Summary:
Given two integers 'a' and 'b' in the form of strings, find the last digit of a^b.
The strings can be very large (up to 1000 characters), so direct computation is impossible.

Methods to Solve:
1. Modular Exponentiation (Character by Character)
2. Cyclicity of Last Digits (Optimal Math Approach)

For EACH method include:

- Intuition (Optimal):
  The last digit of any number raised to a power depends ONLY on the last digit of the base. 
  Furthermore, the sequence of last digits for any base repeats in cycles of 4. 
  For example, powers of 2 end in: 2, 4, 8, 6, 2, 4, 8, 6...
  Therefore, we only need to find the last digit of string 'a', and find the value of 
  string 'b' modulo 4. 
  A mathematical property of modulo 4 is that a number modulo 4 is equal to its 
  last two digits modulo 4.

- Approach (Optimal):
  1. Base Cases: If `b` is "0", return 1. If `a` is "0" (and `b` is not "0"), return 0.
  2. Get the last digit of `a` as an integer (`base`).
  3. Extract the last two digits of string `b` and compute their integer value modulo 4 (`exp`).
  4. If `exp == 0`, it means the power is a multiple of 4, so we set `exp = 4` (to get the last item in the 4-step cycle).
  5. Compute `pow(base, exp) % 10` and return the result.

- Dry Run (small example):
  Input: a = "3", b = "10"
  Base case: neither are "0".
  base = last digit of "3" -> 3.
  exp = last two digits of "10" -> 10.
  10 % 4 = 2. So exp = 2.
  Result = pow(3, 2) % 10 = 9 % 10 = 9.

  Input: a = "6", b = "2"
  base = 6.
  exp = 2 % 4 = 2.
  Result = pow(6, 2) % 10 = 36 % 10 = 6.

- Time Complexity: O(1). Extracting the last characters and doing basic arithmetic takes constant time.
- Space Complexity: O(1). No extra memory is allocated.
- Why better than previous method: We avoid iterating through the entire length of the 1000-character string 'b', reducing processing time to instant O(1) mathematical lookup.
- When to use: Whenever you need cyclicity patterns in large exponentiations.

Comparison Table:
Method             | TC      | SC      | Best Use Case
-------------------|---------|---------|-------------------------
Modular Pow        | O(len)  | O(1)    | Standard modular arithmetic
Cyclicity (Math)   | O(1)    | O(1)    | Optimal for finding exact last digit

Final Recommended Solution:
The Cyclicity approach is optimally fast since it completely ignores the massive lengths of the strings and directly targets the mathematical pattern.
*/

#include <string>
#include <cmath>

class Solution {
public:
    int getLastDigit(std::string& a, std::string& b) {
        // Base case: anything to the power of 0 is 1
        if (b == "0") return 1;
        
        // Base case: 0 to the power of anything is 0
        if (a == "0") return 0;
        
        // Get the last digit of the base
        int base = a.back() - '0';
        
        // Find the exponent modulo 4
        // A number modulo 4 is determined entirely by its last two digits
        int exp = 0;
        int len = b.length();
        
        if (len == 1) {
            exp = b[0] - '0';
        } else {
            exp = (b[len - 2] - '0') * 10 + (b[len - 1] - '0');
        }
        
        exp = exp % 4;
        
        // If modulo is 0, it falls on the 4th cycle
        if (exp == 0) {
            exp = 4;
        }
        
        // Calculate the power and return the last digit
        int result = std::pow(base, exp);
        return result % 10;
    }
};

