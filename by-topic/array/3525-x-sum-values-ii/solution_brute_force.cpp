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
 * LeetCode 3525. 求出数组的 X 值 II
 * 
 * 方法：暴力枚举
 * 
 * 核心思路：
 * - 对于每个查询，先更新数组，然后枚举所有可能的后缀
 * - 从固定的起点 start 开始，枚举所有可能的终点 j
 * - 计算区间 [start, j] 的乘积 % k，统计余数为 x 的个数
 * 
 * 关键技巧：
 * - 边乘边取模：避免溢出
 * - 利用模运算的乘法性质：(a * b) % m = ((a % m) * (b % m)) % m
 * 
 * 时间复杂度：O(q × n)
 * - q 个查询
 * - 每个查询最多遍历 n 个位置
 * 
 * 空间复杂度：O(1)（不计输出数组）
 */
class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        int n = static_cast<int>(nums.size());
        int q = static_cast<int>(queries.size());
        vector<int> result;
        
        // 处理每个查询
        for (const auto& query : queries) {
            int index = query[0];
            int value = query[1];
            int start = query[2];
            int x = query[3];
            
            // 1. 更新数组（永久生效）
            nums[index] = value;
            
            // 2. 从 start 开始枚举所有可能的后缀终点
            int count = 0;
            long long product = 1;
            
            for (int j = start; j < n; j++) {
                // 边乘边取模，避免溢出
                product = (product * (nums[j] % k)) % k;
                
                // 如果余数等于 x，计数器加 1
                if (product == x) {
                    count++;
                }
            }
            
            result.push_back(count);
        }
        
        return result;
    }
};

/*
执行过程示例：

nums = [2, 3, 4], k = 6

查询 1：[1, 5, 0, 0]
- 更新：nums = [2, 5, 4]
- 从 start=0 开始枚举：
  j=0: product = 2 % 6 = 2  (余数 2 ≠ 0) ✗
  j=1: product = (2*5) % 6 = 10 % 6 = 4  (余数 4 ≠ 0) ✗
  j=2: product = (4*4) % 6 = 16 % 6 = 4  (余数 4 ≠ 0) ✗
- count = 0

查询 2：[2, 6, 1, 0]
- 更新：nums = [2, 5, 6]
- 从 start=1 开始枚举：
  j=1: product = 5 % 6 = 5  (余数 5 ≠ 0) ✗
  j=2: product = (5*6) % 6 = 30 % 6 = 0  (余数 0 = 0) ✓
- count = 1

查询 3：[0, 3, 0, 3]
- 更新：nums = [3, 5, 6]
- 从 start=0 开始枚举：
  j=0: product = 3 % 6 = 3  (余数 3 = 3) ✓
  j=1: product = (3*5) % 6 = 15 % 6 = 3  (余数 3 = 3) ✓
  j=2: product = (3*6) % 6 = 18 % 6 = 0  (余数 0 ≠ 3) ✗
- count = 2

最终结果：[0, 1, 2]
*/
