// LeetCode 3348. Smallest Divisible Digit Product II

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

class Solution {
public:
    string smallestNumber(string num, long long t) {
        int i = num.size();
        long long begin = stoll(num);
        string answer;
        for(long long j = begin; j < 1e15; j++)
        {
            if(isValid(j, t))
            {
                return to_string(j);
            }
        }
        return "-1";
    }

private:
    // TODO:
    bool isValid(long long i, long long reference)
    {
        long long x = i, digit = 1;
        while (x > 0)
        {
            long long check = x % 10;
            if(check == 0) return false;
            digit *= check;
            x /= 10;
        }
        if(digit % reference == 0) return true;
        else return false;
    }
    // 如有需要，把辅助函数、状态定义、工具函数写在这里
};
