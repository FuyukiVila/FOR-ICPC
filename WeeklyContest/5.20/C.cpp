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
bool fuxuan, guanxin;

void play(ll n, ll m) {
    if (n + m < s)return;
    if (n >= m && n == s) {
        flag = true;
        cout << "lovely\n";
        return;
    } else if (n < m && m == s) {
        flag = true;
        cout << "type-c\n";
        return;
    }
    if (n >= m) {
        ll a = n % m;
        ll t = s - a;
        if (a == 0) {
            if (s % m != 0) {
                return;
            } else {
                if (s <= n && s >= a) {
                    flag = true;
                    if (!guanxin)cout << "type-c\n";
                    else cout << "lovely\n";
                } else return;
            }
        } else if (t % m == 0) {
            ll b = t / m;
            if (b * m + a <= n && b * m + a >= m) {
                flag = true;
                if (!guanxin)cout << "type-c\n";
                else cout << "lovely\n";
            } else {
                fuxuan = 1;
                guanxin = 0;
                play(a, m);
            }
        } else {
            fuxuan = 1;
            guanxin = 0;
            play(a, m);
        }
    } else if (n < m) {
        ll a = m % n;
        ll t = s - a;
        if (a == 0) {
            if (s % n != 0) {
                return;
            } else {
                ll b = s / n;
                if (b * a <= n && s > a) {
                    flag = true;
                    if (!fuxuan)cout << "lovely\n";
                    else cout << "type-c\n";
                } else {
                    guanxin = 1;
                    play(n, n);
                }
            }
        } else if (t % n == 0) {
            ll b = t / n;
            if (b * n + a <= m && b * n + a > n) {
                flag = true;
                if (!fuxuan)cout << "lovely\n";
                else cout << "type-c\n";
            } else {
                guanxin = 1;
                fuxuan = 0;
                play(n, a);
            }
        } else {
            guanxin = 1;
            fuxuan = 0;
            play(n, a);
        }
    }
}

auto solve() {
    cin >> n >> m >> s;
    flag = false;
    fuxuan = 0;
    guanxin = 0;
    play(n, m);
    if (!flag) cout << "draw\n";
}

signed main() {
    GKD;
    auto T = 1;
    cin >> T;
    while (T--) solve();
    return 0;
}