#include "include/property_container.h"

// The PropertyContainer is a container for various `Value`s of a `Node`. It just presents
// a collection of related properties but is not resposible for the memory management of 
// theses `Values`.
// This data model is very primitive as of now and the ownership model is expected to
// change as well.
// TODO think about using smart pointers for `Value` ownership.
// Hence for now, `Values` can dereference to null which is unsafe.


// having null_value_ on the stack as it is static makes sense ?
// FIXME the constructor for `PropertyContainer` will deallocate all initialised elts
// to prevent memory leaks. Throw exception to signal an error to caller?


NullValue PropertyContainer::null_value_ = NullValue();


PropertyContainer::PropertyContainer(const std::initializer_list<std::pair<std::string, Value*> > &list)
{
  for(auto &l: list){
    auto t = properties_.insert({l.first, l.second});
    if(!t.second) delete this;
  }
}

bool PropertyContainer::add_property(std::string property_name, Value* value)
{
   return properties_.insert({property_name, value}).second ;
}


// the destructor clears the memory assoc with the `Value` subtype. The assumption is that
// the container has been initialised with objects that have been dynamically allocated.
// TODO have the initialiser of `Value` always initialise it on heap 
PropertyContainer::~PropertyContainer()
{
  for(auto &elt: properties_) elt.second->clear();
  properties_.clear();
}
