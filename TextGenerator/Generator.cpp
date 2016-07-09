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

  for (const auto& edge : edges)
  {
    sample -= edge.probability;
    if (sample < 0)
    {
      return edge.word;
    }
  }

  // We may get here only if
  // 1. Probabilites do not sum up to 1. This should trigger an assertion.
  // 2. There were some floating point rounding issues. This should return last word.
  // However, distinguishing one from another would require some carefully deduced epsilon. I don't want to
  // mess with it, just assume it is the second option.
  return edges.back().word;
}
