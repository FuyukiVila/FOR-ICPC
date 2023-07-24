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

struct edge {
    int to{};
    ll value{};
    bool vis{false};

    edge(int _to, ll _v) : to{_to}, value{_v} {}
};

auto genshin_start() {
    unordered_map<ll, ll> p;
    int n, m;
    cin >> n >> m;
    vector<vector<edge> > e(n + 1);
    vector<bool> vis(n + 1);
    queue<tuple<int, ll, int>> q;
    for (int i = 1; i <= m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        e[a].emplace_back(b, c);
        e[b].emplace_back(a, -c);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            q.emplace(i, 0, -1);
            while (!q.empty()) {
                int id = get<0>(q.front());
                ll value = get<1>(q.front());
                int last = get<2>(q.front());
                q.pop();
                if (!vis[id]) {
                    vis[id] = true;
                    p[id] = value;
                } else {
                    if (p[id] != value) {
                        cout << "NO\n";
                        return;
                    }
                }
                for (auto &[to, v, _vis]: e[id]) {
                    if (_vis) {
                        continue;
                    } else {
                        _vis = true;
                        if (to == last) {
                            continue;
                        }
//                        dbg(id,x.to);
//                        dbg(value+x.value);
                        q.emplace(to, v + value, id);
                    }
                }
            }
        }
    }
    cout << "YES\n";
}

signed main() {
    GKD;
    auto T{1};
    cin >> T;
    while (T--) genshin_start();
    return 0;
}