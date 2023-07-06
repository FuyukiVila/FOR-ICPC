#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
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

const int MAXN = 3000005;
int tr[MAXN][2], sum[MAXN];
int n, tot = 1;

inline void insert(int x, int z) {
    int k = 1;
    bool t;
    for (int i = 31; i >= 0; i--) {
        t = x & (1 << i);
        if (!tr[k][t])tr[k][t] = ++tot;
        k = tr[k][t];
        sum[k] += z;
    }
}

inline int search(int p, int l) {
    int k = 1, res = 0;
    bool x, y;
    for (int i = 31; i >= 0; i--) {
        x = p & (1 << i), y = l & (1 << i);
        if (y)res += sum[tr[k][x]], k = tr[k][x ^ 1];
        else k = tr[k][x];
    }
    return res;
}

auto solve() {
    int opt, p, l;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> opt >> p;
        if (opt == 1)insert(p, 1);
        if (opt == 2)insert(p, -1);
        if (opt == 3) {
            cin >> l;
            cout << search(p, l) << '\n';
        }
    }
    return 0;
}

signed main() {
    GKD;
    auto T = 1;
//    cin >> T;
    while (T--) solve();
    return 0;
}