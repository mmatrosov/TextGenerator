#pragma once

struct Chain
{
  using TailHash = std::hash<std::string>::result_type;

  struct Edge
  {
    double probability;
    std::string word;
  };
  using Edges = std::vector<Edge>;
  using Content = std::unordered_map<TailHash, Edges>;

  int order;
  Content content;
};

template<class T>
auto computeHash(const T& x)
{
  return std::hash<T>()(x);
}
