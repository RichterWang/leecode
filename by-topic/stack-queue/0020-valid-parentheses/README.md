# 20. Valid Parentheses

## 题目信息

- **难度**：Easy
- **分类**：String, Stack
- **链接**：https://leetcode.com/problems/valid-parentheses/

## 题目描述

给定一个只包括 `'('`，`')'`，`'{'`，`'}'`，`'['`，`']'` 的字符串 `s`，判断字符串是否有效。

有效字符串需满足：
1. 左括号必须用相同类型的右括号闭合
2. 左括号必须以正确的顺序闭合
3. 每个右括号都有一个对应的相同类型的左括号

### 示例

**示例 1：**
```
输入：s = "()"
输出：true
```

**示例 2：**
```
输入：s = "()[]{}"
输出：true
```

**示例 3：**
```
输入：s = "(]"
输出：false
```

**示例 4：**
```
输入：s = "([)]"
输出：false
解释：虽然有对应的括号，但顺序不正确
```

**示例 5：**
```
输入：s = "{[]}"
输出：true
```

### 约束

- `1 <= s.length <= 10^4`
- `s` 仅由括号 `'()[]{}'` 组成

## 解题思路

### 核心观察

这是经典的**括号匹配问题**，天然适合用**栈（Stack）**来解决：

- **左括号**：压入栈中等待匹配
- **右括号**：与栈顶元素匹配，匹配成功则出栈
- **最终检查**：栈为空说明所有括号都正确配对

### 算法流程

```
初始化空栈

遍历字符串中的每个字符 c：
    if c 是左括号 ('(', '[', '{'):
        压入栈
    else (c 是右括号):
        if 栈为空:
            return false  // 没有对应的左括号
        弹出栈顶元素 temp
        if temp 和 c 不匹配:
            return false  // 括号类型不对应

return 栈是否为空  // 检查是否还有未配对的左括号
```

### 详细步骤

以 `s = "([)]"` 为例：

| 索引 | 字符 | 操作 | 栈状态 | 说明 |
|------|------|------|--------|------|
| 0 | `(` | 压栈 | `['(']` | 左括号入栈 |
| 1 | `[` | 压栈 | `['(', '[']` | 左括号入栈 |
| 2 | `)` | 出栈检查 | `['(']` | 栈顶是 `'['`，与 `')'` 不匹配 → **返回 false** |

以 `s = "{[]}"` 为例：

| 索引 | 字符 | 操作 | 栈状态 | 说明 |
|------|------|------|--------|------|
| 0 | `{` | 压栈 | `['{']` | 左括号入栈 |
| 1 | `[` | 压栈 | `['{', '[']` | 左括号入栈 |
| 2 | `]` | 出栈检查 | `['{']` | 栈顶是 `'['`，与 `']'` 匹配 ✓ |
| 3 | `}` | 出栈检查 | `[]` | 栈顶是 `'{'`，与 `'}'` 匹配 ✓ |
| - | - | 检查 | `[]` | 栈为空 → **返回 true** |

### 边界情况

1. **空字符串**：返回 `true`（题目约束 `s.length >= 1`，但代码可处理）
2. **奇数长度**：必然无法完全配对，可提前返回 `false`（优化）
3. **只有右括号**：栈为空时遇到右括号 → `false`
4. **只有左括号**：遍历结束后栈非空 → `false`

## 复杂度分析

- **时间复杂度**：`O(n)`，其中 n 是字符串长度，需要遍历一次
- **空间复杂度**：`O(n)`，最坏情况下所有字符都是左括号，栈的大小为 n

## 代码实现

### 当前实现（基础版）

```cpp
// 见 solution.cpp
```

**特点**：
- 清晰易懂
- 时间复杂度 O(n)
- LeetCode 用时：约 0-4ms

### 优化版本 1：哈希表优化

```cpp
bool isValid(string s) {
    if(s.size() % 2 != 0) return false;  // 奇数长度直接排除
    
    stack<char> stk;
    unordered_map<char, char> pairs = {
        {')', '('}, 
        {']', '['}, 
        {'}', '{'}
    };
    
    for(char c : s) {
        if(pairs.count(c)) {  // 是右括号
            if(stk.empty() || stk.top() != pairs[c]) 
                return false;
            stk.pop();
        } else {  // 是左括号
            stk.push(c);
        }
    }
    
    return stk.empty();
}
```

