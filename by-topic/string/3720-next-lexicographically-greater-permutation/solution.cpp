#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        vector<int> cnt(26);
        // 统计 s 和 target 的字符差异
        for (int i = 0; i < s.size(); i++) {
            cnt[s[i] - 'a']++;       // s 中的字符 +1
            cnt[target[i] - 'a']--;  // target 中的字符 -1
        }

        // 从右往左尝试找到最早能"超越"的位置
        for (int i = s.size() - 1; i >= 0; i--) {
            int b = target[i] - 'a';
            cnt[b]++;  // 撤销对 target[i] 的消耗
            
            // 检查前缀 [0, i-1] 能否用 s 的字符完全匹配
            if (*min_element(cnt.begin(), cnt.end()) < 0) {
                continue;  // 前缀无法匹配，继续尝试下一个位置
            }
            
            // 在位置 i 放一个比 target[i] 大的最小字符
            for (int j = b + 1; j < 26; j++) {
                if (cnt[j]) {  // 找到可用字符
                    cnt[j]--;
                    target[i] = 'a' + j;
                    target.resize(i + 1);  // 截断到位置 i
                    return target + getMinString(cnt);  // 后续放最小的字符
                }
            }
        }

        return "";  // 无解
    }

private:
    // 获取最小字典序字符串（将 cnt 中的字符按升序排列）
    string getMinString(const vector<int>& cnt) {
        string res;
        for (int i = 0; i < 26; i++) {
            res.append(cnt[i], 'a' + i);  // 添加 cnt[i] 个字符 'a'+i
        }
        return res;
    }
};
