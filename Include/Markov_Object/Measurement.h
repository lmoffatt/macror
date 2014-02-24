#ifndef MEASUREMENT_H
#define MEASUREMENT_H


#include "Markov_Object/Measurement_Unit.h"

namespace Markov_Object {

  template<typename T>
  class Measurement: public virtual Abstract_Object
  {

    // Abstract_Object interface
  public:

    static std::string ClassName();

    static Class_info classInfo();

    virtual Class_info myClassInfo() const;
    virtual std::string myClass() const;
    virtual bool isInternallyValid() const;

    virtual bool empty() const;
    virtual bool refersToValidObjects() const;
    virtual bool isValid() const
    {
      return refersToValidObjects();
    }
    virtual std::set<std::string> referencedObjects() const
    {
      return {unitId_};
    }
    virtual Measurement *create() const
    {
      return new Measurement;
    }
    virtual Measurement *dynamicCast(Abstract_Object *o) const
    {
      return dynamic_cast<Measurement*>(o);
    }
    virtual const Measurement *dynamicCast(const Abstract_Object *o) const
    {
      return dynamic_cast<const Measurement*>(o);

    }
    virtual std::string ToString() const;
    virtual std::string ToString(const Measurement_Unit * other) const;

    virtual bool changeUnit(const Measurement_Unit* otherUnit);

    virtual bool ToObject(Environment *e, const std::string &text, std::size_t &cursor);
    virtual bool ToObject(Environment *e, const std::string &text);


    virtual T value()const;
    virtual const Measurement_Unit* unit()const;


    virtual Measurement* pow(int n) const;

    virtual Measurement* times(const Measurement* other)const;

    virtual Measurement* over(const Measurement* other)const;

    virtual bool isUnknown() const;


    static
    bool is(const std::string &singleLine);
    static
    T get(const std::string &singleLine, std::size_t *pos);


    static T unknownValue();

    Measurement(Environment* E,T value, std::string unit);


  private:

    T value_;
    const std::string unitId_;
  };

}
#endif // MEASUREMENT_H
