#include "Markov_Object/Quantity.h"


namespace Markov_Object {
  
  std::string Quantity::ClassName()
  {
    return "Quantity";
  }
  
  std::string Quantity::myClass() const
  {
    return ClassName();
  }
  
  Class_info Quantity::classInfo()
  {
    return {
        ClassName(),
            SuperClasses(),
            true,
            true,
            false
      };
  }
  
  Class_info Quantity::myClassInfo() const
  {
    return classInfo();
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
  
  
  /// if the definition is valid and the definition is empty is valid
  bool Quantity::invalid() const
  {
    return Abstract_Named_Object::invalid()||
        (Abstract_Named_Object::empty()&&(!def_.empty()));
  }
  
  
  
  bool Quantity::ToObject(const std::string &text, std::size_t &cursor)
  {
    std::size_t cursor0=cursor;
    Abstract_Named_Object::skipSpaces(text,cursor);
    auto clsnms=ClassName().size();
    
    // it should have the classname
    if ((!text.empty())&&(text.substr(cursor,clsnms)==ClassName()))
      {
        cursor+=clsnms;
        if (Abstract_Named_Object::ToObject(text,cursor))
          {
            if (def_.ToObject(text,cursor))
              return true;
          }
      }
    cursor=cursor0;
    return false;
    
  }
  
  
  
  std::set<std::string> Quantity::referencedObjects() const
  {
    std::set<std::string> out;
    for (auto t:def_.value())
      {
        out.insert(t.first);
      }
    return out;
  }
  
  QuantityExpression Quantity::definition() const
  {
    return def_;
  }
  
  QuantityExpression Quantity::baseDefinition() const
  {
    auto o=baseDefinition({});
    return o;
  }
  
  QuantityExpression Quantity::self() const
  {
    return QuantityExpression({{idName(),1}});
  }
  
  
  
  Quantity::Quantity():
    Abstract_Object(),
    Abstract_Named_Object(){}
  
  Quantity::Quantity(Environment *e):
    Abstract_Object(),
    Abstract_Named_Object(e){}

  Quantity::Quantity(Environment *e,
                     std::string quantityAbreviation,
                     QuantityExpression quatityDefinition,
                     std::string longName, std::string whatthis)
 :
    Abstract_Object(),
    Abstract_Named_Object(e,quantityAbreviation,longName,whatthis),
    def_(quatityDefinition)
  {

  }
  
  Quantity::Quantity(Environment *e,
                     std::string quantityAbreviation,
                     std::map<std::string, int> quatityDefinition,
                     std::string longName,
                     std::string whatthis)
    :
      Abstract_Object(),
      Abstract_Named_Object(e,quantityAbreviation,longName,whatthis),
      def_(quatityDefinition)
  {}
  
  Quantity::Quantity(Environment *e,
                     std::string quantityAbreviation,
                     std::string quatityDefinition,
                     std::string longName,
                     std::string whatthis)
    :
      Abstract_Object(),
      Abstract_Named_Object(e,quantityAbreviation,longName,whatthis),
      def_(QuantityExpression::getDefinition(quatityDefinition))
  {}
  
  QuantityExpression Quantity::baseDefinition(std::set<std::string> upstream) const
  {
    upstream.insert(idName());
    QuantityExpression out;
    if (getEnvironment()!=nullptr)
      {
        for (auto t:def_.value())
          {
            std::shared_ptr<Quantity> q=getEnvironment()->Q(t.first);
            if (q==nullptr)
              return QuantityExpression();
            else if (upstream.count(q->idName())!=0)
              return self();
            else
              {
                auto defq=q->baseDefinition(upstream)*t.second;
                out+=defq;
              }
            
          }
      }
    return out;
  }
  
  
  
}



#ifdef MACRO_TEST


#include "Tests/MultipleTests.h"
#include "Tests/TESTS.h"
#include "Tests/ElementaryTest.h"

namespace Markov_Test
{
  namespace Markov_Object_Test
  {
    
    MultipleTests BaseDefinitionInvariant(const std::set<std::shared_ptr<Quantity>>& qs)
    {
      

      MultipleTests M("test for Distributivity of baseDefinition over multiplication",
                            "For all qa, qb  in A,"
                            "qa.baseDefinition+qb.baseDefinition==(qa+qb).baseDefinition");
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
                            "qa.baseDefinition+qb.baseDefinition*-1==(qa+qb*-1).baseDefinition");
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



                  M.push_back(TEST_EQ(q->idName()+"/"+q2->idName(),
                                                  qbase_q2base.baseDefinition().ToString(),
                                                  qperq2.definition().ToString() ));
                }
            }
        }

      


      
      return M;
      
    }
    
    
    
    
    MultipleTests Quantity_Test::classInvariant() const
    {
      MultipleTests M("Quantity Tests",
                      "interface invariants");
      
      M.push_back(Abstract_Named_Object_Test::classInvariant());
      M.push_back(BaseDefinitionInvariant(qe_));
      
      return M;
      
    }
    
    
    Quantity_Test::Quantity_Test(const std::set<std::shared_ptr<Quantity >> &object):
      Abstract_Named_Object_Test(std::set<std::shared_ptr<Abstract_Named_Object>>(
                                   object.begin(),object.end())),
      qe_(object){}
    
    
    
    
    
    
    
  }
}

#endif //MACRO_TEST

