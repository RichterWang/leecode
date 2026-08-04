// LeetCode 3016. Minimum Number of Pushes to Type Word II

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int minimumPushes(string word) {
        unordered_map<char, int> charCount;
        for (char c : word) {
            charCount[c]++;
        }

        vector<int> counts;
        for (const auto& entry : charCount) {
            counts.push_back(entry.second);
        }

        sort(counts.begin(), counts.end(), greater<int>());

        int answer = 0;
        for (int i = 0; i < (int)counts.size(); i++) {
            answer += (i / 8 + 1) * counts[i];
        }
        return answer;
    }

    int minimumPushesCompact(string word) {
        vector<int> counts(26, 0);
        for (char c : word) {
            counts[c - 'a']++;
        }

        sort(counts.begin(), counts.end(), greater<int>());

        int answer = 0;
        for (int i = 0; i < 26 && counts[i] > 0; i++) {
            answer += counts[i] * (i / 8 + 1);
        }
        return answer;
    }
};
