#include "bits/stdc++.h"

template<size_t HashBase = 233>
class StringHash {
    std::vector<size_t> hash;
    std::vector<size_t> hashPow;

public:
    std::string str;

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

class SuffixArray {
public:
    std::vector<size_t> sa;
    std::vector<size_t> rank;
    std::vector<size_t> height;
    explicit SuffixArray() = default;

    explicit SuffixArray(const std::string &str) :
            sa(std::vector<size_t>(str.size())),
            rank(std::vector<size_t>(str.size())),
            height(std::vector<size_t>(str.size())) {
        StringHash<233> sh = StringHash<233>(str);
        for (size_t i = 1; i < str.size(); i++) {
            sa[i] = i;
        }
        std::sort(sa.begin() + 1, sa.end(), [&](size_t a, size_t b) -> bool {
            return sh.compare(a, str.size() - 1, b, str.size() - 1) == -1;
        });
        for (size_t i = 1; i < str.size(); i++) {
            rank[sa[i]] = i;
        }
        for (size_t i = 1, k = 0; i < str.size(); i++) {
            if (rank[i] == 1) {
                k = 0;
            } else {
                if (k) {
                    k--;
                }
                while (str[i + k] == str[sa[rank[i] - 1] + k]) {
                    k++;
                }
            }
            height[rank[i]] = k;
        }
    }
};