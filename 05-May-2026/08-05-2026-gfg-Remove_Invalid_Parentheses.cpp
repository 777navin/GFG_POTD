/*
Date: 08-05-2026
Problem Name: Remove Invalid Parentheses
Platform: GeeksforGeeks
Difficulty: Hard
Tags: Strings, Backtracking, Breadth-First Search (BFS)

Problem Summary
Given a string `s` consisting of lowercase letters and parentheses '(' and ')'.
Remove the minimum number of invalid parentheses from `s` so that the resulting string becomes valid. 
Return all possible distinct valid strings in lexicographically sorted order.

Methods to Solve:
1. Breadth-First Search (BFS)
2. Backtracking / Depth-First Search (Optimal)

===================================================================================
Method 1: Breadth-First Search (BFS)
===================================================================================
- Intuition: 
  BFS is naturally suited for finding the "shortest path" or the "minimum" number of 
  removals. By removing one character at a time and exploring level by level, the first 
  level that produces a valid string guarantees that we have made the minimum removals.

- Approach:
  1. Push the initial string into a queue and mark it visited using a hash set.
  2. For each level, process all strings. If a string is valid, add it to the result 
     list and set a flag `found` to true.
  3. If `found` is true, we do not enqueue any more substrings for the next level 
     (since we only want the minimum removals).
  4. If not valid, generate all possible states by removing one parenthesis at a time, 
     and enqueue them if they haven't been visited.
  5. Sort the final result to return lexicographically.

- Dry Run: s = "()())()"
  Level 0: "()())()" -> Not valid.
  Level 1: Remove one character at a time:
  - Remove index 4: "(())()" -> Valid!
  - Remove index 5: "()()()" -> Valid!
  We stop generating further levels because we found valid strings.

- Time Complexity: O(2^N) in the worst case, where N is the length of the string, as we 
  might generate all subsets of the string.
- Space Complexity: O(2^N) to store the combinations in the queue and visited set.
- Why better than previous method: N/A (Standard baseline approach).
- When to use: When you want a simpler implementation to guarantee the shortest path of removals.

===================================================================================
Method 2: Backtracking / Depth-First Search (Optimal Approach)
===================================================================================
- Intuition: 
  Instead of blindly generating all sub-states, we can first count exactly how many left 
  and right parentheses are misplaced. We then use backtracking to specifically remove 
  only that exact number of invalid parentheses, heavily pruning the recursion tree.

- Approach:
  1. Traverse the string to count the minimum number of misplaced left (`left_rem`) and 
     right (`right_rem`) parentheses.
  2. Use a DFS backtracking function that attempts to remove characters.
  3. Base case: If `left_rem == 0` and `right_rem == 0`, check if the string is valid.
  4. Pruning: To avoid duplicates, skip identical consecutive characters `if (i != index && s[i] == s[i - 1]) continue;`.
  5. Recurse, decrementing `left_rem` or `right_rem` based on the character removed.
  6. Sort the final collected results.

- Dry Run: s = "()())()"
  1. Count misplaced: `left_rem` = 0, `right_rem` = 1.
  2. DFS starts. We only look for ')' to remove.
  3. Removing 1st ')' -> "())()" -> Invalid.
  4. Removing 2nd ')' -> "(())()" -> Valid!
  5. Removing 3rd ')' -> "()()()" -> Valid!
  DFS successfully avoids evaluating completely unrelated branches.

- Time Complexity: O(2^N) worst-case time complexity, but highly optimized due to strict pruning.
- Space Complexity: O(N) auxiliary stack space for the recursion depth.
- Why better than previous method: Drastically reduces the search space compared to BFS, saving both time and memory overhead.
- When to use: When maximum efficiency is needed, particularly for competitive programming or harder test cases.

===================================================================================
Comparison Table:
Method       | TC      | SC      | Best Use Case
-----------------------------------------------------------------------------------
BFS          | O(2^N)  | O(2^N)  | Shortest path intuition, easy to trace levels.
Backtracking | O(2^N)  | O(N)    | Optimal space usage and fast execution via pruning.

Final Recommended Solution: Backtracking / Depth-First Search
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Helper function to check if a string of parentheses is perfectly valid
    bool isValid(const string& s) {
        int balance = 0;
        for (char c : s) {
            if (c == '(') {
                balance++;
            } else if (c == ')') {
                balance--;
            }
            if (balance < 0) {
                return false;
            }
        }
        return balance == 0;
    }

    // Backtracking function
    void dfs(string s, int index, int left_rem, int right_rem, vector<string>& result) {
        // Base Condition: We've removed the required number of parentheses
        if (left_rem == 0 && right_rem == 0) {
            if (isValid(s)) {
                result.push_back(s);
            }
            return;
        }

        for (int i = index; i < s.length(); ++i) {
            // Pruning 1: Skip duplicates to avoid duplicate identical string outcomes
            if (i != index && s[i] == s[i - 1]) continue;

            // Pruning 2 & Recursive calls
            if (s[i] == '(' && left_rem > 0) {
                // Erase character and recurse
                dfs(s.substr(0, i) + s.substr(i + 1), i, left_rem - 1, right_rem, result);
            } else if (s[i] == ')' && right_rem > 0) {
                // Erase character and recurse
                dfs(s.substr(0, i) + s.substr(i + 1), i, left_rem, right_rem - 1, result);
            }
        }
    }

public:
    vector<string> validParenthesis(string &s) {
        int left_rem = 0, right_rem = 0;

        // Step 1: Calculate the minimum number of misplaced left and right parentheses
        for (char c : s) {
            if (c == '(') {
                left_rem++;
            } else if (c == ')') {
                if (left_rem == 0) {
                    right_rem++;
                } else {
                    left_rem--;
                }
            }
        }

        vector<string> result;
        
        // Step 2: DFS to gather all valid expressions
        dfs(s, 0, left_rem, right_rem, result);

        // Step 3: GFG constraint requires output in lexicographically sorted order
        sort(result.begin(), result.end());

        return result;
    }
};

// ==========================================
// Driver Code (Maintained for Local Run)
// ==========================================
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            string s;
            cin >> s;
            
            Solution obj;
            vector<string> ans = obj.validParenthesis(s);
            
            for (const string& str : ans) {
                cout << str << "\n";
            }
            if (ans.empty()) {
                cout << "\n";
            }
        }
    } else {
        // Fallback for custom testing
        Solution obj;
        string s = "()())()";
        cout << "Input: " << s << "\nOutput:\n";
        vector<string> ans = obj.validParenthesis(s);
        for (const string& str : ans) {
            cout << str << "\n";
        }
    }

    return 0;
}
