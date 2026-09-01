#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

/*
 * 3568. 清理教室的最少移动
 *
 * BFS + 状态压缩 + 能量支配剪枝
 *
 * 状态四元组 (x, y, mask, energy)：
 *   - (x, y)  当前位置
 *   - mask    已收集垃圾的位集合，第 k 位为 1 表示 k 号垃圾已收集
 *   - energy  剩余能量
 *
 * best[x][y][mask] 记录"以该位置和收集状态到达时的最大剩余能量"，
 * 承担两个职责：作为 visited 表保证终止性，同时把 energy 维度压缩掉。
 *
 * 错误解法的对照见 wrong_solution.cpp。
 */
class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = static_cast<int>(classroom.size());
        int n = static_cast<int>(classroom[0].size());

        array<int, 4> start;
        vector<vector<int>> garbageId(m, vector<int>(n, -1));
        int total = 0;

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (classroom[i][j] == 'S') {
                    start[0] = i;
                    start[1] = j;
                }
                else if (classroom[i][j] == 'L') garbageId[i][j] = total++;
            }
        }
        if (total == 0) return 0;
        int fullMask = (1 << total) - 1;

        vector<vector<vector<int>>> best(m, vector<vector<int>>(n, vector<int>(1 << total, -1)));
        best[start[0]][start[1]][0] = energy;

        queue<array<int, 4>> bfs_queue;
        start[2] = 0;        // mask：初始什么都没捡
        start[3] = energy;   // energy：初始满能量
        bfs_queue.push(start);

        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        int step = 0;

        while (!bfs_queue.empty())
        {
            int node_num = static_cast<int>(bfs_queue.size());
            for (int i = 0; i < node_num; i++)
            {
                array<int, 4> temp = bfs_queue.front();
                bfs_queue.pop();

                // 层序 BFS 保证首次抵达 fullMask 的层号即最少步数
                if (temp[2] == fullMask) return step;
                // 能量耗尽即死路；此时所在格必然不是 R（踏上 R 的瞬间已补满）
                if (temp[3] == 0) continue;

                for (int j = 0; j < 4; j++)
                {
                    int next_x = temp[0] + dx[j], next_y = temp[1] + dy[j];
                    if (next_x < 0 || next_x >= m || next_y < 0 || next_y >= n) continue;
                    if (classroom[next_x][next_y] == 'X') continue;

                    int next_energy = temp[3] - 1;   // 先付移动代价
                    int next_mask = temp[2];

                    // |= 保证累积且幂等，重复经过同一个 L 不会出错
                    if (classroom[next_x][next_y] == 'L') next_mask |= (1 << garbageId[next_x][next_y]);
                    // 落地后若是 R 则补满，顺序不能与上面的扣减对调
                    if (classroom[next_x][next_y] == 'R') next_energy = energy;

                    // 支配剪枝：能量不超过已有记录的状态做不到任何新事，且步数更多
                    // 用 >= 而非 >，否则等价状态会重复入队
                    if (best[next_x][next_y][next_mask] >= next_energy) continue;
                    best[next_x][next_y][next_mask] = next_energy;
                    bfs_queue.push({next_x, next_y, next_mask, next_energy});
                }
            }
            step++;
        }
        return -1;
    }
};
