#include <vector>

using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = static_cast<int>(nums.size());

        int left = 0, right = n - 1;
        while(left < right)
        {
            int mid = (left + right)/ 2;

            if(nums[mid] > nums[right]) left = mid + 1;
            else right = mid;
        }

        return nums[left];
    }

private:

};
