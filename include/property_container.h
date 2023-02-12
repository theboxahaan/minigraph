#ifndef MINIGRAPH_PROPERTY_CONTAINER_H
#define MINIGRAPH_PROPERTY_CONTAINER_H

#include <unordered_map>
#include <string>

enum class ValueType {kNull, kInt, kFloat};

class Value {

  public:
    virtual ValueType type() = 0;
    inline void clear() { delete this; }  
  
  protected:
    // make the destructor protected to prevent object initialisation on the stack
    virtual ~Value() {}
};


class IntValue : public Value {

  private:
    ValueType type_ = ValueType::kInt;
    int value_;

  public:
    IntValue(int value) : value_{value} {}
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
    FloatValue() {}
    
    inline ValueType type() { return type_; }

    float get() { return value_; }

};


class NullValue : public IntValue, public FloatValue {

  private:
    ValueType type_ = ValueType::kNull;
    bool value_;

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
    std::unordered_map<std::string, Value*> properties_;
    // could inline static decl if using -std=c++17
    static NullValue null_value_;
    friend class PropertyPrinter; 
    // friend class PageWriter;

  public:
    PropertyContainer(const std::initializer_list<std::pair<std::string, Value*> > &);
    bool add_property(std::string , Value* );
    
    template <typename T>
    T* get(const std::string &key) const 
    {
      auto iter = properties_.find(key);
      if(iter != properties_.end()){
        return static_cast<T*>(iter->second);
      } else {
        return static_cast<T*>(&null_value_);
      }
      // FIXME make null_value_ work with the generic T
      // else {
      //   return &null_value_;
      // }
    }
    
    ~PropertyContainer();
};


#endif
