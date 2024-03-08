#ifndef __KMP_HPP
#define __KMP_HPP

#include "bits/stdc++.h"

class KMP2 {
private:
    std::vector<std::vector<int>> dp;
    std::string pat;

public:
    KMP2(std::string pat) : pat(pat) {
        // dp[状态][字符] = 下个状态
        dp = std::vector<std::vector<int>>(pat.length(), std::vector<int>(256, 0));
        // base case
        dp[0][pat[0]] = 1;
        // 影子状态 X 初始为 0
        int X = 0;
        // 构建状态转移图
        for (size_t j = 1; j < pat.length(); j++) {
            for (size_t c = 0; c < 256; c++)
                dp[j][c] = dp[X][c];
            dp[j][pat[j]] = j + 1;
            // 更新影子状态
            X = dp[X][pat[j]];
        }
    }

    int search(std::string txt, size_t pos = 0) {
        // pat 的初始态为 0
        int j = 0;
        for (size_t i = pos; i < txt.length(); i++) {
            // 计算 pat 的下一个状态
            j = dp[j][txt[i]];
            // 到达终止态，返回结果
            if (j == pat.length()) return i - pat.length() + 1;
        }
        // 没到达终止态，匹配失败
        return -1;
    };
};

class KMP {
    std::string pattern;
    std::vector<int> next;

    void buildNext() {
        for (int i = 1, j = 0; i < pattern.size(); i++) {
            while (j && pattern[i] != pattern[j]) j = next[j - 1];
            if (pattern[i] == pattern[j]) j++;
            next[i] = j;
        }
    }

public:
    auto searchAll(std::string txt) {
        std::vector<size_t> p;
        for (size_t i = 0, j = 0; i < txt.size(); i++) {
            while (j && txt[i] != pattern[j]) j = next[j - 1];
            if (txt[i] == pattern[j]) j++;
            if (j == pattern.size()) {
                p.emplace_back(i - pattern.size() + 1);
                j = next[j - 1];
            }
        }
        return p;
    }

    size_t search(std::string txt, size_t pos = 0) {
        for (size_t i = pos, j = 0; i < txt.size(); i++) {
            while (j && txt[i] != pattern[j]) j = next[j - 1];
            if (txt[i] == pattern[j]) j++;
            if (j == pattern.size()) {
                return i - pattern.size() + 1;
            }
        }
        return -1;
    }

    KMP(std::string pattern) : pattern(pattern) {
        next.resize(pattern.size());
        buildNext();
    }
};

#endif