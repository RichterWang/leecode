# 沐曦一面笔试题：实现 strstr 函数

**难度**：Medium　**标签**：字符串、双指针、字符串匹配

## 题目描述

实现一个字符串查找函数 `myStrStr`，在主串 `haystack` 中查找子串 `needle` 的第一次出现位置。

**函数签名**：

```cpp
const char* myStrStr(const char* haystack, const char* needle);
```

**功能**：
- 如果找到子串，返回指向第一次出现位置的指针
- 如果未找到，返回 `nullptr`
- 如果 `needle` 为空字符串，返回 `haystack`

**输入格式**：

```text
第一行：主串 haystack
第二行：子串 needle
```

**输出格式**：

```text
找到：输出子串在主串中的起始索引（从 0 开始）
未找到：输出 -1
```

**示例**：

```text
输入：
hello
ll

输出：
2
```

```text
输入：
hello
world

输出：
-1
```

## 核心思路：暴力匹配（朴素算法）

这是经典的字符串匹配问题，类似 LeetCode 28（实现 strstr）。

### 算法步骤

1. **边界处理**：如果 `needle` 为空，直接返回 `haystack`
2. **外层循环**：遍历 `haystack` 的每个字符作为潜在的起始位置
3. **内层循环**：从当前位置开始，逐字符比较 `haystack` 和 `needle`
4. **匹配成功**：如果 `needle` 全部匹配完（`*b == '\0'`），返回起始位置
5. **未找到**：遍历完所有位置都没匹配，返回 `nullptr`

### 为什么这样设计？

使用**双指针**同时移动：
- 指针 `a` 从 `haystack` 的当前匹配位置开始
- 指针 `b` 从 `needle` 的开头开始
- 逐字符比较，相同则同时前进，不同则重新开始

这是最直观的暴力匹配算法，时间复杂度 `O(m * n)`，但实现简单，适合面试。

## 代码实现

### 核心函数：myStrStr

```cpp
const char* myStrStr(const char* haystack, const char* needle)
{
    // 1. 边界处理：needle 为空，返回 haystack
    if (*needle == '\0') return haystack;

    // 2. 外层循环：遍历 haystack 的每个字符
    for (const char* p = haystack; *p != '\0'; p++) {
        const char* a = p;        // a 指向 haystack 当前匹配位置
        const char* b = needle;   // b 指向 needle 开头
        
        // 3. 内层循环：逐字符比较
        while (*a != '\0' && *b != '\0' && *a == *b) {
            a++;
            b++;
        }
        
        // 4. 判断是否匹配成功
        if (*b == '\0') {
            // needle 已经全部匹配完，返回起始位置
            return p;
        }
    }
    
    // 5. 未找到
    return nullptr;
}
```

### 逐行解析

#### 1. 边界处理

```cpp
if (*needle == '\0') return haystack;
```

如果 `needle` 是空字符串，按照 C 标准库 `strstr` 的行为，应该返回 `haystack` 本身。

这是合理的：空串可以认为"存在"于任何字符串的起始位置。

#### 2. 外层循环

```cpp
for (const char* p = haystack; *p != '\0'; p++)
```

- 指针 `p` 从 `haystack` 的第一个字符开始
- 每次循环尝试以 `p` 为起点匹配 `needle`
- 遇到字符串结束符 `\0` 停止

#### 3. 双指针初始化

```cpp
const char* a = p;
const char* b = needle;
```

- `a`：指向 `haystack` 中的当前匹配位置（从 `p` 开始）
- `b`：指向 `needle` 的开头

每次外层循环开始时，都重新初始化这两个指针。

#### 4. 内层循环：逐字符比较

```cpp
while (*a != '\0' && *b != '\0' && *a == *b) {
    a++;
    b++;
}
```

**三个条件**：
- `*a != '\0'`：`haystack` 还没到结尾
- `*b != '\0'`：`needle` 还没到结尾
- `*a == *b`：当前字符匹配

只要三个条件都满足，就继续匹配下一个字符。

#### 5. 判断匹配结果

```cpp
if (*b == '\0') return p;
```

退出内层循环后，有两种可能：
1. **`*b == '\0'`**：`needle` 已经全部匹配完 → 成功，返回起始位置 `p`
2. **`*a != *b` 或 `*a == '\0'`**：匹配失败 → 继续外层循环，尝试下一个起始位置

注意这里只检查 `*b == '\0'`，因为：
- 如果 `b` 到达结尾，说明 `needle` 全部匹配成功
- 如果 `a` 到达结尾而 `b` 没有，说明剩余长度不够，匹配失败

