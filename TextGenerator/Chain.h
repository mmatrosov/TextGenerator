#pragma once

#include "Common.h"

struct Chain
{
  struct Edge
  {
    double p;  // Cumulative probability
    std::string word;
  };
  // Cumulative probabilities of the edges within this structure are 
  // assumed to increase, with the last one being equal to 1.0
  using Edges = std::vector<Edge>;
  using Nodes = std::unordered_map<WordsSequence, Edges>;

  int order;
  Nodes nodes;
};
