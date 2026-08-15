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
 * Bit manipulation solution for LeetCode 3702
 *
 * 设整个数组的异或和为 totalXor：
 * - 如果 totalXor != 0，那么直接选择整个数组，答案是 n
 * - 如果 totalXor == 0，但数组中存在非零元素，那么删除任意一个非零元素后，
 *   剩余元素的异或和就等于这个被删除的元素本身，因此答案是 n - 1
 * - 如果所有元素都是 0，则不存在异或结果非零的非空子序列，答案是 0
 */
class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        vector<int> drovantila = nums;

        int n = static_cast<int>(nums.size());
        int totalXor = 0;
        for(int i = 0; i < n; i++) totalXor ^= nums[i];
        if(totalXor != 0) return n;

        for(int i = 0; i < n; i++) {
            if(nums[i] != 0) return n - 1;
        }
        return 0;
    }

private:

};
