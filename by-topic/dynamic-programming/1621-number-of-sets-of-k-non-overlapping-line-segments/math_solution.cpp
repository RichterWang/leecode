#include <algorithm>

using namespace std;

/**
 * 数学解法：利用组合数公式 C(n+k-1, 2k)
 * 
 * 核心思想：
 * 这道题可以转化为组合数学问题。答案等于 C(n+k-1, 2k)。
 * 
 * 时间复杂度：O(k)
 * 空间复杂度：O(1)
 */
class Solution {
public:
    int numberOfSets(int n, int k) {
        const int MOD = 1e9 + 7;
        
        // 答案 = C(n + k - 1, 2k)
        return combination(n + k - 1, 2 * k, MOD);
    }

private:
    /**
     * 计算组合数 C(n, m) % MOD
     * 
     * 使用逐步累乘法：
     * C(n, m) = [n × (n-1) × ... × (n-m+1)] / [m × (m-1) × ... × 1]
     * 
     * 在模运算下，除法需要转换为乘以模逆元
     */
    long long combination(int n, int m, int MOD)
    {
        // 边界情况
        if(m > n || m < 0) return 0;
        if(m == 0 || m == n) return 1;

        // 优化：利用 C(n, m) = C(n, n-m)，选择较小的 m
        m = min(m, n - m);

        long long numerator = 1;    // 分子
        long long denominator = 1;  // 分母

        // 逐步计算分子和分母，边乘边取模防止溢出
        for(int i = 0; i < m; i++)
        {
            // 分子：n × (n-1) × (n-2) × ... × (n-m+1)
            numerator = numerator * (n - i) % MOD;
            
            // 分母：1 × 2 × 3 × ... × m
            denominator = denominator * (i + 1) % MOD;
        }

        // 计算 numerator / denominator (mod MOD)
        // = numerator × denominator^(-1) (mod MOD)
        // 使用费马小定理求模逆元
        return numerator * modInverse(denominator, MOD) % MOD;
    }

    /**
     * 快速幂算法：计算 a^b % MOD
     * 
     * 原理：将 b 转换为二进制，利用平方法快速计算
     * 例如：a^13 = a^(1101₂) = a^8 × a^4 × a^1
     * 
     * 时间复杂度：O(log b)
     */
    long long modPow(long long a, long long b, int MOD)
    {
        long long result = 1;
        a %= MOD;
        
        while(b > 0){
            // 如果 b 的当前最低位是 1，累乘到结果中
            if(b & 1) result = result * a % MOD;
            
            // a 自乘：a → a² → a⁴ → a⁸ → ...
            a = a * a % MOD;
            
            // b 右移一位（相当于除以 2）
            b >>= 1;
        }

        return result;
    }

    /**
     * 计算模逆元：a^(-1) mod MOD
     * 
     * 费马小定理：当 MOD 是质数时，a^(MOD-1) ≡ 1 (mod MOD)
     * 因此：a^(-1) ≡ a^(MOD-2) (mod MOD)
     * 
     * 10^9 + 7 是质数，所以可以使用这个方法
     */
    long long modInverse(long long a, int MOD){
        return modPow(a, MOD - 2, MOD);
    }
};
