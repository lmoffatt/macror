
#include "Tests/AssertPlain.h"
#include <cctype>

#include "Markov_Object/Abstract_Object.h"





namespace Markov_Object{



  Class_info Abstract_Object::classInfo()
  {
    return Class_info
    {
        {ClassName()},
        {ClassName()},
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



  bool Abstract_Variable_Object::isValueValid(const Abstract_Value_Object* v)const
  {
    return v->myClassInfo().superClasses.count(defaultValue()->myClass())!=0;
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



  bool Abstract_Value_Object::isClonable()const
  {
    return true;
  }
  Abstract_Value_Object* Abstract_Value_Object::create()const
  {
    return variable()->defaultValue();
  }












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

  Environment* Named_Object::getEnvironment() const
  {
    return e_;
  }

  //  const Environment* Named_Object::getEnvironment()const
  //  {
  //    return e_;
  //  }





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
      Abstract_Object(),
      e_(e),variableName_{variablename},tip_{tip},whatThis_{whatthis}

  {
    auto p=e->V(variablename);
    bool isD=(p);
    isDuplicate_=isD;

  }


  Named_Object::Named_Object(Environment* e)
    :
      Abstract_Object(),
      e_{e},variableName_{},tip_{},whatThis_{},isDuplicate_(false){
    isDuplicate_=false;

  }

  Named_Object::Named_Object()
    :
      Abstract_Object(),
      e_{nullptr},variableName_{},tip_{},whatThis_{},isDuplicate_(false){}




  void Named_Object::setEnvironment(Environment *e)
  {
    e_=e;
  }






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

  Base_Unit *Base_Unit::dynamicCast(Abstract_Object *o) const
  {
    return dynamic_cast<Base_Unit*>(o);

  }

  const Base_Unit *Base_Unit::dynamicCast(const Abstract_Object *o) const
  {
    return dynamic_cast<const Base_Unit*>(o);

  }


  std::string Base_Unit::abbr()const{
    return abbr_;
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
    out+=abbr()+"\n";

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
    std::string abbreviation=getUnit(line);
    abbr_=abbreviation;

    return this;

  }




  Base_Unit::Base_Unit(std::string abbreviation,
                       std::string name,
                       Environment* e,
                       std::string tip,
                       std::string whatthis)
    :
      Named_Object(e,name,tip,whatthis),
      abbr_(abbreviation){
    e->addUnit(this);
  }

  Base_Unit::Base_Unit()
    :
      abbr_(){}


  Base_Unit::Base_Unit(Environment* e)
    :
      Named_Object(e),
      abbr_(){}


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
      Abstract_Object(),
      Abstract_Variable_Object(e,name,tip,whatthis),
      defautValue_(defaultValue),
      u_{e->U(unit)}
  {
    e->addVariable(this);
  }

  template<typename T>
  SimpleVariable<T>::SimpleVariable(Environment* e)
    :
      Abstract_Object(),
      Abstract_Variable_Object(e),
      defautValue_{T()},
      u_{nullptr}
  {}

  template<typename T>
  SimpleVariable<T>::SimpleVariable()
    :
      Abstract_Object(),
      Abstract_Variable_Object(),
      defautValue_{T()},
      u_{nullptr}
  {}


  template<typename T>
  SimpleVariableValue<T>* SimpleVariable<T>::defaultValue() const
  {
    return new SimpleVariableValue<T>(idName(),
                                      defautValue_,
                                      myUnit()->abbr(),
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
    return variable_;
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
    return variable_->myUnit();
  }



  template<typename T>
  SimpleVariableValue<T>::SimpleVariableValue(std::string variablename,
                                              T v,
                                              std::string unit,
                                              Environment *e)
    : variableId_(variablename),
      variable_(dynamic_cast<const SimpleVariable<T>*>(e->V(variablename))),
      unitId_(unit),
      unit_(e->U(unit)),
      value_(v)
  {
  }

  template<typename T>
  SimpleVariableValue<T>::SimpleVariableValue()
    : variableId_(),
      variable_(nullptr),
      unitId_(),
      unit_(nullptr),
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
    std::string out=this->variable()->idName()+"\n";
    out+=std::to_string(value());
    out+=myUnit()->abbr()+"\n";
    return out;
  }


  template<typename T>
  bool SimpleVariableValue<T>::ToObject(Environment* e,const std::string& multipleLines, std::size_t &pos)
  {
    std::size_t pos0=pos;
    std::string name=Named_Object::getName(multipleLines,pos);
    variableId_=name;
    const Named_Object* p=e->V(name);
    if (p!=nullptr)
      variable_=dynamic_cast<const SimpleVariable<T>*>(p);
    else
      {
        pos=pos0;
        return false;
      }
    std::string line=Named_Object::nextLine(multipleLines,pos);
    if (!SimpleVariableValue<T>::is(line))
      {
        pos=pos0;
        return false;
      }
    value_=SimpleVariableValue<T>::get(line);
    std::string ab=Base_Unit::getUnit(line);
    unit_=e->U(ab);
    return this;
  }




  template<typename T>
  std::string SimpleVariable<T>::ToString()const{
    std::string out=Named_Object::ToString();
    out+=std::to_string(defautValue_);
    out+=u_->abbr()+"\n";
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
        return nullptr;
      }
    defautValue_=SimpleVariableValue<T>::get(line);
    std::string ab=Base_Unit::getUnit(line);
    u_=Named_Object::getEnvironment()->U(ab);
    return this;
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


#ifdef MACRO_TEST

#include "Tests/ElementaryTest.h"

namespace Markov_Test
{
  namespace Markov_Object_Test
  {

    using namespace Markov_Object;


    MultipleTests Abstract_Object_Test::classInvariant()const
    {
      MultipleTests results(Abstract_Object::ClassName(),
                            "Class Invariant");

      MultipleTests pMI("methods",
                        "invariants");

      {
        MultipleTests pE("valid unsensitive",
                         "invariants that can be tested on an empty object");



        // validity of superclasses

        Environment E;
        auto sc=object_->myClassInfo().superClasses;
        auto sc2=E.getSuperClasses(object_->myClass());

        std::string ssc;
        for (auto e:sc)
          ssc=ssc+","+e;

        std::string ssc2;
        for (auto e:sc2)
          ssc2=ssc2+","+e;


        pE.push_back(ElementaryTest("myClassInfo.SuperClasses method",
                                    "it should include all classes that can be dynamic_casted \n"
                                    "\nmyClassInfo.SuperClasses  : "+ssc+
                                    "\nEnvironment dynamic_casted: "+ssc2,
                                    object_->myClassInfo().superClasses==
                                    E.getSuperClasses(object_->myClass())));



        MultipleTests cMI("create() method ",
                          "invariants");



        //
        Abstract_Object *o=object_->create();

        cMI.push_back(ElementaryTest(" does not return a null pointer",
                                     "create()!=nullptr",
                                     o!=nullptr));


        if (o!=nullptr)
          {
            cMI.push_back(ElementaryTest("creater pointer not internally valid",
                                         " !o->isInternallyValid()",
                                         !o->isInternallyValid()));


            cMI.push_back(ElementaryTest("match class",
                                         "it the object should be of myClass "+object_->myClass(),
                                         o->myClass()==object_->myClass()));



          }

        pE.push_back(cMI);

        pMI.push_back(pE);
        delete o;
      }
      {
        MultipleTests fMI("ToString()  ToObject() methods ",
                          "invariants");


        std::string str=object_->ToString();

        MultipleTests eEv("ToObject on ToString in an empty Environment",
                          "recovers an internally valid object with invalid references");

        Environment Eempty;







        //

        Abstract_Object* b=object_->create();
        bool isb=b->ToObject(&Eempty,str);


        eEv.push_back(ElementaryTest("the operation is successfull",
                                     "ToObject(E,ToString,n)==true",
                                     isb));

        eEv.push_back(ElementaryTest("the object is internallyValid",
                                     "b->isInternallyValid()",
                                     b->isInternallyValid()));

        eEv.push_back(ElementaryTest("the object returns exactly the same string",
                                     "o->ToString()==object_->ToString()",
                                     b->ToString()==object_->ToString()));

        if (object_->refersEnvironment())
          {
            eEv.push_back(ElementaryTest("the object refers to invalidObjects",
                                         "!o->refersToValidObjects()",
                                         b->refersToValidObjects()==false));
            eEv.push_back(ElementaryTest("the object is not valid",
                                         "o->isValid()==false",
                                         b->isValid()==false));


            std::string mycontext=object_->contextToString();
            std::string acontext;
            auto ref=object_->referencedObjects();

            for (const Abstract_Object* s:ref)
              acontext+=s->ToString()+"\n";
            eEv.push_back(ElementaryTest("contextToString has all the referencedObjects",
                                         "equality of output strings",
                                         mycontext==acontext));

            for (const Abstract_Object* s:ref)
              s->create()->ToObject(&Eempty,s->ToString());

            eEv.push_back(ElementaryTest("after adding the referenced objects, the object is valid",
                                         "o->isValid()==false",
                                         b->isValid()==true));
          }
        else
          {
            eEv.push_back(ElementaryTest("there is no objects to refer",
                                         "!o->refersToValidObjects()",
                                         b->refersToValidObjects()));
            eEv.push_back(ElementaryTest("the object is valid",
                                         "o->isValid()",
                                         b->isValid()));

          }




        //





        if (!object_->myClassInfo().hasIdName)









          results.push_back(pMI);

        return results;


      }
    }

    Abstract_Object_Test::Abstract_Object_Test(const Abstract_Object& object)
      :
        object_(&object)
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



  }
}

#endif //MACRO_TEST



