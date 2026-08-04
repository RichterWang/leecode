// LeetCode 3731. Find Missing Elements
// 先排序，再用一个 reference 表示当前期望出现的下一个整数。
// 若 nums[i] 大于 reference，则把 [reference, nums[i) 内的所有整数加入答案。

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        vector<int> ans;
        int n = nums.size();
        if (n == 0) {
            return ans;
        }

        sort(nums.begin(), nums.end());

        int reference = nums[0];
        for (int i = 0; i < n; i++) {
            if (reference != nums[i]) {
                for (int j = reference; j < nums[i]; j++) {
                    ans.push_back(j);
                }
                reference = nums[i] + 1;
            } else {
                reference++;
            }
        }

        return ans;
    }
};
