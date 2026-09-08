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

## 39. Combination Sum

- **中文名称**：组合总和
- **题目链接**：https://leetcode.com/problems/combination-sum/
- **核心要求**：从互不相同的候选数中选取若干数字，使其总和等于 `target`；同一个候选数可以无限次重复选取。
- **当前状态**：已完成排序 + 回溯解法，同时保留位掩码错误解法用于复盘。

### 当前错误思路：二进制位掩码枚举

当前解法枚举：

```cpp
for (int mask = 0; mask < (1 << n); mask++)
```

并用 `mask` 的第 `j` 位表示是否选择 `candidates[j]`。

一个二进制位只有两种状态：

```text
0 → 不选择
1 → 选择一次
```

因此，这种状态只能表示每个候选数被选择 `0` 次或 `1` 次，无法表示选择 `2` 次、`3` 次等情况。

例如：

```text
candidates = [2, 3, 6, 7]
target = 7
```

正确答案为：

```text
[[2, 2, 3], [7]]
```

位掩码可以表示 `[7]`，却无法表示 `[2, 2, 3]`，因为数组中只有一个 `2`，对应的二进制位无法同时表示“选择三次”。

这说明普通二进制子集枚举适用于 LeetCode 78 这类“每个位置最多选择一次”的问题，不适用于本题的“元素可以无限复用”。

### 当前代码还有一个独立的位判断错误

错误代码：

```cpp
if ((mask & (1 << j)) != 1)
```

`mask & (1 << j)` 的结果不是统一的 `0` 或 `1`，而是：

```text
0 或 2^j
```

例如当 `j = 2` 且第 2 位已置位时：

```cpp
mask & (1 << 2) == 4
```

此时 `4 != 1` 为真，代码反而进入分支。因此，`!= 1` 不能用来判断某一位是否被选中。

普通子集枚举的正确判断应为：

```cpp
if ((mask & (1 << j)) != 0)
```

或者简写为：

```cpp
if (mask & (1 << j))
```

但需要注意：**即使修正这个位判断，位掩码仍然只能让每个元素选择一次，无法满足 LeetCode 39 的无限复用要求。**

### 为什么不能简单增加 mask 位数

理论上可以给每个候选数分配多个位，或者枚举它的选择次数：

```text
0 次、1 次、2 次、...、target / candidates[i] 次
```

但不同候选数的次数上限不同，这已经不再是简单的二进制子集枚举。继续使用 `mask` 会导致状态编码复杂、枚举大量无效情况。

更自然的方法是回溯：每层选择一个候选数，并通过递归参数控制该数字能否再次使用。

### 正确解法：排序 + 回溯

定义搜索状态：

```cpp
dfs(start, remain)
```

含义是：

> 只从下标 `start` 及之后的候选数中选择，凑出剩余目标 `remain`。

核心决策应为：

```cpp
path.push_back(candidates[i]);
dfs(i, remain - candidates[i]);
path.pop_back();
```

递归时继续传入 `i`，而不是 `i + 1`：

| 下一层起点 | 含义 |
|---|---|
| `i` | 当前候选数仍可继续选择，实现无限复用 |
| `i + 1` | 当前候选数不能再次选择，每个数最多选一次 |

完整回溯过程包含三个动作：

```cpp
path.push_back(candidates[i]);                    // 做选择
dfs(i, remain - candidates[i], path, answer, candidates);
path.pop_back();                                  // 撤销选择
```

当 `remain == 0` 时，当前路径已经构成一个合法组合，将它复制到答案中并返回：

```cpp
if (remain == 0) {
    answer.push_back(path);
    return;
}
```

`start` 同时保证候选数只按下标非递减顺序加入路径，避免把以下排列重复计为不同组合：

```text
[2, 2, 3]
[2, 3, 2]
[3, 2, 2]
```

它们在本题中是同一个组合，正确搜索只生成 `[2, 2, 3]`。

### 排序与剪枝

