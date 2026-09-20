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

using namespace std;

/*
 * LeetCode 51. N 皇后问题
 * 
 * 按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
 * n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
 * 给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
 * 每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。
 */
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> answer;
        vector<string> board(n, string(n, '.')); // 初始化棋盘

        unordered_set<int> cols; // 占用列统计
        unordered_set<int> diag1; // 占用主对角线统计
        unordered_set<int> diag2; // 占用副对角线统计

        function<void(int)> backtrace = [&](int row){
            if(row == n){
                answer.push_back(board);
                return;
            }

            for(int col = 0; col < n; col++)
            {
                int d1 = row - col; // 主对角线
                int d2 = row + col; // 副对角线

                if(cols.count(col) || diag1.count(d1) || diag2.count(d2)) continue;

                board[row][col] = 'Q';
                cols.insert(col);
                diag1.insert(d1);
                diag2.insert(d2);

                backtrace(row + 1);
                board[row][col] = '.';
                cols.erase(col);
                diag1.erase(d1);
                diag2.erase(d2);
            }
        };

        backtrace(0);
        return answer;
    }
private:

};
