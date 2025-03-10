#include <bits/stdc++.h>

namespace pst {

    using namespace std;
    constexpr int MAXN = 1e6 + 10;

    template<class T, class V>
    class IPersistentSegmentTree {
    protected:
        typedef T element_type;
        typedef V value_type;

        struct node {
            size_t ls, rs;
            value_type value;
        };

        size_t length;
        size_t total = 0;
        vector<node> tree;

        virtual value_type assign_value(const std::vector<element_type> &arr,
                                        size_t x) = 0;

        virtual value_type merge_value(value_type x, value_type y) = 0;

        void push_up(int node) {
            tree[node].value =
                    merge_value(tree[tree[node].ls].value, tree[tree[node].rs].value);
        }

        void build(const std::vector<element_type> &arr, size_t &node, size_t l,
                   size_t r) {
            node = ++total;
            if (l == r) {
                tree[node].value = assign_value(arr, l);
                return;
            }
            int mid = (l + r) >> 1;
            build(arr, tree[node].ls, l, mid);
            build(arr, tree[node].rs, mid + 1, r);
            push_up(node);
        }

        size_t _update(size_t &node, size_t last, size_t pos, element_type val,
                       size_t l, size_t r) {
            node = ++total;
            tree[node] = tree[last];
            if (l == r) {
                tree[node].value = val;
                return node;
            }
            int mid = (l + r) >> 1;
            if (pos <= mid)
                _update(tree[node].ls, tree[last].ls, pos, val, l, mid);
            else
                _update(tree[node].rs, tree[last].rs, pos, val, mid + 1, r);
            push_up(node);
            return node;
        }

        value_type _get(size_t node, size_t pos, size_t l, size_t r) {
            if (l == r) return tree[node].value;
            int mid = (l + r) >> 1;
            if (pos <= mid)
                return _get(tree[node].ls, pos, l, mid);
            else
                return _get(tree[node].rs, pos, mid + 1, r);
        }

    public:
        // 保存版本信息
        vector<size_t> dir;

        size_t update(size_t &node, size_t last, size_t pos, element_type val) {
            return _update(node, last, pos, val, 1, length);
        }

        value_type get(size_t node, size_t pos) {
            return _get(node, pos, 1, length);
        }
    };

    class PersistentSegmentTree
            : public IPersistentSegmentTree<long long, long long> {
    private:
        value_type assign_value(const std::vector<element_type> &arr, size_t x) {
            return arr[x];
        }

        value_type merge_value(value_type x, value_type y) { return x + y; }

    public:
        explicit PersistentSegmentTree(const std::vector<element_type> &arr) {
            length = arr.size() - 1;
            dir.resize(MAXN);
            tree.resize(MAXN << 5);
            build(arr, dir[0], 1, length);
        }
    };

    class KthMinTree : public IPersistentSegmentTree<int, int> {
    private:
        value_type assign_value(const std::vector<element_type> &arr, size_t x) {
            return arr[x];
        }

        value_type merge_value(value_type x, value_type y) { return x + y; }

        value_type _kthMin(size_t prev, size_t now, size_t l, size_t r, size_t k) {
            if (l == r) return l;
            int mid = (l + r) >> 1;
            int x = tree[tree[now].ls].value - tree[tree[prev].ls].value;
            if (k <= x)
                return _kthMin(tree[prev].ls, tree[now].ls, l, mid, k);
            else
                return _kthMin(tree[prev].rs, tree[now].rs, mid + 1, r, k - x);
        }

        value_type _lessOrEqual(size_t prev, size_t now, size_t l, size_t r, element_type k) {
            if (l == r) {
                return tree[now].value - tree[prev].value;
            }
            int mid = (l + r) >> 1;
            int ans = 0;
            if (k <= mid) {
                ans += _lessOrEqual(tree[prev].ls, tree[now].ls, l, mid, k);
            } else {
                ans += tree[tree[now].ls].value - tree[tree[prev].ls].value;
                ans += _lessOrEqual(tree[prev].rs, tree[now].rs, mid + 1, r, k);
            }
            return ans;
        }

    public:

        KthMinTree() {
            tree.resize(MAXN << 5);
            dir.resize(MAXN);
        }

        explicit KthMinTree(const std::vector<element_type> &arr) {
            length = arr.size() - 1;
            dir.resize(MAXN);
            tree.resize(MAXN << 5);
            unordered_map<element_type, value_type> cnt;
            for (int i = 1; i <= length; i++) {
                update(dir[i], dir[i - 1], arr[i], cnt[arr[i]] + 1);
                cnt[arr[i]] += 1;
            }
        }

        void resize(const std::vector<element_type> &arr) {
            total = 0;
            length = arr.size() - 1;
            unordered_map<element_type, int> cnt;
            for (int i = 1; i <= length; i++) {
                update(dir[i], dir[i - 1], arr[i], cnt[arr[i]] + 1);
                cnt[arr[i]] += 1;
            }
        }

        value_type kthMin(size_t l, size_t r, size_t k) {
            return _kthMin(dir[l - 1], dir[r], 1, length, k);
        }

        value_type lessOrEqual(size_t l, size_t r, element_type k) {
            return _lessOrEqual(dir[l - 1], dir[r], 1, length, k);
        }
    };
}  // namespace pst