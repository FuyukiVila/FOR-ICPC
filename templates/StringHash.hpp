#include "string"
#include "vector"

template<size_t HashBase = 233>
class StringHash {
    std::vector<size_t> hash;
    std::vector<size_t> hashPow;

public:
    StringHash(const std::string &str) {
        hash.resize(str.size() + 1);
        hashPow.resize(str.size() + 1);
        hashPow[0] = 1;
        for (size_t i = 1; i < str.size(); i++) {
            hash[i] = (hash[i - 1] * HashBase + str[i]);
            hashPow[i] = hashPow[i - 1] * HashBase;
        }
    }

    size_t getHash(size_t l, size_t r) {
        return hash[r] - hash[l - 1] * hashPow[r - l + 1];
    }
};