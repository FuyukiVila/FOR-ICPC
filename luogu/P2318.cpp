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

inline void init() {
    /*Init Here*/
}

struct node {
    int id, value;

    bool operator<(const node &a) const { return id < a.id; }
};

struct location {
    int count, id;
};

void idol_produce(int testCase) {
    /*Code Here*/
    int n, m;
    cin >> n >> m;
    int size = 0;
    map<int, location> loc;
    map<int, set<node> > cnt;
    int ans = 0;
    int id = 0;
    for (int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        if (loc.count(x)) {
            ans++;
            int count = loc[x].count;
            int id = loc[x].id;
            cnt[count + 1].insert((node) {id, x});
            cnt[count].erase((node) {id, x});
            if (cnt[count].empty()) cnt.erase(count);
            loc[x].count++;
        } else {
            if (size == n) {
                int p = cnt.begin()->first;
                loc.erase(cnt[p].begin()->value);
                cnt[p].erase(*cnt[p].begin());
                if (cnt[p].empty()) {
                    cnt.erase(p);
                }
            } else {
                size++;
            }
            cnt[1].insert((node) {++id, x});
            loc[x] = (location) {1, id};
        }
    }
    cout << ans << '\n';
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
