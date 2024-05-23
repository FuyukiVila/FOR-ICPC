#include <string>
#include <vector>
struct Manacher {
    std::vector<int> d1;
    std::vector<int> d2;
    Manacher(const std::string &s) {
        d1.resize(s.size());
        d2.resize(s.size());
        getOddPalindrome(s);
        getEvenPalindrome(s);
    }
    // 求奇数回文串
    void getOddPalindrome(const std::string &s) {
        for (int i = 0, l = 0, r = -1; i < s.size(); i++) {
            int k = (i > r) ? 1 : std::min(d1[l + r - i], r - i + 1);
            while (0 <= i - k && i + k < s.size() && s[i - k] == s[i + k]) {
                k++;
            }
            d1[i] = k--;
            if (i + k > r) {
                l = i - k;
                r = i + k;
            }
        }
    }

    // 求偶数回文串
    void getEvenPalindrome(const std::string &s) {
        for (int i = 0, l = 0, r = -1; i < s.size(); i++) {
            int k = (i > r) ? 0 : std::min(d2[l + r - i + 1], r - i + 1);
            while (0 <= i - k - 1 && i + k < s.size() && s[i - k - 1] == s[i + k]) {
                k++;
            }
            d2[i] = k--;
            if (i + k > r) {
                l = i - k - 1;
                r = i + k;
            }
        }
    }
};