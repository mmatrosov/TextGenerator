#include "stdafx.h"
#include "Chain.h"

Chain::Chain(Data data) : m_data(std::move(data))
{
  assert(data.order >= 0);
  assert(boost::algorithm::all_of(data.nodes, [](const auto& node)
  {
    const WordsSequence& wordsSequence = node.first;
    const Edges& edges = node.second;
    return !wordsSequence.empty() && !edges.empty() && edges.back().p == 1.0 &&
      boost::range::is_sorted(edges, [](const Edge& e1, const Edge& e2) { return e1.p < e2.p; });
  }));
}

const Chain::Data& Chain::getData() const
{
  return m_data;
}
