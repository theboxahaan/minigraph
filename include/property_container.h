#ifndef MINIGRAPH_PROPERTY_CONTAINER_H
#define MINIGRAPH_PROPERTY_CONTAINER_H

#include <unordered_map>
#include <string>

enum class ValueType {kInt, kString, kFloat};

class Value {

  public:
    virtual ValueType type() = 0;
    virtual ~Value() {}
};


class IntValue : public Value {

  private:
    ValueType type_ = ValueType::kInt;
    int value_;

  public:
    IntValue(int value) : value_{value} {}
    
    inline ValueType type() { return type_; }

    inline int get() { return value_; }

};


class FloatValue : public Value {

  private:
    ValueType type_ = ValueType::kFloat;
    float value_;

  public:
    FloatValue(float value) : value_{value} {}
    
    inline ValueType type() { return type_; }

    float get() { return value_; }

};


class PropertyContainer {

  private:
    std::unordered_map<std::string, Value*> properties_;
    friend class PropertyPrinter; 

  public:
    PropertyContainer(const std::initializer_list<std::pair<std::string, Value*> > &);
    void add_property(std::string , Value* );
};


#endif
