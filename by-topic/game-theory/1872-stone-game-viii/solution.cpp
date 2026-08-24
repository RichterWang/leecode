#include <algorithm>
#include <vector>

using namespace std;

/*
 * LeetCode 1872. 石子游戏 VIII (Stone Game VIII)
 *
 * 思路：前缀和 + 一维 DP（从后往前）
 *   dp[i] 表示「前 i 个原始石子已经合并成一颗」时，当前先手能取得的最大分数差。
 *   转移：dp[i] = max(dp[i + 1], prefixSum[i + 1] - dp[i + 1])
 *     - dp[i + 1]                    ：本回合不在此处结束取石，继续往右取
 *     - prefixSum[i + 1] - dp[i + 1] ：本回合取到第 i 个原始石子，得分为 prefixSum[i + 1]
 *   边界：dp[n - 1] = prefixSum[n]（只剩 2 颗，规则要求 x > 1，必须全拿，无第二选择）
 *   答案：dp[1]（Alice 首次操作至少取 2 颗）
 *
 * 时间复杂度 O(n)，空间复杂度 O(n)（可优化为 O(1)）
 */
class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = static_cast<int>(stones.size());

        // prefixSum[i] = stones[0] + ... + stones[i - 1]
        vector<int> prefixSum(n + 1);
        for (int i = 1; i <= n; i++)
            prefixSum[i] = prefixSum[i - 1] + stones[i - 1];

        // dp[i]：前 i 个已合并为一颗，此时先手的最大分数差
        vector<int> dp(n + 1);
        dp[n - 1] = prefixSum[n];  // 只剩 2 颗，必须全拿
        for (int i = n - 2; i >= 1; i--)
            dp[i] = max(dp[i + 1], prefixSum[i + 1] - dp[i + 1]);

        return dp[1];
    }
};
