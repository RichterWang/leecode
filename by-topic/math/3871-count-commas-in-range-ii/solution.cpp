/*
 * 3871. 统计范围内的逗号 II
 *
 * 与 3870 思路相同，但数据范围扩大到需要使用 64 位整数。
 * 按 1000、10^6、10^9、10^12 …… 逐层累加每一个逗号位置的贡献。
 */
class Solution {
public:
    long long countCommas(long long n) {
        long long answer = 0;

        for (long long i = 1000; i <= n; i *= 1000) {
            answer += (n - i + 1);
        }

        return answer;
    }
};
