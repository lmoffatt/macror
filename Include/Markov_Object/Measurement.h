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

    virtual Class_info myClassInfo() const override;
    virtual std::string myClass() const override;

    virtual bool empty() const override;
    virtual bool refersToValidObjects() const override;
    virtual bool invalid() const
    {
      return refersToValidObjects();
    }
    virtual std::set<std::string> referencedObjects() const override
    {
      return {unitId_};
    }
    virtual Measurement *create() const override
    {
      return new Measurement;
    }
    virtual Measurement *dynamicCast(Abstract_Object *o) const override
    {
      return dynamic_cast<Measurement*>(o);
    }
    virtual const Measurement *dynamicCast(const Abstract_Object *o) const override
    {
      return dynamic_cast<const Measurement*>(o);

    }
    virtual std::string ToString() const override;
    virtual std::string ToString(const Measurement_Unit * other) const override;

    virtual bool changeUnit(const Measurement_Unit* otherUnit);



    virtual T value()const override;
    virtual std::string unit()const override;


    virtual Measurement* pow(int n) const;

    virtual Measurement* times(const Measurement* other)const;

    virtual Measurement* over(const Measurement* other)const;

    virtual bool isUnknown() const;


    static
    bool is(const std::string &singleLine);
    static
    T get(const std::string &singleLine, std::size_t *pos);


    static T unknownValue();

    Measurement(T value, std::string unit);


    bool ToObject(const std::string &text, std::size_t &cursor);
  private:

    T value_;
    const std::string unitId_;
  };

}
#endif // MEASUREMENT_H