#### 6. 未找到

```cpp
return nullptr;
```

外层循环结束仍未找到，返回空指针。

### 主函数

```cpp
int main()
{
    string a, b;
    
    // 读取两个字符串（不含空格）
    cin >> a;
    cout << '\n';
    cin >> b;
    
    // 调用函数（需要转换为 C 字符串）
    const char* result = myStrStr(a.c_str(), b.c_str());
    
    // 输出结果
    if (result != nullptr) {
        // 计算索引：结果指针 - 起始指针
        cout << (result - a.c_str()) << endl;
    } else {
        cout << -1 << endl;
    }
    
    return 0;
}
```

### 关键点

#### 1. `string` 转 `const char*`

```cpp
a.c_str()
```

`myStrStr` 的参数是 `const char*`，但我们用 `string` 读取输入（更方便）。

`c_str()` 方法返回指向 `string` 内部字符数组的指针，类型是 `const char*`。

#### 2. 指针算术计算索引

```cpp
result - a.c_str()
```

- `a.c_str()` 返回指向字符串起始位置的指针（比如地址 `0x1000`）
- `result` 是指向匹配位置的指针（比如地址 `0x1002`）
- 两个指针相减得到元素个数（索引）：`0x1002 - 0x1000 = 2`

#### 3. `cin >>` vs `getline`

```cpp
cin >> a;    // 遇到空格停止
```

因为代码中用了 `cin >>`，所以**输入字符串不能包含空格**。

如果需要支持空格，改成：

```cpp
getline(cin, a);
getline(cin, b);
```

#### 4. `cout << '\n'` 的作用

```cpp
cout << '\n';
```

这行代码在读取第一个字符串后输出一个换行符，可能是用于调试或格式化输出。

在实际 OJ 提交时，**这行应该删除**，否则会影响输出格式。

## 逐步演示

### 示例 1：找到匹配

**输入**：
```text
haystack = "hello"
needle   = "ll"
```

| 外层循环 | `p` 指向 | 内层匹配过程 | 结果 |
|---|---|---|---|
| 1 | `h` | `h` vs `l` → 不匹配 | 继续 |
| 2 | `e` | `e` vs `l` → 不匹配 | 继续 |
| 3 | `l` | `l` vs `l` ✓，`l` vs `l` ✓，`\0` → 成功 | 返回 `p`（索引 2） |

**输出**：`2`

### 示例 2：未找到

**输入**：
```text
haystack = "hello"
needle   = "world"
```

| 外层循环 | `p` 指向 | 内层匹配过程 | 结果 |
|---|---|---|---|
| 1 | `h` | `h` vs `w` → 不匹配 | 继续 |
| 2 | `e` | `e` vs `w` → 不匹配 | 继续 |
| 3 | `l` | `l` vs `w` → 不匹配 | 继续 |
| 4 | `l` | `l` vs `w` → 不匹配 | 继续 |
| 5 | `o` | `o` vs `w` → 不匹配 | 继续 |
| 结束 | - | 遍历完成 | 返回 `nullptr` |

**输出**：`-1`

### 示例 3：空串

**输入**：
```text
haystack = "hello"
needle   = ""
```

直接命中边界条件：`*needle == '\0'`，返回 `haystack`。

**输出**：`0`（起始索引）

### 示例 4：在开头

**输入**：
```text
haystack = "hello"
needle   = "he"
```

第一次外层循环就匹配成功。

**输出**：`0`

### 示例 5：在结尾

**输入**：
```text
haystack = "hello"
needle   = "lo"
```

第 4 次外层循环匹配成功。

**输出**：`3`

## 边界情况

### 1. `needle` 为空

```cpp
if (*needle == '\0') return haystack;
```

返回 `haystack` 的起始位置，索引为 0。

### 2. `haystack` 为空，`needle` 不为空

外层循环立即退出（`*p == '\0'`），返回 `nullptr`。

### 3. `needle` 比 `haystack` 长

内层循环会因为 `*a == '\0'` 提前退出，匹配失败。

### 4. 完全相等

```text
haystack = "hello"
needle   = "hello"
```

第一次外层循环就全部匹配，返回索引 0。

### 5. 多次出现

```text
haystack = "aaaa"
needle   = "aa"
```

返回**第一次**出现的位置，索引 0。

不会返回后续的匹配（索引 1、2）。

## 常见错误

### 错误 1：忘记边界检查

```cpp
// ❌ 缺少 *needle == '\0' 的处理
const char* myStrStr(const char* haystack, const char* needle)
{
    for (const char* p = haystack; *p != '\0'; p++) {
        // ...
    }
    return nullptr;
}
```

