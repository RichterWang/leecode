# 1807. Evaluate the Bracket Pairs of a String

## 题目信息

- **难度**：Medium
- **分类**：String, Hash Table
- **链接**：https://leetcode.com/problems/evaluate-the-bracket-pairs-of-a-string/

## 题目描述

给你一个字符串 `s`，它包含一些括号对，每个括号中包含一个**非空**的键。

比方说，字符串 `"(name)is(age)yearsold"` 中，有**两个**括号对，分别包含键 `"name"` 和 `"age"`。

你知道许多键对应的值，这些关系由二维字符串数组 `knowledge` 表示，其中 `knowledge[i] = [key_i, value_i]`，表示键 `key_i` 对应的值为 `value_i`。

你需要替换**所有**的括号对。当你替换一个括号对，且它包含的键为 `key_i` 时，你需要：

- 将 `key_i` 和括号用对应的值 `value_i` 替换
- 如果从 `knowledge` 中无法得知某个键对应的值，你需要将 `key_i` 和括号用问号 `"?"` 替换（不需要引号）

`knowledge` 中每个键最多只会出现一次。`s` 中不会有嵌套的括号。

请你返回替换**所有**括号对后的结果字符串。

### 示例

**示例 1**：
```
输入：s = "(name)is(age)yearsold", knowledge = [["name","bob"],["age","two"]]
输出："bobistwoyearsold"
解释：键 "name" 对应的值为 "bob"，所以将 "(name)" 替换为 "bob"
      键 "age" 对应的值为 "two"，所以将 "(age)" 替换为 "two"
```

**示例 2**：
```
输入：s = "hi(name)", knowledge = [["a","b"]]
输出："hi?"
解释：由于不知道键 "name" 对应的值，所以用 "?" 替换 "(name)"
```

**示例 3**：
```
输入：s = "(a)(a)(a)aaa", knowledge = [["a","yes"]]
输出："yesyesyesaaa"
解释：相同的键在 s 中可能会出现多次
      注意只有括号内的键会被替换，括号外的 "aaa" 保持原样
```

## 解题思路

### 核心思想：单指针线性扫描 + 哈希表查找

这道题的本质是**字符串模拟**。因为题目保证没有嵌套括号，所以不需要栈，也不需要回退，一次从左到右的扫描就够了。

整体分两步：

1. **预处理**：把 `knowledge` 建成哈希表，实现 O(1) 查找
2. **扫描替换**：一个指针 `ptr` 从头走到尾，遇到括号就提取 key 查表，否则原样输出

### 为什么不是双指针

双指针的典型特征是两个指针**独立移动、各自承担不同职责**（滑动窗口的左右边界、快慢指针、首尾相向）。

这题只有一个索引 `ptr`：
- 遇到普通字符 → 追加到结果，`ptr++`
- 遇到 `(` → 同一个 `ptr` 继续往后消耗字符直到 `)`

读 key 时的"内层前进"并不是第二个独立指针，而是同一个 `ptr` 在连续推进。所以叫"**模拟 + 哈希**"更贴切。

### 第一步：建立哈希表

```cpp
unordered_map<string, string> reference;
for(const auto& kv : knowledge) reference[kv[0]] = kv[1];
```

**关键设计点**：

- `unordered_map` 而非 `map`：不需要有序，哈希表查找是 O(1)，红黑树是 O(log n)
- **赋值而非追加**：题目保证每个键最多出现一次，所以是一对一映射
- `const auto&`：避免拷贝每个 `vector<string>`
- 范围 for 比索引循环更清晰，也省掉 `static_cast<int>`

#### 常见错误：用 push_back

```cpp
reference[knowledge[i][0]].push_back(knowledge[i][1]);  // ✗ 编译失败
```

两个问题：

1. **类型不匹配**：`reference[...]` 的类型是 `string`，而 `std::string::push_back` 只接受**单个 char**，不接受 `string`
2. **语义错误**：`push_back` 是"追加累积"语义，但每个 key 只对应唯一一个 value，需要的是赋值

如果 `reference` 是 `unordered_map<string, vector<string>>`，`push_back` 才成立，但这题不需要多值。

### 第二步：主循环扫描

```cpp
string answer;
int ptr = 0;
while(ptr < n)
{
    if(s[ptr] == '(') {
        string temp = {};
        ptr++;                      // 跳过 '('
        while(s[ptr] != ')')        // 收集 key
        {
            temp += s[ptr];
            ptr++;
        }
        ptr++;                      // 跳过 ')'
        auto it = reference.find(temp);
        it != reference.end() ? answer += it->second : answer += "?";
    }
    else {
        answer += s[ptr];
        ptr++;
    }
}
return answer;
```

#### 分支一：遇到左括号

三个 `ptr++` 各有明确职责：

| 位置 | 作用 |
|------|------|
| 内层循环前 | 跳过 `(`，让 `ptr` 指向 key 的第一个字符 |
| 内层循环中 | 逐字符消耗 key |
| 内层循环后 | 跳过 `)`，让 `ptr` 指向括号对之后的位置 |

