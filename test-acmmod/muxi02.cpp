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

const char* myStrStr(const char* haystack, const char* needle)
{
    if(*needle == '\0') return haystack;

    for(const char* p = haystack; *p != '\0'; p++)
    {
        const char* a = p;
        const char* b = needle;

        while(*a != '\0' && *b != '\0' && *a == *b)
        {
            a++; b++;
        }

        if(*b == '\0') return p;
    }

    return nullptr;
}

int main()
{
    string a;
    string b;

    cin >> a;
    cout << '\n';
    cin >> b;

    const char* result = myStrStr(a.c_str(), b.c_str());

    if(result != nullptr) cout << (result - a.c_str()) <<endl;
    else cout << -1 << endl;

    return 0;
}
