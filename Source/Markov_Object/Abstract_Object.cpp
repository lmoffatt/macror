
#include "Tests/AssertPlain.h"
#include <cctype>

#include "Markov_Object/Abstract_Object.h"





namespace Markov_Object{


  std::string Abstract_Object::ClassName()
  {
    return "Abstract_Object";
  }


  std::set<std::string> Abstract_Object::mySuperClasses()const
  {
    std::set<std::string> mySC;
    mySC.insert(ClassName());
    return mySC;
  }

  std::set<std::string> A_Named_Object::mySuperClasses()const
  {
    auto mySC=Abstract_Object::mySuperClasses();
    mySC.insert(ClassName());
    return mySC;
  }

  std::string A_Named_Object::ClassName()
  {
    return "Named_Object";
  }

  A_Named_Object::~A_Named_Object()
  {}


  Abstract_Object::~Abstract_Object()
  {}

  Abstract_Object::Abstract_Object(){}

  std::string Complex_Object::beginLabel()
  {
    return "Begin";
  }

  std::string Complex_Object::endLabel()
  {
    return "End";
  }


  std::string A_Named_Object::myClass()const
  {
    return ClassName();
  }


  std::string A_Named_Object::getName(const std::string& multiplelines,std::size_t& pos)

  {
    std::size_t pos0=pos;
    // skip spaces
    pos=multiplelines.find_first_not_of(" \t",pos);
    std::size_t i=multiplelines.find_first_of("_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",pos);
    if (i==pos)
      {
        pos=multiplelines.find_first_not_of("_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",
                                            i);
        std::string name=multiplelines.substr(i,pos-i);
        return name;
      }
    else
      {
        pos=pos0;
        return "";
      }
  }

  std::string A_Named_Object::getTip(const std::string& multiplelines, std::size_t &pos)
  {
    std::size_t pos0=pos;
    std::size_t i=multiplelines.find("//",pos);
    std::size_t endline=multiplelines.find_first_of("\r\n",pos);
    pos=multiplelines.find_first_of("\n",pos);
    if (i<endline)
      {
        if (pos!=std::string::npos) pos++;
        std::string tip=multiplelines.substr(i+2,endline-i-2);
        return tip;
      }
    else
      {
        pos=pos0;

        return "";
      }
  }

  std::string A_Named_Object::removeInitialSpaces(const std::string& line)
  {
    return line.substr(line.find_first_not_of(" \t"));
  }


  std::string A_Named_Object::nextLine(const std::string &lines, std::size_t &n)
  {
    std::size_t n0=n;
    std::size_t nlast=lines.find_first_of("\r\n",n0);
    n=lines.find_first_of("\n",n0);
    if (n!=std::string::npos) n++;
    return lines.substr(n0,nlast-n0);
  }

  std::string A_Named_Object::getWhatThis(const std::string& multiplelines, std::size_t &pos)
  {
    std::size_t pos0=pos;
    std::string whatthis;
    while(pos!=std::string::npos)
      {
        std::string line=nextLine(multiplelines,pos);
        line=removeInitialSpaces(line);
        if (line.find("//")!=0)
          break;
        whatthis+=line.substr(2);
        pos0=pos;
      }
    pos=pos0;
    return whatthis;
  }




  Valued_Object::~Valued_Object(){}


  std::string Valued_Object::ClassName()
  {
    return "Valued_Object";
  }

  std::string Valued_Object::myClass()const
  {
    return ClassName();
  }
  std::set<std::string> Valued_Object::mySuperClasses()const
  {
    auto sc=Abstract_Object::mySuperClasses();
    sc.insert(ClassName());
    return sc;

  }

  std::string Variable_Object::ClassName()
  {
    return "Variable_Object";
  }

  std::string Variable_Object::myClass()const {
    return ClassName();
  }

  std::set<std::string> Variable_Object::mySuperClasses()const {
    auto mySC=Abstract_Object::mySuperClasses();
    mySC.insert(ClassName());
    return mySC;
  }


  Variable_Object::~Variable_Object(){}


