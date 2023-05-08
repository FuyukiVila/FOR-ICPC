#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false);
#define clr(a, b) memset(a, b, sizeof(a))

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
const double pi = acos(-1);
const int INF = 0x3f3f3f3f;

template<typename T>
inline T qpow(T a, T n) {
    if (n == 0)
        return 1;
    else if (n % 2 == 1)
        return (qpow(a, n - 1) * a);
    else {
        T temp = qpow(a, n / 2);
        return temp * temp;
    }
}

template<typename T>
bool isPrime(T num) {
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

const int N = 1e7 + 100;
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

ll b[105][105];

auto solve() {
    int n, m;
    ll ans = 0;
    cin >> n >> m;
    ll min_1 = INF, min_2 = INF, max_1 = -INF, max_2 = -INF;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> b[i][j];
            if (b[i][j] < min_1) {
                min_2 = min_1;
                min_1 = b[i][j];
            } else if (b[i][j] < min_2) {
                min_2 = b[i][j];
            }
            if (b[i][j] > max_1) {
                max_2 = max_1;
                max_1 = b[i][j];
            } else if (b[i][j] > max_2) {
                max_2 = b[i][j];
            }
        }
    }
    ans = (n * m - n - m + 1) * (max_1 - min_1);
//    cout<<min_1<<' '<<min_2<<' '<<max_1<<' '<<max_2<<'\n';
    cout << max(max(ans + (n - 1) * (max_1 - min_1) + (m - 1) * (max_2 - min_1),
                    ans + (n - 1) * (max_2 - min_1) + (m - 1) * (max_1 - min_1)),
                max(ans + (n - 1) * (max_1 - min_1) + (m - 1) * (max_1 - min_2),
                    ans + (m - 1) * (max_1 - min_1) + (n - 1) * (max_1 - min_2))) << '\n';
}

signed main() {
    GKD
    auto T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}