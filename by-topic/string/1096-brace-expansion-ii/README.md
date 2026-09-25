# 1096. Brace Expansion II

## 题目信息

- **难度**：Hard
- **分类**：String, Stack, Recursion, Parsing
- **链接**：https://leetcode.com/problems/brace-expansion-ii/

## 题目描述

如果你熟悉 Shell 编程，那么一定了解过花括号展开，它可以用来生成任意字符串。

花括号展开的表达式可以看作一个由 **花括号、逗号** 和 **小写英文字母** 组成的字符串，定义下面几条语法规则：

1. **单一元素**：如果只给出单一的元素 `x`，那么表达式表示的字符串就只有 `"x"`。
   - `R(x) = {x}`
   - 例如，表达式 `"a"` 表示字符串 `"a"`

2. **并集操作（逗号分隔）**：当两个或多个表达式并列，以逗号分隔，我们取这些表达式中元素的并集。
   - `R({e_1,e_2,...}) = R(e_1) ∪ R(e_2) ∪ ...`
   - 例如，表达式 `"{a,b,c}"` 表示字符串 `"a"`, `"b"`, `"c"`
   - 表达式 `"{{a,b},{b,c}}"` 也可以表示字符串 `"a"`, `"b"`, `"c"`

3. **笛卡尔积操作（相接）**：要是两个或多个表达式相接，中间没有隔开时，我们从这些表达式中各取一个元素依次连接形成字符串。
   - `R(e_1 + e_2) = {a + b for (a, b) in R(e_1) × R(e_2)}`
   - 例如，表达式 `"{a,b}{c,d}"` 表示字符串 `"ac"`, `"ad"`, `"bc"`, `"bd"`

4. **嵌套**：表达式之间允许嵌套，单一元素与表达式的连接也是允许的。
   - 例如，表达式 `"a{b,c,d}"` 表示字符串 `"ab"`, `"ac"`, `"ad"`
   - 表达式 `"a{b,c}{d,e}f{g,h}"` 可以表示字符串 `"abdfg"`, `"abdfh"`, `"abefg"`, `"abefh"`, `"acdfg"`, `"acdfh"`, `"acefg"`, `"acefh"`

给出表示基于给定语法规则的表达式 `expression`，返回它所表示的所有字符串组成的**有序列表**。

### 示例

**示例 1**：
```
输入：expression = "{a,b}{c,{d,e}}"
输出：["ac","ad","ae","bc","bd","be"]
```

**示例 2**：
```
输入：expression = "{{a,z},a{b,c},{ab,z}}"
输出：["a","ab","ac","z"]
解释：输出中不应出现重复的组合结果。
```

## 解题思路

### 核心思想：递归下降解析

这道题的本质是实现一个**表达式解析器**，将花括号表达式按照语法规则展开成所有可能的字符串。

采用**递归下降解析（Recursive Descent Parsing）** 的方法，将解析过程分为三个层级：

```
parseExpression  → 处理逗号（并集操作）
    ↓
parseTerm       → 处理相接（笛卡尔积操作）
    ↓
parseAtom       → 处理单个原子（字母或递归处理花括号）
```

### 三个函数的职责

| 函数 | 处理内容 | 操作 | 示例 |
|------|---------|------|------|
| `parseExpression` | 逗号分隔的项 | 并集 ∪ | `{a,b,c}` → `{"a"} ∪ {"b"} ∪ {"c"}` |
| `parseTerm` | 连续相接的原子 | 笛卡尔积 × | `abc` → `{"a"} × {"b"} × {"c"}` |
| `parseAtom` | 单个原子 | 返回或递归 | `a` → `{"a"}`, `{...}` → 递归 |

### 关键设计

#### 1. 共享位置指针 `int& i`

所有递归函数共享同一个位置指针 `i`（引用传递），解析完成后 `i` 会自动前进到下一个未处理的位置。

```cpp
void parseExpression(const string& s, int& i)  // 注意 int& i，不是 int i
```

这样避免了返回位置信息，简化了代码逻辑。

#### 2. 使用 `set<string>` 自动去重和排序

题目要求返回**有序且无重复**的字符串列表，`set` 天然满足这两个特性：
- 自动去重
- 自动按字典序排序

#### 3. 笛卡尔积的实现

```cpp
set<string> combined;
for(const string& a : result) 
    for(const string& b : next) 
        combined.insert(a + b);
```

对于 `result = {"a", "b"}` 和 `next = {"c", "d"}`：
```
a="a", b="c" → "ac"
a="a", b="d" → "ad"
a="b", b="c" → "bc"
a="b", b="d" → "bd"
```
结果：`{"ac", "ad", "bc", "bd"}`

### parseExpression：处理并集

