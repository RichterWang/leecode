# 2091. Removing Minimum and Maximum From Array

## 题目信息

- **难度**：Medium
- **分类**：Greedy, Array
- **链接**：https://leetcode.com/problems/removing-minimum-and-maximum-from-array/

## 题目描述

给定一个下标从 0 开始的整数数组 `nums`（**互不相同**）。

数组中存在**最小值**和**最大值**。删除操作可以从数组的前端或末端移除一个元素。

返回**移除最小值和最大值**所需的**最少删除次数**。

**示例**：

```
输入：nums = [2, 10, 7, 5, 4, 1, 8, 6]
输出：5

解释：
- 最小值 1 在下标 5
- 最大值 10 在下标 1
- 方案 1：从前删 6 个（删掉 [2,10,7,5,4,1]）
- 方案 2：从后删 3 个（删掉 [8,6,1]）+ 从前删 2 个（删掉 [2,10]）= 5 ✓
最少 5 次
```

## 解题思路

### 核心观察

由于只能从前端或后端删除，要覆盖两个目标位置，有四种方案：

1. **纯前缀删除**：一直从前删到覆盖两者中更靠后的那个
2. **纯后缀删除**：一直从后删到覆盖两者中更靠前的那个
3. **混合 1**：从前删到最小值，从后删到最大值
4. **混合 2**：从前删到最大值，从后删到最小值

取四种方案中的最小值即可。

### 方法：定位 + 枚举四种方案

#### 算法步骤

**第一步：找到最小值和最大值**

```cpp
vector<int> sorted = nums;
sort(sorted.begin(), sorted.end());
int smallest = sorted[0];
int biggest = sorted[n - 1];
```

**第二步：定位它们在原数组中的下标**

由于题目保证元素互不相同，min 和 max 各有唯一位置。用两次遍历分别找：

- 前向扫描找到 `smallest_index.first` 和 `biggest_index.first`（首次出现）
- 后向扫描找到 `smallest_index.second` 和 `biggest_index.second`（末次出现，但因为唯一，其实就是同一位置）

> 注：代码中前后两次扫描是为了兼容"有重复值"的假设，但实际题目保证互不相同，`.first` 和 `.second` 会相等。

**第三步：计算四种方案的代价**

设 `idxMin`、`idxMax` 为最小值和最大值的下标（0-indexed），数组长度为 `n`。

| 方案 | 公式 | 含义 |
|---|---|---|
| `step[0]` | `max(idxMin, idxMax) + 1` | 从前删到覆盖两者中更靠后的 |
| `step[1]` | `n - min(idxMin, idxMax)` | 从后删到覆盖两者中更靠前的 |
| `step[2]` | `idxMin + 1 + (n - idxMax)` | 前删到 min，后删到 max |
| `step[3]` | `idxMax + 1 + (n - idxMin)` | 前删到 max，后删到 min |

代码中用三元运算符实现：

```cpp
// step[0]: max(firstMin, firstMax) + 1
step[0] = smallest_index.first > biggest_index.first 
        ? smallest_index.first + 1 
        : biggest_index.first + 1;

// step[1]: n - min(lastMin, lastMax)
step[1] = smallest_index.second > biggest_index.second 
        ? n - biggest_index.second   // biggest 更靠前，选它
        : n - smallest_index.second;

step[2] = smallest_index.first + 1 + n - biggest_index.second;
step[3] = biggest_index.first + 1 + n - smallest_index.second;
```

**第四步：取最小值**

```cpp
sort(step.begin(), step.end());
return step[0];
```

### 三元运算符解读

```cpp
smallest_index.first > biggest_index.first ? smallest_index.first + 1 : biggest_index.first + 1
```

等价于：

```cpp
if (smallest_index.first > biggest_index.first) {
    return smallest_index.first + 1;  // min 更靠后，前缀要到 min
} else {
    return biggest_index.first + 1;   // max 更靠后，前缀要到 max
}
```