  bool Variable_Object::isClonable()const
  {
    return false;
  }
  Variable_Object *Variable_Object::clone()const
  {
    return nullptr;
  }







  std::string Value_Object::ClassName()
  {
    return "Value_Object";
  }

  std::string Value_Object::myClass()const {
    return ClassName();
  }

  std::set<std::string> Value_Object::mySuperClasses()const {
    auto mySC=Abstract_Object::mySuperClasses();
    mySC.insert(ClassName());
    return mySC;
  }



  Value_Object::~Value_Object(){}



  bool Value_Object::isClonable()const
  {
    return true;
  }
   bool Value_Object::isCreateable()const
   {
     return true;
   }
   Value_Object* Value_Object::create()const
   {
     return variable()->defaultSample();
   }












  std::string Complex_Object::beginLine()const
  {
    return myClass()+" "+beginLabel();
  }
  std::string Complex_Object::endLine()const
  {
    return myClass()+" "+endLabel();
  }




  std::string A_Named_Object::idName()const
  {
    return variableName_;
  }

  /// hint about of the class nature
  std::string A_Named_Object::Tip()const
  {
    return tip_;
  }

  /// a short description of the class
  std::string A_Named_Object::WhatThis()const
  {
    return whatThis_;
  }

  void A_Named_Object::setTip(const std::string &newTip){
    tip_=newTip;
  }

  void A_Named_Object::setWhatThis(const std::string& whatthis)
  {
    whatThis_=whatthis;

  }

  Environment* A_Named_Object::getEnvironment() const
  {
    return e_;
  }

//  const Environment* Named_Object::getEnvironment()const
//  {
//    return e_;
//  }


  std::size_t A_Named_Object::numFields()const
  {
    return 0;
  }



  std::string A_Named_Object::ToString()const
  {
    std::string out;
    if (!idName().empty())
      {
        out+=idName();
        if (!Tip().empty())
          {
            out+="//";
            out+=Tip();
          }
        if(!WhatThis().empty())
          {
            out+="\n";
            std::string whathis=WhatThis();
            std::size_t wpos=0;
            std::string wline=nextLine(whathis,wpos);
            out+="//"+wline;

            while (wpos!=std::string::npos)
              {
                wline=nextLine(whathis,wpos);
                out+="//"+wline;
              }

          }
        out+="\n";
      }
    return out;
  }
  bool A_Named_Object::ToObject(const std::string& text,std::size_t& cursor)
  {
    std::size_t c0=cursor;
    std::string name=getName(text,cursor);
    std::string tip=getTip(text,cursor);
    std::string whatthis=getWhatThis(text,cursor);

    if (!name.empty())
      this->variableName_=name;
    if (!tip.empty())
      setTip(tip);
    if(!whatthis.empty())
      setWhatThis(whatthis);

    if (name.empty()&&tip.empty()&&whatthis.empty())
      {
        cursor=c0;
        return false;
      }
    return true;
  }



  A_Named_Object::A_Named_Object(Environment* e,
                             std::string variablename,
                             std::string tip,
                             std::string whatthis)
    :
      Abstract_Object(),
      e_(e),variableName_(variablename),tip_(tip),whatThis_(whatthis){}






  std::string Base_Unit::getUnit(const std::string& singleLine)
  {
    std::size_t i=singleLine.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    std::size_t j=singleLine.find_first_not_of(
          "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ*/^-+0123456789",i);

    std::string abbr=singleLine.substr(i,j-i);

    return abbr;

  }

  std::string Base_Unit::ClassName(){
    return "Base_Unit";

  }
  std::string Base_Unit::myClass()const{
    return ClassName();
  }

  std::string Base_Unit::abbr()const{
    return abbr_;
  }


  bool Base_Unit::isClonable()const
  {
    return false;
  }
  bool Base_Unit::isCreateable()const
  {
    return false;
  }
  Abstract_Object* Base_Unit::clone()const
  {
    return nullptr;
  }
  Abstract_Object* Base_Unit::create()const
  {
    return nullptr;
  }



