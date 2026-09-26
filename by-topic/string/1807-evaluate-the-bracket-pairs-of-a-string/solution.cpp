#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> reference;

        int n = static_cast<int>(s.size());

        for(const auto& kv : knowledge) reference[kv[0]] = kv[1];

        string answer;

        int ptr = 0;
        while(ptr < n)
        {
            if(s[ptr] == '(') {
                string temp = {};
                ptr++;
                while(s[ptr] != ')')
                {
                    temp += s[ptr];
                    ptr++;
                }
                ptr++;
                auto it = reference.find(temp);
                it != reference.end() ? answer += it->second : answer += "?";
            }
            else {
                answer += s[ptr];
                ptr++;
            }
        }

        return answer;
    }

private:

};