搜索前先排序：

```cpp
sort(candidates.begin(), candidates.end());
```

当当前候选数已经大于剩余目标时：

```cpp
if (candidates[i] > remain) {
    break;
}
```

由于后面的候选数只会更大，因此当前分支以及后续同层分支都不可能凑出 `remain`，可以直接结束循环。

### 示例推演

对于：

```text
candidates = [2, 3, 6, 7]
target = 7
```

主要搜索路径为：

```text
[]
├─ 2 → remain=5
│  ├─ 2 → remain=3
│  │  ├─ 2 → remain=1（剪枝）
│  │  └─ 3 → remain=0，收集 [2, 2, 3]
│  └─ 3 → remain=2（剪枝）
├─ 3 → remain=4
│  └─ 3 → remain=1（剪枝）
├─ 6 → remain=1（剪枝）
└─ 7 → remain=0，收集 [7]
```

最终得到：

```text
[[2, 2, 3], [7]]
```

### 正确解法复杂度

设最小候选数为 `m`，递归深度最大约为 `target / m`。

- **时间复杂度**：最坏为指数级，具体取决于候选数、目标值和合法组合数量；生成每个答案还需要复制当前路径。
- **额外空间复杂度**：`O(target / m)`，用于递归栈和当前路径，不计输出结果。

### 错误解法的适用范围

如果题目改成“每个候选数最多使用一次”，修正位判断后，位掩码可以枚举所有子集：

```cpp
if ((mask & (1 << j)) != 0) {
    sum += candidates[j];
}
```

但如果候选数组含有重复值，还需要额外去重。因此，即使是“最多选择一次”的组合问题，排序加回溯通常也比位掩码更灵活。

### 复杂度分析（当前错误解法）

当前位掩码代码：

- **时间复杂度**：`O(n × 2^n)`
- **额外空间复杂度**：`O(n)`，用于保存当前子集
- **正确性**：不满足“同一个数字可无限次选取”的题意，并且当前 `!= 1` 的位判断也有错误

### 代码

- `leecode39.cpp`：排序 + 回溯正确解法
- `leecode39_wrong.cpp`：位掩码错误解法，仅用于记录和复盘

## 79. Word Search

- **中文名称**：单词搜索
- **题目链接**：https://leetcode.com/problems/word-search/
- **核心思路**：枚举每个可能的起点，通过 DFS 向上、下、左、右搜索下一个字符，并用访问数组保证同一条路径中不会重复使用同一个单元格。

### DFS 状态

递归函数：

```cpp
dfs(x, y, board, word, ptr, visited)
```

表示：

> 当前位于棋盘坐标 `(x, y)`，尝试使用该单元格匹配 `word[ptr]`。

如果当前字符不匹配，当前路径立即失败：

```cpp
if (board[x][y] != word[ptr]) {
    return false;
}
```

如果当前字符已经是单词的最后一个字符，说明整个单词匹配完成：

```cpp
if (ptr == static_cast<int>(word.size()) - 1) {
    return true;
}
```

搜索相邻单元格时，单词下标必须前进一位：

```cpp
dfs(nextX, nextY, board, word, ptr + 1, visited)
```

### 枚举搜索起点

单词可能从棋盘中的任意位置开始，因此需要遍历整个棋盘。只有当前单元格等于单词首字符时才启动 DFS：

```cpp
for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
        if (board[i][j] == word[0] &&
            dfs(i, j, board, word, 0, visited)) {
            return true;
        }
    }
}
```

只要有一个起点能够匹配完整单词，就可以立即返回 `true`。

### 四个移动方向

使用固定数组保存上、下、左、右四个方向：

```cpp
array<pair<int, int>, 4> moving = {{
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1}
}};
```

对于当前位置 `(x, y)`，下一位置为：

```cpp
int nextX = x + dx;
int nextY = y + dy;
```

递归前必须检查下一位置是否越界：

