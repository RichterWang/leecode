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

using namespace std;

/*
 * Segment Tree Solution for LeetCode 2213
 *
 * 使用线段树维护区间信息：
 * - 每个节点维护区间的前缀、后缀、最长重复子串长度
 * - 单点更新时只需要 O(log n) 向上更新受影响的祖先节点
 * - 合并两个子区间时考虑跨越中点的连续段
 */
class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        n = static_cast<int>(s.size());
        this->s = s;
        tree.assign(4 * n, Node());
        build(1, 0, n - 1);

        vector<int> ans;
        ans.reserve(queryCharacters.size()); // performance optimize

        for(int i = 0; i < static_cast<int>(queryCharacters.size()); i++)
        {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            ans.push_back(tree[1].best);
        }

        return ans;
    }

private:
    struct Node{
        int len = 0;      // 区间长度
        char lc = 0;      // 区间最左字符
        char rc = 0;      // 区间最右字符
        int pref = 0;     // 从左端点开始的最长连续段
        int suf = 0;      // 从右端点开始的最长连续段
        int best = 0;     // 区间内最长连续段
    };

    int n = 0;
    string s;
    vector<Node> tree;

    Node mergeNode(const Node& left, const Node& right)
    {
        if (left.len == 0) return right;
        if (right.len == 0) return left;

        Node res;
        res.len = left.len + right.len;
        res.lc = left.lc;
        res.rc = right.rc;

        // 合并前缀：如果左子区间全是同一字符且能和右子区间连接，则延伸
        res.pref = left.pref;
        if(left.pref == left.len && left.rc == right.lc) 
            res.pref = left.len + right.pref;
        
        // 合并后缀：如果右子区间全是同一字符且能和左子区间连接，则延伸
        res.suf = right.suf;
        if (right.suf == right.len && left.rc == right.lc) 
            res.suf = right.len + left.suf;

        // 合并最长段：取两个子区间的最大值，如果跨中点能连接则更新
        res.best = max(left.best, right.best);
        if (left.rc == right.lc) 
            res.best = max(res.best, left.suf + right.pref);

        return res;       
    }

    // 递归构建线段树，idx: 节点在tree数组中的位置，[l,r]: 该节点管理的原字符串区间
    void build(int idx, int l, int r)
    {
        if (l == r)
        {
            tree[idx].len = 1;
            tree[idx].lc = tree[idx].rc = s[l];
            tree[idx].pref = tree[idx].suf = tree[idx].best = 1;

            return;
        }

        int mid = l + (r - l) / 2;
        build(idx * 2, l, mid);
        build(idx * 2 + 1, mid + 1, r);
        tree[idx] = mergeNode(tree[idx * 2], tree[idx * 2 + 1]);
    }

    // 单点更新，将位置 pos 的字符修改为 c
    void update(int idx, int l, int r, int pos, char c)
    {
        if(l == r)
        {
            s[pos] = c;
            tree[idx].lc = tree[idx].rc = c;
            tree[idx].pref = tree[idx].suf = tree[idx].best = 1;

            return;
        }
        
        int mid = l + (r - l) / 2;
        if(pos <= mid) update(idx * 2, l, mid, pos, c);
        else update(idx * 2 + 1, mid + 1, r, pos, c);

        tree[idx] = mergeNode(tree[idx * 2], tree[idx * 2 + 1]);
    }
};
