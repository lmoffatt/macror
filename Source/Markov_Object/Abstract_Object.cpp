#include <cctype>

#include "Tests/AssertPlain.h"

#include "Markov_Object/Abstract_Object.h"
#include "Markov_Object/Environment.h"
#include "Markov_Object/Measurement_Unit.h"
#include "Markov_Object/Abstract_Variable_Object.h"


namespace Markov_Object
{


  
  std::string Abstract_Object::ClassName()
  {
    return "Abstract_Object";
  }

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

  bool Abstract_Object::belongsTo(const std::string classname) const
  {
    return myClassInfo().superClasses.count(classname)!=0;
  }

  Environment *Abstract_Object::getEnvironment() const
  {
    return E_;
  }


  bool Abstract_Object::isValid() const
  {
    return isInternallyValid()&&refersToValidObjects();
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

  bool Abstract_Object::ToObject(Environment *e, const std::string &text)
  {
    std::size_t n=0;
    return ToObject(e,text,n);
  }


  Abstract_Object::Abstract_Object(Environment *E):
    E_(E){}

  Abstract_Object::Abstract_Object():
    E_(nullptr){}
  

  
  Abstract_Object::~Abstract_Object()
  {}

  void Abstract_Object::setEnvironment(Environment *E)
  {
    E_=E;
  }
  
  
  //  std::string Complex_Object::beginLabel()
  //  {
  //    return "Begin";
  //  }
  
  //  std::string Complex_Object::endLabel()
  //  {
  //    return "End";
  //  }
  

  
  
  
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
  
  

  Abstract_Valued_Object *Abstract_Valued_Object::dynamicCast(Abstract_Object *o) const
  {
    return dynamic_cast<Abstract_Valued_Object*>(o);
  }
  
  const Abstract_Valued_Object *Abstract_Valued_Object::dynamicCast(const Abstract_Object *o) const
  {
    return dynamic_cast<const Abstract_Valued_Object*>(o);
  }


  
  
  
  

  
  
  
  
  
  
  //  std::string Complex_Object::beginLine()const
  //  {
  //    return myClass()+" "+beginLabel();
  //  }
  //  std::string Complex_Object::endLine()const
  //  {
  //    return myClass()+" "+endLabel();
  //  }
  
  
  
  

  
  
  
  
  


  
  
  
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
    std::string line=Abstract_Named_Object::nextLine(multipleLines,pos);
    
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
  std::string ToString(Markov_Object::Abstract_Named_Object * const &x)
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
                      const Abstract_Named_Object* rob=object_->getEnvironment()->V(s);
                      if (rob==nullptr)
                        rob=object_->getEnvironment()->U(s);
                      if (rob!=nullptr)
                        {
                          Abstract_Named_Object* oo=rob->create();
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
              if (object_->getEnvironment()->idN(s)!=nullptr)
                acontext+=object_->getEnvironment()->idN(s)->ToString();
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
    
    



  }
}

#endif //MACRO_TEST



