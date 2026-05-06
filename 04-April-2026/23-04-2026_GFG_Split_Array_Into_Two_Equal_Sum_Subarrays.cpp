/*
File Name: 23-04-2026_GFG_Split_Array_Into_Two_Equal_Sum_Subarrays.cpp

Reason of Error:
Driver code expects function name:

bool canSplit(vector<int>& arr)

But previous mismatch may happen on platform.
Using exact required signature now.
*/

class Solution {
public:
    bool canSplit(vector<int>& arr) {
        long long totalSum = 0;

        for (int x : arr)
            totalSum += x;

        long long prefixSum = 0;

        // split into two non-empty subarrays
        for (int i = 0; i < (int)arr.size() - 1; i++) {
            prefixSum += arr[i];

            if (prefixSum == totalSum - prefixSum)
                return true;
        }

        return false;
    }
};
