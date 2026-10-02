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
#include <set>

using namespace std;

/*
 * LeetCode 394: 字符串解码 (Decode String)
 * 
 * 核心思路：双栈法
 * - countStack: 存储重复次数
 * - stringStack: 存储待拼接的字符串
 * 
 * 遇到 '[': 保存当前状态，开始新的一层
 * 遇到 ']': 弹出状态，重复并拼接
 * 遇到数字: 累积成完整数字（处理多位数）
 * 遇到字母: 直接追加到当前字符串
 */
class Solution {
public:
    string decodeString(string s) {
        stack<int> countStack;       // 存储重复次数
        stack<string> stringStack;   // 存储待拼接的字符串
        
        string currentString = "";   // 当前正在构建的字符串
        int currentNum = 0;          // 当前正在累积的数字
        
        for (char ch : s) {
            if (isdigit(ch)) {
                // 累积数字（处理多位数）
                currentNum = currentNum * 10 + (ch - '0');
            }
            else if (ch == '[') {
                // 遇到左括号：保存当前状态，开始新的一层
                countStack.push(currentNum);
                stringStack.push(currentString);
                
                // 重置当前状态
                currentNum = 0;
                currentString = "";
            }
            else if (ch == ']') {
                // 遇到右括号：弹出状态，重复并拼接
                int repeatCount = countStack.top();
                countStack.pop();
                
                string prevString = stringStack.top();
                stringStack.pop();
                
                // 将当前字符串重复 repeatCount 次
                string temp = "";
                for (int i = 0; i < repeatCount; i++) {
                    temp += currentString;
                }
                
                // 拼接到之前的字符串后
                currentString = prevString + temp;
            }
            else {
                // 普通字母：直接追加
                currentString += ch;
            }
        }
        
        return currentString;
    }
};

/*
示例推演：s = "3[a2[c]]"

字符  | currentNum | currentString | countStack | stringStack
-----|-----------|---------------|-----------|-------------
初始  | 0         | ""            | []        | []
'3'  | 3         | ""            | []        | []
'['  | 0         | ""            | [3]       | [""]
'a'  | 0         | "a"           | [3]       | [""]
'2'  | 2         | "a"           | [3]       | [""]
'['  | 0         | ""            | [3,2]     | ["","a"]
'c'  | 0         | "c"           | [3,2]     | ["","a"]
']'  | 0         | "acc"         | [3]       | [""]        ← 2*"c"+"a"
']'  | 0         | "accaccacc"   | []        | []          ← 3*"acc"

输出："accaccacc"
*/
