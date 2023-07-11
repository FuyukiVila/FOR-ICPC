
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

//玩原神导致的
ll a[300005];

void genshin_start() {
    ll n{}, k{};
    ll sum{0};
    cin >> n >> k;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    a[n + 1] = 1e9;
    sort(a + 1, a + n + 1);
    ll median = a[(n + 1) / 2];
    if (sum == median * n) {
        cout << 0 << '\n';
    } else if (median * n > sum) {
        ll t = n * median - sum;
        if (t <= k) {
            cout << t << '\n';
        } else {
            cout << -1 << '\n';
        }
        return;
    } else {
        ll used = 0;
        for (ll i = (n + 1) / 2; i <= n; i++) {
            ll num = i - (n + 1) / 2 + 1;
            ll add = a[i + 1] - a[i];
            if ((median + add) * n >= sum + add * num) {
                ll t = (sum - n * median) / (n - num);
                median += t;
                sum += num * t;
                while (median * n < sum) {
                    median += 1;
                    sum += num;
                    t++;
                }
                used += t * num;
                if (used > k) {
                    cout << -1 << '\n';
                    return;
                }
                if (median * n == sum) {
                    cout << used << '\n';
                    return;
                }
                if (median * n > sum) {
                    ll t1 = n * median - sum;
                    used += t1;
//                    cout<<used<<"\n";
                    if (used <= k) {
                        cout << used << '\n';
                        return;
                    } else {
                        cout << -1 << '\n';
                        return;
                    }
                }
            } else {
                median += add;
                sum += num * add;
                used += num * add;
                if (used > k) {
                    cout << -1 << '\n';
                    return;
                }
            }
        }
    }
}

signed main() {
    GKD;
    auto T = 1;
//    cin >> T;
    while (T--) genshin_start();
    return 0;
}