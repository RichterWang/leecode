#include <algorithm>
#include <string>

using namespace std;

/*
 * LeetCode 678. 有效的括号字符串
 *
 * 核心思路：区间贪心。
 * 由于 '*' 可以是 '(' / ')' / ""，扫描到任意位置时未闭合左括号数不是一个
 * 确定值，而是一个连续区间 [low, high]。只维护上下界即可线性求解。
 */
class Solution {
public:
    bool checkValidString(string s) {
        int low = 0, high = 0;

        for (char c : s) {
            if (c == '(') {
                low++;
                high++;
            } else if (c == ')') {
                low--;
                high--;
            } else {
                // '*' 取两个极端：当 ')' 压低下界，当 '(' 抬高上界
                low--;
                high++;
            }

            // 连最乐观的情况都已欠债，右括号真的多了，无法挽回
            if (high < 0) return false;

            // 未闭合左括号数不可能为负，把下界夹回 0
            low = max(low, 0);
        }

        // 可行值是连续区间，high >= 0 已由循环保证，
        // 只要 low == 0 说明 0 落在区间内，存在合法方案
        return low == 0;
    }
};
