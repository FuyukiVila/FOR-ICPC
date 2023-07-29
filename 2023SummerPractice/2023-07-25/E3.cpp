#include "bits/stdc++.h"

using namespace std;
#define int long long
const int inf = 0x3f3f3f3f3f3f3f3f;
const int maxn = 3e5 + 10;
const int mod = 1e9 + 7;

int a[maxn];
int _a[maxn];
int dp[3005][3005];

void solve() {
    map<int, int> mp;
    int n;
    cin >> n;
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    int _ = 0;
    vector<int> v(1, 0);
    for (int i = 1; i <= n; i++) {
        if (a[i] != a[i - 1]) {
            v.emplace_back(++_);
            mp[_]++;
        } else {
            mp[_]++;
        }
    }
    for (auto const &x: v) {
        dp[1][x] = x;
    }
    for (int i = 2; i <= n; i++) {
        for (auto const &j: v) {
            if (j + mp[j] > i) {
                dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]) % mod;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << dp[i][v.back()] << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int tt = 1;
    cin >> tt;
    while (tt--) {
        solve();
    }
    return 0;
}