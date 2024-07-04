/*
  ______                 _    _  __      ___ _
 |  ____|               | |  (_) \ \    / (_) |
 | |__ _   _ _   _ _   _| | ___   \ \  / / _| | __ _
 |  __| | | | | | | | | | |/ / |   \ \/ / | | |/ _` |
 | |  | |_| | |_| | |_| |   <| |    \  /  | | | (_| |
 |_|   \__,_|\__, |\__,_|_|\_\_|     \/   |_|_|\__,_|
              __/ |
             |___/
*/

#define GKD std::cin.tie(nullptr)->std::ios::sync_with_stdio(false)
#define clr(a, b) memset(a, b, sizeof(a))
#define cpy(a, b) memcpy(a, b, sizeof(a))

#include <bits/stdc++.h>

#ifdef LOCAL

#define dbg(x...) \
    do { \
        std::cout << #x << " -> "; \
        err(x); \
    } while (0);
#else
#define dbg(x...) 114514;
#endif

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
const int INF = 0x3f3f3f3f;
ll mod = 0;

inline ll qpow(ll _a, ll _n, ll _mod = mod) {
    ll ans = 1;
    while (_n) {
        if (_n & 1) ans *= _a;
        _n >>= 1;
        _a *= _a;
        if (_mod > 0) {
            ans %= _mod;
            _a %= _mod;
        }
    }
    return ans;
}

int w[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};

//为什么要演奏春日影！
void haruhikage_start() {
    int n,m;cin >> n >> m;
    vector a(n + 5,vector<char>(m + 5));
    vector<int> f(n * m + 5);
    vector<int> siz(n * m + 5,1);
    vector<int> fl(n * m + 5);
    vector<int> fr(n * m + 5);
    vector<int> fd(n * m + 5);
    vector<int> fu(n * m + 5);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            fl[(i - 1) * m + j] = j - (j > 1);
            fr[(i - 1) * m + j] = j + (j < m);
            fd[(i - 1) * m + j] = i + (i < n);
            fu[(i - 1) * m + j] = i - (i > 1);
        }
    }
    for (int i = 1;i <= n * m;i++) f[i] = i;
    auto find  = [&](auto self,int x) -> int {
        return f[x] == x ? x : f[x] = self(self,f[x]);
    };
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= m;j++) {
            if (a[i][j] == '.') continue;
            for (auto [dx,dy] : w) {
                int x = i + dx,y = j + dy;
                if (x < 1 || x > n || y < 1 || y > m) continue;
                if (a[x][y] == '.') continue;
                int fa = find(find,(i - 1) * m + j),fb = find(find,(x - 1) * m + y);
                if (fa != fb) {
                    f[fa] = fb;
                    siz[fb] += siz[fa];
                    fl[fb] = min(fl[fb],fl[fa]);
                    fr[fb] = max(fr[fb],fr[fa]);
                    fd[fb] = max(fd[fb],fd[fa]);
                    fu[fb] = min(fu[fb],fu[fa]);
                } 
            }
        }
    }
    vector<int>vis(n * m + 5);
    vector<int>row(n + 5),col(m + 5);
    vector c(n + 5,vector<int>(m + 5));
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= m;j++) {
            if (a[i][j] == '.') continue;
            int now = (i - 1) * m + j;
            int fnow = find(find,now);
            if (vis[fnow]) continue;
            int val = siz[fnow];
            row[fu[fnow]]+=val;
            row[fd[fnow] + 1]-=val;
            col[fl[fnow]]+=val;
            col[fr[fnow] + 1]-=val;
            vis[fnow] = 1;
            c[fu[fnow]][fl[fnow]]+=val;
            c[fu[fnow]][fr[fnow] + 1]-=val;
            c[fd[fnow] + 1][fl[fnow]]-=val;
            c[fd[fnow] + 1][fl[fnow] + 1]+=val;
        }
    }
    for (int i = 1;i <= n;i++) {
        row[i] += row[i - 1];
        for (int j = 1;j <= m;j++) {
            c[i][j] = c[i][j] - c[i - 1][j] - c[i][j - 1] + c[i - 1][j - 1]; 
        }
    }
    for (int j = 1;j <= m;j++) col[j] += col[j - 1];
    int mx = 0;
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= m;j++) {
            mx = max(mx,row[i] + col[j] - c[i][j]);
        }
    }
    cout << mx << '\n';
}

signed main() {
    GKD;
    int T = 1;
    cin >> T;
    while (T--) haruhikage_start();
    return 0;
}

