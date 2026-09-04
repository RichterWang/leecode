# LeetCode Hot 100

## 56. Merge Intervals

- **题目链接**：https://leetcode.com/problems/merge-intervals/
- **核心思路**：先按区间左端点排序，再顺序扫描并维护当前合并结果。

### 做法

1. 将所有区间按字典序排序，对区间来说等价于先按左端点升序、再按右端点升序。
2. 用结果数组保存当前已经合并好的区间。
3. 如果当前区间和结果数组最后一个区间有重叠：

```cpp
result.back()[1] >= intervals[i][0]
```

则更新右端点为两者较大值。
4. 如果没有重叠，就把当前区间直接加入结果。

### 复杂度

- **时间复杂度**：`O(n log n)`，排序占主导
- **空间复杂度**：`O(n)`，用于保存结果

### 代码

- `leecode56.cpp`

## 41. First Missing Positive

- **题目链接**：https://leetcode.com/problems/first-missing-positive/
- **核心思路**：利用数组本身作为哈希表，把有效正整数 `x` 放到下标 `x - 1` 的位置。

### 状态范围

数组长度为 `n` 时，最小缺失正整数一定在 `1..n+1` 中：

- 如果 `1..n` 中有缺失值，答案就在这个范围内
- 如果 `1..n` 全部出现，答案就是 `n+1`

因此只需要处理满足下面条件的元素：

```cpp
1 <= nums[i] <= n
```

负数、`0` 和大于 `n` 的数字都不会影响答案，可以直接忽略。

### 原地交换

对于有效数字 `x`，它理想的位置是下标 `x - 1`。对每个位置 `i`，只要当前数字仍然有效、且目标位置不是相同的重复值，就持续交换：

```cpp
while (nums[i] > 0 && nums[i] <= n &&
       nums[i] != nums[nums[i] - 1]) {
    swap(nums[i], nums[nums[i] - 1]);
}
```

使用 `while` 而不是只交换一次，是因为交换后当前位置会换入一个新数字，这个新数字也可能需要继续放到它自己的位置。

判断目标位置的值不相同，可以避免重复数字导致数组不变化、循环无法结束。例如 `[1, 1]` 中，第二个 `1` 不需要再和第一个 `1` 交换。

### 最终扫描

整理后，理想情况是：

```text
nums[0] = 1, nums[1] = 2, nums[2] = 3, ...
```

从左到右找到第一个满足：

```cpp
nums[i] != i + 1
```

的位置，则 `i + 1` 就是最小缺失正整数。如果所有位置都正确，返回 `n + 1`。

### 复杂度

- **时间复杂度**：`O(n)`。虽然包含嵌套 `while`，但每次有效交换都会让一个元素更接近正确位置，整体交换次数是线性的。
- **空间复杂度**：`O(1)`，只在原数组上操作。

### 代码

- `leecode41.cpp`

### 方法一：辅助数组

- **核心思路**：新开一个同样大小的数组，把原数组最后 `k` 个元素放到最前面，其余元素整体后移。

#### 做法

1. 先做 `k %= nums.size()`，避免轮转次数超过数组长度。
2. 创建一个长度为 `nums.size()` 的临时数组 `temp`。
3. 将原数组前 `n - k` 个元素搬到 `temp[k...]`。
4. 将原数组最后 `k` 个元素搬到 `temp[0...k-1]`。
5. 最后执行 `nums = temp`，用轮转后的结果覆盖原数组。

#### 复杂度

- **时间复杂度**：`O(n)`
- **空间复杂度**：`O(n)`

### 方法二：原地三次翻转

- **核心思路**：把数组看成前段 `A` 和后段 `B`，右旋 `k` 位的目标是得到 `B + A`。先整体翻转，再分别翻转前 `k` 个和后 `n-k` 个元素，即可在原地得到结果。

#### 做法

1. 先做 `k %= nums.size()`。
2. 整体翻转整个数组。
3. 翻转前 `k` 个元素。
4. 翻转后 `n-k` 个元素。

#### 复杂度

- **时间复杂度**：`O(n)`
- **空间复杂度**：`O(1)`

### 代码

- `leecode189.cpp`
- `leecode189_reverse.cpp`

## 240. Search a 2D Matrix II

