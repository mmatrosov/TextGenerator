#pragma once

// ToDo: derive it from std::istream
class WordStream
{
public:
  explicit WordStream(std::istream& stream);

  WordStream& operator>>(std::string& word);

  explicit operator bool() const;

private:
  std::istream& m_stream;
};
