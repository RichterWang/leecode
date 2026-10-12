#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // 使用最小堆（优先队列）来维护前 k 个最大的元素
        priority_queue<int, vector<int>, greater<int>> minHeap;

        for (int num : nums) {
            minHeap.push(num);
            if (minHeap.size() > k) {
                minHeap.pop(); // 弹出最小的元素，保持堆的大小为 k
            }
        }

        return minHeap.top(); // 堆顶就是第 k 个最大的元素
    }
};
