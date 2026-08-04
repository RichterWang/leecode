// 字符串匹配三种方法：暴力匹配、双指针、KMP
// 统一接口：在主串 text 中查找模式串 pattern 第一次出现的位置
// 找到返回起始下标，找不到返回 -1

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int bruteForceMatch(const string& text, const string& pattern) {
    int n = static_cast<int>(text.size());
    int m = static_cast<int>(pattern.size());

    if (m == 0) return 0;
    if (m > n) return -1;

    for (int i = 0; i <= n - m; ++i) {
        int j = 0;
        while (j < m && text[i + j] == pattern[j]) {
            ++j;
        }
        if (j == m) {
            return i;
        }
    }

    return -1;
}

int twoPointerMatch(const string& text, const string& pattern) {
    int n = static_cast<int>(text.size());
    int m = static_cast<int>(pattern.size());

    if (m == 0) return 0;
    if (m > n) return -1;

    int i = 0;
    int j = 0;

    while (i < n && j < m) {
        if (text[i] == pattern[j]) {
            ++i;
            ++j;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }

    if (j == m) {
        return i - m;
    }

    return -1;
}

vector<int> buildLPS(const string& pattern) {
    int m = static_cast<int>(pattern.size());
    vector<int> lps(m, 0);

    int len = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            ++len;
            lps[i] = len;
            ++i;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                ++i;
            }
        }
    }

    return lps;
}

int kmpMatch(const string& text, const string& pattern) {
    int n = static_cast<int>(text.size());
    int m = static_cast<int>(pattern.size());

    if (m == 0) return 0;
    if (m > n) return -1;

    vector<int> lps = buildLPS(pattern);
    int i = 0;
    int j = 0;

    while (i < n) {
        if (text[i] == pattern[j]) {
            ++i;
            ++j;
        }

        if (j == m) {
            return i - j;
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                ++i;
            }
        }
    }

    return -1;
}
