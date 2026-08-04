// LeetCode 3020. Find the Maximum Number of Elements in Subset
// 思路：统计每个数出现频次，尝试把每个数作为链的起点，沿着 x -> x^2 -> x^4 ... 扩展
// 特殊处理 1：因为 1 的任意次方仍然是 1，只能取奇数个

#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int maximumLength(vector<int>& nums) {
        int maxVal = 0;
        unordered_map<long long, int> countMap;

        for (int num : nums) {
            countMap[num]++;
            maxVal = max(maxVal, num);
        }

        int ans = 1;

        // 特殊处理 1：最多只能取奇数个 1
        if (countMap.count(1)) {
            int count1 = countMap[1];
            ans = (count1 % 2 == 0) ? count1 - 1 : count1;
        }

        // 枚举每个可能的起点，构造平方链
        for (int num : nums) {
            if (num == 1) continue;

            int length = 0;
            long long current = num;

            // 中间层需要至少两个相同元素，才能继续向上扩展
            while (current <= maxVal && countMap[current] > 1) {
                length += 2;
                current = current * current;
            }

            // 如果当前层恰好还有一个数，可以作为顶层结束
            if (current <= maxVal && countMap[current] == 1) {
                ans = max(ans, length + 1);
            } else {
                // 否则最后一层不能完整作为中间层，需要回退成合法奇数长度
                ans = max(ans, length - 1);
            }
        }

        return ans;
    }
};
