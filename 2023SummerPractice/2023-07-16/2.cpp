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
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;
const ll mod = 1e9 + 7;

template<typename T>
inline constexpr T qpow(T a, T n) {
    T ans = 1;
    while (n) {
        if (n & 1) ans = (ans * a) % mod;
        n >>= 1;
        a = (a * a) % mod;
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
struct node {
    ll b, l, r;

    constexpr bool operator<(node const &y) const {
//        if (l == y.l && r == y.r) {
//            return b < y.b;
//        }
        if (l == y.l) {
            return r > y.r;
        } else {
            return l > y.l;
        }
    }
};

ll a[500005];
priority_queue<node> q;

void genshin_start() {
    int n, m;
    ll ans = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        int b, l, r;
        cin >> b >> l >> r;
        q.push({b, l, r});
    }
    ll zero = 0;
    while (!q.empty()) {
        auto x = q.top();
        q.pop();
        if (x.b == 0 || x.l > x.r) {
            continue;
        }
        int pos = max(x.l, zero + 1);
        if (pos > x.r)continue;
        if (pos != x.l) {
            q.push({x.b, pos, x.r});
            continue;
        }
        ll b = x.b;
        if (a[pos] > b) {
            a[pos] -= b;
            ans += b;
        } else {
            b -= a[pos];
            ans += a[pos];
            zero = pos;
            a[pos] = 0;
            if (b != 0)q.push({b, x.l + 1, x.r});
        }
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