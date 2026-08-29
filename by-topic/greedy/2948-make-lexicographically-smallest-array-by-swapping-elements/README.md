# 2948. Make Lexicographically Smallest Array by Swapping Elements

## 题目信息

- **难度**：Medium
- **分类**：Greedy, Union Find, Sorting
- **链接**：https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/

## 题目描述

给定一个下标从 0 开始的整数数组 `nums` 和一个正整数 `limit`。

在一次操作中，你可以选择两个下标 `i` 和 `j`，如果 `|nums[i] - nums[j]| <= limit`，就可以交换 `nums[i]` 和 `nums[j]`。

返回执行任意次操作后，能得到的**字典序最小**的数组。

如果对于所有 `0 <= i < nums.length`，`a[i] == b[i]`，或者在第一个不同的索引 `k`，`a[k] < b[k]`，则数组 `a` 的字典序小于数组 `b`。

## 解题思路

### 核心观察

1. **可交换关系具有传递性**：
   - 如果 `|a - b| <= limit` 且 `|b - c| <= limit`
   - 那么 a、b、c 三者可以通过一系列交换任意排列
   - 即使 `|a - c| > limit` 也没关系（可以通过 b 中转）

2. **连通分量**：
   - 把所有可交换的元素看成一个连通分量
   - 同一分量内的元素可以任意排列
   - 不同分量之间无法交换

3. **贪心策略**：
   - 要字典序最小，从左到右扫，每个位置尽量放最小值
   - 位置 `i` 只能从"与 `i` 连通的值"中选择
   - 选最小的不会损害后续位置（因为后面只能用同分量剩下的值）

### 方法：排序 + 并查集 + 贪心

#### 算法步骤

**第一步：按值排序找相邻关系**

```
nums = [1, 7, 6, 18, 2, 1], limit = 3
排序 → sorted = [(1,0), (1,5), (2,4), (6,2), (7,1), (18,3)]
                  值 索引  值 索引  值 索引  值 索引  值 索引   值  索引
```

- 保留原索引，因为最后要按原位置构造结果
- 排序后只需检查**相邻对**：如果 `sorted[i+1].值 - sorted[i].值 <= limit`，它们就能互换

**第二步：用并查集建连通分量**

遍历相邻对，差值 <= limit 就把两个**原索引**合并：

```
i=0: |1-1| = 0 ≤ 3  → 合并索引 0 和 5
i=1: |2-1| = 1 ≤ 3  → 合并索引 4 和 5（通过传递，0、4、5 连通）
i=2: |6-2| = 4 > 3  → 不合并
i=3: |7-6| = 1 ≤ 3  → 合并索引 1 和 2
i=4: |18-7| = 11 > 3 → 不合并

最终分量：
- 分量 A：索引 {0, 4, 5}，对应值 {1, 2, 1}
- 分量 B：索引 {1, 2}，对应值 {7, 6}
- 分量 C：索引 {3}，对应值 {18}
```

**第三步：每个分量准备升序值池**

```
root 0: [1, 1, 2]   ← 分量 A 的值升序排列
root 2: [6, 7]      ← 分量 B 的值升序排列
root 3: [18]        ← 分量 C 只有一个值
```

**第四步：从左到右贪心取值**

```
位置 0 → 属于 root 0 → 取 pool[0][0] = 1
位置 1 → 属于 root 2 → 取 pool[2][0] = 6
位置 2 → 属于 root 2 → 取 pool[2][1] = 7
位置 3 → 属于 root 3 → 取 pool[3][0] = 18
位置 4 → 属于 root 0 → 取 pool[0][1] = 1
位置 5 → 属于 root 0 → 取 pool[0][2] = 2

result = [1, 6, 7, 18, 1, 2]
```

### 正确性证明

**为什么只检查排序后的相邻对？**

- 如果三个值 a < b < c 满足 `b - a <= limit` 和 `c - b <= limit`
- 那么 a、b、c 必然相邻（或只隔一个更小的值）
- 排序后的相邻检查 + 传递性 = 完整的连通图

**为什么贪心是最优？**

字典序比较**从左到右**，第一个不同的位置决定大小：
- 位置 0 放最小 → 后续怎么排都不会更优
- 位置 0 固定后，位置 1 放剩余最小 → 同理
- 依次类推，局部最优 = 全局最优

