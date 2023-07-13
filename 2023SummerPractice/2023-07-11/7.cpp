#include<bits/stdc++.h>

#define ll long long
#define PII pair<int,int>
using namespace std;
const int maxn = 1e6 + 9;
int n, a[maxn], g[maxn], f[maxn], sf[maxn];
int ans;

void solve(int l, int r) {
//	cout << "?\n";
    if (l == r) {
        if (a[r] == r) ++ans;
        return;
    }
    int mid = (l + r) / 2;
//    memset(g, 0x3f, sizeof(g));
//    memset(f, 0, sizeof(f));
//    memset(sf, 0, sizeof(sf));
    for (int i = mid + 1; i <= r; i++) {
        if (i == mid + 1) {
            f[i] = g[i] = a[i];
            if (f[i] == i) sf[i] = 1;
        } else {
            f[i] = max(f[i - 1], a[i]);
            g[i] = min(g[i - 1], a[i]);
            sf[i] = sf[i - 1] + (f[i] == i);
        }
    }
    int i = mid;
    int mn = 0x3f3f3f3f, mx = -1e9;
    while (i >= l) {
//		cout << "? " << i << '\n';
        mx = max(mx, a[i]);
        mn = min(mn, a[i]);
        if (i > mn) {
            i--;
            continue;
        }
        if (i == mn) {
            if (f[mx] < mx && g[mx] > i) {
                ++ans;
                cout << "plusx1 " << l << ' ' << r << ' ' << 1 << '\n';
            }
            int x = mid + 1, y = r, z;
            while (x < y) {
                z = (x + y + 1) / 2;
                if (g[z] > i) {
                    x = z;
                } else y = z - 1;
            }
            if (mx >= x) {
                --i;
                continue;
            } else {
                ans += sf[x] - sf[mx];
                cout << "plus1 " << l << ' ' << r << ' ' << sf[x] - sf[mx] << '\n';
                --i;
                continue;
            }
        }
        if (i < mn) {
            if (f[mx] < mx && g[mx] == i) {
                ++ans;
                cout << "plusx2 " << l << ' ' << r << ' ' << 1 << '\n';
            }
            int x = mid + 1, y = r, z, a, b;
            while (x < y) {
                z = (x + y) / 2;
                if (g[z] > i) {
                    x = z + 1;
                } else {
                    y = z;
                }
            }
            a = x;
            x = mid + 1, y = r;
            while (x < y) {
                z = (x + y) / 2;
                if (g[z] >= i) {
                    x = z + 1;
                } else {
                    y = z;
                }
            }
            b = x;
            if (max(a, mx) >= b) {
                --i;
                continue;
            } else {
                ans += sf[b] - sf[max(a, mx)];
                cout << "plus2 " << l << ' ' << r << ' ' << sf[b] - sf[max(a, mx)] << '\n';
                --i;
                continue;
            }
        }
    }
    solve(l, mid);
    solve(mid + 1, r);
}

signed main() {
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    solve(1, n);
    cout << ans << '\n';
    return 0;
}
