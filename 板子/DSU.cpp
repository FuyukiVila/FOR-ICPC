#include "bits/stdc++.h"

struct DSU {
    std::vector<int> f, siz;

    explicit DSU(int n) : f(n + 1), siz(n + 1, 1) { std::iota(f.begin(), f.end(), 0); }

    int find(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }

    bool same(int x, int y) { return find(x) == find(y); }

    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }

    int size(int x) { return siz[find(x)]; }
};