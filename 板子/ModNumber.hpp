#ifndef __MOD_NUMBER_HPP
#define __MOD_NUMBER_HPP

#define int long long

template<const int _MOD>
struct ModNumber {
    int x;

    ModNumber() { x = 0; }

    ModNumber(long long y) { x = y % _MOD; }

    int Int() { return x; }

    int Pow(int y) {
        int ret = 1, tmp = x;
        while (y) {
            if (y & 1)
                ret = ((long long) ret * tmp) % _MOD;
            y >>= 1;
            tmp = ((long long) tmp * tmp) % _MOD;
        }
        return ret;
    }

    void operator=(long long y) { x = y % _MOD; }

    bool operator==(long long y) const { return x == y; }

    bool operator==(ModNumber y) const { return x == y.x; }

    bool operator!=(long long y) const { return x != y; }

    bool operator!=(ModNumber y) const { return x != y.x; }

    bool operator<(long long y) const { return x < y; }

    bool operator<(ModNumber y) const { return x < y.x; }

    bool operator>(long long y) const { return x > y; }

    bool operator>(ModNumber y) const { return x > y.x; }

    bool operator<=(long long y) const { return x <= y; }

    bool operator<=(ModNumber y) const { return x <= y.x; }

    bool operator>=(long long y) const { return x >= y; }

    bool operator>=(ModNumber y) const { return x >= y.x; }

    ModNumber operator+(ModNumber y) const { return ((long long) x + y.x) % _MOD; }

    ModNumber operator*(ModNumber y) const {
        return ((long long) x * y.x) % _MOD;
    }

    ModNumber operator-(ModNumber y) const { return ((x - y.x) % _MOD + _MOD) % _MOD; }

    ModNumber operator+(long long y) const { return ((long long) x + y) % _MOD; }

    ModNumber operator*(long long y) const { return ((long long) x * y) % _MOD; }

    ModNumber operator-(long long y) const { return ((x - y) % _MOD + _MOD) % _MOD; }

    void operator+=(ModNumber y) { *this = *this + y; }

    void operator*=(ModNumber y) { *this = *this * y; }

    void operator-=(ModNumber y) { *this = *this - y; }

    void operator+=(long long y) { x = ((long long) x + y) % _MOD; }

    void operator*=(long long y) { x = ((long long) x * y) % _MOD; }

    void operator-=(long long y) { x = ((x - y) % _MOD + _MOD) % _MOD; }

    ModNumber operator^(int y) {
        ModNumber ret = Pow(y);
        return ret;
    }

    ModNumber operator/(ModNumber y) const {
        return ((long long) x * (y.Pow(_MOD - 2))) % _MOD;
    }

    void operator/=(ModNumber y) { *this = *this / y; }

    template<class T>
    friend bool operator==(T y, ModNumber t) { return y == t.x; }

    template<class T>
    friend ModNumber operator+(T t, ModNumber y) { return ((long long) t + y.x) % _MOD; }

    template<class T>
    friend ModNumber operator*(T t, ModNumber y) { return ((long long) t * y.x) % _MOD; }

    template<class T>
    friend ModNumber operator-(T t, ModNumber y) { return ((t - y.x) % _MOD + _MOD) % _MOD; }

    template<class T>
    friend ModNumber operator/(T t, ModNumber y) { return ModNumber((y / t).Pow(_MOD - 2)); }

    ModNumber operator/(int y) const { return ((long long) x * (ModNumber(y).Pow(_MOD - 2))) % _MOD; }

    void operator/=(int y) { *this = *this / y; }

    void operator++() { *this = *this + 1; }

    void operator--() { *this = *this - 1; }
};

#undef int long long

#endif