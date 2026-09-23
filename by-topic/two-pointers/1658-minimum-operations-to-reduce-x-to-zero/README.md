# 1658. 将 x 减到 0 的最小操作数

- **难度**：Medium
- **标签**：数组、双指针、滑动窗口、前缀和

## 问题描述

给你一个整数数组 `nums` 和一个整数 `x`。每一次操作时，你应当移除数组 `nums` **最左边或最右边**的元素，然后从 `x` 中减去该元素的值。请注意，需要**修改**数组以供接下来的操作使用。

如果可以将 `x` **恰好**减到 `0`，返回**最小操作数**；否则，返回 `-1`。

### 示例

#### 示例 1

```
输入：nums = [1,1,4,2,3], x = 5
输出：2
解释：最佳解决方案是移除后两个元素，将 x 减到 0。
```

#### 示例 2

```
输入：nums = [5,6,7,8,9], x = 4
输出：-1
```

#### 示例 3

```
输入：nums = [3,2,20,1,1,3], x = 10
输出：5
```

### 约束条件

- `1 <= nums.length <= 10^5`
- `1 <= nums[i] <= 10^4`
- `1 <= x <= 10^9`

## 核心思路：逆向思维 ⭐⭐⭐

### 问题转化

这道题的关键在于**转换思维方式**：

```
原问题：从左右两端移除元素，使移除元素之和 = x
       ↓ 转化
新问题：保留中间的连续子数组，使保留元素之和 = sum(nums) - x
```

**为什么可以这样转化？**

从左右两端移除元素，等价于保留中间的连续子数组：

```
原数组：[a, b, c, d, e, f]
移除左边2个 + 右边1个：[a, b] + [f]，和为 x
                ↓
等价于保留中间：[c, d, e]，和为 sum - x
```

### 转化后的优势

- **原问题**：需要枚举左右两端的组合 → O(n²)
- **新问题**：找和为 `target = sum - x` 的**最长**连续子数组 → O(n)

**最少操作数 = 数组长度 - 最长保留子数组的长度**

---

## 解法：滑动窗口

### 算法步骤

1. **计算目标值**：`target = sum(nums) - x`
2. **边界处理**：
   - 如果 `target < 0`：说明 x 大于数组总和，返回 -1
   - 如果 `target == 0`：需要移除所有元素，返回 n
3. **滑动窗口**：找和为 `target` 的最长子数组
   - 右指针扩展窗口，累加元素
   - 当窗口和 > target 时，左指针收缩窗口
   - 当窗口和 == target 时，更新最大长度
4. **计算结果**：`n - maxLen`

### 代码实现

```cpp
int minOperations(vector<int>& nums, int x) {
    int n = nums.size();
    int target = accumulate(nums.begin(), nums.end(), 0) - x;
    
    // 边界情况
    if (target < 0) return -1;
    if (target == 0) return n;
    
    // 滑动窗口找和为 target 的最长子数组
    int left = 0, sum = 0, maxLen = -1;
    
    for (int right = 0; right < n; right++) {
        sum += nums[right];
        
        // 窗口和太大，收缩左边界
        while (sum > target && left <= right) {
            sum -= nums[left++];
        }
        
        // 找到和为 target 的子数组
        if (sum == target) {
            maxLen = max(maxLen, right - left + 1);
        }
    }
    
    return maxLen == -1 ? -1 : n - maxLen;
}
```

### 执行过程图解

以 `nums = [1,1,4,2,3], x = 5` 为例：

```
步骤 1：计算 target
total = 1 + 1 + 4 + 2 + 3 = 11
target = 11 - 5 = 6

步骤 2：滑动窗口寻找和为 6 的最长子数组

初始：left = 0, sum = 0, maxLen = -1

right = 0: [1] sum = 1
right = 1: [1,1] sum = 2
right = 2: [1,1,4] sum = 6 ✓ maxLen = 3
right = 3: [1,1,4,2] sum = 8 > 6
           收缩：[1,4,2] sum = 7 > 6
           收缩：[4,2] sum = 6 ✓ maxLen = 3
right = 4: [4,2,3] sum = 9 > 6
           收缩：[2,3] sum = 5 < 6
           
最长子数组长度 = 3

步骤 3：计算答案
最少操作数 = 5 - 3 = 2

验证：移除 [2, 3] 从右边，2 + 3 = 5 ✓
```

---

## 复杂度分析

- **时间复杂度**：O(n)
  - 计算总和：O(n)
  - 右指针遍历：O(n)
  - 左指针最多移动 n 次：O(n)
  - 总计：O(n)

