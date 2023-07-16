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
void genshin_start() {
<<<<<<< HEAD
    int n, k;
    int sum = 0;
    cin >> n >> k;
    vector<int> a(n);
    vector<int> b(n-1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i > 0) {
            b[i - 1] = abs(a[i] - a[i - 1]);
            sum += abs(a[i] - a[i - 1]);
        }
    }
    sort(b.begin(), b.end(), greater<>());
    for (int i = 0; i < k - 1; i++) {
        sum -= b[i];
    }
    cout << sum << '\n';
=======

>>>>>>> 7d2f77c1139025a18ce7280cd3653cd41faa1591
}

signed main() {
    GKD;
    auto T = 1;
<<<<<<< HEAD
    cin >> T;
=======
//    cin >> T;
>>>>>>> 7d2f77c1139025a18ce7280cd3653cd41faa1591
    while (T--) genshin_start();
    return 0;
}