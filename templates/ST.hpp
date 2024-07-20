#ifndef __ST_HPP
#define __ST_HPP

#include "vector"

template<typename T>
struct ST {
private:
    std::vector<std::vector<T> > maxn;
    std::vector<std::vector<T> > minn;
    std::vector<std::vector<T> > gcd;

    static int msb(int x) {
        int ans = -1;
        while (x) {
            x >>= 1;
            ++ans;
        }
        return ans;
    }

public:
    explicit ST(const std::vector<T> &a) {
        maxn.resize(a.size(), std::vector<T>(32));
        minn.resize(a.size(), std::vector<T>(32));
        gcd.resize(a.size(), std::vector<T>(32));
        for (int i = 0; i < a.size(); i++) {
            maxn[i][0] = minn[i][0] = gcd[i][0] = a[i];
        }
        for (int j = 1; 1 << j <= a.size(); j++) {
            for (int i = 0; i + (1 << j) - 1 < a.size(); i++) {
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
        return __gcd(gcd[l][k], gcd[(r - (1 << k) + 1)][k]);
    }

};

#endif
