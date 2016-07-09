#pragma once

#include "Chain.h"

class Trainer
{
public:
  explicit Trainer(int order);

  Chain createChainFromFiles(const std::vector<boost::filesystem::path>& files);

private:
  using NextWordsCounter = std::unordered_map<std::string, int>;
  using Counts = std::unordered_map<WordsSequence, NextWordsCounter>;

  void updateCountsFromFile(const boost::filesystem::path& file);

  static Chain::Edges counterToEdges(NextWordsCounter& counter);

  int m_order;
  Counts m_counts;
};