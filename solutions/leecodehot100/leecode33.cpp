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
#include <numeric> 

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
    int search(vector<int>& nums, int target) {
        int n = static_cast<int>(nums.size());

        if(n == 0) return -1;

        int left = 0, right = n - 1;
        
        while(left <= right)
        {
            int mid = (left + right)/ 2;

            if(nums[mid] == target) return mid;

            if(nums[left] <= nums[mid])
            {
                if(nums[left] <= target && target < nums[mid]) right = mid - 1;
                else left = mid + 1;
            }
            else{
                if(nums[mid] < target && target <= nums[right]) left = mid + 1;
                else right = mid - 1;
            }
        }

        return -1;
    }

private:

};
/*
leecode33 搜索旋转排序数组
整数数组 nums 按升序排列，数组中的值 互不相同 。
在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 向左旋转，使数组变为 
[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。
例如， [0,1,2,4,5,6,7] 下标 3 上向左旋转后可能变为 [4,5,6,7,0,1,2] 。
给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则
返回 -1 。
你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。
*/
