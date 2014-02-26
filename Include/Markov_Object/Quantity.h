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

    virtual Quantity *create() const;
    virtual std::string ToString() const;

    virtual bool empty() const;

    virtual bool ToObject(Environment *e, const std::string &text, std::size_t &cursor);


    /// checks for the existance of all refered objects
    virtual bool refersToValidObjects()const;

    std::set<std::string> referencedObjects() const;


    virtual bool ToObject(Environment *e, const std::string &text);


    QuantityExpression definition()const
    {
      return definition({idName()});
    }

    QuantityExpression self()const
    {
      return QuantityExpression(getEnvironment(),{{idName(),1}});
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
    QuantityExpression definition(std::set<std::string> upstream) const
    {
      QuantityExpression out;
      if (getEnvironment()!=nullptr)
        {
          for (auto t:def_.value())
            {
              const Quantity* q=getEnvironment()->Q(t.first);
              if (q==nullptr)
                return nullptr;
              else if (upstream.count(q->idName())!=0)
                return self();
              else
                {
                  auto defq=q->definition(upstream)*t.second;
                  out+=defq;
                }

            }
        }
    }


    QuantityExpression def_;

  };



}






#endif // QUANTITY_H
