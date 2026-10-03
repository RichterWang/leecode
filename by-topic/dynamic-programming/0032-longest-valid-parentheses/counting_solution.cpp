#include <algorithm>
#include <string>

using namespace std;

/*
 * LeetCode 32. 最长有效括号 —— 双向计数法
 *
 * O(n) 时间 / O(1) 空间，无堆分配、纯顺序扫描，常数远小于 DP 和栈解法。
 *
 * 必须扫两遍：
 *   正向扫只能在 right > left（右括号多余）时安全归零，
 *   left > right 的情况（如 "(()"）正向永远结算不到，需要反向再扫一遍。
 */
class Solution {
public:
    int longestValidParentheses(const string& s) {
        int n = static_cast<int>(s.size());
        int answer = 0;

        // 正向：处理右括号多余的情况
        for (int i = 0, left = 0, right = 0; i < n; i++) {
            s[i] == '(' ? left++ : right++;

            if (right > left) {
                left = right = 0;
            } else if (left == right) {
                answer = max(answer, 2 * right);
            }
        }

        // 反向：处理左括号多余的情况
        for (int i = n - 1, left = 0, right = 0; i >= 0; i--) {
            s[i] == '(' ? left++ : right++;

            if (left > right) {
                left = right = 0;
            } else if (left == right) {
                answer = max(answer, 2 * left);
            }
        }

        return answer;
    }
};