### 复杂度分析

**时间复杂度**：O(n log n)
- 排序：O(n log n)
- 并查集合并：O(n α(n))，α(n) 是反阿克曼函数，近似常数
- 构造值池和结果：O(n)
- 总体瓶颈在排序

**空间复杂度**：O(n)
- `parent` 数组：O(n)
- `sorted` 数组：O(n)
- `pool` 哈希表：O(n)
- `ptr` 哈希表：O(分量个数) ≤ O(n)

## 代码

```cpp
class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = static_cast<int>(nums.size());

        // 第一步：按值排序，同时保留原索引
        vector<pair<int, int>> sorted(n);
        for (int i = 0; i < n; i++) sorted[i] = {nums[i], i};  // {值, 原索引}
        sort(sorted.begin(), sorted.end());

        // 第二步：初始化并查集，每个元素自己是根
        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0);

        // 路径压缩的 find
        function<int(int)> find = [&](int x) -> int {
            return parent[x] == x ? x : parent[x] = find(parent[x]);
        };

        // 第三步：只检查排序后的相邻对
        for (int i = 0; i + 1 < n; i++) {
            if (sorted[i + 1].first - sorted[i].first <= limit) {
                parent[find(sorted[i + 1].second)] = find(sorted[i].second);
            }
        }

        // 第四步：每个根收集一份升序值池
        unordered_map<int, vector<int>> pool;
        for (int k = 0; k < n; k++) {
            pool[find(sorted[k].second)].push_back(sorted[k].first);
        }

        // 第五步：从左到右贪心取值
        unordered_map<int, int> ptr;
        vector<int> result(n);
        for (int i = 0; i < n; i++) {
            int root = find(i);
            result[i] = pool[root][ptr[root]++];
        }

        return result;
    }
};
```

## 关键细节

### 1. 为什么用 `unordered_map` 存指针而非 `vector`？

```cpp
// ❌ 错误
vector<int> ptr(reference.size(), 0);  // 根的个数是 2
ptr[3]++;  // 但根的编号可能是 3 → 越界！

// ✓ 正确
unordered_map<int, int> ptr;  // key 是根的编号（任意值）
ptr[3]++;  // 自动创建 {3, 0} 再自增 → {3, 1}
```

根的编号 ≠ 根的个数，用 map 避免越界。

或者直接开 `vector<int> ptr(n, 0)`（用原数组长度），也不会越界，但会浪费空间。

### 2. 合并时的写法

```cpp
// 当前代码（恰好安全，但依赖遍历顺序）
parent[find(sorted[i + 1].second)] = find(sorted[i].second);

// 更标准的写法（与遍历顺序无关）
parent[find(sorted[i + 1].second)] = find(sorted[i].second);
```

当前写法左边没用 `find`，但因为 `sorted[i+1].second` 此时还没被赋值过（左边只会写到 `sorted[0..i].second`），所以它本身就是根。虽然正确，但换个题可能就踩坑，建议统一用标准形式。

### 3. `abs()` 可以省略

```cpp
if (sorted[i + 1].first - sorted[i].first <= limit)  // ✓ sorted 已升序，差值恒非负
if (abs(sorted[i + 1].first - sorted[i].first) <= limit)  // 多余但无害
```

### 4. 值池天然有序

按 `sorted` 顺序 push，池内自动升序，无需二次排序。

## 错误方法对比

参见 `wrong_solution.cpp`：贪心局部交换，每次找后面最优的交换对象。

**为什么错？**

- 只考虑当前位置的局部最优，没有利用传递性
- 例如 `[5, 1, 2]`，limit=1：
  - 贪心会交换 5 和 2 → `[2, 1, 5]`
  - 但最优是先 5↔1 再 2↔5 → `[1, 2, 5]`
- 缺少全局视角：没有识别出"1、2、5 三者通过传递可以任意排"

## 相关题目

- [547. Number of Provinces](https://leetcode.com/problems/number-of-provinces/) - 并查集基础题
- [323. Number of Connected Components in an Undirected Graph](https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/) - 同类型
- [1202. Smallest String With Swaps](https://leetcode.com/problems/smallest-string-with-swaps/) - 相似思路：并查集 + 贪心排列
