#include <bits/stdc++.h>

using namespace std;

template<typename T>
class SegTreeLazyRangeAdd {
public:
    struct node {
        T value{};
        int add{};
        int change{};
        size_t l{}, r{};
    };
    vector<node> tree;
    static size_t n, n4;

    void push_up(size_t x) {
        //push up操作
        //区间求和
        tree[x].value = tree[2 * x].value + tree[2 * x + 1].value;
//        区间求max
//        tree[x].value = max(tree[2 * x].value, tree[2 * x + 1].value);
    }

    void push_down(size_t x) {
        //push down操作
        //区间求和
        if (tree[x].change) {
            tree[x * 2].change = tree[x * 2 + 1].change = tree[x].change;
            tree[x].value += tree[x].change * (tree[x].r - tree[x].l + 1);
        }
        if (tree[x].add) {
            tree[x * 2].add = tree[x * 2 + 1].add = tree[x].add;
            tree[x].value += tree[x].add * (tree[x].r - tree[x].l + 1);
        }
        //区间求max
//        if (tree[x].change) {
//            tree[x * 2].change = tree[x * 2 + 1].change = tree[x].change;
//            tree[x].value = tree[x].change;
//        }
//        if (tree[x].add) {
//            tree[x * 2].add = tree[x * 2 + 1].add = tree[x].add;
//            tree[x].value += tree[x].add;
//        }

        tree[x].change = tree[x].add = 0;

    }

    void build(vector<T> &v, int x = 1, int l = 1, int r = n) {
        if (l == r) {
            tree[x].value = v[l];
            tree[x].l = tree[x].r = l;
            return;
        }
        int m = (l + r) / 2;
        build(v, x * 2, l, m);
        build(v, x * 2 + 1, m + 1, r);
        push_up(x);
    }

    SegTreeLazyRangeAdd(vector<T> v) {
        n = v.size();
        n4 = n * 4;
        tree(n4);
        build(v);
    }


};
