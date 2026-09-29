#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <cmath>
#include <numeric>
#include <set>

using namespace std;

/*
 * LeetCode 2267 - 检查是否有合法括号字符串路径
 * 
 * 解法：朴素 DFS（会超时）
 * 
 * 说明：此版本为参考实现，用于理解问题和验证小规模测试用例。
 * 在大数据规模下会超时，需要使用记忆化搜索或动态规划优化。
 */
class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        row = static_cast<int>(grid.size());
        if(row == 0) return false;
        col = static_cast<int>(grid[0].size());

        this->grid = &grid;

        // 路径长度必须是偶数（左右括号数量相等）
        if(((row + col - 1) & 1) != 0) return false;
        
        // 起点必须是 '('
        if(grid[0][0] == ')') return false;

        // 从 (0, 0) 开始，初始 balance = 1
        return dfs(0, 0, 1);
    }

private:
    int row, col;
    vector<vector<char>>* grid;

    bool dfs(int i, int j, int balance)
    {
        // 剪枝 1：右括号先多了（balance < 0）
        if(balance < 0) return false;
        
        // 剪枝 2：balance 太大，剩余路径无法配对完成
        int remain = (row - 1 - i) + (col - 1 - j);
        if(balance > remain) return false;

        // 到达终点：检查括号是否恰好配对
        if(i == row - 1 && j == col - 1) return balance == 0;

        // 向右走
        if(j + 1 < col){
            int new_balance = balance + ((*grid)[i][j + 1] == '(' ? 1 : -1);
            if(dfs(i, j + 1, new_balance)) return true;
        }
        
        // 向下走
        if(i + 1 < row){
            int new_balance = balance + ((*grid)[i + 1][j] == '(' ? 1 : -1);
            if(dfs(i + 1, j, new_balance)) return true;
        }

        return false;
    }
};
