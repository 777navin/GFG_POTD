/*
🧠 Problem: Remove Spaces (GFG POTD)
📅 Date: 14 April 2026 🇮🇳
📊 Difficulty: Basic

📄 Description:
Given a string s, remove all the spaces from the string and return the modified string.

📥 Example:
Input:  "g eeks for ge eeks"
Output: "geeksforgeeks"

💡 Approaches:

1️⃣ Brute Force:
- Traverse string
- Create new string with non-space characters

2️⃣ Optimized:
- Use two pointers
- Overwrite characters in-place

⏱️ Complexity:
Brute Force -> Time: O(n), Space: O(n)
Optimized   -> Time: O(n), Space: O(1)

🚀 Status: Solved
*/

#include <bits/stdc++.h>
using namespace std;

// 🔹 Brute Force Approach
string removeSpacesBrute(string s) {
    string ans = "";
    for (char c : s) {
        if (c != ' ') {
            ans += c;
        }
    }
    return ans;
}

// 🔹 Optimized Approach (In-Place)
string removeSpacesOptimized(string s) {
    int j = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != ' ') {
            s[j++] = s[i];
        }
    }
    return s.substr(0, j);
}

// 🔹 Driver Code
int main() {
    string s = "g eeks for ge eeks";

    cout << "Brute Force Output: " << removeSpacesBrute(s) << endl;
    cout << "Optimized Output: " << removeSpacesOptimized(s) << endl;

    return 0;
}
