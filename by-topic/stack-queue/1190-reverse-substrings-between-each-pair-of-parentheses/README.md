# 1190. Reverse Substrings Between Each Pair of Parentheses

## 题目信息

- **难度**：Medium
- **分类**：Stack, String
- **链接**：https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/

## 题目描述

给出一个字符串 `s`（仅含有小写英文字母和括号）。

请你按照从括号内到外的顺序，逐层反转每对匹配括号中的字符串，并返回最终的结果。

注意，结果中**不应**包含任何括号。

### 示例

```
输入：s = "(abcd)"
输出："dcba"

输入：s = "(u(love)i)"
输出："iloveu"
解释：先反转 "love"，再反转 "u" + "evol" + "i"

输入：s = "(ed(et(oc))el)"
输出："leetcode"
```

## 解题思路

"从内到外逐层处理"是栈或递归的信号。两者本质相同：递归用调用栈，手写栈只是把它显式化。

括号嵌套类题目的通用骨架：

- `(` → 保存现场（入栈 / 递归进入下一层）
- `)` → 处理当前层并合并回上层（出栈 / 函数返回）
- 普通字符 → 追加到当前层

### 解法一：栈 + 翻转尾部（`solution.cpp`）

栈里存的不是字符，而是**遇到 `(` 时 `result` 的长度**，也就是这一层内容在 `result` 中的起点。遇到 `)` 时，把 `[start, end)` 这段尾巴原地翻转。

```cpp
if (c == '(') current.push(static_cast<int>(result.size()));
else if (c == ')') {
    int start = current.top();
    current.pop();
    reverse(result.begin() + start, result.end());
}
else result.push_back(c);
```

跟踪 `"(u(love)i)"`：

```text
'('  push 0          result=""
'u'                  result="u"
'('  push 1          result="u"
love                 result="ulove"
')'  pop 1, 翻 [1,)  result="uevol"
'i'                  result="uevoli"
')'  pop 0, 翻 [0,)  result="iloveu"   ✓
```

内层 `)` 一定先于外层 `)` 出现，所以内层先翻、外层再整体翻，天然就是从内到外。括号本身从不进入 `result`，不需要额外删除。

### 解法二：递归（`solution_recursive.cpp`）

`dfs(s, i)` 负责处理从 `i` 开始、直到匹配的 `)` 或串尾的一层内容：

```cpp
char c = s[i++];
if (c == '(') {
    string inner = dfs(s, i);             // 先处理内层
    reverse(inner.begin(), inner.end());
    current += inner;
}
else if (c == ')') return current;        // 本层结束
else current.push_back(c);
```

两个要点：

**`i` 必须按引用传递。** 子调用消费掉的字符，父调用不能再读一遍。按值传的话，父层会从 `(` 后面重新扫描，结果错乱。

**循环结束后必须 `return current`。** 最外层没有对应的 `)`，走到串尾时是从 `while` 外面返回的。漏写这一句，非 void 函数流出末尾是未定义行为，`-Wall` 会报 `control reaches end of non-void function`。

### 解法三：虫洞跳转 O(n)（`solution_wormhole.cpp`）

前两种解法每层都要真的翻转一次，最坏 `O(n²)`。观察到：

> 一段内容被翻转奇数次等于反着读，偶数次等于正着读。

所以不用真翻，只要换个方向读。

#### 第一遍：配对括号

```cpp
if (s[i] == '(') stk.push(i);
else if (s[i] == ')') {
    int j = stk.top();
    stk.pop();
    pair[i] = j;
    pair[j] = i;
}
```

遇到 `)` 时，栈顶是离它最近、尚未配对的 `(`，正是它的匹配对象。`pair` **双向记录**，因为第二遍中正向走会撞到 `(`、反向走会撞到 `)`，两边都得能查到另一半。字母位置的 `pair` 值不会被读取。

`"(u(love)i)"` 的结果：`pair[0]=9, pair[9]=0, pair[2]=7, pair[7]=2`。

#### 第二遍：跳转 + 掉头

```cpp
for (int i = 0, d = 1; i < n; i += d)
{
    if (s[i] == '(' || s[i] == ')') {
        i = pair[i];   // 穿到配对括号
        d = -d;        // 掉头
    }
    else result.push_back(s[i]);
}
```

`d` 的作用在循环头的 `i += d` 里：循环体只负责改方向，真正的移动由循环头完成。一次跳转分三步：瞬移到配对括号 → 掉头 → 按新方向迈一步离开括号。

跟踪 `"(u(love)i)"`：

| i | 字符 | 动作 | d | result | 下一个 i |
|---|------|------|---|--------|----------|
| 0 | `(` | 跳到 9，掉头 | -1 | "" | 8 |
| 8 | `i` | 收集 | -1 | "i" | 7 |
| 7 | `)` | 跳到 2，掉头 | 1 | "i" | 3 |
| 3~6 | `love` | 依次收集 | 1 | "ilove" | 7 |
| 7 | `)` | 跳到 2，掉头 | -1 | "ilove" | 1 |
| 1 | `u` | 收集 | -1 | "iloveu" | 0 |
| 0 | `(` | 跳到 9，掉头 | 1 | "iloveu" | 10，退出 |

方向翻转的次数等于当前所在的嵌套层数：`love` 在第 2 层，被翻两次所以正着读；`u`、`i` 在第 1 层，反着读。每个括号恰好被穿越两次，每个字母恰好被收集一次。

## 复杂度分析

| 解法 | 时间 | 空间 |
|------|------|------|
| 栈 + 翻转 | `O(n²)` | `O(n)` |
| 递归 | `O(n²)` | `O(n)` |
| 虫洞跳转 | `O(n)` | `O(n)` |

前两种的 `O(n²)` 来自嵌套深度最坏 `n/2`，每层都要翻转一段。题目 `n <= 2000`，三种都能通过。

## 代码

- `solution.cpp`：栈 + 翻转尾部（推荐先写熟）
- `solution_recursive.cpp`：递归
- `solution_wormhole.cpp`：预处理配对 + 虫洞跳转

## 相关题目

- LeetCode 394. Decode String（栈处理嵌套）
- LeetCode 224. Basic Calculator（栈 / 递归处理括号）
- LeetCode 1096. Brace Expansion II（递归下降解析）
- LeetCode 1807. Evaluate the Bracket Pairs of a String（无嵌套括号的线性扫描）
