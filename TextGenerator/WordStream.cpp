#include "stdafx.h"
#include "WordStream.h"

WordStream::WordStream(std::istream& stream) : m_stream(stream)
{
}

WordStream& WordStream::operator>>(std::string& word)
{
  while (m_words.empty())
  {
    std::string line;
    if (!std::getline(m_stream, line))
    {
      return *this;
    }

    boost::split(m_words, line, !boost::is_alpha());
    m_words.erase(
      std::remove_if(m_words.begin(), m_words.end(), [](const std::string& str) { return str.empty(); }),
      m_words.end());
  }

  word = std::move(m_words.front());
  boost::to_lower(word);
  m_words.pop_front();

  return *this;
}

WordStream::operator bool() const
{
  return !!m_stream;
}
