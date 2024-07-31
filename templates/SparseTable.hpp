#ifndef __SPARSE_TABLE_HPP
#define __SPARSE_TABLE_HPP

#include "vector"
#include "cassert"

// SpareTable<ElemType, CompareType> ElemType: 元素类型 CompareType: 比较函数, 默认为greater<>
template<class T = long long, class Cmp = std::greater<T> >
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
        assert(r >= l);
        assert(l >= 0);
        assert(r < st.size());
        int k = std::__lg(r - l + 1);
        return Cmp(st[l][k], st[r - (1 << k) + 1][k]) ? st[l][k] : st[r - (1 << k) + 1][k];
    }

};

#endif
