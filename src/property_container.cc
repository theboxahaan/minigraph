#include "include/property_container.h"

// The PropertyContainer is a container for various `Value`s of a `Node`. It just presents
// a collection of related properties but is not resposible for the memory management of 
// theses `Values`.
// This data model is very primitive as of now and the ownership model is expected to
// change as well.

// having null_value_ on the stack as it is static makes sense ?

NullValue PropertyContainer::null_value_ = NullValue();


// PropertyContainer::PropertyContainer(const std::initializer_list<std::pair<std::string, std::unique_ptr<Value> > > &list)
// {
//   for(auto &l: list){
//     auto t = properties_.insert({l.first, std::move(l.second)});
//     if(!t.second) delete this;
//   }
// }


// insert a property into the container and return true if it succeeds or false otherwise
bool PropertyContainer::add_property(std::string property_name, std::unique_ptr<Value> value)
{
  return properties_.insert({property_name, std::move(value)}).second ;
}


// the destructor clears the memory assoc with the `Value` subtype. The assumption is that
// the container has been initialised with objects that have been dynamically allocated.
// TODO have the initialiser of `Value` always initialise it on heap 
PropertyContainer::~PropertyContainer() noexcept
{
  // for(auto &elt: properties_) elt.second->clear();
  properties_.clear();
}
