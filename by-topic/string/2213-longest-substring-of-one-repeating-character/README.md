# 2213. Longest Substring of One Repeating Character

## 题目信息

- **难度**：Hard
- **分类**：String, Sliding Window, Data Structure
- **链接**：https://leetcode.com/problems/longest-substring-of-one-repeating-character/

## 题目描述

给定字符串 `s`、修改字符数组 `queryCharacters` 和修改下标数组 `queryIndices`。每次查询都会把 `s[queryIndices[i]]` 修改为 `queryCharacters[i]`。要求返回每次查询后，当前字符串中由**同一种字符连续重复组成**的最长子串长度。

## 解法对比

### 解法一：暴力扫描（`solution.cpp`）

最直接的暴力扫描：

1. 模拟每次单点修改
2. 每次修改后重新从头到尾扫描整个字符串
3. 统计当前连续重复段长度，并维护全局最大值

这个版本的核心思路是正确的，但无法通过正式数据，因为每次查询都重扫整串，整体复杂度过高。

**时间复杂度**：`O(n * m)`

- 单次查询后重新扫描字符串是 `O(m)`
- 一共有 `n` 次查询

这在数据范围较大时会超时。

### 解法二：线段树（`solution_segment_tree.cpp`）

利用线段树维护区间信息，避免每次全量扫描。

**核心思路**：

1. 每个线段树节点维护区间的：
   - `len`：区间长度
   - `lc`/`rc`：区间最左/最右字符
   - `pref`：从左端点开始的最长连续段
   - `suf`：从右端点开始的最长连续段
   - `best`：区间内最长连续段

2. 合并两个子区间时：
   - 继承左右子区间的 `best` 最大值
   - 如果左右边界字符相同，考虑跨中点的连续段：`left.suf + right.pref`
   - 前缀和后缀根据是否能延伸来决定

3. 单点更新时，只需向上更新 `O(log n)` 个祖先节点

**时间复杂度**：`O(n log m)`

- 构建线段树：`O(m)`
- 单次查询更新：`O(log m)`
- 总共 `n` 次查询

**空间复杂度**：`O(m)`

线段树需要 `4m` 的数组空间。

## 关键优化点

暴力版本没有利用"单点修改只会影响附近区间"这一关键性质。

线段树通过维护区间信息，将每次更新的影响范围控制在 `O(log m)` 条路径上，从而大幅降低时间复杂度。

## 代码文件

- `solution.cpp`：暴力扫描版本（会超时）
- `solution_segment_tree.cpp`：线段树优化版本（通过所有测试）
