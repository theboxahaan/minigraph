#include "include/property_container.h"
#include "include/property_printer.h"

int main()
{
  auto x = PropertyContainer({ {"property 1", new IntValue(111)}, {"property 2", new FloatValue(12.2)}  });
  PropertyPrinter::pprint(x);
  return 0;

}
