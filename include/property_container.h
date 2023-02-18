#ifndef MINIGRAPH_PROPERTY_CONTAINER_H
#define MINIGRAPH_PROPERTY_CONTAINER_H

#include <unordered_map>
#include <string>

enum class ValueType {kNull, kInt, kFloat};

class Value {

  public:
    virtual ValueType type() = 0;
    // inline void clear() { delete this; }  
  
  //protected:
    // make the destructor protected to prevent object initialisation on the stack
    virtual ~Value() {}
};


class IntValue : public Value {

  private:
    ValueType type_ = ValueType::kInt;
    int value_;

  public:
    IntValue(int value) : value_{value} {}
    // adding default constructor for compat with NullType
    IntValue() {}
    
    inline ValueType type() { return type_; }

    inline int get() { return value_; }

};


class FloatValue : public Value {

  private:
    ValueType type_ = ValueType::kFloat;
    float value_;

  public:
    FloatValue(float value) : value_{value} {}
    // adding default constructor for compat with NullType
    FloatValue() {}
    
    inline ValueType type() { return type_; }

    float get() { return value_; }

};

//TODO come up with something that does not depend on the derived types
class NullValue : public IntValue, public FloatValue {

  private:
    ValueType type_ = ValueType::kNull;

  public:
    NullValue() {}
    
    inline ValueType type() { return type_; }
};


// PropertyContainer is basically a wrapper around an unordered_map to contain different 
// `Value` subclasses.
// It also implements the `NullValue` static object which should always be returned in case
// of a failure.
class PropertyContainer {

  private:
    std::unordered_map<std::string, std::unique_ptr<Value> > properties_;
    // could inline static decl if using -std=c++17
    static NullValue null_value_;
    friend class PropertyPrinter; 
    // friend class PageWriter;

  public:
    PropertyContainer() {}
    // PropertyContainer(const std::initializer_list<std::pair<std::string, std::unique_ptr<Value> > > &);
    
    // define move constructor so that PropertyContainer can be push_back'd or emplace_back'd 
    
    PropertyContainer(PropertyContainer &&o) : properties_{std::move(o.properties_)} {}


    bool add_property(std::string , std::unique_ptr<Value> );
   
    // return a raw pointer to the `Value` object. Treat the pointer as a read only ptr
    // return a pointer to the null value in case nothing is reuturned.
    template <typename T>
    T* get(const std::string &key) const 
    {
      auto iter = properties_.find(key);
      if(iter != properties_.end()){
        return static_cast<T*>(iter->second.get());
      } else {
        return static_cast<T*>(&null_value_);
      }
    }
    
    ~PropertyContainer() noexcept;
};


#endif
