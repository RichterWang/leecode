# 1510. Stone Game IV

## 题目信息

- **难度**：Hard
- **分类**：Dynamic Programming, Game Theory, Math
- **链接**：https://leetcode.com/problems/stone-game-iv/

## 题目描述

Alice 和 Bob 轮流从一堆石子中拿走**非零完全平方数**个石子，Alice 先手。无法操作的玩家输。双方都最优，判断 Alice 是否必胜。

## 解题思路

这是一道经典的**博弈 DP** 问题，本质上是"必胜态/必败态"判断。

定义 `dp[i]` 表示：

> 当还剩 `i` 个石子时，当前行动玩家是否必胜。

**边界条件：**

```cpp
dp[0] = false
```

因为轮到你时已经没有石子可拿，你无法操作，所以输。

**状态转移：**

对每个 `i`，枚举所有满足 `k * k <= i` 的完全平方数。如果存在某个选择 `k * k`，使得：

```cpp
dp[i - k * k] == false
```

说明你拿走 `k * k` 个石子后，对手会进入必败态，那么当前：

```cpp
dp[i] = true
```

否则，如果所有合法选择都不能让对手进入必败态，当前保持：

```cpp
dp[i] = false
```

从小到大填表，保证依赖项已经计算完毕。

**最终答案：**

```cpp
return dp[n];
```

## 复杂度

- **时间复杂度**：`O(n * sqrt(n))`
- **空间复杂度**：`O(n)`

## 代码

```cpp
// 见 solution.cpp
```

## 相关题目

- LeetCode 877. Stone Game
- LeetCode 1140. Stone Game II
- LeetCode 1406. Stone Game III
