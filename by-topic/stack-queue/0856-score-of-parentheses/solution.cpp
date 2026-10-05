#include <algorithm>
#include <stack>
#include <string>

using namespace std;

/*
 * LeetCode 856. 括号的分数
 *
 * 核心思路：用栈模拟自底向上的计算过程。
 * 栈内存储每层的累积分数，遇到 ')' 时结算当前层并合并到外层。
 */
class Solution {
public:
    int scoreOfParentheses(string s) {
        stack<int> stk;
        stk.push(0);  // 栈底元素为 0，表示初始累积分

        for (char c : s) {
            if (c == '(') {
                stk.push(0);  // 进入新的嵌套层，累积分从 0 开始
            } else {
                int v = stk.top(); stk.pop();  // 当前层累积的分数
                int w = stk.top(); stk.pop();  // 外层的累积分数
                
                // max(2 * v, 1) 统一处理两个规则：
                // - v = 0 时：() 得 1 分
                // - v > 0 时：(A) 得 2 * A 分
                stk.push(w + max(2 * v, 1));
            }
        }

        return stk.top();
    }
};
