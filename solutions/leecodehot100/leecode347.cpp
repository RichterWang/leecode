#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> result;
        unordered_map<int, int> frequencyMap;

        for (int num : nums) frequencyMap[num]++;

        auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second;
        };

        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> minHeap(cmp);
        for (const auto& entry : frequencyMap) {
            minHeap.push({entry.first, entry.second});
            if (minHeap.size() > k) minHeap.pop();
        }

        while (!minHeap.empty()) {
            result.push_back(minHeap.top().first);
            minHeap.pop();
        }

        return result;
    }
};
