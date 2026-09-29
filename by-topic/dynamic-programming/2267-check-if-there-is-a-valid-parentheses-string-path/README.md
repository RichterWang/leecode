# 2267. Check if There Is a Valid Parentheses String Path

## 题目信息

- **难度**：Hard
- **分类**：Array, Dynamic Programming, Matrix, String
- **链接**：https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/

## 题目描述

给定一个 `m x n` 的矩阵 `grid`，每个格子包含 `'('` 或 `')'`。

一个**合法括号字符串**满足以下任意条件之一：
- 字符串是 `"()"`
- 字符串可以表示为 `AB`（A 连接 B），其中 A 和 B 都是合法括号字符串
- 字符串可以表示为 `(A)`，其中 A 是合法括号字符串

一条**合法括号路径**需要满足：
- 从左上角 `(0, 0)` 开始
- 在右下角 `(m-1, n-1)` 结束
- 每次只能向右或向下移动
- 路径经过的格子组成的字符串是合法括号字符串

判断是否存在一条合法括号路径。

## 解题思路

### 方法一：朴素 DFS（会超时）

**核心思想**：
使用深度优先搜索遍历所有可能的路径，维护一个 `balance` 变量表示当前未配对的左括号数量：
- 遇到 `'('`：`balance + 1`
- 遇到 `')'`：`balance - 1`

**剪枝策略**：
1. **balance < 0**：右括号先出现多了，提前返回 false
2. **balance > remain**：当前未配对的左括号数量超过剩余路径长度，即使后面全是右括号也配不完

**终止条件**：
到达终点时，`balance == 0` 表示找到合法路径。

**时间复杂度分析**：
- 从 `(0,0)` 到 `(m-1, n-1)` 的路径总数为组合数 `C(m+n-2, m-1)`
- 当 `m = n = 100` 时，路径数量约为 `10^58`，即使有剪枝也会超时
- **时间复杂度**：`O(2^(m+n))`（指数级）
- **空间复杂度**：`O(m + n)`（递归栈深度）

**为什么会超时**：
不同路径可能到达相同的状态 `(i, j, balance)`，朴素 DFS 会对这些状态重复计算。例如：
- 路径 1：`(0,0) → (0,1) → (1,1)`
- 路径 2：`(0,0) → (1,0) → (1,1)`

两条路径都可能以相同的 `balance` 到达 `(1,1)`，但朴素 DFS 会分别搜索后续空间。

状态总数为 `O(m × n × (m+n))`（约 200 万），而路径数为 `10^58`，说明平均每个状态被重复访问了 `10^50` 次以上。

### 方法二：记忆化搜索（推荐）

**优化思路**：
在朴素 DFS 的基础上，把已经算过的状态结果缓存下来，命中缓存时直接返回，不再展开递归。

**状态定义**：
`(i, j, balance)` 表示从 `(i, j)` 出发、当前未配对左括号数量为 `balance` 时，是否存在到达终点的合法路径。

**为什么可以缓存**：
后续能否成功只取决于当前位置和 `balance`，与走到这里用的是哪条路径无关。所以同一个状态只需要算一次。

**实现要点**：

1. 用 `unordered_map<string, bool> memory` 作为缓存，键由 `to_string(i) + "," + to_string(j) + "," + to_string(balance)` 拼成
2. 剪枝条件放在查缓存**之前**，这样非法状态不会占用缓存空间
3. 终点判断也放在查缓存之前，终点本身没有子问题需要缓存
4. 两个分支都算完（或提前命中 true）后，把 `result` 写回缓存再返回

```cpp
// 剪枝 + 终点判断
if(balance < 0) return false;
int remain = (row - 1 - i) + (col - 1 - j);
if(remain < balance) return false;
if(i == row - 1 && j == col - 1) return balance == 0;

// 查缓存
string key = to_string(i) + "," + to_string(j) + "," + to_string(balance);
if(memory.count(key)) return memory[key];

// 递归两个方向
bool result = false;
if(j + 1 < col){ /* 向右 */ }
if(!result && i + 1 < row){ /* 向下 */ }

// 写缓存
memory[key] = result;
return result;
```

注意 `if(!result && i + 1 < row)` 这个短路：向右已经找到答案时就不用再向下搜。

**优化后复杂度**：
- **时间复杂度**：`O(m × n × (m+n))`，每个状态只计算一次
- **空间复杂度**：`O(m × n × (m+n))`

对于 `m = n = 100`，状态总数约 200 万，可以通过。

**进一步优化方向**：
- 把 `unordered_map<string, bool>` 换成三维数组 `vector<vector<vector<int8_t>>>`，用 `-1/0/1` 表示未计算/false/true，省掉字符串拼接和哈希计算的开销
- 或者用位集压缩 `balance` 维度，改写成自底向上的 DP

## 初始检查

在开始搜索前，可以进行以下优化：

1. **路径长度必须是偶数**：
   - 路径长度 = `m + n - 1`（从起点到终点经过的格子数）
   - 如果长度为奇数，左右括号数量不可能相等

2. **起点必须是 `'('`**：
   - 如果起点是 `')'`，无论如何都无法构成合法括号字符串

## 代码实现

| 文件 | 解法 | 复杂度 | 结果 |
|------|------|--------|------|
| `solution_naive_dfs.cpp` | 朴素 DFS | `O(2^(m+n))` | 超时，仅供学习对比 |
| `solution.cpp` | 记忆化搜索 | `O(mn(m+n))` | 通过 |

两个文件的剪枝逻辑和 `balance` 维护方式完全一致，唯一区别是 `solution.cpp` 在递归前后加了缓存的读写。

## 测试用例

```cpp
// 测试用例 1
grid = [["(","(","("],
        [")","(",")"],
        ["(","(",")"],
        ["(","(",")"]]
输出：true
解释：一条合法路径为 (0,0)→(0,1)→(0,2)→(1,2)→(2,2)→(3,2)
组成字符串 "((()))"，是合法括号字符串

// 测试用例 2
grid = [[")",")"],
        ["(","("]]
输出：false
解释：起点是 ')'，无法构成合法括号字符串
```

## 相关问题

- [20. Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)
- [678. Valid Parenthesis String](https://leetcode.com/problems/valid-parenthesis-string/)
- [1190. Reverse Substrings Between Each Pair of Parentheses](https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/)
