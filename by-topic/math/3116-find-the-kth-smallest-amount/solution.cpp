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

using namespace std;

/*
 * Daily question draft
 *
 * 使用方式：
 * 1. 先根据题目改函数名、参数列表和返回值类型
 * 2. 在 Solution 中补核心算法
 * 3. 提交到 LeetCode 时，通常只需要复制 Solution 类
 */
class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        vector<long long> filtered_coins = filterCoins(coins);
        int n = filtered_coins.size();

        long long left = *min_element(filtered_coins.begin(), filtered_coins.end());
        long long right = left * k;

        while(left < right)
        {
            long long mid = left + (right - left)/2;

            long long count = countLessOrEqual(mid, filtered_coins);

            if(count < k) left = mid + 1;
            else right = mid;
        }

        return left;
    }

private:
// 辅助函数1: 去除倍数关系
vector<long long> filterCoins(vector<int>& coins)
{
    int n = static_cast<int>(coins.size());
    vector<long long> filtered;

    for(int i = 0; i < n; i++)
    {
        bool is_mutiple = false;

        for(int j = 0; j < n; j++)
        {
            if(i != j && coins[i] % coins[j] == 0){
                is_mutiple = true;
                break;
            }
        }

        if(!is_mutiple) filtered.push_back(coins[i]);
    }

    return filtered;
}

// 递归计算最大公约数
long long gcd(long long a, long long b)
{
    return b == 0 ? a : gcd(b, a % b);
}

// 计算最小公倍数
long long lcm(long long a, long long b)
{
    return a / gcd(a, b) * b;
}

// 利用容斥原理计算小于给定x的金额数量
long long countLessOrEqual(long long x, vector<long long>& coins)
{
    int n = coins.size();
    long long count = 0;

    for(int mask = 1; mask < (1 << n); mask++)
    {
        long long current_lcm = 1; //当前子集中所有硬币的最小公倍数
        int bits = 0; // 当前子集中的硬币数量

        for(int i = 0; i < n; i++)
        {
            if(mask & (1 << i)){
                current_lcm = lcm(current_lcm, coins[i]);
                bits++;

                if(current_lcm > x) break;
            }
        }

        if(current_lcm <= x)
        {
            if(bits % 2 == 1) count += x / current_lcm;
            else count -= x / current_lcm;
        }
    }

    return count;
}
};