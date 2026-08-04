# 3016. Minimum Number of Pushes to Type Word II

## 题目信息

- **难度**：Medium
- **分类**：String, Greedy, Sorting, Hash Table
- **链接**：https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-ii/

## 题目描述

字符可以重复出现，把字母重新映射到 8 个按键上，求输入 `word` 的最少按键次数。

## 解题思路

先统计每个字符频率，再按频率从大到小排序。高频字符优先占低代价位置。

第 `i` 个频率的代价是 `i / 8 + 1`，总贡献为 `频率 * 代价`。

提供两个版本：
- `unordered_map` 版本
- 长度 26 的数组优化版本

**时间复杂度**：O(n + k log k)，k <= 26  
**空间复杂度**：O(k)

## 代码

```cpp
// 见 solution.cpp
```

## 相关题目

- LeetCode 3014. Minimum Number of Pushes to Type Word I
