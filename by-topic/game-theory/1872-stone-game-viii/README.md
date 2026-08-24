# 1872. 石子游戏 VIII (Stone Game VIII)

## 题目描述

Alice 和 Bob 玩一个游戏，两人轮流操作，**Alice 先手**。

总共有 `n` 个石子排成一行。轮到某个玩家的回合时，如果石子的数目**大于 1**，他将执行以下操作：

- 选择一个整数 `x > 1`，并且**移除**最左边的 `x` 个石子
- 将移除的石子价值之**和**累加到该玩家的分数中
- 将一个**新的石子**放在最左边，且新石子的值为被移除石子值之和

当只剩下**一个**石子时，游戏结束。

Alice 和 Bob 的**分数之差**为 `Alice 的分数 - Bob 的分数`。Alice 的目标是**最大化**分数差，Bob 的目标是**最小化**分数差。

给你一个长度为 `n` 的整数数组 `stones`，其中 `stones[i]` 是从左边起第 `i` 个石子的价值。请返回在双方都采用**最优**策略的情况下，Alice 和 Bob 的分数之差。

---

## 示例

### 示例 1

```
输入: stones = [-1,2,-3,4,-5]
输出: 5
解释:
- Alice 移除最左边的 4 个石子，得分 (-1) + 2 + (-3) + 4 = 2，
  数组变为 [2, -5]
- Bob 移除剩下的 2 个石子，得分 2 + (-5) = -3，数组变为 [-3]
- 分数差为 2 - (-3) = 5
```

### 示例 2

```
输入: stones = [7,-6,5,10,5,-2,-6]
输出: 13
```

### 示例 3

```
输入: stones = [-10,-12]
输出: -22
解释: Alice 只能把两颗全部拿走，得 -22，Bob 得 0
```

---

## 约束条件

- `n == stones.length`
- `2 <= n <= 10^5`
- `-10^4 <= stones[i] <= 10^4`

---

## 关键理解

### 1. 「先手一口气拿完」不一定最优

不少人第一反应是：Alice 直接取走全部石子，Bob 一分都拿不到，岂不必胜？

这在**全为正数**时成立，但 `stones[i]` **可以为负**。全拿意味着把所有负数也吞进自己的分数里，此时留一部分给对手反而更优。这正是本题成为博弈题的原因。

### 2. 每次得分恰好是一个前缀和

关键性质：**每回合的得分一定等于当前最左边那一堆的总和**，而那一堆恰好是原数组的一个前缀。

设 `prefixSum[i] = stones[0] + ... + stones[i-1]`。若整局的取法依次取到位置 `j₁ < j₂ < ... < j_m = n`，则

```
Alice: prefixSum[j₁]
Bob:   prefixSum[j₂]
Alice: prefixSum[j₃]
...
分数差 = prefixSum[j₁] - prefixSum[j₂] + prefixSum[j₃] - ...
```

于是问题转化为：**在 `prefixSum[2..n]` 中选一个递增下标序列（必须以 `n` 结尾），双方轮流各取一项，交错求和，Alice 最大化、Bob 最小化。**

> ⚠️ 常见误区：认为「合并出的新石子双方都拿到了，可以抵消」。这是错的。`prefixSum[j₁]` 和 `prefixSum[j₂]` 是**不同的数**，不会两两约掉；`prefixSum` 每被向后传递一次就会换一次符号，而符号取决于后续还要走几步，这个步数本身是被优化决定的，不是常数偏移，无法提出去。

---

## 解题思路

### 状态定义

```
dp[i] = 当前面 i 个原始石子已经合并成一颗时，轮到的玩家（先手）能取得的最大分数差
```

此时局面为 `[合并石子(值 = prefixSum[i]), stones[i], ..., stones[n-1]]`。

### 状态转移

先手若选择「取到第 `i` 个原始石子」（即取走合并石子 + `stones[i]`），得分为

```
prefixSum[i] + stones[i] = prefixSum[i + 1]
```

随后对手面对状态 `i + 1`，其最优差值为 `dp[i + 1]`，故本分支的差值为 `prefixSum[i+1] - dp[i+1]`。

若先手不在此处停手、继续往右取，则等价于直接落入状态 `i + 1` 由自己继续决策，差值为 `dp[i + 1]`。

```
dp[i] = max( dp[i + 1],  prefixSum[i + 1] - dp[i + 1] )
```

### 边界（本题最易错的一处）

```cpp
dp[n - 1] = prefixSum[n];
```

