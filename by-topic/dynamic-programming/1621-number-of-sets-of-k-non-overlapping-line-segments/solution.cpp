#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int numberOfSets(int n, int k) {
        if(k >= n) return 0;

        const int MOD = 1e9 + 7;

        // dp[i][j] 表示用前 i 个点形成 j 条线段的方案数
        // prefix[i][j] 表示 dp[0][j] + dp[1][j] + ... + dp[i][j] 的前缀和
        vector<vector<long long>>dp(n + 1, vector<long long>(k + 1, 0));
        vector<vector<long long>> prefix(n + 1, vector<long long>(k + 1, 0));

        // 初始化：0 条线段的情况
        for(int i = 0; i < n; i++) 
        {
            prefix[0][i] = i + 1;  // 前缀和初始化
            dp[i][0] = 1;           // 不选任何线段，方案数为 1
        }

        // 状态转移
        for(int i = 1; i <= n; i++)
        {
            for(int j = 0; j <= k; j++)
            {
                // dp[i][j] = 不使用第 i 个点 + 使用第 i 个点作为某条线段的右端点
                // 不使用第 i 个点：dp[i-1][j]
                // 使用第 i 个点：枚举所有可能的线段起点，需要前面已经有 j-1 条线段
                // 使用前缀和优化：prefix[i-1][j-1] 表示所有可能的起点位置
                dp[i][j] = (dp[i - 1][j] + prefix[i - 1][j - 1]) % MOD;
                
                // 更新前缀和
                prefix[i][j] = (dp[i][j] + prefix[i - 1][j]) % MOD;
            }
        }

        return dp[n][k] % MOD;
    }
};
