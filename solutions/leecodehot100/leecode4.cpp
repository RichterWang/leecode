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
#include <set>

using namespace std;

/*
 * LeetCode 4 - 寻找两个正序数组的中位数
 * 
 * 解法：二分切割
 * 
 * 核心思想：
 * 不需要真正合并数组，而是在两个数组中找到合适的切割位置，
 * 使得左半部分元素数量 = 右半部分元素数量（或相差1），
 * 且左半部分所有元素 <= 右半部分所有元素。
 * 
 * 时间复杂度：O(log(min(m, n)))
 * 空间复杂度：O(1)
 */
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = static_cast<int>(nums1.size()); // short
        int n = static_cast<int>(nums2.size()); // long

        if(m > n) return findMedianSortedArrays(nums2, nums1);

        int left = 0, right = m;

        while(left <= right)
        {
            int i = (left + right) >> 1;
            int j = ((m + n + 1) >> 1) - i;

            int max_leftA = (i == 0) ? INT_MIN : nums1[i - 1];
            int min_rightA = (i == m) ? INT_MAX : nums1[i];
            int max_leftB = (j == 0) ? INT_MIN : nums2[j - 1];
            int min_rightB = (j == n) ? INT_MAX : nums2[j];

            if(max_leftA <= min_rightB && max_leftB <= min_rightA)
            {
                if(((m + n) & 1) == 0) return(max(max_leftA, max_leftB) + min(min_rightA, min_rightB)) / 2.0f;
                else return max(max_leftA, max_leftB);
            }
            else if(max_leftA > min_rightB) right = i - 1;
            else left = i + 1;
        }

        return 0.0f;
    }

private:

};
