#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
 * 78. Subsets
 *
 * 位掩码枚举幂集。
 *
 * n 个互不相同的元素共有 2^n 个子集，用 [0, 2^n) 区间内的整数
 * 与子集建立一一对应：mask 的第 i 位为 1 表示选取 nums[i]。
 *
 * mask 在这里是循环计数器（只读输入），不是被累积计算出来的状态，
 * 所以内层只用 & 查询，不需要 |= 置位。
 */
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<vector<int>> ans;
        ans.reserve(1 << n);      // 结果数量已知，预分配省掉扩容
        vector<int> temp;         // 放在循环外，clear() 保留容量

        // mask = 0 对应空集，无需额外手动 push
        for (int mask = 0; mask < (1 << n); mask++)
        {
            temp.clear();
            for (int i = 0; i < n; i++)
            {
                // 第 i 位为 1 则取 nums[i]
                if (mask & (1 << i)) temp.push_back(nums[i]);
            }
            ans.push_back(temp);
        }

        return ans;
    }
};
