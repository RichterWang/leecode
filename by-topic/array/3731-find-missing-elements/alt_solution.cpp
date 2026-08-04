// LeetCode 3731. Find Missing Elements
// 双指针版本：i 扫描排序后的数组，expected 记录当前应该出现的下一个整数

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        vector<int> ans;
        if (nums.empty()) return ans;

        sort(nums.begin(), nums.end());

        int i = 0;
        int expected = nums[0];

        while (i < (int)nums.size()) {
            if (nums[i] == expected) {
                ++i;
                ++expected;
            } else if (nums[i] > expected) {
                ans.push_back(expected);
                ++expected;
            } else {
                ++i;
            }
        }

        return ans;
    }
};
