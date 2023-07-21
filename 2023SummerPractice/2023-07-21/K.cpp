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

#define int ll

ll a[1000005];
bool b[1000005];
ll dp[1000005][3];
vector<int> pos;

auto genshin_start() {
    int n;
    cin >> n;
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        if (b[i] == 1) {
            pos.emplace_back(i);
        }
    }
    for (int i = 0; i < pos.size(); i++) {
        if (i == 0) {
            int j = pos[i];
            if (j == 1) {
                dp[i][0] = -INF;
                dp[i][1] = a[j];
                dp[i][2] = a[j + 1];
            } else {
                dp[i][0] = a[j - 1];
                dp[i][1] = a[j];
                dp[i][2] = a[j + 1];
            }
        } else {
            int j = pos[i];
            int k = pos[i - 1];
            if (j - k >= 3) {
                dp[i][0] = max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]}) + a[j - 1];
                dp[i][1] = max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]}) + a[j];
                dp[i][2] = max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]}) + a[j + 1];
            } else if (j - k == 1) {
                dp[i][0] = dp[i - 1][0] + a[j - 1];
                dp[i][1] = max({dp[i - 1][0], dp[i - 1][1]}) + a[j];
                dp[i][2] = max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]}) + a[j + 1];
            } else if (j - k == 2) {
                dp[i][0] = max({dp[i - 1][0], dp[i - 1][1]}) + a[j - 1];
                dp[i][1] = max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]}) + a[j];
                dp[i][2] = max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]}) + a[j + 1];
            }
        }
        for (int j = 0; j < 3; j++) {
            ans = max(ans, dp[i][j]);
        }
    }
//    for (int i = 1; i <= n; i++) {
//        dp[i] = dp[i - 1];
//        if (i == 1) {
//            if (b[i] == 1) {
//                dp[i] = a[i];
//                one.insert(a[i]);
//            } else {
//                zero = a[i];
//            }
//        } else if (b[i] == 1) {
//            dp[i] += a[i];
////            if (zero > a[i]) {
////                dp[i] -= a[i];
////                dp[i] += zero;
////                zero = a[i];
////                one.clear();
////            } else {
//                one.insert(a[i]);
////            }
//        } else if (b[i] == 0) {
//            if (one.empty()) {
//                zero = a[i];
//                continue;
//            }
//            auto x = one.begin();
//            if (*x < a[i]) {
//                zero = *x;
//                dp[i] += a[i];
//                dp[i] -= *x;
//            } else {
//                zero = a[i];
//            }
//            one.clear();
//        }
//    }
    cout << ans << '\n';
}

signed main() {
    GKD;
    auto T{1};
//    cin >> T;
    while (T--) genshin_start();
    return 0;
}