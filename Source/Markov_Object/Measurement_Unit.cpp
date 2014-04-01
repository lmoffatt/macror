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






  std::set<std::string> Measurement_Unit::mySuperClasses() const
  {
    return SuperClasses();
  }




  Measurement_Unit Measurement_Unit::DerivedUnit(Environment *E,
                                                 std::string idName,
                                                 double scale,
                                                 std::string definition,
                                                 std::string fullname,
                                                 std::string whatthis)
  {
    ScaledExpression sc(E,scale,definition);
    QuantityExpression q;
    return Measurement_Unit(E,idName,sc,q,fullname,whatthis);
}


  ScaledExpression Measurement_Unit::self() const
  {
    return ScaledExpression(getEnvironment(),1.0,QuantityExpression(getEnvironment(),{idName(),1}));
  }

  ScaledExpression Measurement_Unit::definition() const
  {
    return def_;
  }

  ScaledExpression Measurement_Unit::baseDefinition() const
  {
    return baseDefinition({});
  }
  
  bool Measurement_Unit::empty() const
  {
    return  Abstract_Named_Object::empty()&&def_.empty();
    
  }
  
  
  Measurement_Unit* Measurement_Unit::create()const
  {
    return new Measurement_Unit;
  }
  
  std::set<std::string> Measurement_Unit::referencedObjects() const
  {
    std::set<std::string> out;
    for (auto t:def_.value())
      {
        out.insert(Measurement_Unit::ClassName()+"::"+t.first);
      }
    return out;
  }



  std::shared_ptr<const Quantity> Measurement_Unit::getQuantity() const
  {
    return getEnvironment()->Qd(qdef_);
  }

  QuantityExpression Measurement_Unit::getQuantityDefinition() const
  {
    return qdef_;
  }

 
  bool Measurement_Unit::operator<(const Measurement_Unit &rh) const
  {
    return idName()<rh.idName();
  }


  Measurement_Unit::Measurement_Unit():
    Abstract_Named_Object(),
    qdef_{},
    def_{}{}
  

  

  std::string Measurement_Unit::ToString()const
  {
    if (!empty())
      {
        std::string out=Abstract_Named_Object::ToString();
        out+=definition().ToString()+"\n";
        out+=getQuantityDefinition().ToString()+"\n";

        return out;
      }
    else
      {
        return "";
      }
  }

  Measurement_Unit *Measurement_Unit:: CreateObject(const std::string &text, std::size_t &cursor) const
  {
    auto tmp=create();
    auto out=tmp->ToObject(text,cursor);
    if (out==nullptr)
      delete tmp;
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
    auto d=def_.CreateObject(multipleLines,pos);
    if (d==nullptr)
      {
        pos=pos0;
        return nullptr;
      }
    def_=*d;
    delete d;
    auto q=qdef_.CreateObject(multipleLines,pos);
    if (q==nullptr)
      {
        pos=pos0;
        return nullptr;
      }
    qdef_=*q;
    delete q;
    return this;

  }

  ScaledExpression Measurement_Unit::baseDefinition(std::set<std::string> upstream) const
  {    upstream.insert(idName());
       ScaledExpression out;
          int n0=0,n=0;

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
                                     ScaledExpression definition,
                                     QuantityExpression qdefinition,
                                     std::string fullname,
                                     std::string whatthis)
    :
      Abstract_Named_Object(E,idName,fullname,whatthis),
      qdef_(qdefinition),
      def_(definition)
  {}

  Measurement_Unit::Measurement_Unit(Environment *E,
                                     std::string idName,
                                     double scale,
                                     std::string definition,
                                     std::string qdefinition,
                                     std::string fullname,
                                     std::string whatthis)
    :
      Abstract_Named_Object(E,idName,fullname,whatthis),
      qdef_{E,qdefinition},
      def_{E,scale,definition}
  {}


}





#ifdef MACRO_TEST


#include "Tests/MultipleTests.h"
#include "Tests/TESTS.h"
#include "Tests/ElementaryTest.h"
#include "Markov_IO/auxiliarIO.h"


/*

namespace Markov_Test
{
  namespace Markov_Object_Test
  {


    MultipleTests isreferenced(const std::set<std::shared_ptr<Measurement_Unit>>&  qs)
    {
      MultipleTests M("is-Referenced",
                      "poscondition");

      for (std::shared_ptr<Measurement_Unit> o:qs)
        {
            M.push_back(TEST_EQ("the environment returns a reference to this",
                                o->getEnvironment()->U(o->idName())
                                ,o));
      M.push_back(TEST_NEQ("the environment returns not a reference to this",
                                 o->getEnvironment()->U(o->idName())
                                 ,o));
        }
      return M;

    }


    MultipleTests TestDefinition(const std::set<std::shared_ptr<Measurement_Unit>>& qs)
    {
      MultipleTests O("check invariants over definition object",
                      "test classInvariants",
      {"Quantity"},
      {"Quantity::definition()"});
      std::set<std::shared_ptr<ScaledExpression> > qe;
      for (std::shared_ptr<Measurement_Unit> q:qs)
        {
          qe.insert(std::make_shared<ScaledExpression>(q->definition()));
        }
      ScaledExpression_Test t(qe);
      O.push_back(t.classInvariant());
      return O;

    }


    MultipleTests BaseDefinitionInvariant(const std::set<std::shared_ptr<Measurement_Unit>>& qs)
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
                  Measurement_Unit qbase_q2base(q->getEnvironment(),
                                                q->idName()+"_TIMES_"+q2->idName(),
                                                q->definition()+q2->definition(),
                                                q->getQuantityDefinition()+q2->getQuantityDefinition(),
                                                "lonname","");

                      }
            }
        }


      MultipleTests D("test for Distributivity of baseDefinition over division",
                      "For all qa, qb  in A,"
                      "qa.baseDefinition+qb.baseDefinition*-1==(qa+qb*-1).baseDefinition",
      {"Measurement_Unit","ScaledExpression"},
      {"Measurement_Unit::baseDefinition()",
       "Measurement_Unit::definition()",
       "ScaledExpression::operator *=(int)",
       "ScaledExpression::ToString()",
       "operator+(const QuantityExpression&,const QuantityExpression&)"});
      for (std::shared_ptr<Measurement_Unit> q:qs)
        {
          for (std::shared_ptr<Measurement_Unit> q2:qs)
            {
              if (q->getEnvironment()==q2->getEnvironment())
                {
                  Measurement_Unit qbase_q2base(q->getEnvironment(),
                                                q->idName()+"_DIV_"+q2->idName(),
                                                q->definition()+q2->definition()*(-1),
                                                q->getQuantityDefinition()+q2->getQuantityDefinition()*(-1),
                                                "lonname","");




                 }
            }
        }



      O.push_back(M);
      O.push_back(D);

      return O;

    }




    MultipleTests Measurement_Unit_Test::classInvariant() const
    {
      MultipleTests M("Quantity Tests",
                      "interface invariants");

      M.push_back(Abstract_Named_Object_Test::classInvariant());
      M.push_back(BaseDefinitionInvariant(mue_));
      M.push_back(TestDefinition(mue_));



      return M;

    }


    Measurement_Unit_Test::Measurement_Unit_Test(const std::set<std::shared_ptr<Measurement_Unit >> &object):
      Abstract_Named_Object_Test(
        std::set<std::shared_ptr<Abstract_Named_Object>>(object.begin(),object.end())),
      mue_(object){}







  }
}

*/
#endif //MACRO_TEST
