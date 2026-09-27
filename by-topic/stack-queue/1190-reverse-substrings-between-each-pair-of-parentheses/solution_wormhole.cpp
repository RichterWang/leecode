#include <stack>
#include <string>
#include <vector>

using namespace std;

// 解法三：预处理括号配对 + 虫洞跳转
// 时间 O(n)，空间 O(n)
class Solution {
public:
    string reverseParentheses(string s) {
        int n = static_cast<int>(s.size());
        vector<int> pair(n);  // pair[i]：括号 i 的配对括号下标（双向记录）
        stack<int> stk;

        // 第一遍：用栈配对括号
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '(') stk.push(i);
            else if (s[i] == ')') {
                int j = stk.top();
                stk.pop();
                pair[i] = j;
                pair[j] = i;
            }
        }

        // 第二遍：遇到括号就跳到配对位置并掉头，d 控制行进方向
        string result;
        for (int i = 0, d = 1; i < n; i += d)
        {
            if (s[i] == '(' || s[i] == ')')
            {
                i = pair[i];  // 穿到配对括号
                d = -d;       // 掉头，循环头的 i += d 负责离开括号
            }
            else result.push_back(s[i]);
        }

        return result;
    }
};
