class Solution {
public:
    int minTime(int n, int s1, int s2) {

        long long total = n;
        long long a = s1;
        long long b = s2;

        long long numerator = total * b;
        long long denominator = a + b;

        long long x1 = numerator / denominator;
        long long x2 = (numerator + denominator - 1) / denominator;

        long long time1 = max(x1 * a, (total - x1) * b);
        long long time2 = max(x2 * a, (total - x2) * b);

        return (int)min(time1, time2);
    }
};
