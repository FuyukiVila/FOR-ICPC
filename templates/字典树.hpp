#ifndef __TRIE_HPP
#define __TRIE_HPP

#include "bits/stdc++.h"

// Trie<ElementType> 是一个字典树模板类, ElementType 是字典树中存储的元素类型, 默认为 char
template<class T = char>
class Trie {
private:
    typedef T element_type;

    struct TrieNode {
        size_t wordCount;
        std::map<element_type, std::shared_ptr<TrieNode> > next;

        TrieNode() : wordCount(0), next(std::map<element_type, std::shared_ptr<TrieNode> >()) {}

    };

    std::shared_ptr<TrieNode> _root;

    size_t dfs(std::shared_ptr<TrieNode> p) {
        if (p == nullptr) return 0;
        size_t res = p->wordCount;
        for (auto const &i: p->next) res += dfs(i.second);
        return res;
    }

public:

    Trie() { _root = std::make_shared<TrieNode>(); }

    std::shared_ptr<TrieNode> root() { return _root; }

    std::shared_ptr<TrieNode> begin() { return _root; }

    std::shared_ptr<TrieNode> end() { return nullptr; }

    // 清空Trie
    void clear() { _root = std::make_shared<TrieNode>(); }

    // 插入一个单词到Trie树的某个前缀上, 返回最后一个字符插入的位置. word:插入的单词, pos:前缀最后一个字符的位置, 空表示从根节点开始插入.
    std::shared_ptr<TrieNode> insert(const std::basic_string<element_type> &word, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? _root : pos;
        for (char const &i: word) {
            if (location->next[i] == nullptr) {
                location->next[i] = std::make_shared<TrieNode>();
            }
            location = location->next[i];
        }
        location->wordCount++;
        return location;
    }

    // 插入一个字符到Trie树的某个前缀上, 返回最后一个字符插入的位置. character:插入的字符, pos:前缀最后一个字符的位置, 空表示从根节点开始插入.
    std::shared_ptr<TrieNode> insert(element_type character, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? _root : pos;
        if (location->next[character] == nullptr) {
            location->next[character] = std::make_shared<TrieNode>();
        }
        location = location->next[character];
        location->wordCount++;
        return location;
    }

    // 查找Trie树中以某个前缀开头的单词的位置, 返回最后一个字符的位置, 未找到返回空指针. word:查找的前缀, pos:前缀最后一个字符的位置, 空表示从根节点开始查找.
    std::shared_ptr<TrieNode> find(const std::basic_string<element_type> &word, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? _root : pos;
        for (int i = 0; i < word.length() && location; i++)
            location = location->next[word[i]];
        return location;
    }

    // 查找Trie树中以某个前缀开头的字符的位置, 返回最后一个字符的位置, 未找到返回空指针. character:查找的字符, pos:前缀最后一个字符的位置, 空表示从根节点开始查找.
    std::shared_ptr<TrieNode> find(element_type character, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? _root : pos;
        return location->next[character];
    }

    // 返回Trie树中以某个前缀开头的单词的数量, pos:前缀最后一个字符的位置, 空表示从根节点开始查找.
    size_t count(const std::basic_string<element_type> &word, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? _root : pos;
        for (int i = 0; i < word.length() && location; i++)
            location = location->next[word[i]];
        return location == nullptr ? 0 : location->wordCount;
    }

    // 返回Trie树中以某个前缀开头的字符的数量, pos:前缀最后一个字符的位置, 空表示从根节点开始查找.
    size_t count(element_type character, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? _root : pos;
        return location->next[character] == nullptr ? 0 : location->next[character]->wordCount;
    }

    // 删除Trie树中以某个前缀开头的单词, 返回最后一个字符的位置, 未找到返回空指针. word:查找的前缀, pos:前缀最后一个字符的位置, 空表示从根节点开始查找.
    std::shared_ptr<TrieNode> erase(const std::basic_string<element_type> &word, std::shared_ptr<TrieNode> pos = nullptr, size_t count = 1) {
        auto location = (pos == nullptr) ? _root : pos;
        for (int i = 0; i < word.length() && location; i++)
            location = location->next[word[i]];
        if (location == nullptr) return nullptr;
        location->wordCount -= min(count, location->wordCount);
        return location;
    }

    // 删除Trie树中以某个前缀开头的字符, 返回最后一个字符的位置, 未找到返回空指针. character:查找的字符, pos:前缀最后一个字符的位置, 空表示从根节点开始查找.
    std::shared_ptr<TrieNode> erase(element_type character, std::shared_ptr<TrieNode> pos = nullptr, size_t count = 1) {
        auto location = (pos == nullptr) ? _root : pos;
        if (location->next[character] == nullptr) return nullptr;
        location->next[character]->wordCount -= min(count, location->next[character]->wordCount);
        return location;
    }

    // 返回Trie树中以某个前缀开头的所有包含单词前缀的单词总数, pos:前缀最后一个字符的位置, 空表示从根节点开始查找.
    size_t countPrefix(const std::basic_string<element_type> &word, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? _root : pos;
        for (int i = 0; i < word.length() && location; i++)
            location = location->next[word[i]];
        return dfs(location);
    }

    // 返回Trie树中以某个前缀开头的所有包含字符前缀的单词总数, pos:前缀最后一个字符的位置, 空表示从根节点开始查找.
    size_t countPrefix(element_type character, std::shared_ptr<TrieNode> pos = nullptr) {
        auto location = (pos == nullptr) ? _root : pos;
        return dfs(location->next[character]);
    }

};

#endif