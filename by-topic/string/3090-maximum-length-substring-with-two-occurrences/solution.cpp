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
 * Sliding window solution for LeetCode 3090
 *
 * 维护一个窗口，使得窗口内每个字符最多出现两次。
 * 当右端字符加入后导致次数超过 2 时，移动左指针缩小窗口，
 * 直到当前窗口重新满足条件。
 */
class Solution {
public:
    int maximumLengthSubstring(string s) {
        int n = s.size();
        if(n == 0) return 0;
        if(n == 1) return 1;
        int ans = 2;
        unordered_map<char, int> reference;

        int left = 0, right = 1;
        reference[s[left]] ++;
        
        while(right < n)
        {
            if(reference[s[right]] < 2) {
                reference[s[right]] ++;
                ans = max(ans, right - left + 1);
            }
            else{
                reference[s[right]] ++;
                while(reference[s[right]] > 2){
                    reference[s[left]] --;
                    left ++;
                }
            }
            right++;
        }

        return ans;
    }

private:

};
