#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

/*
 * 3904. First Stable Index II
 *
 * 前缀最大值 + 后缀最小值，两遍线性扫描。
 *
 * 判据：max(nums[0..i]) - min(nums[i..n-1]) <= k，返回最小的 i，无解返回 -1。
 * 注意 nums[i] 同时属于两侧区间，所以不稳定值恒为非负。
 *
 * suf_min 用 push_back 逆序构建（suf_min[j] 对应原下标 n-1-j），
 * 第二遍扫描时用 suf_min[n-1-i] 换算回来。
 * temp_max 必须在判断之前更新，这样第 i 轮才覆盖 nums[0..i]。
 */
class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        vector<int> suf_min;
        int n = static_cast<int>(nums.size());
        int temp = INT_MAX;

        // 从右往左累积运行最小值，suf_min 内为逆序存放
        for (int i = n - 1; i >= 0; i--) {
            temp = min(temp, nums[i]);
            suf_min.push_back(temp);
        }

        int temp_max = INT_MIN;
        for (int i = 0; i < n; i++) {
            temp_max = max(temp_max, nums[i]);              // max(nums[0..i])
            if (temp_max - suf_min[n - 1 - i] <= k) return i;   // 换算回原下标
            suf_min.pop_back();
        }

        return -1;
    }

private:

};
