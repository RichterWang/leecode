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
#include <numeric>
#include <set>

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

private:

};

class MinStack {
public:
    MinStack() {
        // 构造函数保持为空 RAII
    }
    
    void push(int value) {
        stk.push(value);

        if(help_stk.empty() || value <= help_stk.top()) help_stk.push(value);
    }
    
    void pop() {
        if(stk.empty()) return;

        if(stk.top() == help_stk.top()) help_stk.pop();
        stk.pop();
    }
    
    int top() {
        return stk.top();
    }
    
    int getMin() {
        return help_stk.top();
    }

private:
    stack<int> stk;
    stack<int> help_stk;

};
/*
leecode155 实现最小栈
*/
