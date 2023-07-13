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

#include <bits/stdc++.h>

using namespace std;

//玩原神导致的

void genshin_start() {
    int n, m;
    cin >> n >> m;
    if (n > 1 && n == m) {
        cout << n - 1 << '\n';
    } else if (n == 1 || m >= 2 * n) {
        cout << -1 << '\n';
    } else {
        cout << n << '\n';
    }
}

signed main() {
    GKD;
    auto T = 1;
    cin >> T;
    while (T--) genshin_start();
    return 0;
}