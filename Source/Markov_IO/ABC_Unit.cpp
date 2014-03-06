#include "Markov_IO/MeasurementUnits.h"
#include "Markov_IO/auxiliarIO.h"

namespace Markov_IO
{
  bool UnitCompare::operator ()(const ElementaryUnit* one, const ElementaryUnit* two)
  {
    return *one<*two;

  }


  char nToAbbr(int n)
  {
    switch (n)
      {

      case 15:
        return char('P');
        break;
      case 12:
        return char('T');
        break;
      case 9:
        return char('G');
        break;
      case 6:
        return char('M');
        break;
      case 3:
        return char('k');
        break;
      case 0:
        return char(' ');
        break;
      case -1:
        return char('d');
        break;
      case -2:
        return char('c');
        break;
      case -3:
        return char('m');
        break;
      case -6:
        return char('u');
        break;
      case -9:
        return char('n');
        break;
      case -12:
        return char('p');
        break;
      case -15:
        return char('f');
        break;
      case -18:
        return char('a');
        break;

      default:
        return char('!');
      }
  }

  std::string nToFullName(int n)
  {
    switch (n)
      {

      case 15:
        return "Peta";
        break;
      case 12:
        return "Tera";
        break;
      case 9:
        return "Giga";
        break;
      case 6:
        return "Mega";
        break;
      case 3:
        return "kilo";
        break;
      case 0:
        return " ";
        break;
      case -1:
        return "deci";
        break;
      case -2:
        return "centi";
        break;
      case -3:
        return "mili";
        break;
      case -6:
        return "micro";
        break;
      case -9:
        return "nano";
        break;
      case -12:
        return "pico";
        break;
      case -15:
        return "femto";
        break;
      case -18:
        return "atto";
        break;

      default:
        return "!error!";
      }
  }






  DerivedUnit::DerivedUnit(const ABC_Unit &other):
    myTerms(other.terms()),
    prefixDigits(other.numericPrefixDigits())
  {}


  std::string DerivedUnit::fullName()const
  {
    std::string out;
    if (numericPrefixDigits()==1)
      {
        out+="10";
        out+=multiplicationSymbol();
      }
    else if (numericPrefixDigits()!=0)
      {
        out+="10^";
        out+=ToString(numericPrefixDigits());
        out+=multiplicationSymbol();
      }

    std::map<ElementaryUnit*,int,UnitCompare>::const_iterator it;
    for (it=myTerms.begin(); it!=myTerms.end(); ++it)
      {
        if (it!=myTerms.begin())
          out+=multiplicationSymbol();
        ElementaryUnit* u=it->first;
        out+=u->fullName();
        if (it->second!=1)
          {
            out+="^";
            out+=ToString(it->second);
          }
      }
    return out;
  }
  std::string DerivedUnit::abbr()const
  {
    std::string out;
    if (numericPrefixDigits()==1)
      {
        out+="10";
        out+=multiplicationSymbol();
      }
    else if (numericPrefixDigits()!=0)
      {
        out+="10^";
        out+=ToString(numericPrefixDigits());
        out+=multiplicationSymbol();
      }

    std::map<ElementaryUnit*,int,UnitCompare>::const_iterator it;
    for (it=myTerms.begin(); it!=myTerms.end(); ++it)
      {
        if (it!=myTerms.begin())
          out+=multiplicationSymbol();
        ElementaryUnit* u=it->first;
        out+=u->abbr();
        if (it->second!=1)
          {
            out+="^";
            out+=ToString(it->second);
          }
      }
    return out;
  }

  int DerivedUnit::numericPrefixDigits()const
  {
    return prefixDigits;
  }

  double DerivedUnit::removePrefixDigits()
  {
    double out=std::pow(10.0,prefixDigits);
    prefixDigits=0;
    return out;
  }



  ABC_Unit* DerivedUnit::pow(int exponent)const
  {
    DerivedUnit* out=new DerivedUnit(*this);
    out->prefixDigits*=exponent;
    std::map<ElementaryUnit*,int,UnitCompare>::iterator it;
    for (it=out->myTerms.begin(); it!=out->myTerms.end(); ++it)
      it->second*=exponent;
    return out;
  }

  ABC_Unit* DerivedUnit::times(const ABC_Unit* other)const
  {
    DerivedUnit* out=new DerivedUnit(*this);
    std::map<ElementaryUnit*,int,UnitCompare>::const_iterator it;
    for (it=other->terms().begin(); it!=other->terms().end(); ++it)
      {
        std::pair<std::map<ElementaryUnit*,int,UnitCompare>::iterator,
            bool> res=out->myTerms.insert(*it);
        if(!res.second)
          {
            ElementaryUnit* u=res.first->first;
            if (u->decimalPlaces()!=it->first->decimalPlaces())
              {
                int dp=u->decimalPlaces()*res.first->second+
                    it->first->decimalPlaces()*it->second;
                int exp=res.first->second+it->second;
                int ndp=dp/exp;
                int fac=dp-ndp*exp;
                ElementaryUnit* ne=u->pow10(ndp);
                fac+=ne->numericPrefixDigits();
                ne->removePrefixDigits();
                out->prefixDigits+=fac;
                //remove the constant elementary unit to change its value
                out->myTerms.erase(res.first);
                delete u;
                // new value inserted
                out->myTerms.insert(std::pair<ElementaryUnit*,int>(ne,exp));


              }
            else
              {
                res.first->second+=it->second;
                if (res.first->second==0)
                  {
                    out->myTerms.erase(res.first);
                    delete u;
                  }
              }
          }

      }
    return out;

  }

