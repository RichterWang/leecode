// 115. 不同的子序列
//
// 计数型 DP（推送 / push 方向）
//
// 状态：dp[i][j] = 用 s 的前 i 个字符，凑出 t 的前 j 个字符的方案数
//       「前 i 个」= s[0..i-1]，均已做过「选 / 不选」的决定
//
// 转移（站在 dp[i][j] 上，处理下一个字符 s[i]，目标是 t[j]）：
//   1) 不用 s[i]        → dp[i+1][j]   += dp[i][j]    无条件
//   2) 用 s[i] 顶 t[j]  → dp[i+1][j+1] += dp[i][j]    仅当 s[i] == t[j]
//   字符相同时两条路都要走：相同不代表必须用它，留着让后面的同款字符来配
//   也是一种独立方案（如 "bbb" 中取两个 b 有 3 种下标组合）。
//
// 种子：dp[0][0] = 1 —— 用 0 个字符凑空串，唯一方案是「什么都不选」。
//       这是整张表唯一的非零初值，写成 0 则全表归零。
//       dp[i][0] 那一整列会沿「不用」分支自动推出为 1，无需手填。
//
// 内层 j 必须遍历到 m（含）：dp[i][m] 表示 t 已配完，这些方案还要沿
//   「不用」分支传递到 dp[i+1][m]（s 剩余字符全部跳过也是合法的）。
//   漏掉会丢失所有中途配完 t 的方案，例如 s="ab", t="a" 会返回 0。
//
// 为什么用 unsigned long long：
//   题目只保证「最终答案」在 32 位内，不保证中间格子。
//   反例 s = "a"*100 + "z", t = "a"*50 + "b"：答案为 0（s 中无 'b'），
//   但 dp[100][50] = C(100,50) ~ 1e29，long long / __int128 均装不下。
//   无符号溢出在 C++ 中是良定义的（对 2^64 取模），且本 DP 只含加法，
//   而加法与取模同态，故 dp[n][m] 严格等于「真实答案 mod 2^64」；
//   真实答案 < 2^31 < 2^64，取模后等于自身，因此结果精确。
//   （若转移中出现除法或取 max，回绕值失去大小序，此技巧即失效。）
//
// 复杂度：时间 O(n*m)，空间 O(n*m)
//   仅依赖上一行，可压成一维滚动数组降至 O(m)，详见 README。

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) {
        int n = static_cast<int>(s.size());
        int m = static_cast<int>(t.size());

        vector<vector<unsigned long long>> dp(n + 1, vector<unsigned long long>(m + 1, 0));
        dp[0][0] = 1;  // 用 0 个字符凑空串：什么都不选，唯一方案

        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= m; j++) {   // 注意到 m（含）
                // 剪枝：无方案的格子推送 0 没有意义。
                // 注意回绕后此处只是性能优化，不代表「此路不通」。
                if (dp[i][j] == 0) continue;

                dp[i + 1][j] += dp[i][j];                     // 不用 s[i]
                if (j < m && s[i] == t[j]) {
                    dp[i + 1][j + 1] += dp[i][j];             // 用 s[i] 顶 t[j]
                }
            }
        }

        return static_cast<int>(dp[n][m]);
    }
};
