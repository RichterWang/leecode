# 2265. 统计值等于子树平均值的节点数

**难度**：Medium  **标签**：树、深度优先搜索、二叉树

## 题目描述

给你一棵二叉树的根节点 `root`，找出并返回满足要求的节点数，要求节点的值等于其 **子树** 中值的 **平均值**。

注意：

- `n` 个元素的平均值可以由 `n` 个元素求和后再除以 `n`，并 **向下舍入** 到最近的整数- `root` 的 **子树** 由 `root` 和它的所有后代组成

## 核心思路

判断一个节点是否满足条件，需要它子树的平均值：

```text
平均值 = 子树节点值之和 / 子树节点个数
```

因此每次递归必须向上带回 **两个** 信息：

1. 子树的节点值之和 `sum`
2. 子树的节点个数 `count`

用 `pair<int, int>` 一次返回这两个量，同时把全树累计的答案 `answer` 以引用传下去。

## 为什么必须是后序遍历

当前节点的判断依赖左右子树的统计结果，所以顺序只能是：

```text先递归左子树
再递归右子树
最后处理当前节点
```

这正是后序遍历。不能像 LeetCode 131 那样"先处理再递归"，因为处理当前节点所需的数据还没算出来。

## 关键设计：区分全局量与局部量

这是本题最容易出错的地方。两类数据的传递方式完全不同：

| 变量 | 语义 | 传递方式 |
|---|---|---|
| `answer` | 全树的 **全局累计** 结果 | 引用参数，只有一份 |
| `sum` / `count` | 当前子树的 **局部属性** | 返回值，每层独立 |

判断标准是：**这个量属于整棵树，还是属于当前这个子树？**

- 属于整棵树 → 共享引用（或成员变量）
- 属于当前子树 → 必须每层独立，通过返回值带上来

### 反例：把 count 也做成共享引用

如果写成：

```cpp
int dfs_search(TreeNode* current, int& answer, int& count) {
    // ...
    count++;                                     // 错误
    if (current->val == (left + right + current->val) / count) answer++;
    return left + right + current->val;
}
```

由于 `count` 只有一份并被所有层共享，`count++` 累计出的实际含义变成了：

> 后序遍历中，到目前为止一共访问过多少个节点

而不是当前子树的节点个数。

以下面这棵树为例：

```text
        4
      /   \
     8     5
    / \      \
   0   1      6
```

后序访问顺序为 `0 → 1 → 8 → 6 → 5 → 4`：

| 处理节点 | 正确 count | 共享 count | 正确平均 | 错误计算 | 结果 |
|---|---:|---:|---|---|---|
| `0` | 1 | 1 | `0 / 1 = 0` | `0 / 1 = 0` | 恰好相同 |
| `1` | 1 | 2 | `1 / 1 = 1` | `1 / 2 = 0` | 漏计 |
| `8` | 3 | 3 | `9 / 3 = 3` | `9 / 3 = 3` | 巧合相同 |
| `6` | 1 | 4 | `6 / 1 = 6` | `6 / 4 = 1` | 漏计 |
| `5` | 2 | 5 | `11 / 2 = 5` | `11 / 5 = 2` | 漏计 |
| `4` | 6 | 6 | `24 / 6 = 4` | `24 / 6 = 4` | 巧合相同 |

正确答案是 `5`，共享 `count` 的版本只会返回 `3`。

`8` 和 `4` 看起来正确，是因为它们恰好是各自子树后序遍历的最后一个节点，此时累计数正好等于子树大小。这种"部分正确"最容易掩盖问题。

## 递归出口

空节点的子树里没有任何节点：

```cpp
if (current == nullptr) return {0, 0};
```

返回 `{0, 0}` 的好处是父节点可以无条件累加，不需要在调用前逐个判断 `left != nullptr`、`right != nullptr`。

绝不能返回 `{0, 1}`，否则每个空指针都会被算成一个节点，导致 `count` 偏大、平均值偏小。

## 合并子树结果

```cpp
pair<int, int> from_left = dfs_search(current->left, answer);pair<int, int> from_right = dfs_search(current->right, answer);

int count = 1 + from_left.second + from_right.second;
int sum = current->val + from_left.first + from_right.first;
```

`count` 加 `1` 是把当前节点自身计入子树。这里用的是 **赋值** 重新计算，而不是对某个共享变量做 `++`，这正是与上文反例的本质区别。

