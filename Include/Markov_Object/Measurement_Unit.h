#ifndef MEASUREMENT_UNIT_H
#define MEASUREMENT_UNIT_H
#include "Markov_Object/Abstract_Named_Object.h"
#include "Markov_Object/ScaledExpression.h"

namespace Markov_Object {


 template<typename T>
  class Measurement;

  class Measurement_Unit:public Abstract_Named_Object
  {
  public:
    static
    int abbrToN(char c);
    static
    std::string nToFullName(int n);

    static char nToAbbr(int n);


    static std::string ClassName();
    static Class_info classInfo();

    static std::set<std::string> SuperClasses();



    virtual std::string myClass()const override;
    virtual Class_info myClassInfo()const override;

    /// cast an Abstract_Object to Base_Unit
    virtual Measurement_Unit * dynamicCast(Abstract_Object* o)const override;
    virtual const Measurement_Unit * dynamicCast(const Abstract_Object* o)const override;


    virtual std::string myQuantity()const
    {
      return idQuantity_;
    }

    ScaledExpression self()const
    {
      return ScaledExpression(1.0,QuantityExpression({{idName(),1}}));
    }

    virtual ScaledExpression definition()const
    {
      return def_;
    }


    virtual ScaledExpression BaseDefinition()const
    {
      return baseDefinition({});
    }


    virtual bool empty()const override
    {

    }

    virtual bool invalid()const override
    {

    }

    ///
    virtual double conversionFactor(const Measurement_Unit *other)const
    {


    }

    virtual std::string ToString()const override;

    virtual Measurement_Unit *
    CreateObject(const std::string &text, std::size_t &cursor) const override
    {
      auto tmp=create();
      auto out=tmp->ToObject(text,cursor);
      if (out==nullptr)
        delete tmp;
      return out;
    }


    virtual Measurement_Unit* create()const override;

    virtual std::set<std::string> referencedObjects()const override;



    Measurement_Unit();


    Measurement_Unit(Environment* E,
                     std::string idName,
                     double scaleFactor,
                     std::string definition,
                     std::string idQuantity,
                     std::string fullname,
                     std::string whatthis);

    Measurement_Unit( Environment*  e);

  protected:
    virtual Measurement_Unit *
    ToObject(const std::string& multipleLines,std::size_t& pos) override;


  private:
    std::string idQuantity_;
    ScaledExpression def_;
    ScaledExpression baseDefinition(std::set<std::string> upstream) const;
  };











}

#endif // MEASUREMENT_UNIT_H
