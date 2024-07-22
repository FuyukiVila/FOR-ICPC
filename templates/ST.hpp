#ifndef __ST_HPP
#define __ST_HPP

#include "vector"

template<typename T, typename Cmp = std::greater<T> >
struct SparseTable {
private:
    std::vector<std::vector<T> > st;
public:
    explicit SparseTable(const std::vector<T> &&a) {
        st.resize(a.size(), std::vector<T>(32));
        for (int i = 0; i < a.size(); i++) {
            st[i][0] = a[i];
        }
        for (int j = 1; 1 << j <= a.size(); j++) {
            for (int i = 0; i + (1 << j) - 1 < a.size(); i++) {
                st[i][j] = Cmp(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]) ? st[i][j - 1] : st[i + (1 << (j - 1))][j - 1];
            }
        }
    }

    T get(int l, int r) {
        int k = std::__lg(r - l + 1);
        return Cmp(st[l][k], st[r - (1 << k) + 1][k]) ? st[l][k] : st[r - (1 << k) + 1][k];
    }

};

#endif
