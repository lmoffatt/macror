#include <cctype>
#include <cmath>

#include "Tests/AssertPlain.h"



#include "Markov_Object/Abstract_Object.h"





namespace Markov_Object{
  
  
  
  Class_info Abstract_Object::classInfo()
  {
    return Class_info
    {
        {ClassName()},
        {ClassName()},
        false,
        false,
        false
      };
    
  }
  
  Class_info Abstract_Object::myClassInfo() const
  {
    return classInfo();
  }
  
  std::string Abstract_Object::myClass() const
  {
    return ClassName();
  }
  
  
  
  std::set<std::string> Abstract_Object:: SuperClasses()
  {
    std::set<std::string> mySC;
    mySC.insert(ClassName());
    return mySC;
  }
  
  
  Abstract_Object *Abstract_Object::dynamicCast(Abstract_Object *o) const
  {
    return dynamic_cast<Abstract_Object*>(o);
  }
  
  const Abstract_Object *Abstract_Object::dynamicCast(const Abstract_Object *o) const
  {
    return dynamic_cast<const Abstract_Object*>(o);
  }
  
  std::string Abstract_Object::contextToString() const
  {
    std::string s;
    for (auto r : referencedObjects())
      {
        auto v=getEnvironment()->V(r);
        if (v!=nullptr)
          s+=v->ToString();
        else
          {
            auto u=getEnvironment()->U(r);
            if (u!=nullptr)
              s+=u->ToString();
          }
        
      }
    return s;
  }
  
  std::set<std::string> Named_Object:: SuperClasses()
  {
    auto mySC=Abstract_Object::SuperClasses();
    mySC.insert(ClassName());
    return mySC;
  }
  
  Class_info Named_Object::classInfo()
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
  
  Class_info Named_Object::myClassInfo() const
  {
    return classInfo();
  }
  
  
  std::string Named_Object::ClassName()
  {
    return "Named_Object";
  }
  
  Named_Object *Named_Object::dynamicCast(Abstract_Object *o) const
  {
    return dynamic_cast<Named_Object*>(o);
  }
  
  const Named_Object *Named_Object::dynamicCast(const Abstract_Object *o) const
  {
    return dynamic_cast<const Named_Object*>(o);
  }
  Named_Object::~Named_Object()
  {}
  
  
  Abstract_Object::~Abstract_Object()
  {}
  
  
  //  std::string Complex_Object::beginLabel()
  //  {
  //    return "Begin";
  //  }
  
  //  std::string Complex_Object::endLabel()
  //  {
  //    return "End";
  //  }
  
  
  std::string Named_Object::myClass()const
  {
    return ClassName();
  }
  
  
  std::string Named_Object::getName(const std::string& multiplelines,std::size_t& pos)
  
