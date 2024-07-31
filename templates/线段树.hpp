#ifndef __ISEGMENT_TREE_HPP
#define __ISEGMENT_TREE_HPP

#include <vector>
#include <cassert>

template<class T, class V>
class ISegmentTree {

protected:
    typedef T element_type;
    typedef V value_type;

    struct node {
        value_type value;
        element_type add;
        element_type change;
        bool isChange{false};
        size_t id{0};
        size_t l{0}, r{0};

        constexpr bool inRange(int l, int r) {
            return this->l >= l && this->r <= r;
        }

        constexpr bool outOfRange(int l, int r) {
            return this->l > r || this->r < l;
        }

        constexpr size_t size() { return r - l + 1; }
    };

    constexpr static size_t ls(size_t x) { return 2 * x; }

    constexpr static size_t rs(size_t x) { return 2 * x + 1; }

    std::vector<node> tree;

    //you should modify these functions
    virtual value_type assign_value(const std::vector<element_type> &arr, size_t x) = 0;

    virtual value_type merge_value(value_type x, value_type y) = 0;

    virtual void add_value(size_t x, element_type add) = 0;

    virtual void change_value(size_t x, element_type change) = 0;

    void add_tag(size_t x, element_type add) {
        add_value(x, add);
        tree[x].add += add;
    }

    void change_tag(size_t x, element_type change) {
        change_value(x, change);
        tree[x].change = change;
        tree[x].isChange = true;
        tree[x].add = 0;
    }

    void push_down(size_t x) {
        if (tree[x].isChange) {
            change_tag(ls(x), tree[x].change);
            change_tag(rs(x), tree[x].change);
            tree[x].isChange = false;
            tree[x].change = 0;
        }
        if (tree[x].add) {
            add_tag(ls(x), tree[x].add);
            add_tag(rs(x), tree[x].add);
            tree[x].add = 0;
        }
    }

    void push_up(size_t x) {
        tree[x].value = merge_value(tree[ls(x)].value, tree[rs(x)].value);
    }

    void build(const std::vector<element_type> &arr, size_t x, size_t l, size_t r) {
        tree[x].id = x;
        tree[x].l = l, tree[x].r = r;
        if (l == r) {
            // how to assign value
            tree[x].value = assign_value(arr, l);
            return;
        }
        size_t m = (l + r) >> 1;
        build(arr, ls(x), l, m);
        build(arr, rs(x), m + 1, r);
        push_up(x);
    }

    // 区间加
    void add(size_t l, size_t r, T val, size_t x = 1) {
        if (tree[x].inRange(l, r)) {
            add_tag(x, val);
            return;
        }
        push_down(x);
        if (!tree[ls(x)].outOfRange(l, r))add(l, r, val, ls(x));
        if (!tree[rs(x)].outOfRange(l, r))add(l, r, val, rs(x));
        push_up(x);
    }

    // 区间修改
    void change(size_t l, size_t r, T val, size_t x = 1) {
        if (tree[x].inRange(l, r)) {
            change_tag(x, val);
            return;
        }
        push_down(x);
        if (!tree[ls(x)].outOfRange(l, r))change(l, r, val, ls(x));
        if (!tree[rs(x)].outOfRange(l, r))change(l, r, val, rs(x));
        push_up(x);
    }

    // 区间查询
    value_type query(size_t l, size_t r, size_t x = 1) {
        if (tree[x].inRange(l, r)) {
            return tree[x].value;
        }
        push_down(x);
        if (tree[ls(x)].outOfRange(l, r))return query(l, r, rs(x));
        if (tree[rs(x)].outOfRange(l, r))return query(l, r, ls(x));
        return merge_value(query(l, r, ls(x)), query(l, r, rs(x)));
    }

public:

    // 区间加
    void add(int l, int r, element_type val) {
        assert(l <= r);
        add(l, r, val, 1);
    }

    // 区间修改
    void change(int l, int r, element_type val) {
        assert(l <= r);
        change(l, r, val, 1);
    }

    // 区间查询
    value_type query(int l, int r) {
        assert(l <= r);
        return query(l, r, 1);
    }
};

#endif

class SegmentSumTree : public ISegmentTree<long long, long long> {
private:
    value_type assign_value(const std::vector<element_type> &arr, size_t x) override {
        return arr[x];
    }

    value_type merge_value(value_type x, value_type y) override {
        return x + y;
    }

    void add_value(size_t x, value_type val) override {
        tree[x].value += val * tree[x].size();
    }

    void change_value(size_t x, value_type val) override {
        tree[x].value = val * tree[x].size();
    }

public:
    explicit SegmentSumTree(const std::vector<element_type> &arr) {
        tree.resize(arr.size() * 4 + 1);
        build(arr, 1, 1, arr.size() - 1);
    }
};

class SegmentMaxTree : public ISegmentTree<long long, long long> {
private:
    value_type assign_value(const std::vector<element_type> &arr, size_t x) override {
        return arr[x];
    }

    value_type merge_value(value_type x, value_type y) override {
        return std::max(x, y);
    }

    void add_value(size_t x, value_type val) override {
        tree[x].value += val;
    }

    void change_value(size_t x, value_type val) override {
        tree[x].value = val;
    }

public:
    explicit SegmentMaxTree(const std::vector<element_type> &arr) {
        tree.resize(arr.size() * 4 + 1);
        build(arr, 1, 1, arr.size() - 1);
    }
};

class SegmentMinTree : public ISegmentTree<long long, long long> {
private:
    value_type assign_value(const std::vector<element_type> &arr, size_t x) override {
        return arr[x];
    }

    value_type merge_value(value_type x, value_type y) override {
        return std::min(x, y);
    }

    void add_value(size_t x, value_type val) override {
        tree[x].value += val;
    }

    void change_value(size_t x, value_type val) override {
        tree[x].value = val;
    }

public:
    explicit SegmentMinTree(const std::vector<element_type> &arr) {
        tree.resize(arr.size() * 4 + 1);
        build(arr, 1, 1, arr.size() - 1);
    }
};