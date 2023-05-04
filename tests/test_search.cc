#include<vector>
#include<array>
#include<iostream>
#include <unordered_map>

#include "include/rtree.h"


int main()
{
    auto rt  = Rtree(true);
    std::vector<std::array<std::pair<Dim ,Dim>, 2>> input = {
    {{{-122.2962555, -122.2951035}, {37.8597504, 37.8599832}}},
  };

    IdxEntryVectorD v;
    rt.search_d(rt.root_d_[0].second, v, Rectangle(input[0]));
    std::cout << "size of results " << v.size() << std::endl;

    for(auto x: v){
        std::cout << "-> " << x.first[0].first << " " << x.first[0].second << " " << x.first[1].first << " " << x.first[1].second << " " << x.second <<  std::endl;
    }

}
