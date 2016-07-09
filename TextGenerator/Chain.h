#pragma once

#include "Common.h"

struct Chain
{
  struct Edge
  {
    double probability;
    std::string word;
  };
  using Edges = std::vector<Edge>;  // Probabilities of these edges are assumed to sum up to 1.0
  using Content = std::unordered_map<WordsSequence, Edges>;

  int order;
  Content content;
};
