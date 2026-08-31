# 2058. Find the Minimum and Maximum Number of Nodes Between Critical Points

## 题目信息

- **难度**：Medium
- **分类**：Linked List
- **链接**：https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/

## 题目描述

链表中的**临界点**定义为一个**局部极大值点**或**局部极小值点**。

- **局部极大值点**：当前节点的值**严格大于**前一个节点和后一个节点
- **局部极小值点**：当前节点的值**严格小于**前一个节点和后一个节点

**注意**：节点只有在**同时存在前一个节点和后一个节点**的情况下，才能成为临界点。

给定一个链表 `head`，返回一个长度为 2 的数组 `[minDistance, maxDistance]`，其中：

- `minDistance` 是任意两个不同临界点之间的**最小距离**
- `maxDistance` 是任意两个不同临界点之间的**最大距离**

如果临界点少于两个，则返回 `[-1, -1]`。

### 示例 1

```
输入：head = [3,1]
输出：[-1,-1]
解释：链表中没有临界点
```

### 示例 2

```
输入：head = [5,3,1,2,5,1,2]
输出：[1,3]
解释：
有三个临界点：
- [5,3,1]: 3 是局部极大值（5 < 3，3 > 1）
- [5,3,1,2,5,1]: 1 是局部极小值（3 > 1，1 < 2）
- [2,5,1]: 5 是局部极大值（2 < 5，5 > 1）

最小距离是位置 3 和位置 4 之间：1
最大距离是位置 2 和位置 5 之间：3
```

### 示例 3

```
输入：head = [1,3,2,2,3,2,2,2,7]
输出：[3,3]
解释：
有两个临界点：
- [1,3,2]: 3 是局部极大值
- [3,2,2,2,7]: 7 不是临界点（前一个是 2，但没有"严格小于"）
- [2,2,3,2]: 3 是局部极大值
等等...

实际上只有位置 2 和位置 5 是临界点
距离是 3
```

### 约束条件

- 链表中节点数在 `[2, 10^5]` 范围内
- `1 <= Node.val <= 10^5`

## 解题思路

### 核心观察

1. **临界点条件**：节点 `ptr` 是临界点当且仅当：
   - 它有前驱 `prev` 和后继 `ptr->next`
   - `prev->val < ptr->val > ptr->next->val`（局部极大值）
   - 或 `prev->val > ptr->val < ptr->next->val`（局部极小值）

2. **可能的临界点范围**：
   - 第一个节点（head）：无前驱 → 不可能
   - 最后一个节点：无后继 → 不可能
   - **只有中间节点才可能是临界点**

3. **距离计算**：
   - **最大距离**：第一个临界点到最后一个临界点
   - **最小距离**：相邻临界点的最小间隔

### 方法：一次遍历 + 记录位置

#### 算法步骤

**第一步：边界检查**

```cpp
if(head->next == nullptr || head->next->next == nullptr || head->next->next->next == nullptr) 
    return {-1, -1};
```

至少需要 3 个节点才可能有临界点（中间节点需要前后各一个）。

**第二步：遍历链表，记录所有临界点的位置**

```cpp
vector<int> index;
ListNode* prev = head;
ListNode* ptr = head->next;
int current_index = 2;  // 编号从2开始（head是1）

while(ptr->next != nullptr)
{
    // 检查 ptr 是否为临界点
    if((prev->val < ptr->val && ptr->next->val < ptr->val) ||
       (prev->val > ptr->val && ptr->next->val > ptr->val)) {
        index.push_back(current_index);
    }
    
    prev = prev->next;
    ptr = ptr->next;
    current_index++;
}
```

关键点：
- `prev` 和 `ptr` 同步移动
- 只检查 `ptr`（因为它同时有前驱和后继）
- 循环条件是 `ptr->next != nullptr`（保证 `ptr` 有后继）

**第三步：计算最小和最大距离**

