#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = static_cast<int>(nums1.size());
        long long k = static_cast<long long>(k1) + static_cast<long long>(k2);
        vector<long long> diff(n);
        long long total_diff = 0;
        for (int i = 0; i < n; i++) 
        {
            diff[i] = static_cast<long long>(abs(nums1[i] - nums2[i]));
            total_diff += diff[i];
        }

        if (total_diff <= k) return 0;

        sort(diff.begin(), diff.end(), greater<long long>()); // 降序排列

        for (int i = 0; i < n && k > 0; i++) {
            if (diff[i] == 0) break;

            long long next = (i + 1 < n) ? diff[i + 1] : 0;
            long long count = i + 1;
            long long reduce = min(k / count, diff[i] - next);
            for (int j = 0; j <= i; j++) {
                diff[j] -= reduce;
            }
            k -= reduce * count;
        }

        if (k > 0) for (int i = 0; i < min(k, static_cast<long long>(n)); i++) diff[i]--;
        
        long long result = 0;
        for (int i = 0; i < n; i++) {
            result += diff[i] * diff[i];
        }
        return result;
    }
};