第三个 `ptr++` 是最容易漏掉的。少了它，下一轮会在 `)` 上死循环或误判。

#### 分支二：普通字符

直接追加，`ptr++` 前进一格。

#### 关键：`ptr++` 必须放在各自分支内

```cpp
// ✗ 错误写法：统一在循环末尾 ptr++
while(ptr < n)
{
    if(s[ptr] == '(') {
        ...
        ptr++;          // 已经跳过 ')'
    }
    else answer += s[ptr];
    ptr++;              // ← 括号分支走完这里又加一次，吞掉一个字符
}
```

括号分支内部已经把 `ptr` 推到 `)` 之后了，末尾再统一 `ptr++` 会多跳一格。

例如 `"(name)is"`：处理完 `(name)` 后 `ptr` 指向 `i`，末尾的 `ptr++` 让它跳到 `s`，结果 `i` 丢失，输出变成 `"bobs"` 而不是 `"bobis"`。

正确做法：让两个分支各自管好自己的推进。

### 哈希表查找：find vs count

```cpp
// 写法 A：find + 迭代器（推荐，一次查找）
auto it = reference.find(temp);
answer += (it != reference.end()) ? it->second : "?";

// 写法 B：count + operator[]（两次查找）
answer += reference.count(temp) ? reference[temp] : "?";
```

`find` 返回迭代器：
- `it->first` 是 key
- `it->second` 是 value
- 找不到返回 `reference.end()`

写法 B 的问题：`count` 查一次，`reference[temp]` 又查一次。而且 `operator[]` 在 key 不存在时会**插入一个空 value**（这里有 `count` 保护不会触发，但习惯上 `find` 更安全）。

### 常见陷阱：下标与字符混淆

这是写这类扫描题最高频的错误：

```cpp
if(ptr == '(')          // ✗ ptr 是 int 下标，'(' 是 char (ASCII 40)
if(s[ptr] == '(')       // ✓ 取出字符再比较

while(ptr != ')')       // ✗ 等价于 while(ptr != 41)
while(s[ptr] != ')')    // ✓

temp.push_back(ptr);    // ✗ 把下标当字符塞进去
temp += s[ptr];         // ✓
```

第一个错误特别隐蔽：`if(ptr == '(')` 等价于 `if(ptr == 40)`，正常输入下几乎永远走 `else` 分支，程序**不会崩溃**，只是输出等于输入。本地随便测一个 case 很容易漏掉。

第二个错误更危险：如果进了循环而 `ptr` 一直不等于 41，会一路 `ptr++` 越界读取字符串外的内存。

**建议测试用例**：`s = "(name)is(age)yearsold"`, `knowledge = [["name","bob"],["age","two"]]`，期望输出 `"bobistwoyearsold"`。

## 复杂度分析

**时间复杂度**：`O(n + m)`
- `n` 是字符串 `s` 的长度，每个字符恰好被访问一次
- `m` 是 `knowledge` 中所有字符串的总长度，用于建表
- 哈希表查找平均 O(1)，但需要计算 key 的哈希值，所以严格来说是 O(|key|)

**空间复杂度**：`O(m + n)`
- `O(m)` 存储哈希表
- `O(n)` 存储结果字符串（最坏情况下结果可能比 `n` 更长，取决于 value 的长度）

## 可选优化

### 1. 预分配结果空间

```cpp
answer.reserve(s.size());
```

避免字符串多次扩容重分配。对通过题目没影响，但是个好习惯。

### 2. 用 substr 替代逐字符累积

```cpp
if (s[ptr] == '(')
{
    int start = ++ptr;                  // 跳过 '('，记下 key 起点
    while (s[ptr] != ')') ptr++;
    string key = s.substr(start, ptr - start);
    ptr++;                              // 跳过 ')'

    auto it = reference.find(key);
    answer += (it != reference.end()) ? it->second : "?";
}
```

复杂度相同。`substr` 版本可读性略好，逐字符版本少一次子串分配。

### 3. 三元运算符的写法

当前代码：

```cpp
it != reference.end() ? answer += it->second : answer += "?";
```

能编译（两个操作数都是赋值表达式），但把有副作用的赋值塞进三元运算符可读性较差。更清晰的写法：

```cpp
answer += (it != reference.end()) ? it->second : "?";
```

把三元用在**取值**上，赋值动作留在外面。注意 `it->second` 是 `string`，`"?"` 是 `const char*`，`const char*` 可隐式转 `string`，所以类型能统一。

## 代码

```cpp
// 见 solution.cpp
```

## 相关题目

- LeetCode 1096. Brace Expansion II (Hard - 递归下降解析，有嵌套)
- LeetCode 394. Decode String (Medium - 需要栈处理嵌套)
- LeetCode 771. Jewels and Stones (Easy - 哈希表基础应用)
- LeetCode 811. Subdomain Visit Count (Medium - 字符串切分 + 哈希计数)
