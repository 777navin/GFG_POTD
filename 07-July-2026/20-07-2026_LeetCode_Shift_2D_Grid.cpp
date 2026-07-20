/*
=========================================================
Date        : 20-07-2026
Problem Name: Shortest Unique Prefix for Every Word
Platform    : GeeksforGeeks (GFG)
Difficulty  : Hard
Tags        : Trie, Data Structures, Strings

Problem Summary:
Given an array of strings, find the shortest prefix of each string that 
uniquely identifies it among all strings in the array. A prefix is unique 
if it is not a prefix of any other string in the array.

Key Observation:
A Trie data structure can track the frequency of prefixes. The shortest unique 
prefix for any word is determined by traversing the Trie until we hit a node 
with a frequency of 1.
=========================================================
*/

// =========================================================
// APPROACH 1: Trie-Based Frequency Tracking (Optimized & Standard)
// =========================================================
// • Intuition: 
//   By inserting all words into a Trie, we can maintain a frequency count 
//   at each node representing how many words share that prefix.
// • Approach: 
//   1. Define a Trie node containing a frequency counter and a child array.
//   2. Insert all words, incrementing the frequency of each character node.
//   3. Traverse the Trie for each word and stop as soon as a node with a frequency of 1 is reached.
// • Why it Works: 
//   A frequency of 1 guarantees that no other word in the input array shares 
//   this prefix, making it the shortest unique prefix.
// • Time Complexity (TC): 
//   O(N * L) where N is the number of words and L is the maximum length of a word.
// • Space Complexity (SC): 
//   O(N * L * 26) to store the characters in the Trie structure.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Trie Node Definition
struct TrieNode {
    int freq;
    TrieNode* child[26];
    
    TrieNode() {
        freq = 0;
        for (int i = 0; i < 26; i++) {
            child[i] = nullptr;
        }
    }
};

class Solution {
private:
    // Insert a word into the Trie and update frequencies
    void insert(TrieNode* root, const string& word) {
        TrieNode* curr = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (!curr->child[idx]) {
                curr->child[idx] = new TrieNode();
            }
            curr = curr->child[idx];
            curr->freq++;
        }
    }

    // Find the shortest unique prefix for a given word
    string getUniquePrefix(TrieNode* root, const string& word) {
        TrieNode* curr = root;
        string prefix = "";
        for (char ch : word) {
            prefix += ch;
            int idx = ch - 'a';
            curr = curr->child[idx];
            if (curr->freq == 1) {
                break;
            }
        }
        return prefix;
    }

public:
    /*
    =========================================================
    FINAL APPROACH CHOICE:
    This Trie approach is selected because it efficiently resolves prefix clashes 
    in linear time relative to the total number of characters. It avoids 
    the O(N^2 * L) brute-force string comparisons, optimizing both performance 
    and clarity to meet constraints comfortably.
    =========================================================
    */
    vector<string> findPrefixes(vector<string>& arr) {
        TrieNode* root = new TrieNode();
        
        // Step 1: Build the Trie
        for (const string& word : arr) {
            insert(root, word);
        }
        
        // Step 2: Find prefixes for each word
        vector<string> result;
        for (const string& word : arr) {
            result.push_back(getUniquePrefix(root, word));
        }
        
        // Optional: Memory cleanup could be added here if required, 
        // but skipped for pure competitive programming performance.
        return result;
    }
};
