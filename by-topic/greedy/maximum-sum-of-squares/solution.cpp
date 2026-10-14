#include <algorithm>
#include <string>

using namespace std;

class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if(sum < 1 || sum > num * 9) return "";

        string result;
        int remain_sum = sum;

        for(int i = 0; i < num; i++)
        {
            int remain_positions = num - i - 1;

            int min_digit = max(0, remain_sum - 9 * remain_positions);
            if(i == 0) min_digit = max(1, min_digit);

            int max_digit = min(9, remain_sum);

            if(min_digit > max_digit) return "";

            result += char('0' + max_digit);
            remain_sum -= max_digit;
        }

        return result;
    }
};
