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
 * 方法：前后缀积（存在问题的初始实现）
 * 
 * 问题：
 * 1. 除法在模运算中不适用
 * 2. 逻辑错误：比较的是 remainder == (front + back) 而不是统计每个余数
 * 3. 三层循环效率低
 */
class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        
        vector<long long> prefix(n + 1, 1);
        vector<long long> suffix(n + 1, 1);
        long long total = 1;

        vector<long long> answer(k, 0);

        // 计算前缀积和后缀积
        for(int i = 1; i <= n; i++)
        {
            prefix[i] = prefix[i - 1] * nums[i - 1];
            total = total * nums[i - 1];
            suffix[i] = suffix[i - 1] * nums[n - i];
        }

        // 枚举所有可能的前缀和后缀移除方案
        for(int front = 0; front < n; front++)
        {
            for(int back = 0; back < n; back++)
            {
                if(front + back >= n) break;
                for(int x = 0; x < k; x++)
                    if((total / (prefix[front] * suffix[back])) % k == (back + front)) 
                        answer[x]++;
            }
        }

        return answer;
    }
};
