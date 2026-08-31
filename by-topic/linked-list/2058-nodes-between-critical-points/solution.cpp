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

using namespace std;

/*
 * 2058. 链表中的临界点之间的最小和最大距离
 *
 * 思路：遍历链表记录所有临界点的位置，然后计算最小和最大距离
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        // 至少需要3个节点才可能存在临界点（第2个节点需要前后各一个）
        if(head->next == nullptr || head->next->next == nullptr || head->next->next->next == nullptr) 
            return {-1, -1};

        vector<int> index;

        ListNode* prev = head;
        ListNode* ptr = head->next;
        int current_index = 2;  // 从编号2开始（head是1，head->next是2）
        
        while(ptr->next != nullptr)
        {
            // 检查是否为局部极大值或极小值
            if(prev->val < ptr->val && ptr->next->val < ptr->val) 
                index.push_back(current_index);
            else if(prev->val > ptr->val && ptr->next->val > ptr->val) 
                index.push_back(current_index);

            current_index++;
            ptr = ptr->next;
            prev = prev->next;
        }

        // 少于2个临界点无法计算距离
        int n = static_cast<int>(index.size());
        if(n < 2) return {-1, -1};

        // 最大距离 = 最后一个 - 第一个
        vector<int> result(2);
        result[1] = index[n - 1] - index[0];
        
        // 最小距离 = 相邻临界点的最小间隔
        int min_distance = INT_MAX;
        for(int i = 1; i < n; i++)
        {
            min_distance = min(min_distance, index[i] - index[i - 1]);
        }
        result[0] = min_distance;

        return result;
    }
};
