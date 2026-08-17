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
    int stoneGameV(vector<int>& stoneValue) {
        int n = static_cast<int>(stoneValue.size());

        vector<int> prefixsum(n + 1, 0);
        for(int i = 0; i < n; i++) prefixsum[i + 1] = stoneValue[i] + prefixsum[i];

        // define dp matrix
        vector<vector<int>> dp(n + 1, vector<int>(n, 0));
        for(int i = 0; i < n; i++) dp[i][i] = 0;
        for(int len = 2; len <= n; len++)
        {
            for(int left = 0; left + len - 1 < n; left++)
            {
                int right = left + len - 1;
                for(int k = left; k < right; k++)
                {
                    int leftSum = prefixsum[k + 1] - prefixsum[left];
                    int rightSum = prefixsum[right + 1] - prefixsum[k + 1];

                    if (leftSum < rightSum) {
                        dp[left][right] = max(dp[left][right], leftSum + dp[left][k]);
                    } else if (leftSum > rightSum) {
                        dp[left][right] = max(dp[left][right], rightSum + dp[k + 1][right]);
                    } else {
                        dp[left][right] = max(dp[left][right], leftSum + max(dp[left][k], dp[k + 1][right]));
                    }
                }
            }
        }
        
        return dp[0][n - 1];
    }

private:

};
