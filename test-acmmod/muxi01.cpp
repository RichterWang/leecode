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

typedef struct{
    int minValue;
    int maxValue;
}Segment;

typedef struct{
    int segNum;
    vector<Segment> segs;
}SegRanges;

SegRanges mergeSegs(SegRanges segs)
{
    SegRanges result;
    result.segNum = 0;
    if(segs.segs.empty()) return result;

    sort(segs.segs.begin(), segs.segs.end(), 
    [] (const Segment& a, const Segment& b)
    {
        if(a.minValue != b.minValue) return a.minValue < b.minValue;
        else return a.maxValue < b.maxValue;
    });

    Segment current = segs.segs[0];

    for(int i = 1; i < static_cast<int>(segs.segs.size()); i++)
    {
        if(segs.segs[i].minValue <= current.maxValue) current.maxValue = max(current.maxValue, segs.segs[i].maxValue);
        else{
            result.segs.push_back(current);
            result.segNum++;
            current = segs.segs[i];
        }
    }

    result.segs.push_back(current);
    result.segNum++;

    return result;
} 

int main()
{
    SegRanges input;
    int n;
    cin >> n;
    input.segNum = n;

    for(int i = 0; i < n; i++)
    {
        Segment seg;
        cin >> seg.minValue >> seg.maxValue;
        input.segs.push_back(seg);
    }

    SegRanges answer = mergeSegs(input);

    cout << answer.segNum << endl;
    for(const auto& seg : answer.segs) cout << seg.minValue << " " << seg.maxValue << endl;
    
    return 0;
}
