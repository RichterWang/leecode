// LeetCode 76. Minimum Window Substring
// 滑动窗口：右指针扩张窗口，左指针在满足覆盖条件后尽量收缩窗口

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        int m = s.size(), n = t.size();
        if (m < n) return "";

        unordered_map<char, int> reference, window;
        for (char c : t) {
            reference[c]++;
        }

        int required = static_cast<int>(reference.size());
        int formed = 0;
        int left = 0;
        int bestStart = 0;
        int bestLen = m + 1;

        for (int right = 0; right < m; right++) {
            if (reference.count(s[right])) {
                window[s[right]]++;
                if (window[s[right]] == reference[s[right]]) {
                    formed++;
                }
            }

            while (formed == required && left <= right) {
                int currentLen = right - left + 1;
                if (currentLen < bestLen) {
                    bestLen = currentLen;
                    bestStart = left;
                }

                if (reference.count(s[left])) {
                    if (window[s[left]] == reference[s[left]]) {
                        formed--;
                    }
                    window[s[left]]--;
                }
                left++;
            }
        }

        if (bestLen == m + 1) return "";
        return s.substr(bestStart, bestLen);
    }
};
