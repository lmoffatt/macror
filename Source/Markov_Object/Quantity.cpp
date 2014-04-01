#include "Markov_Object/Quantity.h"
#include "Markov_Object/IdentifierName.h"
#include "Markov_Object/Environment.h"
#include "Markov_Object/Unit_System.h"

namespace Markov_Object {
  
  std::string Quantity::ClassName()
  {
    return "Quantity";
  }
  
  std::string Quantity::myClass() const
  {
    return ClassName();
  }
  

  
  std::set<std::string> Quantity::mySuperClasses() const
  {
    return SuperClasses();
  }
  
  std::set<std::string> Quantity::SuperClasses()
  {
    auto mySC=Abstract_Named_Object::SuperClasses();
    mySC.insert(ClassName());
    return mySC;
    
  }


  
  Quantity *Quantity::create() const
  {
    return new Quantity;
  }
  
  std::string Quantity::ToString() const
  {
    if (Abstract_Named_Object::idName().empty())
      return "";
    else
      {
        std::string o=ClassName()+" "+ Abstract_Named_Object::ToString();
        o+=def_.ToString();
        return o;
      }
  }
  
  bool Quantity::empty() const
  {
    return  Abstract_Named_Object::empty()&&def_.empty();
  }
  
  



  Quantity *Quantity::CreateObject(const std::string &text, std::size_t &cursor) const
  {
    auto tmp=create();
    auto out=tmp->ToObject(text,cursor);
    if (out==nullptr)
      delete tmp;
    return out;
  }
  
  
  
  Quantity *Quantity::ToObject(const std::string &text, std::size_t &cursor)
  {
    std::size_t cursor0=cursor;
    IdentifierName::skipSpaces(text,cursor);
    auto clsnms=ClassName().size();
    
    // it should have the classname
    if ((!text.empty())&&(text.substr(cursor,clsnms)==ClassName()))
      {
        cursor+=clsnms;
        if (Abstract_Named_Object::ToObject(text,cursor))
          {
            auto tmp=def_.CreateObject(text,cursor);
            if (tmp!=nullptr)
              {
                def_=std::move(*tmp);
                return this;
              }
          }
      }
    cursor=cursor0;
    return nullptr;
    
  }
  
  
  
  std::set<std::string> Quantity::referencedObjects() const
  {
    std::set<std::string> out;
    for (auto t:def_.value())
      {
        out.insert(Quantity::ClassName()+"::"+t.first);
      }
    return out;
  }
  
  QuantityExpression Quantity::definition() const
  {
    return def_;
  }
  
  QuantityExpression Quantity::baseDefinition(Unit_System *us) const
  {
    auto o=baseDefinition({},us);
    return o;
  }

  QuantityExpression Quantity::self() const
  {
    return QuantityExpression(getEnvironment(),{idName(),1});
  }

  


  
  

  Quantity::Quantity():
    Abstract_Named_Object(){}


  Quantity::Quantity(Environment*  e,
                     std::string quantityAbreviation,
                     QuantityExpression quatityDefinition,
                     std::string longName, std::string whatthis)
    :
      Abstract_Named_Object(e,quantityAbreviation,longName,whatthis),
      def_(quatityDefinition)
  {

  }

  Quantity::Quantity(Environment*  e,
                     std::string quantityAbreviation,
                     std::map<std::string, int> quatityDefinition,
                     std::string longName,
                     std::string whatthis)
    :
      Abstract_Named_Object(e,quantityAbreviation,longName,whatthis),
      def_(e,quatityDefinition)
  {}

  Quantity::Quantity( Environment*  e,
                      std::string quantityAbreviation,
                      std::string quatityDefinition,
                      std::string longName,
                      std::string whatthis)
    :
       Abstract_Named_Object(e,quantityAbreviation,longName,whatthis),
      def_(e,QuantityExpression::getDefinition(quatityDefinition))
  {}

  QuantityExpression Quantity::baseDefinition(std::set<std::string> upstream,
                                              Unit_System* us) const

  {
    if (us==nullptr)
      us=getEnvironment()->getUnit_System();
    upstream.insert(idName());
    QuantityExpression out;
    if (getEnvironment()!=nullptr)
      {
        for (auto t:def_.value())
          {
            std::shared_ptr<const Quantity> q=getEnvironment()->Q(t.first);
            if (q==nullptr)
              return QuantityExpression();
            else if (us->isStdQuantity(q->idName())||
                       upstream.count(q->idName())!=0)
              return self();
            else
              {
                auto defq=q->baseDefinition(upstream,us)*t.second;
                out+=defq;
              }

          }
      }
    return out;
  }


  bool Quantity::operator<( const Quantity &rh)const
  {
    return idName()<rh.idName();
  }




}



#ifdef MACRO_TEST


