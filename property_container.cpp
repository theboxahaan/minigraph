#include <unordered_map>
#include <string>

enum class ValueType {kInt, kString , kFloat};

class Value {
  public:
    virtual ValueType repr() = 0;
    virtual ~Value();
};


class IntValue : Value {
  private:
    ValueType type_ = ValueType::kInt;
  
  public:
    
    
    ValueType repr()
    {
      return type_;
    } 

};

class PropertyContainer {
  private:
    std::unordered_map<std::string, std::shared_ptr<Value>> properties_;
    
  public:
    void add_property(std::string property_name, std::shared_ptr<Value> value)
    {
      properties_.insert({property_name, value});
    }
};


// try subclassing for types of properties
int main()
{
  auto x = PropertyContainer();

}
