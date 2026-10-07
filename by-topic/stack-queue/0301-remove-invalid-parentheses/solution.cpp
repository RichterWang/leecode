#include <algorithm>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

/*
 * LeetCode 301. 删除无效的括号
 *
 * 核心思路：BFS + 剪枝
 * - 按删除数量分层搜索（第 k 层 = 删除 k 个字符）
 * - 找到第一层有效解就停止（保证删除最少）
 * - 用哈希表去重，避免重复处理
 */
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> result;
        unordered_set<string> visited;
        queue<string> q;

        q.push(s);
        visited.insert(s);

        while (!q.empty()) {
            int size = q.size();
            bool found = false;
            
            // 处理完整的一层
            for (int k = 0; k < size; k++) {
                string cur = q.front();
                q.pop();
                
                if (isValid(cur)) {
                    result.push_back(cur);
                    found = true;
                }
                
                // 如果本层找到有效解，不再扩展
                if (found) continue;
                
                // 尝试删除每个括号
                for (int i = 0; i < cur.size(); i++) {
                    // 只删除括号，不删除字母
                    if (cur[i] != '(' && cur[i] != ')') continue;
                    
                    // 剪枝：连续相同括号只删一次
                    if (i > 0 && cur[i] == cur[i-1]) continue;
                    
                    string next = cur.substr(0, i) + cur.substr(i+1);
                    if (!visited.count(next)) {
                        q.push(next);
                        visited.insert(next);
                    }
                }
            }
    
            // 如果本层找到有效解，直接返回，不处理下一层
            if (found) break;
        }

        return result;
    }

private:
    // 判断括号字符串是否有效
    bool isValid(const string& s) {
        int count = 0;
        for (char c : s) {
            if (c == '(') {
                count++;
            } else if (c == ')') {
                count--;
                if (count < 0) return false;  // 右括号过多
            }
        }
        return count == 0;  // 左右括号数量相等
    }
};
