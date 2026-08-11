// LeetCode 2996. Smallest Missing Integer Greater Than Sequential Prefix Sum

#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        int prefixSum = nums[0];
        unordered_set<int> seen;

        for (int value : nums) {
            seen.insert(value);
        }

        for (int i = 0; i < n - 1; i++) {
            if (nums[i + 1] - nums[i] == 1) {
                prefixSum += nums[i + 1];
            } else {
                break;
            }
        }

        while (seen.count(prefixSum)) {
            prefixSum++;
        }

        return prefixSum;
    }
};
