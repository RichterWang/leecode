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
#include <functional>
#include <array>

using namespace std;

/*
 * 常用算法模板集合
 * 
 * 这个文件包含了 LeetCode Hot 100 中常用的算法模板
 * 可以作为快速参考和代码片段库使用
 */

// ============================================================
// 1. 二分查找 - 左边界模板（标准写法）
// ============================================================
// 适用场景：查找第一个 >= target 的位置
// 类似题目：LeetCode 35, 34, 69, 278, 875

class BinarySearch {
public:
    // 查找第一个 >= target 的位置
    int lowerBound(vector<int>& nums, int target) {
        int left = 0, right = nums.size();  // 左闭右开区间 [left, right)
        
        while(left < right) {
            int mid = left + (right - left) / 2;
            if(nums[mid] < target) {
                left = mid + 1;  // 答案在 [mid+1, right)
            } else {
                right = mid;     // 答案在 [left, mid)
            }
        }
        return left;  // 第一个 >= target 的位置
    }
    
    // 查找第一个 > target 的位置
    int upperBound(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        
        while(left < right) {
            int mid = left + (right - left) / 2;
            if(nums[mid] <= target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
};

// ============================================================
// 2. 回溯模板
// ============================================================
// 适用场景：组合、排列、子集问题
// 类似题目：LeetCode 17, 22, 39, 40, 46, 47, 78, 90, 131

class Backtrack {
public:
    // 组合问题模板（例如：LeetCode 39 组合总和）
    void combinationSum(int start, int remain, 
                       vector<int>& path, 
                       vector<vector<int>>& answer,
                       vector<int>& candidates) {
        // 终止条件
        if (remain == 0) {
            answer.push_back(path);
            return;
        }
        
        // 枚举选择
        for (int i = start; i < candidates.size(); i++) {
            if (candidates[i] > remain) break;  // 剪枝
            
            path.push_back(candidates[i]);           // 做选择
            combinationSum(i, remain - candidates[i], // i: 可重复选择
                          path, answer, candidates);  // i+1: 不可重复
            path.pop_back();                          // 撤销选择
        }
    }
    
    // 排列问题模板（例如：LeetCode 46 全排列）
    void permute(vector<int>& nums, vector<bool>& used,
                vector<int>& path, vector<vector<int>>& answer) {
        // 终止条件
        if (path.size() == nums.size()) {
            answer.push_back(path);
            return;
        }
        
        // 枚举选择
        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) continue;  // 已使用的元素跳过
            
            used[i] = true;                    // 标记
            path.push_back(nums[i]);           // 做选择
            permute(nums, used, path, answer); // 递归
            path.pop_back();                   // 撤销选择
            used[i] = false;                   // 恢复标记
        }
    }
    
    // 子集问题模板（例如：LeetCode 78 子集）
    void subsets(int start, vector<int>& nums,
                vector<int>& path, vector<vector<int>>& answer) {
        // 每个状态都是一个子集
        answer.push_back(path);
        
        // 枚举选择
        for (int i = start; i < nums.size(); i++) {
            path.push_back(nums[i]);           // 做选择
            subsets(i + 1, nums, path, answer); // 递归下一位
            path.pop_back();                    // 撤销选择
        }
    }
};

// ============================================================
// 3. DFS + 访问标记模板（网格搜索）
// ============================================================
// 适用场景：二维网格中的路径搜索
// 类似题目：LeetCode 79 单词搜索, 200 岛屿数量, 695 岛屿最大面积

class GridDFS {
public:
    // 四个移动方向：上、下、左、右
    array<pair<int, int>, 4> directions = {{
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    }};
    
