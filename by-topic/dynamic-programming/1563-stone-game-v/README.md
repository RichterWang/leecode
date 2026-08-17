# 1563. Stone Game V

## 题目信息

- **难度**：Hard
- **分类**：Array, Dynamic Programming, Prefix Sum, Game Theory
- **链接**：https://leetcode.com/problems/stone-game-v/

## 题目描述

给定一排石子 `stoneValue`。每一轮 Alice 先将当前这排石子切分成左右两个非空连续部分，Bob 会丢弃其中元素和更大的那一部分，Alice 获得剩下那一部分的元素和作为本轮得分。

- 如果左半部分和右半部分不相等，Bob 一定丢掉和更大的那边。
- 如果两边和相等，Alice 可以决定保留左边还是右边。
- 之后游戏在被保留下来的那一部分上继续进行。
- 当只剩一块石子时，游戏结束。

要求返回 Alice 能获得的最大总分。

## 解题思路

这题适合用区间动态规划。

定义：

```cpp
dp[left][right]
```

表示当前只在区间 `stoneValue[left..right]` 上进行游戏时，Alice 最多可以获得的总分。

### 状态初始化

当区间内只剩一个石子时，无法继续切分，因此：

```cpp
dp[i][i] = 0
```

### 前缀和

为了快速计算任意区间的元素和，先预处理前缀和数组：

```cpp
prefixsum[i + 1] = prefixsum[i] + stoneValue[i]
```

这样区间和可以在 `O(1)` 时间得到：

```cpp
sum(l, r) = prefixsum[r + 1] - prefixsum[l]
```

### 状态转移

对于每个区间 `[left, right]`，枚举切分点 `k`，把区间分成：

- 左边 `[left, k]`
- 右边 `[k + 1, right]`

设：

```cpp
leftSum = sum(left, k)
rightSum = sum(k + 1, right)
```

分三种情况讨论：

1. 如果 `leftSum < rightSum`
   - Bob 会丢弃右边
   - Alice 本轮得到 `leftSum`
   - 后续继续在左区间上进行

```cpp
leftSum + dp[left][k]
```

2. 如果 `leftSum > rightSum`
   - Bob 会丢弃左边
   - Alice 本轮得到 `rightSum`
   - 后续继续在右区间上进行

```cpp
rightSum + dp[k + 1][right]
```

3. 如果 `leftSum == rightSum`
   - Alice 可以选择保留更优的一边

```cpp
leftSum + max(dp[left][k], dp[k + 1][right])
```

对所有切分点取最大值即可。

### 填表顺序

因为 `dp[left][right]` 依赖更短区间的结果，所以按区间长度从小到大递推：

- 长度为 `1` 的区间先初始化
- 再计算长度为 `2, 3, ..., n` 的区间

## 复杂度

- **时间复杂度**：`O(n^3)`，需要枚举区间长度、区间起点和切分点。
- **空间复杂度**：`O(n^2)`，用于保存区间 DP 状态。

## 代码

```cpp
// 见 solution.cpp
```
