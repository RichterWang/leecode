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
 * Search a 2D Matrix II
 *
 * 从右上角开始搜索：
 * - 当前值大于 target，向左移动
 * - 当前值小于 target，向下移动
 * 利用行列递增的性质，每一步都能排除一整行或一整列。
 */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty() || matrix[0].empty()) return false;

        int m = matrix.size();
        int n = matrix[0].size();

        int i = 0, j = n - 1;
        while(i < m && j >= 0)
        {
            if(matrix[i][j] == target) return true;
            if(matrix[i][j] < target) i++;
            else j--;
        }
        return false;
    }

private:

};
