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

inline

void init() {
    /*Init Here*/
}

struct SegTree {
    vector<ll> a;

    static int lowbit(int x) {
        return x & -x;
    }

    void add(int x, int k) {
        while (x < a.size()) {
            a[x] += k;
            x += lowbit(x);
        }
    }

    ll get(int x) {
        ll res = 0;
        while (x) {
            res += a[x];
            x -= lowbit(x);
        }
        return res;
    }
};

SegTree cnt;

SegTree value;
vector<ll> nums;

//离散化
int get_num(int x) {
    return lower_bound(nums.begin(), nums.end(), x) - nums.begin() + 1;
}

ll check(ll n) {
    ll p = 0, q = 0;
    if (n >= nums.back()) {
        p = 0;
    } else {
        p = cnt.get(nums.size()) - cnt.get(upper_bound(nums.begin(), nums.end(), n) - nums.begin());
    }
    if (n < nums[0]) {
        q = 0;
    } else {
        q = value.get(upper_bound(nums.begin(), nums.end(), n) - nums.begin());
    }
    return p * n + q;
}


void idol_produce(int testCase) {
    /*Code Here*/
    int n;
    cin >> n;
    vector<pair<int, int> > q;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        q.emplace_back(x, y);
        if (x == 1) nums.push_back(y);
    }
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    cnt.a.resize(nums.size() + 1);
    value.a.resize(nums.size() + 1);
    int maxn = 0;
    int f = 0;
    for (auto const &[x, y]: q) {
        if (x == 1) {
            f++;
            maxn = max(maxn, y);
            cnt.add(get_num(y), 1);
            value.add(get_num(y), y);
        } else {
            ll l = 0, r = 1e15 + 5;
            while (l <= r) {
                ll mid = (l + r) >> 1;
                ll w = check(mid);
                if (w / y < mid) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            cout << r << '\n';
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
