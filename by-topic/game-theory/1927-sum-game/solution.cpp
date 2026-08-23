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
    bool sumGame(string num) {
        int n = static_cast<int>(num.size());
        
        int pre_sum = 0, back_sum = 0;
        int pre_num = 0, back_num = 0;
        for(int i = 0; i < n / 2; i++)
        {
            if(num[i] != '?') pre_sum += num[i] - '0';
            else pre_num++;
            if(num[i + n / 2] != '?') back_sum += num[i + n / 2] - '0';
            else back_num++;
        }

        // 只有这两种情况bob可能获胜
        if(pre_sum == back_sum && pre_num == back_num) return false;

        // 只有差值以下情况可以完成：
        if((pre_sum > back_sum && pre_num < back_num) || (pre_sum < back_sum && pre_num > back_num))
        {
            int remain = abs(pre_sum - back_sum);
            int abs_num = abs(pre_num - back_num);

            if((abs_num % 2 == 0) && (abs_num * 9 / 2 == remain)) return false;
            else return true;
        }
        return true;
    }

private:

};

/*
    leecode1927
*/