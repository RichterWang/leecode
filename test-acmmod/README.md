# 沐曦一面笔试题：合并区间

**难度**：Medium　**标签**：数组、排序、贪心

## 题目描述

给定 n 个区间 `[minValue, maxValue]`，合并所有重叠的区间，返回合并后的区间数量和每个区间的起止值。

**输入格式**：

```text
第一行：区间数量 n
接下来 n 行：每行两个整数 minValue 和 maxValue，表示一个区间
```

**输出格式**：

```text
第一行：合并后的区间数量
接下来若干行：每行两个整数，表示合并后的一个区间
```

**示例**：

```text
输入：
4
1 3
2 6
8 10
15 18

输出：
3
1 6
8 10
15 18
```

**解释**：
- 区间 `[1,3]` 和 `[2,6]` 重叠，合并为 `[1,6]`
- 区间 `[8,10]` 独立
- 区间 `[15,18]` 独立

## 核心思路：排序 + 贪心合并

这是经典的"合并区间"问题，类似 LeetCode 56。

### 算法步骤

1. **按起点排序**：将所有区间按 `minValue` 升序排列（起点相同时按 `maxValue` 排序）
2. **初始化当前区间**：用第一个区间初始化 `current`
3. **遍历合并**：
   - 如果下一个区间的起点 ≤ `current` 的终点 → 有重叠，更新终点为两者最大值
   - 否则 → 没有重叠，保存 `current`，开始新区间
4. **收尾**：循环结束后，保存最后一个区间

### 为什么要排序？

未排序时，区间顺序混乱，无法判断哪些区间相邻。排序后，所有可能重叠的区间会相邻排列，只需一次遍历。

### 关键判断条件

```cpp
if (segs[i].minValue <= current.maxValue)
```

用 `<=` 而不是 `<`，因为边界相接的区间也算能合并：
- `[1,3]` 和 `[3,5]` → 合并为 `[1,5]`

如果题目要求严格重叠（不含边界相接），改成 `<`。

### 更新终点用 `max`

```cpp
current.maxValue = max(current.maxValue, segs[i].maxValue);
```

因为排序只保证起点递增，终点可能乱序。例如：
- 区间 `[[1,10], [2,3]]` 排序后不变
- 合并时应该是 `[1,10]` 而不是 `[1,3]`

所以必须取两个终点的最大值。

## 代码实现

### 数据结构

```cpp
typedef struct {
    int minValue;
    int maxValue;
} Segment;

typedef struct {
    int segNum;
    vector<Segment> segs;
} SegRanges;
```

用结构体封装区间和区间集合，便于管理。

### 核心函数：mergeSegs

```cpp
SegRanges mergeSegs(SegRanges segs)
{
    SegRanges result;
    result.segNum = 0;
    
    // 空输入直接返回
    if (segs.segs.empty()) return result;

    // 1. 按起点排序（相同时按终点排序）
    sort(segs.segs.begin(), segs.segs.end(), 
        [](const Segment& a, const Segment& b) {
            if (a.minValue != b.minValue) 
                return a.minValue < b.minValue;
            else 
                return a.maxValue < b.maxValue;
        });

    // 2. 初始化：第一个区间作为"当前区间"
    Segment current = segs.segs[0];
    
    // 3. 从第二个区间开始遍历
    for (int i = 1; i < static_cast<int>(segs.segs.size()); i++) {
        // 判断是否能合并
        if (segs.segs[i].minValue <= current.maxValue) {
            // 能合并：更新当前区间的终点
            current.maxValue = max(current.maxValue, segs.segs[i].maxValue);
        } else {
            // 不能合并：保存当前区间，开始新区间
            result.segs.push_back(current);
            result.segNum++;
            current = segs.segs[i];
        }
    }
    
    // 4. 别忘了最后一个区间
    result.segs.push_back(current);
    result.segNum++;
    
    return result;
}
```

### 主函数

```cpp
int main()
{
    SegRanges input;
    int n;
    
    // 读取区间数量
    cin >> n;
    input.segNum = n;
    
    // 读取每个区间
    for (int i = 0; i < n; i++) {
        Segment seg;
        cin >> seg.minValue >> seg.maxValue;
        input.segs.push_back(seg);
    }
    
    // 合并
    SegRanges answer = mergeSegs(input);
    
    // 输出
    cout << answer.segNum << endl;
    for (const auto& seg : answer.segs) {
        cout << seg.minValue << " " << seg.maxValue << endl;
    }
    
    return 0;
}
```

## 逐步演示

**输入**：`[[1,3], [2,6], [8,10], [15,18]]`

### 排序后

已经按起点排序，不变。

### 遍历合并

