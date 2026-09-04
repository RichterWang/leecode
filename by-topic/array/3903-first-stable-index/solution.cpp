#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

/*
 * 3903. First Stable Index
 *
 * 前缀最大值 + 后缀最小值，一遍扫描。
 *
 * 判据：max(nums[0..i]) - min(nums[i..n-1]) <= k，求最小的 i。
 * 注意 nums[i] 同时属于两侧（见 README 中 [0,0] 这个分辨用例）。
 *
 * sufMin 预处理成数组；preMax 边扫边累积，且必须在判断之前更新，
 * 这样第 i 轮的 preMax 才覆盖 nums[0..i]。
 */
class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());

        // sufMin[i] = min(nums[i..n-1])
        vector<int> sufMin(n);
        sufMin[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            sufMin[i] = min(nums[i], sufMin[i + 1]);
        }

        int preMax = INT_MIN;
        for (int i = 0; i < n; i++) {
            preMax = max(preMax, nums[i]);          // max(nums[0..i])
            if (preMax - sufMin[i] <= k) return i;
        }

        return -1;
    }
};
