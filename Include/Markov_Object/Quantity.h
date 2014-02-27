#ifndef QUANTITY_H
#define QUANTITY_H
#include <cstring>
#include "Markov_Object/Abstract_Named_Object.h"
#include "Markov_Object/Environment.h"
#include "Markov_Object/QuantityExpression.h"

namespace Markov_Object {

  class Quantity: public Abstract_Named_Object
  {
  public:
    // static methods


    static std::string ClassName();
    static Class_info classInfo();
    static std::set<std::string> SuperClasses();

    // virtual methods
    virtual std::string myClass()const override;
    virtual Class_info myClassInfo()const override;
    virtual Quantity *create() const override;
    virtual std::string ToString() const override;
    virtual bool empty() const override;
    virtual bool invalid() const override;

    virtual bool ToObject(const std::string &text, std::size_t &cursor) override;

    /// checks for the existance of all refered objects
    std::set<std::string> referencedObjects() const override;


    // new methods
    QuantityExpression definition()const;

    QuantityExpression self()const
    {
      return QuantityExpression({{idName(),1}});
    }



    Quantity();

    Quantity(Environment* e);


    Quantity(Environment* e,
             std::string magnitudeAbbreviation,
             std::map<std::string, int> quatityDefinition,
             std::string longName,
             std::string whatthis);

    Quantity(Environment* e,
             std::string magnitudeAbbreviation,
             std::string quatityDefinition,
             std::string longName,
             std::string whatthis);

  private:
    QuantityExpression definition(std::set<std::string> upstream) const;
    QuantityExpression def_;

  };



}






#endif // QUANTITY_H
