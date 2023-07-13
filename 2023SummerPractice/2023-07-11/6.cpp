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
const int MAXN = 1e6 + 5;
//玩原神导致的
int n;
int f[MAXN], g[MAXN];

//void solve(int l, int r) {
//    if (l > r)return;
//    else if (l == r) {
//        if (a[l] == l)ans++;
//        return;
//    }
//    int mid = (l + r) / 2;
//    int i = mid, j = mid;
//    int mx = a[mid], mn = a[mid];
//    while (i >= l) {
//        if (mn < l) {
//            i--;
//            mx = max(a[i], mx);
//            mn = min(a[i], mn);
//        } else if (mn == i) {
//            while (j <= r) {
//                if (g[j] > i)break;
//                if (g[j] > i && j > mx && f[j] == j) {
//                    ans++;
//                    bool flag = true;
//                }
//                j++;
//            }
//        } else if (mn > i) {
//            while (j <= r) {
//                if (g[j] > i)break;
//                if (g[j] == i && j > mx && f[j] == j) {
//                    ans++;
//                    bool flag = true;
//                }
//                j++;
//            }
//        }
//    }
//    solve(l, mid), solve(mid + 1, r);
//}
ull a[MAXN];
ull b[MAXN];
ull r[MAXN];
ull ans = 0;

void genshin_start() {
    cin >> n;
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<int> dis(1, INT32_MAX);
    for (int i = 1; i <= n; i++) {
        r[i] = dis(eng);
//        cout << r[i] << ' ';l
    }
//    cout << '\n';
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = r[i] ^ r[a[i]];
//        if (i == 1) {
//            f[i] = g[i] = a[i];
//        } else {
//            f[i] = max(f[i - 1], a[i]);
//            g[i] = min(g[i - 1], a[i]);
//        }
    }
//    solve(1, n);
    unordered_map<ull, ull> m;
    ull cur = 0;
    m[0] = 1;
    for (int i = 1; i <= n; i++) {
        cur ^= b[i];
        ans += m[cur];
        m[cur]++;
    }
    cout << ans << '\n';
}


signed main() {
    GKD;
    auto T = 1;
//    cin >> T;
    while (T--) genshin_start();
    return 0;
}