#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> graph(n);
        vector<bool> visited(n, false);

        for (const auto& edge : invocations) {
            graph[edge[0]].push_back(edge[1]);
        }

        bfs(k, graph, visited);

        for (const auto& edge : invocations) {
            if (!visited[edge[0]] && visited[edge[1]]) {
                vector<int> all;
                for (int i = 0; i < n; ++i) {
                    all.push_back(i);
                }
                return all;
            }
        }

        vector<int> answer;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                answer.push_back(i);
            }
        }
        return answer;
    }

private:
    void bfs(int node, vector<vector<int>>& graph, vector<bool>& visited) {
        queue<int> q;
        q.push(node);
        visited[node] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int next : graph[current]) {
                if (!visited[next]) {
                    q.push(next);
                    visited[next] = true;
                }
            }
        }
    }
};
