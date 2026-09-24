#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * LeetCode 3550. 寻找满足数位和等于下标的最小下标
 * 
 * 解法：模拟 + 数位和计算
 * 
 * 时间复杂度：O(n * log(max(nums)))
 * 空间复杂度：O(1)
 */
class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        
        // 边界情况
        if (n == 0) return -1;
        
        // 遍历每个下标
        for (int i = 0; i < n; i++) {
            // 计算 nums[i] 的数位和
            int digitSum = 0;
            int current = nums[i];
            
            while (current != 0) {
                digitSum += current % 10;
                current = current / 10;
            }
            
            // 如果数位和等于下标，返回该下标
            if (digitSum == i) {
                return i;
            }
        }
        
        // 没有找到满足条件的下标
        return -1;
    }
};

/**
 * 辅助函数：计算一个数的数位和
 */
int getDigitSum(int num) {
    int sum = 0;
    while (num != 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

/**
 * 测试用例
 */
int main() {
    Solution sol;
    
    // 测试用例 1
    vector<int> nums1 = {10, 12, 13, 14};
    cout << "Test 1: " << sol.smallestIndex(nums1) << endl;  // 期望输出：1 (nums[1]=12, 1+2=3, 但下标1不等于3)
    
    // 测试用例 2
    vector<int> nums2 = {0, 1, 2, 3, 4};
    cout << "Test 2: " << sol.smallestIndex(nums2) << endl;  // 期望输出：0 (nums[0]=0, 0的数位和=0)
    
    // 测试用例 3
    vector<int> nums3 = {5, 10, 15};
    cout << "Test 3: " << sol.smallestIndex(nums3) << endl;  // 期望输出：-1
    
    // 测试用例 4
    vector<int> nums4 = {1, 11, 2, 3};
    cout << "Test 4: " << sol.smallestIndex(nums4) << endl;  // 期望输出：2 (nums[2]=2, 数位和=2, 下标=2)
    
    return 0;
}
