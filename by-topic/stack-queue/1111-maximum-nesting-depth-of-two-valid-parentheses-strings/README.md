# 1111. Maximum Nesting Depth of Two Valid Parentheses Strings

## 题目信息

- **难度**：Medium
- **分类**：String, Stack, Greedy
- **链接**：https://leetcode.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/

## 题目描述

给定一个**有效括号字符串（VPS）** `seq`，将其拆分成两个不相交的子序列 A 和 B，使得：
1. A 和 B 都是 VPS
2. `A.length + B.length = seq.length`

返回一个 `answer` 数组（长度为 `seq.length`），其中：
- `answer[i] = 0` 表示 `seq[i]` 属于子序列 A
- `answer[i] = 1` 表示 `seq[i]` 属于子序列 B

**目标**：使 `max(depth(A), depth(B))` 的值最小。

### 有效括号字符串（VPS）定义

- 空字符串 `""`
- 可以表示为 `AB`（A 连接 B），其中 A 和 B 都是 VPS
- 可以表示为 `(A)`，其中 A 是 VPS

### 嵌套深度定义

- `depth("") = 0`
- `depth(A + B) = max(depth(A), depth(B))`
- `depth("(" + A + ")") = 1 + depth(A)`

**示例**：
- `"()"` → depth = 1
- `"(())"` → depth = 2
- `"()()"` → depth = 1
- `"(()(()))"` → depth = 3

## 解题思路

### 核心观察

**关键**：要让两个子序列的最大深度尽可能小，就要把"嵌套深的部分"**均匀分配**到两个子序列中。

最优策略是按照**深度的奇偶性**进行分配：
- 深度为奇数的括号分给 A
- 深度为偶数的括号分给 B

这样可以保证两个子序列的深度约为原深度的一半。

### 算法步骤

1. 维护当前深度 `current_depth`
2. 从左到右扫描字符串：
   - 遇到 `'('`：
     - `current_depth++`（进入更深一层）
     - `answer[i] = current_depth & 1`（按奇偶分配）
   - 遇到 `')'`：
     - `answer[i] = current_depth & 1`（与对应的 `'('` 同组）
     - `current_depth--`（退出当前层）

### 正确性证明

**为什么按奇偶分配有效？**

以 `"((()))"` 为例：

```
索引:     0   1   2   3   4   5
字符:     (   (   (   )   )   )
深度:     1   2   3   3   2   1
分配:     1   0   1   1   0   1  (depth & 1)

A (0): 位置 {1, 4} → "()" → depth = 1
B (1): 位置 {0, 2, 3, 5} → "(())" → depth = 2
max(1, 2) = 2
```

原始深度 3 降到了 2，接近最优（理论下界为 ⌈3/2⌉ = 2）。

**通用性**：
- 原始深度为 `d` 的字符串，拆分后 `max(depth(A), depth(B)) ≤ ⌈d/2⌉`
- 奇偶分配可以达到这个下界

### 为什么 `')'` 要先分配再减深度？

```cpp
if(seq[i] == ')') {
    answer[i] = current_depth & 1;  // 先分配
    current_depth--;                 // 再减深度
}
```

**原因**：`')'` 要和**对应的** `'('` 分到同一组。

例如 `"(())"` 的配对关系：
```
索引: 0  1  2  3
字符: (  (  )  )
     └──┘  └──┘
```

- 索引 0 的 `'('` 在深度 1，分给 B
- 索引 3 的 `')'` 要和它配对，也必须在深度 1 时分配给 B

如果先减深度再分配，索引 3 会被分到错误的组。

## 复杂度分析

- **时间复杂度**：`O(n)`，单次遍历
- **空间复杂度**：`O(n)`，输出数组

## 代码实现

```cpp
// 见 solution.cpp
```

## 测试用例

### 示例 1

```cpp
输入：seq = "(()())"
输出：[0,1,1,1,1,0]
解释：
- A = "()()"（位置 0, 2, 3, 5）→ depth = 1
- B = "()"（位置 1, 4）→ depth = 1
- max(1, 1) = 1
```

### 示例 2

```cpp
输入：seq = "()(())()"
输出：[0,0,0,1,1,0,1,1]
解释：
- A = "()()"（位置 0, 1, 5, 7）→ depth = 1
- B = "(())"（位置 2, 3, 4, 6）→ depth = 2
- max(1, 2) = 2
```

### 示例 3

```cpp
输入：seq = "(((()))))"
输出：[0,1,0,1,1,0,1,0,0]
解释：
- 原始 depth = 4
- 拆分后 max(depth(A), depth(B)) = 2
```

## 扩展思考

### 为什么不是其他分配策略？

**错误策略 1：前半部分给 A，后半部分给 B**
- 反例：`"((()))"` → A = `"((("`, B = `")))"`，都不是 VPS ❌

**错误策略 2：随机分配**
- 可能无法保证 A 和 B 都是 VPS
- 即使都是 VPS，深度也不是最优

**奇偶分配的优势**：
- 保证配对的括号在同一组（VPS 要求）
- 深度平均分配（最优性）

### 其他实现方式

也可以用栈记录配对关系，但会增加空间复杂度到 `O(n)`（栈空间），而奇偶法只需 `O(1)` 额外空间。

## 相关问题

- [20. Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)
- [678. Valid Parenthesis String](https://leetcode.com/problems/valid-parenthesis-string/)
- [856. Score of Parentheses](https://leetcode.com/problems/score-of-parentheses/)
- [1003. Check If Word Is Valid After Substitutions](https://leetcode.com/problems/check-if-word-is-valid-after-substitutions/)
