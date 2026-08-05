#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> graph(n);
        vector<bool> visited(n, false);

        for (const auto& edge : invocations) {
            graph[edge[0]].push_back(edge[1]);
        }

        stack<int> st;
        st.push(k);
        visited[k] = true;

        while (!st.empty()) {
            int node = st.top();
            st.pop();

            for (int next : graph[node]) {
                if (!visited[next]) {
                    visited[next] = true;
                    st.push(next);
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
