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
#include <set>

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
    string removeOuterParentheses(string s) {
        int depth = 0;

        string result;

        for(char c : s) {
            if(c == '(') {
                depth++;
                if(depth > 1) result += c;
            } else {
                depth--;
                if(depth >= 1) result += c;
            }
        }

        return result;
    }

private:

};
/*
leecode 1021 删除最外层的括号
*/
