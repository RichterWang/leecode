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
    long long findKthSmallest(vector<int>& coins, int k) {
        int n = static_cast<int>(coins.size());
        sort(coins.begin(), coins.end());
        unordered_set<int> reference;
        vector<int> current_offset(n, 1);

        for(int i = 0; i < k; i++)
        {
            int temp_min = INT_MAX;
            bool current_modify = false;
            int last_index = 0;
            for(int j = 0; j < n; j++)
            {
                if(reference.count(current_offset[j] * coins[j])) current_offset[j]++; //跳过重复值
                if(current_modify == true && current_offset[j] * coins[j] < temp_min && !reference.count(current_offset[j] * coins[j]))
                {
                    reference.emplace(current_offset[j] * coins[j]);
                    temp_min = current_offset[j] * coins[j];
                    current_offset[j]++;
                    // 之前存入的信息退出
                    reference.erase(current_offset[last_index] * coins[last_index]);
                    current_offset[last_index]--;
                    last_index = j;
                }
                else if(current_offset[j] * coins[j] < temp_min && !reference.count(current_offset[j] * coins[j])){
                    reference.emplace(current_offset[j] * coins[j]);
                    temp_min = current_offset[j] * coins[j];
                    current_offset[j]++;
                    current_modify = true;
                    last_index = j;
                }
            }
        }

        auto it = max_element(reference.begin(), reference.end());
        if(it != reference.end()) return *it;
    }

private:

};

/*
leecode3116: 单面值组合的k小金额
    给你一个整数数组 coins 表示不同面额的硬币，另给你一个整数 k 。
    你有无限量的每种面额的硬币。但是，你 不能 组合使用不同面额的硬币。
    返回使用这些硬币能制造的 第 kth 小 金额。
*/