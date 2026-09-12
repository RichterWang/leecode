#include <algorithm>
#include <vector>
#include <array>

using namespace std;

/*
 * 3414. 不重叠区间的最大得分
 *
 * 带权区间调度 + 字典序约束
 * 核心：dp[r][i] 存储 {最大分数, 字典序最小下标组}
 */
class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = static_cast<int>(intervals.size());

        // 1. 打包原始下标后按右端点排序
        vector<array<int, 4>> arr(n);
        for(int i = 0; i < n; i++) arr[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        sort(arr.begin(), arr.end(), [](const array<int, 4>& a, const array<int, 4>& b){
                return a[1] < b[1];
            });

        // 2. 右端点数组，供二分
        vector<int> right_end(n);
        for(int i = 0; i < n; i++) right_end[i] = arr[i][1];

        // 3. dp[r][i] = {前 i 个区间选 r 个的最大权值, 字典序最小下标组}
        using state = pair<long long, vector<int>>;
        vector<vector<state>> dp(5, vector<state>(n + 1, {0LL, {}}));

        for(int r = 1; r < 5; r++)
        {
            for(int i = 1; i <= n; i++)
            {
                int real_idx = i - 1;
                
                // 方案 A：不选 arr[real_idx]
                state opt1 = dp[r][i - 1];

                // 方案 B：选 arr[real_idx]
                int p = lower_bound(right_end.begin(), right_end.end(), arr[real_idx][0]) - right_end.begin();

                state opt2 = dp[r - 1][p];
                opt2.first += arr[real_idx][2];
                opt2.second.push_back(arr[real_idx][3]);
                sort(opt2.second.begin(), opt2.second.end());

                // 先比分数，分数相同比字典序
                if(opt1.first > opt2.first) dp[r][i] = opt1;
                else if(opt1.first < opt2.first) dp[r][i] = opt2;
                else dp[r][i] = opt1.second < opt2.second ? opt1 : opt2;
            }
        }

        return dp[4][n].second;
    }
};
