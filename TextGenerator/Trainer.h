#pragma once

#include "Chain.h"

class Trainer
{
public:
  explicit Trainer(int order);

  Chain createChainFromFiles(const std::vector<fs::path>& files);

private:
  using NextWordsCounter = std::unordered_map<std::string, int>;
  using Counts = std::unordered_map<WordsSequence, NextWordsCounter>;

  void updateCountsFromFile(const fs::path& file);

  static Chain::Edges counterToEdges(NextWordsCounter& counter);

  int m_order;
  Counts m_counts;
};