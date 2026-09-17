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
#include <array>

using namespace std;

class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = static_cast<int>(arr.size());

        vector<int> prefixmin(n, INT_MAX);

        int left = 0, right = 0;
        int temp = 0;
        int result = INT_MAX;
        int current = INT_MAX;

        while(right < n)
        {
            temp += arr[right];
            if(temp > target){
                while(temp > target && left < right){
                    temp -= arr[left];
                    left++;
                }
            }
            if(temp == target) {
                if(left > 0 && prefixmin[left - 1] != INT_MAX) result = min(result, right - left + 1 + prefixmin[left - 1]);
                current = min(current, right - left + 1);
            }
            prefixmin[right] = current;
            if(right > 0) prefixmin[right] = min(prefixmin[right], prefixmin[right - 1]);

            right++;
        }

        return result == INT_MAX ? -1 : result;
    }
};
