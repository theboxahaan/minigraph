#include<vector>
#include<array>
#include<iostream>

#include "include/rtree.h"



int main()
{
  std::vector<std::array<std::pair<int ,int>, 2>> input = {
    {{{23, 51},{24,52}}},
    {{{37, 38},{38,39}}},
    {{{8 , 34},{9 ,35}}},
    {{{9 , 96},{10,97}}},
    {{{66, 35},{67,38}}},
    {{{46, 89},{47,90}}},
    {{{23, 20},{24,21}}},
    {{{83, 14},{84,15}}},
    {{{48, 63},{49,64}}},
  };
  
  // create the rtree
  auto rt = Rtree();
  std::cout<< "rtree built" << std::endl;
  for(auto &x: input){
    rt.insert(IdxEntry(Rectangle(x), nullptr)); 
    std::cout << "insert" << std::endl; 
  }
  return 0;
}