当 `needle` 为空时，应该返回 `haystack`，而不是 `nullptr`。

### 错误 2：内层循环判断条件错误

```cpp
// ❌ 缺少 *a != '\0' 检查
while (*b != '\0' && *a == *b) {
    a++; b++;
}
```

如果 `haystack` 先结束，`*a` 会是 `\0`，但仍然可能满足 `*a == *b`（如果 `*b` 也是 `\0`），导致错误匹配。

正确的应该是：

```cpp
while (*a != '\0' && *b != '\0' && *a == *b)
```

### 错误 3：判断匹配成功的条件错误

```cpp
// ❌ 只检查 *a 是否结束
if (*a == '\0') return p;
```

这会导致误判。应该检查 `*b == '\0'`，因为：
- `*b == '\0'` 说明 `needle` 全部匹配完
- `*a == '\0'` 只说明 `haystack` 的当前段结束了，不代表 `needle` 匹配完

### 错误 4：指针初始化位置错误

```cpp
// ❌ 在外层循环外初始化
const char* a = haystack;
const char* b = needle;

for (const char* p = haystack; *p != '\0'; p++) {
    while (*a != '\0' && *b != '\0' && *a == *b) {
        a++; b++;
    }
    // ...
}
```

这样 `a` 和 `b` 只初始化一次，后续外层循环无法重新开始匹配。

应该在每次外层循环内重新初始化：

```cpp
for (const char* p = haystack; *p != '\0'; p++) {
    const char* a = p;
    const char* b = needle;
    // ...
}
```

### 错误 5：main 函数中的类型错误

```cpp
// ❌ 指针和 string 相减
string a = "hello";
const char* result = myStrStr(a.c_str(), "ll");
cout << (result - a) << endl;  // 编译错误
```

`result` 是 `const char*`，`a` 是 `string`，无法直接相减。

正确：

```cpp
cout << (result - a.c_str()) << endl;
```

## 复杂度分析

- **时间复杂度**：`O(m * n)`
  - `m` = `haystack` 的长度
  - `n` = `needle` 的长度
  - 外层循环 `O(m)` 次
  - 每次内层循环最多 `O(n)` 次
  - 最坏情况：`haystack = "aaaa...b"`，`needle = "aaab"`
  
- **空间复杂度**：`O(1)`
  - 只用了常数个指针变量

## 优化方向

### KMP 算法（Knuth-Morris-Pratt）

时间复杂度优化到 `O(m + n)`，通过预处理 `needle` 的部分匹配表（next 数组），避免重复比较。

**适用场景**：
- `needle` 很长
- `haystack` 和 `needle` 有大量重复字符
- 需要多次匹配（可以复用 next 数组）

**缺点**：
- 实现复杂
- 空间 `O(n)`
- 对短字符串可能比暴力慢（常数因子）

### Rabin-Karp 算法（哈希匹配）

使用滚动哈希，时间复杂度平均 `O(m + n)`。

### Boyer-Moore 算法

实际应用中最快的字符串匹配算法，平均 `O(m / n)`。

### 面试建议

- **面试时先写暴力算法**（本题实现），快速通过基本测试
- 如果面试官追问优化，再讨论 KMP 或其他算法
- 暴力算法代码简洁，不易出错，适合有时间限制的场景

## 测试用例

| 输入（haystack / needle） | 输出 | 说明 |
|---|---|---|
| `hello` / `ll` | `2` | 正常匹配 |
| `hello` / `world` | `-1` | 未找到 |
| `hello` / `` | `0` | 空串 |
| `hello` / `he` | `0` | 在开头 |
| `hello` / `lo` | `3` | 在结尾 |
| `aaaa` / `aa` | `0` | 多次出现 |
| `` / `hello` | `-1` | 主串为空 |
| `hello` / `hello` | `0` | 完全相等 |
| `mississippi` / `issip` | `4` | 复杂匹配 |

## 相关题目

- **LeetCode 28. 找出字符串中第一个匹配项的下标**：原题
- **LeetCode 686. 重复叠加字符串匹配**：字符串匹配的变体
- **LeetCode 796. 旋转字符串**：可以用字符串匹配解决
- **KMP 模板题**：各大 OJ 的字符串匹配专题

## 文件说明

- `muxi02.cpp`：完整实现，包含 `myStrStr` 函数和测试 main 函数
- 函数实现了 C 标准库 `strstr` 的基本功能
- 使用朴素的双指针暴力匹配算法
