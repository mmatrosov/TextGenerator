#pragma once

#include "Concatenator.h"
#include "Chain.h"

class Generator
{
public:
  Generator(const Chain& chain, std::istream& input);

  std::string genNextWord();

private:
  const std::string& pickRandomWord(const Chain::Edges& edges);

  const Chain& m_chain;
  Concatenator m_concatenator;

  std::uniform_real_distribution<double> m_randDistr;
  std::default_random_engine m_randEngine;
};