**优点**：
- O(1) 哈希查找
- 代码更简洁
- 用时：0-4ms

### 优化版本 2：数组模拟栈（最快）

```cpp
bool isValid(string s) {
    int n = s.size();
    if(n % 2 != 0) return false;
    
    vector<char> stk;
    stk.reserve(n);  // 预分配空间
    
    for(char c : s) {
        if(c == '(' || c == '[' || c == '{') {
            stk.push_back(c);
        } else {
            if(stk.empty()) return false;
            char left = stk.back();
            stk.pop_back();
            if((c == ')' && left != '(') ||
               (c == ']' && left != '[') ||
               (c == '}' && left != '{')) {
                return false;
            }
        }
    }
    
    return stk.empty();
}
```

**优点**：
- 避免 `std::stack` 的开销
- 连续内存（缓存友好）
- 用时：**0ms**（击败 100%）

## 性能对比

| 实现方式 | 时间复杂度 | 空间复杂度 | LeetCode 用时 | 击败比例 |
|---------|-----------|-----------|--------------|---------|
| 基础栈 + if-else | O(n) | O(n) | 0-4ms | 60-80% |
| 哈希表优化 | O(n) | O(n) | 0-4ms | 70-90% |
| 数组模拟栈 | O(n) | O(n) | 0ms | 100% |

## 常见错误

### 错误 1：忘记检查栈是否为空

```cpp
// ❌ 错误
char temp = stk.top();  // 如果栈为空会崩溃
stk.pop();
```

**正确做法**：
```cpp
// ✓ 正确
if(stk.empty()) return false;
char temp = stk.top();
stk.pop();
```

### 错误 2：忘记最后检查栈是否为空

```cpp
// ❌ 错误
return true;  // 可能还有未配对的左括号
```

**正确做法**：
```cpp
// ✓ 正确
return stk.empty();  // 确保所有括号都配对
```

### 错误 3：匹配逻辑错误

```cpp
// ❌ 错误
else if(temp == '[' && c != ']') return false;
else if(c != ']') return false;  // 这行会误判 ')'
```

**正确做法**：
```cpp
// ✓ 正确
if(temp == '(' && c != ')') return false;
else if(temp == '{' && c != '}') return false;
else if(temp == '[' && c != ']') return false;
```

## 扩展思考

### 1. 为什么用栈？

**栈的特性**：后进先出（LIFO）
- 最近的左括号应该最先匹配
- 符合括号嵌套的自然顺序

**例子**：`{[()]}`
```
遇到 '(' → 最里层
遇到 ')' → 应该先匹配最里层的 '('
这正是栈 LIFO 的特性
```

### 2. 可以用其他数据结构吗？

| 数据结构 | 可行性 | 原因 |
|---------|-------|------|
| 队列 | ❌ 不可行 | FIFO 顺序不符合括号匹配规则 |
| 数组 | ✓ 可行 | 可模拟栈，性能更好 |
| 双端队列 | ✓ 可行 | 但没有必要，功能过剩 |

### 3. 如果有其他字符怎么办？

题目保证只有括号，但如果有其他字符：

```cpp
bool isValid(string s) {
    stack<char> stk;
    for(char c : s) {
        if(c == '(' || c == '[' || c == '{') {
            stk.push(c);
        } 
        else if(c == ')' || c == ']' || c == '}') {
            if(stk.empty()) return false;
            char temp = stk.top();
            stk.pop();
            if((c == ')' && temp != '(') ||
               (c == ']' && temp != '[') ||
               (c == '}' && temp != '{')) {
                return false;
            }
        }
        // 其他字符直接忽略
    }
    return stk.empty();
}
```

## 相关问题

- [22. Generate Parentheses](https://leetcode.com/problems/generate-parentheses/) - 生成所有有效括号组合
- [32. Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/) - 最长有效括号子串
- [678. Valid Parenthesis String](https://leetcode.com/problems/valid-parenthesis-string/) - 含通配符的括号匹配
- [921. Minimum Add to Make Parentheses Valid](https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/) - 最少添加使括号有效
- [1111. Maximum Nesting Depth of Two Valid Parentheses Strings](https://leetcode.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/) - 拆分括号序列
