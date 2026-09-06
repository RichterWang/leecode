// 115. 不同的子序列 —— 暴力版（位掩码枚举）
//
// 思路：s 的每个字符「选 / 不选」，共 2^m 种方案，用 m 位二进制数 mask 表示。
//       mask 的第 i 位为 1 表示取 s[i]，按 i 递增拼接可保证保序（即子序列）。
//       生成后与 t 比较，相等则计数。
//
// 注意：不去重。同一个字符串可能来自不同的下标组合（如 "bbb" 中的 "bb" 有 3 种），
//       题目数的正是下标集合的个数。
//
// 复杂度：时间 O(2^m * m)，空间 O(m)
//
// 局限：仅在 m <= 20 时可用。
//   1) m >= 31 时 `1 << m` 溢出 int，是未定义行为（UBSan 会直接报错）
//   2) 即使换成 1LL << m，2^m 的循环次数也不可能跑完
//   本题约束 s.length <= 1000，故此版本无法通过，只能作为对拍基准。
//   正解见 solution.cpp。

#include <string>

using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = static_cast<int>(s.size());

        // 位掩码枚举的可行边界：2^20 约 100 万，可瞬间跑完；
        // m >= 31 会导致 1 << m 未定义行为。
        if (m > 20) return -1;  // 超出适用范围

        int answer = 0;

        for (int mask = 0; mask < (1 << m); mask++) {
            string temp;
            // i 递增遍历，保证 temp 中字符按原下标顺序排列（子序列必须保序）
            for (int i = 0; i < m; i++) {
                if (mask & (1 << i)) temp.push_back(s[i]);
            }
            if (temp == t) answer++;
        }

        return answer;
    }
};