- **题目链接**：https://leetcode.com/problems/search-a-2d-matrix-ii/
- **核心思路**：从右上角开始利用行列递增的单调性，每一步排除一整行或一整列。

### 做法

1. 先处理空矩阵或空行，直接返回 `false`。
2. 从右上角 `matrix[0][n - 1]` 开始。
3. 如果当前值等于 `target`，直接返回 `true`。
4. 如果当前值大于 `target`，说明这一列当前位置及其下方都不可能是答案，向左移动。
5. 如果当前值小于 `target`，说明这一行当前位置及其左边都不可能是答案，向下移动。
6. 指针越界后仍未找到，则返回 `false`。

### 为什么从右上角开始

右上角位置同时满足：

- 左边的元素都更小
- 下边的元素都更大

因此和 `target` 比较后，下一步方向是唯一确定的：

```cpp
if (matrix[i][j] < target) i++;
else j--;
```

### 复杂度

- **时间复杂度**：`O(m + n)`
- **空间复杂度**：`O(1)`

### 代码

- `leecode240.cpp`

## 141. Linked List Cycle

- **题目链接**：https://leetcode.com/problems/linked-list-cycle/
- **核心思路**：快慢指针（Floyd's Cycle Detection Algorithm），如果链表有环，快指针最终会追上慢指针。

### 算法思想

设置两个指针：
- `slow`（慢指针）：每次移动 1 步
- `fast`（快指针）：每次移动 2 步

如果链表有环，两个指针都会进入环中，且快指针与慢指针的距离每次缩小 1，最终一定会相遇。

如果链表无环，快指针会先到达链表尾部（`nullptr`）。

### 关键细节

#### 1. 判断相遇

用**指针地址**判断，而不是节点的值：

```cpp
if (slow == fast)  // 正确：比较指针地址
```

❌ 错误写法：
```cpp
if (slow->val == fast->val)  // 错误：值相同不代表是同一个节点
```

#### 2. 边界检查

必须在访问指针成员之前检查指针是否为空：

```cpp
if (head == nullptr || head->next == nullptr) {
    return false;  // 空链表或单节点链表无环
}
```

#### 3. 循环条件

在移动 `fast` 指针（`fast->next->next`）之前，必须确保：
- `fast != nullptr`（fast 本身存在）
- `fast->next != nullptr`（fast 的下一个节点存在）

```cpp
while (fast->next != nullptr && fast->next->next != nullptr)
```

这样可以避免空指针解引用错误。

### 链表操作基础

#### 移动到下一个节点

```cpp
slow = slow->next;           // 慢指针移动 1 步
fast = fast->next->next;     // 快指针移动 2 步
```

#### 尾节点判断

链表的尾节点是最后一个实际存在的节点，它的 `next` 指向 `nullptr`：

```
节点1 → 节点2 → 节点3 → nullptr
                 ↑        ↑
               尾节点    不是节点
```

判断到达尾部：
```cpp
if (node->next == nullptr)  // node 是尾节点
```

### 复杂度

- **时间复杂度**：`O(n)`，每个节点最多被访问常数次
- **空间复杂度**：`O(1)`，只使用两个指针

### 代码

- `leecode141.cpp`

## 78. Subsets

- **题目链接**：https://leetcode.com/problems/subsets/
- **核心思路**：位掩码枚举。用 `[0, 2^n)` 区间内的每个整数表示一种选取方案，第 `i` 位为 1 就取 `nums[i]`。

### 做法

1. 记 `n = nums.size()`，子集总数为 `2^n`。
2. 外层循环让 `mask` 从 `0` 遍历到 `(1 << n) - 1`，每个取值对应一个子集。
3. 内层循环逐位检查，第 `i` 位为 1 就把 `nums[i]` 收进当前子集：

```cpp
if (mask & (1 << i)) temp.push_back(nums[i]);
```

4. 内层结束后把 `temp` 压入结果。

### 为什么不需要去重

`mask` 与子集是双射关系：每个 `mask` 唯一决定一个子集，每个子集也唯一对应一个 `mask`，而 `mask` 在 `[0, 2^n)` 上每个值恰好取一次。所以天然不会重复，不需要任何去重逻辑。

`n = 3` 时的对应关系：

