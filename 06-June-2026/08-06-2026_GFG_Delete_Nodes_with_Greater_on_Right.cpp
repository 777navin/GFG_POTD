/*
Date: 08-06-2026
Problem Name: Delete Nodes with Greater on Right
Platform: GeeksforGeeks
Difficulty: Easy
Tags: Linked List

Problem Summary:
Given a singly linked list, remove all nodes that have a node with a greater 
value anywhere to their right in the list.

Methods to Solve:
1. Reverse List Approach (Optimal)
2. Stack/Recursion Approach

For Method 1 (Reverse List):
- Intuition: If we traverse from right to left, we can keep track of the 
  maximum value seen so far. If a current node is smaller than the max 
  seen, it needs to be deleted.
- Approach: Reverse the linked list, iterate, maintain 'maxSoFar', build 
  a new list (or modify pointers) only keeping nodes that are >= 'maxSoFar', 
  then reverse back.
- Time Complexity: O(N) where N is the number of nodes.
- Space Complexity: O(1) (excluding input space).
- Why better: It traverses the list only a few times and uses no extra data 
  structures like a stack.

Comparison Table:
Method               | TC   | SC   | Best Use Case
---------------------|------|------|-------------------------
Reverse List (Opt)   | O(N) | O(1) | Standard production code

Final Recommended Solution: Reverse List Approach
*/

/* Note: Do not redefine struct Node. 
It is already defined in the Driver code.
*/

class Solution {
public:
    // Helper function to reverse a linked list
    Node* reverse(Node* head) {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;
        while (curr != nullptr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    Node* compute(Node* head) {
        if (!head || !head->next) return head;
        
        // Step 1: Reverse the list to process from end
        head = reverse(head);

        // Step 2: Traverse and remove nodes smaller than max seen so far
        Node* curr = head;
        int maxVal = curr->data;
        Node* prev = head;
        curr = curr->next;

        while (curr != nullptr) {
            if (curr->data >= maxVal) {
                maxVal = curr->data;
                prev = curr;
                curr = curr->next;
            } else {
                // Delete node
                prev->next = curr->next;
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }

        // Step 3: Reverse the list back to original order
        return reverse(head);
    }
};
