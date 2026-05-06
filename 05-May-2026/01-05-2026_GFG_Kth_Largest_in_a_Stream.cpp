/*
Date: 01-05-2026
Problem Name: Kth Largest in a Stream
Platform: GeeksforGeeks (GFG)
Difficulty: Medium
Tags: Heap, Data Streams, Priority Queue

Problem Summary:
Given an input stream of 'n' integers, find the Kth largest element after each insertion.
If the Kth largest element does not exist (i.e., total elements < k), return -1 for that insertion.
The output should be a list of size 'n' representing these values.

Methods to Solve:
1. Brute Force (Sorting after every insertion)
2. Optimal Approach (Min-Heap of size K)

-------------------------------------------------------------------------------
1. Method: Brute Force
- Intuition: Maintain a sorted list of all elements encountered so far.
- Approach: After every new element from the stream, add it to a list, sort the list in descending order, and pick the Kth element.
- Time Complexity: O(n * n log n) due to sorting 'n' times.
- Space Complexity: O(n) to store the elements.
- When to use: Never for large streams; only for very small n.

2. Method: Optimal Approach (Min-Heap)
- Intuition: We only care about the K largest elements seen so far. The smallest among these K elements is the "Kth largest" overall.
- Approach: 
    - Use a Min-Heap (priority_queue in C++) to store at most K elements.
    - For each element in the stream:
        1. Push it into the Min-Heap.
        2. If heap size exceeds K, pop the smallest element (top).
        3. If heap size is less than K, the Kth largest doesn't exist (result is -1).
        4. If heap size is exactly K, the top of the Min-Heap is the Kth largest.
- Dry Run: arr = [1, 2, 3, 4, 5, 6], k = 4
    - element 1: Heap=[1], size < 4 -> Output -1
    - element 2: Heap=[1, 2], size < 4 -> Output -1
    - element 3: Heap=[1, 2, 3], size < 4 -> Output -1
    - element 4: Heap=[1, 2, 3, 4], size=4, top=1 -> Output 1
    - element 5: Heap=[1, 2, 3, 4, 5] -> pop(1) -> Heap=[2, 3, 4, 5], top=2 -> Output 2
    - element 6: Heap=[2, 3, 4, 5, 6] -> pop(2) -> Heap=[3, 4, 5, 6], top=3 -> Output 3
- Time Complexity: O(n log k) - Each insertion/extraction in heap takes log k.
- Space Complexity: O(k) - To store K elements in the heap.
- Why better than previous: Significantly faster than sorting the entire list repeatedly.
- When to use: Standard approach for "Kth largest/smallest" in a streaming context.

-------------------------------------------------------------------------------
Comparison Table:
Method       | TC          | SC   | Best Use Case
-------------|-------------|------|-------------------------
Brute Force  | O(n^2 log n)| O(n) | Not recommended
Min-Heap     | O(n log k)  | O(k) | Large data streams

Final Recommended Solution: Min-Heap (Optimal Approach)
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
  public:
    /**
     * @brief Finds the Kth largest element in a stream of integers.
     * * @param arr The input stream of integers.
     * @param k The rank of the largest element to find.
     * @return vector<int> List containing the Kth largest element after each insertion.
     */
    vector<int> kthLargest(vector<int>& arr, int k) {
        int n = arr.size();
        // Min-heap to keep track of the top K largest elements
        priority_queue<int, vector<int>, greater<int>> minHeap;
        vector<int> result;

        for (int i = 0; i < n; i++) {
            minHeap.push(arr[i]);

            // If the heap grows larger than k, remove the smallest element.
            // This ensures the heap always contains the 'k' largest elements seen so far.
            if (minHeap.size() > k) {
                minHeap.pop();
            }

            // If we have fewer than k elements, the kth largest doesn't exist.
            if (minHeap.size() < k) {
                result.push_back(-1);
            } else {
                // The top of the min-heap is the smallest among the k largest elements,
                // which makes it the kth largest element overall.
                result.push_back(minHeap.top());
            }
        }

        return result;
    }
};

// Driver code for local testing (GFG compatible format)
int main() {
    Solution ob;
    vector<int> arr1 = {1, 2, 3, 4, 5, 6};
    int k1 = 4;
    vector<int> res1 = ob.kthLargest(arr1, k1);
    
    // Output should be: -1 -1 -1 1 2 3 
    for (int x : res1) cout << x << " ";
    cout << endl;

    return 0;
}
