#include <string>
#include <random>
#include <vector>
#include <iostream>

#include "include/property_container.h"
#include "include/property_printer.h"

// The test spawns N PropertyContainers each with M IntValues.
// After creation, assert that the stored values are equal to the initialised values
// Then delete containers


std::string random_string(std::size_t length)
{
  const std::string CHARS = "01234567890abcdefghijklmnopqrstuvwxyz";
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> distribution(0, CHARS.size()-1);

  std::string rs;
  for(std::size_t i=0; i<length; ++i){
    rs += CHARS[distribution(generator)];
  }

  return rs;

}


int main(int argc, char *argv[])
{

  int M = 10;
  int N = 1; 

  if(argc == 3){
    // no formatting checks here - assuming the test input in legal
    std::size_t pos;
    M = std::stoi(argv[1], &pos);
    N = std::stoi(argv[2], &pos);
  }
  std::cout << "M: " << M << ", N: " << N << std::endl;
  std::vector< std::vector<std::string>> S;
  std::vector<PropertyContainer> Q;
  std::cout << "constructing property containers..." << std::endl;
  for(int i=0; i< N; i++){
    try{
      // auto PC = new PropertyContainer({ {"property 1", new IntValue(0)}, {"property 2", new IntValue(1)} });
      //Q.push_back(PropertyContainer());
      Q.emplace_back();
      S.push_back(std::vector<std::string> {});
    } catch(std::bad_alloc&){
      std::cerr << "container alloc failed" << std::endl;
    }
  }

  std::cout << "adding properties..." << std::endl;
  for(int j=0; j<N; j++){
    for(int i=0; i<M; ++i){
      std::string s = random_string(60);
      try{
        bool flag = Q[j].add_property(s, std::make_unique<IntValue>(i) );
        if(flag) S[j].push_back(s);
        else i--;

      } catch(std::bad_alloc&){
        std::cerr<<"bad alloc"<<std::endl;
      }
    }
  }
  int index = 0;
  for(auto &x: Q){
    std::cout << "testing: " << index << std::endl;
    assert(x.get<IntValue>("theboxahaan")->type() == ValueType::kNull);
    for(int i=0; i < S[index].size(); i++){
      assert(x.get<IntValue>(S[index][i])->get() == i);
    }
    index++;
    // PropertyPrinter::pprint(*x);
  }
  
  std::cout << "deleting containers... " << std::endl; 
  // letting Q go out of scope should ideally dete all containers
  // for(auto &x: Q) delete x; 
  
  return 0;
  


}
