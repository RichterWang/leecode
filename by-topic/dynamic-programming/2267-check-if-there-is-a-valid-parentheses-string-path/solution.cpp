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
 * 解法：记忆化搜索（DFS + 状态缓存）
 *
 * 状态定义：(i, j, balance)
 *   - i, j    ：当前所在格子
 *   - balance ：走到该格子时未配对的左括号数量
 *
 * 关键点：到达同一个 (i, j, balance) 的不同路径，后续搜索空间完全相同，
 * 因此只需要计算一次，把结果缓存下来即可避免指数级的重复计算。
 *
 * 时间复杂度：O(m * n * (m + n))
 * 空间复杂度：O(m * n * (m + n))
 */
class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        row = static_cast<int>(grid.size());
        if(row == 0) return false;
        col = static_cast<int>(grid[0].size());
        this->grid = &grid;

        // 路径长度 = row + col - 1，必须为偶数才可能左右括号配对
        if(((row + col - 1) & 1) != 0) return false;
        // 起点必须是左括号
        if(grid[0][0] == ')') return false;

        memory.clear();  // 清空缓存
        return dfs(0, 0, 1);
    }

private:
    int col, row;
    vector<vector<char>>* grid;

    // buffer memory, 当前状态 + 状态对应的结果
    unordered_map<string, bool> memory;

    bool dfs(int i, int j, int balance)
    {
        // 剪枝 1：右括号先多了
        if(balance < 0) return false;
        // 剪枝 2：剩余步数不足以把未配对的左括号全部配对
        int remain = (row - 1 - i) + (col - 1 - j);
        if(remain < balance) return false;
        // 终点：括号恰好配完
        if(i == row - 1 && j == col - 1) return balance == 0;

        // 记忆化：状态已算过则直接复用
        string key = to_string(i) + "," + to_string(j) + "," + to_string(balance);
        if(memory.count(key)) return memory[key];

        bool result = false;
        if(j + 1 < col){
            int new_balance = balance + ((*grid)[i][j + 1] == '(' ? 1 : -1);
            if(dfs(i, j + 1, new_balance)) result = true;
        }
        if(!result && i + 1 < row){
            int new_balance = balance + ((*grid)[i + 1][j] == '(' ? 1 : -1);
            if(dfs(i + 1, j, new_balance)) result = true;
        }

        memory[key] = result;
        return result;
    }
};
