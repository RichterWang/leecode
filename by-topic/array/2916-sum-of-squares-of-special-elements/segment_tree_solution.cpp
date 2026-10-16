#include <vector>
#include <unordered_map>
using namespace std;

/**
 * LeetCode 2916: 子数组不同元素数目的平方和 II
 * 
 * 解法：线段树 + 延迟标记
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(n)
 * 
 * 核心思想：
 * 1. 对于每个右端点 r，维护所有左端点 i (0 <= i <= r) 的不同元素计数 cnt[i]
 * 2. 当 nums[r] 之前在位置 p 出现过，则 [p+1, r] 的 cnt 都要加 1
 * 3. 使用线段树支持：区间加法 + 区间平方和查询
 */
class Solution {
public:
    int sumCounts(vector<int>& nums) {
        this->n = nums.size();
        tree.resize(4 * n);
        build(1, 0, n - 1);
        
        unordered_map<int, int> last;  // 记录每个元素上次出现的位置
        long long answer = 0;
        
        for (int r = 0; r < n; r++) {
            // 找到 nums[r] 上次出现的位置
            int p = last.count(nums[r]) ? last[nums[r]] : -1;
            
            // 区间 [p+1, r] 的所有左端点对应的 cnt 加 1
            rangeAdd(1, 0, n - 1, p + 1, r, 1);
            
            // 查询所有以 r 结尾的子数组的 cnt² 之和
            long long contribution = querySum(1, 0, n - 1, 0, r);
            answer = (answer + contribution) % MOD;
            
            // 更新最后出现位置
            last[nums[r]] = r;
        }

        return answer;
    }

private:
    static const int MOD = 1e9 + 7;

    // 线段树节点
    struct Node {
        long long sum_cnt;     // 区间内所有 cnt 的和：Σcnt[i]
        long long sum_square;  // 区间内所有 cnt² 的和：Σcnt[i]²
        int lazy;              // 延迟标记（区间加的值）

        Node() : sum_cnt(0), sum_square(0), lazy(0) {}
    };

    vector<Node> tree;
    int n;

    /**
     * 向上更新：合并左右子节点的信息
     */
    void push_up(int node) {
        tree[node].sum_cnt = (tree[node * 2].sum_cnt + tree[node * 2 + 1].sum_cnt) % MOD;
        tree[node].sum_square = (tree[node * 2].sum_square + tree[node * 2 + 1].sum_square) % MOD;
    }

    /**
     * 向下传递延迟标记
     */
    void push_down(int node, int left, int right) {
        if (tree[node].lazy == 0) return;

        int mid = (left + right) / 2;
        int delta = tree[node].lazy;

        // 应用延迟标记到左右子节点
        apply_lazy(node * 2, left, mid, delta);
        apply_lazy(node * 2 + 1, mid + 1, right, delta);

        tree[node].lazy = 0;
    }

    /**
     * 应用延迟标记到节点
     * 
     * 数学推导：区间 [left, right] 内每个 cnt 都加 delta
     * 
     * 新的 sum_cnt = 旧的 + len * delta
     * 
     * 新的 sum_square 计算：
     * Σ(cnt + delta)² = Σ(cnt² + 2*cnt*delta + delta²)
     *                 = Σcnt² + 2*delta*Σcnt + len*delta²
     *                 = old_sum_square + 2*delta*old_sum_cnt + len*delta²
     */
    void apply_lazy(int node, int left, int right, int delta) {
        int len = right - left + 1;
        long long old_sum = tree[node].sum_cnt;
        
        // 更新 sum_cnt
        tree[node].sum_cnt = (old_sum + (long long)len * delta) % MOD;
        
        // 更新 sum_square：分两步累加
        long long new_sum_square = tree[node].sum_square;
        
        // 第一项：2*delta*Σcnt[i]（交叉项）
        new_sum_square = (new_sum_square + 2LL * delta % MOD * old_sum % MOD) % MOD;
        
        // 第二项：len*delta²（平方项）
        new_sum_square = (new_sum_square + (long long)len * delta % MOD * delta % MOD) % MOD;
        
        tree[node].sum_square = new_sum_square;
        
        // 累加延迟标记
        tree[node].lazy = (tree[node].lazy + delta) % MOD;
    }

    /**
     * 建树（初始所有 cnt = 0）
     */
    void build(int node, int l, int r) {
        tree[node] = Node();
        if (l == r) return;
        
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
    }

    /**
     * 区间更新：[ql, qr] 内所有 cnt 加 delta
     */
    void rangeAdd(int node, int l, int r, int ql, int qr, int delta) {
        if (ql > r || qr < l) return;
        
        // 完全覆盖：直接应用延迟标记
        if (ql <= l && r <= qr) {
            apply_lazy(node, l, r, delta);
            return;
        }
        
        // 部分覆盖：递归处理左右子树
        push_down(node, l, r);
        int mid = (l + r) / 2;
        rangeAdd(node * 2, l, mid, ql, qr, delta);
        rangeAdd(node * 2 + 1, mid + 1, r, ql, qr, delta);
        push_up(node);
    }

    /**
     * 区间查询：查询 [ql, qr] 内所有 cnt² 的和
     */
    long long querySum(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        
        // 完全覆盖：直接返回结果
        if (ql <= l && r <= qr) {
            return tree[node].sum_square;
        }
        
        // 部分覆盖：递归查询左右子树
        push_down(node, l, r);
        int mid = (l + r) / 2;
        long long left_sum = querySum(node * 2, l, mid, ql, qr);
        long long right_sum = querySum(node * 2 + 1, mid + 1, r, ql, qr);
        return (left_sum + right_sum) % MOD;
    }
};
