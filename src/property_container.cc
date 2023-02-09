#include "include/property_container.h"

// The PropertyContainer is a container for various `Value`s of a `Node`. It just presents
// a collection of related properties but is not resposible for the memory management of 
// theses `Values`.
// This data model is very primitive as of now and the ownership model is expected to
// change as well.
// TODO think about using smart pointers for `Value` ownership.
// Hence for now, `Values` can dereference to null which is unsafe.

PropertyContainer::PropertyContainer(const std::initializer_list<std::pair<std::string, Value*> > &list)
  {
    for(auto &l: list){
      properties_.insert({l.first, l.second});
    }
  }

void PropertyContainer::add_property(std::string property_name, Value* value)
  {
    properties_.insert({property_name, value});
  }

