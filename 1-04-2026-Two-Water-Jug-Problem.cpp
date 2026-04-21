# Two Water Jug Problem

Solved GeeksforGeeks - Two Water Jug Problem using C++.

## Problem Statement

You are given two jugs of capacity `m` and `n` litres.

Both jugs are initially empty.

You need to measure exactly `d` litres of water using minimum number of operations.

Allowed operations:

- Fill a jug completely
- Empty a jug
- Pour water from one jug to another until one becomes empty or the other becomes full

Return the minimum number of steps required.

If it is not possible, return `-1`.

---

## Approach

### Key Idea

This problem is based on:

- `d <= max(m, n)`
- `d % gcd(m, n) == 0`

If above condition fails, answer is `-1`.

Otherwise simulate two possibilities:

1. Pour from jug `m` to jug `n`
2. Pour from jug `n` to jug `m`

Return minimum steps from both simulations.

---

## Why Efficient?

Instead of BFS over all states, mathematical simulation gives direct answer.

---

## Data Structures Used

- Euclidean Algorithm (`gcd`)
- Simulation using variables only

---

## C++ Code

```cpp
class Solution {
public:
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    int pour(int fromCap, int toCap, int d) {
        int from = fromCap, to = 0;
        int step = 1;

        while (from != d && to != d) {
            int temp = min(from, toCap - to);
            to += temp;
            from -= temp;
            step++;

            if (from == d || to == d)
                break;

            if (from == 0) {
                from = fromCap;
                step++;
            }

            if (to == toCap) {
                to = 0;
                step++;
            }
        }

        return step;
    }

    int minSteps(int m, int n, int d) {
        if (d > max(m, n))
            return -1;

        if (d % gcd(m, n) != 0)
            return -1;

        return min(pour(m, n, d), pour(n, m, d));
    }
};
