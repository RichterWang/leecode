// LeetCode 3348. Smallest Divisible Digit Product II
// 贪心构造 + gcd 追踪剩余因子（可以通过的版本）

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string smallestNumber(string num, long long t) {
        int n = num.size();

        // t 只能由 2,3,5,7 质因子组成，否则无解
        long long rest = t;
        for (int p : {2, 3, 5, 7}) {
            while (rest % p == 0) rest /= p;
        }
        if (rest > 1) return "-1";

        // 把 t 分解成最少个数位（从 9 往 2 贪心）
        vector<int> base = factorize(t);
        int k = base.size();

        // 情况 1：所需数位个数超过 num 长度，答案就是 k 位升序排列
        if (k > n) {
            string res;
            for (int d : base) res += char('0' + d);
            return res;
        }

        // prefixRem[i] 表示保留 num[0..i-1] 后，还剩下多少需求没满足
        vector<long long> prefixRem(n + 1, 0);
        prefixRem[0] = t;
        int firstZero = n;
        for (int j = 0; j < n; j++) {
            if (num[j] == '0') {
                firstZero = j;
                break;
            }
            long long d = num[j] - '0';
            prefixRem[j + 1] = prefixRem[j] / myGcd(prefixRem[j], d);
        }

        // num 本身就无零且数位之积满足条件
        if (firstZero == n && prefixRem[n] == 1) return num;

        // 枚举分岔位 i：前缀保持和 num 一致，第 i 位放一个更大的数字
        // i 越大越优，所以从右往左找第一个可行解
        int maxI = min(n - 1, firstZero);
        for (int i = maxI; i >= 0; i--) {
            long long rem = prefixRem[i];
            int cnt = n - 1 - i;  // 分岔位后面还有多少位可以自由填

            for (int d = (num[i] - '0') + 1; d <= 9; d++) {
                long long rem2 = rem / myGcd(rem, (long long)d);
                vector<int> tail = factorize(rem2);

                if ((int)tail.size() <= cnt) {
                    string res = num.substr(0, i);
                    res += char('0' + d);
                    res += string(cnt - tail.size(), '1');  // 不影响乘积的填充
                    for (int x : tail) res += char('0' + x);
                    return res;
                }
            }
        }

        // 情况 2：n 位构造不出来，位数加一，前面补 1
        string res(n + 1 - k, '1');
        for (int d : base) res += char('0' + d);
        return res;
    }

private:
    long long myGcd(long long a, long long b) {
        while (b != 0) {
            long long tmp = a % b;
            a = b;
            b = tmp;
        }
        return a;
    }

    // 从 9 往 2 贪心分解，得到最少数位个数，返回升序列表
    vector<int> factorize(long long t) {
        vector<int> digits;
        for (int d = 9; d >= 2; d--) {
            while (t % d == 0) {
                digits.push_back(d);
                t /= d;
            }
        }
        sort(digits.begin(), digits.end());
        return digits;
    }
};
