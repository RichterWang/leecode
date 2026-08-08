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
    vector<int> validSequence(string word1, string word2) {
        int length1 = word1.size();
        int length2 = word2.size();
        vector<int> answer;

        // T[j] 对应原来 dp[i][j][1] 这一层：表示 word1[i:] 能精确匹配
        // word2[j:] 时，i 能取到的最大值（临界位置），-1 表示无法匹配。
        vector<int> T(length2 + 1, -1);
        T[length2] = length1;    // 边界：空串永远可以匹配，对应 dp[i][length2][1]=true

        int p = length1 - 1;
        for (int j = length2 - 1; j >= 0; j--) {
            while (p >= 0 && word1[p] != word2[j]) p--;
            if (p < 0) break;    // 后面的 T[j] 保持 -1，即无法匹配
            T[j] = p;
            p--;
        }    // 填表部分结束，空间从 O(n*m) 降为 O(m)

        // 找位置组合：结构不变，只是把查 dp[i+1][j+1][1] 换成查 T[j+1]
        int next = 0;
        bool used = false;
        for (int j = 0; j < length2; j++) {
            bool found = false;
            for (int i = next; i < length1; i++) {
                bool canChoose = false;
                if (word1[i] == word2[j]) {
                    // 精确匹配永远不比用替换机会差，直接可选，不需要查表
                    canChoose = true;
                } else if (!used) {
                    // 对应原来的 dp[i+1][j+1][1]
                    canChoose = (T[j + 1] != -1 && i + 1 <= T[j + 1]);
                }

                if (canChoose) {
                    answer.push_back(i);
                    next = i + 1;
                    if (word1[i] != word2[j]) used = true;
                    found = true;
                    break;
                }
            }
            if (!found) return {};
        }

        return answer;
    }

private:

};