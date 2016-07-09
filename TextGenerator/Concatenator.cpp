#include "stdafx.h"
#include "Concatenator.h"

#include <boost/algorithm/cxx11/all_of.hpp>

Concatenator::Concatenator(int order) : m_order(order)
{
  assert(order >= 0);
}

void Concatenator::pushWord(const std::string& word)
{
  assert(boost::algorithm::all_of(word, boost::is_alpha()));

  if (m_order == m_currentOrder)
  {
    popWord();
  }
  else
  {
    m_currentOrder++;
  }

  if (!m_concatenation.empty())
  {
    m_concatenation += ' ';
  }

  m_concatenation += word;
}

void Concatenator::popWord()
{
  if (m_order > 1)
  {
    m_concatenation.erase(0, m_concatenation.find(' ') + 1);
  }
  else
  {
    m_concatenation.clear();
  }
}

int Concatenator::getCurrentOrder() const
{
  return m_currentOrder;
}

const std::string& Concatenator::getConcatenation() const
{
  return m_concatenation;
}
