# 3718. 缺失的最小倍数 (Missing Smallest Multiple)

## 题目描述

给你一个整数数组 `nums` 和一个整数 `k`，请返回从 `nums` 中缺失的、**最小的正整数 k 的倍数**。

**倍数**指能被 k 整除的任意正整数。

---

## 示例

### 示例 1

```
输入: nums = [3, 6, 9], k = 3
输出: 12
解释: 
- 3, 6, 9 都在数组中
- 12 是第一个缺失的 3 的倍数
```

### 示例 2

```
输入: nums = [5, 10, 20], k = 5
输出: 15
解释:
- 5, 10 在数组中
- 15 缺失，是最小的缺失倍数
```

### 示例 3

```
输入: nums = [1, 2, 3, 4], k = 7
输出: 7
解释:
- 数组中没有 7 的倍数
- 答案是 7
```

---

## 约束条件

- `1 <= nums.length <= 10^5`
- `1 <= nums[i], k <= 10^9`

---

## 解题思路

### 方法：哈希集合 + 顺序查找

#### 核心思路

1. 将数组所有元素存入哈希集合 `reference`
2. 从 `k` 开始，依次检查 `k, 2k, 3k, ...`
3. 返回第一个**不在集合中**的倍数

#### 为什么这样可行？

- 题目要求**最小的缺失倍数**，所以必须从小到大检查
- 哈希集合提供 O(1) 的查找时间
- 第一个不在集合中的倍数就是答案

---

## 代码实现

```cpp
class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        unordered_set<int> reference;
        int n = static_cast<int>(nums.size());
        
        // 将所有数字存入哈希集合
        for(int i = 0; i < n; i++) 
            if(!reference.count(nums[i])) 
                reference.emplace(nums[i]);
        
        // 从 k 开始依次检查倍数
        int index = 1;
        while(reference.count(k * index)) 
            index++;
        
        return index * k;
    }
};
```

---

## 复杂度分析

### 时间复杂度

- **构建哈希集合**：O(n)
- **查找缺失倍数**：O(m)，其中 m = 答案 / k
  - 最好情况：O(1)（k 本身就缺失）
  - 最坏情况：O(max(nums) / k)（所有倍数都在数组中）

**总时间复杂度**：O(n + m)

### 空间复杂度

- 哈希集合存储所有元素：O(n)

---

## 代码优化建议

### 优化 1：简化集合构建

```cpp
// 原版
for(int i = 0; i < n; i++) 
    if(!reference.count(nums[i])) 
        reference.emplace(nums[i]);

// 简化版（unordered_set 自动去重）
unordered_set<int> reference(nums.begin(), nums.end());
```

### 优化 2：只存储 k 的倍数（降低空间和时间）

```cpp
int missingMultiple(vector<int>& nums, int k) {
    unordered_set<int> multiples;
    
    // 只存储 k 的倍数
    for (int num : nums) {
        if (num % k == 0) {
            multiples.insert(num);
        }
    }
    
    // 查找缺失的倍数
    for (int multiple = k; ; multiple += k) {
        if (!multiples.count(multiple)) {
            return multiple;
        }
    }
}
```

**优点**：
- 空间从 O(n) 降低到 O(m)，m 是数组中 k 的倍数个数
- 通常 m << n，节省空间
- 避免检查非倍数元素

---

## 手动推演

### 例子：`nums = [3, 6, 12, 15], k = 3`

```
步骤 1：构建哈希集合
reference = {3, 6, 12, 15}

步骤 2：依次检查倍数
index = 1: k * 1 = 3  → 在集合中，继续
index = 2: k * 2 = 6  → 在集合中，继续
index = 3: k * 3 = 9  → 不在集合中！返回 9

答案：9
```

---

## 常见错误

### 错误 1：忘记去重

```cpp
// ❌ 可能插入重复元素（虽然 unordered_set 会自动去重）
for(int i = 0; i < n; i++) 
    reference.insert(nums[i]);  // 重复插入不会报错，但浪费时间
```

**实际上**：`unordered_set` 的 `insert` 和 `emplace` 都会自动去重，所以 `if(!reference.count(...))` 这个判断是**多余的**。

### 错误 2：整数溢出

```cpp
while(reference.count(k * index))  // ← 当 k * index > INT_MAX 时会溢出
    index++;
```

**修正**：如果 k 很大，需要使用 `long long`：

```cpp
long long index = 1;
while(reference.count(k * index)) 
    index++;
return k * index;
```

### 错误 3：效率问题

当 `nums = [k, 2k, 3k, ..., 10^9]` 时，循环会执行 `10^9 / k` 次，可能 TLE。

**解决方案**：使用优化 2（只存储 k 的倍数）。

---

## 对比：原版 vs 优化版

| 特性 | 原版（本实现） | 优化版（只存倍数） |
|-----|-------------|-----------------|
| 空间复杂度 | O(n) | O(m)，m ≤ n |
| 查找次数 | 最坏 O(max/k) | 最坏 O(m) |
| 代码简洁度 | ⭐⭐⭐ | ⭐⭐⭐⭐ |
| 适用场景 | 小数据量 | 大数据量、k 较大 |

---

## 相关题目

- [41. 缺失的第一个正数](../../array/0041-first-missing-positive/) - 类似思想，找缺失的最小正整数
- [268. 丢失的数字](../../array/0268-missing-number/) - 找缺失的数字
- [287. 寻找重复数](../../array/0287-find-the-duplicate-number/) - 数组查找问题
- [2996. 大于等于顺序前缀和的最小缺失整数](../../array/2996-smallest-missing-integer-greater-than-sequential-prefix-sum/) - 缺失数字变体
