// 09-05-2026_Codeforces_Boy_or_Girl.cpp

/*
Date: 09-05-2026
Problem Name: Boy or Girl (236A)
Platform: Codeforces
Difficulty: 800
Tags: Strings, Implementation, Hashing, Sorting

Problem Summary:
Determine the gender of a user based on their username. 
- If the number of distinct characters in the username is odd, it's a male ("IGNORE HIM!").
- If the number of distinct characters is even, it's a female ("CHAT WITH HER!").
The input is a single string of lowercase English letters (up to 100 characters).

Methods to Solve:
1. Brute Force (Sorting)
2. Optimal Approach (Hash Set)
3. Extra Approach (Frequency Array / Boolean Array)

-------------------------------------------------------------------------------
Method 1: Brute Force (Sorting)
- Intuition: If we sort the string, all identical characters will be adjacent. We can then easily count the unique characters by iterating through the string and comparing each character with the previous one.
- Approach: Read the string, apply `std::sort`, loop through and increment a counter whenever `s[i] != s[i-1]`.
- Dry Run (small example): "wjmzbmr" -> sorted: "bjjmmrw". Count changes at 'j', 'm', 'r', 'w'. Unique count = 6. Even -> "CHAT WITH HER!".
- Time Complexity: O(N log N) due to the sorting step.
- Space Complexity: O(1) or O(log N) depending on the sorting algorithm overhead.
- Why better than previous method: N/A (Baseline).
- When to use: When you want to avoid extra space and don't mind modifying the original string.

-------------------------------------------------------------------------------
Method 2: Optimal Approach (Hash Set)
- Intuition: A Set data structure automatically handles duplicates and only stores unique elements.
- Approach: Insert all characters of the string into a `std::unordered_set`. The size of the set directly gives the number of distinct characters. Check if the size is even or odd.
- Dry Run (small example): "xiaodao" -> set gets {'x', 'i', 'a', 'o', 'd'}. Size = 5 (odd). Output -> "IGNORE HIM!".
- Time Complexity: O(N) where N is the length of the string, as insertion into an unordered_set takes O(1) on average.
- Space Complexity: O(K) where K is the number of distinct characters (max 26 for lowercase English letters). Effectively O(1).
- Why better than previous method: Faster execution time compared to sorting.
- When to use: General string character deduplication tasks where order doesn't matter.

-------------------------------------------------------------------------------
Method 3: Extra Approach (Boolean Frequency Array)
- Intuition: Since the string only contains lowercase English letters, there are only 26 possible distinct characters. 
- Approach: Create a boolean array of size 26 initialized to `false`. Iterate through the string, mapping each char to an index (0-25) using `s[i] - 'a'`, and mark it `true`. Count the `true` values.
- Time Complexity: O(N) to traverse the string.
- Space Complexity: O(1) as the array size is always strictly 26.
- Why better than previous method: Slightly lower overhead constant than `std::unordered_set` operations.

Comparison Table:
Method                    | TC         | SC   | Best Use Case
--------------------------------------------------------------------------
1. Sorting                | O(N log N) | O(1) | Memory constrained environments where string mutation is allowed.
2. Hash Set               | O(N)       | O(1) | Standard competitive programming; cleanest and shortest code.
3. Boolean Array          | O(N)       | O(1) | Maximum performance optimization avoiding hashing overhead.

Final Recommended Solution: Method 2 (Hash Set) for its clean, concise, and modern C++ idiomatic style.
*/

#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm> // FIXED: Required for std::sort

using namespace std;

// Method 1: Sorting approach (For reference)
void solve_sorting() {
    string s;
    cin >> s;
    
    // Edge case for empty string
    if (s.empty()) return;
    
    sort(s.begin(), s.end());
    int distinct_count = 1; // First character is always unique
    
    // FIXED: Changed 'int' to 'size_t' to avoid signed/unsigned comparison warning
    for (size_t i = 1; i < s.length(); ++i) {
        if (s[i] != s[i - 1]) {
            distinct_count++;
        }
    }
    
    if (distinct_count % 2 == 0) {
        cout << "CHAT WITH HER!\n";
    } else {
        cout << "IGNORE HIM!\n";
    }
}

// Method 3: Boolean array approach (For reference)
void solve_bool_array() {
    string s;
    cin >> s;
    
    bool seen[26] = {false};
    int distinct_count = 0;
    
    for (char c : s) {
        if (!seen[c - 'a']) {
            seen[c - 'a'] = true;
            distinct_count++;
        }
    }
    
    if (distinct_count % 2 == 0) {
        cout << "CHAT WITH HER!\n";
    } else {
        cout << "IGNORE HIM!\n";
    }
}

// Method 2: Optimal Hash Set Approach (Main execution)
void solve() {
    string s;
    cin >> s;
    
    // Initialize an unordered_set using range constructor
    unordered_set<char> distinct_chars(s.begin(), s.end());
    
    // Check parity of the number of distinct characters
    if (distinct_chars.size() % 2 == 0) {
        cout << "CHAT WITH HER!\n";
    } else {
        cout << "IGNORE HIM!\n";
    }
}

int main() {
    // Fast I/O for Competitive Programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Call the optimal solution
    solve();
    
    return 0;
}09-05-2026_Codeforces_Boy_or_Girl.cpp
