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

ll n, m, s;
bool flag;
bool f;//true 失败序列在符玄，false 失败序列在观星
bool fuxuan;
bool guanxin;

void play(ll n, ll m) {
    if (n == 0 || m == 0)return;
    if (n + m < s)return;
    if (n >= m && n == s) {
        flag = true;
        f = true;
        return;
    } else if (n < m && m == s) {
        flag = true;
        f = false;
        return;
    }
    if (n >= m) {
        fuxuan = true;
        ll mod = n % m;
        if ((s - mod) % m != 0 || s < mod + m || s > n) {
            play(mod, m);
        } else {
            flag = true;
            f = true;
        }
    } else if (n < m) {
        guanxin = true;
        ll mod = m % n;
        if (mod == 0) {
            if ((s - mod) % n != 0 || s < 2 * n || s > m) {
                play(n, n);
            } else {
                flag = true;
                f = false;
            }
        } else {
            if ((s - mod) % n != 0 || s < n + mod || s > m) {
                play(n, mod);
            } else {
                flag = true;
                f = false;
            }
        }
    }
}

auto solve() {
    guanxin = false;
    fuxuan = false;
    cin >> n >> m >> s;
    flag = false;
    play(n, m);
    if (!flag) cout << "draw\n";
    else {
        if (f) {
            if (fuxuan)cout << "type-c\n";
            else cout << "lovely\n";
        } else if (!f) {
            if (guanxin)cout << "lovely\n";
            else cout << "type-c\n";
        }
    }
}

signed main() {
    GKD;
    auto T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}