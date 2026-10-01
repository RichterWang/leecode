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
 * LeetCode 20 - 有效的括号
 * 
 * 解法：栈匹配
 * 
 * 核心思想：
 * 使用栈存储左括号，遇到右括号时检查栈顶是否匹配。
 * 
 * 算法：
 * 1. 遍历字符串
 * 2. 遇到左括号 '(', '[', '{' → 入栈
 * 3. 遇到右括号 ')', ']', '}' → 检查栈顶是否匹配，匹配则出栈，否则返回 false
 * 4. 遍历结束后检查栈是否为空
 * 
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */
class Solution {
public:
    bool isValid(string s) {
        int n = static_cast<int>(s.size());

        if(n == 0) return true;

        stack<char> stk;

        for(char c : s)
        {
            if(c == '(' || c == '[' || c == '{') {
                stk.push(c);
            }
            else {
                if(stk.empty()) return false;
                char temp = stk.top();
                stk.pop();
                if(temp == '(' && c != ')') return false;
                else if(temp == '{' && c != '}') return false;
                else if(temp == '[' && c != ']') return false;
            }
        }

        return stk.empty();
    }
};