  const std::map<ElementaryUnit*,int,UnitCompare> &
  DerivedUnit::terms()const
  {
    return myTerms;
  }






  std::string ElementaryUnit::fullName()const
  {
    std::string out;
    if (numericPrefixDigits()==1)
      {
        out+="10";
        out+=multiplicationSymbol();
      }
    else if (numericPrefixDigits()!=0)
      {
        out+="10^";
        out+=ToString(numericPrefixDigits());
        out+=multiplicationSymbol();
      }
    out+=nToAbbr(symbolicPrefixDigits);
    out+=myName;

    return out;
  }
  std::string ElementaryUnit::abbr()const
  {
    std::string out;
    if (numericPrefixDigits()==1)
      {
        out+="10";
        out+=multiplicationSymbol();
      }
    else if (numericPrefixDigits()!=0)
      {
        out+="10^";
        out+=ToString(numericPrefixDigits());
        out+=multiplicationSymbol();
      }
    out+=nToAbbr(symbolicPrefixDigits);
    out+=myabbr;

    return out;

  }

  std::string ElementaryUnit::name()const
  {
    return myName;
  }

  int ElementaryUnit::numericPrefixDigits()const
  {
    return prefixDigits;
  }

  double ElementaryUnit::removePrefixDigits()
  {
    double out=std::pow(10.0,prefixDigits);
    prefixDigits=0;
    return out;
  }


  ABC_Unit* ElementaryUnit::pow(int exponent)const
  {
    DerivedUnit* out=new DerivedUnit(*this);

    out->myTerms.begin()->second=exponent;
    out->prefixDigits*=exponent;
    return out;
  }

  ABC_Unit* ElementaryUnit::times(const ABC_Unit* other)const
  {
    DerivedUnit* out=new DerivedUnit(*other);
    std::pair<std::map<ElementaryUnit*,int,UnitCompare>::iterator,
        bool> res=out->myTerms.insert(*(myTerms.begin()));
    if(!res.second)
      {
        ElementaryUnit* u=res.first->first;
        if (u->decimalPlaces()!=decimalPlaces())
          {
            int dp=u->decimalPlaces()*res.first->second+
                decimalPlaces();
            int exp=res.first->second+1;
            int ndp=dp/exp;
            int fac=dp-ndp*exp;
            ElementaryUnit* ne=u->pow10(ndp);
            fac+=ne->numericPrefixDigits();
            ne->removePrefixDigits();
            out->prefixDigits+=fac;
            //remove the constant elementary unit to change its value
            out->myTerms.erase(res.first);
            delete u;
            // new value inserted
            out->myTerms.insert(std::pair<ElementaryUnit*,int>(ne,exp));


          }
        else
          {
            res.first->second+=1;
            if (res.first->second==0)
              {
                out->myTerms.erase(res.first);
                delete u;
              }
          }
      }

    return out;
  }

  int ElementaryUnit::decimalPlaces()const
  {
    return symbolicPrefixDigits;
  }

  ElementaryUnit* ElementaryUnit::pow10(int exponent)const
  {

  }

  ElementaryUnit::ElementaryUnit(){}

  ElementaryUnit* ElementaryUnit::create(Markov_Console::Markov_CommandManager* cm,
                                         const std::string& name,
                                         const std::string& abbr,
                                         int digits)
  {
    ElementaryUnit* out=new ElementaryUnit;
    out->myName=name;
    out->myabbr=abbr;

    int symbDigits=digits;
    if (symbDigits==0)
      {
        out->symbolicPrefixDigits=0;
        out->prefixDigits=0;
      }
    else
      {
        if (symbDigits>-16)
          {
            while (nToAbbr(symbDigits)==char('!'))
              symbDigits--;
          }
        else
          {
            symbDigits=-15;

          }
        out->symbolicPrefixDigits=symbDigits;
        out->prefixDigits=digits-symbDigits;
      }

    out->myTerms[out]=1;
    cm->add_unit(out);
    return out;
  }



  const std::map<ElementaryUnit*,int,UnitCompare>& ElementaryUnit::terms()const
  {
    return myTerms;
  }
  bool ElementaryUnit::operator < (const ElementaryUnit& other)const
  {

    return fullName()<other.fullName();
  }

  char multiplicationSymbol()
  {
    return char(250);

  }

}


