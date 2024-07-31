#ifndef __LCA_HPP
#define __LCA_HPP

#include "vector"
#include "assert.h"

class LCA {
private:
    std::vector<std::vector<int> > f;
    std::vector<int> depth;

    void dfs(int root, int father, const std::vector<std::vector<int> > &g) {
        f[root][0] = father;
        depth[root] = depth[father] + 1;
        for (int i = 1; (1 << i) <= depth[root]; i++) {
            f[root][i] = f[f[root][i - 1]][i - 1];
        }
        for (auto const &v: g[root]) {
            if (v == father) {
                continue;
            }
            dfs(v, root, g);
        }
    }

public:

    // g: 无向边构成的树, root: 根节点, 默认为1
    explicit LCA(int n, const std::vector<std::vector<int>> &g, int root = 1) {
        f.resize(n + 1, std::vector<int>(32));
        depth.resize(n + 1);
        dfs(root, 0, g);
    }

    // 返回u和v的最近公共祖先
    int query(int u, int v) {
        if (depth[u] < depth[v]) {
            std::swap(u, v);
        }
        while (depth[u] > depth[v]) {
            u = f[u][std::__lg(depth[u] - depth[v])];
        }
        if (u == v) {
            return u;
        }
        for (int i = std::__lg(depth[u]); i >= 0; i--) {
            if (f[u][i] != f[v][i]) {
                u = f[u][i];
                v = f[v][i];
            }
        }
        return f[u][0];
    }

    // 返回u和v之间的距离
    int distance(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[query(u, v)];
    }

};

#endif
