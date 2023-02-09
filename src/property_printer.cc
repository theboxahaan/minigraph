#include <iostream>

#include "include/property_container.h"
#include "include/property_printer.h"

void PropertyPrinter::pprint(const PropertyContainer &c)
{
  for(auto &elt: c.properties_){

    switch(elt.second->type()){
   
      case ValueType::kInt :  {
                                auto x = static_cast<IntValue *> (elt.second);
                                std::cout<<elt.first<<": "<< x->get() << std::endl;
                                break;
                              }
      case ValueType::kFloat :{
                                auto x = static_cast<FloatValue *> (elt.second);
                                std::cout<<elt.first<<": "<< x->get() << std::endl;
                                break;
                              }
    }
  }    
}



