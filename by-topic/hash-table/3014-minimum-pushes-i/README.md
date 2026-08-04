# 3014. Minimum Number of Pushes to Type Word I

## 题目信息

- **难度**：Easy
- **分类**：String, Greedy
- **链接**：https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-i/

## 题目描述

字符互不相同，把字母重新映射到 8 个按键上，求输入 `word` 的最少按键次数。

## 解题思路

因为每个字符只出现一次，所以不需要统计频率。直接按层分配：前 8 个字符按 1 次，接下来 8 个按 2 次，以此类推。

第 `i` 个字符的代价是 `i / 8 + 1`。

**时间复杂度**：O(n)  
**空间复杂度**：O(1)

## 代码

```cpp
// 见 solution.cpp
```

## 相关题目

- LeetCode 3016. Minimum Number of Pushes to Type Word II
