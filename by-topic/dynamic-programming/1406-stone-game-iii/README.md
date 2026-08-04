# 1406. Stone Game III

## 题目信息

- **难度**：Hard
- **分类**：Array, Dynamic Programming, Game Theory
- **链接**：https://leetcode.com/problems/stone-game-iii/

## 题目描述

两个玩家轮流从数组左端取 1、2 或 3 个石子，双方都最优决策。返回胜者名字，平局返回 `Tie`。

## 解题思路

定义 `dp[i]` 表示从下标 `i` 开始，当前行动玩家比对手多拿多少分。

枚举当前位置可以取 1、2、3 个石子三种选择：

- 取 1 个：`stoneValue[i] - dp[i+1]`
- 取 2 个：`stoneValue[i] + stoneValue[i+1] - dp[i+2]`
- 取 3 个：`stoneValue[i] + stoneValue[i+1] + stoneValue[i+2] - dp[i+3]`

取三者最大值作为 `dp[i]`。

从右往左填表。

**时间复杂度**：O(n)  
**空间复杂度**：O(n)

## 代码

```cpp
// 见 solution.cpp
```

## 相关题目

- LeetCode 486. Predict the Winner
- LeetCode 877. Stone Game
