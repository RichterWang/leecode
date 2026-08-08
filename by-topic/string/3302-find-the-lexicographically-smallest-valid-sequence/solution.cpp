// LeetCode 3302. Find the Lexicographically Smallest Valid Sequence
// Compressed suffix feasibility + greedy reconstruction

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int length1 = static_cast<int>(word1.size());
        int length2 = static_cast<int>(word2.size());

        // suffixStart[j] is the largest possible starting index in word1
        // from which word2[j:] can be matched exactly as a subsequence.
        vector<int> suffixStart(length2 + 1, -1);
        suffixStart[length2] = length1;

        int word1Index = length1 - 1;
        for (int j = length2 - 1; j >= 0; j--) {
            while (word1Index >= 0 && word1[word1Index] != word2[j]) {
                word1Index--;
            }
            if (word1Index < 0) break;

            suffixStart[j] = word1Index;
            word1Index--;
        }

        vector<int> answer;
        answer.reserve(length2);

        int next = 0;
        bool used = false;
        for (int j = 0; j < length2; j++) {
            bool found = false;

            for (int i = next; i < length1; i++) {
                bool canChoose = false;

                if (word1[i] == word2[j]) {
                    canChoose = true;
                } else if (!used) {
                    // Use the one allowed replacement at this position.
                    canChoose = suffixStart[j + 1] != -1 &&
                                i + 1 <= suffixStart[j + 1];
                }

                if (canChoose) {
                    answer.push_back(i);
                    next = i + 1;
                    if (word1[i] != word2[j]) used = true;
                    found = true;
                    break;
                }
            }

            if (!found) return {};
        }

        return answer;
    }
};