```text
mask = 0b000 = 0  →  {}
mask = 0b001 = 1  →  {nums[0]}
mask = 0b010 = 2  →  {nums[1]}
mask = 0b011 = 3  →  {nums[0], nums[1]}
mask = 0b100 = 4  →  {nums[2]}
mask = 0b101 = 5  →  {nums[0], nums[2]}
mask = 0b110 = 6  →  {nums[1], nums[2]}
mask = 0b111 = 7  →  {nums[0], nums[1], nums[2]}
```

题目给的"元素互不相同"是这个双射成立的前提。如果允许重复元素（LeetCode 90 子集 II），不同 `mask` 会产出相同的值集合，例如 `nums = [1, 1]` 时 `0b01` 和 `0b10` 都得到 `{1}`，此时需要先排序再跳过同层重复，位掩码解法不如回溯顺手。

### mask 只读，不需要置位

内层的 `mask & (1 << i)` 是**查询**第 `i` 位，不涉及写操作。`mask` 由外层的 `mask++` 驱动，是循环给定的输入，信息流向是 `mask → temp`。

这一点容易和状态压缩搜索里的用法混淆。对比记忆：

| | mask 的角色 | 操作 | 含义 |
|---|---|---|---|
| 本题 | 循环计数器，只读输入 | `&` 查询 | 当前方案选了哪些元素 |
| 状压搜索（如 3568、864） | 搜索状态，被动累积 | `\|=` 置位 | 我已经收集/取得了什么 |

如果在内层修改 `mask`，会破坏外层的枚举顺序，导致漏掉或重复一批子集。

### 常见错误

**空集重复。** 循环从 `mask = 0` 开始，这一轮内层一次都不 push，`temp` 保持为空，空集已经被生成了。如果在循环前又手动写一句 `ans.push_back({})`，结果数量会变成 `2^n + 1`。

**循环边界。** 写 `mask < (1 << n)` 而不是 `<=`。`[0, 2^n)` 恰好 `2^n` 个值，用 `<=` 会多枚举一个越界的 `mask`。

**运算符优先级。** `&` 的优先级低于 `==`，所以 `mask & (1 << i) == 0` 会被解析成 `mask & ((1 << i) == 0)`，恒为 0。要写成 `(mask & (1 << i)) == 0`，括号不能省。

**忘记 return。** 声明了返回值却走到函数末尾是未定义行为，加 `-Wall` 可以当场发现。

### 另一种解法：回溯

递归地对每个位置做"选/不选"的二叉决策：

```cpp
void dfs(int i) {
    if (i == n) { ans.push_back(path); return; }
    dfs(i + 1);                    // 不选 nums[i]
    path.push_back(nums[i]);
    dfs(i + 1);                    // 选 nums[i]
    path.pop_back();
}
```

两者本质相同——递归树的每条根到叶路径就是一个 `mask` 的比特序列。位掩码版没有递归开销、代码更短；回溯版在需要剪枝时（限定子集大小、处理重复元素）更灵活。

### 复杂度

- **时间复杂度**：`O(n × 2^n)`。共 `2^n` 个子集，每个需要 `O(n)` 扫一遍所有位。这也是下界，因为输出本身就有 `n × 2^(n-1)` 个元素。
- **空间复杂度**：输出占 `O(n × 2^n)`，额外空间 `O(n)`。

### 代码

- `leecode78.cpp`

## 17. Letter Combinations of a Phone Number

- **题目链接**：https://leetcode.com/problems/letter-combinations-of-a-phone-number/
- **核心思路**：回溯。递归深度等于 `digits.size()`，每层枚举当前数字对应的所有字母。

### 为什么必须用递归

如果 `digits = "23"`，两层嵌套循环就够了：

```cpp
for (char a : "abc")
    for (char b : "def")
        answer.push_back(string{a, b});
```

但 `"234"` 要三层，`"2345"` 要四层。**层数由运行时的输入长度决定，没法写成固定层数的嵌套循环。** 递归正是用来模拟这种"层数可变的嵌套循环"：递归一层等价于多写一层 `for`。

这也解释了为什么单层 `for (int i = 0; i < n; i++)` 走不通。单层循环只能携带一份状态线性往下走，而第 `i` 位有 3~4 个分支，每个分支都要各自继续展开成完整字符串。一个 `temp` 装不下"同时存在多条待续路径"的结构。

### 做法

