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




  int numPoints = 100;
  int rand_mod = 600;
  for(int iter = 0; iter < 1; iter++){
    srand(time(NULL));

    std::vector<std::array<std::pair<Dim, Dim>, 2>> input;
    
    for(int i = 0; i < numPoints; i++){
      int x1 = rand() % rand_mod;
      int y1 = rand() % rand_mod;
      input.push_back(std::array<std::pair<Dim, Dim>, 2>({std::pair<Dim, Dim>({x1, (x1 + rand() % 100) + 1}), 
                                                          std::pair<Dim, Dim>({y1, (y1 + rand() % 100) + 1})}));
    }


    auto rt = Rtree();
    // std::cout<< "rtree built" << std::endl;
    for(auto &x: input){
      rt.insert(IdxEntry(Rectangle(x), nullptr)); 
      // std::cout << "insert" << std::endl; 
    }
    
    //rand_mod = rand_mod * 2;
    //numPoints = numPoints * 2;
    rt.walk();
  }

  return 0;

}
