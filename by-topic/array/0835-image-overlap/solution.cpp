#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

/*
 * 835. 图像重叠
 *
 * 核心思路：平移 = 坐标偏移
 * 统计所有 (img1的1, img2的1) 配对产生的偏移量，
 * 频次最高的偏移量即为最大重叠数
 */
class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = static_cast<int>(img1.size());

        // 提取所有 1 的坐标
        vector<pair<int, int>> coordinates1, coordinates2;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (img1[i][j] == 1) coordinates1.emplace_back(i, j);
                if (img2[i][j] == 1) coordinates2.emplace_back(i, j);
            }
        }

        // 统计每种偏移量的出现次数
        unordered_map<int, int> shift_count;
        for (auto [x1, y1] : coordinates1) {
            for (auto [x2, y2] : coordinates2) {
                int row = x1 - x2;
                int col = y1 - y2;
                shift_count[(row << 6) + col]++;  // << 6 即 * 64，足以容纳 [-29,29]
            }
        }

        // 返回最大频次
        int answer = 0;
        for (auto [_, cnt] : shift_count)
            answer = max(answer, cnt);

        return answer;
    }
};
