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
 * Optimized solution using hash map
 *
 * 使用方式：
 * 1. 先根据题目改函数名、参数列表和返回值类型
 * 2. 在 Solution 中补核心算法
 * 3. 提交到 LeetCode 时，通常只需要复制 Solution 类
 */
class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, vector<bool>> rowMap;

        // 初始化有预订的行
        for (const auto& seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            if (rowMap.find(row) == rowMap.end()) {
                rowMap[row] = vector<bool>(10, false);
            }
            rowMap[row][col - 1] = true;
        }

        int ans = 0;

        // 先计算有预订的行
        for (auto& [row, seats] : rowMap) {
            for (int j : {1, 3, 5}) {
                bool canPlace = true;
                for (int k = j; k < j + 4; k++) {
                    if (seats[k]) {
                        canPlace = false;
                        break;
                    }
                }
                if (canPlace) {
                    for (int k = j; k < j + 4; k++) {
                        seats[k] = true;
                    }
                    ans++;
                }
            }
        }

        // 剩下的空行，每行可以放 2 组
        int emptyRows = n - rowMap.size();
        ans += emptyRows * 2;

        return ans;
    }

private:

};
