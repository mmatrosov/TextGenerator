#include "stdafx.h"
#include "SequenceMaker.h"

#include <boost/algorithm/cxx11/all_of.hpp>

SequenceMaker::SequenceMaker(int maxSize) : m_maxSize(maxSize)
{
  assert(maxSize >= 0);
}

void SequenceMaker::pushWord(const std::string& word)
{
  assert(boost::algorithm::all_of(word, boost::is_alpha()));

  if (m_maxSize == m_currentSize)
  {
    popWord();
  }
  else
  {
    m_currentSize++;
  }

  if (!m_sequence.empty())
  {
    m_sequence += ' ';
  }

  m_sequence += word;
}

void SequenceMaker::popWord()
{
  if (m_maxSize > 1)
  {
    m_sequence.erase(0, m_sequence.find(' ') + 1);
  }
  else
  {
    m_sequence.clear();
  }
}

int SequenceMaker::getCurrentSize() const
{
  return m_currentSize;
}

const WordsSequence& SequenceMaker::getSequence() const
{
  return m_sequence;
}