  std::string Base_Unit::ToString()const
  {
    std::string out=A_Named_Object::ToString();
    out+=abbr()+"\n";

    return out;
  }

  bool Base_Unit::ToObject(const std::string& multipleLines,std::size_t& pos)
  {
    std::size_t pos0=pos;
    std::string line=nextLine(multipleLines,pos);
    if (!A_Named_Object::ToObject(multipleLines,pos))
      {
        pos=pos0;

        return false;
      }
    line=nextLine(multipleLines,pos);
    std::string abbreviation=getUnit(line);
    abbr_=abbreviation;

    return true;

  }

  bool Base_Unit::IsObject(const std::string& singleLine) const
  {
    return !getUnit(singleLine).empty();
  }



  Base_Unit::Base_Unit(std::string abbreviation,
                       std::string name,
                       Environment* e,
                       std::string tip,
                       std::string whatthis)
    :
      A_Named_Object(e,name,tip,whatthis),
      abbr_(abbreviation){
    e->addUnit(this);
  }



  template<typename T>
  std::string SimpleVariable<T>::myClass()const{
    return ClassName();
  }



  template<>
  std::string SimpleVariable<double>::ClassName(){
    return "double";

  }

  template<>
  std::string SimpleVariable<std::size_t>::ClassName(){
    return "count";

  }

  template<typename T>
  std::set<std::string> SimpleVariable<T>::mySuperClasses()const
  {
    //Variable_Object,public Valued_Object,public Named_Object
    auto vo=Variable_Object::mySuperClasses();

    auto va=Valued_Object::mySuperClasses();
    auto na=A_Named_Object::mySuperClasses();
    vo.insert(va.begin(),va.end());
    vo.insert(na.begin(),na.end());


    vo.insert(ClassName());
    return vo;

  }



  template<typename T>
  const Base_Unit* SimpleVariable<T>::myUnit()const{
    return u_;
  }


  template<typename T>
  SimpleVariable<T>::SimpleVariable(std::string name,
                                    T defaultValue,
                                    std::string unit,
                                    Environment* e,
                                    std::string tip,
                                    std::string whatthis)
    :
      A_Named_Object(e,name,tip,whatthis),
      defautValue_(defaultValue),
      u_{e->U(unit)}
  {
    e->addVariable(this);
  }



  template<typename T>
  SimpleVariableValue<T>* SimpleVariable<T>::defaultSample() const
  {
    return new SimpleVariableValue<T>(idName(),
                                      defautValue_,
                                      myUnit()->abbr(),
                                      getEnvironment(),
                                      idName()+"_dval",
                                      idName()+" default value",
                                      "default valued generated by "+idName());
  }


  template<typename T>
  bool SimpleVariable<T>::isCreateable()const
  {
    return true;
  }

  template<typename T>
  SimpleVariable<T>* SimpleVariable<T>::create()const
  {
    return new SimpleVariable<T>("",T(),"",getEnvironment(),"","");
  }


  template<typename T>
  SimpleVariable<T>::~SimpleVariable(){}

  template<typename T>
  const SimpleVariable<T>* SimpleVariableValue<T>::variable()const
  {
    return variable_;
  }






  template<typename T>
  std::set<std::string>
  SimpleVariableValue<T>::mySuperClasses()const {
    auto mySC=Abstract_Object::mySuperClasses();
    mySC.insert(ClassName());
    return mySC;
  }





  template<typename T>
  std::string SimpleVariableValue<T>::myClass()const
  {
    return ClassName();
  }

  template<>
  std::string SimpleVariableValue<std::size_t>::ClassName()
  {
    return "count_value";
  }

  template<>
  std::string SimpleVariableValue<double>::ClassName()
  {
    return "real_value";
  }



  template<typename T>
  const Base_Unit* SimpleVariableValue<T>::myUnit()const
  {
    return variable_->myUnit();
  }



