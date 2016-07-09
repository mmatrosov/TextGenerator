#include "stdafx.h"
#include "Trainer.h"

#include "WordStream.h"
#include "SequenceMaker.h"

Trainer::Trainer(int order) : m_order(order)
{
  assert(order >= 0);
}

Chain Trainer::createChainFromFiles(const std::vector<fs::path>& files)
{
  m_counts.clear();

  for (const auto& file : files)
  {
    std::clog << "Processing file " << file << "...";
    updateCountsFromFile(file);
    std::clog << " done" << std::endl;
  }

  Chain chain;

  chain.order = m_order;
  for (auto& item : m_counts)
  {
    chain.content[item.first] = counterToEdges(item.second);
  }

  return chain;
}

void Trainer::updateCountsFromFile(const fs::path& file)
{
  fs::ifstream input(file);
  WordStream wordStream(input);

  std::string word;
  SequenceMaker sequenceMaker(m_order);

  while (wordStream >> word)
  {
    if (sequenceMaker.getCurrentSize() == m_order)
    {
      auto sequence = sequenceMaker.getSequence();
      m_counts[sequence][word]++;
    }

    sequenceMaker.pushWord(word);
  }
}

Chain::Edges Trainer::counterToEdges(NextWordsCounter& counter)
{
  int wordsCount = 0;
  for (const auto& item : counter)
  {
    wordsCount += item.second;
  }

  Chain::Edges edges;
  edges.reserve(counter.size());

  for (auto& item : counter)
  {
    auto probability = item.second / static_cast<double>(wordsCount);
    auto& word = item.first;
    edges.push_back({ probability, std::move(word) });
  }

  // Sort edges so the most probable come first
  std::sort(edges.begin(), edges.end(), 
    [](const Chain::Edge& edge1, const Chain::Edge& edge2)
    {
      return edge1.probability > edge2.probability;
    });

  return edges;
}
