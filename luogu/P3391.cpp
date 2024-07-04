/*
  ______                 _    _  __      ___ _
 |  ____|               | |  (_) \ \    / (_) |
 | |__ _   _ _   _ _   _| | ___   \ \  / / _| | __ _
 |  __| | | | | | | | | | |/ / |   \ \/ / | | |/ _` |
 | |  | |_| | |_| | |_| |   <| |    \  /  | | | (_| |
 |_|   \__,_|\__, |\__,_|_|\_\_|     \/   |_|_|\__,_|
              __/ |
             |___/
*/

#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
#define clr(a, b) memset(a, b, sizeof(a))
#define cpy(a, b) memcpy(a, b, sizeof(a))

#include <bits/stdc++.h>

#ifdef LOCAL

#define dbg(x...)                                                              \
    do {                                                                       \
        std::cout << #x << " -> ";                                             \
        err(x);                                                                \
    } while (0);
#else
#define dbg(x...) 114514;
#endif

void err() { std::cout << std::endl; }

template<class T, class... Ts>
void err(T arg, Ts &...args) {
    std::cout << arg << ' ';
    err(args...);
}

using namespace std;
using ll = long long;
using ull = unsigned long long;
const int INF = 0x3f3f3f3f;
ll mod = 0;

inline ll qpow(ll _a, ll _n, ll _mod = mod) {
    ll ans = 1;
    while (_n) {
        if (_n & 1)
            ans *= _a;
        _n >>= 1;
        _a *= _a;
        if (_mod > 0) {
            ans %= _mod;
            _a %= _mod;
        }
    }
    return ans;
}

constexpr int _N = 1e7 + 100;
vector<int> minp(_N);
vector<int> primes;
bitset<_N> st;

void get_primes(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i])
            minp[i] = i, primes.emplace_back(i);
        for (int j = 0; primes[j] * i <= n; j++) {
            int t = primes[j] * i;
            st[t] = true;
            minp[t] = primes[j];
            if (i % primes[j] == 0)
                break;
        }
    }
}

const int N = 500000;
int n, m;

struct Node {
    int s[2], p, v;
    int sz;
    bool rev;

    void init(int _v, int _p) { v = _v, p = _p, sz = 1; }
} tr[N];

int root, idx;

void pushup(int u) { tr[u].sz = tr[tr[u].s[0]].sz + tr[tr[u].s[1]].sz + 1; }

void pushdown(int u) {
    if (tr[u].rev) {
        swap(tr[u].s[0], tr[u].s[1]);
        tr[tr[u].s[0]].rev ^= 1;
        tr[tr[u].s[1]].rev ^= 1;
        tr[u].rev = 0;
    }
}

void rotate(int u) {
    int v = tr[u].p, w = tr[v].p;
    int k = tr[v].s[1] == u;
    tr[w].s[tr[w].s[1] == v] = u;
    tr[u].p = w;
    tr[v].s[k] = tr[u].s[k ^ 1];
    tr[tr[u].s[k ^ 1]].p = v;
    tr[u].s[k ^ 1] = v;
    tr[v].p = u;
    pushup(v);
    pushup(u);
}

void splay(int u, int k) {
    while (tr[u].p != k) {
        int v = tr[u].p, w = tr[v].p;
        if (w != k)
            (tr[v].s[1] == u) ^ (tr[w].s[1] == v) ? rotate(u) : rotate(v);
        rotate(u);
    }
    if (k == 0)
        root = u;
}

void insert(int v) {
    int u = root, p = 0;
    while (u) {
        p = u;
        u = tr[u].s[v > tr[u].v];
    }
    u = ++idx;
    tr[u].init(v, p);
    if (p)
        tr[p].s[v > tr[p].v] = u;
    splay(u, 0);
}

int kth(int k) {
    int u = root;
    while (true) {
        pushdown(u);
        if (tr[tr[u].s[0]].sz + 1 == k)
            return u;
        else if (tr[tr[u].s[0]].sz >= k)
            u = tr[u].s[0];
        else
            k -= tr[tr[u].s[0]].sz + 1, u = tr[u].s[1];
    }
    return -1;
}

vector<int> ans;

void dfs(int u) {
    if (!u) return;
    pushdown(u);
    dfs(tr[u].s[0]);
    if (tr[u].v >= 1 && tr[u].v <= n) ans.push_back(tr[u].v);
    dfs(tr[u].s[1]);
}

inline void init() {
    /*Init Here*/
}

void idol_produce(int testCase) {
    /*Code Here*/
    cin >> n >> m;
    for (int i = 0; i <= n + 1; i++) {
        insert(i);
    }
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        l = kth(l), r = kth(r + 2);
        splay(l, 0), splay(r, l);
        tr[tr[r].s[0]].rev ^= 1;
    }
    dfs(root);
//    reverse(ans.begin(), ans.end());
    for (auto x: ans) {
        cout << x << ' ';
    }
}

signed main() {
    GKD;
    init();
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; i++) {
        idol_produce(i);
    }
    return 0;
}
