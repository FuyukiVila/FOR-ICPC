#include "bits/stdc++.h"

struct RollingDsu {
    std::vector<int> f, siz, tag, st;

    RollingDsu() = default;

    explicit RollingDsu(int n) : f(n + 1), siz(n + 1, 1), tag(n + 1, 0) { std::iota(f.begin(), f.end(), 0); }


    int find(int x) {
        while (x != f[x]) x = f[x];
        return x;
    }

    bool same(int x, int y) { return find(x) == find(y); }

    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (siz[x] < siz[y]) {
            std::swap(x, y);
        }
        tag[y] -= tag[x];
        siz[x] += siz[y];
        f[y] = x;
        st.emplace_back(y);
        return true;
    }

    int size() {
        return st.size();
    }

    int size(int x) {
        return siz[find(x)];
    }

    void rollBack(int lastSize = 0) {
        assert(lastSize <= st.size());
        while (st.size() != lastSize) {
            int y = st.back();
            int x = f[y];
            siz[x] -= siz[y];
            tag[y] += tag[x];
            f[y] = y;
            st.pop_back();
        }
    }

    void add(int x, int v) { tag[find(x)] += v; }

};

struct TimeSegTree {

    RollingDsu dsu;

    struct node {
        int l{0}, r{0};
        std::vector<std::pair<int, int> > op;
        bool exist{false};

        constexpr bool inRange(int l, int r) {
            return this->l >= l && this->r <= r;
        }

        constexpr bool outOfRange(int l, int r) {
            return this->l > r || this->r < l;
        }

        constexpr int length() { return this->r - this->l + 1; }

        constexpr int size() { return length(); }

        constexpr void add(int u, int v) { op.emplace_back(u, v); }

        constexpr void clear() { op.clear(); }
    };

    std::vector<node> tree;

    TimeSegTree() = default;

    // time:时间长度, size:图上节点个数
    explicit TimeSegTree(int time, int size) {
        dsu = RollingDsu(size);
        tree.resize(time * 4 + 5);
        build(time, 1, 1, time);
    }

    void build(int time, int u, int l, int r) {
        tree[u].l = l;
        tree[u].r = r;
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(time, u << 1, l, mid);
        build(time, u << 1 | 1, mid + 1, r);
    }

    // 在[l, r]时间段上,连接x, y
    void modify(int l, int r, int x, int y, int u = 1) {
        if (tree[u].inRange(l, r)) {
            tree[u].add(x, y);
            return;
        }
        if (tree[u].outOfRange(l, r)) return;
        tree[u].exist = true;
        modify(l, r, x, y, u << 1);
        modify(l, r, x, y, u << 1 | 1);
    }

    void solve(int u = 1) {
        int lastSize = dsu.size();
        for (auto &[x, y]: tree[u].op) {
            dsu.merge(x, y);
        }
        if (!tree[u].exist) {
            // to do sth at this time
            execute(u);
            dsu.rollBack(lastSize);
            return;
        }
        solve(u << 1);
        solve(u << 1 | 1);
        dsu.rollBack(lastSize);
    }

    void execute(int u) {
        // how to do
    }
};
