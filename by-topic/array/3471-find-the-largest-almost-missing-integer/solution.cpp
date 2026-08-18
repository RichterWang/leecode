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
    int largestInteger(vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        unordered_map<int, int> reference;

        for(int i = 0; i <= n - k; i++)
        {
            unordered_set<int> haswritten;
            for(int j = i; j < i + k; j++)
            {
                if(!haswritten.count(nums[j])) reference[nums[j]]++;
                haswritten.insert(nums[j]);
            }
            haswritten.clear();
        }

        vector<int> answer;

        for (auto& [key, val] : reference){
            if (val == 1) answer.push_back(key);
        }

        if(answer.empty()) return -1;

        return *max_element(answer.begin(), answer.end());
    }

private:

};