- **空间复杂度**：O(1)
  - 只使用常数个变量

---

## 为什么其他方法不适用？

### 动态规划 ❌

**尝试定义状态**：
- `dp[i]` = 到位置 i 的最小操作数？
- 问题：无法表达"从左边移除 vs 从右边移除"

**改进**：
- `dp[i][j]` = 左边移除 i 个，右边移除 j 个的最小操作数
- 时间复杂度：O(n²)
- 结论：比暴力枚举还复杂，不如滑动窗口

### 贪心 ❌

**可能的贪心策略**：
1. 每次移除值最大的端点元素
2. 每次移除和最接近 x 的端点元素

**反例**：
```
nums = [1, 1, 4, 2, 3], x = 5

贪心策略 1（移除最大）：
移除 4（不在端点）❌

贪心策略 2：
左端：1 → x = 4
右端：3 → x = 2
左端：1 → x = 1
...无法找到最优解
```

贪心无法处理"必须从两端移除"且"和恰好等于 x"的约束。

### 暴力枚举 ⚠️

**思路**：枚举左边移除 i 个，右边移除 j 个

```cpp
int minOps = INT_MAX;
for (int left = 0; left <= n; left++) {
    for (int right = 0; right <= n - left; right++) {
        int sum = 0;
        // 计算左边 left 个 + 右边 right 个的和
        if (sum == x) {
            minOps = min(minOps, left + right);
        }
    }
}
```

- **时间复杂度**：O(n²)
- **结果**：可以通过，但效率低

---

## 核心知识点

### 1. 逆向思维

- **正向难题 → 逆向简化**
- 从两端移除 ⇔ 保留中间
- 最少移除 ⇔ 最多保留

### 2. 滑动窗口的适用条件

✅ 适用场景：
- **连续子数组/子串**问题
- 求**最长/最短**长度
- 元素都是**正数**（单调性）

❌ 不适用：
- 需要子序列（不连续）
- 元素有负数（和不单调）

### 3. 双指针技巧

```cpp
// 标准滑动窗口模板
int left = 0;
for (int right = 0; right < n; right++) {
    // 扩展窗口
    window.add(nums[right]);
    
    // 收缩窗口（当不满足条件时）
    while (不满足条件 && left <= right) {
        window.remove(nums[left]);
        left++;
    }
    
    // 更新答案
    if (满足条件) {
        ans = update(ans, right - left + 1);
    }
}
```

---

## 常见错误

### 错误 1：忘记处理边界情况

```cpp
// ❌ 错误
int target = sum - x;
// 如果 target < 0 会导致错误结果

// ✅ 正确
if (target < 0) return -1;
if (target == 0) return n;
```

### 错误 2：窗口收缩条件错误

```cpp
// ❌ 错误：只收缩一次
if (sum > target) {
    sum -= nums[left++];
}

// ✅ 正确：持续收缩直到满足条件
while (sum > target && left <= right) {
    sum -= nums[left++];
}
```

### 错误 3：忘记检查是否找到解

```cpp
// ❌ 错误：maxLen 可能为 -1
return n - maxLen;

// ✅ 正确
return maxLen == -1 ? -1 : n - maxLen;
```

---

## 相关题目

### 相同思路

- [209. 长度最小的子数组](https://leetcode.cn/problems/minimum-size-subarray-sum/) - 滑动窗口
- [560. 和为 K 的子数组](https://leetcode.cn/problems/subarray-sum-equals-k/) - 前缀和 + 哈希表
- [862. 和至少为 K 的最短子数组](https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/) - 单调队列

### 两端操作

- [LCR 016. 无重复字符的最长子串](https://leetcode.cn/problems/wtcaE1/) - 滑动窗口
- [2091. 从数组中移除最大值和最小值](https://leetcode.cn/problems/removing-minimum-and-maximum-from-array/) - 贪心

---

## 总结

这道题的精髓在于**问题转化**：

| 视角 | 描述 | 复杂度 |
|------|------|--------|
| 直接思考 | 从两端移除元素 | O(n²) |
| **转化思维** | **保留中间子数组** | **O(n)** |

**解题关键**：
1. 🔄 逆向思维：移除 → 保留
2. 🎯 问题转化：两端操作 → 连续子数组
3. 🪟 滑动窗口：利用元素正数的单调性

**适用技巧**：
- 遇到"从两端操作"的问题，考虑"保留中间"
- 连续子数组 + 和相关 → 滑动窗口/前缀和
- 最优化问题 → 转化为最大化/最小化子问题
