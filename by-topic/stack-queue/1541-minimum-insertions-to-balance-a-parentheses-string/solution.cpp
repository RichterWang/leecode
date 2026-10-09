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
    int minInsertions(string s) {
        int insertions = 0;
        int balance = 0; // 目前需要多少个右括号来匹配左括号

        int n = static_cast<int>(s.size());
        int i = 0;
        
        while (i < n) {
            if (s[i] == '(') {
                balance += 2; // 遇到左括号，增加需要的右括号数量
                i++;
            } else { // s[i] == ')'
                if (i + 1 < n && s[i + 1] == ')') {
                    balance -= 2;
                    i += 2;
                } else {
                    balance -= 2;
                    i++;
                    insertions++;
                }
                
                while(balance < 0){
                    insertions ++;
                    balance += 2;
                }
            }
        }
        
        return insertions + balance;
    }

private:

};
/*
leecode 1541 平衡括号字符串的最小插入次数
给你一个括号字符串 s ，它只包含字符 '(' 和 ')' 。一个括号字符串被称为平衡的当它满足：
任何左括号 '(' 必须对应两个连续的右括号 '))' 。
左括号 '(' 必须在对应的连续两个右括号 '))' 之前。
比方说 "())"， "())(())))" 和 "(())())))" 都是平衡的， ")()"， "()))" 和 "(()))" 都是不平衡的。
你可以在任意位置插入字符 '(' 和 ')' 使字符串平衡。
请你返回让 s 平衡的最少插入次数。
*/
