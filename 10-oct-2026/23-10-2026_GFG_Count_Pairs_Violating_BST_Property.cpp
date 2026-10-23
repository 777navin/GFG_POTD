/*
=========================================================
Date        : 23-10-2026
Problem Name: Count Pairs Violating BST Property
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Binary Tree, BST, Inorder Traversal,
              Merge Sort, Inversion Count

Problem Summary:
- Given a binary tree, count pairs of nodes violating
  the Binary Search Tree (BST) ordering property.
- An inorder traversal converts the tree into an array.
- Count inversions in this array to find the violations.

Key Observation:
- A valid BST has a strictly increasing inorder traversal.
- Every inversion (i < j and arr[i] > arr[j]) represents
  a pair violating the BST property.
=========================================================

APPROACH 1: BRUTE FORCE

- Intuition:
  An inorder traversal of a valid BST must be sorted.
- Approach:
  Store inorder values and check every pair (i, j).
- Why it Works:
  Each pair where arr[i] > arr[j] is an inversion.
- TC: O(N^2)
- SC: O(N)

APPROACH 2: BETTER — ORDERED DATA STRUCTURE

- Intuition:
  Count previously encountered values greater than
  the current value.
- Approach:
  Use an order-statistics tree (PBDS) to count inversions.
- Why it Works:
  The data structure efficiently tracks sorted values.
- TC: O(N log N)
- SC: O(N)

APPROACH 3: OPTIMIZED — MERGE SORT

- Intuition:
  Merge sort counts inversions while sorting the array.
- Approach:
  During merging, if arr[i] > arr[j], all remaining
  elements in the left half form inversions with arr[j].
- Why it Works:
  Every inversion is counted exactly once.
- TC: O(N log N)
- SC: O(N)

FINAL APPROACH:
- Use inorder traversal followed by merge-sort inversion counting.
- Unlike brute force, it avoids checking every pair individually.
- Unlike PBDS, it uses standard C++17 without compiler extensions.
- Use long long internally to avoid overflow in the inversion count.
- Return the count using the GFG-required int return type.
*/

class Solution {
private:
    void inorder(Node* root, vector<int>& values) {
        if (root == nullptr) {
            return;
        }

        inorder(root->left, values);
        values.push_back(root->data);
        inorder(root->right, values);
    }

    long long mergeAndCount(
        vector<int>& values,
        vector<int>& temp,
        int left,
        int mid,
        int right
    ) {
        int i = left;
        int j = mid + 1;
        int k = left;

        long long inversions = 0;

        while (i <= mid && j <= right) {
            if (values[i] <= values[j]) {
                temp[k++] = values[i++];
            } else {
                temp[k++] = values[j++];

                // All remaining elements in the left half
                // are greater than values[j - 1].
                inversions += (mid - i + 1LL);
            }
        }

        while (i <= mid) {
            temp[k++] = values[i++];
        }

        while (j <= right) {
            temp[k++] = values[j++];
        }

        for (int index = left; index <= right; ++index) {
            values[index] = temp[index];
        }

        return inversions;
    }

    long long mergeSort(
        vector<int>& values,
        vector<int>& temp,
        int left,
        int right
    ) {
        if (left >= right) {
            return 0;
        }

        int mid = left + (right - left) / 2;

        long long inversions = 0;

        inversions += mergeSort(values, temp, left, mid);
        inversions += mergeSort(values, temp, mid + 1, right);
        inversions += mergeAndCount(values, temp, left, mid, right);

        return inversions;
    }

public:
    int pairsViolatingBST(Node* root) {
        vector<int> values;
        inorder(root, values);

        int n = static_cast<int>(values.size());

        if (n <= 1) {
            return 0;
        }

        vector<int> temp(n);

        long long answer = mergeSort(values, temp, 0, n - 1);

        return static_cast<int>(answer);
    }
};
