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
    void serialize(Archive& ar, Chain& chain, const unsigned int version)
    {
      ar & chain.order;
      ar & chain.content;
    }
  }
}