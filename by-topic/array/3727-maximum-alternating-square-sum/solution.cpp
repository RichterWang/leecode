#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        int minus = (n >> 1);

        sort(nums.begin(), nums.end(), [](int a, int b){
            return abs(a) > abs(b);
        });

        long long answer = 0LL;

        for(int i = 0; i < n - minus; i++) answer += (long long)nums[i] * nums[i];
        
        for(int i = n - minus; i < n; i++) answer -= (long long)nums[i] * nums[i];

        return answer;
    }
};
