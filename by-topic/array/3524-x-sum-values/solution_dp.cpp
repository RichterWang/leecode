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
 * LeetCode 3524. 求出数组的 X 值 I
 * 
 * 方法：动态规划（最优解）
 * 
 * 核心思路：
 * - 状态定义：dp[i][j] = 以位置 i 结尾、乘积 % k 余数为 j 的子数组数量
 * - 状态转移：
 *   1. 单独成子数组：dp[i][nums[i] % k]++
 *   2. 接在前面的子数组后面：dp[i][new_mod] += dp[i-1][j]
 *      其中 new_mod = (j * (nums[i] % k)) % k
 * 
 * 优点：
 * - 时间复杂度 O(n × k)，比暴力枚举的 O(n²) 快
 * - 当 k 较小时（本题 k ≤ 50）非常高效
 * - 空间可以优化为 O(k)（滚动数组）
 * 
 * 时间复杂度：O(n × k)
 * 空间复杂度：O(n × k) 或 O(k)（滚动数组优化）
 */

// 版本1：二维 DP（更清晰易懂）
class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        vector<long long> answer(k, 0);
        
        // dp[i][j] = 以位置 i 结尾、余数为 j 的子数组数量
        vector<vector<long long>> dp(n, vector<long long>(k, 0));
        
        // 初始化第一个元素
        dp[0][nums[0] % k] = 1;
        answer[nums[0] % k]++;
        
        // 动态规划
        for (int i = 1; i < n; i++) {
            int cur_mod = nums[i] % k;
            
            // 情况1：单独成为子数组 [i]
            dp[i][cur_mod]++;
            
            // 情况2：接在前面的子数组后面
            for (int j = 0; j < k; j++) {
                if (dp[i-1][j] > 0) {
                    // 新余数 = (前面的余数 * 当前元素) % k
                    int new_mod = (static_cast<long long>(j) * cur_mod) % k;
                    dp[i][new_mod] += dp[i-1][j];
                }
            }
            
            // 统计以 i 结尾的所有子数组
            for (int j = 0; j < k; j++) {
                answer[j] += dp[i][j];
            }
        }
        
        return answer;
    }
};

// 版本2：滚动数组优化（节省空间）
class SolutionOptimized {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        vector<long long> answer(k, 0);
        vector<long long> dp(k, 0);  // 只需要一维数组
        
        // 初始化
        dp[nums[0] % k] = 1;
        answer[nums[0] % k]++;
        
        // 动态规划
        for (int i = 1; i < n; i++) {
            int cur_mod = nums[i] % k;
            vector<long long> new_dp(k, 0);  // 新的一层
            
            // 情况1：单独成子数组
            new_dp[cur_mod]++;
            
            // 情况2：接在前面的子数组后面
            for (int j = 0; j < k; j++) {
                if (dp[j] > 0) {
                    int new_mod = (static_cast<long long>(j) * cur_mod) % k;
                    new_dp[new_mod] += dp[j];
                }
            }
            
            // 统计并更新 dp
            for (int j = 0; j < k; j++) {
                answer[j] += new_dp[j];
            }
            dp = new_dp;
        }
        
        return answer;
    }
};

/*
执行过程示例：

nums = [2, 3, 4], k = 6

初始化（i=0）：
nums[0] = 2, mod = 2
dp[0][2] = 1  // 子数组 [2]
answer[2] = 1

i=1（nums[1]=3）：
cur_mod = 3
情况1：dp[1][3] = 1  // 子数组 [3]
情况2：dp[0][2]=1 存在 → new_mod = (2*3)%6 = 0
       dp[1][0] += 1  // 子数组 [2,3]
统计：answer[3]+=1, answer[0]+=1

i=2（nums[2]=4）：
cur_mod = 4
情况1：dp[2][4] = 1  // 子数组 [4]
情况2：dp[1][3]=1 → new_mod = (3*4)%6 = 0, dp[2][0]+=1  // [3,4]
       dp[1][0]=1 → new_mod = (0*4)%6 = 0, dp[2][0]+=1  // [2,3,4]
统计：answer[4]+=1, answer[0]+=2

最终：answer[0]=3, answer[2]=1, answer[3]=1, answer[4]=1
对应子数组：
余数0: [2,3], [3,4], [2,3,4]
余数2: [2]
余数3: [3]
余数4: [4]
*/
