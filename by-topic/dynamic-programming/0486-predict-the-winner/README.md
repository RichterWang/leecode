# 486. Predict the Winner

## 题目信息

- **难度**：Medium
- **分类**：Array, Dynamic Programming, Recursion, Game Theory
- **链接**：https://leetcode.com/problems/predict-the-winner/

## 题目描述

给定一个整数数组 `nums`，两个玩家轮流从数组两端取数，每次取一个。双方都最优决策，判断玩家1是否能保证赢或平局。

## 解题思路

### 核心状态

定义 `score(left, right)`：在区间 `[left, right]` 中，当前行动的玩家比对手多拿多少分。

### 状态转移

- 选左端：`nums[left] - score(left+1, right)`
- 选右端：`nums[right] - score(left, right-1)`

取两者最大值。

### 方法一：递归 + 记忆化搜索

**时间复杂度**：O(n^2)  
**空间复杂度**：O(n^2)

### 方法二：区间 DP

先算短区间，再算长区间。

**时间复杂度**：O(n^2)  
**空间复杂度**：O(n^2)

## 代码

```cpp
// 见 solution.cpp
```

## 相关题目

- LeetCode 877. Stone Game
- LeetCode 1406. Stone Game III
