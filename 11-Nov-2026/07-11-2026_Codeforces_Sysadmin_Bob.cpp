/*
=========================================================
Date        : 07-11-2026
Problem Name: Sysadmin Bob
Platform    : Codeforces
Difficulty  : 1500
Tags        : Strings, Greedy, Implementation

Problem Summary:
- Given a concatenated string of Berland email addresses without commas.
- Each email is of the form A@B where A and B are non-empty strings of small Latin letters.
- Reconstruct any valid comma-separated list of these email addresses, or output "No solution".

Key Observation:
- Every email requires at least one character before '@' (prefix A) and at least one character after '@' (suffix B).
- Consequently, the first '@' cannot be at index 0, the last '@' cannot be at the last index, and between any two adjacent '@' symbols, there must be at least 2 characters so that the first gets a suffix character and the second gets a prefix character.
=========================================================
*/

/*
=========================================================
APPROACH EXPLANATION
=========================================================

1. Greedy / Validation Approach
   • Intuition: Identify all '@' positions and check validity rules for email boundaries.
   • Approach: 
     - Collect all indices where '@' occurs.
     - Validate that there is at least one '@', no '@' is at the very beginning or end of the string, and the distance between any two adjacent '@' indices is at least 3.
     - If any validation fails, output "No solution".
     - Otherwise, greedily partition the string by placing commas after the character immediately following each intermediate '@'.
   • Why it Works: Each '@' separates an email's domain suffix from the next email's username prefix. Allocating one character after '@' to the current email and the next character to the subsequent email is both necessary and sufficient given the constraints.
   • Time Complexity (TC): O(N) where N is the length of the string, as we scan the string and collect indices.
   • Space Complexity (SC): O(N) to store the indices of '@' and the resulting string/output.

Final Approach Chosen:
- The linear greedy validation and reconstruction approach is chosen because it runs in optimal O(N) time and O(N) space, perfectly handling all edge cases and constraints (N <= 200).
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    // Optimize standard input/output streams for speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    int n = s.length();
    vector<int> at_indices;

    // Find all occurrences of '@'
    for (int i = 0; i < n; ++i) {
        if (s[i] == '@') {
            at_indices.push_back(i);
        }
    }

    int k = at_indices.size();

    // Check basic validity conditions
    // 1. Must have at least one '@'
    // 2. First '@' cannot be at index 0 (missing prefix A)
    // 3. Last '@' cannot be at index n-1 (missing suffix B)
    if (k == 0 || at_indices[0] == 0 || at_indices.back() == n - 1) {
        cout << "No solution\n";
        return 0;
    }

    // 4. Distance between any two adjacent '@' must be at least 3
    // (meaning at least 2 characters between them to act as B_1 and A_2)
    for (int i = 0; i < k - 1; ++i) {
        if (at_indices[i + 1] - at_indices[i] < 3) {
            cout << "No solution\n";
            return 0;
        }
    }

    // Construct the result
    string result = "";
    int current_start = 0;

    for (int i = 0; i < k - 1; ++i) {
        int at_pos = at_indices[i];
        // Email ends at at_pos + 1 (including one character after '@')
        result += s.substr(current_start, (at_pos + 1) - current_start + 1);
        result += ",";
        // Next email starts at at_pos + 2
        current_start = at_pos + 2;
    }

    // Append the last email
    result += s.substr(current_start);

    cout << result << "\n";

    return 0;
}
