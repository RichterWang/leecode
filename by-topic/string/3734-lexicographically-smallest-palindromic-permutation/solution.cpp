#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = static_cast<int>(s.size());
        vector<int> cnt(26);

        for(char c : s) cnt[c - 'a']++;

        int oddCount = 0, oddChar = -1;

        for(int i = 0; i < 26; i++)
        {
            if(cnt[i] % 2 == 1)
            {
                oddCount++;
                oddChar = i;
            }
        }
        if(oddCount > 1) return "";

        int half = n / 2;
        vector<int> halfCnt(26);
        for(int i = 0; i < 26; i++) halfCnt[i] = cnt[i]/2;

        string targetHalf = target.substr(0, half);
        
        vector<int> difference = halfCnt;
        // 找到前半段差的数量
        for(int i = 0; i < half; i++) difference[targetHalf[i] - 'a']--;

        // 情况 A：前半段与 targetHalf 完全一致，差异落在中间字符或后半段
        if(*min_element(difference.begin(), difference.end()) >= 0)
        {
            string candidate = targetHalf;
            if(n % 2 == 1) candidate += static_cast<char>('a' + oddChar);
            for(int k = half - 1; k >= 0; k--) candidate += targetHalf[k];
            if(candidate > target) return candidate;
        }

        // 情况 B：从右往左找第一个能放更大字符的位置
        for(int i = half - 1; i >= 0; i--)
        {
            int b = targetHalf[i] - 'a';
            difference[b]++;
            
            if(*min_element(difference.begin(), difference.end()) < 0) continue;

            for(int j = b + 1; j < 26; j++)
            {
                if(difference[j] > 0)
                {
                    difference[j]--;
                    targetHalf[i] = 'a' + j;
                    targetHalf.resize(i + 1);

                    string restHalf = getMinString(difference);
                    string resultHalf = targetHalf + restHalf;

                    // 构造完整的回文子串
                    string result = resultHalf;
                    if(n % 2 == 1) result += ('a' + oddChar);
                    for(int k = half - 1; k >= 0; k--) result += resultHalf[k];
                    return result;
                }
            }
        }

        return "";
    }

private:
    string getMinString(const vector<int>& array)
    {
        string result;
        for(int i = 0; i < 26; i++) result.append(array[i], 'a' + i);
        return result;
    }
};
