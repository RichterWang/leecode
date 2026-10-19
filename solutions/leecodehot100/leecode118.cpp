#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
 * LeetCode 118 - Pascal's Triangle
 * 杨辉三角
 * 
 * 难度：Easy
 * 标签：Array, Dynamic Programming
 */
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> answer;

        for(int i = 0; i < numRows; i++)
        {
            vector<int> row(i + 1, 1);

            for(int j = 1; j < i; j++) row[j] = answer[i - 1][j - 1] + answer[i - 1][j];

            answer.push_back(row);
        }

        return answer;
    }
};

int main() {
    Solution solution;

    int numRows;
    cin >> numRows;

    vector<vector<int>> result = solution.generate(numRows);

    // 输出格式：[[1],[1,1],[1,2,1],...]
    int result_size = static_cast<int>(result.size());
    cout << "[";
    for(int i = 0; i < result_size; i++)
    {
        cout << "[";
        for(int j = 0; j < static_cast<int>(result[i].size()); j++){
            cout << result[i][j];
            if(j < static_cast<int>(result[i].size()) - 1) cout << ",";
        }
        cout << "]";
        if(i < result_size - 1) cout << ","; 
    }
    cout << "]" << endl;

    return 0;
}
