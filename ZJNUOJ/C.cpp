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

auto solve() {
    ll a, b;
    cin >> a >> b;
    ll sum = 0;
    ll t;
    for (t = 1; sum < a + b; t++) {
        sum += t;
    }
    if (sum != a + b)cout << "NO\n";
    else {
        t--;
        cout << "YES\n";
        pair<ll, char> A = {a, 'A'};
        pair<ll, char> B = {b, 'B'};
        vector<char> ans;
        for (ll i = t; i >= 1; i--) {
            if (A.first > B.first)swap(A, B);
            if (!A.first) {
                B.first -= i;
                ans.push_back(B.second);
                continue;
            } else if (!B.first) {
                A.first -= i;
                ans.push_back(A.second);
                continue;
            }
            if (A.first - i >= 0) {
                A.first -= i;
                ans.push_back(A.second);
            } else {
                B.first -= i;
                ans.push_back(B.second);
            }
        }
        std::reverse(ans.begin(), ans.end());
        for (auto x: ans) {
            cout << x;
        }
    }
}

signed main() {
    GKD;
    auto T = 1;
//    cin >> T;
    while (T--) solve();
    return 0;
}