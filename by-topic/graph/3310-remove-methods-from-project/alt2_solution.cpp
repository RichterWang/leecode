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

        queue<int> q;
        q.push(k);
        visited[k] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int next : graph[node]) {
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }

        for (const auto& edge : invocations) {
            if (!visited[edge[0]] && visited[edge[1]]) {
                vector<int> all;
                for (int i = 0; i < n; ++i) {
                    all.push_back(i);
                }
                return all;
            }
        }

        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};
