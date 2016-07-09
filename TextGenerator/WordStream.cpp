#include "stdafx.h"
#include "WordStream.h"

WordStream::WordStream(std::istream& stream) : m_stream(stream)
{
}

WordStream& WordStream::operator>>(std::string& word)
{
  while (m_stream >> word)
  {
    word.erase(
      std::remove_if(word.begin(), word.end(), !boost::is_alpha()),
      word.end());

    if (!word.empty())
    {
      break;
    }
  }

  boost::to_lower(word);

  return *this;
}

WordStream::operator bool() const
{
  return !!m_stream;
}
