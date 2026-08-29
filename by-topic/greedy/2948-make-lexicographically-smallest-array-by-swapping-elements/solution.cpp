#include <algorithm>
#include <functional>
#include <numeric>
#include <unordered_map>
#include <vector>

using namespace std;

/*
 * 2948. 交换得到字典序最小的数组
 *
 * 思路：排序 + 并查集 + 贪心
 * 1. 按值排序（保留原索引），只检查相邻对，差值 <= limit 就把两个原索引合并
 * 2. 同一连通分量内的元素可以任意排列
 * 3. 从左到右扫位置，每个位置取所在分量剩余的最小值
 */
class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = static_cast<int>(nums.size());

        // 第一步：按值排序，同时保留原索引
        vector<pair<int, int>> sorted(n);
        for (int i = 0; i < n; i++) sorted[i] = {nums[i], i};  // {值, 原索引}
        sort(sorted.begin(), sorted.end());

        // 第二步：初始化并查集，每个元素自己是根
        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0);

        // 路径压缩的 find，lambda 捕获 parent 引用，用 function 包装以支持递归
        function<int(int)> find = [&](int x) -> int {
            return parent[x] == x ? x : parent[x] = find(parent[x]);
        };

        // 第三步：只检查排序后的相邻对，靠传递性串起整个分量
        // 注意合并的是原索引，不是排序位置
        for (int i = 0; i + 1 < n; i++) {
            if (sorted[i + 1].first - sorted[i].first <= limit) {
                parent[find(sorted[i + 1].second)] = find(sorted[i].second);
            }
        }

        // 第四步：每个根收集一份升序值池
        // 按 sorted 顺序 push，池内天然升序，无需再排序
        unordered_map<int, vector<int>> pool;
        for (int k = 0; k < n; k++) {
            pool[find(sorted[k].second)].push_back(sorted[k].first);
        }

        // 第五步：从左到右贪心，位置 i 取所在分量剩余的最小值
        // 用 map 而非 vector 存指针，因为根的编号不等于根的个数
        unordered_map<int, int> ptr;
        vector<int> result(n);
        for (int i = 0; i < n; i++) {
            int root = find(i);
            result[i] = pool[root][ptr[root]++];
        }

        return result;
    }
};
