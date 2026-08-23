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
    bool checkDivisibility(int n) {
        vector<int> get_digit;
        int original = n;

        while(n > 0)
        {
            int digit = n % 10;
            n /= 10;
            get_digit.push_back(digit);
        }

        int size = static_cast<int>(get_digit.size());

        int temp_mutiply = 1, temp_sum = 0;
        for(int i = 0; i < size; i ++)
        {
            temp_sum += get_digit[i];
            temp_mutiply *= get_digit[i];
        }

        return(original % (temp_mutiply + temp_sum) == 0);
    }

private:

};