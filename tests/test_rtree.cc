#include<vector>
#include<array>
#include<iostream>

#include "include/rtree.h"

int main()
{
  std::cout << "R_DIM: " << R_DIM << ", R_RECORDS_MAX: " << R_RECORDS_MAX << std::endl;
  std::vector<std::array<std::pair<Dim ,Dim>, 2>> input = {
    // {{{23, 51},{24,52}}},
    // {{{37, 38},{38,39}}},
    // {{{8 , 34},{9 ,35}}},
    // {{{9 , 96},{10,97}}},  
    // {{{6 , 35},{7 ,38}}},
    // {{{46, 89},{47,90}}},
    // {{{3 , 20},{4 ,21}}},
    // {{{8 , 14},{9 ,15}}},
    // {{{48, 63},{49,64}}},
    {{{40.4342149, 40.4427254},{-86.9194118,-86.9152541}}},
    {{{40.4342049, 40.4427154},{-86.9194018,-86.9152441}}},
    {{{40.4602579, 40.4673138},{-86.9620917,-86.9620512}}},
    {{{40.4602479, 40.4673038},{-86.9620817,-86.9620412}}},
    
  };
  
  // 40.4342049, -86.9152441
  // 40.4427154, -86.9194018

  // 40.4602479, -86.9620412
  // 40.4673038, -86.9620817


  //create the rtree
  auto rt = Rtree();
  for(auto &x: input){
    // rt.insert(IdxEntry(Rectangle(x), nullptr)); 
    rt.insert_d(IdxEntryD(Rectangle(x), 0)); 
  }
  rt.walk_d();
  // rt.read_from_offset(174);
  // rt.read_from_offset(516);
  // db_out.close();
  // db_in.close();
  
  // return 0;




  // int numPoints = 400;
  // int rand_mod = 700;
  // for(int iter = 0; iter < 1; iter++){
  //   srand(time(NULL));

  //   std::vector<std::array<std::pair<Dim, Dim>, 2>> input;
    
  //   for(int i = 0; i < numPoints; i++){
  //     float x1 = static_cast<float>(rand() % rand_mod) + static_cast<float>((rand() % 1000)/100000.0);
  //     float y1 = static_cast<float>(rand() % rand_mod + (rand() % 1000)/100000.0);
  //     input.push_back(std::array<std::pair<Dim, Dim>, 2>({std::pair<Dim, Dim>({x1, (x1 + rand() % 200 + (rand() % 1000)/100000.0) + 1}), 
  //                                                         std::pair<Dim, Dim>({y1, (y1 + rand() % 200 + (rand() % 1000)/100000.0) + 1})}));
  //     std::cout << x1 << "," << y1 << std::endl;
  //   }


  //   auto rt = Rtree();
  //   // std::cout<< "rtree built" << std::endl;
  //   for(auto &x: input){
  //     // rt.insert(IdxEntry(Rectangle(x), nullptr)); 
  //     rt.insert_d(IdxEntryD(Rectangle(x), 0)); 
  //     // std::cout << "insert" << std::endl; 
  //   }
    
  //   //rand_mod = rand_mod * 2;
  //   //numPoints = numPoints * 2;
  //   rt.walk_d();
  // }

  db_out.close();
  db_in.close();

  return 0;

}
