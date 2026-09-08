#include <iostream>

using namespace std;

/*
 * 3870. 统计范围内的逗号
 *
 * 当前版本为错误解法，仅用于记录和复盘。
 */
class Solution {
public:
    int countCommas(int n) {
        int ans = 0;
        int offset = 1;

        while (n / 1000 != 0) {
            int temp = n - 1000 + 1;
            ans += temp * offset;
            offset = offset << 3;
            n = n / 1000;
        }

        return ans;
    }
};
