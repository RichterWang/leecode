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
    vector<string> maxNumOfSubstrings(string s) {
        // 预处理：计算每个字符首次或者末次出现的位置
        int n = static_cast<int>(s.size());

        vector<int> first(26, -1), last(26, -1);
        for(int i = 0; i < n; i++)
        {
            int c = s[i] - 'a';
            if(first[c] == -1) first[c] = i;
            last[c] = i;
        }

        // 扩散：为每个字符计算有效区间
        vector<pair<int, int>> intervals;
        for(int i = 0; i < 26; i++)
        {
            if(first[i] == -1) continue;

            int l = first[i], r = last[i];

            for(int i = l; i <= r; i++)
            {
                int ch = s[i] - 'a';
                if(first[ch] < l || last[ch] > r)
                {
                    l = min(l, first[ch]);
                    r = max(r, last[ch]);
                    i = l;
                }
            }

            intervals.push_back({l, r});
        }

        sort(intervals.begin(), intervals.end());
        intervals.erase(unique(intervals.begin(), intervals.end()), intervals.end());

        sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b){
            if(a.second != b.second) return a.second < b.second;
            return (a.second - a.first) < (b.second - b.first);
        });

        vector<string> result;
        int lastEnd = -1;
        for(auto [l, r] : intervals)
        {
            if(l > lastEnd){
                result.push_back(s.substr(l, r - l + 1));
                lastEnd = r;
            }
        }

        return result;
    }

private:

};

/* 1520. 最多的不重叠子字符串
给你一个只包含小写字母的字符串 s ，你需要找到 s 中最多数目的非空子字符串，满足如下条件：
这些字符串之间互不重叠，也就是说对于任意两个子字符串 s[i..j] 和 s[x..y] ，要么 j < x 要么 i > y 。
如果一个子字符串包含字符 char ，那么 s 中所有 char 字符都应该在这个子字符串中。
请你找到满足上述条件的最多子字符串数目。如果有多个解法有相同的子字符串数目，请返回这些子字符串总长度最小的一个解。可以证明最小总长度解是唯一的。
请注意，你可以以 任意 顺序返回最优解的子字符串。
*/
