# 3345. Smallest Divisible Digit Product I

## 题目信息

- **难度**：Easy
- **分类**：Math, Number Theory, Enumeration
- **链接**：https://leetcode.com/problems/smallest-divisible-digit-product-i/

## 题目描述

给定正整数 `n` 和 `t`，从 `n` 开始向上寻找最小的整数，使这个整数所有数位的乘积能够被 `t` 整除。

返回满足条件的最小整数。

题目约束保证 `n` 和 `t` 较小，其中 `t <= 10`，因此可以直接枚举候选数字。

## 解题思路

### 方法一：枚举 + 数位乘积

从 `n` 开始依次检查每个整数：

1. 拆出当前数字的各个数位
2. 计算所有数位的乘积
3. 判断数位乘积是否满足 `product % t == 0`
4. 第一个满足条件的数字就是答案

由于是从小到大枚举，所以第一个找到的数字一定是最小答案。

### 数位提取

对于三位数 `i`：

- 个位：`i % 10`
- 十位：`(i / 10) % 10`
- 百位：`(i / 100) % 10`

因此三位数的数位乘积为：

```cpp
(i % 10) * ((i / 10) % 10) * ((i / 100) % 10)
```

当前解法根据数字位数分别处理一位数、两位数和三位数。

### 为什么找到第一个就可以返回

候选数字按照 `n, n + 1, n + 2, ...` 的顺序检查。

因此第一个满足条件的数字前面不存在更小的可行数字，直接返回即可。

### 复杂度

设实际检查了 `k` 个候选数字。

**时间复杂度**：`O(k)`，当前约束下 `k` 很小。

**空间复杂度**：`O(1)`。

## 代码

```cpp
// 见 solution.cpp
```

## 相关题目

- LeetCode 3348. Smallest Divisible Digit Product II
- LeetCode 2520. Count the Digits That Divide a Number
