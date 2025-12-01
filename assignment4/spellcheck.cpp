#include "spellcheck.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  // 1.获取一个所有指向空白字符的迭代器构成的列表
  auto spaceIter = find_all(source.begin(), source.end(), 
    // 创建一个 Lambda，它内部调用 std::isspace
    [](unsigned char c) { return std::isspace(c); }
);
  
  // 2.构建一个初始化Token的函数
  auto buildToken = [&source] (auto it1, auto it2) {
    return Token(source, it1, it2);
  };

  // 3.对每对相邻空白字符迭代器之间的序列，调用Token的初始化函数
  Corpus tokens;
  auto inserter = std::inserter(tokens, tokens.end());
  std::transform(spaceIter.begin(), spaceIter.end() - 1, spaceIter.begin() + 1, inserter, buildToken);

  // 4.从std::set<Token>中删除空标记
  auto checkEmptyToken = [] (Token t) {
    return t.content.empty();
  };
  std::erase_if(tokens, checkEmptyToken);

  return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  namespace rv = std::ranges::views;
  // 1.跳过已经正确拼写的单词
  auto checkMisspell = [&dictionary] (const Token& t) {
    return !dictionary.contains(t.content);
  };

  // 2.查找仅有一个编辑距离的错误拼写
  auto giveSuggestions = [&dictionary] (const Token& t) {
    // 构造辅助函数
    auto oneDistance = [&t] (const std::string& s) {
      return levenshtein(s, t.content) == 1;
    };

    auto view = rv::filter(dictionary, oneDistance);
    std::set<std::string> suggestions(view.begin(), view.end());
    return Misspelling{t, suggestions};
  };

  // 3.删除没有建议的错误拼写
  auto isNotEmpty = [] (const Misspelling& m) {
    return !m.suggestions.empty();
  };

  auto missspellings = source 
    | rv::filter(checkMisspell)
    | rv::transform(giveSuggestions)
    | rv::filter(isNotEmpty);

  return std::set<Misspelling>(missspellings.begin(), missspellings.end());
};

/* Helper methods */

#include "utils.cpp"