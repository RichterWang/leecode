// LeetCode 3302. Find the Lexicographically Smallest Valid Sequence
// Full dynamic programming table kept for comparison

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int length1 = static_cast<int>(word1.size());
        int length2 = static_cast<int>(word2.size());
        vector<vector<vector<bool>>> dp(
            length1 + 1,
            vector<vector<bool>>(length2 + 1, vector<bool>(2, false)));

        for (int i = 0; i <= length1; i++) {
            dp[i][length2][0] = true;
            dp[i][length2][1] = true;
        }
        for (int j = 0; j < length2; j++) {
            dp[length1][j][0] = false;
            dp[length1][j][1] = false;
        }

        for (int i = length1 - 1; i >= 0; i--) {
            for (int j = length2 - 1; j >= 0; j--) {
                for (int used = 0; used <= 1; used++) {
                    dp[i][j][used] = dp[i + 1][j][used];

                    if (word1[i] == word2[j]) {
                        dp[i][j][used] =
                            dp[i][j][used] || dp[i + 1][j + 1][used];
                    } else if (used == 0) {
                        dp[i][j][used] =
                            dp[i][j][used] || dp[i + 1][j + 1][1];
                    }
                }
            }
        }

        if (!dp[0][0][0]) return {};

        vector<int> answer;
        answer.reserve(length2);
        int next = 0;
        int used = 0;

        for (int j = 0; j < length2; j++) {
            for (int i = next; i < length1; i++) {
                int nextUsed = used;
                bool canChoose = false;

                if (word1[i] == word2[j]) {
                    canChoose = dp[i + 1][j + 1][nextUsed];
                } else if (used == 0) {
                    nextUsed = 1;
                    canChoose = dp[i + 1][j + 1][nextUsed];
                }

                if (canChoose) {
                    answer.push_back(i);
                    next = i + 1;
                    used = nextUsed;
                    break;
                }
            }

            if (answer.size() != static_cast<size_t>(j + 1)) return {};
        }

        return answer;
    }
};
