# 3069. Distribute Elements Into Two Arrays I

## 题目信息

- **难度**：Easy
- **分类**：Array, Simulation
- **链接**：https://leetcode.com/problems/distribute-elements-into-two-arrays-i/

## 题目描述

给定一个下标从 1 开始、长度为 n 的整数数组 `nums`。

创建两个数组 `arr1` 和 `arr2`，初始都为空。需要将 `nums` 的所有元素按照以下规则分配到这两个数组中：

1. 将 `nums[1]` 加入 `arr1`
2. 将 `nums[2]` 加入 `arr2`
3. 从 `i = 3` 开始：
   - 如果 `arr1` 的最后一个元素大于 `arr2` 的最后一个元素，将 `nums[i]` 加入 `arr1`
   - 否则，将 `nums[i]` 加入 `arr2`

最后，将 `arr1` 和 `arr2` 连接起来形成结果数组。

返回连接后的整数数组 `result`。

## 解题思路

### 方法：双指针 + 动态插入

算法维护两个指针 `ptr1` 和 `ptr2`，分别追踪结果数组中的两个关键位置：

1. **初始化**：将前两个元素加入结果数组
   - `answer = [nums[0], nums[1]]`
   - `ptr1 = 0`, `ptr2 = 1`

2. **遍历剩余元素**：从 `i = 2` 开始
   - 如果 `answer[ptr1] > answer[ptr2]`：
     - 在 `ptr1` 后面插入 `nums[i]`
     - 同时移动两个指针：`ptr1++`, `ptr2++`
   - 否则：
     - 将 `nums[i]` 追加到数组末尾
     - 只移动 `ptr2++`

3. **边界处理**：
   - 当数组长度为 1 或 2 时，直接返回原数组

### 算法特点

- 根据两个指针位置的值大小关系，决定新元素的插入位置
- `ptr1` 始终指向较早加入的元素
- `ptr2` 在不断向后移动的过程中可能超过 `ptr1`
- 使用 `vector::insert` 在中间位置插入元素（时间复杂度 O(n)）

### 复杂度分析

**时间复杂度**：O(n²)
- 外层循环遍历 n-2 个元素：O(n)
- `vector::insert` 在最坏情况下需要移动后续所有元素：O(n)
- 总体：O(n²)

**空间复杂度**：O(1)
- 不考虑返回数组的空间，只使用常数个额外变量

### 可能的优化方向

如果频繁进行中间插入操作，可以考虑：
- 使用 `list` 代替 `vector`，插入操作降至 O(1)
- 或者先记录插入位置，最后统一重组数组

## 代码

```cpp
class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if(n == 1 || n == 2) return nums;
        vector<int> answer;

        answer.push_back(nums[0]);
        answer.push_back(nums[1]);
        int ptr1 = 0, ptr2 = 1;

        for(int i = 2; i < n; i++)
        {
            if(answer[ptr1] > answer[ptr2]){
                answer.insert(answer.begin() + ptr1 + 1, nums[i]);
                ptr1++;
                ptr2++;
            }
            else{
                answer.push_back(nums[i]);
                ptr2++;
            }
        }
        return answer;
    }
};
```

## 注意事项

- 题目要求数组下标从 1 开始，但实现中使用标准的 0 索引
- `arr1` 和 `arr2` 需要最终连接，顺序是 `arr1` 在前，`arr2` 在后
- 边界情况：当数组长度为 1 或 2 时，直接返回原数组即可

## 相关题目

- [3072. Distribute Elements Into Two Arrays II](https://leetcode.com/problems/distribute-elements-into-two-arrays-ii/) - 本题的进阶版本，使用树状数组优化
