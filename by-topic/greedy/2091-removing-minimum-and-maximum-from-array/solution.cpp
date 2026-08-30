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
#include <numeric>
#include <functional>

using namespace std;

/*
 * 2091. 从数组中移除最大值和最小值
 *
 * 思路：定位 min / max 下标后，枚举四种删除方案取最小
 */
class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());
        int left = 0, right = n - 1;
        int smallest = sorted[0];
        int biggest = sorted[n - 1];
        if(smallest == biggest) return n; // 说明所有的int都一样，直接全部弹出

        pair<int, int> smallest_index, biggest_index;

        bool is_padded_smallest = false;
        bool is_padded_biggest = false;
        int i = 0;
        while(i < n)
        {
            if(nums[i] == smallest) {
                smallest_index.first = i;
                is_padded_smallest = true;
            }
            else if(nums[i] == biggest){
                biggest_index.first = i;
                is_padded_biggest = true;
            }
            if(is_padded_smallest && is_padded_biggest) break;
            i++;
        }
        is_padded_biggest = false;
        is_padded_smallest = false;
        i = n - 1;
        while(i >= 0)
        {
            if(nums[i] == smallest) {
                smallest_index.second = i;
                is_padded_smallest = true;
            }
            else if(nums[i] == biggest){
                biggest_index.second = i;
                is_padded_biggest = true;
            }
            if(is_padded_smallest && is_padded_biggest) break;
            i--;
        }

        vector<int> step(4);
        step[0] = smallest_index.first > biggest_index.first ? smallest_index.first + 1 : biggest_index.first + 1;
        step[1] = smallest_index.second > biggest_index.second ? n - biggest_index.second : n - smallest_index.second;
        step[2] = smallest_index.first + 1 + n - biggest_index.second;
        step[3] = biggest_index.first + 1 + n - smallest_index.second;

        sort(step.begin(), step.end());
        return step[0];
    }

private:

};
