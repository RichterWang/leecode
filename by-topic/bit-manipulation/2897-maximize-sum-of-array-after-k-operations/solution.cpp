#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        const int BIT_SIZE = 30;

        vector<int> bit_count(BIT_SIZE, 0);
        for(int num : nums) for(int i = 0; i < BIT_SIZE; i++) if(num & (1 << i)) bit_count[i]++;

        vector<long long> result(k, 0);
        for(int bit = BIT_SIZE - 1; bit >= 0; bit--) for(int i = 0; i < min(k, bit_count[bit]); i++) result[i] |= (1 << bit);

        long long sum = 0;
        for(long long num : result) sum = (sum + (num * num) % MOD) % MOD;
        return sum;
    }
};
