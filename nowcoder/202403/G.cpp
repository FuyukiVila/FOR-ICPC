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
struct node {
    int x, y, z;
};
vector<node> a(55);
int n;

int cmp(int x, int y) {
    if (x > y) {
        return 1;
    }
    return 0;
}

bool check(vector<int> &s) {
    for (int i = 1; i <= n; i++) {
        if (cmp(s[a[i].x], s[a[i].y]) != a[i].z) {
            return false;
        }
    }
    return true;
}

void genshin_start(int testCase) {
    cin >> n;
    a.clear();
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y >> a[i].z;
    }
    vector<int> s{0, 1, 2, 3};
    for (int i = 1; i <= 6; i++) {
        if (check(s)) {
            cout << "Yes\n";
            return;
        }
        next_permutation(s.begin() + 1, s.end());
    }
    s = {0, 1, 1, 2};
    for (int i = 1; i <= 6; i++) {
        if (check(s)) {
            cout << "Yes\n";
            return;
        }
        next_permutation(s.begin() + 1, s.end());
    }
    s = {0, 1, 2, 2};
    for (int i = 1; i <= 6; i++) {
        if (check(s)) {
            cout << "Yes\n";
            return;
        }
        next_permutation(s.begin() + 1, s.end());
    }
    s = {0, 1, 1, 1};

    if (check(s)) {
        cout << "Yes\n";
        return;
    }
    cout << "No\n";
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

