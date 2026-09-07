// LeetCode 39. Combination Sum
// Wrong Solution：二进制位掩码只能表示每个候选数“选或不选”，
// 无法表示同一个候选数可被无限次选择。
//
// 此外，当前判断 `(mask & (1 << j)) != 1` 也不正确：
// 按位与的结果是 0 或 2^j，而不总是 0 或 1。
// 如果只是普通子集枚举，应判断 `(mask & (1 << j)) != 0`，
// 但即使修正，仍然无法解决本题要求的无限复用问题。

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        int n = static_cast<int>(candidates.size());
        vector<vector<int>> answer;

        for (int mask = 0; mask < (1 << n); mask++) {
            int temp = 0;
            vector<int> temp_vec;

            for (int j = 0; j < n; j++) {
                // 错误 1：该条件不能正确判断第 j 位是否被选中。
                // 错误 2：位掩码本身只能让每个元素选择 0 或 1 次。
                if ((mask & (1 << j)) != 0) {
                    temp += candidates[j];
                    temp_vec.push_back(candidates[j]);
                }
            }

            if (temp == target) {
                answer.push_back(temp_vec);
            }
        }

        return answer;
    }
};
