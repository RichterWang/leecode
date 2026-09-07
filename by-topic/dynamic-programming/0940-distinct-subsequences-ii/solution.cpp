// 940. 不同的子序列 II
//
// 状态：dp[k] = 扫到当前位置为止，以字母 'a'+k 结尾的、互不相同的非空子序列个数
// 转移：扫到字符 c 时，dp[c] = total + 1//       total = 26 格之和 = 当前所有不同非空子序列个数（可作前缀的材料）
//       +1 = 空前缀，对应 c 单独成串// 去重：用 = 覆盖而非 += 累加

#include <numeric>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int distinctSubseqII(string s) {
        const long long mod_num = 1e9 + 7;

        // dp[k] = 以字母 'a'+k 结尾的、互不相同的非空子序列个数
        // 按结尾字符分组：去重只可能发生在结尾字符相同的串之间
        vector<long long> dp(26, 0);

        for (char ch : s) {            // 先读旧值：total = 当前所有不同非空子序列个数
            long long total = accumulate(dp.begin(), dp.end(), 0LL) % mod_num;
            // 后覆盖：total 种非空前缀 + 1 种空前缀，各接一个 ch
            // 注意是 =（覆盖）不是 +=，这一个符号就是去重
            dp[ch - 'a'] = (total + 1) % mod_num;
        }

        long long answer = accumulate(dp.begin(), dp.end(), 0LL) % mod_num;
        return static_cast<int>(answer);
    }
};
