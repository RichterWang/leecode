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
 * LeetCode 3498. 字符串的反转度
 * 
 * 题目：计算字符串的反转度
 * - 对于每个字符，将其在反转字母表中的位置（'a' = 26, 'b' = 25, ..., 'z' = 1）
 *   与其在字符串中的位置（下标从 1 开始）相乘
 * - 将这些乘积加起来，得到字符串中所有字符的和
 * - 返回反转度
 */
class Solution {
public:
    int reverseDegree(string s) {
        int n = static_cast<int>(s.size());
        if(n == 0) return 0;

        int answer = 0;
        
        for(int i = 0; i < n; i++) answer += (26 - s[i] + 'a') * (i + 1);

        return answer;
    }
private:

};
