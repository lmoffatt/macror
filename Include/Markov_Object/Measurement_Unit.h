#ifndef MEASUREMENT_UNIT_H
#define MEASUREMENT_UNIT_H
#include "Markov_Object/Abstract_Named_Object.h"

namespace Markov_Object {


  class Measurement_Unit:public virtual Abstract_Named_Object
  {
  public:
    static std::string getUnit(const std::string& singleLine);

    static std::string ClassName();
    virtual std::string myClass()const override;


    static Class_info classInfo();
    virtual Class_info myClassInfo()const override;

    static std::set<std::string> SuperClasses();

    /// cast an Abstract_Object to Base_Unit
    virtual Measurement_Unit * dynamicCast(Abstract_Object* o)const override;
    virtual const Measurement_Unit * dynamicCast(const Abstract_Object* o)const override;


    virtual std::string longName()const;

    virtual std::string ToString()const;
    virtual bool ToObject(Environment* e,const std::string& multipleLines,std::size_t& pos);

    virtual bool isCreateable()const;

    virtual Measurement_Unit* create()const;

    virtual std::set<std::string> referencedObjects()const
    {
      return std::set<std::string>();
    }


    virtual bool refersToValidObjects()const override
    {
      return true;
    }

    virtual std::size_t numFields()const{return 0;}

    Measurement_Unit();

    Measurement_Unit(std::string abbreviation,
              std::string name,
              Environment* e,
              std::string tip,
              std::string whatthis);

    Measurement_Unit(Environment* e);


  private:

    std::string longName_;

  };

}

#endif // MEASUREMENT_UNIT_H
