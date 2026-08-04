# 76. Minimum Window Substring

## 题目信息

- **难度**：Hard
- **分类**：String, Hash Table, Sliding Window
- **链接**：https://leetcode.com/problems/minimum-window-substring/

## 题目描述

给定两个字符串 `s` 和 `t`，在 `s` 中找到一个最短子串，使得该子串包含 `t` 中所有字符及其出现次数。如果不存在这样的子串，返回空字符串 `""`。

## 解题思路

### 方法一：双指针滑动窗口

这是一个标准的滑动窗口问题。

- 右指针负责扩张窗口，把字符纳入当前子串
- 左指针负责在窗口满足条件后尽量收缩
- 每当窗口满足覆盖条件时，就尝试更新最短答案

### 核心数据结构

使用两张哈希表：

- `reference`：记录 `t` 中每个字符需要多少次
- `window`：记录当前窗口中每个字符出现多少次

### 两个关键变量

#### `required`

表示 `t` 中一共需要满足多少种不同字符：

```cpp
int required = reference.size();
```

#### `formed`

表示当前窗口里，已经有多少种字符满足了需求。

注意：

- `formed` 不是窗口里相关字符的总个数
- 而是“满足要求的字符种类数”

例如 `t = "AABC"` 时：

- `reference['A'] = 2`
- `reference['B'] = 1`
- `reference['C'] = 1`
- `required = 3`

只有当窗口中的 `A` 数量达到 2 时，`A` 这一类字符才算满足，`formed` 才能增加。

### 窗口满足条件的判断

不需要每次写一个完整 `check` 函数去扫描整张表。

最高效的做法是直接判断：

```cpp
formed == required
```

这样每次字符进入或离开窗口时，只需要局部更新状态，而不用反复遍历 `reference`。

### 扩张窗口时如何更新 `formed`

当右指针加入字符 `s[right]` 时：

- 如果它是 `t` 中需要的字符，就更新 `window[s[right]]`
- 只有当：

```cpp
window[s[right]] == reference[s[right]]
```

时，才说明这一类字符刚好满足需求，此时才能 `formed++`

### 收缩窗口时如何更新 `formed`

当左指针准备移出字符 `s[left]` 时：

- 如果这个字符不在 `reference` 中，直接跳过即可
- 如果它在 `reference` 中，并且当前刚好满足需求：

```cpp
window[s[left]] == reference[s[left]]
```

那么移出之后就会不再满足，所以要先 `formed--`，再减少窗口计数

### 为什么删掉关键字符后不用立刻 `break`

因为在删掉左端字符之前，当前合法窗口已经被记录成候选答案了。

然后如果删掉后不再满足条件，`formed == required` 会在下一轮 `while` 判断中自动失效，循环自然退出，不需要手动 `break`。

这也是滑动窗口代码成立的关键顺序：

1. 先记录当前合法窗口
2. 再尝试收缩它
3. 如果收缩后失效，由 `while` 条件自动停止

### 为什么不能最后直接 `substr(i, j)`

题目要求的是“历史上最短的合法窗口”，而不是循环结束时的那个窗口。

因此必须在每次窗口合法时记录：

- 最优起点 `bestStart`
- 最优长度 `bestLen`

最后返回：

```cpp
s.substr(bestStart, bestLen)
```

## 复杂度

**时间复杂度**：`O(|s| + |t|)`  
每个字符最多被左右指针各访问一次。

**空间复杂度**：`O(|Σ|)`  
用于维护哈希表，字符集固定时可视为常数。

## 代码

```cpp
// 见 solution.cpp
```

## 相关题目

- LeetCode 3. Longest Substring Without Repeating Characters
- LeetCode 438. Find All Anagrams in a String
- LeetCode 567. Permutation in String
