#include<vector>
#include<array>
#include<iostream>

#include "include/rtree.h"

int main()
{
  std::cout << "R_DIM: " << R_DIM << ", R_RECORDS_MAX: " << R_RECORDS_MAX << std::endl;
  std::vector<std::array<std::pair<int ,int>, 2>> input = {
    {{{23, 51},{24,52}}},
    {{{37, 38},{38,39}}},
    {{{8 , 34},{9 ,35}}},
    {{{9 , 96},{10,97}}},
    {{{6 , 35},{7 ,38}}},
    {{{46, 89},{47,90}}},
    {{{3 , 20},{4 ,21}}},
    {{{8 , 14},{9 ,15}}},
    {{{48, 63},{49,64}}},
  };
  
  // create the rtree
  auto rt = Rtree();
  std::cout<< "rtree built" << std::endl;
  for(auto &x: input){
    rt.insert(IdxEntry(Rectangle(x), nullptr)); 
  }
  return 0;
}
