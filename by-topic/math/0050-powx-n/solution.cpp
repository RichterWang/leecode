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
#include <numeric>
#include <functional>
#include <array>

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
    double myPow(double x, int n) {
        long long exp = n;

        if(n < 0){
            exp = abs(exp);
            x = 1.0 / x;
        }

        double result = 1.0f;

        while(exp > 0)
        {
            if(exp % 2 == 1) result = result * x;
            x = x * x;
            exp = exp / 2;
        }

        return result;
    }

private:

};

/* leecode 50
*/