  {
    if (multiplelines.empty())
      return multiplelines;
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
  
  std::string Named_Object::getTip(const std::string& multiplelines, std::size_t &pos)
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
  
  std::string Named_Object::removeInitialSpaces(const std::string& line)
  {
    if (line.empty())
      return "";
    return line.substr(line.find_first_not_of(" \t"));
  }
  
  
  std::string Named_Object::nextLine(const std::string &lines, std::size_t &n)
  {
    std::size_t n0=n;
    std::size_t nlast=lines.find_first_of("\r\n",n0);
    n=lines.find_first_of("\n",n0);
    if (n!=std::string::npos) n++;
    return lines.substr(n0,nlast-n0);
  }
  
  std::string Named_Object::getWhatThis(const std::string& multiplelines, std::size_t &pos)
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
  
  
  
  
  Abstract_Valued_Object::~Abstract_Valued_Object(){}
  
  
  std::string Abstract_Valued_Object::ClassName()
  {
    return "Valued_Object";
  }
  
  std::string Abstract_Valued_Object::myClass()const
  {
    return ClassName();
  }
  std::set<std::string> Abstract_Valued_Object::SuperClasses()
  {
    std::set<std::string> sc=Abstract_Object::SuperClasses();
    sc.insert(ClassName());
    return sc;
    
  }
  Class_info Abstract_Valued_Object::classInfo()
  {
    return Class_info
    {
        {ClassName()},
        {SuperClasses()},
        true,
        false,
        false
      };
    
  }
  
  Class_info Abstract_Valued_Object::myClassInfo() const
  {
    return classInfo();
  }
  
  
  std::string Abstract_Variable_Object::ClassName()
  {
    return "Variable_Object";
  }
  
  std::string Abstract_Variable_Object::myClass()const {
    return ClassName();
  }
  
  Class_info Abstract_Variable_Object::classInfo()
  {
    return Class_info
    {
        {ClassName()},
        {SuperClasses()},
        false,
        false,
        false
      };
    
  }
  
  Class_info Abstract_Variable_Object::myClassInfo() const
  {
    return classInfo();
  }
  
  
  std::set<std::string> Abstract_Variable_Object:: SuperClasses() {
    auto mySC=Named_Object::SuperClasses();
    mySC.insert(ClassName());
    return mySC;
  }
  
  Abstract_Valued_Object *Abstract_Valued_Object::dynamicCast(Abstract_Object *o) const
  {
    return dynamic_cast<Abstract_Valued_Object*>(o);
  }
  
  const Abstract_Valued_Object *Abstract_Valued_Object::dynamicCast(const Abstract_Object *o) const
  {
    return dynamic_cast<const Abstract_Valued_Object*>(o);
  }
  Abstract_Variable_Object::~Abstract_Variable_Object(){}
  
  Abstract_Variable_Object *Abstract_Variable_Object::dynamicCast(Abstract_Object *o) const
  {
    return dynamic_cast<Abstract_Variable_Object *>(o);
  }
  
  const Abstract_Variable_Object *Abstract_Variable_Object::dynamicCast(const Abstract_Object *o) const
  {
    return dynamic_cast<const Abstract_Variable_Object *>(o);
  }
  
  
  

  
  
  
  
  
  
  std::string Abstract_Value_Object::ClassName()
  {
    return "Value_Object";
  }
  
  std::string Abstract_Value_Object::myClass()const {
    return ClassName();
  }
  
  Class_info Abstract_Value_Object::classInfo()
  {
    return Class_info
    {
        {ClassName()},
        {SuperClasses()},
        false,
        false,
        false
      };
    
  }
  
  Class_info Abstract_Value_Object::myClassInfo() const
  {
    return classInfo();
  }
  
  
  std::set<std::string> Abstract_Value_Object:: SuperClasses() {
    auto mySC=Abstract_Object::SuperClasses();
    mySC.insert(ClassName());
    return mySC;
  }
  
  Abstract_Value_Object *Abstract_Value_Object::dynamicCast(Abstract_Object *o) const
  {
    return dynamic_cast<Abstract_Value_Object*> (o);
  }
  
  const Abstract_Value_Object *Abstract_Value_Object::dynamicCast(const Abstract_Object *o) const
  {
    return dynamic_cast<const Abstract_Value_Object*> (o);
  }
  
  
  Abstract_Value_Object::~Abstract_Value_Object(){}
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  //  std::string Complex_Object::beginLine()const
  //  {
  //    return myClass()+" "+beginLabel();
  //  }
  //  std::string Complex_Object::endLine()const
  //  {
  //    return myClass()+" "+endLabel();
  //  }
  
  
  
  
  std::string Named_Object::idName()const
  {
    return variableName_;
  }
  
  bool Named_Object::isReferenced() const
  {
    return (getEnvironment()!=nullptr)&&(getEnvironment()->V(idName())==this);
  }
  
  bool Named_Object::isDuplicate() const
  {
    if (getEnvironment()==nullptr)
      return false;
    else
      {
        auto p=getEnvironment()->V(idName());
        if (p==nullptr)
          return false;
        else
          return p!=this;
      }
  }
  
  /// hint about of the class nature
  std::string Named_Object::Tip()const
  {
    return tip_;
  }
  
  /// a short description of the class
  std::string Named_Object::WhatThis()const
  {
    return whatThis_;
  }
  
  void Named_Object::setTip(const std::string &newTip){
    tip_=newTip;
  }
  
  void Named_Object::setWhatThis(const std::string& whatthis)
  {
    whatThis_=whatthis;
    
  }
  
  
  
  
  
  
  std::string Named_Object::ToString()const
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
  bool Named_Object::ToObject(Environment* e,const std::string& text,std::size_t& cursor)
  {
    std::size_t c0=cursor;
    std::string name=getName(text,cursor);
    std::string tip=getTip(text,cursor);
    std::string whatthis=getWhatThis(text,cursor);
    if (name.empty()&&tip.empty()&&whatthis.empty())
      {
        cursor=c0;
        return false;
      }
    
    this->setEnvironment(e);
    if (!name.empty())
      this->variableName_=name;
    if (!tip.empty())
      this->setTip(tip);
    if(!whatthis.empty())
      this->setWhatThis(whatthis);
    return true;
  }
  
  
  
  Named_Object::Named_Object(Environment* e,
                             std::string variablename,
                             std::string tip,
                             std::string whatthis)
    :
      Abstract_Object(e),
      variableName_{variablename},tip_{tip},whatThis_{whatthis}
    
  {
  }
  
  
  Named_Object::Named_Object(Environment* e)
    :
      Abstract_Object(e),
      variableName_{},tip_{},whatThis_{}{
    
  }
  
  Named_Object::Named_Object()
    :
      Abstract_Object(),
      variableName_{},tip_{},whatThis_{}{}
  
  
  
  
  
  
  
  
  
  
  std::string Base_Unit::getUnit(const std::string& singleLine)
  {
    std::size_t i=singleLine.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    if (i==singleLine.npos)
      return "";
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
  
  std::set<std::string> Base_Unit:: SuperClasses()
  {
    auto mySC=Named_Object::SuperClasses();
    mySC.insert(ClassName());
    return mySC;
  }
  
  Class_info Base_Unit::classInfo()
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
  
  Class_info Base_Unit::myClassInfo() const
  {
    return classInfo();
  }
  
  
  Base_Unit *Base_Unit::dynamicCast(Abstract_Object *o) const
  {
    return dynamic_cast<Base_Unit*>(o);
    
  }
  
  const Base_Unit *Base_Unit::dynamicCast(const Abstract_Object *o) const
  {
    return dynamic_cast<const Base_Unit*>(o);
    
  }
  
  
  std::string Base_Unit::longName()const{
    return longName_;
  }
  
  
  bool Base_Unit::isCreateable()const
  {
    return false;
  }
  Base_Unit* Base_Unit::create()const
  {
    return new Base_Unit;
  }
  
  
  
  std::string Base_Unit::ToString()const
  {
    std::string out=Named_Object::ToString();
    out+=longName()+"\n";
    
    return out;
  }
  
  bool Base_Unit::ToObject(Environment* e,const std::string& multipleLines,std::size_t& pos)
  {
    std::size_t pos0=pos;
    if (!Named_Object::ToObject( e,multipleLines,pos))
      {
        pos=pos0;
        
        return nullptr;
      }
    std::string line=nextLine(multipleLines,pos);
    std::string longName=getUnit(line);
    longName_=longName;
    
    
    return this;
    
  }
  
  
  
  
  Base_Unit::Base_Unit(std::string abbreviation,
                       std::string name,
                       Environment* e,
                       std::string tip,
                       std::string whatthis)
    :
      Named_Object(e,abbreviation,tip,whatthis),
      longName_(name){}
  
  Base_Unit::Base_Unit()
    :
      longName_(){}
  
  
  Base_Unit::Base_Unit(Environment* e)
    :
      Named_Object(e),
      longName_(){}
  
  
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
  Class_info SimpleVariable<T>::classInfo()
  {
    return Class_info
    {
        {ClassName()},
        {SuperClasses()},
        true,
        false,
        false
      };
    
  }
  template<typename T>
  Class_info SimpleVariable<T>::myClassInfo() const
  {
    return classInfo();
  }
  
  template<typename T>
  std::set<std::string> SimpleVariable<T>:: SuperClasses()
  {
    //Variable_Object,public Valued_Object,public Named_Object
    auto vo=Abstract_Variable_Object::SuperClasses();
    
    auto va=Abstract_Valued_Object::SuperClasses();
    vo.insert(va.begin(),va.end());
    
    
    vo.insert(ClassName());
    return vo;
    
  }
  
  template<typename T>
  SimpleVariable<T> *SimpleVariable<T>::dynamicCast(Abstract_Object *o) const
  {
    return dynamic_cast< SimpleVariable<T> *>(o);
  }
  
  template<typename T>
  const SimpleVariable<T> *SimpleVariable<T>::dynamicCast(const Abstract_Object *o) const
  {
    return dynamic_cast< const SimpleVariable<T> *>(o);
  }
  
  
  template<typename T>
  const Base_Unit* SimpleVariable<T>::myUnit()const{
    if (getEnvironment()!=nullptr)
      return getEnvironment()->U(unitId_);
    else
      return nullptr;
  }
  
  
  template<typename T>
  SimpleVariable<T>::SimpleVariable(std::string name,
                                    T defaultValue,
                                    std::string unit,
                                    Environment* e,
                                    std::string tip,
                                    std::string whatthis)
    :
      Abstract_Object(e),
      Abstract_Variable_Object(e,name,tip,whatthis),
      defautValue_(defaultValue),
      unitId_(unit)
   {

  }
  
  template<typename T>
  SimpleVariable<T>::SimpleVariable(Environment* e)
    :
      Abstract_Object(e),
      Abstract_Variable_Object(e),
      defautValue_{T()},
      unitId_{}
  {}
  
  template<typename T>
  SimpleVariable<T>::SimpleVariable()
    :
      Abstract_Object(),
      Abstract_Variable_Object(),
      defautValue_{T()},
      unitId_{}
  {}
  
  
  template<typename T>
  SimpleVariableValue<T>* SimpleVariable<T>::defaultValue() const
  {
    return new SimpleVariableValue<T>(idName(),
                                      defautValue_,
                                      unitId_,
                                      getEnvironment());
  }
  


  
  template<typename T>
  bool SimpleVariable<T>::isCreateable()const
  {
    return true;
  }
  
  template<typename T>
  SimpleVariable<T>* SimpleVariable<T>::create()const
  {
    return new SimpleVariable<T>;
  }
  
  
  template<typename T>
  SimpleVariable<T>::~SimpleVariable(){}
  
  template<typename T>
  const SimpleVariable<T>* SimpleVariableValue<T>::variable()const
  {
    
    if (getEnvironment()!=nullptr)
      return dynamic_cast<const SimpleVariable<T>*>(getEnvironment()->V(variableId_));
    else
      return nullptr;
  }
  
  
  
  
  
  
  
  
  template<typename T>
  std::set<std::string> SimpleVariableValue<T>:: SuperClasses()
  {
    //Variable_Object,public Valued_Object,public Named_Object
    auto vo=Abstract_Value_Object::SuperClasses();
    
    auto va=Abstract_Valued_Object::SuperClasses();
    vo.insert(va.begin(),va.end());
    
    
    vo.insert(ClassName());
    return vo;
    
  }
  
  
  
  template<typename T>
  Class_info SimpleVariableValue<T>::classInfo()
  {
    return Class_info
    {
        {ClassName()},
        {SuperClasses()},
        true,
        false,
        false
      };
    
  }
  template<typename T>
  Class_info SimpleVariableValue<T>::myClassInfo() const
  {
    return classInfo();
  }
  
  
  template<typename T>
  SimpleVariableValue<T> *SimpleVariableValue<T>::dynamicCast(Abstract_Object *o) const
  {
    return dynamic_cast<  SimpleVariableValue<T> *> (o);
  }
  
  template<typename T>
  const SimpleVariableValue<T> *SimpleVariableValue<T>::dynamicCast(const Abstract_Object *o) const
  {
    return dynamic_cast<  const SimpleVariableValue<T> *> (o);
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
    if (getEnvironment()!=nullptr)
      return getEnvironment()->U(unitId_);
    else
      return nullptr;
  }
  
  
  
  template<typename T>
  SimpleVariableValue<T>::SimpleVariableValue(std::string variablename,
                                              T v,
                                              std::string unit,
                                              Environment *e)
    : Abstract_Object(e),
      variableId_(variablename),
      unitId_(unit),
      value_(v)
  {
  }
  
  
  template<typename T>
  SimpleVariableValue<T>::SimpleVariableValue()
    : variableId_(),
      unitId_(),
      value_()
  {  }
  
  
  
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
  std::size_t SimpleVariableValue<std::size_t>::get(const std::string& singleLine,std::size_t* pos)
  {
    std::size_t out;
    try
    {
      out=std::stoul(singleLine,pos);
    }
    catch (...)
    {
      return 0;
    }
    return out;
  }
  
  
  template<>
  bool SimpleVariableValue<double>::isUnknown()const
  {
    return std::isnan(value_);
  }


  template<>
  bool SimpleVariableValue<std::size_t>::isUnknown()const
  {
    return value_==std::numeric_limits<std::size_t>::max();
  }
  
  template<>
  double SimpleVariableValue<double>::unknownValue()
  {
    return std::numeric_limits<double>::quiet_NaN();
  }



  template<>
  std::size_t SimpleVariableValue<std::size_t>::unknownValue()
  {
    return std::numeric_limits<std::size_t>::max();
  }

  
  
  template<>
  double SimpleVariableValue<double>::get(const std::string& singleLine,std::size_t* pos)
  {
    double out;
    try
    {
      out=std::stod(singleLine,pos);
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
    if (variableId_.empty()&&unitId_.empty())
      return "";
    std::string out=variableId_+"\n";
    out+=std::to_string(value());
    out+=unitId_+"\n";
    return out;
  }
  
  
  template<typename T>
  bool SimpleVariableValue<T>::ToObject(Environment* e,const std::string& multipleLines, std::size_t &pos)
  {
    std::size_t pos0=pos;
    variableId_=Named_Object::getName(multipleLines,pos);
    const Named_Object* p=e->V(variableId_);
    if (p!=nullptr)
      {
        if (dynamic_cast<const SimpleVariable<T>*>(p)==nullptr)
          {
            pos=pos0;
            return false;
          }
      }
    ++pos;
    std::string line=Named_Object::nextLine(multipleLines,pos);
    if (!SimpleVariableValue<T>::is(line))
      {
        pos=pos0;
        return false;
      }
    std::size_t posline=0;
    value_=SimpleVariableValue<T>::get(line,&posline);
    unitId_=Base_Unit::getUnit(line.substr(posline));
    if (this->isInternallyValid())
      {
        setEnvironment(e);
        return true;
      }
    else
      return false;
    
  }
  
  
  
  
  template<typename T>
  std::string SimpleVariable<T>::ToString()const
  {
    std::string out=Named_Object::ToString();
    if (out.empty()&&unitId_.empty())
      return "";
    out+=std::to_string(defautValue_);
    out+=unitId_+"\n";
    return out;
  }
  
  template<typename T>
  bool SimpleVariable<T>::ToObject(Environment* e,const std::string& multipleLines, std::size_t &pos)
  {
    std::size_t pos0=pos;
    if (!Named_Object::ToObject(e,multipleLines,pos))
      {
        pos=pos0;
        return false;
      }
    std::string line=nextLine(multipleLines,pos);
    if (!SimpleVariableValue<T>::is(line))
      {
        pos=pos0;
        return false;
      }
     std::size_t posline=0;
    defautValue_=SimpleVariableValue<T>::get(line,&posline);
    unitId_=Base_Unit::getUnit(line.substr(posline));

    return true;
  }
  
  
  
  
  //  std::string Complex_Object::getClassName(const std::string& singleLine)
  //  {
  //    std::size_t pos=0;
  //    std::string classname=Named_Object::getName(singleLine,pos);
  //    std::string bgl=Named_Object::getName(singleLine,pos);
  //    if (bgl==beginLabel())
  //      return classname;
  //    else
  //      return "";
  
  //  }
  
  
  
  //  std::string Complex_Object::getFieldName(const std::string &singleLine)
  //  {
  //    std::size_t pos=0;
  //    std::string fieldname=Named_Object::getName(singleLine,pos);
  //    return fieldname;
  //  }
  
  static Abstract_Variable_Object* getFieldValue(const std::string multipleLines,std::size_t& pos)
  {
    std::string line=Named_Object::nextLine(multipleLines,pos);
    
  }
  
  
  
  
  
  
  
  //  std::string Complex_Object::ClassName(){
  //    return "Complex_object";
  //  }
  
  //  std::string Complex_Object::myClass()const{
  //    return ClassName();
  //  }
  
  
  //  std::set<std::string> Complex_Object:: SuperClasses() {
  //    auto mySC=Abstract_Object::mySuperClasses();
  //    mySC.insert(ClassName());
  //    return mySC;
  //  }
  
  
  //  std::size_t Complex_Object::numFields()const{
  //    return fieldNames_.size();
  //  }
  
  //  std::string Complex_Object::fieldName(std::size_t i)const{
  //    return fieldNames_[i];
  //  }
  
  
  //  bool Complex_Object::hasField(const std::string& fieldN)const
  //  {
  //    return fieldVariables_.find(fieldN)!=fieldVariables_.end();
  //  }
  
  
  //  bool Complex_Object::setField(const std::string& fieldN,Abstract_Object*  o)
  //  {
  //    if (hasField(fieldN))
  //      {
  //        fieldVariables_[fieldN]=o;
  //        return true;
  //      }
  //    else
  //      return false;
  //  }
  
  
  //  bool Complex_Object::push_back(const std::string & fieldname,
  //                                 Abstract_Object* object)
  //  {
  //    if (!setField(fieldname,object))
  //      {
  //        fieldNames_.push_back(fieldname);
  //        fieldVariables_[fieldname]=object;
  //      }
  //    return true;
  
  //  }
  
  
  
  //  const Abstract_Object* Complex_Object::fieldVariable(const std::string& fieldname)const
  //  {
  //    auto it=fieldVariables_.find(fieldname);
  //    if (it!=fieldVariables_.end())
  //      return it->second;
  //    else
  //      return nullptr;
  //  }
  //  Abstract_Object *Complex_Object::fieldVariable(const std::string& fieldname)
  //  {
  //    auto it=fieldVariables_.find(fieldname);
  //    if (it!=fieldVariables_.end())
  //      return it->second;
  //    else
  //      return nullptr;
  //  }
  
  
  
  //  std::string Complex_Object::ToString()const{
  //    std::string out=beginLine()+"\n";
  //    for (std::size_t i=0; i<numFields(); ++i)
  //      {
  //        out+=fieldName(i)+"\n";
  //        out+=fieldVariable(fieldName(i))->ToString();
  //      }
  //    out+=endLine()+"\n";
  //    return out;
  //  }
  
  //  bool Complex_Object::ToObject(Environment* e,const std::string& multipleLines, std::size_t &pos)
  //  {
  //    std::size_t pos0=pos;
  //    std::string line=Named_Object::nextLine(multipleLines,pos);
  //    if (line!=beginLine())
  //      {
  //        pos=pos0;
  //        return false;
  //      }
  
  //    if (!Named_Object::ToObject(e,multipleLines,pos))
  //      return false;
  
  
  //    line=nextLine(multipleLines,pos);
  //    while ((line!=endLine())&&pos<multipleLines.size())
  //      {
  //        std::string fieldname=getFieldName(line);
  //        if (!hasField(fieldname))
  //          {
  //            pos=pos0;
  //            return false;
  //          }
  //        Abstract_Object *v=this->fieldVariable(fieldname);
  //        v->ToObject(e,multipleLines,pos);
  //        line=nextLine(multipleLines,pos);
  //      }
  //    return true;
  
  //  }
  
  //  bool Complex_Object::IsObject(const std::string& singleLine)const
  //  {
  //    return singleLine==beginLine();
  //  }
  
  //  Complex_Object:: ~Complex_Object(){}
  
  //  Complex_Object::Complex_Object(Environment* e,
  //                                 std::string name,
  //                                 std::string tip,
  //                                 std::string whatthis)
  //    :
  //      Named_Object(e,name,tip,whatthis)
  //  {}
  
  
  
  
  //  std::string Composite_Variable::ClassName(){
  //    return "Complex_Variable";
  //  }
  
  //  std::string Composite_Variable::myClass()const{
  //    return ClassName();
  //  }
  
  
  //  std::set<std::string> Composite_Variable:: SuperClasses() {
  //    //public Variable_Object, public Complex_Object
  //    auto mySC=Abstract_Variable_Object::mySuperClasses();
  //    auto co=Complex_Object::mySuperClasses();
  //    mySC.insert(co.begin(),co.end());
  //    mySC.insert(ClassName());
  //    return mySC;
  //  }
  
  
  
  //  Abstract_Variable_Object const * Composite_Variable::fieldVariable(const std::string& fieldname)const
  //  {
  //    return dynamic_cast<Abstract_Variable_Object const *>(Complex_Object::fieldVariable(fieldname));
  //  }
  
  //  Abstract_Variable_Object  * Composite_Variable::fieldVariable(const std::string& fieldname)
  //  {
  //    return dynamic_cast<Abstract_Variable_Object*>(Complex_Object::fieldVariable(fieldname));
  
  //  }
  
  
  //  bool Composite_Variable::setField(const std::string& fieldN,Abstract_Variable_Object*  o)
  //  {
  //    return Complex_Object::setField(fieldN,o);
  //  }
  
  
  //  bool Composite_Variable::push_back(const std::string &fieldname,
  //                                   Abstract_Variable_Object* object)
  //  {
  //    return Complex_Object::push_back(fieldname,object);
  
  //  }
  
  //  Composite_Variable::Composite_Variable(Environment* e,
  //                                     std::string name,
  //                                     std::string tip,
  //                                     std::string whatthis)
  //    :Complex_Object(e,name,tip,whatthis)
  //  {
  //    e->addVariable(this);
  //  }
  
  
  //  Composite_Variable::~Composite_Variable(){}
  
  //  std::string Complex_Variable_Value::ClassName(){
  //    return "Complex_Variable_Value";
  //  }
  
  //  std::string Complex_Variable_Value::myClass()const{
  //    return ClassName();
  //  }
  
  
  //  std::set<std::string> Complex_Variable_Value:: SuperClasses() {
  //    //public Complex_Object,public Value_Object
  
  //    auto mySC=Complex_Object::mySuperClasses();
  //    auto vo=Abstract_Value_Object::mySuperClasses();
  //    mySC.insert(vo.begin(),vo.end());
  //    mySC.insert(ClassName());
  //    return mySC;
  //  }
  
  
  //  Abstract_Value_Object const * Complex_Variable_Value::fieldVariable(const std::string& fieldname)const
  //  {
  //    return dynamic_cast<Abstract_Value_Object const *>(Complex_Object::fieldVariable(fieldname));
  //  }
  
  //  Abstract_Value_Object  * Complex_Variable_Value::fieldVariable(const std::string& fieldname)
  //  {
  //    return dynamic_cast<Abstract_Value_Object*>(Complex_Object::fieldVariable(fieldname));
  
  //  }
  
  
  //  bool Complex_Variable_Value::setField(const std::string& fieldN,Abstract_Value_Object*  o)
  //  {
  //    return Complex_Object::setField(fieldN,o);
  //  }
  
  
  //  bool Complex_Variable_Value::push_back(const std::string &fieldname,
  //                                         Abstract_Value_Object* object)
  //  {
  //    return Complex_Object::push_back(fieldname,object);
  //  }
  
  
  
  //  Complex_Variable_Value::Complex_Variable_Value(Environment* e,
  //                                                 std::string name,
  //                                                 std::string tip,
  //                                                 std::string whatthis,
  //                                                 std::string complexvar):
  //    Complex_Object(e,name,tip,whatthis),
  //    cmplxvar_(dynamic_cast<Composite_Variable const*>(e->V(complexvar,Composite_Variable::ClassName())))
  //  {}
  
  //  Complex_Variable_Value::~Complex_Variable_Value(){}
  
  
  
  
  //  Complex_Variable_Value* Composite_Variable::defaultValue() const {
  
  //    Complex_Variable_Value* out= new Complex_Variable_Value(
  //          getEnvironment(),
  //          idName()+"_default_sample",
  //          "default sample",
  //          idName()+"complex variable default sample",
  //          idName());
  //    for (std::size_t i=0; i<this->numFields(); i++)
  //      {
  //        out->push_back(fieldName(i),fieldVariable(fieldName(i))->defaultValue());
  //      }
  //    return out;
  
  //  }
  
  
  
  //  const Abstract_Variable_Object* Complex_Variable_Value::variable()const
  //  {
  //    return cmplxvar_;
  
  //  }
  
  
  
  
  template
  class SimpleVariable<std::size_t>;
  
  template
  class SimpleVariable<double>;
  
  
  template
  class SimpleVariableValue<std::size_t>;
  
  template
  class SimpleVariableValue<double>;
  
  Abstract_Object *Environment::create(std::string classname)
  {
    auto it=classes_.find(classname);
    if (it!=classes_.end())
      return it->second->create();
    else
      return nullptr;
    
  }
  
  
  bool Environment::doesDynCast(const Abstract_Object *o, std::string classname)
  {
    // concrete classes
    auto it=classes_.find(classname);
    if (it!=classes_.end())
      {
        const Abstract_Object* c=it->second;
        return c->dynamicCast(o)!=nullptr;
      }
    else
      // Abstract classes one by one
      if (classname==Abstract_Object::ClassName())
        return dynamic_cast<const Abstract_Object*>(o)!=nullptr;
      else if (classname==Abstract_Valued_Object::ClassName())
        return dynamic_cast<const Abstract_Valued_Object*>(o)!=nullptr;
      else if (classname==Abstract_Value_Object::ClassName())
        return dynamic_cast<const Abstract_Value_Object*>(o)!=nullptr;
      else if (classname==Abstract_Variable_Object::ClassName())
        return dynamic_cast<const Abstract_Variable_Object*>(o)!=nullptr;
      else return false;
    
  }
  
  std::set<std::string> Environment::getSuperClasses(const std::string &classname)
  {
    // concrete classes
    Abstract_Object* o=create(classname);
    std::set<std::string> s;
    for (auto it:classes_)
      {
        const Abstract_Object* v=it.second;
        if (v->dynamicCast(o))
          s.insert(it.first);
      }
    // Abstract classes one by one
    if (dynamic_cast<const Abstract_Object*>(o)!=nullptr)
      s.insert(Abstract_Object::ClassName());
    if (dynamic_cast<const Abstract_Valued_Object*>(o)!=nullptr)
      s.insert(Abstract_Valued_Object::ClassName());
    if (dynamic_cast<const Abstract_Value_Object*>(o)!=nullptr)
      s.insert(Abstract_Value_Object::ClassName());
    if (dynamic_cast<const Abstract_Variable_Object*>(o)!=nullptr)
      s.insert(Abstract_Variable_Object::ClassName());
    if (dynamic_cast<const Named_Object*>(o)!=nullptr)
      s.insert(Named_Object::ClassName());
    
    return s;
  }
  
  
  Environment::Environment()
    :
      units_{},
      variables_{},
      classes_{}
  {
    classes_[Base_Unit::ClassName()]=new Base_Unit;
    classes_[SimpleVariable<double>::ClassName()]=new SimpleVariable<double>;
    classes_[SimpleVariable<std::size_t>::ClassName()]=new SimpleVariable<std::size_t>;
    classes_[SimpleVariableValue<double>::ClassName()]=new SimpleVariableValue<double>;
    classes_[SimpleVariableValue<std::size_t>::ClassName()]=new SimpleVariableValue<std::size_t>;
  }
  
  
  
}

#include <sstream>

namespace  Markov_IO {
  
  
  std::string ToString(Markov_Object::Environment * const &x)
  {
    
    std::stringstream ss;
    ss<<x;
    std::string str=ss.str();
    return str;
    
  }
  std::string ToString(Markov_Object::Abstract_Object * const &x)
  {
    
    std::stringstream ss;
    ss<<x;
    std::string str=ss.str();
    return str;
    
  }
  std::string ToString(Markov_Object::Named_Object * const &x)
  {
    
    std::stringstream ss;
    ss<<x;
    std::string str=ss.str();
    return str;
    
  }
  
  std::string ToString(decltype (nullptr) const& )
  {
    return "nullptr";
  }
  
  
  
}



#ifdef MACRO_TEST

#include "Tests/TESTS.h"
#include "Tests/ElementaryTest.h"




namespace Markov_Test
{
  namespace Markov_Object_Test
  {
    
    using namespace Markov_Object;
    
    
    MultipleTests getClassInfoInvariants(const Abstract_Object* object_)
    {
      Environment E;
      
      MultipleTests classInfoI("classInfo",
                               "invariants");
      object_->myClassInfo();
      E.getSuperClasses(object_->myClass());
      
      classInfoI.push_back(TEST_EQ("myClassInfo.SuperClasses method",
                                   object_->myClassInfo().superClasses,
                                   E.getSuperClasses(object_->myClass())));
      
      return classInfoI;
      
      
    }
    
    MultipleTests getcreateInvariants(const Abstract_Object* object_)
    
    {
      MultipleTests createI("create() method ",
                            "o=object_->create()");
      Abstract_Object *o=object_->create();
      
      createI.push_back(ElementaryTest(" does not return a null pointer",
                                       "create()!=nullptr",
                                       o!=nullptr));
      
      
      if (o!=nullptr)
        {
          createI.push_back(TEST_EQ("creater pointer empty",
                                    o->empty(),true));
          createI.push_back(TEST_EQ("creater pointer not internally valid",
                                    o->isInternallyValid(),false));
          
          
          createI.push_back(TEST_EQ("match class",
                                    object_->myClass(),
                                    o->myClass()));
          
          
          createI.push_back(ElementaryTest("no Environment",
                                           "o->getEnvironment()==nullptr",
                                           o->getEnvironment()==nullptr));
          
          
        }
      delete o;
      return createI;
      
    }
    
    
    
    
    MultipleTests getToStringToObjectInvariants(const Abstract_Object* object_,
                                                Environment& E)
    {
      
      std::string environmentclass;
      std::string objectclass;
      
      if (E.empty())
        environmentclass="Empty";
      else if (object_->getEnvironment()==&E)
        environmentclass="Native";
      else
        environmentclass="Foreign";
      
      if (object_->empty())
        objectclass="empty";
      else if (object_->isValid())
        objectclass="valid";
      else
        objectclass="internallyValid";
      
      MultipleTests M(environmentclass+" Environment,"+objectclass+" object",
                      "To String/ ToObject invariants");
      
      
      if (!object_->isInternallyValid())
        {
          M.push_back(TEST_NEQ("internally invalid objects are  empty",
                               object_->isInternallyValid(),
                               object_->empty()));
          
          M.push_back(TEST_EQ("empty objects returns empty strings",
                              object_->ToString(),
                              std::string("")));
          
          Abstract_Object* o=object_->create();
          bool isToObject=o->ToObject(&E,object_->ToString());
          
          M.push_back(ElementaryTest("ToObject on empty string returns false",
                                     "ToString(ToObject(" "))==false ",
                                     isToObject==false));
          M.push_back(ElementaryTest("ToObject do not set the environment",
                                     "getEnvironment==nullptr",
                                     o->getEnvironment()==nullptr));
          
          
          
          
        }
      else
        {
          M.push_back(ElementaryTest("internally valid objects are not empty",
                                     "isinternallyvalid!=empty()",
                                     !object_->empty()));
          
          Abstract_Object* o=object_->create();
          bool isToObject=o->ToObject(&E,object_->ToString());
          
          
          MultipleTests M2("applying o->ToObject on o->ToString",
                           "invariants");
          
          
          
          M2.push_back(ElementaryTest("ToObject  returns true",
                                      "ToString(ToObject(ToString))==true ",
                                      isToObject));
          
          M2.push_back(TEST_EQ("myClass is recovered",
                               object_->myClass(),
                               o->myClass()));
          
          M2.push_back(TEST_EQ("ToString is recovered",
                               object_->ToString(),
                               o->ToString()));
          
          
          M.push_back(M2);
          MultipleTests M33("ToObject on getEnvironment",
                            "invariants");
          M33.push_back(ElementaryTest("ToObject sets the environment",
                                       "getEnvironment==&E",
                                       o->getEnvironment()==&E));
          
          if (!object_->myClassInfo().refersEnvironment)
            {
              M33.push_back(ElementaryTest("refersToValidObjects true",
                                           "In a new environment if it does not refer to anyone,"
                                           "the object is valid "
                                           "object_->refersToValidObjects()==true",
                                           object_->refersToValidObjects()==true));
            }
          else if  (E.empty()|| &E!=object_->getEnvironment())
            {
              if (E.empty())
                M33.push_back(ElementaryTest("In a new empty environment references are invalid",
                                             "o->refersToValidObjects()==false",
                                             o->refersToValidObjects()==false));
              
              if (object_->refersToValidObjects())
                {
                  auto ref=object_->referencedObjects();
                  for (auto s:ref)
                    {
                      const Named_Object* rob=object_->getEnvironment()->V(s);
                      if (rob==nullptr)
                        rob=object_->getEnvironment()->U(s);
                      if (rob!=nullptr)
                        {
                          Named_Object* oo=rob->create();
                          std::string strrob=rob->ToString();
                          if (oo->ToObject(&E,strrob))
                            E.add(oo);
                          
                          
                        }
                    }  // referred objects added to environment
                  
                  M33.push_back(ElementaryTest("After adding the referred objects",
                                               "object_->refersToValidObjects()==true",
                                               o->refersToValidObjects()==true));
                }
              
            }
          else if (&E==object_->getEnvironment())
            {
              M33.push_back(ElementaryTest("In the same environment references are valid",
                                           "object_->refersToValidObjects()==o->refersToValidObjects",
                                           o->refersToValidObjects()==object_->refersToValidObjects()));
            }
          
          M.push_back(M33);
          
          std::string acontext;
          auto ref=object_->referencedObjects();
          
          for (auto s:ref)
            {
              if (object_->getEnvironment()->V(s)!=nullptr)
                acontext+=object_->getEnvironment()->V(s)->ToString();
              else if (object_->getEnvironment()->U(s)!=nullptr)
                acontext+=object_->getEnvironment()->U(s)->ToString();
            }
          M.push_back(TEST_EQ("contextToString has all the referencedObjects",
                              object_->contextToString(),
                              acontext));
        }
      
      return M;
    }
    
    
    
    MultipleTests Abstract_Object_Test::classInvariant()const
    {
      MultipleTests results(Abstract_Object::ClassName(),
                            "Class Invariants");
      
      MultipleTests methodsI("methods",
                             "invariants");
      
      object_->myClassInfo();
      
      methodsI.push_back(getClassInfoInvariants(object_));
      
      methodsI.push_back(getcreateInvariants(object_));
      
      
      MultipleTests ToStringToObjectI("ToString()  ToObject() methods ",
                                      "invariants");
      
      Environment E;
      ToStringToObjectI.push_back(getToStringToObjectInvariants(object_,E));
      if (object_->getEnvironment()!=nullptr)
        ToStringToObjectI.push_back(getToStringToObjectInvariants(object_,*object_->getEnvironment()));
      
      
      methodsI.push_back(ToStringToObjectI);
      results.push_back(methodsI);
      
      return results;
      
      
    }
    
    Abstract_Object_Test::Abstract_Object_Test(const Abstract_Object *object)
      :
        object_(object)
    {}
    
    Abstract_Object_Test::~Abstract_Object_Test()
    {
      
    }
    
    std::string Abstract_Object_Test::TestName()
    {
      return "Abstract_Object_Test";
    }
    
    std::string Abstract_Object_Test::myTest()const
    {
      return TestName();
    }
    
    
    MultipleTests isreferenced(const Named_Object* o)
    {
      MultipleTests M("is-Referenced",
                      "poscondition");
      
      if (o->isReferenced())
        M.push_back(TEST_EQ("the environment returns a reference to this",
                            o->getEnvironment()->V(o->idName())
                            ,o));
      else
        M.push_back(TEST_NEQ("the environment returns not a reference to this",
                             o->getEnvironment()->V(o->idName())
                             ,o));
      return M;
      
    }
    
    
    MultipleTests idNameInvariant(const Named_Object* o,Environment* E)
    {
      std::string environmentclass;
      std::string objectclass;
      
      if (E->empty())
        environmentclass="Empty";
      else if (o->getEnvironment()==E)
        environmentclass="Native";
      else
        environmentclass="Foreign";
      
      if (o->empty())
        objectclass="empty";
      else if (o->isValid())
        objectclass="valid";
      else if (o->isDuplicate())
        objectclass="duplicate";
      else
        objectclass="internallyValid";
      
      MultipleTests M(environmentclass+" Environment,"+objectclass+" object",
                      "To String/ ToObject invariants");
      
      if (o->isValid()&&!o->isDuplicate())
        
        {
          MultipleTests M2("case isValid and not duplicate",
                           "conditions");
          M2.push_back(TEST_EQ("isReferenced",
                               o->getEnvironment()->V(o->idName()),o));
          M2.push_back(TEST_EQ("same value",
                               o->getEnvironment()->V(o->idName())->ToString(),
                               o->ToString()));
          M2.push_back(TEST_EQ("same name",
                               o->getEnvironment()->V(o->idName())->idName(),
                               o->idName()));
          M.push_back(M2);
        }
      else if (o->isDuplicate())
        {
          MultipleTests M2("duplicate Objects ",
                           "the environment has a copy");
          M2.push_back(TEST_NEQ("different address",
                                o->getEnvironment()->V(o->idName()),
                                o));
          M2.push_back(TEST_EQ("same name",
                               o->getEnvironment()->V(o->idName())->idName(),
                               o->idName()));
          M.push_back(M2);
          
          
        }
      else if (o->getEnvironment()!=nullptr)
        {
          MultipleTests M2("non integrated Objects ",
                           "the environment knows nothing about them");
          
          M2.push_back(TEST_EQ("no address",
                               o->getEnvironment()->V(o->idName()),
                               nullptr));
          M.push_back(M2);
        }
      
      
      // now test on to object and generation of duplicates
      Named_Object* no=o->create();
      std::size_t n=0;
      bool isno=no->ToObject(E,o->ToString(),n);
      
      // operations on empty objects produce nothing
      
      if (!o->isInternallyValid())
        {
          MultipleTests M2("internally invalid object",
                           "o->isInternallyValid()==false");
          
          M2.push_back(ElementaryTest("result of ToObject",
                                      "no->ToObject(E,o->ToString(),n)==false",
                                      isno==false));
          
          M2.push_back(TEST_NEQ("the environment is not transferred",
                                no->getEnvironment(),E));
          
          M2.push_back(TEST_EQ("the new object is empty",
                               no->empty(),true));
          
          M2.push_back(TEST_EQ("the new object gives empty string",
                               no->ToString(),std::string("")));
          M.push_back(M2);
          
        }
      else
        {
          MultipleTests M2("internally valid object",
                           "o->isInternallyValid()==true");
          
          M2.push_back(TEST_EQ("refers to the provided environment",
                               no->getEnvironment(),E));
          
          if (environmentclass=="empty")
            {
              M2.push_back(TEST_EQ("is not duplicate",
                                   no->isDuplicate(),false));
              M2.push_back(TEST_EQ("the Environment has no reference of this yet",
                                   E->V(no->idName()),nullptr));
              
            }
          else if ((environmentclass=="native")&&(o->isValid()))
            {
              M2.push_back(TEST_EQ("is duplicate",
                                   no->isDuplicate(),true));
              M2.push_back(TEST_EQ("the Environment refers the old object ",
                                   E->V(no->idName()),o));
              M2.push_back(TEST_EQ("same name",
                                   E->V(o->idName())->idName(),
                                   no->idName()));
            }
          M.push_back(M2);
          if (o->getEnvironment()!=E)
            {
              E->add(no);
              MultipleTests M3("Environment adds the new object",
                               "postconditions of this operation");
              
              M3.push_back(TEST_EQ("Environment returns the right address",
                                   E->V(no->idName()),
                                   no));
              M3.push_back(TEST_EQ("same value",
                                   E->V(no->idName())->ToString(),
                                   no->ToString()));
              
              M3.push_back(TEST_EQ("not duplicate",
                                   no->isDuplicate(),
                                   false));
              
              
              M.push_back(M3);
              // add a duplicate
              Named_Object* no2=o->create();
              std::size_t n2=0;
              MultipleTests M4("we create a second copy in the Environment",
                               "postconditions of this operation");
              
              bool isno2=no2->ToObject(E,o->ToString(),n2);
              M4.push_back(ElementaryTest("succesfully created",
                                          "no2->ToObject(E,o->ToString())==true",
                                          isno2));
              
              M4.push_back(TEST_EQ("returns the same string",
                                   no2->ToString(),
                                   o->ToString()));
              
              M4.push_back(TEST_EQ("new object is duplicate",
                                   no2->isDuplicate(),
                                   true));
              
              M4.push_back(TEST_EQ("old new object is not duplicate",
                                   no->isDuplicate(),
                                   false));
              
              
              
              M.push_back(M4);
              MultipleTests M5("we add the second copy to the Environment",
                               "postconditions of this operation");
              
              E->add(no2);
              M5.push_back(TEST_EQ("point to new object",
                                   E->V(o->idName()),
                                   no2));
              
              M.push_back(M5);
              
              
            }
        }
      
      return M;
    }
    
    
    MultipleTests Named_Object_Test::classInvariant() const
    {
      
      
      MultipleTests M("Named Object Tests",
                      "interface invariants");
      
      M.push_back(Abstract_Object_Test::classInvariant());
      
      Environment E;
      M.push_back(idNameInvariant(named_object_,&E));
      if (named_object_->getEnvironment()!=nullptr)
        M.push_back(idNameInvariant(named_object_,named_object_->getEnvironment()));
      
      return M;
      
    }
    
    
    MultipleTests variableMethodPostConditions(const Abstract_Value_Object* o)
    {
      MultipleTests M("variable() method",
                      "postconditions");

      if (o->isValid())
        {
          M.push_back(TEST_NEQ("returns a non null pointer",
                               o->variable(),
                               nullptr));
          M.push_back(TEST_EQ("is a valid value of its variable",
                              o->variable()->isValidValue(o),
                              true));
        }

      return M;
      }




    
    MultipleTests unknownMethodPostConditions(const Abstract_Value_Object* o)
    {
      MultipleTests M("unknown() method",
                      "postconditions");

      Abstract_Value_Object* u=o->variable()->unKnownValue();
      M.push_back(ElementaryTest("variable()->unknown",
                                 "o->variable()->unKnownValue()->isUnknown()==true",
                                 u->isUnknown()==true));
      Abstract_Value_Object* ou=o->create();
      bool isu=ou->ToObject(o->getEnvironment(),u->ToString());
      M.push_back(ElementaryTest("serialize unknown value",
                                 "ToObject(unknownValue)==true",
                                 isu==true));

      M.push_back(TEST_EQ("same string",
                              u->ToString(),
                          ou->ToString()));

      return M;

    }






    MultipleTests Abstract_Value_Test::classInvariant() const
    {
      
      
      MultipleTests M("Abstract Value Tests",
                      "interface invariants");
      M.push_back(Abstract_Object_Test::classInvariant());
      
      M.push_back(variableMethodPostConditions(this->value_object_));
      M.push_back(unknownMethodPostConditions(this->value_object_));

      return M;
      
    }


    
  }
}

#endif //MACRO_TEST



