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

template<typename T>
inline bool isPrime(T num) {
    if (num == 1 || num == 4)
        return false;
    if (num == 2 || num == 3)
        return true;
    if (num % 6 != 1 && num % 6 != 5)
        return false;
    T tmp = sqrt(num);
    for (T i = 5; i <= tmp; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0)
            return false;
    }
    return true;
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

auto genshin_start() {
    int n;
    ll sum = 0;
    cin >> n;
    vector<ll> a(n + 5);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    if (n == 1 && isPrime(a[1])) {
        cout << "Yes";
        return;
    } else if (n == 1) {
        cout << "No";
        return;
    }
    if (n == 2) {
        if (sum % 2 == 0 && sum > 2) {
            cout << "Yes\n";
            return;
        } else if (sum > 2 && isPrime(sum - 2)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
        return;
    }
    sum = sum - (n - 2) * 2;
    if (sum >= 4) {
        cout << "Yes";
        return;
    } else {
        cout << "No";
        return;
    }
}

signed main() {
    GKD;
    auto T{1};
//    cin >> T;
    while (T--) genshin_start();
    return 0;
}