```cpp
if (nextX < 0 || nextX >= row ||
    nextY < 0 || nextY >= col) {
    continue;
}
```

### 访问标记与回溯

题目规定同一条搜索路径中不能重复使用同一个单元格，因此进入当前格后进行标记：

```cpp
visited[x][y] = true;
```

只有尚未出现在当前路径中的相邻格才能继续搜索：

```cpp
if (visited[nextX][nextY]) {
    continue;
}
```

当前分支搜索完成后，要撤销当前格的访问标记：

```cpp
visited[x][y] = false;
```

完整过程是：

```cpp
visited[x][y] = true;    // 做选择
dfs(...);                // 搜索相邻位置
visited[x][y] = false;   // 撤销选择
```

这里的 `visited` 表示“当前搜索路径使用过哪些单元格”，而不是所有起点共享的永久访问记录。撤销标记后，其他分支和其他起点仍然可以使用该单元格。

### 递归返回值传播

找到完整单词后，子递归返回的 `true` 必须逐层向上传递：

```cpp
if (dfs(nextX, nextY, board, word, ptr + 1, visited)) {
    visited[x][y] = false;
    return true;
}
```

如果忽略子递归返回值，即使下层已经找到答案，上层也无法获知结果。

当所有相邻方向都失败时，需要恢复状态并明确返回 `false`：

```cpp
visited[x][y] = false;
return false;
```

### 示例

对于：

```text
board =
A B C E
S F C S
A D E E

word = "ABCCED"
```

可以找到路径：

```text
A(0,0)
→ B(0,1)
→ C(0,2)
→ C(1,2)
→ E(2,2)
→ D(2,1)
```

每进入一个单元格就将其标记为已访问，避免搜索过程中绕回并重复使用同一个位置。

### 复杂度

设棋盘大小为 `m × n`，单词长度为 `L`：

- **时间复杂度**：最坏为 `O(m × n × 3^(L - 1))`。每个单元格都可能作为起点；第一步之后不能立即返回上一个单元格，因此每层最多继续搜索三个方向。宽松估计也可写为 `O(m × n × 4^L)`。
- **空间复杂度**：`O(m × n + L)`。二维访问数组占 `O(m × n)`，递归栈最深为 `O(L)`。

### 代码

- `leecode79.cpp`

## 131. Palindrome Partitioning

- **中文名称**：分割回文串
- **题目链接**：https://leetcode.com/problems/palindrome-partitioning/
- **核心思路**：DFS + 回溯。把字符串的每个位置视为新的分割起点，枚举从该位置开始的所有回文前缀，再递归处理剩余后缀。

### DFS 状态

递归函数：

```cpp
dfs(current_index, temp, s, answer)
```

表示：

> 下标 `[0, current_index - 1]` 的内容已经完成分割，`temp` 保存当前分割方案；接下来枚举从 `current_index` 开始的下一段回文子串。

例如：

```text
s = "aab"
current_index = 2
temp = ["aa"]
```

表示前两个字符已经被分成 `"aa"`，接下来只需要分割从下标 `2` 开始的 `"b"`。

### 枚举当前子串的结束位置

固定起点 `current_index` 后，枚举结束位置 `i`：

```cpp
for (int i = current_index;
     i < static_cast<int>(s.size());
     ++i)
```

当前候选子串是闭区间：

```text
s[current_index...i]
```

对应的 C++ 提取方式为：

```cpp
s.substr(current_index, i - current_index + 1)
```

`substr` 的第二个参数是长度，因此需要加 `1`。

只有候选子串是回文串时，才继续搜索：

```cpp
if (!isPalindrome(s, current_index, i)) {
    continue;
}
```

这是本题的核心剪枝，因为题目要求分割出的每一段都必须是回文串。

### 递归与回溯

找到回文子串后，执行：

```cpp
temp.push_back(
    s.substr(current_index, i - current_index + 1)
);
dfs(i + 1, temp, s, answer);
temp.pop_back();
```

三个步骤分别表示：

