#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

/**
 * LeetCode 1569: 将子数组重新排列得到一个二叉搜索树的方案数
 * 
 * 解法：递归 + 组合数学（Pascal 三角）
 * 时间复杂度：O(n²)
 * 空间复杂度：O(n²)
 * 
 * 核心思想：
 * 1. BST 的结构由元素的相对大小关系决定，与具体插入顺序无关
 * 2. 第一个元素必须是根节点
 * 3. 左子树元素必须全部小于根，右子树元素必须全部大于根
 * 4. 左右子树内部可以任意交错排列，只要相对顺序不变
 * 5. 递归公式：ways(nums) = ways(left) × ways(right) × C(|left|+|right|, |left|)
 */
class Solution {
public:
    int numOfWays(vector<int>& nums) {
        constexpr int mod = 1e9 + 7;
        int n = static_cast<int>(nums.size());

        // 预处理组合数（Pascal 三角）
        // comb[i][j] = C(i, j) = 从 i 个元素中选 j 个的方案数
        vector<vector<long long>> comb(n + 1, vector<long long>(n + 1, 0));
        comb[0][0] = 1;
        for(int i = 1; i <= n; i++){
            comb[i][0] = 1;  // 从 i 个中选 0 个，只有 1 种方案
            for(int j = 1; j <= i; j++) {
                // Pascal 三角递推公式：C(i,j) = C(i-1,j-1) + C(i-1,j)
                comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % mod;
            }
        }

        // Lambda 递归函数
        function<long long(vector<int>&)> dfs = [&](vector<int>& nums) -> long long{
            int n = static_cast<int>(nums.size());
            if(n <= 1) return 1;  // 空或单节点，只有 1 种排列

            int root = nums[0];  // 第一个元素是根
            vector<int> left, right;

            // 根据大小关系分割左右子树
            for(int i = 1; i < n; i++)
            {
                if(nums[i] < root) left.push_back(nums[i]);
                else right.push_back(nums[i]);
            }

            // 递归计算左右子树的方案数
            long long left_count = dfs(left);
            long long right_count = dfs(right);

            // 左右子树交错排列的方案数：C(total, left_size)
            int total = n - 1;  // 除去根节点
            int left_size = static_cast<int>(left.size());

            long long interleave = comb[total][left_size];
            
            // 总方案数 = 左子树方案数 × 右子树方案数 × 交错方案数
            return left_count * right_count % mod * interleave % mod;
        };        

        // 减 1 是因为原序列不算在"重排"方案中
        return (dfs(nums) - 1 + mod) % mod;
    }
};
