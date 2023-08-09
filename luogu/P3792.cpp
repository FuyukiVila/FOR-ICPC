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

//玩原神导致的
std::random_device rd;
std::mt19937 eng(rd());
std::uniform_int_distribution<int> ranint(1, 1e9);
const int MAXN = 500005;
int a[MAXN];
int mp[MAXN];
ll cur[MAXN];
int n, m;
struct node {
    int l{}, r{};
    int minn{}, maxn{};
    ll sum{};
} d[MAXN * 4];

void build(int s = 1, int t = n, int p = 1) {
    d[p].l = s, d[p].r = t;
    if (s == t) {
        d[p].maxn = d[p].minn = a[s];
        if (a[s] > n) {
            d[p].sum = 0;
        } else {
            d[p].sum = mp[a[s]];
        }
        return;
    }
    int mid = (s + t) / 2;
    build(s, mid, p * 2), build(mid + 1, t, p * 2 + 1);
    d[p].sum = d[p * 2].sum + d[p * 2 + 1].sum;
    d[p].maxn = max(d[p * 2].maxn, d[p * 2 + 1].maxn);
    d[p].minn = min(d[p * 2].minn, d[p * 2 + 1].minn);
}

void update(int pos, int k, int p = 1) {
    if (pos < d[p].l || pos > d[p].r) {
        return;
    }

    if (d[p].l == d[p].r) {
        d[p].minn = d[p].maxn = k;
        d[p].sum = mp[k];
        return;
    }

    update(pos, k, p * 2), update(pos, k, p * 2 + 1);
    d[p].sum = d[p * 2].sum + d[p * 2 + 1].sum;
    d[p].maxn = max(d[p * 2].maxn, d[p * 2 + 1].maxn);
    d[p].minn = max(d[p * 2].minn, d[p * 2 + 1].minn);
}

pair<int, int> getMinMax(int l, int r, int p = 1) {
    if (l <= d[p].l && r >= d[p].r) {
        return {d[p].minn, d[p].maxn};
    }
    if (l > d[p].r || r < d[p].l) {
        return {INF, 0};
    }
    auto f = getMinMax(l, r, p * 2);
    auto s = getMinMax(l, r, p * 2 + 1);
    auto minmax = make_pair(min(f.first, s.first), max(f.second, s.second));
    return minmax;
}

ll getSum(int l, int r, int p = 1) {
    if (l <= d[p].l && r >= d[p].r) {
        return d[p].sum;
    }
    if (l > d[p].r || r < d[p].l) {
        return 0;
    }
    return getSum(l, r, p * 2) + getSum(l, r, p * 2 + 1);
}

void genshin_start() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        mp[i] = ranint(eng);
        cur[i] = cur[i - 1] + mp[i];
    }
    build(1, n, 1);
    for (int i = 1; i <= m; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int pos, x;
            cin >> pos >> x;
            update(pos, x);
        } else {
            int l, r;
            cin >> l >> r;
            if (l == r) {
                cout << "damushen\n";
                continue;
            }
            auto minmax = getMinMax(l, r);
            int minn = minmax.first;
            int maxn = minmax.second;
            if (maxn - minn != r - l || cur[maxn] - cur[minn - 1] != getSum(l, r)) {
                cout << "yuanxing\n";
            } else {
                cout << "damushen\n";
            }
        }
    }
}

signed main() {
    GKD;
    auto T = 1;
//    cin >> T;
    while (T--) genshin_start();
    return 0;
}