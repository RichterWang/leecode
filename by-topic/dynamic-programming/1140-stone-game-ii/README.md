# 1140. Stone Game II

## 题目信息

- **难度**：Medium
- **分类**：Array, Dynamic Programming, Game Theory
- **链接**：https://leetcode.com/problems/stone-game-ii/

## 题目描述

给定一排石子 `piles`，Alice 先手。初始 `M = 1`，每回合可以从左端取走 `1` 到 `2M` 堆石子；取走 `x` 堆后，下一轮 `M = max(M, x)`。双方都最优，求 Alice 最多能拿多少石子。

## 解题思路

定义 `dp[i][M]` 表示：从第 `i` 堆开始、当前参数为 `M` 时，当前行动玩家最多能获得的石子数。

先预处理后缀和 `suffixSum[i]`，表示从 `i` 到结尾的总石子数。

- 如果 `n - i <= 2 * M`，当前玩家可以一次拿完剩余所有石子，直接返回 `suffixSum[i]`
- 否则枚举当前拿走的堆数 `x`，其中 `1 <= x <= 2M`
- 选择 `x` 后，对手进入状态 `dp[i + x][max(M, x)]`
- 当前玩家本轮的收益就是 `suffixSum[i] - dp[i + x][max(M, x)]`
- 取所有合法 `x` 的最大值

由于状态只依赖更靠后的 `i`，所以从后往前填表。

## 复杂度

- **时间复杂度**：`O(n^3)`
- **空间复杂度**：`O(n^2)`

## 代码

```cpp
// 见 solution.cpp
```
