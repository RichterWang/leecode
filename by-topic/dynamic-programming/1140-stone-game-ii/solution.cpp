// LeetCode 1140. Stone Game II
// DP with suffix sums

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = static_cast<int>(piles.size());
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        vector<int> suffixSum(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffixSum[i] = suffixSum[i + 1] + piles[i];
        }

        for (int i = n - 1; i >= 0; i--) {
            for (int M = 1; M <= n; M++) {
                for (int x = 1; x <= min(2 * M, n - i); x++) {
                    dp[i][M] = max(dp[i][M], suffixSum[i] - dp[i + x][max(M, x)]);
                }
            }
        }

        return dp[0][1];
    }
};
