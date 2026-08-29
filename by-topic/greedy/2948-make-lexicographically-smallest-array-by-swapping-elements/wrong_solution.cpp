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
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = static_cast<int>(nums.size());
        vector<int> result = nums;

        for(int i = 0; i < n; i++)
        {
            int temp = INT_MIN;
            int back_index;
            bool need_swap = false;
            for(int j = i + 1; j < n; j++)
            {
                if(abs(result[i] - result[j]) <= limit && result[i] > result[j] &&  result[i] - result[j] > temp)
                {
                    temp = result[i] - result[j];
                    back_index = j;
                    need_swap = true;   
                }
            }
            if(need_swap) swap(result[i], result[back_index]);
        }

        return result;
    }

private:

};