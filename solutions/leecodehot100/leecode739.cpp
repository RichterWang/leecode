#include <stack>
#include <vector>

using namespace std;

/*
 * LeetCode 739. 每日温度
 *
 * 单调递减栈：栈内存下标，对应温度自栈底到栈顶递减。
 * 当前温度比栈顶高时，栈顶元素找到了答案，弹出并结算 i - idx。
 *
 * 时间 O(n)，空间 O(n)。
 */
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = static_cast<int>(temperatures.size());

        vector<int> ans(n, 0);
        stack<int> stk; // 存储下标

        for (int i = 0; i < n; i++)
        {
            while (!stk.empty() && temperatures[i] > temperatures[stk.top()])
            {
                int idx = stk.top();
                stk.pop();
                ans[idx] = i - idx;
            }
            stk.push(i);
        }
        return ans;
    }
};
