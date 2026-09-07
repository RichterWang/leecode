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
#include <functional>
#include <array>

using namespace std;

/*
 * Daily question draft
 *
 * 使用方式：
 * 1. 先根据题目改函数名、参数列表和返回值类型
 * 2. 在 Solution 中补核心算法
 * 3. 提交到 LeetCode 时，通常只需要复制 Solution 类
 */
class Solution {
public:
    array<pair<int, int>, 4> moving = {{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};

    bool exist(vector<vector<char>>& board, string word) {
        int row = static_cast<int>(board.size());
        if(row == 0) return false;
        int col = static_cast<int>(board[0].size());
        if(col == 0) return false;
        vector<pair<int, int>> init;
        vector<vector<bool>> visited(row, vector<bool>(col, false));
        if(word.empty()) return true;

        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < col; j++)
            {
                if(board[i][j] == word[0] && dfs(i, j, board, word, 0, visited)) return true;
            }
        }

        return false;
    }

private:
    bool dfs(int x, int y, vector<vector<char>>& board, string& word, int ptr, vector<vector<bool>>& visited)
    {
        if(board[x][y] == word[ptr]) {
            if(ptr == static_cast<int>(word.size()) - 1) return true;
            
            visited[x][y] = true;

            int row = static_cast<int>(board.size());
            int col = static_cast<int>(board[0].size());

            for(const auto& [dx, dy] : moving)
            {
                int nextX = x + dx;
                int nextY = y + dy;

                if (nextX < 0 || nextX >= row || nextY < 0 || nextY >= col) continue;
                if(visited[nextX][nextY]) continue;
                if(dfs(nextX, nextY, board, word, ptr + 1, visited)) {
                    visited[x][y] = false;
                    return true;
                }
            }
            visited[x][y] = false;
            return false;
        }
        else return false;
    }
};

/* leecode79 单词搜索

*/
