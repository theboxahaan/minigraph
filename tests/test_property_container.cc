#include <string>
#include <random>
#include <vector>

#include "include/property_container.h"
#include "include/property_printer.h"

int N = 10;
int M = 10;

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
  auto x = new PropertyContainer({ {"property 1", new IntValue(0)}, {"property 2", new IntValue(1)}  });
  for(int i=0; i<M; ++i){
    std::string s = random_string(30);
    S.push_back(s);
    x->add_property(s, new IntValue(i));
  }
  
  auto x2 = x->get("theboxahaan");
  assert(x2->type() == ValueType::kNull);
  PropertyPrinter::pprint(*x);
  
  delete x; 
  
  return 0;
  


}
