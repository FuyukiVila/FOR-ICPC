#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
#define clr(a, b) memset(a, b, sizeof(a))
#define cpy(a, b) memcpy(a, b, sizeof(a))
// #define _DEBUG
// #define PRIME

#include <bits/stdc++.h>

#ifdef _DEBUG

#define dbg(x...)                  \
    do {                           \
        std::cout << #x << " -> "; \
        err(x);                    \
    } while (0)

void err() { std::cout << std::endl; }

template <class T, class... Ts>
void err(T arg, Ts &...args) {
    std::cout << arg << ' ';
    err(args...);
}

#else

#define dbg(x...) 114514;

#endif

using namespace std;
using ll = long long;
using ull = unsigned long long;
constexpr int INF = 0x3f3f3f3f;
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

#ifdef PRIME

namespace prime {
const int N = 1e7 + 100;
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
}  // namespace prime

#endif

inline void init() { /*Init Here*/ }

#define int long long
void idol_produce(int testCase) {
    /*Code Here*/
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    int w = 0;
    set<pair<int, vector<int>>> ans;
    int id = 0;
    do {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                sum += *min_element(a.begin() + i, a.begin() + j + 1);
            }
        }
        if (sum > w) {
            w = sum;
            ans.clear();
            ans.insert({id, a});
        } else if (sum == w) {
            ans.insert({id, a});
        }
        id++;
    } while (next_permutation(a.begin(), a.end()));
    cout << ans.size() << endl;
    int last = 0;
    for (auto i : ans) {
        // cout << i.first << ": ";
        cout << i.first - last;
        last = i.first;
        // for (auto j : i.second) {
        //     cout << j << " ";
        // }
        cout << endl;
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
