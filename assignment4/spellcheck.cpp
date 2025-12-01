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
  auto spaceIter = find_all(source.begin(), source.end(), ::isspace); // FIXME
  
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
  /* TODO: Implement this method */
  return std::set<Misspelling>();
};

/* Helper methods */

#include "utils.cpp"