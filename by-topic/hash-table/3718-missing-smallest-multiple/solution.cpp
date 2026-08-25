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
 * LeetCode 3718. 缺失的最小倍数 (Missing Smallest Multiple)
 *
 * 思路：哈希集合 + 顺序遍历
 *   将所有数字存入哈希集合，从 k 开始依次检查 k, 2k, 3k, ...
 *   返回第一个不在集合中的 k 的倍数
 *
 * 时间复杂度 O(n + m)，其中 m 是答案 / k（最坏情况）
 * 空间复杂度 O(n)
 */
class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        unordered_set<int> reference;
        int n = static_cast<int>(nums.size());
        for(int i = 0; i < n; i++) if(!reference.count(nums[i])) reference.emplace(nums[i]);
        int index = 1;
        while(reference.count(k * index)) index++;
        return index * k;
    } 

private:

};
