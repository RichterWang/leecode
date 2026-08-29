# 3734. Lexicographically Smallest Palindromic Permutation

## 题目信息

- **难度**：Medium
- **分类**：String, Greedy, Palindrome, Permutation
- **链接**：https://leetcode.com/problems/lexicographically-smallest-palindromic-permutation/

## 题目描述

给你两个长度均为 n 的字符串 `s` 和目标字符串 `target`，它们都由小写英文字母组成。

返回 **字典序最小** 的字符串，该字符串 **既** 是 `s` 的一个 **回文排列**，**又** 是字典序 **严格大于** `target` 的。如果不存在这样的排列，则返回一个空字符串。

**定义**：
- 如果字符串 `a` 和字符串 `b` 长度相同，在它们首次出现不同的位置上，字符串 `a` 处的字母在字母表中的顺序晚于字符串 `b` 处的对应字母，则字符串 `a` 在 **字典序上严格大于** 字符串 `b`。
- **排列** 是指对字符串中所有字符的重新排列。
- 如果一个字符串从前向后读和从后向前读都一样，则该字符串是 **回文** 的。

## 解题思路

这道题是 **LeetCode 3720（下一个排列）** 和 **回文串构造** 的结合：
1. 需要找字典序最小且严格大于 target 的排列（3720）
2. 结果必须是回文串（回文约束）

### 核心洞察

回文串由**前半部分**唯一决定（后半部分是镜像），所以我们只需要：
1. **在前半部分应用"下一个排列"算法**
2. **后半部分自动镜像**
3. **中间字符固定**（奇数长度时）

### 关键难点：两种情况

回文串 P 严格大于 target，第一个不同字符的位置有两种可能：

#### 情况 A：差异在中间字符或后半段

- P 的前半部分 == target 的前半部分
- 候选唯一确定：前半段固定，中间字符固定，后半段镜像
- **必须优先检查**（字典序最小）

#### 情况 B：差异在前半段

- P 的前半部分 > target 的前半部分
- 应用 3720 算法：从右往左找最早能"超越"的位置

### 算法步骤

#### 步骤 1：检查回文可行性

```cpp
vector<int> cnt(26);
for(char c : s) cnt[c - 'a']++;

int oddCount = 0, oddChar = -1;
for(int i = 0; i < 26; i++) {
    if(cnt[i] % 2 == 1) {
        oddCount++;
        oddChar = i;
    }
}
if(oddCount > 1) return "";  // 超过1个奇数频次字符，无法构成回文
```

**回文串的必要条件**：
- 偶数长度：所有字符出现偶数次
- 奇数长度：最多1个字符出现奇数次（作为中间字符）

#### 步骤 2：构建前半部分的字符池

```cpp
int half = n / 2;
vector<int> halfCnt(26);
for(int i = 0; i < 26; i++) {
    halfCnt[i] = cnt[i] / 2;  // 每个字符的一半分配给前半部分
}

string targetHalf = target.substr(0, half);
```

#### 步骤 3：情况 A - 前半段完全相同

```cpp
vector<int> difference = halfCnt;
for(int i = 0; i < half; i++) {
    difference[targetHalf[i] - 'a']--;
}

// difference 总和恒为 0，所以 min >= 0 等价于全为 0
// 即 targetHalf 正好是前半段字符池的一个合法排列
if(*min_element(difference.begin(), difference.end()) >= 0) {
    string candidate = targetHalf;
    if(n % 2 == 1) candidate += ('a' + oddChar);  // 添加中间字符
    for(int k = half - 1; k >= 0; k--) {
        candidate += targetHalf[k];  // 镜像
    }
    if(candidate > target) return candidate;
}
```

**为什么先检查情况 A？**
- 情况 A 的前半段 == targetHalf
- 情况 B 的前半段 > targetHalf
- 所以情况 A 字典序必然更小

#### 步骤 4：情况 B - 从右往左找超越点

```cpp
for(int i = half - 1; i >= 0; i--) {
    int b = targetHalf[i] - 'a';
    difference[b]++;  // 撤销对 targetHalf[i] 的消耗
    
    // 检查前缀 [0, i-1] 能否用剩余字符完全匹配
    if(*min_element(difference.begin(), difference.end()) < 0) {
        continue;
    }
    
    // 在位置 i 放一个比 targetHalf[i] 大的最小字符
    for(int j = b + 1; j < 26; j++) {
        if(difference[j] > 0) {
            difference[j]--;
            targetHalf[i] = 'a' + j;
            targetHalf.resize(i + 1);
            
            // 后续放最小的字符
            string restHalf = getMinString(difference);
            string resultHalf = targetHalf + restHalf;
            
            // 构造完整回文
            string result = resultHalf;
            if(n % 2 == 1) result += ('a' + oddChar);
            for(int k = half - 1; k >= 0; k--) {
                result += resultHalf[k];
            }
            return result;
        }
    }
}

return "";  // 无解
```

