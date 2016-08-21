#pragma once

#include "Chain.h"

namespace boost 
{
  namespace serialization 
  {
    template<class Archive>
    void serialize(Archive& ar, Chain::Edge& edge, const unsigned int version)
    {
      ar & edge.p;
      ar & edge.word;
    }

    template<class Archive>
    void serialize(Archive& ar, Chain::Data& data, const unsigned int version)
    {
      ar & data.order;
      ar & data.nodes;
    }
  }
}