`i = n - 1` 时，局面只有「合并石子 + `stones[n-1]`」共 2 颗，而规则要求 `x > 1`，因此**必须全部取走，没有第二个选择**。

如果偷懒写成 `dp[n] = 0` 再让循环从 `i = n - 1` 开始，就变成

```cpp
dp[n-1] = max(dp[n], prefixSum[n] - dp[n]) = max(0, prefixSum[n])
```

那个 `0` 代表「跳过、不在这里取」——但这一步**不存在跳过的选项**。当 `prefixSum[n] < 0` 时会错误地取到 0。

反例 `stones = [-1, -2]`：`prefixSum = [0, -1, -3]`，错误写法得 `max(0, -3) = 0`，正确答案是 `-3`。

**只有最后一格是特例**，因此必须显式初始化，循环从 `i = n - 2` 起。

### 答案

```cpp
return dp[1];
```

Alice 首次操作至少取 2 颗，取完后前 2 个已合并，因此起点是 `dp[1]`，而不是 `dp[0]`。

---

## 代码

```cpp
int stoneGameVIII(vector<int>& stones) {
    int n = static_cast<int>(stones.size());

    vector<int> prefixSum(n + 1);
    for (int i = 1; i <= n; i++)
        prefixSum[i] = prefixSum[i - 1] + stones[i - 1];

    vector<int> dp(n + 1);
    dp[n - 1] = prefixSum[n];  // 只剩 2 颗，必须全拿
    for (int i = n - 2; i >= 1; i--)
        dp[i] = max(dp[i + 1], prefixSum[i + 1] - dp[i + 1]);

    return dp[1];
}
```

---

## 手动推演：`stones = [-1, 2, -3, 4, -5]`

```
prefixSum = [0, -1, 1, -2, 2, -3]

dp[4] = prefixSum[5]                        = -3
dp[3] = max(dp[4], prefixSum[4] - dp[4]) = max(-3, 2 - (-3)) = 5
dp[2] = max(dp[3], prefixSum[3] - dp[3]) = max( 5, -2 - 5  ) = 5
dp[1] = max(dp[2], prefixSum[2] - dp[2]) = max( 5,  1 - 5  ) = 5

答案 = dp[1] = 5   ✓
```

---

## 复杂度分析

- **时间复杂度**：`O(n)`，一次前缀和 + 一次线性 DP
- **空间复杂度**：`O(n)`；由于 `dp[i]` 只依赖 `dp[i+1]`，可用单变量滚动优化到 `O(1)`

### O(1) 空间版本

```cpp
int stoneGameVIII(vector<int>& stones) {
    int n = stones.size();
    vector<int> pre(n);
    partial_sum(stones.begin(), stones.end(), pre.begin());

    int dp = pre[n - 1];
    for (int i = n - 2; i >= 1; i--)
        dp = max(dp, pre[i] - dp);
    return dp;
}
```

> 注意此版本用的是 `pre[i] = stones[0..i]`（无前导 0），与上文 `prefixSum` 下标相差 1，即 `pre[i] == prefixSum[i + 1]`。

---

## 踩坑记录

| 错误写法 | 后果 |
|---|---|
| `dp[n-1] = stones[n-1]` | 漏掉合并进来的 `prefixSum[n-1]`，错误值沿 DP 链一路污染 |
| 转移式写成 `prefixSum[k] - prefixSum[i] - dp[k]` | 误把已合并石子排除在得分外；`[-1,2,-3,4,-5]` 输出 7（应为 5） |
| 内层再套一层 `for k` 求 `max` | `O(n²)`，`n = 1e5` 直接 TLE。该式是后缀最大值，`dp[i+1]` 已经承担了这个角色 |
| `return dp[0]` | `dp[0]` 表示「0 颗已合并」，与「首次至少取 2 颗」矛盾 |
| 省掉 `dp[n-1]` 初始化、循环从 `n-1` 起 | 引入不存在的「跳过」选项，`prefixSum[n] < 0` 时答案错误 |

---

## 相关题目

- [486. 预测赢家](../../dynamic-programming/0486-predict-the-winner/)
- [1140. 石子游戏 II](../../dynamic-programming/1140-stone-game-ii/)
- [1406. 石子游戏 III](../../dynamic-programming/1406-stone-game-iii/)
- [1510. 石子游戏 IV](../../dynamic-programming/1510-stone-game-iv/)
- [1563. 石子游戏 V](../../dynamic-programming/1563-stone-game-v/)
- [2029. 石子游戏 IX](../../dynamic-programming/2029-stone-game-ix/)
- [1927. 求和游戏](../1927-sum-game/)