  template<typename T>
  SimpleVariableValue<T>::SimpleVariableValue(std::string variablename,
                                              T v,
                                              std::string unit, Environment *e,
                                              std::string name,
                                              std::string tip,
                                              std::string whatthis)
    : A_Named_Object(e,name,tip,whatthis),
      variable_(dynamic_cast<const SimpleVariable<T>*>(e->V(variablename,SimpleVariable<T>::ClassName()))),
      value_(v),
      unit_(e->U(unit))
  {}

  template<typename T>
  SimpleVariableValue<T>::~SimpleVariableValue(){}

  template<>
  bool SimpleVariableValue<std::size_t>::is(const std::string &singleLine)
  {
    std::size_t firstNotNumber=singleLine.find_first_not_of(" 0123456789\t");
    std::size_t firstNumber=singleLine.find_first_of("0123456789");
    if (firstNotNumber<firstNumber)
      return false;
    std::size_t lastnumber=singleLine.find_last_of("0123456789");
    std::size_t firstNumberInterr=singleLine.find_first_not_of("0123456789",firstNumber);
    if (firstNumberInterr==std::string::npos)
      return true;
    if (lastnumber!=firstNumberInterr-1)
      return false;
    return true;
  }

  template<>
  bool SimpleVariableValue<double>::is(const std::string &singleLine)
  {
    try
    {
      std::stod(singleLine);
    }
    catch (...)
    {
      return false;
    }
    return true;
  }

  template<>
  std::size_t SimpleVariableValue<std::size_t>::get(const std::string& singleLine)
  {
    std::size_t out;
    try
    {
      out=std::stoul(singleLine);
    }
    catch (...)
    {
      return 0;
    }
    return out;
  }

  template<>
  double SimpleVariableValue<double>::get(const std::string& singleLine)
  {
    double out;
    try
    {
      out=std::stod(singleLine);
    }
    catch (...)
    {
      return 0;
    }
    return out;
  }





  template<typename T>
  T SimpleVariableValue<T>::value()const{
    return value_;
  }

  template<typename T>
  std::string SimpleVariableValue<T>::ToString()const
  {
    std::string out=A_Named_Object::ToString();
    out+=std::to_string(value());
    out+=myUnit()->abbr()+"\n";
    return out;
  }


  template<typename T>
  bool SimpleVariableValue<T>::ToObject(const std::string& multipleLines, std::size_t &pos)
  {
    std::size_t pos0=pos;
    if (!A_Named_Object::ToObject(multipleLines,pos))
      return false;
    std::string line=nextLine(multipleLines,pos);
    if (!SimpleVariableValue<T>::is(line))
      {
        pos=pos0;
        return false;
      }
    value_=SimpleVariableValue<T>::get(line);
    std::string ab=Base_Unit::getUnit(line);
    unit_=getEnvironment()->U(ab);
    return true;
  }

  template<typename T>
  bool SimpleVariableValue<T>::IsObject(const std::string &singleLine) const
  {
    return SimpleVariableValue<T>::is(singleLine);
  }

  template<typename T>
  SimpleVariableValue<T>* SimpleVariableValue<T>::clone()const
  {
//    return new SimpleVariableValue(variable()->idName(),
//                                   value(),

//                                   Environment *e,
//                                   std::string name,
//                                   std::string tip,
//                                   std::string whatthis);

  }


  template<typename T>
  std::string SimpleVariable<T>::ToString()const{
    std::string out=A_Named_Object::ToString();
    out+=std::to_string(defautValue_);
    out+=u_->abbr()+"\n";
    return out;
  }

  template<typename T>
  bool SimpleVariable<T>::ToObject(const std::string& multipleLines, std::size_t &pos)
  {
    std::size_t pos0=pos;
    if (!A_Named_Object::ToObject(multipleLines,pos))
      return false;
    std::string line=nextLine(multipleLines,pos);
    if (!SimpleVariableValue<T>::is(line))
      {
        pos=pos0;
        return false;
      }
    defautValue_=SimpleVariableValue<T>::get(line);
    std::string ab=Base_Unit::getUnit(line);
    u_=getEnvironment()->U(ab);
    return true;
  }


