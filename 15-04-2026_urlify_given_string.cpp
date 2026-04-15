// Problem: URLify a given string
// Platform: GeeksforGeeks
// Date: 15-04-2026

/*
Intuition:
We need to replace every space character ' ' in the string
with "%20". Instead of modifying the original string directly,
we create a new result string and build the answer step by step.

Approach:
1. Traverse each character of the input string.
2. If the character is a space:
      append "%20" to result.
3. Otherwise:
      append the current character.
4. Return the final string.

Example:
Input:  "i love programming"
Output: "i%20love%20programming"

Time Complexity: O(n)
- We visit each character once.

Space Complexity: O(n)
- Extra string is used to store answer.
*/

class Solution {
public:
    string URLify(string &s) {
        string result = "";

        for(char ch : s) {
            if(ch == ' ')
                result += "%20";
            else
                result += ch;
        }

        return result;
    }
};
