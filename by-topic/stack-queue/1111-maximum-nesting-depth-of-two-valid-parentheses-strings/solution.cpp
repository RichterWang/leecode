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
 * LeetCode 1111 - 有效括号的嵌套深度
 * 
 * 解法：贪心 + 奇偶分配
 * 
 * 核心思想：
 * 将括号按照嵌套深度的奇偶性分配到两个子序列，使得每个子序列的最大深度约为原深度的一半。
 * 
 * 算法：
 * 1. 维护当前深度 current_depth
 * 2. 遇到 '('：深度加 1，按深度奇偶性分配（depth & 1）
 * 3. 遇到 ')'：先按当前深度奇偶性分配（与对应的 '(' 同组），再深度减 1
 * 
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)（输出数组）
 */
class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int n = static_cast<int>(seq.size());
        vector<int> answer(n);
        int current_depth = 0;

        for(int i = 0; i < n; i++)
        {
            if(seq[i] == '(') {
                // 遇到左括号：深度加 1，然后按奇偶分配
                current_depth++;
                answer[i] = current_depth & 1;
            }
            else {
                // 遇到右括号：先按当前深度分配（与对应的左括号同组），再深度减 1
                answer[i] = current_depth & 1;
                current_depth--;
            }
        }

        return answer;
    }
};