  template<typename T>
  bool SimpleVariable<T>::IsObject(const std::string &singleLine)const
  {
    return SimpleVariableValue<T>::is(singleLine);
  }


  std::string Complex_Object::getClassName(const std::string& singleLine)
  {
    std::size_t pos=0;
    std::string classname=A_Named_Object::getName(singleLine,pos);
    std::string bgl=A_Named_Object::getName(singleLine,pos);
    if (bgl==beginLabel())
      return classname;
    else
      return "";

  }



  std::string Complex_Object::getFieldName(const std::string &singleLine)
  {
    std::size_t pos=0;
    std::string fieldname=A_Named_Object::getName(singleLine,pos);
    return fieldname;
  }

  static Variable_Object* getFieldValue(const std::string multipleLines,std::size_t& pos)
  {
    std::string line=A_Named_Object::nextLine(multipleLines,pos);

  }







  std::string Complex_Object::ClassName(){
    return "Complex_object";
  }

  std::string Complex_Object::myClass()const{
    return ClassName();
  }


  std::set<std::string> Complex_Object::mySuperClasses()const {
    auto mySC=A_Named_Object::mySuperClasses();
    mySC.insert(ClassName());
    return mySC;
  }


  std::size_t Complex_Object::numFields()const{
    return fieldNames_.size();
  }

  std::string Complex_Object::fieldName(std::size_t i)const{
    return fieldNames_[i];
  }


  bool Complex_Object::hasField(const std::string& fieldN)const
  {
    return fieldVariables_.find(fieldN)!=fieldVariables_.end();
  }


  bool Complex_Object::setField(const std::string& fieldN,Abstract_Object*  o)
  {
    if (hasField(fieldN))
      {
        fieldVariables_[fieldN]=o;
        return true;
      }
    else
      return false;
  }


  bool Complex_Object::push_back(const std::string & fieldname,
                                 Abstract_Object* object)
  {
    if (!setField(fieldname,object))
      {
        fieldNames_.push_back(fieldname);
        fieldVariables_[fieldname]=object;
      }
    return true;

  }



  const Abstract_Object* Complex_Object::fieldVariable(const std::string& fieldname)const
  {
    auto it=fieldVariables_.find(fieldname);
    if (it!=fieldVariables_.end())
      return it->second;
    else
      return nullptr;
  }
  Abstract_Object *Complex_Object::fieldVariable(const std::string& fieldname)
  {
    auto it=fieldVariables_.find(fieldname);
    if (it!=fieldVariables_.end())
      return it->second;
    else
      return nullptr;
  }



  std::string Complex_Object::ToString()const{
    std::string out=beginLine()+"\n";
    out+=A_Named_Object::ToString();
    for (std::size_t i=0; i<numFields(); ++i)
      {
        out+=fieldName(i)+"\n";
        out+=fieldVariable(fieldName(i))->ToString();
      }
    out+=endLine()+"\n";
    return out;
  }

  bool Complex_Object::ToObject(const std::string& multipleLines, std::size_t &pos)
  {
    std::size_t pos0=pos;
    std::string line=nextLine(multipleLines,pos);
    if (line!=beginLine())
      {
        pos=pos0;
        return false;
      }

    if (!A_Named_Object::ToObject(multipleLines,pos))
      return false;


    line=nextLine(multipleLines,pos);
    while ((line!=endLine())&&pos<multipleLines.size())
      {
        std::string fieldname=getFieldName(line);
        if (!hasField(fieldname))
          {
            pos=pos0;
            return false;
          }
        Abstract_Object *v=this->fieldVariable(fieldname);
        v->ToObject(multipleLines,pos);
        line=nextLine(multipleLines,pos);
      }
    return true;

  }

  bool Complex_Object::IsObject(const std::string& singleLine)const
  {
    return singleLine==beginLine();
  }

  Complex_Object:: ~Complex_Object(){}

  Complex_Object::Complex_Object(Environment* e,
                                 std::string name,
                                 std::string tip,
                                 std::string whatthis)
    :
      A_Named_Object(e,name,tip,whatthis)
  {}





