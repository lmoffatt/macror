#ifndef QUANTITY_H
#define QUANTITY_H
//#include <cstring>
#include "Macror_Var/Implement_Named_Object.h"
#include "Macror_Var/Implement_Refer_Environment.h"

#include "Macror_Var/ExpressionProduct.h"

namespace Macror_Var {
  class Unit_System;

  class Quantity: public Implement_Named_Object
  {
  public:
      // static methods

    static constexpr char* allowed="abcdefghijklmopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";


    static std::string ClassName();

    static std::set<std::string> SuperClasses();


    // virtual methods
    virtual std::string myClass()const override;
    virtual std::set<std::string> mySuperClasses()const override;
    virtual Quantity *create() const override;
    virtual std::string ToString() const override;
    virtual bool empty() const override;


    virtual Quantity* CreateObject(const std::string &text, std::size_t &cursor)const  override;

    /// checks for the existance of all refered objects
    std::set<std::string> referencedObjects() const override;

  // nested classes

    class Expression: public Implement_Refer_Environment,
        private ExpressionProduct
    {
    public:


      static std::string ClassName();

      static std::set<std::string> SuperClasses();



      // Abstract_Object interface
      virtual std::set<std::string> mySuperClasses() const override;
      virtual std::string myClass() const override;

      virtual bool empty() const override;
      virtual std::string ToString() const override;


      virtual Expression *create() const override;


      virtual Expression*
      CreateObject(const std::string &text, std::size_t &cursor) const override;

      // new methods non virtual

      Expression dimensionless();


      Expression& removeUnitTerms();


      std::map<std::string, int>& value();

      const std::map<std::string, int>& value()const;

      Expression &operator+=(const Expression& other);

      Expression& operator*=(int n);

      bool operator<(const Expression& other)const;

      Expression(Environment* e,std::map<std::string,int> expression);
      Expression(Environment* e,std::string exp);


      Expression(const Expression& E);


      Expression();


     protected:
      virtual Expression*
      ToObject(const std::string &text, std::size_t &cursor)  override;
      friend class Quantity;




       };

    virtual Environment* getEnvironment()const
    {
      return def_.getEnvironment();
    }


    // new methods


    Expression definition()const;
    Expression baseDefinition(Unit_System* us=nullptr)const;

    Expression self()const;


    bool operator<(const Quantity& rh)const;



    Quantity();

    Quantity( Environment*  e);


    Quantity(Expression quatityDefinition,
             std::string quantityAbreviation,
                          std::string longName,
             std::string whatthis);

    Quantity(Environment*  e,
             std::string magnitudeAbbreviation,
             std::map<std::string, int> quatityDefinition,
             std::string longName,
             std::string whatthis);

    Quantity(Environment*  e,
             std::string magnitudeAbbreviation,
             std::string quatityDefinition,
             std::string longName,
             std::string whatthis);




  protected:
    virtual Quantity*
    ToObject(const std::string &text, std::size_t &cursor)  override;

    virtual void setEnvironment(Environment* E);

  private:
    Expression baseDefinition(std::set<std::string> upstream,
                                      Unit_System *us=nullptr) const;

    Expression def_;

  };



  class Quantity_Expression: public Quantity::Expression
  {
  public:
   Quantity_Expression(const Quantity::Expression& one):
                      Quantity::Expression(one){}
  };


inline
  Quantity::Expression operator*(const Quantity::Expression& one,int n)
  {
    Quantity::Expression out(one);
    out*=n;
    return out;
  }

inline
  Quantity::Expression operator+(const Quantity::Expression& one,const Quantity::Expression& other)
{
  Quantity::Expression out(one);
  out+=other;
  return out;
}





}


#ifdef MACRO_TEST

namespace  Markov_IO {



}

#include "Tests/MultipleTests.h"
/*
namespace Markov_Test
{
  namespace Macror_Var_Test
  {

    using namespace Macror_Var;



    class Quantity_Test:public Abstract_Named_Object_Test
    {
    public:

      virtual MultipleTests classInvariant()const;

      Quantity_Test(const std::set<std::shared_ptr<Quantity >> &object);

      virtual~Quantity_Test(){}
      static std::string TestName()
      {
        return "Quantity_Test";
      }

      virtual std::string myTest()const
      {
        return TestName();
      }


    protected:
      std::set<std::shared_ptr< Quantity>> qe_;
    };





  }
}
*/
#endif //MACRO_TEST






#endif // QUANTITY_H
