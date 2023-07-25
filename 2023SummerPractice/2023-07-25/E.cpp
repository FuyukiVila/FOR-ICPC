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
template<typename T>
using umap = unordered_map<T, T>;
template<class T>
using uset = unordered_set<T, T>;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;
const ll mod = 1e9 + 7;

template<typename T>
inline constexpr T qpow(T _a, T _n, T _mod = mod) {
    T ans = 1;
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

const int MAXN = 3005;
ll jc[MAXN];

void init() {
    jc[0] = 1;
    for (int i = 1; i <= MAXN - 2; i++) {
        jc[i] = jc[i - 1] * i % mod;
    }
}

ll A(ll n, ll m) {
    if (n < m) return 0;
    return jc[n] * qpow(jc[n - m], mod - 2) % mod;
}

map<vector<int>, bool> m;

//auto genshin_start() {
//    int n{};
//    ll div = 1, rec = 1,cnt = 0;
//    cin >> n;
//    for (int i{1}; i <= n; i++) {
//        cin >> a[i];
//    }
//    sort(a + 1, a + n + 1);
//    int _ = 0;
//    int _a[MAXN];
//    for (int i = 1; i <= n; i++) {
//        if (a[i] != a[i - 1]) {
//            _a[i] = ++_;
//        } else {
//            _a[i] = _;
//        }
//    }
//    for (int i = 1; i <= n; i++) {
//        a[i] = _a[i];
//    }
//    a[n + 1] = 2e9;a[0] =  -1;
//    for (int i = n; i >= 1; i--) {
//        if (a[i] != a[i + 1]) {
//            div = div * jc[rec] % mod;
//            rec = 1;
//            cnt ++;
//        } else {
//            rec++;
//        }
//    }
//    div = div*jc[rec] % mod;
//    cout << "?? " << div << ' ' << cnt << '\n';
//    for(int k = 1;k <= n;k ++){
//        cout << A(cnt,k)*qpow(div,mod - 2)%mod << '\n';
//    }
//    return;
//}
vector<int> a;

void dabiao(int n, int k) {
    vector<int> g;
    a.clear();
    for (int i = 2; i <= 3; i++) {
        a.push_back(i);
    }
    a.push_back(3);
    while(a.size() < n) a.push_back(4);
    m.clear();
    int cnt = 0;
    do {
        g.clear();
        for (int i = 0; i <= k - 1; i++) {
            if (i == 0) {
                g.push_back(a[i]);
                continue;
            }
            if (a[i] < g.back()) {
                g.push_back(g.back());
                continue;
            } else {
                g.push_back(a[i]);
            }
        }
        if (m[g] == 0) {
            cnt++;
            m[g] = 1;
        }
    } while (next_permutation(a.begin(), a.end()));
    cout << cnt << '\n';
}

ll dp[3005][3005];
//ll a[3005];
ll _a[3005];
map<ll, ll> cnt;
ll ans[3005];

//void solve() {
//    int n;
//    cin >> n;
//    for (int i = 1; i <= n; i++) {
//        cin >> a[i];
//    }
//    sort(a + 1, a + n + 1);
//    int _ = 0;
//    for (int i = 1; i <= n; i++) {
//        if (a[i] != a[i - 1]) {
//            _a[i] = ++_;
//        } else {
//            _a[i] = _;
//        }
//    }
//    vector<ll> v;
//    for (int i = 1; i <= n; i++) {
//        if (_a[i] != _a[i - 1]) {
//            v.push_back(_a[i]);
//        }
//        cnt[_a[i]]++;
//    }
//
//}

signed main() {
//    GKD;
//    auto T{1};
//    cin >> T;
//    while (T--) {
//        solve();
//    }
//    init();
    for (int n = 2; n <= 6; n++) {
        cout << "n == " << n << '\n';
        for (int k = 1; k <= n; k++) {
            dabiao(n, k);
        }
    }
    return 0;
}