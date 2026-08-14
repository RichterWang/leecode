# 3090. Maximum Length Substring With Two Occurrences

## 题目信息

- **难度**：Easy
- **分类**：String, Hash Table, Sliding Window
- **链接**：https://leetcode.com/problems/maximum-length-substring-with-two-occurrences/

## 题目描述

给定一个字符串 `s`，要求找出最长的子字符串，使得其中每个字符都最多出现两次，并返回这个子字符串的最大长度。

## 解题思路

使用滑动窗口维护当前合法子字符串 `[left, right]`：

- `reference` 记录当前窗口内每个字符出现的次数
- 初始时先把 `s[left]` 放入窗口，`right` 从 `1` 开始向右扩展
- 如果 `s[right]` 在当前窗口中的出现次数小于 `2`，则可以直接加入窗口，并用当前窗口长度更新答案
- 如果 `s[right]` 已经出现了 `2` 次，那么将其加入后会变成 `3` 次，此时不断移动 `left`，直到该字符在窗口中的出现次数重新不超过 `2`

这个过程保证窗口始终朝右移动，每个字符最多被加入和移出窗口一次。

## 代码中的窗口含义

- `left`：当前合法窗口的左边界
- `right`：当前准备加入窗口的字符位置
- `reference[c]`：字符 `c` 在当前窗口中的出现次数

当 `reference[s[right]] < 2` 时，加入 `s[right]` 后窗口仍然合法；
当 `reference[s[right]] >= 2` 时，加入后需要收缩左边界，直到窗口恢复合法。

## 复杂度

- **时间复杂度**：`O(n)`，左右指针都只会单调向右移动。
- **空间复杂度**：`O(k)`，其中 `k` 为字符集大小；对英文小写字母场景可视为常数空间。

## 代码

```cpp
// 见 solution.cpp
```
