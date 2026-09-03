#include <algorithm>
#include <vector>

using namespace std;

/*
 * 3876. Construct Parity Consistent Array II
 *
 * 排序后只看最小元素的奇偶性：
 *   - 最小元素是奇数  -> 可以全部变成奇数
 *   - 全部元素都是偶数 -> 本身已经满足
 * 其余情况无解。
 */
class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int n = static_cast<int>(nums1.size());

        sort(nums1.begin(), nums1.end());

        if(nums1[0] % 2 == 0 && nums1[n - 1] % 2 == 1) return false;
        if(nums1[0] % 2 == 1) return true;

        // 接下来只有最开始是偶数，最后也是偶数的情况了
        for(int i = 1; i < n - 1; i++)
        {
            if(nums1[i] % 2 == 1) return false;
        }
        return true;
    }

private:

};
