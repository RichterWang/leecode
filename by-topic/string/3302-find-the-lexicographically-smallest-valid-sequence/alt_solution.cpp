// LeetCode 3302. Find the Lexicographically Smallest Valid Sequence
// Greedy reconstruction with a direct suffix feasibility check

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        bool used = false;
        int last = 0;
        vector<int> answer;

        for (int i = 0; i < static_cast<int>(word2.size()); i++) {
            bool found = false;

            for (int j = last; j < static_cast<int>(word1.size()); j++) {
                if (word1[j] == word2[i] &&
                    isValidSuffix(i + 1, j + 1, word1, word2)) {
                    answer.push_back(j);
                    last = j + 1;
                    found = true;
                    break;
                }

                if (!used &&
                    isValidSuffix(i + 1, j + 1, word1, word2)) {
                    answer.push_back(j);
                    used = true;
                    last = j + 1;
                    found = true;
                    break;
                }
            }

            if (!found) return {};
        }

        return answer;
    }

private:
    static bool isValidSuffix(
        int word2Index,
        int word1Index,
        const string& word1,
        const string& word2) {
        while (word2Index < static_cast<int>(word2.size()) &&
               word1Index < static_cast<int>(word1.size())) {
            if (word1[word1Index] == word2[word2Index]) {
                word2Index++;
            }
            word1Index++;
        }

        return word2Index == static_cast<int>(word2.size());
    }
};
