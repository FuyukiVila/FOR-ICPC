#include <string>
#include <vector>
struct Manacher {

    // 求奇数回文串
    std::vector<int> static getOddPalindrome(const std::string &s) {
        std::vector<int> d1(s.size());
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
        return d1;
    }

    // 求偶数回文串
    std::vector<int> static getEvenPalindrome(const std::string &s) {
        std::vector<int> d2(s.size());
        for (int i = 0, l = 0, r = -1; i < s.size(); i++) {
            int k = (i > r) ? 0 : std::min(d2[l + r - i + 1], r - i + 1);
            while (0 <= i - k - 1 && i + k < s.size() &&
                    s[i - k - 1] == s[i + k]) {
                k++;
            }
            d2[i] = k--;
            if (i + k > r) {
                l = i - k - 1;
                r = i + k;
            }
        }
        return d2;
    }
};
