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
const int INF = 0x3f3f3f3f;
ll mod = 0;

ll qpow(ll _a, ll _n, ll _mod = mod) {
    ll ans = 1;
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
vector<int> minp(N);
vector<int> primes;
bitset<N> st;

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

//玩原神导致的
int ans = 10;
int a[11];
int n, m;
vector<pair<int, int> > s;

void dfs(int p) {
    if (p == m) {
        int tmp = 1;
        for (int i = 1; i <= n; i++) {
            if (a[i] > a[1]) {
                tmp++;
            }
        }
        ans = min(ans, tmp);
        return;
    }
    if (s[p].first == 1) {
        a[1] += 3;
        dfs(p + 1);
        a[1] -= 3;
    } else {
        int u = s[p].first, v = s[p].second;
        a[u] += 3;
        dfs(p + 1);
        a[u] -= 3;
        a[v] += 3;
        dfs(p + 1);
        a[v] -= 3;
        a[u] += 1, a[v] += 1;
        dfs(p + 1);
        a[u] -= 1, a[v] -= 1;
    }
};

void genshin_start(int testCase) {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    s.clear();
    ans = 10;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        if (u > v)swap(u, v);
        s.emplace_back(u, v);
    }
    sort(s.begin(), s.end());
    dfs(0);
    cout << ans << '\n';
}

signed main() {
    GKD;
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        genshin_start(i);
    }
    return 0;
}