本质就是 `max(idxMin, idxMax) + 1`。

```cpp
smallest_index.second > biggest_index.second ? n - biggest_index.second : n - smallest_index.second
```

条件为真时，`biggest_index.second` 更小（更靠前），后缀要覆盖它；为假时 `smallest_index.second` 更小。等价于 `n - min(idxMin, idxMax)`。

### 复杂度分析

**时间复杂度**：O(n log n)
- 排序找 min/max：O(n log n)
- 两次线性扫描：O(n)
- 瓶颈在排序

**空间复杂度**：O(n)
- 复制了一份数组用于排序

### 优化建议

排序只是为了找 min/max，可以用 `*min_element(...)` 和 `*max_element(...)` 替代，降低到 O(n)：

```cpp
int smallest = *min_element(nums.begin(), nums.end());
int biggest = *max_element(nums.begin(), nums.end());
```

然后一次遍历同时找到两个下标：

```cpp
int idxMin = -1, idxMax = -1;
for (int i = 0; i < n; i++) {
    if (nums[i] == smallest) idxMin = i;
    if (nums[i] == biggest) idxMax = i;
}
```

时间复杂度降为 O(n)，空间 O(1)。

## 代码

```cpp
class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());
        int smallest = sorted[0];
        int biggest = sorted[n - 1];
        if(smallest == biggest) return n; // 所有元素相同

        pair<int, int> smallest_index, biggest_index;

        // 前向扫描找首次出现
        bool is_padded_smallest = false;
        bool is_padded_biggest = false;
        int i = 0;
        while(i < n)
        {
            if(nums[i] == smallest) {
                smallest_index.first = i;
                is_padded_smallest = true;
            }
            else if(nums[i] == biggest){
                biggest_index.first = i;
                is_padded_biggest = true;
            }
            if(is_padded_smallest && is_padded_biggest) break;
            i++;
        }

        // 后向扫描找末次出现
        is_padded_biggest = false;
        is_padded_smallest = false;
        i = n - 1;
        while(i >= 0)
        {
            if(nums[i] == smallest) {
                smallest_index.second = i;
                is_padded_smallest = true;
            }
            else if(nums[i] == biggest){
                biggest_index.second = i;
                is_padded_biggest = true;
            }
            if(is_padded_smallest && is_padded_biggest) break;
            i--;
        }

        // 四种方案
        vector<int> step(4);
        step[0] = smallest_index.first > biggest_index.first ? smallest_index.first + 1 : biggest_index.first + 1;
        step[1] = smallest_index.second > biggest_index.second ? n - biggest_index.second : n - smallest_index.second;
        step[2] = smallest_index.first + 1 + n - biggest_index.second;
        step[3] = biggest_index.first + 1 + n - smallest_index.second;

        sort(step.begin(), step.end());
        return step[0];
    }
};
```

## 关键细节

### 1. 为什么前后各扫一次？

原代码设计考虑了"元素可能重复"的情况（虽然题目保证互不相同）：

- `.first` 存首次出现（从前往后扫）
- `.second` 存末次出现（从后往前扫）

如果元素真的唯一，`.first == .second`，前后两次扫描其实多余，一次就够。

### 2. 边界情况

```cpp
if(smallest == biggest) return n;
```

所有元素相同时，min 和 max 重合，需要删掉整个数组，返回 `n`。

### 3. step[2] 和 step[3] 不会越界吗？

混合方案的代价是前缀 + 后缀，理论上最坏情况是 `(n-1) + n = 2n-1`（两个目标在数组两端），但因为我们取四个方案中的最小值，纯前缀或纯后缀一定 ≤ n，所以最终结果不会超过 n。

## 相关题目

- [1749. Maximum Absolute Sum of Any Subarray](https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/) - 也需要枚举多种方案
- [2195. Append K Integers With Minimal Sum](https://leetcode.com/problems/append-k-integers-with-minimal-sum/) - 贪心找最值
