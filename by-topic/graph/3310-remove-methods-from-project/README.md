# 3310. Remove Methods From Project

## 题目信息

- **难度**：Medium
- **分类**：Graph, DFS, BFS, Reachability
- **链接**：https://leetcode.com/problems/remove-methods-from-project/

## 题目描述

给你 `n` 个方法，编号为 `0` 到 `n - 1`，以及调用关系 `invocations[i] = [a, b]`，表示方法 `a` 会调用方法 `b`。

已知方法 `k` 存在 bug。所有从 `k` 出发能够到达的方法都属于 suspicious methods。

如果存在某个非 suspicious 方法调用了 suspicious 方法，那么这些 suspicious methods 不能被删除；此时返回所有方法编号。

否则，返回删除 suspicious methods 后剩余的方法编号。

## 解题思路

### 方法一：单源 DFS + 边检查

先把调用关系建成有向图 `a -> b`。

第一步，从 `k` 出发做 DFS，标记所有能够到达的方法，它们就是 suspicious methods。

第二步，扫描所有边，检查是否存在：

- `a` 不在 suspicious 中
- `b` 在 suspicious 中

如果有这样的边，说明外部正常方法依赖了可疑方法，整批 suspicious methods 都不能删，直接返回所有方法编号。

如果没有这样的边，就返回所有未被标记的方法。

### 方法二：迭代 DFS + 边检查

这和方法一完全一致，只是不用递归，而是使用 `stack` 显式维护待访问节点。

- 先把起点 `k` 入栈
- 每次弹出栈顶节点，向外扩展邻居
- 用 `visited` 标记已经访问过的方法，避免重复入栈

这种写法可以避免递归过深带来的栈深风险。

### 方法三：BFS + 边检查

这版把遍历结构换成 `queue`，按层向外扩展：

- 先把起点 `k` 入队
- 每次取出队头节点
- 把它能到达且未访问的邻居加入队尾

对于这道题，DFS 和 BFS 的目标都一样，都是找出从 `k` 出发的可达点集合。区别只在于遍历顺序和实现方式。

### 方法四：BFS 辅助函数版

如果不想把遍历逻辑直接写在主函数里，可以把 BFS 单独抽成一个辅助函数：

- `remainingMethods()` 负责建图、检查外部依赖、组织返回值
- `bfs()` 只负责从起点出发标记所有可达节点

这种写法更适合复用，也更接近常见的“主流程 + 辅助函数”结构。

### 为什么这样判断就够了

题目关心的是“删掉 suspicious methods 后，是否会破坏外部方法的依赖关系”。

因此只需要检查有没有外部节点指向 suspicious 节点：

- 有，说明删除不合法
- 没有，说明可以安全删除

### 复杂度

**时间复杂度**：`O(n + m)`，其中 `m` 是调用关系数量。

**空间复杂度**：`O(n + m)`，用于邻接表和访问标记。

## 代码

```cpp
// 见 solution.cpp
```

```cpp
// 见 alt1_solution.cpp
```

```cpp
// 见 alt2_solution.cpp
```

```cpp
// 见 alt3_solution.cpp
```

## 相关题目

- LeetCode 1971. Find if Path Exists in Graph
- LeetCode 2360. Longest Cycle in a Graph
- LeetCode 802. Find Eventual Safe States
