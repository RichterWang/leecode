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
 * LeetCode 74. 搜索二维矩阵
 * 
 * 给你一个满足下述两条属性的 m x n 整数矩阵：
 * - 每行中的整数从左到右按非严格递增顺序排列。
 * - 每行的第一个整数大于前一行的最后一个整数。
 * 给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。
 * 你必须编写一个时间复杂度为 O(log(m * n)) 的解决方案。
 */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row = static_cast<int>(matrix.size());
        if(row == 0) return false; 
        int col = static_cast<int>(matrix[0].size());
        if(col == 0) return false;

        int up = 0, low = row;
        int targetRow = -1;
        while(up != low)
        {
            int mid = (up + low) / 2;
            if(matrix[mid][0] == target) return true;
            if(matrix[mid][0] < target) {
                targetRow = mid;
                up = mid + 1;
            }
            else low = mid;
        }
        if(targetRow == -1) return false;

        int left = 0, right = col;
        while(left != right)
        {
            int current = (left + right) / 2;
            if(matrix[targetRow][current] == target) return true;
            matrix[targetRow][current] > target ? right = current : left = current + 1;
        }
        return false;
    }
private:

};
