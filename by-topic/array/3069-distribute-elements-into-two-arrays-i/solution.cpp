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
    vector<int> resultArray(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if(n == 1 || n == 2) return nums;
        vector<int> answer;

        answer.push_back(nums[0]);
        answer.push_back(nums[1]);
        int ptr1 = 0, ptr2 = 1;

        for(int i = 2; i < n; i++)
        {
            if(answer[ptr1] > answer[ptr2]){
                answer.insert(answer.begin() + ptr1 + 1, nums[i]);
                ptr1++;
                ptr2++;
            }
            else{
                answer.push_back(nums[i]);
                ptr2++;
            }
        }
        return answer;
    }

private:

};