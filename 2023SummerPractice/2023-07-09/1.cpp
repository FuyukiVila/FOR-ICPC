#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
#define clr(a, b) memset(a, b, sizeof(a))

#include <bits/stdc++.h>

#include <random>

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

struct node {
    double x, y;

    constexpr node operator+(node const &b) const {
        node res{};
        res.x = this->x + b.x;
        res.y = this->y + b.y;
        return res;
    }

    constexpr void operator+=(node const &b) {
        this->x += b.x;
        this->y += b.y;
    }

    constexpr node operator-(node const &b) const {
        node res{};
        res.x = this->x - b.x;
        res.y = this->y - b.y;
        return res;
    }

    constexpr void operator-=(node const &b) {
        this->x -= b.x;
        this->y -= b.y;
    }

    constexpr double getLen() const {
        return x * x + y * y;
    }
} v[100005];

inline bool left(node a) {
    return a.x > 0 || (a.x == 0 && a.y >= 0);
}

inline bool cmp(node a, node b) {
    if (left(a) != left(b)) return left(a) > left(b);
    else return (a.x * b.y - a.y * b.x) > 0;
}

//玩原神玩的
auto genshin_start() {
    int n;
    cin >> n;
    node ans = {0, 0};
    for (int i = 1; i <= n; i++) {
        cin >> v[i].x >> v[i].y;
        if (v[i].y < 0) {
            v[i].x = -v[i].x;
            v[i].y = -v[i].y;
        }
        ans = ans + v[i];
    }
    sort(v + 1, v + n + 1, cmp);
    double res = ans.getLen();
    for (int i = 1; i <= n; i++) {
        ans = ans - v[i];
        ans = ans - v[i];
        if (ans.getLen() > res) {
            res = ans.getLen();
        }
    }
    cout << fixed << setprecision(10);
    cout << sqrt(res) << '\n';
}

signed main() {
    GKD;
    auto T = 1;
    cin >> T;
    while (T--) genshin_start();
    return 0;
}