/*
Problem Statement:
You are given a 0-indexed m x n matrix grid consisting of positive integers.

You can start at any cell in the first column of the matrix, and traverse the grid in the following way:

From a cell (row, col), you can move to any of the cells: (row - 1, col + 1), (row, col + 1) and (row + 1, col + 1) such that the value of the cell you move to, should be strictly bigger than the value of the current cell.
Return the maximum number of moves that you can perform.

Example 1:

Input: grid = [[2,4,3,5],[5,4,9,3],[3,4,2,11],[10,9,13,15]]
Output: 3
Explanation: We can start at the cell (0, 0) and make the following moves:
- (0, 0) -> (0, 1).
- (0, 1) -> (1, 2).
- (1, 2) -> (2, 3).
It can be shown that it is the maximum number of moves that can be made.

Example 2:

Input: grid = [[3,2,4],[2,1,9],[1,1,7]]
Output: 0
Explanation: Starting from any cell in the first column we cannot perform any moves.


Constraints:

m == grid.length
n == grid[i].length
2 <= m, n <= 1000
4 <= m * n <= 105
1 <= grid[i][j] <= 106

*/

#include<iostream>
#include<vector>
using namespace std;


int maxMovesHelper(int i, int j, vector<vector<int>>& grid, vector<vector<int>>& dp){
	int n = grid.size();
	int m = grid[0].size();
	if(j == m){
		//if I reached last column then i can't go further
		return 0;
	}

	//If result already calculated for state (i, j)
	if(dp[i][j] != -1) return dp[i][j];

	//for each cell we have 3 options:
	//1.i-1, j+1
	//2.i, j+1
	//3.i+1, j+1
	int res = 0;
	if(j+1<m){
		if(i-1>=0 && grid[i-1][j+1] > grid[i][j]){
			//if right top neighbour i.e. (i-1, j+1) exists and is greater than current cell
			res = max(res, 1 + maxMovesHelper(i-1,j+1, grid, dp));
		}
		
		if(grid[i][j+1] > grid[i][j]){
			//if right neighbour i.e. (i, j+1) exists and is greater than current cell
			res = max(res, 1 + maxMovesHelper(i,j+1, grid, dp));
		}
		
		if(i+1 < n && grid[i+1][j+1] > grid[i][j]){
			//if right bottom neighbour i.e. (i+1, j+1) exists and is greater than current cell
			res = max(res, 1 + maxMovesHelper(i+1, j+1, grid, dp));
		}
	}

	//store the result
	return dp[i][j] = res;
}

int maxMoves(vector<vector<int>> &grid){
	int n = grid.size();
	int m = grid[0].size();
	int ans = 0;
	int j = 0;
	
	vector<vector<int>> dp(n, vector<int>(m,-1));
	
	for(int i = 0; i < n; i++){
		ans = max(maxMovesHelper(i, j, grid, dp), ans);
	}
	
	return ans;
}

int main(){
	int n,m;
	cin >> n >> m;
	vector<vector<int>> grid(n, vector<int>(m));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			cin >> grid[i][j];
		}
	}
	
	int ans = maxMoves(grid);
	cout << ans;
	
	return 0;
}

/*
Sample input:
4 4
2 4 3 5
5 4 9 3
3 4 2 11
10 9 13 15

Sample output:
3
*/
