#include <string>

using namespace std;

/*
 * LeetCode 856. 括号的分数 - 深度计数法
 *
 * 核心思路：只有 () 这种原子单元真正贡献分数，外层括号只是不断翻倍。
 * 每个 () 在深度 d 时贡献 2^d 分。
 *
 * 优势：O(1) 空间，比栈法更优。
 */
class Solution {
public:
    int scoreOfParentheses(string s) {
        int ans = 0, depth = 0;
        
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                depth++;
            } else {
                depth--;
                // 只有 () 贡献分数，外层只是翻倍
                if (s[i-1] == '(') {
                    ans += (1 << depth);  // 2^depth
                }
            }
        }
        
        return ans;
    }
};
