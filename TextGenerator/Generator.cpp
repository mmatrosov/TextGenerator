#include "stdafx.h"
#include "Generator.h"

#include "WordStream.h"

Generator::Generator(const Chain& chain, std::istream& input) : 
  m_chain(chain),
  m_sequenceMaker(chain.order),
  m_randDistr(0, 1)
{
  WordStream wordStream(input);

  for (int i = 0; i < chain.order; ++i)
  {
    std::string word;

    if (!(wordStream >> word))
    {
      throw std::runtime_error(("Too few initial words! "
        "Expected: " + std::to_string(chain.order) + ", provided: " + std::to_string(i) + ".").c_str());
    }

    m_sequenceMaker.pushWord(word);
  }
}

std::string Generator::genNextWord()
{
  auto it = m_chain.content.find(m_sequenceMaker.getSequence());
  if (it == m_chain.content.end())
  {
    throw std::runtime_error("Cannot generate next word! Train your chain better.");
  }

  std::string nextWord = pickRandomWord(it->second);

  m_sequenceMaker.pushWord(nextWord);

  return nextWord;
}

const std::string& Generator::pickRandomWord(const Chain::Edges& edges)
{
  assert(!edges.empty());

  double sample = m_randDistr(m_randEngine);

  auto it = std::lower_bound(edges.begin(), edges.end(), sample,
    [](const Chain::Edge& e1, double p)
    {
      return e1.p < p;
    });

  assert(it != edges.end());

  return it->word;
}
