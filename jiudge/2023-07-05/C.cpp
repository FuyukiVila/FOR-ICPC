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

int a[100005];
int b[100005];
bool vis[100005];
int n;
int pos = 1;

void next() {
    for (int i = pos; i <= n; i++) {
        if (b[i] == -1) {
            pos = i;
            return;
        }
    }
    pos = n + 1;
}

auto solve() {
    cin >> n;
    a[0] = -1;
    vector<int> v;
    for (int i = 1; i <= n; i++)b[i] = -1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
//        if (a[i] == 0 && i == 1) {
//            b[i] = 1;
//            vis[1] = true;
//            v.emplace_back(a[i]);
//        }
        if (a[i] != a[i - 1]) {
            b[i] = a[i - 1];
            v.emplace_back(a[i]);
        }
        if (a[i] > i) {
            cout << -1 << '\n';
            return;
        }
    }
    if (a[1] == 1) b[1] = 0;
    for (int i = 1; i < v.size(); i++) {
        vis[v[i - 1]] = true;
        for (int j = v[i - 1]; j < v[i]; j++) {
            if (vis[j])continue;
            next();
            b[pos] = j;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (b[i] == -1)b[i] = 1000000;
        cout << b[i] << ' ';
    }
}

signed main() {
    GKD;
    auto T = 1;
//    cin >> T;
    while (T--) solve();
    return 0;
}