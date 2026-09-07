// LeetCode 39. Combination Sum
// 回溯：start 避免生成重复排列，递归传 i 允许当前候选数重复使用。

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());

        vector<vector<int>> answer;
        vector<int> path;

        dfs(0, target, path, answer, candidates);
        return answer;
    }

private:
    void dfs(int start,
             int remain,
             vector<int>& path,
             vector<vector<int>>& answer,
             const vector<int>& candidates) {
        if (remain == 0) {
            answer.push_back(path);
            return;
        }

        for (int i = start; i < static_cast<int>(candidates.size()); ++i) {
            // candidates 已排序，当前值超过 remain 时，后续值也一定超过。
            if (candidates[i] > remain) {
                break;
            }

            path.push_back(candidates[i]);

            // 继续传 i 而不是 i + 1，允许当前候选数被重复选取。
            dfs(i, remain - candidates[i], path, answer, candidates);

            // 恢复进入本轮选择之前的路径。
            path.pop_back();
        }
    }
};
