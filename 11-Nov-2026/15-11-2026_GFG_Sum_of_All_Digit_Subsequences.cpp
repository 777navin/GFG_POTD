#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, s;
    if (!(cin >> n >> s)) return;

    int total_sum = 0;
    int max_mug = 0;

    for (int i = 0; i < n; ++i) {
        int volume;
        cin >> volume;
        total_sum += volume;
        max_mug = max(max_mug, volume);
    }

    // Check if the sum of the smallest (n - 1) mugs fits in the cup
    if (total_sum - max_mug <= s) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
