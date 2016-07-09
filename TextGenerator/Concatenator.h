#pragma once

class Concatenator
{
public:
  explicit Concatenator(int order);

  void pushWord(const std::string& word);
  void popWord();

  int getCurrentOrder() const;

  // ToDo: it will be more efficient to represent concatenation as a deque of strings and provide a hash for it
  const std::string& getConcatenation() const;

private:
  int m_order;
  int m_currentOrder = 0;
  std::string m_concatenation;
};
