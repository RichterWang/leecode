#include <string>
#include <vector>

using namespace std;

/*
 * LeetCode 131. 分割回文串
 *
 * 使用 DFS 枚举从 current_index 开始的所有回文前缀。
 * temp 按值传递，每个递归分支持有独立的路径副本。
 */
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> answer;
        vector<string> temp;

        dfs(0, temp, s, answer);

        return answer;
    }

private:
    void dfs(int current_index,
             vector<string> temp,
             const string& s,
             vector<vector<string>>& answer) {
        if (current_index == static_cast<int>(s.size())) {
            answer.push_back(temp);
            return;
        }

        for (int i = current_index;
             i < static_cast<int>(s.size());
             ++i) {
            if (!isPalindrome(s, current_index, i)) {
                continue;
            }

            temp.push_back(
                s.substr(current_index, i - current_index + 1)
            );
            dfs(i + 1, temp, s, answer);
            temp.pop_back();
        }
    }

    bool isPalindrome(const string& s, int begin, int end) {
        while (begin < end) {
            if (s[begin] != s[end]) {
                return false;
            }

            ++begin;
            --end;
        }

        return true;
    }
};
