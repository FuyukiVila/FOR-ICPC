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

struct point {
    double x, y;

    bool operator<(const point &p) const {
        return x < p.x || (x == p.x && y > p.y);
    }

    bool operator==(const point &p) const {
        return x == p.x && y == p.y;
    }

    bool operator<=(const point &p) const {
        return (x == p.x && y == p.y) || (x < p.x || (x == p.x && y > p.y));
    }
};

struct line {
    int id;
    double k, b;

    bool operator<(const line &p) const {
        return k < p.k || (k == p.k && b > p.b);
    }

    //求交点
    point get(const line &p) const {
        point ret;
        ret.x=((double)p.b-(double)b)/((double)k-(double)p.k);
        ret.y=p.k*ret.x+p.b;
        return ret;
    }
};


inline void init() {
    /*Init Here*/
}

void idol_produce(int testCase) {
    /*Code Here*/
    int n;
    cin >> n;
    vector<line> a(n + 1);
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        a[i].id = i;
        a[i].k = x;
        a[i].b = y;
    }
    sort(a.begin() + 1, a.end());
    vector<line> lines{a[1]};
    for (int i = 2; i <= n; i++) {
        if (a[i].k == a[i - 1].k) continue;
        while (lines.size() > 1 &&
               lines[lines.size() - 1].get(lines[lines.size() - 2]) <= a[i].get(lines[lines.size() - 2])) {
            lines.pop_back();
        }

        lines.emplace_back(a[i]);
    }
    sort(lines.begin(), lines.end(), [&](line a, line b) {
        return a.id < b.id;
    });
    for (auto const &x: lines) {
        cout << x.id << ' ';
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
