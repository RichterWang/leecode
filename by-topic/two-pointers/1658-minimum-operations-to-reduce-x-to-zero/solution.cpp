#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * LeetCode 1658. 将 x 减到 0 的最小操作数
 * 
 * 解法：滑动窗口（双指针）
 * 核心思路：逆向思维 - 从两端移除元素 = 保留中间连续子数组
 * 
 * 时间复杂度：O(n)
 * 空间复杂度：O(1)
 */
class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = static_cast<int>(nums.size());
        
        // 计算目标：保留的子数组和 = 总和 - x
        int target = accumulate(nums.begin(), nums.end(), 0) - x;
        
        // 边界情况
        if (target < 0) return -1;  // x 大于数组总和，无解
        if (target == 0) return n;   // 需要移除所有元素
        
        // 滑动窗口找和为 target 的最长子数组
        int left = 0;
        int temp_sum = 0;
        int maxLen = -1;
        
        for (int right = 0; right < n; right++) {
            temp_sum += nums[right];
            
            // 窗口和太大，收缩左边界
            while (temp_sum > target && left <= right) {
                temp_sum -= nums[left];
                left++;
            }
            
            // 找到和为 target 的子数组，更新最大长度
            if (temp_sum == target) {
                maxLen = max(maxLen, right - left + 1);
            }
        }
        
        // 最少操作数 = 总长度 - 最长保留子数组长度
        return maxLen == -1 ? -1 : n - maxLen;
    }
};

/**
 * 测试用例
 */
int main() {
    Solution sol;
    
    // 测试用例 1
    vector<int> nums1 = {1, 1, 4, 2, 3};
    int x1 = 5;
    cout << "Test 1: " << sol.minOperations(nums1, x1) << endl;  // 期望输出：2
    
    // 测试用例 2
    vector<int> nums2 = {5, 6, 7, 8, 9};
    int x2 = 4;
    cout << "Test 2: " << sol.minOperations(nums2, x2) << endl;  // 期望输出：-1
    
    // 测试用例 3
    vector<int> nums3 = {3, 2, 20, 1, 1, 3};
    int x3 = 10;
    cout << "Test 3: " << sol.minOperations(nums3, x3) << endl;  // 期望输出：5
    
    return 0;
}