  std::string Complex_Variable::ClassName(){
    return "Complex_Variable";
  }

  std::string Complex_Variable::myClass()const{
    return ClassName();
  }


  std::set<std::string> Complex_Variable::mySuperClasses()const {
    //public Variable_Object, public Complex_Object
    auto mySC=Variable_Object::mySuperClasses();
    auto co=Complex_Object::mySuperClasses();
    mySC.insert(co.begin(),co.end());
    mySC.insert(ClassName());
    return mySC;
  }



  Variable_Object const * Complex_Variable::fieldVariable(const std::string& fieldname)const
  {
    return dynamic_cast<Variable_Object const *>(Complex_Object::fieldVariable(fieldname));
  }

  Variable_Object  * Complex_Variable::fieldVariable(const std::string& fieldname)
  {
    return dynamic_cast<Variable_Object*>(Complex_Object::fieldVariable(fieldname));

  }


  bool Complex_Variable::setField(const std::string& fieldN,Variable_Object*  o)
  {
    return Complex_Object::setField(fieldN,o);
  }


  bool Complex_Variable::push_back(const std::string &fieldname,
                                   Variable_Object* object)
  {
    return Complex_Object::push_back(fieldname,object);
  }

  Complex_Variable::Complex_Variable(Environment* e,
                                     std::string name,
                                     std::string tip,
                                     std::string whatthis)
    :Complex_Object(e,name,tip,whatthis)
  {
    e->addVariable(this);
  }


  Complex_Variable::~Complex_Variable(){}

  std::string Complex_Variable_Value::ClassName(){
    return "Complex_Variable_Value";
  }

  std::string Complex_Variable_Value::myClass()const{
    return ClassName();
  }


  std::set<std::string> Complex_Variable_Value::mySuperClasses()const {
    //public Complex_Object,public Value_Object

    auto mySC=Complex_Object::mySuperClasses();
    auto vo=Value_Object::mySuperClasses();
    mySC.insert(vo.begin(),vo.end());
    mySC.insert(ClassName());
    return mySC;
  }


  Value_Object const * Complex_Variable_Value::fieldVariable(const std::string& fieldname)const
  {
    return dynamic_cast<Value_Object const *>(Complex_Object::fieldVariable(fieldname));
  }

  Value_Object  * Complex_Variable_Value::fieldVariable(const std::string& fieldname)
  {
    return dynamic_cast<Value_Object*>(Complex_Object::fieldVariable(fieldname));

  }


  bool Complex_Variable_Value::setField(const std::string& fieldN,Value_Object*  o)
  {
    return Complex_Object::setField(fieldN,o);
  }


  bool Complex_Variable_Value::push_back(const std::string &fieldname,
                                         Value_Object* object)
  {
    return Complex_Object::push_back(fieldname,object);
  }



  Complex_Variable_Value::Complex_Variable_Value(Environment* e,
                                                 std::string name,
                                                 std::string tip,
                                                 std::string whatthis,
                                                 std::string complexvar):
    Complex_Object(e,name,tip,whatthis),
    cmplxvar_(dynamic_cast<Complex_Variable const*>(e->V(complexvar,Complex_Variable::ClassName())))
  {}

  Complex_Variable_Value::~Complex_Variable_Value(){}




  Complex_Variable_Value* Complex_Variable::defaultSample() const {

    Complex_Variable_Value* out= new Complex_Variable_Value(
          getEnvironment(),
          idName()+"_default_sample",
          "default sample",
          idName()+"complex variable default sample",
          idName());
    for (std::size_t i=0; i<this->numFields(); i++)
      {
        out->push_back(fieldName(i),fieldVariable(fieldName(i))->defaultSample());
      }
    return out;

  }



  const Variable_Object* Complex_Variable_Value::variable()const
  {
    return cmplxvar_;

  }




  template
  class SimpleVariable<std::size_t>;

  template
  class SimpleVariable<double>;


  template
  class SimpleVariableValue<std::size_t>;

  template
  class SimpleVariableValue<double>;


}

