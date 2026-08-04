# 73. Set Matrix Zeroes

## 题目信息

- **难度**：Medium
- **分类**：Array, Hash Table, Matrix
- **链接**：https://leetcode.com/problems/set-matrix-zeroes/

## 题目描述

给定一个 `m x n` 的整数矩阵 `matrix`，如果一个元素为 `0`，则将其所在行和列的所有元素都设为 `0`。

## 解题思路

### 方法一：标记数组法

先遍历整个矩阵，记录哪些行和列需要置零；再统一置零。这样可以避免边遍历边修改带来的错误扩散。

**时间复杂度**：O(m * n)  
**空间复杂度**：O(m + n)

## 代码

```cpp
// 见 solution.cpp
```

## 相关题目

- LeetCode 289. Game of Life
