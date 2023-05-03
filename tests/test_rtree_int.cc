#include<vector>
#include<array>
#include<iostream>

#include "include/rtree.h"

int main()
{
  std::cout << "R_DIM: " << R_DIM << ", R_RECORDS_MAX: " << R_RECORDS_MAX << std::endl;
//  std::vector<std::array<std::pair<int ,int>, 2>> input = {
//    {{{23, 51},{24,52}}},
//    {{{37, 38},{38,39}}},
//    {{{8 , 34},{9 ,35}}},
//    {{{9 , 96},{10,97}}},
//    {{{6 , 35},{7 ,38}}},
//    {{{46, 89},{47,90}}},
//    {{{3 , 20},{4 ,21}}},
//    {{{8 , 14},{9 ,15}}},
//    {{{48, 63},{49,64}}},
//  };
//  
//  // create the rtree
//  auto rt = Rtree();
//  for(auto &x: input){
//    rt.insert(IdxEntry(Rectangle(x), nullptr)); 
//  }
//  return 0;




  int numPoints = 10000000;
  int rand_mod = 9000;
  int dim_diff = 200;

  for(int iter = 0; iter < 1; iter++){
    srand(time(NULL));

    std::vector<std::array<std::pair<Dim, Dim>, 2>> input;
    
    for(int i = 0; i < numPoints; i++){
      Dim x1 = rand() % rand_mod;
      Dim y1 = rand() % rand_mod;
      input.push_back(std::array<std::pair<Dim, Dim>, 2>({std::pair<Dim, Dim>({x1, (x1 + rand() % dim_diff) + 1}), 
                                                          std::pair<Dim, Dim>({y1, (y1 + rand() % dim_diff) + 1})}));
    }


    auto rt = Rtree();
    // std::cout<< "rtree built" << std::endl;
    for(auto &x: input){
      rt.insert(IdxEntry(Rectangle(x), nullptr)); 
      // std::cout << "insert" << std::endl; 
    }
    
    rand_mod = rand_mod + 1000;
    numPoints = numPoints + 100000;
    dim_diff = dim_diff + 10;
    // rt.walk();
  }

  return 0;

}
