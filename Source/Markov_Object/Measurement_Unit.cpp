#include "Markov_Object/Measurement_Unit.h"

namespace Markov_Object {

  std::string Measurement_Unit::getUnit(const std::string& singleLine)
  {
    std::size_t i=singleLine.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    if (i==singleLine.npos)
      return "";
    std::size_t j=singleLine.find_first_not_of(
          "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ*/^-+0123456789",i);


    std::string abbr=singleLine.substr(i,j-i);

    return abbr;

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


  Measurement_Unit *Measurement_Unit::dynamicCast(Abstract_Object *o) const
  {
    return dynamic_cast<Measurement_Unit*>(o);

  }

  const Measurement_Unit *Measurement_Unit::dynamicCast(const Abstract_Object *o) const
  {
    return dynamic_cast<const Measurement_Unit*>(o);

  }


  std::string Measurement_Unit::longName()const{
    return longName_;
  }


  bool Measurement_Unit::isCreateable()const
  {
    return false;
  }
  Measurement_Unit* Measurement_Unit::create()const
  {
    return new Measurement_Unit;
  }



  std::string Measurement_Unit::ToString()const
  {
    std::string out=Abstract_Named_Object::ToString();
    out+=longName()+"\n";

    return out;
  }

  bool Measurement_Unit::ToObject(Environment* e,const std::string& multipleLines,std::size_t& pos)
  {
    std::size_t pos0=pos;
    if (!Abstract_Named_Object::ToObject( e,multipleLines,pos))
      {
        pos=pos0;

        return nullptr;
      }
    std::string line=nextLine(multipleLines,pos);
    std::string longName=getUnit(line);
    longName_=longName;


    return this;

  }




  Measurement_Unit::Measurement_Unit(std::string abbreviation,
                       std::string name,
                       Environment* e,
                       std::string tip,
                       std::string whatthis)
    :
      Abstract_Named_Object(e,abbreviation,tip,whatthis),
      longName_(name){}

  Measurement_Unit::Measurement_Unit()
    :
      longName_(){}


  Measurement_Unit::Measurement_Unit(Environment* e)
    :
      Abstract_Named_Object(e),
      longName_(){}


}
