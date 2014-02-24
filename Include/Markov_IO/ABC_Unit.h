#ifndef ABC_UNIT_H
#define ABC_UNIT_H
#include <vector>

#include "Markov_Console/Markov_CommandManager.h"

namespace Markov_IO


{
  class ElementaryUnit;

  struct UnitCompare
  {
    bool operator()(const ElementaryUnit* one, const ElementaryUnit* two);
  };

  int abbrToN(char c);
  char nToAbbr(int n);
  char multiplicationSymbol();

  std::string nToFullName(int n);


  class ABC_Unit
  {
  public:


    virtual  std::string fullName()const=0;

    virtual  std::string abbr()const=0;


    virtual ABC_Unit* pow(int exponent)const=0;

    virtual ABC_Unit* times(const ABC_Unit* other)const=0;

    virtual int numericPrefixDigits()const=0;

    virtual const
    std::map<ElementaryUnit*,int,UnitCompare>& terms()const=0;

  };

  class DerivedUnit: public ABC_Unit
  {
  public:

    virtual  std::string fullName()const;
    virtual  std::string abbr()const;

    virtual ABC_Unit* pow(int exponent)const;

    virtual ABC_Unit* times(const ABC_Unit* other)const;




    friend class ElementaryUnit;

    virtual const
    std::map<ElementaryUnit*,int,UnitCompare> &terms()const;

    virtual int numericPrefixDigits()const;

    virtual double removePrefixDigits();

  private:
    DerivedUnit(const ABC_Unit& other);
    std::map<ElementaryUnit*,int,UnitCompare> myTerms;
    int prefixDigits;
  };

  class ElementaryUnit: public ABC_Unit

  {
  public:
    virtual std::string name()const;
    virtual  std::string fullName()const;
    virtual  std::string abbr()const;

    virtual int decimalPlaces()const;

    virtual ElementaryUnit* pow10(int exponent)const;

    virtual ABC_Unit* pow(int exponent)const;

    virtual ABC_Unit* times(const ABC_Unit* other)const;


    virtual int numericPrefixDigits()const;

    virtual double removePrefixDigits();

    virtual bool operator < (const ElementaryUnit& other)const;
    virtual const
    std::map<ElementaryUnit*,int,UnitCompare> &terms()const;

    static ElementaryUnit* create(Markov_Console::Markov_CommandManager *cm,
                   const std::string& name,
                   const std::string& abbr, int digits=0);




  private:
    ElementaryUnit();
    ElementaryUnit(const ElementaryUnit& other);
    std::string myName;
     std::string myabbr;
     std::map<ElementaryUnit*,int,UnitCompare> myTerms;
     int symbolicPrefixDigits;
     int prefixDigits;
  };





}


#endif // ABC_UNIT_H
