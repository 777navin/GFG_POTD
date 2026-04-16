// Problem: Implement Atoi
// Platform: GeeksforGeeks
// Date: 16-04-2026

/*
Intuition:
We need to convert a string into a 32-bit signed integer
without using built-in conversion functions.

We must carefully handle:
1. Leading whitespaces
2. Optional '+' or '-' sign
3. Digits conversion
4. Stopping at first non-digit character
5. Integer overflow

Approach:
1. Skip all leading spaces.
2. Check if next character is '+' or '-'.
3. Traverse digits one by one:
   result = result * 10 + digit
4. If overflow happens:
   return INT_MAX or INT_MIN
5. Apply sign and return answer.

Example:
Input: "   -123abc"
Output: -123

Input: "4193 with words"
Output: 4193

Time Complexity: O(n)
- Traverse string once.

Space Complexity: O(1)
- Constant extra space.
*/

class Solution {
public:
    int myAtoi(string s) {
        int n = s.size();
        int i = 0;

        // Skip leading spaces
        while (i < n && s[i] == ' ')
            i++;

        // Handle sign
        int sign = 1;
        if (i < n && (s[i] == '+' || s[i] == '-')) {
            if (s[i] == '-')
                sign = -1;
            i++;
        }

        long long result = 0;

        // Convert digits
        while (i < n && isdigit(s[i])) {
            result = result * 10 + (s[i] - '0');

            // Overflow check
            if (sign == 1 && result > INT_MAX)
                return INT_MAX;

            if (sign == -1 && -result < INT_MIN)
                return INT_MIN;

            i++;
        }

        return (int)(sign * result);
    }
};