### 算法示例

#### 示例 1：情况 A 的例子

```
输入: s = "aabb", target = "abab"

步骤 1: cnt = [2,2,0,...] → oddCount=0 ✓

步骤 2: half=2, halfCnt=[1,1,0,...], targetHalf="ab"

步骤 3: difference = [1,1] - [1,1] = [0,0]
        min=0 ✓
        candidate = "ab" + "" + "ba" = "abba"
        "abba" > "abab" ✓
        返回 "abba"
```

#### 示例 2：情况 B 的例子

```
输入: s = "aabb", target = "abba"

步骤 1-2: 同上

步骤 3: candidate = "abba"
        "abba" > "abba" ✗（不严格大于）
        继续到情况 B

步骤 4: 
i=1: difference['b']++ = [0,1]
     min=0 ✓
     找 j>'b': 无
     
i=0: difference['a']++ = [1,1]
     min=1 ✓
     找 j>'a': j=1('b'), difference[1]=1 ✓
     targetHalf[0]='b', resize→"b"
     restHalf = getMinString([1,0,...]) = "a"
     resultHalf = "ba"
     result = "ba" + "" + "ab" = "baab"
     返回 "baab"
```

#### 示例 3：边界情况（n=1）

```
输入: s = "b", target = "a"

步骤 1: cnt = [0,1,0,...] → oddCount=1, oddChar=1 ✓

步骤 2: half=0, targetHalf=""

步骤 3: difference = [0,0,...]
        min=0 ✓
        candidate = "" + "b" + "" = "b"
        "b" > "a" ✓
        返回 "b"
```

### 时间复杂度分析

- **统计字符**：O(n)
- **检查回文性**：O(26) = O(1)
- **情况 A**：O(n/2 + 26) = O(n)
- **情况 B**：O(n/2 × 26) = O(n)
- **总复杂度**：O(n)

### 空间复杂度

- `cnt`, `halfCnt`, `difference`：O(26) = O(1)
- **总复杂度**：O(1)（不计返回值）

## 复杂度

- **时间复杂度**：O(n)
- **空间复杂度**：O(1)

## 关键要点

1. **回文降维**：只需处理前半部分，后半部分由镜像决定
2. **两种情况**：差异在前半段（B）vs 差异不在前半段（A）
3. **优先级**：A 的字典序 < B 的字典序，必须先检查 A
4. **情况 A 判据**：`min(difference) >= 0` 等价于 targetHalf 可由 halfCnt 构成
5. **复用 3720**：情况 B 就是在前半部分应用"下一个排列"算法
6. **边界处理**：n=1 时 half=0，情况 A 直接返回中间字符

## 易错点

### 错误 1：只实现情况 B

```cpp
// 错误：直接从右往左找
for(int i = half - 1; i >= 0; i--) { ... }
```

**反例**：`s="aabb", target="abab"` 应返回 `"abba"` 但返回 `"baab"`

**原因**：情况 A 的 `"abba"` 字典序更小，必须优先检查

### 错误 2：情况 A 不检查 candidate > target

```cpp
// 错误：直接返回 candidate
if(min >= 0) return candidate;
```

**反例**：`s="aba", target="aba"` 应返回 `""` 但返回 `"aba"`

**原因**：candidate 可能等于 target，不满足"严格大于"

### 错误 3：忘记处理 n=1

**反例**：`s="b", target="a"` 应返回 `"b"` 但返回 `""`

**原因**：half=0 时循环不执行，情况 A 补上了这个空洞

## 相关题目

- [3720. Lexicographically Greater Permutation](https://leetcode.com/problems/lexicographically-greater-permutation/) - 本题的前置题（无回文约束）
- [31. Next Permutation](https://leetcode.com/problems/next-permutation/) - 经典下一个排列
- [266. Palindrome Permutation](https://leetcode.com/problems/palindrome-permutation/) - 判断能否构成回文
- [267. Palindrome Permutation II](https://leetcode.com/problems/palindrome-permutation-ii/) - 生成所有回文排列
