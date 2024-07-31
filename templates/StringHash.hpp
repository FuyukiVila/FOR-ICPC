#include "bits/stdc++.h"

template<size_t HashBase = 233>
class StringHash {
    std::string str;
    std::vector<size_t> hash;
    std::vector<size_t> hashPow;

public:
    explicit StringHash() = default;

    explicit StringHash(const std::string &str) :
            str(str),
            hash(std::vector<size_t>(str.size())),
            hashPow(std::vector<size_t>(str.size())) {
        hashPow[0] = 1;
        hash[0] = 0;
        for (size_t i = 1; i < str.size(); i++) {
            hash[i] = (hash[i - 1] * HashBase + str[i]);
            hashPow[i] = hashPow[i - 1] * HashBase;
        }
    }

    constexpr size_t getHash(size_t l, size_t r) {
        assert(r >= l);
        assert(l > 0);
        assert(r < str.size());
        return hash[r] - hash[l - 1] * hashPow[r - l + 1];
    }

    int compare(size_t l1, size_t r1, size_t l2, size_t r2) {
        assert(r1 >= l1 && r2 >= l2);
        assert(l1 > 0 && l2 > 0);
        assert(r1 < str.size() && r2 < str.size());
        size_t l = 0, r = std::min(r1 - l1, r2 - l2) + 1;
        size_t ans;
        while (l <= r) {
            size_t mid = (l + r) / 2;
            if (getHash(l1, l1 + mid - 1) == getHash(l2, l2 + mid - 1)) {
                l = mid + 1;
                ans = mid;
            } else {
                r = mid - 1;
            }
        }
        if (ans == std::min(r1 - l1, r2 - l2) + 1) {
            if (r1 - l1 == r2 - l2) {
                return 0;
            } else if (r1 - l1 > r2 - l2) {
                return 1;
            } else {
                return -1;
            }
        } else {
            return (str[l1 + ans] > str[l2 + ans]) ? 1 : -1;
        }
    }
};