#include "Markov_Object/Abstract_Named_Object.h"
#include "Markov_Object/Measurement_Unit.h"

#include "Markov_Object/Environment.h"

namespace  Markov_Object {


  std::set<std::string> Abstract_Named_Object:: SuperClasses()
  {
    auto mySC=Abstract_Object::SuperClasses();
    mySC.insert(ClassName());
    return mySC;
  }

  Class_info Abstract_Named_Object::classInfo()
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

  Class_info Abstract_Named_Object::myClassInfo() const
  {
    return classInfo();
  }


  std::string Abstract_Named_Object::ClassName()
  {
    return "Named_Object";
  }

  Abstract_Named_Object *Abstract_Named_Object::dynamicCast(Abstract_Object *o) const
  {
    return dynamic_cast<Abstract_Named_Object*>(o);
  }

  const Abstract_Named_Object *Abstract_Named_Object::dynamicCast(const Abstract_Object *o) const
  {
    return dynamic_cast<const Abstract_Named_Object*>(o);
  }

  Abstract_Named_Object::~Abstract_Named_Object()
  {}


  std::string Abstract_Named_Object::idName()const
  {
    return variableName_;
  }

  bool Abstract_Named_Object::isReferenced() const
  {
    return (getEnvironment()!=nullptr)&&(getEnvironment()->V(idName())==this);
  }

  bool Abstract_Named_Object::isDuplicate() const
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
  std::string Abstract_Named_Object::Tip()const
  {
    return tip_;
  }

  /// a short description of the class
  std::string Abstract_Named_Object::WhatThis()const
  {
    return whatThis_;
  }

  void Abstract_Named_Object::setTip(const std::string &newTip){
    tip_=newTip;
  }

  void Abstract_Named_Object::setWhatThis(const std::string& whatthis)
  {
    whatThis_=whatthis;

  }






  std::string Abstract_Named_Object::ToString()const
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
  bool Abstract_Named_Object::ToObject(Environment* e,const std::string& text,std::size_t& cursor)
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



  Abstract_Named_Object::Abstract_Named_Object(Environment* e,
                             std::string variablename,
                             std::string tip,
                             std::string whatthis)
    :
      Abstract_Object(e),
      variableName_{variablename},tip_{tip},whatThis_{whatthis}

  {
  }


  Abstract_Named_Object::Abstract_Named_Object(Environment* e)
    :
      Abstract_Object(e),
      variableName_{},tip_{},whatThis_{}{

  }

  Abstract_Named_Object::Abstract_Named_Object()
    :
      Abstract_Object(),
      variableName_{},tip_{},whatThis_{}{}


  std::string Abstract_Named_Object::myClass()const
  {
    return ClassName();
  }


  std::string Abstract_Named_Object::getName(const std::string& multiplelines,std::size_t& pos)

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

  std::string Abstract_Named_Object::getTip(const std::string& multiplelines, std::size_t &pos)
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

  std::string Abstract_Named_Object::removeInitialSpaces(const std::string& line)
  {
    if (line.empty())
      return "";
    return line.substr(line.find_first_not_of(" \t"));
  }


  std::string Abstract_Named_Object::nextLine(const std::string &lines, std::size_t &n)
  {
    std::size_t n0=n;
    std::size_t nlast=lines.find_first_of("\r\n",n0);
    n=lines.find_first_of("\n",n0);
    if (n!=std::string::npos) n++;
    return lines.substr(n0,nlast-n0);
  }

  std::string Abstract_Named_Object::getWhatThis(const std::string& multiplelines, std::size_t &pos)
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





}




#ifdef MACRO_TEST

#include "Tests/TESTS.h"
#include "Tests/ElementaryTest.h"




namespace Markov_Test
{
  namespace Markov_Object_Test
  {

    using namespace Markov_Object;





    MultipleTests isreferenced(const Abstract_Named_Object* o)
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


    MultipleTests idNameInvariant(const Abstract_Named_Object* o,Environment* E)
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
      Abstract_Named_Object* no=o->create();
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
              Abstract_Named_Object* no2=o->create();
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





    MultipleTests Abstract_Named_Object_Test::classInvariant() const
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



  }
}

#endif //MACRO_TEST



