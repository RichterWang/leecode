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
 * LeetCode 3524. 求出数组的 X 值 I
 * 
 * 方法：双层循环暴力枚举
 * 
 * 思路：
 * - 枚举所有可能的子数组 [left, right]
 * - 每个子数组对应一种"移除前缀和后缀"的操作
 * - 直接计算子数组元素乘积对 k 取模
 * 
 * 优点：
 * - 逻辑简单清晰
 * - 避免了除法在模运算中的问题
 * - 边乘边取模防止溢出
 * 
 * 缺点：
 * - 时间复杂度 O(n²)，对于大数据量会超时
 */
class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        vector<long long> answer(k, 0);
        
        // 以位置i结尾，尾数为j的子数组数量
        vector<vector<long long>> dp(n, vector<long long>(k, 0));

        // 初始化
        dp[0][nums[0] % k] = 1;
        answer[nums[0] % k]++;

        for(int i = 1; i < n; i++)
        {
            int cur_mod = nums[i] % k;

            dp[i][cur_mod]++;

            for(int j = 0; j < k; j++)
            {
                if(dp[i - 1][j] > 0)
                {
                    int new_mod = (j * cur_mod) % k;
                    dp[i][new_mod] += dp[i - 1][j];
                }
            }

            for(int j = 0; j < k; j++) answer[j] += dp[i][j];
        }
        
        return answer;
    }
};
