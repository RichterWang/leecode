#include <algorithm>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        long long k = (long long)k1 + k2;
        
        map<long long, long long> freq;
        long long totalDiff = 0;
        
        // 统计差值频率
        for (int i = 0; i < n; i++) {
            long long d = abs(nums1[i] - nums2[i]);
            freq[d]++;
            totalDiff += d;
        }
        
        // 如果 k 够大，直接返回 0
        if (k >= totalDiff) return 0;
        
        // 从大到小贪心降低
        while (k > 0) {
            auto it = prev(freq.end());  // 最大差值
            long long maxDiff = it->first;
            long long count = it->second;
            
            if (maxDiff == 0) break;
            
            // 找下一个阶梯
            auto nextIt = prev(it);
            long long nextDiff = (it != freq.begin()) ? nextIt->first : 0;
            
            // 计算能降低的量
            long long gap = maxDiff - nextDiff;
            long long needed = gap * count;  // 降到下一个阶梯需要的操作数
            
            if (k >= needed) {
                // k 够用，完全降到下一个阶梯
                freq.erase(it);
                freq[nextDiff] += count;
                k -= needed;
            } else {
                // k 不够，只能部分降低
                long long reduce = k / count;
                long long remainder = k % count;
                
                freq.erase(it);
                if (remainder > 0) {
                    freq[maxDiff - reduce - 1] += remainder;
                    freq[maxDiff - reduce] += (count - remainder);
                } else {
                    freq[maxDiff - reduce] += count;
                }
                k = 0;
            }
        }
        
        // 计算最终的平方和
        long long result = 0;
        for (auto& [diff, cnt] : freq) {
            result += diff * diff * cnt;
        }
        return result;
    }
};
