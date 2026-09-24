# 3550. 寻找满足数位和等于下标的最小下标

- **难度**：Easy
- **标签**：数组、数学、模拟

## 问题描述

给你一个整数数组 `nums`。

返回满足 `nums[i]` 的**数位和**（每一位数字相加求和）等于 `i` 的**最小**下标 `i`。

如果不存在满足要求的下标，返回 `-1`。

### 示例

#### 示例 1

```
输入：nums = [10, 12, 13, 14]
输出：1
解释：
- 下标 0: nums[0] = 10, 数位和 = 1 + 0 = 1 ≠ 0
- 下标 1: nums[1] = 12, 数位和 = 1 + 2 = 3 ≠ 1
- 下标 2: nums[2] = 13, 数位和 = 1 + 3 = 4 ≠ 2
- 下标 3: nums[3] = 14, 数位和 = 1 + 4 = 5 ≠ 3
```

#### 示例 2

```
输入：nums = [0, 1, 2, 3, 4]
输出：0
解释：下标 0: nums[0] = 0, 数位和 = 0 = 0 ✓
```

#### 示例 3

```
输入：nums = [5, 10, 15]
输出：-1
解释：没有满足条件的下标
```

#### 示例 4

```
输入：nums = [1, 11, 2, 3]
输出：2
解释：下标 2: nums[2] = 2, 数位和 = 2 = 2 ✓
```

### 约束条件

- `1 <= nums.length <= 10^5`
- `0 <= nums[i] <= 10^9`

---

## 核心思路：直接模拟

这是一道简单的模拟题，核心在于：
1. **遍历数组**：从下标 0 开始遍历
2. **计算数位和**：对每个 `nums[i]` 计算其各位数字之和
3. **判断条件**：如果数位和等于下标 `i`，立即返回 `i`
4. **返回结果**：如果遍历结束仍未找到，返回 `-1`

### 数位和计算方法

对于一个整数 `num`，计算其数位和：

```cpp
int digitSum = 0;
while (num != 0) {
    digitSum += num % 10;  // 取最后一位
    num = num / 10;        // 去掉最后一位
}
```

**示例**：`num = 12345`

```
迭代 1: digitSum = 0 + 5 = 5,  num = 1234
迭代 2: digitSum = 5 + 4 = 9,  num = 123
迭代 3: digitSum = 9 + 3 = 12, num = 12
迭代 4: digitSum = 12 + 2 = 14, num = 1
迭代 5: digitSum = 14 + 1 = 15, num = 0
结果: 15
```

---

## 解法：线性扫描

### 算法步骤

1. **边界检查**：如果数组为空，返回 `-1`
2. **遍历数组**：对每个下标 `i` 从 0 到 n-1：
   - 计算 `nums[i]` 的数位和
   - 如果数位和 == i，返回 i
3. **未找到**：返回 `-1`

### 代码实现

```cpp
int smallestIndex(vector<int>& nums) {
    int n = nums.size();
    
    if (n == 0) return -1;
    
    for (int i = 0; i < n; i++) {
        // 计算 nums[i] 的数位和
        int digitSum = 0;
        int current = nums[i];
        
        while (current != 0) {
            digitSum += current % 10;
            current = current / 10;
        }
        
        // 找到满足条件的下标
        if (digitSum == i) {
            return i;
        }
    }
    
    return -1;
}
```

### 执行过程图解

以 `nums = [1, 11, 2, 3]` 为例：

```
下标 0:
  nums[0] = 1
  数位和 = 1
  1 ≠ 0 ❌

下标 1:
  nums[1] = 11
  数位和 = 1 + 1 = 2
  2 ≠ 1 ❌

下标 2:
  nums[2] = 2
  数位和 = 2
  2 == 2 ✓
  返回 2
```

---

## 复杂度分析

- **时间复杂度**：O(n × d)
  - n 是数组长度
  - d 是数字的位数，d = O(log(max(nums)))
  - 遍历数组：O(n)
  - 每次计算数位和：O(d)
  - 总计：O(n × log(max(nums)))

- **空间复杂度**：O(1)
  - 只使用常数个变量

---

## 优化思考

### 能否提前终止？✓

由于题目要求**最小**下标，而我们是从下标 0 开始遍历的，所以找到第一个满足条件的下标就是答案，可以立即返回。

### 能否预处理？❌

**预处理数位和**：
- 可以预先计算所有数字的数位和
- 但仍需要线性扫描查找
- 空间换时间不划算

```cpp
// 预处理版本（不推荐）
vector<int> digitSums(n);
for (int i = 0; i < n; i++) {
    digitSums[i] = getDigitSum(nums[i]);
}
for (int i = 0; i < n; i++) {
    if (digitSums[i] == i) return i;
}
return -1;
```

**结论**：对于这道题，预处理没有明显优势。

### 能否二分查找？❌

**为什么不能二分**：
- 数位和与下标的关系**不单调**
- 例如：`nums = [1, 11, 2]`
  - 下标 0: 数位和 = 1
  - 下标 1: 数位和 = 2
  - 下标 2: 数位和 = 2
- 没有单调性，无法应用二分

---

## 边界情况处理

### 情况 1：空数组

