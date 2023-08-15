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

std::random_device rd;
std::default_random_engine eng(rd());
std::uniform_int_distribution<ll> ranint(1, 1e18);

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

void genshin_start() {
    int n;
    cin >> n;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    vector<bitset<5005>> ok(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            ok[i][j] = true;
        }
    }
    vector<DSU> dsu(n + 1, DSU(n + 2));
    for (int i = 1; i <= n; i++) {
        int l = i, r = i;
        int cur = p[i];
        while (l >= 1 && r <= n) {
            int nl = l, nr = r;
            while (nr + 1 <= n) {
                nr++;
                if (p[nr] < cur) {
                    nr--;
                    break;
                }
            }
            while (nl - 1 >= 1) {
                nl--;
                if (p[nl] > cur) {
                    nl++;
                    break;
                }
            }
            for (int k = nl; k <= l; k++) {
                for (int j = dsu[k].find(r); j <= nr; j = dsu[k].find(j)) {
                    ok[k][j] = false;
                    dsu[k].merge(j + 1, j);
                }
            }
            l = nl - 1, r = nr + 1;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += ok[i].count();
    }
    cout << ans << '\n';
}

signed main() {
    GKD;
    auto T = 1;
    cin >> T;
    while (T--) genshin_start();
    return 0;
}