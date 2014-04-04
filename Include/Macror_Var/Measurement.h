#ifndef MEASUREMENT_H
#define MEASUREMENT_H


#include "Macror_Var/Measurement_Unit.h"

namespace Macror_Var {
/*
  template<typename T>
  class Measurement: public  Abstract_Object
  {
    // Abstract_Object interface
  public:

    static std::string ClassName();



    virtual std::set<std::string> mySuperClasses() const override;
    virtual std::string myClass() const override;

    virtual Measurement *create() const override;
    virtual Measurement *dynamicCast(Abstract_Object *o) const override;
    virtual const Measurement *dynamicCast(const Abstract_Object *o) const override;
    virtual std::string ToString() const override;

    virtual std::string ToString(const Measurement_Unit * other) const override;

    virtual bool changeUnit(const Measurement_Unit* otherUnit);

    virtual T value()const override;
    virtual std::string unit()const override;


    Measurement& pow(int n);

    Measurement& operator*= (const Measurement& other);

    Measurement& operator+= (const Measurement& other);

    Measurement& operator/= (const Measurement& other);


    virtual bool isUnknown() const;


    static
    bool is(const std::string &singleLine);

    static
    T get(const std::string &singleLine, std::size_t *pos);


    static T unknownValue();


    Measurement(T value, std::string unit);

protected:
    bool ToObject(const std::string &text, std::size_t &cursor);
  private:

    T value_;

    const std::string unitId_;
  };

  */
}
#endif // MEASUREMENT_H
