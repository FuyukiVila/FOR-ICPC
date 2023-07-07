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

int a[2000005];
bool is[2000005];

auto solve() {
    ll n, k;
    cin >> n >> k;
    ll cnt = 0;
    bool flag = false;
    ll zero = 0;
    ll has = 0;
    for (int i = 1; i <= n; i++) {
        is[i] = false;
        char c;
        cin >> c;
        if (c == '0')a[i] = 0;
        else a[i] = 1;
    }
    int next = 1;
    for (int i = 1; i <= n && cnt < k; i++) {
        if (a[i] == 0 && i == next) {
            next++;
            zero++;
            is[i] = true;
        } else if (a[i] == 0 && i - next <= k - cnt) {
            is[i] = true;
            cnt += i - next;
            next++;
            zero++;
        } else if (a[i] == 0) {
            next = i - (k - cnt);
            is[i] = true;
            flag = true;
            cnt = k;
        }
    }
    for (int i = 1; i <= zero; i++) {
        cout << 0;
    }
    for (int i = 1; i <= n; i++) {
        if (has + zero == next - 1 && flag) {
            cout << 0;
            flag = false;
        }
        if (!is[i]) {
            cout << a[i];
            has++;
        }
    }
    cout << '\n';
}

signed main() {
    GKD;
    auto T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}