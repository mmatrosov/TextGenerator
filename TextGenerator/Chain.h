#pragma once

#include "Common.h"

struct Chain
{
  struct Edge
  {
    double probability;
    std::string word;
  };
  using Edges = std::vector<Edge>;
  using Content = std::unordered_map<WordsSequence, Edges>;

  int order;
  Content content;
};
