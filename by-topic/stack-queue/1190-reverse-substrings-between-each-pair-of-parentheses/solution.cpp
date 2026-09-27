#include <algorithm>
#include <stack>
#include <string>

using namespace std;

// 解法一：栈 + 原地翻转尾部
// 时间 O(n^2)，空间 O(n)
class Solution {
public:
    string reverseParentheses(string s) {
        string result;
        stack<int> current;  // 每个 '(' 出现时 result 的长度，即该层在 result 中的起点
        for (char c : s)
        {
            if (c == '(') current.push(static_cast<int>(result.size()));
            else if (c == ')') {
                int start = current.top();
                current.pop();
                reverse(result.begin() + start, result.end());  // 翻转最内层这段
            }
            else result.push_back(c);
        }
        return result;
    }
};