    bool dfs(int x, int y, vector<vector<char>>& board,
            string& word, int index, vector<vector<bool>>& visited) {
        // 检查当前字符是否匹配
        if (board[x][y] != word[index]) {
            return false;
        }
        
        // 找到完整单词
        if (index == word.size() - 1) {
            return true;
        }
        
        // 标记当前格子为已访问
        visited[x][y] = true;
        
        // 尝试四个方向
        for (auto [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;
            
            // 边界检查
            if (nx < 0 || nx >= board.size() || 
                ny < 0 || ny >= board[0].size()) {
                continue;
            }
            
            // 跳过已访问的格子
            if (visited[nx][ny]) {
                continue;
            }
            
            // 递归搜索
            if (dfs(nx, ny, board, word, index + 1, visited)) {
                visited[x][y] = false;  // 恢复状态
                return true;
            }
        }
        
        // 回溯：恢复当前格子的访问状态
        visited[x][y] = false;
        return false;
    }
};

// ============================================================
// 4. 快慢指针模板（链表）
// ============================================================
// 适用场景：链表环检测、找中点、倒数第k个节点
// 类似题目：LeetCode 141, 142, 19, 876

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class TwoPointers {
public:
    // 检测链表是否有环
    bool hasCycle(ListNode *head) {
        if (!head || !head->next) return false;
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast && fast->next) {
            slow = slow->next;          // 慢指针走1步
            fast = fast->next->next;    // 快指针走2步
            
            if (slow == fast) {         // 相遇则有环
                return true;
            }
        }
        
        return false;
    }
    
    // 找到链表的中点
    ListNode* findMiddle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;  // 偶数个节点时返回中间靠右的节点
    }
};

// ============================================================
// 5. 滑动窗口模板
// ============================================================
// 适用场景：子串、子数组问题
// 类似题目：LeetCode 3, 76, 209, 438, 567

class SlidingWindow {
public:
    // 最小覆盖子串模板
    string minWindow(string s, string t) {
        unordered_map<char, int> need, window;
        for (char c : t) need[c]++;
        
        int left = 0, right = 0;
        int valid = 0;  // 窗口中已满足条件的字符种类数
        
        int start = 0, len = INT_MAX;
        
        while (right < s.size()) {
            // 扩大窗口
            char c = s[right];
            right++;
            
            // 更新窗口数据
            if (need.count(c)) {
                window[c]++;
                if (window[c] == need[c]) {
                    valid++;
                }
            }
            
            // 收缩窗口
            while (valid == need.size()) {
                // 更新结果
                if (right - left < len) {
                    start = left;
                    len = right - left;
                }
                
                // 移出窗口
                char d = s[left];
                left++;
                
                // 更新窗口数据
                if (need.count(d)) {
                    if (window[d] == need[d]) {
                        valid--;
                    }
                    window[d]--;
                }
            }
        }
        
        return len == INT_MAX ? "" : s.substr(start, len);
    }
};

// ============================================================
// 6. 单调栈模板
// ============================================================
// 适用场景：下一个更大/更小元素
// 类似题目：LeetCode 496, 503, 739, 84, 85

class MonotonicStack {
public:
    // 下一个更大元素
    vector<int> nextGreaterElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, -1);
        stack<int> stk;  // 存储索引
        
        for (int i = 0; i < n; i++) {
            // 当前元素比栈顶元素大，说明找到了栈顶元素的下一个更大元素
            while (!stk.empty() && nums[i] > nums[stk.top()]) {
                result[stk.top()] = nums[i];
                stk.pop();
            }
            stk.push(i);
        }
        
        return result;
    }
};

// ============================================================
// 7. 动态规划常见状态转移
// ============================================================

class DP {
public:
    // 01背包
    int knapsack(vector<int>& weights, vector<int>& values, int capacity) {
        int n = weights.size();
        vector<int> dp(capacity + 1, 0);
        
        for (int i = 0; i < n; i++) {
            for (int j = capacity; j >= weights[i]; j--) {
                dp[j] = max(dp[j], dp[j - weights[i]] + values[i]);
            }
        }
        
        return dp[capacity];
    }
    
    // 最长递增子序列
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        
        return *max_element(dp.begin(), dp.end());
    }
};

// ============================================================
// 使用说明：
// 1. 这些模板是经过验证的标准写法
// 2. 使用时根据具体题目调整判断条件和边界处理
// 3. 注意理解每个模板的循环不变量和终止条件
// 4. 建议配合 README.md 中的详细题解一起学习
// ============================================================