`pair` 的两个成员含义固定：

```text
first  → 子树节点值之和
second → 子树节点个数
```

也可以用 C++17 结构化绑定让语义更直观：

```cppauto [leftSum, leftCount] = dfs_search(current->left, answer);auto [rightSum, rightCount] = dfs_search(current->right, answer);
```

## 整数除法自动向下取整

题目要求的平均值是向下舍入的整数除法：

```cpp
if (current->val == sum / count) answer++;
```

C++ 中两个 `int` 相除本身就会截断小数部分。题目保证节点值非负，因此截断方向就是向下取整，直接比较即可。

不要转成 `double` 再比较：

```cppif (current->val == (double)sum / count)   // 错误做法
```

浮点会引入精度问题，而且 `double` 除法不做向下取整，语义与题目不符。

## 示例分析

```text
        4
      /   \
     8     5
    / \      \
   0   1      6
```

后序遍历逐节点计算：

```text
dfs(0) → {0, 1}，0 == 0 / 1 = 0        答案 +1
dfs(1) → {1, 1}，1 == 1 / 1 = 1        答案 +1
dfs(8) → {9, 3}，8 != 9 / 3 = 3dfs(6) → {6, 1}，6 == 6 / 1 = 6        答案 +1
dfs(5) → {11, 2}，5 == 11 / 2 = 5      答案 +1
dfs(4) → {24, 6}，4 == 24 / 6 = 4      答案 +1
```

最终答案为 `5`。

注意节点 `5`：子树为 `{5, 6}`，和为 `11`，个数为 `2`，`11 / 2` 向下取整得 `5`，正好等于节点值，因此计入答案。这个用例专门用于验证向下取整是否处理正确。

## 参考实现

```cpp
class Solution {
public:
    int averageOfSubtree(TreeNode* root) {
        int answer = 0;        dfs_search(root, answer);
        return answer;
    }

private:    pair<int, int> dfs_search(TreeNode* current, int& answer) {
        if (current == nullptr) return {0, 0};

        pair<int, int> from_left = dfs_search(current->left, answer);
        pair<int, int> from_right = dfs_search(current->right, answer);

        int count = 1 + from_left.second + from_right.second;        int sum = current->val + from_left.first + from_right.first;

        if (current->val == sum / count) answer++;

        return {sum, count};
    }
};
```

## 常见错误

**把子树大小做成共享引用。** 见上文反例，这是本题最主要的陷阱。局部属性必须走返回值。

**空节点返回 `{0, 1}`。** 空指针不是节点，会让所有子树的计数偏大。

**只返回一个 `int`。** `int dfs(TreeNode*)` 无法同时带回 sum 和 count，父节点算不出平均值。要么返回 `pair`，要么用额外的引用出参，要么设为成员变量。

**误把调用写成声明。** 在函数体内写：

```cpp
int dfs_search(root);
```

C++ 会把它解析成函数声明，`root` 被当作类型名查找并报错。调用时不写返回类型：

```cpp
dfs_search(root, answer);
```

**忘记 `return answer;`。** 声明了返回值却走到函数末尾是未定义行为，开启 `-Wall` 可以当场发现。

**用 `double` 求平均值。** 与题目"向下舍入"的要求不符，且引入精度风险。

## 不需要担心的点

**溢出。** 约束下节点数不超过 `1000`、节点值不超过 `1000`，最大和为 `10^6`，`int` 足够，不需要 `long long`。

**负数除法截断方向。** 题目保证节点值非负，不涉及负数向零截断与向下取整不一致的问题。

## 代码中的冗余

`averageOfSubtree` 内声明的：

```cpp
int count = 0; // 子节点个数
```

在改用 `pair` 返回后已经不再被使用。子树大小是递归内部的中间量，外层函数不需要感知，这行可以删除。当前保留不影响正确性。

## 复杂度分析

设节点数为 `n`，树高为 `h`：

- **时间复杂度**：`O(n)`，每个节点恰好访问一次，每次做常数次运算
- **空间复杂度**：`O(h)`，来自递归栈。平衡树为 `O(log n)`，退化成链时最坏为 `O(n)`

## 文件说明

- `solution.cpp`：后序遍历 + `pair` 返回 `{sum, count}` 的实现
