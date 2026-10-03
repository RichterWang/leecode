#include <algorithm>
#include <string>
#include <vector>

using namespace std;

/*
 * LeetCode 32. 最长有效括号
 *
 * 一维动态规划，从前往后填表，O(n) 时间 / O(n) 空间。
 *
 * 状态定义：
 *   dp[i] = 以下标 i 结尾的最长有效括号子串长度
 *
 * 关键点：s[i] == '(' 时 dp[i] 恒为 0（左括号不可能作为有效串的结尾）。
 */
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = static_cast<int>(s.size());

        vector<int> dp(n, 0);
        int answer = 0;
        for(int i = 1; i < n; i++)
        {
            if(s[i] == ')')
            {
                if(s[i - 1] == '(')
                {
                    // 情况一：... "()"  直接配对
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                }
                else if(i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(')
                {
                    // 情况二：... "( <已匹配的 dp[i-1] 段> )"  跨过中间段去配对
                    dp[i] = dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
                }
            }
            answer = max(answer, dp[i]);
        }
        return answer;
    }
};
