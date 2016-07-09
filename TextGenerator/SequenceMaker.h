#pragma once

#include "Common.h"

class SequenceMaker
{
public:
  explicit SequenceMaker(int maxSize);

  void pushWord(const std::string& word);
  void popWord();

  int getCurrentSize() const;

  const WordsSequence& getSequence() const;

private:
  int m_maxSize;
  int m_currentSize = 0;
  WordsSequence m_sequence;
};
