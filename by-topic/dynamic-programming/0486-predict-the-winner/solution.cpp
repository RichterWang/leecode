// LeetCode 486. Predict the Winner

#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        memory = vector<vector<int>>(n, vector<int>(n, INT_MIN));
        return score(nums, 0, n - 1) >= 0;
    }

private:
    vector<vector<int>> memory;

    int score(vector<int>& nums, int left, int right) {
        if (left > right) return 0;
        if (memory[left][right] != INT_MIN) return memory[left][right];

        int chooseLeft = nums[left] - score(nums, left + 1, right);
        int chooseRight = nums[right] - score(nums, left, right - 1);

        memory[left][right] = max(chooseLeft, chooseRight);
        return memory[left][right];
    }
};

class SolutionDP {
public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            dp[i][i] = nums[i];
        }

        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                int pickLeft = nums[i] - dp[i + 1][j];
                int pickRight = nums[j] - dp[i][j - 1];
                dp[i][j] = max(pickLeft, pickRight);
            }
        }

        return dp[0][n - 1] >= 0;
    }
};
