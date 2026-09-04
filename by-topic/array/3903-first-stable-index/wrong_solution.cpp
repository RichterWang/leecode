#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

/*
 * 3903. First Stable Index —— 错误版本（照题面字面实现）
 *
 * 这一版严格按题面写的 max(nums[0..i-1]) - min(nums[i..n-1]) 实现：
 * 前缀不含 nums[i]，i=0 时前缀为空集无法取 max，所以循环从 i=1 起。
 *
 * 反例：nums = [0,0], k = 0
 *   本实现 -> 1（i=0 从未被检查）
 *   预期   -> 0
 *
 * 说明实际判据两侧都含 nums[i]，且 i 从 0 起枚举。
 * [5,0,1,4] k=3 在两种读法下都得 3，分辨不出差异，
 * 只有 [0,0] 这类用例才能暴露。详见 README。
 *
 * 另外每轮拷贝 + 全排序只为取一个最小值，复杂度 O(n^2 log n)。
 */
class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        vector<int> back_temp;
        int temp_min = INT_MAX;
        int temp_max = INT_MIN;

        for(int i = n - 1; i >= 0; i--) back_temp.push_back(nums[i]);

        for(int i = 1; i < n; i++)
        {
            back_temp.pop_back();
            temp_max = max(temp_max, nums[i - 1]);
            vector<int> temp = back_temp;
            sort(temp.begin(), temp.end());
            temp_min = temp[0];
            if(temp_max - temp_min <= k) return i;         
        }

        return -1;
    }

private:

};
