#include <algorithm>
#include <string>

using namespace std;

// 解法二：递归
// 时间 O(n^2)，空间 O(n)
class Solution {
public:
    string reverseParentheses(string s) {
        int i = 0;
        return dfs(s, i);
    }

private:
    // 处理从 i 开始，直到遇到匹配的 ')' 或串尾的部分
    // i 按引用传递：子调用消费过的字符，父调用不会再读
    string dfs(const string& s, int& i)
    {
        string current;
        while (i < static_cast<int>(s.size()))
        {
            char c = s[i++];
            if (c == '(') {
                string inner = dfs(s, i);             // 先处理内层
                reverse(inner.begin(), inner.end());  // 内层结果翻转后并入本层
                current += inner;
            }
            else if (c == ')') return current;        // 本层结束，交给上层
            else current.push_back(c);
        }
        return current;  // 最外层走到串尾时从这里返回，不能省
    }
};
