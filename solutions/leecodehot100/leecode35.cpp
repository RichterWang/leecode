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
#include <functional>
#include <array>

using namespace std;

/*
 * LeetCode 35. 搜索插入位置
 * 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。
 * 如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
 * 请必须使用时间复杂度为 O(log n) 的算法。
 */
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = static_cast<int>(nums.size());

        if(nums[n - 1] < target) return n;
        else if(nums[0] > target) return 0;

        if(n == 1)
        {
            if(nums[0] >= target) return 0;
            else return 1;
        }

        int left = 0, right = n - 1, current = (left + right) / 2;
        if(n == 2)
        {
            if(nums[left] >= target) return 0;
            if(nums[right] >= target) return 1;
            else return 2;
        }
        while(left < right - 1)
        {
            if(target == nums[left]) return left;
            if(target == nums[right]) return right;
            if(nums[current] == target) return current;
            if(nums[current] < target) {
                left = current;
                current = (left + right)/ 2;
            }
            else {
                right = current;
                current = (left + right)/ 2;
            }
        }
        return left + 1;
    }

private:

};
