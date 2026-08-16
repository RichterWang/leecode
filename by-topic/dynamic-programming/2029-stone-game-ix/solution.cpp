#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

/*
 * Daily question draft
 *
 * 使用方式：
 * 1. 先根据题目改函数名、参数列表和返回值类型
 * 2. 在 Solution 中补核心算法
 * 3. 提交到 LeetCode 时，通常只需要复制 Solution 类
 */
class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int n = static_cast<int>(stones.size());
        vector<int> cnt(3, 0);

        for(int x : stones) {
            int temp = x % 3;
            if(temp == 0) cnt[0]++;
            if(temp == 1) cnt[1]++;
            if(temp == 2) cnt[2]++;
        }

        if(cnt[0] % 2 == 0) return(cnt[1] > 0 && cnt[2] > 0);
        else return (abs(cnt[2] - cnt[1]) > 2);     
    }

private:

};
