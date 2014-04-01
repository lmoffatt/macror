#include <string>
#include "Markov_Object/Abstract_Named_Object.h"
#include "Markov_Object/Measurement_Unit.h"

#include "Markov_Object/Environment.h"
#include "Markov_Object/IdentifierName.h"

namespace  Markov_Object {


  std::set<std::string> Abstract_Named_Object:: SuperClasses()
  {
    auto mySC=Abstract_Object::SuperClasses();
    mySC.insert(ClassName());
    return mySC;
  }


  std::set<std::string> Abstract_Named_Object::mySuperClasses() const
  {
    return SuperClasses();
  }


  std::string Abstract_Named_Object::ClassName()
  {
    return "Named_Object";
  }




  Abstract_Named_Object::~Abstract_Named_Object()
  {}

  Abstract_Named_Object::Abstract_Named_Object(const Abstract_Named_Object &other):
    Abstract_Refers_Environment(other.getEnvironment()),
    variableName_(other.variableName_),
    tip_(other.tip_),
    whatThis_(other.whatThis_){}








  bool Abstract_Named_Object::refersToValidObjects() const
  {
    for (auto o:this->referencedObjects())
      {
        auto v =getEnvironment()->idN(o);
        if (v==nullptr)
          return false;
      }
    return true;
  }

  std::string Abstract_Named_Object::contextToString() const
  {
    std::string s;
    for (auto r : referencedObjects())
      {
        auto v=getEnvironment()->idN(r);
        if (v!=nullptr)
          s+=v->ToString();

      }
    return s;
  }



  std::string Abstract_Named_Object::idName()const
  {
    return variableName_;
  }







