#ifndef MINIGRAPH_PROPERTY_CONTAINER_H
#define MINIGRAPH_PROPERTY_CONTAINER_H

#include <unordered_map>
#include <string>

enum class ValueType {kInt, kFloat, kNull};

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


class NullValue : public Value {

  private:
    ValueType type_ = ValueType::kNull;
    int value_;

  public:
    NullValue() {}
    
    inline ValueType type() { return type_; }
};


class PropertyContainer {

  private:
    std::unordered_map<std::string, Value*> properties_;
    // could inline static decl if using -std=c++17
    static NullValue null_value_;
    friend class PropertyPrinter; 

  public:
    PropertyContainer(const std::initializer_list<std::pair<std::string, Value*> > &);
    void add_property(std::string , Value* );
    Value* get(const std::string &) const;
};


#endif
