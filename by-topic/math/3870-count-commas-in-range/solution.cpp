/*
 * 3870. 统计范围内的逗号
 *
 * 按照 1,000、1,000,000、1,000,000,000……这些阈值，
 * 分别统计每一层逗号产生的贡献。
 */
class Solution {
public:
    int countCommas(int n) {
        long long ans = 0;

        for (long long threshold = 1000;
             threshold <= n;
             threshold *= 1000) {
            ans += static_cast<long long>(n) - threshold + 1;
        }

        return static_cast<int>(ans);
    }
};
