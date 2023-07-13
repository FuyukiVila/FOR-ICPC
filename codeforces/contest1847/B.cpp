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

template<typename T>
constexpr T qpow(T a, T n) {
    if (n == 0)
        return 1;
    else if (n % 2 == 1)
        return (qpow(a, n - 1) * a);
    else {
        T temp = qpow(a, n / 2);
        return temp * temp;
    }
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
int a[200005];

void genshin_start() {
    int n;
    cin >> n;
    int sum = 0;
    int all = 0;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (i == 1) {
            all = a[i];
        } else {
            all &= a[i];
        }
        if (sum == 0) {
            ans++;
            sum = a[i];
        } else {
            sum &= a[i];
        }
    }
    if (sum == all) {
        cout << ans << '\n';
    } else {
        cout << max(1, ans - 1) << '\n';
    }
}

signed main() {
    GKD;
    auto T = 1;
    cin >> T;
    while (T--) genshin_start();
    return 0;
}