#include "Tests/MultipleTests.h"
#include "Tests/TESTS.h"
#include "Tests/ElementaryTest.h"
#include "Markov_IO/auxiliarIO.h"

namespace  Markov_IO {

  template std::string ToString(std::shared_ptr< const Markov_Object::Quantity> const&x);

}
/*

namespace Markov_Test
{
  namespace Markov_Object_Test
  {


    MultipleTests isreferenced(const std::set<std::shared_ptr<Quantity>>&  qs)
    {
      MultipleTests M("is-Referenced",
                      "poscondition");

      for (std::shared_ptr<Quantity> o:qs)
        {
            M.push_back(TEST_EQ("the environment returns a reference to this",
                                o->getEnvironment()->Q(o->idName())
                                ,o));
            }
      return M;

    }


    MultipleTests TestDefinition(const std::set<std::shared_ptr<Quantity>>& qs)
    {
      MultipleTests O("check invariants over definition object",
                      "test classInvariants",
      {"Quantity"},
      {"Quantity::definition()"});
      std::set<std::shared_ptr<QuantityExpression> > qe;
      for (auto q:qs)
        {
          qe.insert(std::make_shared<QuantityExpression>(q->definition()));
        }
      QuantityExpression_Test t(qe);
      O.push_back(t.classInvariant());
      return O;

    }


    MultipleTests BaseDefinitionInvariant(const std::set<std::shared_ptr<Quantity>>& qs)
    {

      MultipleTests O("test for Distributivity of baseDefinition","compare both ways");
      MultipleTests M("test for Distributivity of baseDefinition over multiplication",
                      "For all qa, qb  in A,"
                      "qa.baseDefinition+qb.baseDefinition==(qa+qb).baseDefinition",
      {"Quantity","QuantityExpression"},
      {"Quantity::baseDefinition()",
       "Quantity::definition()",
       "QuantityExpression::ToString()",
       "operator+(const QuantityExpression&,const QuantityExpression&)"});
      for (auto q:qs)
        {
          for (auto q2:qs)
            {
              if (q->getEnvironment()==q2->getEnvironment())
                {
                  Quantity qbase_q2base(q->getEnvironment(),
                                        q->idName()+"_TIMES_"+q2->idName(),
                                        q->definition()+q2->definition(),
                                        "lonname","");

                  Quantity qperq2(q->getEnvironment(),q->idName()+"PER2"+q2->idName(),
                                  q->baseDefinition()+q2->baseDefinition(),"lonname","");



                  M.push_back(TEST_EQ(q->idName()+"*"+q2->idName(),
                                      qbase_q2base.baseDefinition().ToString(),
                                      qperq2.definition().ToString() ));
                }
            }
        }


      MultipleTests D("test for Distributivity of baseDefinition over division",
                      "For all qa, qb  in A,"
                      "qa.baseDefinition+qb.baseDefinition*-1==(qa+qb*-1).baseDefinition",
      {"Quantity","QuantityExpression"},
      {"Quantity::baseDefinition()",
       "Quantity::definition()",
       "QuantityExpression::operator *=(int)",
       "QuantityExpression::ToString()",
       "operator+(const QuantityExpression&,const QuantityExpression&)"});
      for (std::shared_ptr<Quantity> q:qs)
        {
          for (std::shared_ptr<Quantity> q2:qs)
            {
              if (q->getEnvironment()==q2->getEnvironment())
                {
                  Quantity qbase_q2base(q->getEnvironment(),
                                        q->idName()+"_DIV_"+q2->idName(),
                                        q->definition()+q2->definition()*(-1),
                                        "lonname","");

                  Quantity qperq2(q->getEnvironment(),q->idName()+"_DIV_"+q2->idName(),
                                  q->baseDefinition()+q2->baseDefinition()*(-1),"lonname","");



                  D.push_back(TEST_EQ(q->idName()+"/"+q2->idName(),
                                      qbase_q2base.baseDefinition().ToString(),
                                      qperq2.definition().ToString() ));
                }
            }
        }



      O.push_back(M);
      O.push_back(D);

      return O;

    }




    MultipleTests Quantity_Test::classInvariant() const
    {
      MultipleTests M("Quantity Tests",
                      "interface invariants");

      M.push_back(Abstract_Named_Object_Test::classInvariant());
      M.push_back(BaseDefinitionInvariant(qe_));
      M.push_back(TestDefinition(qe_));



      return M;

    }


    Quantity_Test::Quantity_Test(const std::set<std::shared_ptr<Quantity >> &object):
      Abstract_Named_Object_Test(std::set<std::shared_ptr<Abstract_Named_Object>>(
                                                                                   object.begin(),object.end())),
      qe_(object){}







  }
}

*/

#endif //MACRO_TEST
