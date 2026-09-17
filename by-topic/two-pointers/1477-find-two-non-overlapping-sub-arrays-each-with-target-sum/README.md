# 1477. 找两个和为目标值且不重叠的子数组

**难度**: Medium

## 题目描述

给你一个整数数组 `arr` 和一个整数值 `target`。

请你在 `arr` 中找**两个互不重叠的子数组**且它们的和都等于 `target`。可能会有多种方案，请你返回满足要求的两个子数组长度和的**最小值**。

请返回满足要求的最小长度和，如果无法找到这样的两个子数组，请返回 `-1`。

## 示例

### 示例 1
```
输入：arr = [3,2,2,4,3], target = 3
输出：2
解释：只有两个子数组和为 3 （[3] 和 [3]）。它们的长度和为 2。
```

### 示例 2
```
输入：arr = [7,3,4,7], target = 7
输出：2
解释：尽管我们有 3 个和为 7 的子数组（[7], [3,4] 和 [7]），但我们会选择第一个和第三个子数组，因为它们的长度和 2 是最小值。
```

### 示例 3
```
输入：arr = [4,3,2,6,2,3,4], target = 6
输出：-1
解释：我们只有一个和为 6 的子数组。
```

## 约束条件

- `1 <= arr.length <= 10^5`
- `1 <= arr[i] <= 1000`
- `1 <= target <= 10^8`

## 解题思路

### 核心思想

使用**滑动窗口 + 前缀最小值**的方法，一次遍历找到答案。

### 算法步骤

1. **滑动窗口**：使用双指针 `left` 和 `right` 维护一个窗口，找出所有和为 `target` 的子数组
2. **前缀最小值数组** `prefixmin[i]`：记录在位置 `i` 及之前，和为 `target` 的最短子数组长度
3. **组合答案**：当找到一个子数组 `[left, right]` 时，检查 `prefixmin[left-1]`（前面不重叠的最短子数组），更新最小长度和

### 关键变量

- `temp`：当前窗口的和
- `current`：当前遍历到的最短子数组长度
- `prefixmin[i]`：位置 `i` 及之前的最短子数组长度
- `result`：最终答案（两个子数组长度之和的最小值）

### 滑动窗口逻辑

```
while (right < n):
    1. temp += arr[right]  // 扩展窗口
    2. if temp > target:   // 缩小窗口
          while (temp > target && left < right):
              temp -= arr[left]
              left++
    3. if temp == target:  // 找到目标子数组
          更新答案和前缀最小值
    4. right++
```

### 图解示例

以 `arr = [3,2,2,4,3], target = 3` 为例：

```
位置:    0  1  2  3  4
数组:   [3, 2, 2, 4, 3]

right=0: temp=3,  找到 [0,0]✅, len=1, current=1, prefixmin[0]=1
right=1: temp=5→2, 不满足
right=2: temp=4,   不满足
right=3: temp=8→4, 不满足
right=4: temp=7→3, 找到 [4,4]✅, len=1
         检查 prefixmin[3]=1 (即子数组[0,0])
         result = 1 + 1 = 2 ✅
```

## 复杂度分析

- **时间复杂度**：O(n)
  - `right` 指针遍历数组一次
  - `left` 指针最多移动 n 次
  - 每个元素最多被访问两次
  
- **空间复杂度**：O(n)
  - `prefixmin` 数组占用 O(n) 空间

## 标签

- 数组
- 双指针
- 滑动窗口
- 前缀和
- 动态规划

## 相关题目

- [209. 长度最小的子数组](https://leetcode.cn/problems/minimum-size-subarray-sum/)
- [560. 和为 K 的子数组](https://leetcode.cn/problems/subarray-sum-equals-k/)
- [718. 最长重复子数组](https://leetcode.cn/problems/maximum-length-of-repeated-subarray/)
