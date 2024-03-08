#ifndef __SEG_TREE_HPP
#define __SEG_TREE_HPP

#include <vector>

using namespace std;

template<typename T>
class SegTree {
private:
    struct node {
        T value{0};
        T add{0};
        T change{0};
        bool isChange{false};
        int l{0}, r{0};

        constexpr bool inRange(int l, int r) {
            return this->l >= l && this->r <= r;
        }

        constexpr bool outOfRange(int l, int r) {
            return this->l > r || this->r < l;
        }

        constexpr int length() {
            return this->r - this->l + 1;
        }

        constexpr int size() {
            return length();
        }

    };

    vector<node> tree;

    void push_down(int x) {
        //push down操作
        //区间求和
        if (tree[x].isChange) {
            tree[x * 2].value = tree[x].change * tree[x * 2].size();
            tree[x * 2 + 1].value = tree[x].change * tree[x * 2 + 1].size();
            tree[x * 2].change = tree[x * 2 + 1].change = tree[x].change;
            tree[x * 2].isChange = tree[x * 2 + 1].isChange = true;
        }
        if (tree[x].add) {
            tree[x * 2].value += tree[x].add * tree[x * 2].size();
            tree[x * 2 + 1].value += tree[x].add * tree[x * 2 + 1].size();
            tree[x * 2].add += tree[x].add;
            tree[x * 2 + 1].add += tree[x].add;
        }
        //区间求max
//        if (tree[x].change) {
//            tree[x * 2].value = tree[x].change;
//            tree[x * 2 + 1].value = tree[x].change;
//            tree[x * 2].change = tree[x * 2 + 1].change = tree[x].change;
//            tree[x * 2].isChange = tree[x * 2 + 1].isChange = true;
//        }
//        if (tree[x].add) {
//            tree[x * 2].value += tree[x].add;
//            tree[x * 2 + 1].value += tree[x].add;
//            tree[x * 2].add += tree[x].add;
//            tree[x * 2 + 1].add += tree[x].add;
//        }

        tree[x].isChange = tree[x].change = tree[x].add = 0;

    }

    void push_up(int x) {
        //push up操作
        //区间求和
        tree[x].value = tree[2 * x].value + tree[2 * x + 1].value;
//        区间求max
//        tree[x].value = max(tree[2 * x].value, tree[2 * x + 1].value);
    }

    void build(const vector<T> &arr, int x, int l, int r) {
        tree[x].l = l, tree[x].r = r;
        if (l == r) {
            tree[x].value = arr[l];
            return;
        }
        int m = (l + r) >> 1;
        build(arr, x * 2, l, m);
        build(arr, x * 2 + 1, m + 1, r);
        push_up(x);
    }

public:
    explicit SegTree(const vector<T> &arr) {
        int n = arr.size() - 1;
        tree.resize(n * 4 + 5);
        build(arr, 1, 1, n);
    }

    void add(int l, int r, T val, int x = 1) {
        if (tree[x].outOfRange(l, r)) {
            return;
        }
        if (tree[x].inRange(l, r)) {
            tree[x].add += val;
            //区间求和
            tree[x].value += val * tree[x].size();
            //区间求Max
            // tree[x].value += val;
            return;
        }
        push_down(x);
        add(l, r, val, x * 2);
        add(l, r, val, x * 2 + 1);
        push_up(x);
    }

    void change(int l, int r, T val, int x = 1) {
        if (tree[x].outOfRange(l, r)) {
            return;
        }
        if (tree[x].inRange(l, r)) {
            tree[x].isChange = true;
            tree[x].add = 0;
            tree[x].change = val;
            //区间求和
            tree[x].value = val * tree[x].size();
            //区间求Max
            // tree[x].value = val;
            return;
        }
        push_down(x);
        change(l, r, val, x * 2);
        change(l, r, val, x * 2 + 1);
        push_up(x);
    }

    T query(int l, int r, int x = 1) {
        if (tree[x].outOfRange(l, r)) {
            return 0;
        }
        if (tree[x].inRange(l, r)) {
            return tree[x].value;
        }
        push_down(x);
        return query(l, r, x * 2) + query(l, r, x * 2 + 1);
//        return max(query(l, r, x * 2), query(l, r, x * 2 + 1));
    }
};

#endif
