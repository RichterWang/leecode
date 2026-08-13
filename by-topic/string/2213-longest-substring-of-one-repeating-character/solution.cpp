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
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int m = s.size();
        int n = queryCharacters.size();
        vector<int> ans;

        for(int i = 0; i < n; i++)
        {
            s[queryIndices[i]] = queryCharacters[i];
            int left = 0, right = 1;
            int currentLen = 1, bestLen = 1;
            while(right < m)
            {
                if(s[right] == s[right - 1]){
                    currentLen++;
                    bestLen = max(currentLen, bestLen);
                }
                else{
                    while(s[left] != s[right]){
                        left = right;
                        currentLen = 1;
                    }
                }
                right++;
            }
            ans.push_back(bestLen);
        }
        return ans;
    }

private:

};