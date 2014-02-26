#include "Markov_Object/Quantity.h"


namespace Markov_Object {

  std::string Quantity::ClassName()
  {
    return "Quantity";
  }

  std::string Quantity::myClass() const
  {
    return ClassName();
  }

  Class_info Quantity::classInfo()
  {
    return {
        ClassName(),
            SuperClasses(),
            true,
            true,
            false
      };
  }

  Class_info Quantity::myClassInfo() const
  {
    return classInfo();
  }

  std::set<std::string> Quantity::SuperClasses()
  {
    auto mySC=Abstract_Named_Object::SuperClasses();
    mySC.insert(ClassName());
    return mySC;

  }

  Quantity *Quantity::create() const
  {
    return new Quantity;
  }

  std::string Quantity::ToString() const
  {
    if (Abstract_Named_Object::idName().empty())
      return "";
    else
      {
        std::string o=ClassName()+" "+ Abstract_Named_Object::ToString();
        o+=def_.ToString();
        return o;
      }
  }

  bool Quantity::ToObject(Environment *e, const std::string &text, std::size_t &cursor)
  {
    std::size_t cursor0=cursor;
    Abstract_Named_Object::skipSpaces(text,cursor);
    auto clsnms=ClassName().size();

    // it should have the classname
    if ((!text.empty())&&(text.substr(cursor,clsnms)==ClassName()))
      {
        cursor+=clsnms;
        if (Abstract_Named_Object::ToObject(e,text,cursor))
          {
            if (def_.ToObject(e,text,cursor))
              return true;
          }
      }
    cursor=cursor0;
    return false;

  }


  bool Quantity::refersToValidObjects() const
  {
  }

  std::set<std::string> Quantity::referencedObjects() const
  {
    std::set<std::string> out;
    for (auto t:def_.value())
      {
        out.insert(t.first);
      }
    return out;
  }

  bool Quantity::ToObject(Environment *e, const std::string &text)
  {
    std::size_t n=0;
    return ToObject(e,text,n);
  }




  Quantity::Quantity():
    Abstract_Object(),
    Abstract_Named_Object(){}

  Quantity::Quantity(Environment *e):
    Abstract_Object(e),
    Abstract_Named_Object(e){}

  Quantity::Quantity(Environment *e,
                     std::string quantityAbreviation,
                     std::map<std::string, int> quatityDefinition,
                     std::string longName,
                     std::string whatthis)
    :
      Abstract_Object(e),
      Abstract_Named_Object(e,quantityAbreviation,longName,whatthis),
      def_(e,quatityDefinition)
  {}

  Quantity::Quantity(Environment *e,
                     std::string quantityAbreviation,
                     std::string quatityDefinition,
                     std::string longName,
                     std::string whatthis)
    :
      Abstract_Object(e),
      Abstract_Named_Object(e,quantityAbreviation,longName,whatthis),
      def_(e,QuantityExpression::getDefinition(quatityDefinition))
  {}













}

