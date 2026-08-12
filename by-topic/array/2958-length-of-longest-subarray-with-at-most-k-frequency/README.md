# 2958. Length of Longest Subarray With at Most K Frequency

## 题目信息

- **难度**：Medium
- **分类**：Array, Hash Table, Sliding Window
- **链接**：https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/

## 题目描述

给定整数数组 `nums` 和整数 `k`。

如果一个数组中每个元素的出现次数都不超过 `k`，则称它为好数组。要求返回 `nums` 中最长好子数组的长度。

子数组必须是原数组中连续且非空的一段元素。

## 解题思路

使用双指针滑动窗口维护当前子数组 `[left, right]`：

- `right` 每次向右扩展一个元素
- 使用 `unordered_map<int, int>` 记录当前窗口中每个元素的频率
- 新元素加入后，只可能导致这个新元素的频率超过 `k`
- 如果 `nums[right]` 的频率超过 `k`，不断移动 `left`，并减少离开窗口的元素频率，直到窗口恢复合法
- 当前窗口恢复合法后，用 `right - left + 1` 更新最长长度

本实现中，答案只在扩展后没有触发收缩时更新。因为触发收缩时，窗口最终长度不会超过扩展前已经处理过的合法窗口长度；也可以把更新答案统一放在收缩循环之后，结果相同。

## 代码中的边界

- 空数组直接返回 `0`
- `right` 的范围是 `[0, nums.size())`，因此使用 `while (right < n)` 防止越界
- 窗口频率表动态维护，不需要预先统计整个数组的频率

## 复杂度

- **时间复杂度**：`O(n)`。左右指针都只向右移动，每个元素最多进入和离开窗口一次。
- **空间复杂度**：`O(n)`，最坏情况下哈希表保存 `n` 个不同元素。

## 代码

```cpp
// 见 solution.cpp
```
