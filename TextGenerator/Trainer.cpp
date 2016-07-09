#include "stdafx.h"
#include "Trainer.h"

#include "WordStream.h"
#include "Concatenator.h"

Trainer::Trainer(int order) : m_order(order)
{
}

Chain Trainer::createChainFromFiles(const std::vector<boost::filesystem::path>& files)
{
  m_counts.clear();

  for (const auto& file : files)
  {
    updateCountsFromFile(file);
  }

  Chain chain;

  chain.order = m_order;
  for (auto& item : m_counts)
  {
    chain.content[item.first] = counterToEdges(item.second);
  }

  return chain;
}

void Trainer::updateCountsFromFile(const boost::filesystem::path& file)
{
  boost::filesystem::ifstream input(file);
  WordStream wordStream(input);

  std::string word;
  Concatenator concatenator(m_order);

  while (wordStream >> word)
  {
    if (concatenator.getCurrentOrder() == m_order)
    {
      auto hash = computeHash(concatenator.getConcatenation());
      m_counts[hash][word]++;
    }

    concatenator.pushWord(word);
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
