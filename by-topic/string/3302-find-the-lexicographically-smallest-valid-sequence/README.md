# 3302. Find the Lexicographically Smallest Valid Sequence

## 题目信息

- **难度**：Medium
- **分类**：String, Dynamic Programming, Greedy
- **链接**：https://leetcode.com/problems/find-the-lexicographically-smallest-valid-sequence/

## 题目描述

给定字符串 `word1` 和 `word2`，从 `word1` 中选择一个长度等于 `word2` 的下标序列。选择的字符按顺序组成的字符串需要与 `word2` 相同，或者最多修改其中一个位置后与 `word2` 相同。

在所有满足条件的下标序列中，返回字典序最小的序列；如果不存在，返回空数组。

## 解题思路

### 方法一：压缩后缀可行性 + 贪心构造（推荐）

原始 DP 使用 `dp[i][j][used]` 保存 `word1[i:]` 是否能够匹配 `word2[j:]`，空间复杂度为 `O(|word1| * |word2|)`，在数据范围较大时会超出内存限制。

优化后只保存精确匹配的后缀临界位置：

- `suffixStart[j]` 表示从 `word1[suffixStart[j]:]` 开始，能够精确匹配 `word2[j:]` 的最大起始下标
- `suffixStart[j] == -1` 表示剩余部分无法精确匹配
- `suffixStart[length2] = length1` 表示空字符串可以从任意位置开始匹配

通过从右向左扫描 `word1` 和 `word2`，可以在线性时间内计算 `suffixStart`。之后从左到右贪心选择下标：

1. 如果当前字符相同，直接选择当前最小下标
2. 如果字符不同且替换机会尚未使用，则检查 `word2[j+1:]` 是否可以从 `word1[i+1:]` 精确匹配
3. 如果当前选择不可行，就跳过当前 `word1` 下标

因为所有候选下标按升序尝试，所以第一个可行下标能够保证答案字典序最小。

### 方法二：完整动态规划

保留 `dp[i][j][used]` 表示从 `word1[i:]` 匹配 `word2[j:]` 的可行性，其中：

- `used = 0`：还没有使用允许的一次替换
- `used = 1`：已经使用过替换

该版本便于理解状态转移，但空间复杂度较高，只作为对照实现保存在 `dp_solution.cpp`。

### 方法三：贪心加后缀可行性检查

从 `word2` 的每个位置开始，依次尝试 `word1` 中最靠前的下标，并用双指针检查选择后剩余字符串是否能作为子序列匹配。该实现保存在 `alt_solution.cpp`。

## 复杂度

推荐方法：

- **时间复杂度**：`O(|word1| + |word2|)`
- **空间复杂度**：`O(|word2|)`，不计返回值

完整 DP：

- **时间复杂度**：`O(|word1| * |word2|)`
- **空间复杂度**：`O(|word1| * |word2|)`

直接后缀检查：

- **时间复杂度**：最坏 `O(|word1| * |word2| * (|word1| + |word2|))`
- **空间复杂度**：`O(|word1| + |word2|)`，不计返回值

## 代码

- `solution.cpp`：压缩后缀可行性 + 贪心构造，推荐提交
- `dp_solution.cpp`：完整三维 DP，对照实现
- `alt_solution.cpp`：直接后缀可行性检查
