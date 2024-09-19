#ifndef __SPARSE_TABLE_HPP
#define __SPARSE_TABLE_HPP

#include "bits/stdc++.h"

template <class T = long long, class V = long long>
struct SparseTable {
   private:
    std::function <V(T, T)> fun;
    std::vector<std::vector<T> > st;

   public:
    explicit SparseTable() = default;
    explicit SparseTable(const std::vector<T> &a, const std::function <V(T, T)> &fun = [](const T &a, const T &b) -> V {return a > b ? a : b;}) {
        st.resize(a.size(), std::vector<T>(32));
        this->fun = fun;
        for (int i = 0; i < a.size(); i++) {
            st[i][0] = a[i];
        }
        for (int j = 1; 1 << j <= a.size(); j++) {
            for (int i = 0; i + (1 << j) - 1 < a.size(); i++) {
                st[i][j] = fun(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T get(int l, int r) {
        assert(r >= l);
        assert(l >= 0);
        assert(r < st.size());
        int k = std::__lg(r - l + 1);
        return fun(st[l][k], st[r - (1 << k) + 1][k]);
    }
};

#endif