1. 建立数字到字母的映射表。
2. 用 `idx` 标记当前处理 `digits` 的第几位，`temp` 保存当前已选的字母。
3. 递归出口：`idx == n` 时 `temp` 已凑满 `n` 个字母，收进结果并返回。
4. 否则取出 `digits[idx]` 对应的字母串，逐个尝试：追加到 `temp` → 递归下一位 → 从 `temp` 弹出。

```cpp
function<void(int)> backtrack = [&](int idx) {
    if (idx == n) { answer.push_back(temp); return; }
    for (char c : reference[digits[idx]]) {
        temp.push_back(c);      // 做选择
        backtrack(idx + 1);     // 递归下一位
        temp.pop_back();        // 撤销选择
    }
};
```

### pop_back 为什么不能省

`temp` 只有一份，被所有分支**共享复用**。递归返回时 `temp` 里还留着刚才那条路径的字母，不弹掉的话下一个分支就会接在错误的前缀后面。

`pop_back()` 的职责是把 `temp` 恢复成"进入本层循环时的状态"，保证每次迭代起点一致。"回溯"这个名字就来自这个撤销动作。

`digits = "23"` 的 `temp` 变化（缩进表示递归深度）：

```text
backtrack(0), temp=""
  c='a' → temp="a"
    backtrack(1)
      c='d' → temp="ad" → 收集 "ad" → pop → temp="a"
      c='e' → temp="ae" → 收集 "ae" → pop → temp="a"
      c='f' → temp="af" → 收集 "af" → pop → temp="a"
  pop → temp=""
  c='b' → temp="b" → ... 收集 "bd" "be" "bf"
  pop → temp=""
  c='c' → temp="c" → ... 收集 "cd" "ce" "cf"
```

每次内层递归返回后 `temp` 都被还原成 `"a"`，靠的就是 `pop_back()`。

### 替代写法：按值传参

不共享状态就不需要撤销：

```cpp
function<void(int, string)> backtrack = [&](int idx, string cur) {
    if (idx == n) { answer.push_back(cur); return; }
    for (char c : reference[digits[idx]]) {
        backtrack(idx + 1, cur + c);   // 每层拿到独立副本
    }
};
```

写起来更省心，代价是每次递归都拷贝一份字符串。本题字符串短，差别不大。但"共享 + 撤销"是更通用的模式，子集、排列、组合、N 皇后都是这个套路，值得优先写熟。

### 替代写法：迭代按层展开

把状态从"一个 `temp`"换成"一个结果集"，每处理一位就把已有结果全部扩展一轮：

```cpp
vector<string> answer{""};                 // 注意初始是一个空串
for (int i = 0; i < n; i++) {
    const string& letters = reference[digits[i]];
    vector<string> next;
    for (const string& prefix : answer)
        for (char c : letters)
            next.push_back(prefix + c);
    answer = move(next);
}
```

`answer` 规模随层递增：`1 → 3 → 9`（对应 `"23"`）。这是 BFS 式展开，不用递归。

易错点：`answer` 必须初始化成 `{""}` 而不是 `{}`，否则第一轮内层循环一次都不执行，结果恒为空。

两种写法同量级，但空间不同：回溯是 `O(n)`（只存一条路径 + 递归栈），迭代是 `O(4^n)`（要同时存住整层）。

### 常见错误

**空串输入。** `digits` 为空时应返回空数组 `{}`，而不是含一个空串的 `{""}`。如果不提前特判，`backtrack(0)` 会立刻命中 `idx == n` 把空串收进结果。

**忘记 return。** 声明了返回值却走到函数末尾是未定义行为，加 `-Wall` 能当场发现。

### 优化空间

映射表用 `static` 或直接数组索引可以省掉每次调用的构造开销：

```cpp
static const string mp[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
// 取用：mp[digits[idx] - '0']
```

题目保证只含 2-9，不用担心越界。本题数据量小，`unordered_map` 完全够用。

### 复杂度

设 `n = digits.size()`，每位最多 4 个字母：

- **时间复杂度**：`O(4^n × n)`。结果最多 `4^n` 个，每个长度 `n`，构造和拷贝都要 `O(n)`
- **空间复杂度**：额外 `O(n)`（`temp` + 递归栈），不计输出

### 代码

- `leecode17.cpp`
