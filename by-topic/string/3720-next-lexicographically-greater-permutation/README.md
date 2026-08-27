# 3720. Lexicographically Greater Permutation

## 题目信息

- **难度**：Medium
- **分类**：String, Greedy, Permutation
- **链接**：https://leetcode.com/problems/lexicographically-greater-permutation/

## 题目描述

给你两个长度均为 n 且仅由小写英文字母组成的字符串 `s` 和 `target`。

返回 `s` 的**字典序最小的排列**，要求该排列**严格大于** `target`。如果 `s` 不存在任何字典序严格大于 `target` 的排列，则返回一个空字符串。

**定义**：
- 如果两个长度相同的字符串 `a` 和 `b` 在它们首次出现不同字符的位置上，字符串 `a` 对应的字母在字母表中出现在 `b` 对应字母的**后面**，则字符串 `a` 字典序严格大于字符串 `b`。
- **排列**是字符串中所有字符的一种重新排列。

## 解题思路

这道题是经典的**下一个排列（Next Permutation）** 问题的变体，需要找到**刚好大于 target** 且**字典序最小**的 s 的排列。

### 核心思想

从右往左回溯，找到**最早能"超越"target 的位置**，然后在该位置放一个比 target[i] 大的最小字符，后续位置放剩余字符的最小排列。

### 算法步骤

#### 步骤 1：统计字符差异

使用差值数组 `cnt[26]` 统计 s 和 target 的字符频次差异：
- `cnt[c] = s 中字符 c 的数量 - target 中字符 c 的数量`
- 初始状态表示"假设完全匹配 target，s 和 target 的字符库存差异"

```cpp
vector<int> cnt(26);
for (int i = 0; i < s.size(); i++) {
    cnt[s[i] - 'a']++;       // s 的字符 +1
    cnt[target[i] - 'a']--;  // target 的字符 -1
}
```

#### 步骤 2：从右往左尝试超越

从右往左遍历 target，逐步"释放"字符（撤销对 target 后缀的消耗），寻找最早能超越的位置：

```cpp
for (int i = s.size() - 1; i >= 0; i--) {
    int b = target[i] - 'a';
    cnt[b]++;  // 撤销对 target[i] 的消耗
    
    // 检查前缀 [0, i-1] 能否用 s 的字符完全匹配
    if (*min_element(cnt.begin(), cnt.end()) < 0) {
        continue;  // 前缀无法匹配，跳过
    }
    
    // 在位置 i 放一个比 target[i] 大的最小字符
    for (int j = b + 1; j < 26; j++) {
        if (cnt[j]) {
            cnt[j]--;
            target[i] = 'a' + j;
            target.resize(i + 1);  // 截断到位置 i
            return target + getMinString(cnt);  // 后续放最小的
        }
    }
}
```

**关键点**：
- **撤销消耗**：`cnt[b]++` 表示不再尝试匹配 target[i]，该字符重新可用
- **检查前缀**：`*min_element(cnt) >= 0` 确保前缀 [0, i-1] 可以用 s 的字符完全匹配
- **找更大字符**：从 `b+1` 开始找第一个可用字符（保证字典序最小）
- **后续最小化**：剩余字符按升序排列

#### 步骤 3：构造最小字典序后缀

```cpp
string getMinString(const vector<int>& cnt) {
    string res;
    for (int i = 0; i < 26; i++) {
        res.append(cnt[i], 'a' + i);  // 按字母顺序添加
    }
    return res;
}
```

### 算法示例

```
输入: s = "abcd", target = "bdac"

步骤 1: 统计差异
cnt = [0, 0, 0, 0, ...] (字符组成相同)

步骤 2: 从右往左尝试

i=3 (最右):
  cnt['c']++ → cnt = [0, 0, 1, 0, ...]
  min(cnt) = 0 ✓
  找 j > 'c': 没有更大的可用字符
  继续

i=2:
  cnt['a']++ → cnt = [1, 0, 1, 0, ...]
  min(cnt) = 0 ✓
  找 j > 'a': 
    'b': cnt[1]=0 ✗
    'c': cnt[2]=1 ✓
  
  在位置 2 放 'c':
    target = "bd" + "c" = "bdc"
    剩余: cnt = [1, 0, 0, 0, ...] → "a"
    返回: "bdc" + "a" = "bdca"

结果: "bdca" > "bdac" ✓
```

### 时间复杂度分析

- **统计字符**：O(n)
- **从右往左遍历**：O(n)
  - 每次 `min_element`：O(26) = O(1)
  - 查找更大字符：O(26) = O(1)
- **构造后缀**：O(26) = O(1)
- **总复杂度**：O(n)

### 空间复杂度

- `cnt` 数组：O(26) = O(1)
- **总复杂度**：O(1)（不计返回值）

## 复杂度

- **时间复杂度**：O(n)，其中 n 是字符串长度
- **空间复杂度**：O(1)

## 关键要点

1. **差值数组妙用**：用 `cnt` 追踪字符"库存"差异，高效判断可行性
2. **从右往左回溯**：贪心策略，找最早能超越的位置
3. **撤销消耗**：`cnt[b]++` 表示不再匹配该位置，字符重新可用
4. **前缀检查**：`min(cnt) >= 0` 确保前缀可以完全匹配
5. **后缀最小化**：剩余字符按字典序升序排列，保证整体最小

## 相关题目

- [31. Next Permutation](https://leetcode.com/problems/next-permutation/)
- [556. Next Greater Element III](https://leetcode.com/problems/next-greater-element-iii/)
- [3302. Find the Lexicographically Smallest Valid Sequence](https://leetcode.com/problems/find-the-lexicographically-smallest-valid-sequence/)
