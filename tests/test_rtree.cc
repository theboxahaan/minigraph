#include<vector>
#include<array>
#include<iostream>

#include<cstdlib>
#include<time.h>

#include "include/rtree.h"



int main()
{
  int numPoints = 10000;
  int rand_mod = 300;
  for(int iter = 0; iter < 10; iter++){
    srand(time(NULL));

    std::vector<std::array<std::pair<int ,int>, 2>> input;
    
    for(int i = 0; i < numPoints; i++){
      int x1 = rand() % rand_mod;
      int y1 = rand() % rand_mod;
      input.push_back(std::array<std::pair<int ,int>, 2>({std::pair<int ,int>({x1, (x1 + rand() % 100) + 1}), 
                                                          std::pair<int ,int>({y1, (y1 + rand() % 100) + 1})}));
    }
  
    // std::vector<std::array<std::pair<int ,int>, 2>> input = {
    //   {{{23, 51},{24,52}}},
    //   {{{37, 38},{38,39}}},
    //   {{{8 , 34},{9 ,35}}},
    //   {{{9 , 96},{10,97}}},
    //   {{{66, 35},{67,38}}},
    //   {{{46, 89},{47,90}}},
    //   {{{23, 20},{24,21}}},
    //   {{{83, 14},{84,15}}},
    //   {{{48, 63},{49,64}}},
    // };
    
  
    // for(auto rec : input){
    //   std::cout<<std::endl;
    //   for(auto dim : rec){
    //     std::cout<<dim.first<<" "<<dim.second<<std::endl;
    //   }
    // }
  
  
    // create the rtree
    auto rt = Rtree();
    // std::cout<< "rtree built" << std::endl;
    for(auto &x: input){
      rt.insert(IdxEntry(Rectangle(x), nullptr)); 
      // std::cout << "insert" << std::endl; 
    }
    
    rand_mod = rand_mod * 2;
    numPoints = numPoints * 2;
  }
  return 0;
}
