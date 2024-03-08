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

inline ll qpow(ll _a, ll _n, ll _mod = mod) {
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
vector<vector<int> > male(1e5 + 100);
vector<vector<int> > female(1e5 + 100);
vector<vector<double> > man(1e5 + 100);
vector<vector<double> > woman(1e5 + 100);

void genshin_start(int testCase) {
    int n, m, k;
    cin >> n >> m >> k;
    cout << fixed << setprecision(10);
    cout << "float\n";
    for (int i = 1; i <= k; i++) {
        int x, y;
        cin >> x >> y;
        female[x].emplace_back(y);
        male[y].emplace_back(x);
    }
    double ans = 0;
    for (int i = 1; i <= n; i++) {
        for (auto const &x: female[i]) {
            woman[x].emplace_back(1.0 / female[i].size());
        }
    }
    for (int i = 1; i <= m; i++) {
        for (auto const &x: male[i]) {
            man[x].emplace_back(1.0 / male[i].size());
        }
    }
    double ans1 = 0, ans2 = 0;
    for (int i = 1; i <= n; i++) {
        if (man[i].empty()) {
            continue;
        }
        double tmp = 1;
        for (auto const &x: man[i]) {
            tmp *= (1.0 - x);
        }
        ans1 += (1.0 - tmp);
    }
    for (int i = 1; i <= m; i++) {
        if (woman[i].empty()) {
            continue;
        }
        double tmp = 1;
        for (auto const &x: woman[i]) {
            tmp *= (1.0 - x);
        }
        ans2 += (1.0 - tmp);
    }
    cout << ans1 << ' ' << ans2 << '\n';
}

signed main() {
    GKD;
    int T = 1;
//    cin >> T;
    for (int i = 1; i <= T; i++) {
        genshin_start(i);
    }
    return 0;
}

