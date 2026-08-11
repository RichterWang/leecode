// LeetCode 189. Rotate Array

#include <vector>

using namespace std;

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        vector<int> temp(nums.size());
        for (int i = 0; i < static_cast<int>(nums.size()) - k; i++) temp[i + k] = nums[i];
        for (int i = 0; i < k; i++) temp[i] = nums[static_cast<int>(nums.size()) - k + i];
        nums = temp;
    }
};
