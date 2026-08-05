#include <vector>

using namespace std;

class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> graph(n);
        vector<bool> visited(n, false);

        for (const auto& edge : invocations) {
            graph[edge[0]].push_back(edge[1]);
        }

        dfs(k, graph, visited);

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

private:
    void dfs(int node, const vector<vector<int>>& graph, vector<bool>& visited) {
        visited[node] = true;
        for (int next : graph[node]) {
            if (!visited[next]) {
                dfs(next, graph, visited);
            }
        }
    }
};
