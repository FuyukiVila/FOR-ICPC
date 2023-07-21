
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

struct node {
    int id;
    int value;

    constexpr bool operator<(const node &b) const {
        return value < b.value;
    }
};


auto genshin_start() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<bool> vis(m + 1, false);
    vector<priority_queue<node>> q(n + 1);
    set<int> ans;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            q[i].push({j, x});
        }
    }
    int pos = k % n;
    for (; k > 0; k--) {
        if (pos == 0)pos = n;
        while (vis[q[pos].top().id])q[pos].pop();
        vis[q[pos].top().id] = true;
        ans.insert(q[pos].top().id);
        pos--;
    }
    for (auto x: ans) {
        cout << x << ' ';
    }
    cout << '\n';
}

signed main() {
    GKD;
    auto T{1};
    cin >> T;
    while (T--) genshin_start();
    return 0;
}