```cpp
int n = index.size();
if(n < 2) return {-1, -1};  // 少于2个临界点

// 最大距离 = 最后一个 - 第一个
int maxDist = index[n - 1] - index[0];

// 最小距离 = 相邻临界点的最小间隔
int minDist = INT_MAX;
for(int i = 1; i < n; i++) {
    minDist = min(minDist, index[i] - index[i - 1]);
}

return {minDist, maxDist};
```

### 下标编号方案

代码采用**1-based 编号**：

```
head → node2 → node3 → node4 → null
 1       2        3        4
```

- `head` 是节点 1
- `head->next` 是节点 2（第一个可检查的节点）
- `current_index` 从 2 开始

这与采用 0-based 编号在逻辑上等价，只要保持一致即可。

### 复杂度分析

**时间复杂度**：O(n)
- 遍历链表一次：O(n)
- 计算最小距离：O(k)，其中 k 是临界点数量，k ≤ n
- 总体 O(n)

**空间复杂度**：O(k)
- `index` 数组存储 k 个临界点位置
- 最坏情况 k = n-2（除了首尾都是临界点），空间 O(n)

### 优化思路

如果不需要记录所有位置，可以边遍历边更新最小/最大距离，将空间降至 O(1)：

```cpp
int first = -1, last = -1, prev_critical = -1;
int minDist = INT_MAX, maxDist = -1;

while(ptr->next != nullptr) {
    if (isCritical(prev, ptr, ptr->next)) {
        if (first == -1) {
            first = current_index;  // 记录第一个
        } else {
            minDist = min(minDist, current_index - prev_critical);
        }
        prev_critical = current_index;
        last = current_index;
    }
    // ...移动指针
}

if (first == last) return {-1, -1};  // 只有1个或0个
maxDist = last - first;
return {minDist, maxDist};
```

## 代码

```cpp
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        // 至少需要3个节点才可能存在临界点
        if(head->next == nullptr || head->next->next == nullptr || 
           head->next->next->next == nullptr) 
            return {-1, -1};

        vector<int> index;
        ListNode* prev = head;
        ListNode* ptr = head->next;
        int current_index = 2;
        
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
```

## 关键细节

### 1. 为什么循环条件是 `ptr->next != nullptr`？

因为判断 `ptr` 是否为临界点需要访问 `ptr->next->val`：

```cpp
if(prev->val < ptr->val && ptr->next->val < ptr->val)
```

如果 `ptr->next == nullptr`，访问 `ptr->next->val` 会段错误。

### 2. 为什么 `prev` 用 `prev->next` 而不是直接跟踪 `ptr` 的前一个？

```cpp
prev = prev->next;  // ✓ 正确
ptr = ptr->next;
```

这样 `prev` 和 `ptr` 始终保持"相邻"关系。如果写成：

```cpp
prev = ptr;        // ✗ 错误
ptr = ptr->next;
```

第一轮后 `prev` 指向 `head->next`，但 `ptr` 已经是 `head->next->next`，它们不相邻了。

不过在你的代码中两种写法都能工作，因为初始化时 `prev = head`，`ptr = head->next`，循环中 `prev->next` 刚好等于"旧的 ptr"。但为了逻辑清晰，推荐用 `prev = ptr; ptr = ptr->next;` 的对称形式。

### 3. 边界情况

| 情况 | 输出 | 原因 |
|---|---|---|
| 链表长度 < 3 | `{-1, -1}` | 无法有临界点 |
| 无临界点（如 `1→2→3`） | `{-1, -1}` | `index` 为空，`n < 2` |
| 只有 1 个临界点 | `{-1, -1}` | 无法计算距离 |
| 所有节点相等（如 `2→2→2`） | `{-1, -1}` | 不满足"严格大于/小于" |

## 相关题目

- [206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/) - 链表基础遍历
- [876. Middle of the Linked List](https://leetcode.com/problems/middle-of-the-linked-list/) - 双指针技巧
- [2181. Merge Nodes in Between Zeros](https://leetcode.com/problems/merge-nodes-in-between-zeros/) - 链表分段处理
