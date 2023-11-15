#include<bits/stdc++.h>

#define ll long long
#define PII pair<int,int>
#define endl '\n'
#define i128 __int128_t
#define umap unordered_map
using namespace std;
const int maxn = 2e5 + 9;
int a[maxn], b[maxn];
int vp[maxn];

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) vp[i] = 0;
    a[1] = 1;
    for (int i = 2; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    sort(a + 1, a + 1 + n);
    sort(b + 1, b + 1 + n);
    int p = 0;
    vp[0] = 0;
    int rm = 0;
    for (int i = 1; i <= n - rm; i++) {
        int k = upper_bound(b + 1, b + 1 + n, a[i]) - b;
        if (k == n + 1) {
            rm += n - rm - i + 1;
            break;
        }
        if (k > vp[i - 1] + 1) {
            rm += k - vp[i - 1] - 1;
            vp[i] = k;
            vp[i - 1] = k - 1;
        } else {
            vp[i] = vp[i - 1] + 1;
        }
    }
    int rec = rm;
    int l = 2, r = m + 1;
    int mid = (l + r) / 2;
//	cout << "??\n";
    while (l < r) {
        mid = (l + r) / 2;
//		cout << "? " << l << ' ' << r << ' ' << mid << '\n';
        a[1] = mid;
        for (int i = 1; i <= n; i++) vp[i] = 0;
        sort(a + 1, a + 1 + n);
        sort(b + 1, b + 1 + n);
        p = 0;
        vp[0] = 0;
        rm = 0;
        for (int i = 1; i <= n - rm; i++) {
            int k = upper_bound(b + 1, b + 1 + n, a[i]) - b;
            if (k == n + 1) {
                rm += n - rm - i + 1;
                break;
            }
            if (k > vp[i - 1] + 1) {
                rm += k - vp[i - 1] - 1;
                vp[i] = k;
                vp[i - 1] = k - 1;
            } else {
                vp[i] = vp[i - 1] + 1;
            }
        }
        if (rm == rec) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
//	cout << "??? " << l << ' ' << r << endl;
    if (r == m + 1) {
// 		cout << "1A\n";
        cout << 1LL * m * rec << '\n';
    } else {
//		cout << "2B\n";
            cout << 1LL * (r - 1) * rec + 1LL * (m - l) * (rec + 1) << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}