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
//#define LOCAL
//#define PRIME

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

#ifdef PRIME

const int N = 1e7 + 100;
vector<int> minp(N);
vector<int> primes;
bitset<N> st;

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

#endif

const int N = 2e5 + 1;


inline void init() {
    /*Init Here*/
}

int tr[300000];
int n, q;

int lowbit(int x) { return x & -x; }

void add(int x, int v) {
    for (; x <= n; x += lowbit(x)) {
        tr[x] += v;
    }
}

int get_prefix(int x) {
    int res = 0;
    while (x > 0) {
        res += tr[x];
        x -= lowbit(x);
    }
    return res;
}

int find(int x) {
    int l = 0, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (get_prefix(mid) >= x) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return r;
}

void idol_produce(int testCase) {
    /*Code Here*/
    cin >> n >> q;
    vector<int> a(n + 1);
    int tmp = 0;
    set<int> s;
    bitset<N> bs;
    bs.set(0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        tmp += a[i];
        add(i, a[i]);
        bs.set(tmp);
        if (a[i] == 0) s.insert(i);
    }
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            cin >> x;
            if (x == 0) {
                if (!s.empty()) {
                    cout << *s.begin() << ' ' << *s.begin() << '\n';
                } else {
                    cout << -1 << '\n';
                }
                continue;
            }

            auto tmp = ((bs >> x) & bs);
            if (tmp.any()) {
                int s1 = tmp._Find_first();
                int l = find(s1) + 1;
                int r = find(s1 + x);
                cout << l << ' ' << r << '\n';
            } else {
                cout << -1 << '\n';
            }
        } else if (op == 2) {
            int i, v;
            cin >> i >> v;
            if (a[i] == v) continue;
            if (a[i] == 0) {
                s.erase(i);
                int p = get_prefix(i);
                int d = N - p - 1;
                bs = (bs << d >> d) | (bs >> p << (p + v - a[i]));
            } else {
                int p = get_prefix(i) + 1;
                int d = N - p;
                bs = (bs << d >> d) | (bs >> p << (p + v - a[i]));
            }
            add(i, v - a[i]);
            a[i] = v;
            if (v == 0) s.insert(i);
        }
    }
}

signed main() {
    GKD;
    init();
    int T = 1;
//    cin >> T;
    for (int i = 1; i <= T; i++) {
        idol_produce(i);
    }
    return 0;
}