1. `push_back`：将当前回文子串加入分割方案；
2. `dfs(i + 1, ...)`：当前区间已经处理到 `i`，所以下一段从 `i + 1` 开始；
3. `pop_back`：撤销当前选择，继续尝试当前层的其他结束位置。

下一层必须传入 `i + 1`，而不是 `current_index + 1`。因为本次选择的是整个区间 `[current_index, i]`，这段区间都已经处理完毕。

### 终止条件

当起点到达字符串末尾之后：

```cpp
if (current_index == static_cast<int>(s.size())) {
    answer.push_back(temp);
    return;
}
```

说明整个字符串已经被若干个回文子串恰好覆盖，当前 `temp` 是一种完整分割方案。

终止条件是：

```cpp
current_index == s.size()
```

而不是：

```cpp
current_index == s.size() - 1
```

例如选择最后一个字符后，下一层收到的下标正好等于字符串长度。

### 回文判断

使用双指针检查闭区间 `[begin, end]`：

```cpp
bool isPalindrome(const string& s, int begin, int end) {
    while (begin < end) {
        if (s[begin] != s[end]) {
            return false;
        }

        ++begin;
        --end;
    }

    return true;
}
```

两端字符不同即可立即返回 `false`；否则指针向中间收缩。单字符和空心区间会自然判定为回文。

### `temp` 按值传递的特点

当前代码将路径参数声明为：

```cpp
vector<string> temp
```

因此每次调用 `dfs` 都会获得一份独立的路径副本。子递归对 `temp` 的修改不会影响父递归。

不过当前层循环中的不同迭代仍然共享当前函数内部的这一份 `temp`，所以递归返回后仍需执行：

```cpp
temp.pop_back();
```

否则本轮加入的子串会残留到同一层的下一个候选分支中。

例如在根节点先选择 `"a"` 后，如果不弹出它，再尝试 `"aa"` 时，路径会错误地变成：

```text
["a", "aa"]
```

而不是：

```text
["aa"]
```

更常见的写法是将 `temp` 按引用传递：

```cpp
vector<string>& temp
```

这样可以避免每层递归复制整个路径，但同样必须使用 `push_back` 和 `pop_back` 维护共享状态。当前按值版本逻辑正确，优点是子递归状态彼此隔离，代价是额外的路径复制。

### `"aab"` 搜索过程

```text
dfs(0), temp=[]
├─ 选择 "a"
│  └─ dfs(1), temp=["a"]
│     ├─ 选择 "a"
│     │  └─ dfs(2), temp=["a","a"]
│     │     └─ 选择 "b"
│     │        └─ dfs(3)，收集 ["a","a","b"]
│     └─ "ab" 不是回文，跳过
├─ 选择 "aa"
│  └─ dfs(2), temp=["aa"]
│     └─ 选择 "b"
│        └─ dfs(3)，收集 ["aa","b"]
└─ "aab" 不是回文，跳过
```

最终结果：

```text
[["a", "a", "b"], ["aa", "b"]]
```

### 为什么不需要访问数组

本题每次递归都会使下标严格向右移动：

```cpp
current_index = i + 1
```

搜索不可能回到已经处理过的字符，因此不存在环，也不会重复使用之前的字符，不需要像 LeetCode 79 单词搜索那样维护 `visited`。

### 复杂度

设字符串长度为 `n`：

- **时间复杂度**：最坏为 `O(n × 2^n)`。字符串的 `n - 1` 个间隙都有切或不切两种可能；检查回文、构造子串和复制完整方案均可能需要线性时间。
- **额外空间复杂度**：当前按值传递路径的实现最坏可占 `O(n²)`，递归链上的每一层都可能保留一份总长度为 `O(n)` 的路径副本；不计输出结果。若将路径改为引用传递，额外空间可降至 `O(n)` 量级。
- **输出空间**：最坏为 `O(n × 2^n)`。

### 代码

- `leecode131.cpp`
