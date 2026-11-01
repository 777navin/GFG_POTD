class Solution {
public:
    int maximumSubarray(vector<int>& arr) {

        int noSq = arr[0];
        int withSq = arr[0] * arr[0];

        int ans = max(noSq, withSq);

        for (int i = 1; i < arr.size(); i++) {

            int x = arr[i];

            int newNoSq = max(x, noSq + x);

            int newWithSq = max({
                x * x,
                noSq + x * x,
                withSq + x
            });

            noSq = newNoSq;
            withSq = newWithSq;

            ans = max({ans, noSq, withSq});
        }

        return ans;
    }
};
