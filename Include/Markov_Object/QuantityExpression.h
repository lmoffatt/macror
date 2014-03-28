#ifndef QUANTITYEXPRESSION_H
#define QUANTITYEXPRESSION_H

#include <cstring>
#include "Markov_Object/Abstract_Named_Object.h"

namespace Markov_Object {
  class Quantity;

  class QuantityExpression: public  Abstract_Object
  {
  public:
    static const char pow='^';
    static  const char mult='*';
    static  const char div='/';
   // static  const char lb='(';
   // static  const char rb=')';



    static constexpr const char* allowed="abcdefghijklmopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static constexpr const char* numeric="1234567890+-";

    static  std::string legal();

    static constexpr const char* separator=" \t\n";

    static    std::string getName(const std::string text, std::size_t &cursor);
    static    std::string getName(const std::string text);

    static
    std::map<std::string,int> getDefinition(const std::string& defs,std::size_t& cursor);


    static
    std::map<std::string,int> getDefinition(const std::string& defs);



    static std::string ClassName();

    static std::set<std::string> SuperClasses();

    QuantityExpression dimensionless();


    QuantityExpression& removeUnitTerms();

    // new methods non virtual
    QuantityExpression &operator+=(const QuantityExpression& other);
    QuantityExpression& operator*=(int n);

    bool operator<(const QuantityExpression& other)const;


    // Abstract_Object interface
    virtual std::set<std::string> mySuperClasses() const override;
    virtual std::string myClass() const override;

    virtual bool empty() const override;


    virtual QuantityExpression *create() const override;

    virtual std::string ToString() const override;

    virtual QuantityExpression*
    CreateObject(const std::string &text, std::size_t &cursor) const override;



    QuantityExpression(std::map<std::string,int> expression);
    QuantityExpression(std::string exp);


    QuantityExpression();

    virtual std::map<std::string, int> value()const;

   protected:
    virtual QuantityExpression*
    ToObject(const std::string &text, std::size_t &cursor)  override;


  private:
    std::map<std::string, int> expr_;


  };

  QuantityExpression operator*(const QuantityExpression& one,int n);


  QuantityExpression operator+(const QuantityExpression& one,const QuantityExpression& other);

}





#ifdef MACRO_TEST


#include "Tests/MultipleTests.h"

/*
namespace Markov_Test
{
  namespace Markov_Object_Test
  {

    using namespace Markov_Object;



    class QuantityExpression_Test:public Abstract_Object_Test
    {
    public:

      virtual MultipleTests classInvariant()const;

      QuantityExpression_Test(const std::set<std::shared_ptr<QuantityExpression>>& object);

      virtual~QuantityExpression_Test(){}
      static std::string TestName()
      {
        return "QuantityExpression_Test";
      }

      virtual std::string myTest()const
      {
        return TestName();
      }


    protected:
      std::set<std::shared_ptr<QuantityExpression> > qe_;
    };





  }
}


*/
#endif //MACRO_TEST





#endif // QUANTITYEXPRESSION_H
