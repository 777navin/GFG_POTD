class Solution {
public:
    int cntSubsets(vector<int>& arr, int l, int r) {

        const long long MOD = 1000000007LL;
        int n = arr.size();

        vector<int> freq(n + 1, 0);

        for (int x : arr) {
            freq[x]++;
        }

        vector<long long> pow2(n + 1, 1);

        for (int i = 1; i <= n; i++) {
            pow2[i] = (pow2[i - 1] * 2) % MOD;
        }

        long long ans = 0;
        long long required = 1;
        int prefixFreq = 0;

        for (int k = 0; k <= r; k++) {

            int greaterCount = n - prefixFreq - freq[k];

            if (k >= l) {
                long long ways = (required * pow2[greaterCount]) % MOD;
                ans = (ans + ways) % MOD;
            }

            if (freq[k] == 0) {
                break;
            }

            long long choices = (pow2[freq[k]] - 1 + MOD) % MOD;

            required = (required * choices) % MOD;

            prefixFreq += freq[k];
        }

        return (int)ans;
    }
};
