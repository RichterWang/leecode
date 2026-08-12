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
    int maxSubarrayLength(vector<int>& nums, int k) {
        if(nums.size() == 0) return 0;
        int ans = 1;
        int n = nums.size();
        unordered_map<int, int> countFrequency;

        // 左指针是子数组的结尾项（含在子数组中），右指针是当前的判断项，也是在先加入到子数组中再判断
        int left = 0, right = 0;
        while(right < n)
        {
            countFrequency[nums[right]] ++;
            if(countFrequency[nums[right]] <= k) ans = max(ans, right - left + 1);
            else
            {
                while(countFrequency[nums[right]] > k && left <= right) {
                    countFrequency[nums[left]] --;
                    left++;
                }
            }
            right ++;
        }
        return ans;
    }

private:

};
