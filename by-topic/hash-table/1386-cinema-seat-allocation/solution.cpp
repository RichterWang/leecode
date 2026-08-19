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
 * Daily question draft
 *
 * 使用方式：
 * 1. 先根据题目改函数名、参数列表和返回值类型
 * 2. 在 Solution 中补核心算法
 * 3. 提交到 LeetCode 时，通常只需要复制 Solution 类
 */
class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        vector<vector<bool>> map(n, vector<bool>(10, 0));
        int ans = 0;

        for(const auto& seat : reservedSeats)
        {
            int i = seat[0];
            int j = seat[1];

            map[i - 1][j - 1] = true;
        }

        // 贪心构造寻找可用区间
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                if(map[i][j] == false && j != 0 && j != 2 && j != 4 && j < 6){
                    bool signal = true;
                    for(int k = j; k < j + 4; k++)
                    {
                        if(map[i][k] == true) signal = false;
                    }
                    if(signal == true)
                    {
                        for(int k = j; k < j + 4; k++) map[i][k] = true;
                        ans ++;
                    }
                }
            }
        }

        return ans;
    }

private:

};
