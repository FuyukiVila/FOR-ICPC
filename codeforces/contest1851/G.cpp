#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
#define clr(a, b) memset(a, b, sizeof(a))

#include <bits/stdc++.h>

#define dbg(x...) \
    do { \
        std::cout << #x << " -> "; \
        err(x); \
    } while (0)

void err() {
    std::cout << std::endl;
}

template<class T, class... Ts>
void err(T arg, Ts &... args) {
    std::cout << arg << ' ';
    err(args...);
}

using namespace std;
using ll = long long;
using ull = unsigned long long;
template<typename T>
using umap = unordered_map<T, T>;
template<typename T>
using uset = unordered_set<T, T>;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;
const int mod = 0;

template<typename T>
inline constexpr T qpow(T _a, T _n, T _mod = mod) {
    T ans = 1;
    while (_n) {
        if (_n & 1) ans *= _a;
        _n >>= 1;
        _a *= _a;
        if (_mod > 0) {
            ans %= _mod;
            _a %= _mod;
        }
    }
    return ans;
}

constexpr int N = 1e7 + 100;
int minp[N];
vector<int> primes;
bool st[N];

void get_primes(int n) {
    for (int i = 2; i <= n; i++) {
        if (!st[i]) minp[i] = i, primes.emplace_back(i);
        for (int j = 0; primes[j] * i <= n; j++) {
            int t = primes[j] * i;
            st[t] = true;
            minp[t] = primes[j];
            if (i % primes[j] == 0) break;
        }
    }
}

struct DSU {
    std::vector<int> f, siz;

    explicit DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }

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

//玩原神导致的
namespace solve {
    vector<int> h;

    void init(int n) { h.resize(n, 0); };

    struct edge {
        int u{}, v{};

        bool operator<(const edge &b) const {
            return max(h[u], h[v]) < max(h[b.u], h[b.v]);
        }

        int getMax() const {
            return max(h[u], h[v]);
        }

    };

    struct query {
        int id{};
        int u{}, v{};
        int e{};

        bool operator<(const query &b) const {
            return h[u] + e < h[b.u] + b.e;
        }

    };
}


void genshin_start() {
    int n, m;
    using namespace solve;
    cin >> n >> m;
    init(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    vector<edge> e(m);
    for (int i = 0; i < m; i++) {
        cin >> e[i].u >> e[i].v;
        e[i].u--;
        e[i].v--;
    }
    sort(e.begin(), e.end());
    int q;
    cin >> q;
    vector<query> qry(q);
    vector<bool> ans(q, false);
    for (int i = 0; i < q; i++) {
        cin >> qry[i].u >> qry[i].v >> qry[i].e;
        qry[i].id = i;
        qry[i].u--;
        qry[i].v--;
    }
    sort(qry.begin(), qry.end());
    DSU dsu(n);
    int j = 0;
    for (auto &i: qry) {
        int limit = i.e + h[i.u];
        while (j < m && limit >= e[j].getMax()) {
            dsu.merge(e[j].u, e[j].v);
            j++;
        }
        if (dsu.same(i.u, i.v)) {
            ans[i.id] = true;
        }
    }
    for (auto const &x: ans) {
        if (x) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

signed main() {
    GKD;
    auto T = 1;
    cin >> T;
    while (T--) genshin_start();
    return 0;
}