#ifndef __MODINT_HPP
#define __MODINT_HPP

#include <iostream>

#if __cplusplus < 201703L
#define constexpr inline
#endif

template<int T>
struct ModInt {
    int x;

    constexpr ModInt(long long x = 0) : x(x % T) {}

    constexpr int val() { return x; }

    constexpr ModInt operator=(const ModInt &a) { return x = a.x; }

    constexpr ModInt operator=(long long y) { return x = y % T; }

    constexpr ModInt operator+(const ModInt &a) const {
        int x0 = x + a.x;
        return ModInt(x0 < T ? x0 : x0 - T);
    }

    constexpr ModInt operator-(const ModInt &a) const {
        int x0 = x - a.x;
        return ModInt(x0 < 0 ? x0 + T : x0);
    }

    constexpr ModInt operator*(const ModInt &a) const { return ModInt(1LL * x * a.x % T); }

    constexpr ModInt operator/(const ModInt &a) const { return *this * a.inv(); }

    constexpr bool operator==(const ModInt &a) const { return x == a.x; };

    constexpr bool operator!=(const ModInt &a) const { return x != a.x; };

    constexpr void operator+=(const ModInt &a) {
        x += a.x;
        if (x >= T) x -= T;
    }

    constexpr void operator-=(const ModInt &a) {
        x -= a.x;
        if (x < 0) x += T;
    }

    constexpr void operator*=(const ModInt &a) { x = 1LL * x * a.x % T; }

    constexpr void operator/=(const ModInt &a) { *this = *this / a; }

    constexpr friend ModInt operator+(int y, const ModInt &a) {
        int x0 = y + a.x;
        return ModInt(x0 < T ? x0 : x0 - T);
    }

    constexpr friend ModInt operator-(int y, const ModInt &a) {
        int x0 = y - a.x;
        return ModInt(x0 < 0 ? x0 + T : x0);
    }

    constexpr friend ModInt operator*(int y, const ModInt &a) { return ModInt(1LL * y * a.x % T); }

    constexpr friend ModInt operator/(int y, const ModInt &a) { return ModInt(y) / a; }

    constexpr friend std::ostream &operator<<(std::ostream &os, const ModInt &a) { return os << a.x; }

    constexpr friend std::istream &operator>>(std::istream &is, ModInt &t) { return is >> t.x; }

    constexpr ModInt pow(int n) const {
        ModInt res(1), mul(x);
        while (n) {
            if (n & 1) res *= mul;
            mul *= mul;
            n >>= 1;
        }
        return res;
    }

    constexpr ModInt operator^(int n) const {
        return pow(n);
    }

    constexpr ModInt inv() const {
        int a = x, b = T, u = 1, v = 0;
        while (b) {
            int t = a / b;
            a -= t * b;
            std::swap(a, b);
            u -= t * v;
            std::swap(u, v);
        }
        if (u < 0) u += T;
        return u;
    }

    constexpr ModInt operator~() const {
        return inv();
    }

    constexpr ModInt &operator++() {
        ++x;
        if (x >= T) x -= T;
        return *this;
    }

    constexpr ModInt &operator--() {
        --x;
        if (x < 0) x += T;
        return *this;
    }

    constexpr ModInt operator++(int) {
        ModInt t = *this;
        ++*this;
        return t;
    }

    constexpr ModInt operator--(int) {
        ModInt t = *this;
        --*this;
        return t;
    }
};


using Mint = ModInt<998244353>;

#endif //__MODINT_HPP
