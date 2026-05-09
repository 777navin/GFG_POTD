/*
Date: 09-05-2026
Problem Name: Count Spanning Trees in a Graph
Platform: GeeksforGeeks
Difficulty: Hard
Tags: Graph, Matrix, Determinant, Math, Kirchhoff's Theorem

Problem Summary: 
Given a connected undirected graph with 'n' vertices and 'm' edges, calculate the total number of distinct spanning trees that can be formed from the graph.

Methods to Solve:
1. Brute Force (Edge Combinations)
2. Optimal Approach: Kirchhoff's Matrix Tree Theorem

--------------------------------------------------------------------------
Method 1: Brute Force (Edge Combinations)
- Intuition: 
  A spanning tree must have exactly (n-1) edges. We can generate all possible combinations of (n-1) edges out of the 'm' given edges and check if they form a valid tree (i.e., are connected and contain no cycles).
- Approach:
  1. Generate all combinations of m edges taken (n-1) at a time.
  2. For each combination, use Disjoint Set Union (DSU) or Depth First Search (DFS) to verify if the selected edges connect all 'n' vertices without forming a cycle.
  3. Count all valid configurations.
- Time Complexity: O(C(m, n-1) * alpha(n)) where C is the binomial coefficient. This grows exponentially and will quickly cause a Time Limit Exceeded (TLE) error for larger graphs.
- Space Complexity: O(n) for DSU or DFS data structures.
- Why better than previous method: N/A (Baseline approach).
- When to use: Strictly for very small graphs where m is close to n.

--------------------------------------------------------------------------
Method 2: Optimal Approach: Kirchhoff's Matrix Tree Theorem
- Intuition: 
  Kirchhoff's theorem provides an elegant algebraic way to find the exact number of spanning trees in any general graph. The theorem states that the number of spanning trees is equal to any cofactor of its Laplacian matrix.
  The Laplacian matrix (L) is defined as L = D - A, where:
  - D is the Degree matrix (a diagonal matrix where D[i][i] is the degree of vertex i).
  - A is the Adjacency matrix (A[i][j] = 1 if an edge exists between i and j, else 0).
- Approach:
  1. Construct a 2D array of size n x n initialized to 0 to act as our Laplacian matrix.
  2. Traverse the given edges: for an edge between u and v, increment the diagonal elements L[u][u] and L[v][v] (degree), and set L[u][v] = -1 and L[v][u] = -1 (adjacency).
  3. Create a submatrix by removing the 1st row (index 0) and 1st column (index 0) from L. This gives an (n-1) x (n-1) matrix.
  4. The determinant of this submatrix is the total number of spanning trees.
  5. Given the constraint n <= 10, the submatrix will be at most 9x9. We can safely and quickly compute its determinant using cofactor expansion (recursive approach).
- Dry Run (small example):
  n = 3, edges = [[0, 1], [0, 2], [1, 2]]
  Degree Matrix (D):
  [2, 0, 0]
  [0, 2, 0]
  [0, 0, 2]
  Adjacency Matrix (A):
  [0, 1, 1]
  [1, 0, 1]
  [1, 1, 0]
  Laplacian Matrix (L = D - A):
  [ 2, -1, -1]
  [-1,  2, -1]
  [-1, -1,  2]
  Remove row 0, col 0 -> Submatrix:
  [ 2, -1]
  [-1,  2]
  Determinant = (2*2) - (-1*-1) = 4 - 1 = 3. Output: 3.
- Time Complexity: O((N-1)!) for the recursive determinant calculation. Given N <= 10, the maximum number of operations is 9! = 362,880, which executes in a fraction of a millisecond. 
- Space Complexity: O(N^2) to store the Laplacian matrix and auxiliary submatrices during recursion.
- Why better than previous method: It runs in factorial time bounded by a small constant (N<=10) instead of exploding based on the number of edges combinations.
- When to use: Ideal for finding exact numbers of spanning trees, especially useful when N is small enough to avoid precision/overflow issues with floating-point matrix operations or complex integer arithmetic.

Comparison Table:
Method                             | TC             | SC     | Best Use Case
-----------------------------------|----------------|--------|--------------------------------
Brute Force                        | O(C(m,n)*a(n)) | O(n)   | Never, unless m is extremely small.
Kirchhoff's Matrix Tree Theorem    | O(N!)          | O(N^2) | Best fit for the constraints provided (N <= 10).

Final Recommended Solution: Method 2 (Kirchhoff's Matrix Tree Theorem)
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    // Helper function to calculate the determinant of an NxN matrix using cofactor expansion
    int calculateDeterminant(vector<vector<int>>& mat, int n) {
        // Base Cases
        if (n == 1) {
            return mat[0][0];
        }
        if (n == 2) {
            return (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
        }

        int det = 0;
        int sign = 1;

        // Iterate through the first row to calculate cofactors
        for (int f = 0; f < n; f++) {
            vector<vector<int>> subMatrix(n - 1, vector<int>(n - 1));
            int sub_i = 0, sub_j = 0;

            // Fill the submatrix by excluding the 0th row and f-th column
            for (int row = 1; row < n; row++) {
                for (int col = 0; col < n; col++) {
                    if (col == f) continue; // Skip the column of the current pivot

                    subMatrix[sub_i][sub_j++] = mat[row][col];
                    if (sub_j == n - 1) {
                        sub_j = 0;
                        sub_i++;
                    }
                }
            }

            // Accumulate the determinant
            det += sign * mat[0][f] * calculateDeterminant(subMatrix, n - 1);
            sign = -sign; // Alternate signs for the cofactor expansion (+ - + -)
        }

        return det;
    }

public:
    int countSpanTree(int n, vector<vector<int>>& edges) {
        // A single vertex is effectively its own spanning tree with 0 edges.
        if (n == 1) return 1;

        // Create the Laplacian Matrix (N x N) initialized to 0
        vector<vector<int>> laplacian(n, vector<int>(n, 0));

        // Populate the Laplacian matrix: L = D - A
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            // Add degrees to the diagonal (Degree Matrix component)
            laplacian[u][u]++;
            laplacian[v][v]++;

            // Subtract 1 for connected edges (Adjacency Matrix component)
            laplacian[u][v] = -1;
            laplacian[v][u] = -1;
        }

        // Create an (N-1) x (N-1) submatrix by removing the 0th row and 0th column
        vector<vector<int>> cofactorSubMatrix(n - 1, vector<int>(n - 1));
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                cofactorSubMatrix[i - 1][j - 1] = laplacian[i][j];
            }
        }

        // The determinant of this submatrix equals the number of spanning trees
        return calculateDeterminant(cofactorSubMatrix, n - 1);
    }
};

// ==========================================
// Driver Code for Local Execution
// ==========================================
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cout << "Enter number of test cases: ";
    if (!(cin >> t)) return 0;

    while (t--) {
        int n, m;
        cout << "Enter number of vertices (n) and edges (m): ";
        cin >> n >> m;

        vector<vector<int>> edges(m, vector<int>(2));
        cout << "Enter the edges (u v): \n";
        for (int i = 0; i < m; i++) {
            cin >> edges[i][0] >> edges[i][1];
        }

        Solution obj;
        int ans = obj.countSpanTree(n, edges);
        
        cout << "Total distinct spanning trees: " << ans << "\n";
        cout << "--------------------------------------\n";
    }

    return 0;
}
