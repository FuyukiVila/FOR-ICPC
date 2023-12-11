#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
#define clr(a, b) memset(a, b, sizeof(a))

#include <bits/stdc++.h>

#define dbg(x...)                                                              \
    do {                                                                       \
        std::cout << #x << " -> ";                                             \
        err(x);                                                                \
    } while (0)

void err() { std::cout << std::endl; }

template<class T, class... Ts>
void err(T arg, Ts &...args) {
    std::cout << arg << ' ';
    err(args...);
}

using namespace std;
using ll = long long;
using ull = unsigned long long;
template<typename T, typename K> using umap = unordered_map<T, K>;
template<class T> using uset = unordered_set<T>;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;
ll mod = 0;

ll qpow(ll _a, ll _n, ll _mod = mod) {
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

constexpr int N = 1e7 + 100;
int minp[N];
vector<int> primes;
bool st[N];

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

std::random_device rd;
std::default_random_engine eng(rd());
std::uniform_int_distribution<ll> ranint(1, 1e18);

// 玩原神导致的
ll a[200005], b[200005], c[200005];
ll error[200005][2];
vector<int> e[200005];
ll ans;

void dfs(int now, int fa) {
    if (now != 1) a[now] = min(a[now], a[fa]);
    error[now][b[now]] += (b[now] != c[now]);
    for (auto const &x: e[now]) {
        if (x == fa)continue;
        dfs(x, now);
        error[now][0] += error[x][0], error[now][1] += error[x][1];
    }
    ll t = min(error[now][0], error[now][1]);
    ans += t * 2 * a[now];
    error[now][0] -= t, error[now][1] -= t;
}

void genshin_start() {
    int n;
    cin >> n;
    int s1 = 0, s2 = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> c[i];
        s1 += b[i], s2 += c[i];
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        e[x].emplace_back(y);
        e[y].emplace_back(x);
    }
    if (s1 != s2) {
        cout << -1 << '\n';
        return;
    }
    dfs(1, 0);
    cout << ans << '\n';
}

signed main() {
    GKD;
    auto T = 1;
//    cin >> T;
    while (T--)
        genshin_start();
    return 0;
}