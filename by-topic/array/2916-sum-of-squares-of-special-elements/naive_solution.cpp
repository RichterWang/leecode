#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        const int mod = 1e9 + 7;
        long long answer = 0;

        for(int i = 0; i < n; i++)
        {
            unordered_map<int, int> reference;
            int distinct_cnt = 0;

            for(int j = i; j < n; j++)
            {
                if(reference[nums[j]] == 0) distinct_cnt++;
                reference[nums[j]]++;

                answer = (answer + (long long)distinct_cnt * distinct_cnt) % mod;
            }
        }

        return answer;
    }
};