  bool Abstract_Named_Object::empty() const
  {
    return (getEnvironment()==nullptr&&
            idName().empty()&&
            Tip().empty()&&
            WhatThis().empty());

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

  Abstract_Named_Object *Abstract_Named_Object::CreateObject(const std::string &text, std::size_t &cursor) const
  {
    auto tmp=create();
    auto out=tmp->ToObject(text,cursor);
    if (out==nullptr)
      delete tmp;
    return out;
  }

  Abstract_Named_Object*
  Abstract_Named_Object::ToObject(const std::string& text, std::size_t& cursor)
  {
    std::size_t c0=cursor;
    std::string name=IdentifierName::get(text,cursor);
    std::string tip=getTip(text,cursor);
    std::string whatthis=getWhatThis(text,cursor);
    if (name.empty()&&tip.empty()&&whatthis.empty())
      {
        cursor=c0;
        return nullptr;
      }


    if (!name.empty())
      {
        variableName_=name;
        if (!tip.empty())
          setTip(tip);
        if(!whatthis.empty())
          setWhatThis(whatthis);
        return this;
      }
    else
      return nullptr;
  }




  Abstract_Named_Object::Abstract_Named_Object(Environment*  e,
                                               std::string variablename,
                                               std::string tip,
                                               std::string whatthis)
    :
      Abstract_Refers_Environment(e),
      variableName_{variablename},tip_{tip},whatThis_{whatthis}

  {
  }


   Abstract_Named_Object::Abstract_Named_Object()
    :
      Abstract_Refers_Environment(),
      variableName_{},
      tip_{},
      whatThis_{}{}


  std::string Abstract_Named_Object::myClass()const
  {
    return ClassName();
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
    auto n=line.find_first_not_of(" \t");
    if (n==line.npos)
      return "";
    else
      return line.substr(n);
  }





  std::string Abstract_Named_Object::getTip(const std::string &multiplelines)
  {
    std::size_t n=0;
    return getTip(multiplelines,n);
  }

  std::string Abstract_Named_Object::getWhatThis(const std::string &multiplelines)
  {
    std::size_t n=0;
    return getWhatThis(multiplelines,n);
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

namespace  Markov_IO {

  std::string ToString(Markov_Object::Environment*const & x);

  std::string ToString(const std::shared_ptr<const Markov_Object::Abstract_Named_Object> &x)
  {

    std::stringstream ss;
    ss<<x;
    std::string str=ss.str();
    return str;

  }
  std::string ToString(const std::shared_ptr<const Markov_Object::Abstract_Variable_Object> &x)
  {

    std::stringstream ss;
    ss<<x;
    std::string str=ss.str();
    return str;

  }


  std::string ToString(const std::shared_ptr<const Markov_Object::Environment> &x)
  {
    std::stringstream ss;
    ss<<x;
    std::string str=ss.str();
    return str;

  }


}


/*

namespace Markov_Test
{
  namespace Markov_Object_Test
  {

    using namespace Markov_Object;






    /* move this to Quantity, Measurment_unit and Abstact_Variable

    MultipleTests idNameInvariant(std::shared_ptr<Abstract_Named_Object> o,
                                  Environment*  E)
    {
      std::string environmentclass;

      if (E->empty())
        environmentclass="Empty";
      else if (o->getEnvironment()==E)
        environmentclass="Native";
      else
        environmentclass="Foreign";

      MultipleTests M(environmentclass+" Environment,",
                      "To String/ ToObject invariants");

      if (!o->invalid()&&!o->empty())
        {
          if (o->isReferenced())

            {
              MultipleTests M2("case isValid and not duplicate",
                               "conditions",
              {"Abstract_Named_Object",
                               "Environment"},
              {Abstract_Named_Object::idName(),
                               Abstract_Named_Object::ToString(),
                               Environment::idN()});
              M2.push_back(TEST_EQ("isReferenced",
                                   o->getEnvironment()->idN(o->idName()).get(),o.get()));
              M2.push_back(TEST_EQ("same value",
                                   o->getEnvironment()->idN(o->idName())->ToString(),
                                   o->ToString()));
              M2.push_back(TEST_EQ("same name",
                                   o->getEnvironment()->idN(o->idName())->idName(),
                                   o->idName()));
              M.push_back(M2);
            }
          else if (o->isDuplicate())
            {
              MultipleTests M2("duplicate Objects ",
                               "the environment has a copy");
              M2.push_back(TEST_NEQ("different address",
                                    o->getEnvironment()->idN(o->idName()).get(),
                                    o.get()));
              M2.push_back(TEST_EQ("same name",
                                   o->getEnvironment()->idN(o->idName())->idName(),
                                   o->idName()));
              M.push_back(M2);


            }
          else
            {
              MultipleTests M2("non integrated Objects ",
                               "the environment knows nothing about them");

              M2.push_back(TEST_EQ("no address",
                                   o->getEnvironment()->V(o->idName()),
                                   nullptr));
              M.push_back(M2);
            }
        }

      // now test on to object and generation of duplicates
      std::size_t n=0;
      std::shared_ptr<Abstract_Named_Object> no(o->CreateObject(o->ToString(),n));
      bool isno=no.get()!=nullptr;

      // operations on empty objects produce nothing

      if (o->empty()||o->invalid())
        {
          MultipleTests M2("empty or invalid object",
                           "o->empty()||o->invalid()");

          M2.push_back(ElementaryTest("result of ToObject",
                                      "no->ToObject(E,o->ToString(),n)==false",
                                      isno==false));

          M2.push_back(TEST_NEQ("the environment is not transferred",
                                no->getEnvironment(),E));

          M2.push_back(TEST_EQ("the new object is empty or invalid",
                               no->empty()||no->invalid(),true));

          M.push_back(M2);

        }
      else
        {
          MultipleTests M2("valid object",
                           "!o->empty&&!o->invalid()==true");

          M2.push_back(TEST_EQ("refers to the provided environment",
                               no->getEnvironment(),E));

          if (environmentclass=="empty")
            {
              M2.push_back(TEST_EQ("is not duplicate",
                                   no->isDuplicate(),false));
              M2.push_back(TEST_EQ("the Environment has no reference of this yet",
                                   E->V(no->idName()),nullptr));

            }
          else if (environmentclass=="native")
            {
              M2.push_back(TEST_EQ("is duplicate",
                                   no->isDuplicate(),true));
              M2.push_back(TEST_EQ("the Environment refers the old object ",
                                   E->idN(no->idName()),o));
              M2.push_back(TEST_EQ("same name",
                                   E->idN(o->idName())->idName(),
                                   no->idName()));
            }
          M.push_back(M2);
          if (o->getEnvironment()!=E)
            {
              E->add(no);
              MultipleTests M3("Environment adds the new object",
                               "postconditions of this operation");

              M3.push_back(TEST_EQ("Environment returns the right address",
                                   E->idN(no->idName()),
                                   no));
              M3.push_back(TEST_EQ("same value",
                                   E->idN(no->idName())->ToString(),
                                   no->ToString()));

              M3.push_back(TEST_EQ("not duplicate",
                                   no->isDuplicate(),
                                   false));


              M.push_back(M3);
              // add a duplicate
              std::size_t n2=0;
              std::shared_ptr<Abstract_Named_Object> no2(o->CreateObject(o->ToString(),n2));
              MultipleTests M4("we create a second copy in the Environment",
                               "postconditions of this operation");

              bool isno2=no2.get()!=nullptr;
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
                                   E->idN(o->idName()),
                                   no2));

              M.push_back(M5);


            }
        }
      return M;

    }


    MultipleTests getToStringToObjectInvariants(
        std::shared_ptr<Abstract_Named_Object> object_,
       Environment*  E)
    {

      std::string environmentclass;
      std::string objectclass;

      if (E->empty())
        environmentclass="Empty";
      else if (object_->getEnvironment()==E)
        environmentclass="Native";
      else
        environmentclass="Foreign";

      if (object_->empty())
        objectclass="empty";
      else if (object_->invalid())
        objectclass="valid";
      else
        objectclass="internallyValid";

      MultipleTests M(environmentclass+" Environment,"+objectclass+" object",
                      "To String/ ToObject invariants");


      if (object_->invalid())
        {
          M.push_back(TEST_NEQ("invalid objects are not empty",
                               object_->invalid(),
                               object_->empty()));

          M.push_back(TEST_NEQ("invalid objects returns non empty strings",
                               object_->ToString(),
                               std::string("")));

          std::size_t n=0;
          std::unique_ptr<Abstract_Named_Object> o(object_->CreateObject(object_->ToString(),n));
          bool isToObject=o.get()!=nullptr;

          M.push_back(ElementaryTest("ToObject on invalid string returns false",
                                     "ToString(ToObject(" "))==false ",
                                     isToObject==false));




        }
      else if (!object_->empty())
        {
          M.push_back(ElementaryTest(" valid objects are not empty",
                                     "isinternallyvalid!=empty()",
                                     !object_->empty()));

          std::size_t n=0;
          std::shared_ptr<Abstract_Named_Object> o(object_->CreateObject(object_->ToString(),n));

          bool isToObject=o.get()!=nullptr;


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
                                       o->getEnvironment()==E));

          if (!object_->mySuperClasses().refersEnvironment)
            {
              M33.push_back(ElementaryTest("refersToValidObjects true",
                                           "In a new environment if it does not refer to anyone,"
                                           "the object is valid "
                                           "object_->refersToValidObjects()==true",
                                           object_->refersToValidObjects()==true));
            }
          else if  (E->empty()|| E!=object_->getEnvironment())
            {
              if (E->empty())
                M33.push_back(ElementaryTest("In a new empty environment references are invalid",
                                             "o->refersToValidObjects()==false",
                                             o->refersToValidObjects()==false));

              if (object_->refersToValidObjects())
                {
                  auto ref=object_->referencedObjects();
                  for (auto s:ref)
                    {
                     std::shared_ptr<const Abstract_Named_Object> rob=object_->getEnvironment()->idN(s);
                      if (rob!=nullptr)
                        {
                          std::size_t n=0;
                          std::string strrob=rob->ToString();
                          std::shared_ptr<Abstract_Named_Object> oo(rob->CreateObject(strrob,n));

                          if (oo.get()!=nullptr)
                            E->add(oo);


                        }
                    }  // referred objects added to environment

                  M33.push_back(ElementaryTest("After adding the referred objects",
                                               "object_->refersToValidObjects()==true",
                                               o->refersToValidObjects()==true));
                }

            }
          else if (E==object_->getEnvironment())
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

*/




/*
    MultipleTests Abstract_Named_Object_Test::classInvariant() const
    {


      MultipleTests M("Named Object Tests",
                      "interface invariants");

      M.push_back(Abstract_Object_Test::classInvariant());

      /*
      for (auto n:named_objects_)
        {
          MultipleTests MM("testing "+n->idName(),"class invariants");
         Environment E=Environment();
          MM.push_back(idNameInvariant(n,&E));
          MM.push_back(getToStringToObjectInvariants(n,&E));
          if (n->getEnvironment())
            {
              MM.push_back(idNameInvariant(n,n->getEnvironment()));
              MM.push_back(getToStringToObjectInvariants(n,n->getEnvironment()));


            }

          M.push_back(MM);
        }
        */
/*
      return M;

    }
  }
}



*/

#endif //MACRO_TEST

