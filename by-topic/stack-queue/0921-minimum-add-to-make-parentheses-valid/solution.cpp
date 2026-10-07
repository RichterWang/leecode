#include <string>
#include <stack>
using namespace std;

/*
 * LeetCode 921. 使括号有效的最少添加
 *
 * 核心思路：用两个计数器分别统计需要补充的左括号和右括号数量。
 * - balance：当前未匹配的左括号数量
 * - additions：需要补充的左括号数量（右括号过多时）
 */
class Solution {
public:
    int minAddToMakeValid(string s) {
        int balance = 0;    // 未匹配的左括号数
        int additions = 0;  // 需要补充的左括号数
        
        for (char c : s) {
            if (c == '(') {
                balance++;
            } else {
                balance--;
                if (balance < 0) {
                    // 右括号过多，需要在前面补一个左括号
                    additions++;
                    balance = 0;  // 重置
                }
            }
        }
        
        // additions: 需要补的左括号数（右括号过多）
        // balance: 需要补的右括号数（左括号过多）
        return additions + balance;
    }
};
