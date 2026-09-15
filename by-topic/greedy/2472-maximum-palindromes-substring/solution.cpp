#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <cmath>
#include <numeric>
#include <functional>
#include <array>

using namespace std;

/*
 * Daily question draft
 *
 * 使用方式：
 * 1. 先根据题目改函数名、参数列表和返回值类型
 * 2. 在 Solution 中补核心算法
 * 3. 提交到 LeetCode 时，通常只需要复制 Solution 类
 */
class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();
        int count = 0;
        int i = 0;
        
        while (i < n) {
            if (i + k <= n && isPalindrome(s, i, i + k - 1)) {
                count++;
                i += k;
            }
            else if (i + k + 1 <= n && isPalindrome(s, i, i + k)) {
                count++;
                i += k + 1;
            }
            else {
                i++;
            }
        }
        
        return count;
    }

private:
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }
};

/* leecode2472 不重叠回文子字符串的最大数目
给你一个字符串 s 和一个 正 整数 k 。
从字符串 s 中选出一组满足下述条件且 不重叠 的子字符串：
每个子字符串的长度 至少 为 k 。
每个子字符串是一个 回文串 。
返回最优方案中能选择的子字符串的 最大 数目。
子字符串 是字符串中一个连续的字符序列。
*/