```cpp
set<string> parseExpression(const string& s, int& i)
{
    set<string> result = parseTerm(s, i);  // 解析第一项
    
    while(i < s.size() && s[i] == ',')     // 遇到逗号
    {
        i++;                                // 跳过逗号
        set<string> next = parseTerm(s, i); // 解析下一项
        result.insert(next.begin(), next.end());  // 合并（并集）
    }
    
    return result;
}
```

**执行示例**：`"{a,b,c}"`
```
1. parseTerm() → {"a"}, i=2
2. s[2]=',' → i=3, parseTerm() → {"b"}, result={"a","b"}
3. s[4]=',' → i=5, parseTerm() → {"c"}, result={"a","b","c"}
4. s[6]='}' → 退出循环
```

### parseTerm：处理笛卡尔积

```cpp
set<string> parseTerm(const string& s, int& i)
{
    set<string> result = parseAtom(s, i);  // 解析第一个原子
    
    // 只要后面还有字符且不是逗号或右括号，就继续相接
    while(i < s.size() && s[i] != ',' && s[i] != '}')
    {
        set<string> next = parseAtom(s, i);
        
        // 计算笛卡尔积
        set<string> combined;
        for(const string& a : result) 
            for(const string& b : next) 
                combined.insert(a + b);
        
        result = combined;
    }
    
    return result;
}
```

**执行示例**：`"{a,b}{c,d}"`
```
1. parseAtom() → {"a","b"}, i=6
2. s[6]='{' → parseAtom() → {"c","d"}, i=12
3. 笛卡尔积：{"a","b"} × {"c","d"} = {"ac","ad","bc","bd"}
4. i=12, 退出循环
```

### parseAtom：处理单个原子

```cpp
set<string> parseAtom(const string& s, int& i)
{
    if(s[i] == '{')
    {
        i++;                                    // 跳过 '{'
        set<string> result = parseExpression(s, i);  // 递归处理
        i++;                                    // 跳过 '}'
        return result;
    }
    else 
    {
        return {string(1, s[i++])};  // 返回单字符字符串
    }
}
```

**关键点**：
- 遇到 `{` 时递归调用 `parseExpression`
- `string(1, s[i++])` 构造单字符字符串并返回单元素 `set`
- `{expr}` 是 C++11 的列表初始化语法

### 完整执行流程示例

**输入**：`"{a,b}{c,d}"`

```
parseExpression(i=0):
  ├─ parseTerm(i=0):
  │   ├─ parseAtom(i=0): s[0]='{'
  │   │   └─ i++, parseExpression(i=1):  // 递归处理 "a,b"
  │   │       └─ 返回 {"a","b"}, i=5
  │   │   └─ i++, 返回 {"a","b"}, i=6
  │   │
  │   ├─ result = {"a","b"}
  │   │
  │   ├─ while: i=6, s[6]='{'
  │   │   ├─ parseAtom(i=6): s[6]='{'
  │   │   │   └─ i++, parseExpression(i=7):  // 递归处理 "c,d"
  │   │   │       └─ 返回 {"c","d"}, i=11
  │   │   │   └─ i++, 返回 {"c","d"}, i=12
  │   │   │
  │   │   ├─ next = {"c","d"}
  │   │   ├─ 笛卡尔积 → {"ac","ad","bc","bd"}
  │   │   └─ result = {"ac","ad","bc","bd"}
  │   │
  │   └─ 返回 {"ac","ad","bc","bd"}
  │
  └─ 返回 {"ac","ad","bc","bd"}
```

### 为什么能正确处理嵌套？

关键在于 `parseAtom` 中的递归调用：

```cpp
if(s[i] == '{')
{
    i++;
    set<string> result = parseExpression(s, i);  // 递归！
    i++;
    return result;
}
```

每当遇到 `{`，就递归调用 `parseExpression` 处理内部的子表达式，处理完后 `i` 已经指向对应的 `}` 之后，外层函数继续处理剩余部分。

## 复杂度分析

**时间复杂度**：`O(n × m)`
- `n` 是表达式长度
- `m` 是生成的字符串数量（最坏情况下指数级）
- 每个字符串的生成涉及拼接操作

**空间复杂度**：`O(m × k)`
- `m` 是生成的字符串数量
- `k` 是平均字符串长度
- 递归调用栈深度最多 `O(n)`

## 代码

```cpp
// 见 solution.cpp
```

## 相关题目

- LeetCode 1087. Brace Expansion (Easy - 此题的简化版)
- LeetCode 394. Decode String (Medium - 类似的递归解析)
- LeetCode 726. Number of Atoms (Hard - 化学式解析)
- LeetCode 224. Basic Calculator (Hard - 表达式解析)
