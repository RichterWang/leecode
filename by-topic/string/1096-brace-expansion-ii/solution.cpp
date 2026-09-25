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
#include <set>

using namespace std;

class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        int i = 0;
        set<string> resultSet = parseExpression(expression, i);
        return vector<string>(resultSet.begin(), resultSet.end());
    }

private:
    // 处理逗号（并集）
    set<string> parseExpression(const string& s, int& i)
    {
        set<string> result = parseTerm(s, i);

        while(i < static_cast<int>(s.size()) && s[i] == ',')
        {
            i++;
            set<string> next = parseTerm(s, i);
            result.insert(next.begin(), next.end());
        }

        return result;
    }

    // 处理相接（笛卡尔积）
    set<string> parseTerm(const string& s, int& i)
    {
        set<string> result = parseAtom(s, i);

        while(i < static_cast<int>(s.size()) && s[i] != ',' && s[i] != '}')
        {
            set<string> next = parseAtom(s, i);

            set<string> combined;
            for(const string& a : result) for(const string& b : next) combined.insert(a + b);

            result = combined;
        }

        return result;
    }

    // 处理单个元素
    set<string> parseAtom(const string& s, int& i)
    {
        if(s[i] == '{')
        {
            i++;
            set<string> result = parseExpression(s, i);
            i++;
            return result;
        }
        else return {string(1, s[i++])};
    }
};
