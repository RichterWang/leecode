#include <utility>

using namespace std;

/*
 * 2265. 统计值等于子树平均值的节点数
 *
 * 后序遍历，每层返回 {子树节点值之和, 子树节点个数}。 * answer 作为全局累计量以引用传递。
 */
class Solution {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    int averageOfSubtree(TreeNode* root) {
        int answer = 0; // 满足要求答案个数
        int count = 0; // 子节点个数        dfs_search(root, answer); // 前一个int为和，后一个int为数量
        return answer;
    }
private:
    pair<int, int> dfs_search(TreeNode* current, int& answer)
    {        if(current == nullptr) return{0, 0};
        pair<int, int> from_left = dfs_search(current->left, answer);
        pair<int, int> from_right = dfs_search(current->right, answer);
        
        int count = 1+ from_left.second + from_right.second;
        int sum = current->val + from_left.first + from_right.first;

        if(current->val == sum / count) answer++;
        return {sum, count};  
    }
};
