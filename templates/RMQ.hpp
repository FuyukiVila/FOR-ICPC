#ifndef __RMQ_HPP
#define __RMQ_HPP

#include "bits/stdc++.h"

using namespace std;

template<typename T>
struct RMQ {
private:
    vector<vector<T>> maxn;
    vector<vector<T>> minn;
    vector<vector<T>> gcd;

    static int msb(int x) {
        assert(x > 0);
        int ans = -1;
        while (x) {
            x >>= 1;
            ++ans;
        }
        return ans;
    }

public:
    explicit RMQ(const vector<T> &a) {
        maxn.resize(a.size() + 1, vector<T>(32));
        minn.resize(a.size() + 1, vector<T>(32));
        int n = a.size() - 1;
        for (int i = 1; i <= n; i++) {
            maxn[i][0] = minn[i][0] = gcd[i][0] = a[i];
        }
        for (int j = 1; 1 << j <= n; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                assert(j - 1 >= 0 && i + (1 << (j - 1)) - 1 <= n);
                maxn[i][j] = max(maxn[i][j - 1], maxn[i + (1 << (j - 1))][j - 1]);
                minn[i][j] = min(minn[i][j - 1], minn[i + (1 << (j - 1))][j - 1]);
                gcd[i][j] = __gcd(gcd[i][j - 1], gcd[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T getMax(int l, int r) {
        int k = msb(r - l + 1);
        return max(maxn[l][k], maxn[r - (1 << k) + 1][k]);
    }

    T getMin(int l, int r) {
        int k = msb(r - l + 1);
        return min(minn[l][k], minn[r - (1 << k) + 1][k]);
    }

    T getGCD(int l, int r) {
        int k = msb(r - l + 1);
        return gcd[l][k];
    }

};

#endif
