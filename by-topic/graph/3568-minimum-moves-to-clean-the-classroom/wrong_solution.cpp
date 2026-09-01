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

using namespace std;

/*
 * 3568. 清理教室的最少移动 —— 错误解法（反面教材）
 *
 * 这份代码是第一次尝试的产物，思路是"普通网格 BFS + 全局计数器"。
 * 它在设计层面和实现层面都有问题，保留下来用于对照学习。
 *
 * === 设计层面（根本性错误，改不动，必须换状态设计）===
 *
 * 1. 状态维度缺失
 *    状态只有 (x, y)，但真正决定后续能做什么的还有：
 *      - 已收集哪些垃圾（决定还差多少）
 *      - 剩余能量（决定还能走几步）
 *    正确状态应该是 (x, y, mask)，能量作为附加属性做支配剪枝。
 *
 * 2. temp_energy 是全局变量，但能量是路径相关的
 *    同一层的不同节点走的路不同，有的路过 R 被补满，有的没有。
 *    用一个变量记录全层能量，从根上就是错的。
 *
 * 3. need_collect 是全局递减，但垃圾收集也是路径相关的
 *    A 路径捡到的垃圾被算到了 B 路径头上；
 *    同一个 'L' 格子还会被不同路径反复减，导致提前归零。
 *
 * 4. visited[x][y] 封死了回头路
 *    为了绕去 R 补能量、或按不同顺序捡垃圾，走回头路是常态。
 *    一个格子标记一次就再也不能进，正解被直接剪掉。
 *
 * === 实现层面（低级 bug，即使状态设计对了也会崩）===
 *
 * 5. m / n 含义搞反
 *      m = classroom[0].size();  // 实际是列数
 *      n = classroom.size();     // 实际是行数
 *    后面却拿 m 当行数遍历 → 非方阵时越界或漏格。
 *
 * 6. 邻居扩展全写成了自己
 *      if (visited[next_x][next_y] || classroom[temp.first][temp.second] == 'X')
 *                                                ^^^^ 该检查 next
 *      visited[temp.first][temp.second] = true;   // 该标记 next
 *      bfs_queue.push({temp.first, temp.second}); // 该 push next
 *    push 自己 → 队列里塞满重复节点，死循环 / MLE。
 *
 * 7. 终止判断用了 energy 而不是 temp_energy
 *      if (energy == 0 && need_collect != 0) return -1;
 *    energy 是最大容量，全程不变，这个分支永远不会触发。
 *
 * 正确解法见 solution.cpp（BFS + bitmask + 能量支配剪枝）。
 */
class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = static_cast<int>(classroom[0].size());   // BUG 5: 这是列数
        int n = static_cast<int>(classroom.size());      // BUG 5: 这是行数

        pair<int, int> start;
        int need_collect = 0;

        for(int i = 0; i < m; i++)          // BUG 5: 拿列数当行数遍历
        {
            for(int j = 0; j < n; j++)
            {
                if(classroom[i][j] == 'S'){
                    start.first = i;
                    start.second = j;
                }
                else if(classroom[i][j] == 'L') need_collect++;
            }
        }

        queue<pair<int, int>> bfs_queue;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int temp_energy = energy;           // BUG 2: 能量是路径相关的，全局变量装不下
        int step = 0;
        bfs_queue.push(start);
        visited[start.first][start.second] = true;

        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};

        while(!bfs_queue.empty())
        {
            int node_num = static_cast<int>(bfs_queue.size());
            for(int i = 0; i < node_num; i++)
            {
                pair<int, int> temp = bfs_queue.front();
                bfs_queue.pop();

                if(classroom[temp.first][temp.second] == 'L') need_collect--;   // BUG 3: 全局递减 + 重复递减
                if(classroom[temp.first][temp.second] == 'R') temp_energy = energy;

                for(int j = 0; j < 4; j++)
                {
                    int next_x = temp.first + dx[j], next_y = temp.second + dy[j];
                    if(next_x < 0 || next_x >= m || next_y < 0 || next_y >= n) continue;
                    // BUG 6: 障碍检查、visited 标记、入队，三处全写成了自己而不是 next
                    if(visited[next_x][next_y] || classroom[temp.first][temp.second] == 'X') continue;
                    visited[temp.first][temp.second] = true;
                    bfs_queue.push({temp.first, temp.second});
                }
            }
            if(energy == 0 && need_collect != 0) return -1;   // BUG 7: energy 恒不为 0，永远进不来
            else if(need_collect == 0) return step;
            temp_energy--;
            step++;
        }
        return -1;
    }

private:

};