| 步骤 | 遍历区间 | `current` | 判断 | 操作 | `result` |
|---|---|---|---|---|---|
| 初始 | - | `[1,3]` | - | 初始化 | `[]` |
| i=1 | `[2,6]` | `[1,3]` | `2 ≤ 3` ✓ | 合并，`current = [1, max(3,6)] = [1,6]` | `[]` |
| i=2 | `[8,10]` | `[1,6]` | `8 ≤ 6` ✗ | 保存 `[1,6]`，`current = [8,10]` | `[[1,6]]` |
| i=3 | `[15,18]` | `[8,10]` | `15 ≤ 10` ✗ | 保存 `[8,10]`，`current = [15,18]` | `[[1,6], [8,10]]` |
| 结束 | - | `[15,18]` | - | 保存最后的 `current` | `[[1,6], [8,10], [15,18]]` |

### 输出

```text
3
1 6
8 10
15 18
```

## 边界情况

### 1. 只有一个区间

```text
输入：
1
5 10

输出：
1
5 10
```

循环不进入（`i` 从 1 开始），直接保存 `current`。

### 2. 所有区间都重叠

```text
输入：
3
1 4
2 5
3 6

输出：
1
1 6
```

每次都合并，最终只剩一个区间。

### 3. 没有重叠

```text
输入：
3
1 2
3 4
5 6

输出：
3
1 2
3 4
5 6
```

每次都不合并，结果和输入相同。

### 4. 区间完全包含

```text
输入：
3
1 10
2 3
4 5

输出：
1
1 10
```

`[2,3]` 和 `[4,5]` 都被 `[1,10]` 包含，合并时取 `max` 确保正确。

### 5. 边界相接

```text
输入：
2
1 3
3 5

输出：
1
1 5
```

因为用 `<=` 判断，边界相接也会合并。

## 常见错误

### 错误 1：忘记保存最后一个区间

```cpp
// ❌ 循环结束后缺少这一行
result.segs.push_back(current);
result.segNum++;
```

最后一个 `current` 还没加入结果，必须在循环外补上。

### 错误 2：不用 `max` 更新终点

```cpp
// ❌ 直接赋值
current.maxValue = segs.segs[i].maxValue;
```

这样会导致 `[[1,10], [2,3]]` 合并成 `[1,3]`，错误。

应该：

```cpp
current.maxValue = max(current.maxValue, segs.segs[i].maxValue);
```

### 错误 3：合并条件用 `<`

```cpp
// ❌ 边界相接的区间无法合并
if (segs.segs[i].minValue < current.maxValue)
```

`[1,3]` 和 `[3,5]` 会被当作不重叠，输出两个区间。

应该用 `<=`（除非题目明确要求严格重叠）。

### 错误 4：Lambda 语法错误

```cpp
// ❌ 缺少参数列表的括号
[] const Segment& a, const Segment& b { ... }
```

正确：

```cpp
[](const Segment& a, const Segment& b) { ... }
```

### 错误 5：忘记排序

不排序直接合并会漏掉很多可以合并的区间，因为它们不相邻。

## 复杂度分析

- **时间复杂度**：`O(n log n)`
  - 排序：`O(n log n)`
  - 遍历：`O(n)`
  - 总时间：`O(n log n)`

- **空间复杂度**：`O(1)`
  - 原地排序（不算输入和输出的空间）
  - 只用了常数个辅助变量

## 优化建议

### 1. 简化排序

如果只关心起点，排序可以简化：

```cpp
sort(segs.segs.begin(), segs.segs.end(), 
    [](const Segment& a, const Segment& b) {
        return a.minValue < b.minValue;
    });
```

因为合并时会用 `max` 更新终点，所以终点的初始顺序无关紧要。

### 2. 避免修改输入

如果需要保留原输入，传 `const` 引用，函数内复制一份：

```cpp
SegRanges mergeSegs(const SegRanges& segs)
{
    // ...
    vector<Segment> sorted = segs.segs;
    sort(sorted.begin(), sorted.end(), ...);
    // 后续用 sorted 操作
}
```

### 3. 用 `std::tie` 简化排序

```cpp
sort(segs.segs.begin(), segs.segs.end(), 
    [](const Segment& a, const Segment& b) {
        return std::tie(a.minValue, a.maxValue) < 
               std::tie(b.minValue, b.maxValue);
    });
```

需要 `#include <tuple>`。

## 测试用例

### 测试 1：基本用例

```text
输入：
4
1 3
2 6
8 10
15 18

输出：
3
1 6
8 10
15 18
```

### 测试 2：全部合并

```text
输入：
4
1 4
4 5
5 6
6 7

输出：
1
1 7
```

### 测试 3：无重叠

```text
输入：
3
1 2
4 5
7 8

输出：
3
1 2
4 5
7 8
```

### 测试 4：包含关系

```text
输入：
4
1 10
2 3
4 5
6 7

输出：
1
1 10
```

## 相关题目

- **LeetCode 56. 合并区间**：原题
- **LeetCode 57. 插入区间**：在已排序的区间列表中插入新区间
- **LeetCode 986. 区间列表的交集**：求两个区间列表的交集
- **LeetCode 435. 无重叠区间**：移除最少区间使剩余区间不重叠

## 文件说明

- `muxi01.cpp`：完整实现，包含数据结构定义、合并函数和主函数
