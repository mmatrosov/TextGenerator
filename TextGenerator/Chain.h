#pragma once

struct Chain
{
  using TailHash = std::string;

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
