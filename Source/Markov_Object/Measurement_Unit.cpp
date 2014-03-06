#include "Markov_Object/Measurement_Unit.h"
#include "Markov_Object/Environment.h"
#include "Markov_Object/IdentifierName.h"
#include "Markov_Object/Quantity.h"
namespace Markov_Object {

  int Measurement_Unit::abbrToN(char c)
  {
    switch (c)
      {
      case 'P':
        return 15;
        break;
      case 'T':
        return 12;
        break;
      case 'G':
        return 9;
        break;
      case 'M':
        return 6;
        break;
      case 'k':
        return 3;
        break;
      case 'd':
        return -1;
        break;
      case 'c':
        return -2;
        break;
      case 'm':
        return -3;
        break;
      case 'u':
        return -6;
        break;
      case 'n':
        return -9;
        break;
      case 'p':
        return -12;
        break;
      case 'f':
        return -15;
        break;
      case 'a':
        return -18;
        break;

      default:
        return 0;
      }
  }

  std::string Measurement_Unit::nToFullName(int n)
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

  char Measurement_Unit::nToAbbr(int n)
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



  std::string Measurement_Unit::ClassName(){
    return "Base_Unit";

  }
  std::string Measurement_Unit::myClass()const{
    return ClassName();
  }

  std::set<std::string> Measurement_Unit:: SuperClasses()
  {
    auto mySC=Abstract_Named_Object::SuperClasses();
    mySC.insert(ClassName());
    return mySC;
  }

  Class_info Measurement_Unit::classInfo()
  {
    return Class_info
    {
        {ClassName()},
        {SuperClasses()},
        false,
        true,
        false
      };

  }


  Class_info Measurement_Unit::myClassInfo() const
  {
    return classInfo();
  }


  Measurement_Unit *Measurement_Unit::dynamicCast(Abstract_Object*o) const
  {
    return dynamic_cast<Measurement_Unit*>(o);

  }

  const Measurement_Unit *Measurement_Unit::dynamicCast(const Abstract_Object*o) const
  {
    return dynamic_cast<const Measurement_Unit*>(o);

  }





  Measurement_Unit* Measurement_Unit::create()const
  {
    return new Measurement_Unit;
  }
  
  std::set<std::string> Measurement_Unit::referencedObjects() const
  {
    return std::set<std::string>();
  }

  Measurement_Unit::Measurement_Unit():
    Abstract_Named_Object(),
    idQuantity_(),
    def_(){}
  

  

  std::string Measurement_Unit::ToString()const
  {
    std::string out=Abstract_Named_Object::ToString();
    out+=myQuantity()+"\n";
    out+=definition().ToString()+"\n";

    return out;
  }

  Measurement_Unit* Measurement_Unit::ToObject(const std::string& multipleLines, std::size_t& pos)
  {
    std::size_t pos0=pos;
    if (!Abstract_Named_Object::ToObject(multipleLines,pos))
      {
        pos=pos0;

        return nullptr;
      }
    idQuantity_=IdentifierName::get(multipleLines,pos,Quantity::allowed);
    if (idQuantity_.empty())
      {
        pos=pos0;
        return nullptr;
      }
    auto d=def_.CreateObject(multipleLines,pos);
    if (d==nullptr)
      {
        pos=pos0;
        return nullptr;
      }
    def_=*d;

   return this;

  }

  ScaledExpression Measurement_Unit::baseDefinition(std::set<std::string> upstream) const
{    upstream.insert(idName());
    ScaledExpression out;
     int n0=0,n;

    if (getEnvironment()!=nullptr)
      {
        for (auto t:def_.value())
          {
            std::shared_ptr<const Measurement_Unit> q=getEnvironment()->U(t.first);
            if (q==nullptr)
              {
                n=0;
                if (!t.first.empty())
                n=abbrToN(t.first[0]);
                if (n!=0)
                q=getEnvironment()->U(t.first.substr(1));
              }
              if (q==nullptr)
              return ScaledExpression();
            else if (upstream.count(q->idName())!=0)
              return self();
            else
              {
                ScaledExpression defq=q->baseDefinition(upstream)*t.second;
                out+=defq;
                n0+=n*t.second;
              }

          }
      }
    double scale=def_.scale()*std::pow(10.0,n);
    out.setScale(scale);
    return out;
  }





  Measurement_Unit::Measurement_Unit(Environment*  E,
                                     std::string idName,
                                     double scaleFactor,
                                     std::string definition,
                                     std::string idQuantity,
                                     std::string fullname,
                                     std::string whatthis)
    :
      Abstract_Named_Object(E,idName,fullname,whatthis),
      idQuantity_(idQuantity),
      def_(scaleFactor,QuantityExpression(QuantityExpression::getDefinition(definition)))
  {}



}
