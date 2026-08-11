# 2996. Smallest Missing Integer Greater Than Sequential Prefix Sum

## 题目信息

- **难度**：Easy
- **分类**：Array, Hash Table
- **链接**：https://leetcode.com/problems/smallest-missing-integer-greater-than-sequential-prefix-sum/

## 题目描述

给定一个整数数组 `nums`。

如果前缀 `nums[0..i]` 满足对所有 `1 <= j <= i` 都有：

```cpp
nums[j] = nums[j - 1] + 1
```

那么这个前缀称为**顺序前缀**。只包含 `nums[0]` 的前缀也算顺序前缀。

要求返回一个最小整数 `x`，满足：

- `x` 没有出现在 `nums` 中
- `x` 大于等于最长顺序前缀的元素和

## 解题思路

先从左到右找到最长顺序前缀，并计算它的和 `prefixSum`。

随后用哈希集合记录数组中所有出现过的整数。从 `prefixSum` 开始向上查找，第一个没有出现在数组中的值就是答案。

步骤如下：

1. 初始化 `prefixSum = nums[0]`
2. 顺着数组向右扫描，只要相邻元素差值为 `1`，就继续把元素加入前缀和
3. 用 `unordered_set` 保存 `nums` 中的所有值
4. 从 `prefixSum` 开始不断加一，直到找到一个不在集合中的整数

## 复杂度

- **时间复杂度**：`O(n)`
- **空间复杂度**：`O(n)`

## 代码

```cpp
// 见 solution.cpp
```
