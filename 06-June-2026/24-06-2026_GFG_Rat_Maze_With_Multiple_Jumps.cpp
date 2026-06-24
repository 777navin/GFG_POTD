/*
Date: 24-06-2026
Problem Name: Rat Maze With Multiple Jumps
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Backtracking, Memoization, DFS, Matrix

Problem Summary:
Given an n x n matrix where mat[i][j] represents the maximum number of steps a rat can jump 
either forward (right) or downward from that cell. Find a path from (0,0) to (n-1, n-1). 
A cell with 0 is blocked. If multiple paths exist, choose the one with the shortest 
jumps first, and for the same jump length, prefer moving right over downward. 
If no path exists, return -1.

Methods to Solve:
1. Backtracking with Memoization (DFS)
   - Intuition: Use DFS to explore paths. Memoize results to avoid redundant calculations.
   - Approach: At each cell (i, j), try jumps from 1 to mat[i][j] for both directions.
   - Time Complexity: O(N^3) - Each cell is visited and for each cell, we iterate up to N steps.
   - Space Complexity: O(N^2) - For the DP table and recursion stack.

Comparison Table:
Method | TC | SC | Best Use Case
Backtracking + Memo | O(N^3) | O(N^2) | Efficient pathfinding on grids

Final Recommended Solution: Backtracking with Memoization
*/

class Solution {
  public:
    bool solve(int i,int j,vector<vector<int>>& mat,vector<vector<int>>&ans,vector<vector<int>>&dp){
        //base case
        int n=mat[0].size();
         if(i==n-1 && j==n-1){
            ans[n-1][n-1]=1;
            return true;
        } 
        if(i>=n || j>=n || mat[i][j]==0) return false;
        
        //recursive case
        if(dp[i][j] != -1) return dp[i][j];
        ans[i][j]=1;
        int steps = mat[i][j];
        for(int k =1;k<=steps;k++){
            if (solve(i,j+k,mat,ans,dp)) return dp[i][j]=1;
            if (solve(i+k,j,mat,ans,dp)) return dp[i][j]=1;
        }
        ans[i][j]=0;
        return dp[i][j]=0;
    }
    vector<vector<int>> shortestDist(vector<vector<int>>& mat) {
        // CodeGenius
        int n= mat[0].size();
        vector<vector<int>>ans(n,vector<int>(n,0));
        vector<vector<int>>dp(n,vector<int>(n,-1));
        if(!solve(0,0,mat,ans,dp)) return {{-1}};
        return ans;
        
    }
};
