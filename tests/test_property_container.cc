#include <string>
#include <random>
#include <vector>
#include <iostream>

#include "include/property_container.h"
#include "include/property_printer.h"

int N = 10;
int M = 100000;

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


int main()
{
  std::vector<std::string> S {"property 1", "property 2"};
  std::vector<PropertyContainer *> Q;
  try{
    auto PC = new PropertyContainer({ {"property 1", new IntValue(0)}, {"property 2", new IntValue(1)} });
    Q.push_back(PC);
  } catch(std::bad_alloc&){
    std::cerr << "container alloc failed" << std::endl;
  }
  for(int i=2; i<M; ++i){
    std::string s = random_string(60);
    try{
      bool flag = Q[0]->add_property(s, new IntValue(i));
      if(flag) S.push_back(s);
      else i--;

    } catch(std::bad_alloc&){
      std::cerr<<"bad alloc"<<std::endl;
    }
  }
  
  for(auto &x: Q){
    // assert(x->get("theboxahaan")->type() == ValueType::kNull);
    for(int i=0; i < S.size(); i++){
      assert(x->get<IntValue>(S[i])->get() == i);
      // IntValue *q = static_cast<IntValue *>(x->get(S[i]));
      // assert(static_cast<IntValue *>(x->get(S[i]))->get() == i);
    }
    // PropertyPrinter::pprint(*x);
  }
  
  for(auto &x: Q) delete x; 
  
  return 0;
  


}