```cpp
nums = []
输出：-1
```

### 情况 2：数组首元素满足条件

```cpp
nums = [0, 5, 10]
nums[0] = 0, 数位和 = 0 == 0
输出：0
```

### 情况 3：大数字

```cpp
nums = [999999999]  // 9个9
数位和 = 9 × 9 = 81
下标 = 0
81 ≠ 0
输出：-1
```

### 情况 4：所有元素都不满足

```cpp
nums = [100, 100, 100]
所有数位和都是 1，但下标是 0, 1, 2
输出：-1
```

---

## 常见错误

### 错误 1：处理负数

```cpp
// ❌ 题目约束中 nums[i] >= 0，不需要处理负数
if (num < 0) num = -num;  // 多余的代码
```

### 错误 2：数位和计算错误

```cpp
// ❌ 错误：对于 num = 0，会直接跳过循环
while (current != 0) {
    digitSum += current % 10;
    current /= 10;
}
// 当 nums[i] = 0 时，digitSum = 0 是正确的

// ✓ 正确：上述代码对于 0 也能正确处理
```

### 错误 3：忘记返回 -1

```cpp
// ❌ 错误：没有处理找不到的情况
for (int i = 0; i < n; i++) {
    if (digitSum == i) return i;
}
// 缺少 return -1;
```

### 错误 4：使用字符串转换（效率低）

```cpp
// ❌ 低效：字符串转换开销大
int digitSum = 0;
string s = to_string(nums[i]);
for (char c : s) {
    digitSum += (c - '0');
}

// ✓ 推荐：直接数学计算
int digitSum = 0;
int current = nums[i];
while (current != 0) {
    digitSum += current % 10;
    current /= 10;
}
```

---

## 数位和的性质

### 性质 1：数位和的范围

对于一个 d 位数，其数位和的范围：
- **最小值**：1（例如 1000...0）
- **最大值**：9d（例如 999...9）

**推论**：对于 `nums[i] <= 10^9`（最多10位），数位和最大为 90。

### 性质 2：数位和与模运算

一个数的数位和对 9 取模，等于该数本身对 9 取模：

```
digitSum(n) ≡ n (mod 9)
```

**示例**：
- `123 % 9 = 6`
- `digitSum(123) = 1 + 2 + 3 = 6`

### 性质 3：可能的匹配范围

对于下标 `i`，只有当 `nums[i]` 的数位和恰好等于 `i` 时才满足条件。

**观察**：
- 下标较小时（i < 10），容易找到满足条件的数字
- 下标较大时，需要的数位和也较大，可能需要更大的数字

---

## 相关题目

### 数位和相关

- [258. 各位相加](https://leetcode.cn/problems/add-digits/) - 数位和的迭代
- [202. 快乐数](https://leetcode.cn/problems/happy-number/) - 数位平方和
- [1945. 字符串转化后的各位数字之和](https://leetcode.cn/problems/sum-of-digits-of-string-after-convert/) - 数位和变换

### 数组查找

- [35. 搜索插入位置](https://leetcode.cn/problems/search-insert-position/) - 二分查找
- [167. 两数之和 II](https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/) - 双指针
- [704. 二分查找](https://leetcode.cn/problems/binary-search/) - 标准二分

### 模拟题

- [1523. 区间内的奇数个数](https://leetcode.cn/problems/count-odd-numbers-in-an-interval-range/) - 数学模拟
- [728. 自除数](https://leetcode.cn/problems/self-dividing-numbers/) - 数字处理

---

## 扩展思考

### 问题变种 1：找到所有满足条件的下标

```cpp
vector<int> allIndices(vector<int>& nums) {
    vector<int> result;
    for (int i = 0; i < nums.size(); i++) {
        if (getDigitSum(nums[i]) == i) {
            result.push_back(i);
        }
    }
    return result;
}
```

### 问题变种 2：数位积等于下标

```cpp
int digitProduct(int num) {
    if (num == 0) return 0;
    int product = 1;
    while (num != 0) {
        product *= (num % 10);
        num /= 10;
    }
    return product;
}

int smallestIndexProduct(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        if (digitProduct(nums[i]) == i) {
            return i;
        }
    }
    return -1;
}
```

### 问题变种 3：下标等于数位和的平方

```cpp
int smallestIndexSquare(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        int ds = getDigitSum(nums[i]);
        if (ds * ds == i) {
            return i;
        }
    }
    return -1;
}
```

---

## 总结

这道题是一道典型的**模拟 + 数学**题目：

| 方面 | 要点 |
|------|------|
| **核心操作** | 计算数位和 |
| **查找策略** | 线性扫描（因为要找最小下标） |
| **优化空间** | 找到即返回（提前终止） |

**解题关键**：
1. 🔢 **数位和计算**：使用取模和整除操作
2. 🔍 **线性扫描**：从前往后遍历，找到即返回
3. ⚠️ **边界处理**：空数组、数字 0 的情况

**学习价值**：
- 掌握数位操作的基本技巧
- 理解何时线性扫描是最优解
- 练习简洁的代码实现

虽然这道题比较简单，但它是很多复杂数学问题的基础，熟练掌握数位处理对于解决更难的题目很有帮助。
