// LeetCode 3014. Minimum Number of Pushes to Type Word I

#include <string>

using namespace std;

class Solution {
public:
    int minimumPushes(string word) {
        int n = word.size();
        int answer = 0;
        for (int i = 0; i < n; i++) {
            answer += i / 8 + 1;
        }
        return answer;
    }
};
