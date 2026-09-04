#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/*
 * 17. Letter Combinations of a Phone Number
 *
 * 回溯：递归深度 = digits.size()，每层枚举当前数字对应的字母。
 * 层数由输入决定，写不出固定层数的嵌套循环，所以用递归模拟。
 *
 * temp 被所有分支共享，递归返回后必须 pop_back() 还原，
 * 否则下一个分支会接在错误的前缀后面。
 */
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};

        unordered_map<char, string> reference{
            {'2', "abc"},
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"}
        };

        vector<string> answer;
        string temp;
        int n = static_cast<int>(digits.size());

        // idx 表示当前要处理 digits 的第几位
        function<void(int)> backtrack = [&](int idx) {
            if (idx == n) {                     // 凑满 n 个字母，收集一个答案
                answer.push_back(temp);
                return;
            }
            const string& letters = reference[digits[idx]];
            for (char c : letters) {            // 这一层的循环：枚举当前位的所有字母
                temp.push_back(c);              // 做选择
                backtrack(idx + 1);             // 递归处理下一位
                temp.pop_back();                // 撤销选择
            }
        };

        backtrack(0);
        return answer;
    }

private:

};
