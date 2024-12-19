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

void idol_produce(int testCase) {
    /*Code Here*/
    int n;
    cin >> n;
    int pos = 1;
    int ans = 0;
    while(pos <= n){
        // cout << pos << '\n';
        ans++;
        if(pos == n) break;
        int next = (pos + 1) * 2;
        pos = min(n, next);
    }
    cout << ans << endl;
}

signed main() {
    GKD;
    init();
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        idol_produce(i);
    }
    return 0;
}
