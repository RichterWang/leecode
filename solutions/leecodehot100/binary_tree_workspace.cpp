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
#include <set>
#include <map>
#include <sstream> 

using namespace std;

/*
 * Daily question draft
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(root == nullptr) return nullptr;

        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;

        invertTree(root->left);
        invertTree(root->right);

        return root;
    }

    // 迭代版本中序遍历
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> stk;
        TreeNode* current = root;

        while(current != nullptr || !stk.empty()){
            while(current != nullptr){
                stk.push(current);
                current = current->left;
            }

            current = stk.top();
            stk.pop();
            result.push_back(current->val);

            current = current->right;
        }
        return result;
    }

    // 二叉树最近公共祖先（普通二叉树版本）
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr) return nullptr;
        if(root == p || root == q) return root;

        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if(left != nullptr && right != nullptr) return root;

        return left != nullptr ? left : right;
    }

    // 二叉树最近公共祖先（二叉搜索树版本）
    TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q){
        if(p->val < root->val && q->val < root->val) return lowestCommonAncestorBST(root->left, p, q);
        if(p->val > root->val && q->val > root->val) return lowestCommonAncestorBST(root->right, p, q);
        return root;
    }

private:

};

class helper_BST {
public:
    // 没有null的时候可以使用
    TreeNode* insertIntoBST(TreeNode* root, int val){
        if(root == nullptr) return new TreeNode(val);

        if(val < root->val) root->left = insertIntoBST(root->left, val);
        else root->right = insertIntoBST(root->right, val);

        return root;
    }

    // 层序构造二叉树（有null的时候使用）
    TreeNode* build_tree(vector<int>& nums)
    {
        if(nums.empty() || nums[0] == -1) return nullptr;
        int n = static_cast<int>(nums.size());

        TreeNode* root = new TreeNode(nums[0]);
        queue<TreeNode*> q;
        q.push(root);

        int i = 1;
        while(!q.empty() && i < n)
        {
            TreeNode* current = q.front();
            q.pop();

            if(i < n){
                if(nums[i] != -1) {
                    current->left = new TreeNode(nums[i]);
                    q.push(current->left);
                }
                ++i;
            }

            if(i < n){
                if(nums[i] != -1) {
                    current->right = new TreeNode(nums[i]);
                    q.push(current->right);
                }
                ++i;
            }
        }

        return root;
    }

    // 层序构造二叉树转为数组
    vector<int> tree2array(TreeNode* root){
        if(root == nullptr) return{};

        vector<int> result;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty())
        {
            TreeNode* current = q.front();
            q.pop();

            if(current != nullptr){
                result.push_back(current->val);
                q.push(current->left);
                q.push(current->right);
            } else {
                result.push_back(-1);
            }
        }

        while(!result.empty() && result.back() == -1) result.pop_back();

        return result;
    }

private:
    
};

// 函数入口，用于debug和本地测试，提交到 LeetCode 时可以删除 main 函数
int main() {
    Solution solution;
    helper_BST helper_BST;

    vector<int> nums;

    // // vector的标准流式输入
    // string line;
    // getline(cin, line); // 从标准输入读取一整行直到eof
    // istringstream iss(line); // 创建一个字符串输入流对象，用line初始化
    // int num;
    // while (!iss.eof()) {
    //     if (iss >> num) {
    //         nums.push_back(num);
    //     } else {
    //         iss.clear(); // 清除错误状态标志
    //         iss.ignore(1); // 忽略一个字符（通常是空格或逗号）
    //     }
    // }

    // 从字符串读取的stdin标准流输入
    string line;
    getline(cin, line);
    istringstream iss(line);
    string token;

    while(iss >> token){
        if(token == "null" || token == "NULL" || token == "Null") nums.push_back(-1);
        else nums.push_back(stoi(token));
    }

    // 从数组构造二叉树
    TreeNode* root = nullptr;
    for(int i : nums) root = helper_BST.insertIntoBST(root, i);

    TreeNode* result_root = solution.invertTree(root);

    // int n = static_cast<int>(result.size());
    // cout << "current output: [";
    // for (int i = 0; i < n; i++) {
    //     cout << result[i];
    //     if (i < n - 1) {
    //         cout << ", ";
    //     }
    // }

    // 二叉树转换为数组
    vector<int> result = helper_BST.tree2array(root);

    int n = static_cast<int>(result.size());
    for(int i = 0; i < n; i++){
        cout << result[i];
        if(i < n - 1) cout << ",";
    }
    cout << endl;

    return 0;
}

// 编译运行的命令：g++ -std=c++20 -o build/debugging solutions/everydayquestion.cpp

// gdb调试命令：gdb ./build/debugging

/*

*/
