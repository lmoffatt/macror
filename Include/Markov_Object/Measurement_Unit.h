#ifndef MEASUREMENT_UNIT_H
#define MEASUREMENT_UNIT_H
#include "Markov_Object/Abstract_Named_Object.h"

namespace Markov_Object {



  class ElementaryUnit;
  struct UnitCompare
  {
    bool operator()(const ElementaryUnit* one, const ElementaryUnit* two);
  };

  int abbrToN(char c);
  char nToAbbr(int n);
  char multiplicationSymbol();

  std::string nToFullName(int n);





  template<typename T>
  class Measurement;


  class Measurement_Unit:public virtual Abstract_Named_Object
  {
  public:
    static std::string getUnit(const std::string& singleLine, std::size_t& cursor);
    static std::string getUnit(const std::string& singleLine);

    static std::string ClassName();
    virtual std::string myClass()const override;


    static Class_info classInfo();

    static Measurement_Unit Dimensionless();
    virtual Class_info myClassInfo()const override;
    static std::set<std::string> SuperClasses();

    /// cast an Abstract_Object to Base_Unit
    virtual Measurement_Unit * dynamicCast(Abstract_Object* o)const override;
    virtual const Measurement_Unit * dynamicCast(const Abstract_Object* o)const override;


    virtual std::string fullName()const;

    virtual Measurement_Unit *pow(int exponent) const;
    virtual std::pair<Measurement_Unit  *,double> times(const Measurement_Unit *other) const
    {

    }
    virtual int numericPrefixDigits() const
    {

    }


    ///
    virtual double conversionFactor(const Measurement_Unit *other)const
    {

    }



    virtual std::map<Measurement_Unit *, int, UnitCompare> elementaryTerms() const{

    }



    virtual bool sameAs(const Measurement_Unit* other)const{}


    virtual std::string ToString()const;
    virtual bool ToObject(Environment* e,const std::string& multipleLines,std::size_t& pos);


    virtual Measurement_Unit* create()const;

    virtual std::set<std::string> referencedObjects()const;


    virtual bool refersToValidObjects()const override;

    virtual std::size_t numFields()const;

    Measurement_Unit();


    Measurement_Unit(std::string fullname,
                     std::string name,
                     std::string terms,
                     Environment* e,
                     std::string tip,
                     std::string whatthis);

    Measurement_Unit(Environment* e);


  private:
    std::string idMagnitude_;
    std::string longName_;
    std::map<std::string,int> terms_;

    // Abstract_Object interface

    // Abstract_Named_Object interface
  public:
    virtual bool isReferenced() const
    {
      return true;
    }
    virtual bool isDuplicate() const
    {
      return false;
    }

    // Abstract_Object interface
  };











}

#endif // MEASUREMENT_UNIT_H
