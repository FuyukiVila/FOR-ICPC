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


// <>内为Typename 整型均匀分布参数为左右闭区间,实型为左闭右开,正态分布中为均值和标准差。
std::default_random_engine eng(std::random_device());

std::uniform_int_distribution<ll> ranint(1, 1e18);
std::uniform_real_distribution<double> rd2(1, 1e18);
std::normal_distribution<double> rd3(9, 999);

//为什么要演奏春日影！
struct node {
    int pos;
    char c;

    bool operator<(const node &p) const {
        return c < p.c;
    }
};
    0
void haruhikage_start(int testCase) {
    int n;
    cin >> n;
    vector<node> s(n + 1);
    deque<node> q;
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        s[i] = {i, c};
        while (!q.empty() && q.back().c < c)q.pop_back();
        q.push_back(s[i]);
    }
    for (int i = 0, j = q.size() - 1; i < j; i++, j--) {
        swap(s[q[i].pos], s[q[j].pos]);
    }
    int step = 0;
    for (int i = 1; i < q.size(); i++) {
        if (q[i].c != q.front().c) {
            step++;
        }
    }
    for (int i = 2; i <= n; i++) {
        if (s[i] < s[i - 1]) {
            cout << -1 << '\n';
            return;
        }
    }
    cout << step << '\n';
}

signed main() {
    GKD;
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        haruhikage_start(i);
    }
    return 0;
}