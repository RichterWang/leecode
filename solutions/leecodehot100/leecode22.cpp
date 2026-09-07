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
    vector<string> generateParenthesis(int n) {
        string temp;
        vector<string> answer;
        int current_num = n;
        int reference_num = 0;

        dfs(current_num, reference_num, temp, answer);

        return answer;
    }

private:
    void dfs(int current_num, int reference_num, string temp, vector<string>& answer)
    {
        if(current_num == 0 && reference_num == 0) {
            answer.push_back(temp);
            return;
        }
        else{
            if(current_num == 0 && reference_num != 0){
                for(int i = 0; i < reference_num; i++) temp.push_back(')');
                answer.push_back(temp);
                return;
            }
            else if(current_num != 0){
                temp.push_back('(');
                dfs(current_num - 1, reference_num + 1, temp, answer);
                temp.pop_back();
                if(reference_num != 0){
                    temp.push_back(')');
                    dfs(current_num, reference_num - 1, temp, answer);
                }
            }
        }
    }
};

/* leecode79 单词搜索 
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
*/
