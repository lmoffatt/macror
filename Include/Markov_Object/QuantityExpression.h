#ifndef QUANTITYEXPRESSION_H
#define QUANTITYEXPRESSION_H

#include <cstring>
#include "Markov_Object/Abstract_Named_Object.h"
#include "Markov_Object/Environment.h"

namespace Markov_Object {
  class Quantity;


  class QuantityExpression: public virtual Abstract_Object
  {
  public:
    static const char pow='^';
    static  const char mult='*';
    static constexpr const char* allowed="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static constexpr const char* numeric="1234567890+-";

    static  std::string legal();

    static constexpr const char* separator=" \t\n";

    static
    std::map<std::string,int> getDefinition(const std::string& defs,std::size_t& cursor);


    static
    std::map<std::string,int> getDefinition(const std::string& defs);



    QuantityExpression &operator+=(const QuantityExpression& other);
    QuantityExpression& operator*=(int n);

    static
    QuantityExpression dimensionless();

    bool operator<(const QuantityExpression& other);

    //static

    static std::string ClassName();

    static Class_info classInfo();


    static std::set<std::string> SuperClasses();



    // Abstract_Object interface
    virtual Class_info myClassInfo() const override;
    virtual std::string myClass() const override;

    virtual bool empty() const override;

    virtual bool isValid() const override;
    virtual QuantityExpression *create() const override;
    virtual QuantityExpression *dynamicCast(Abstract_Object *o) const override;
    virtual const QuantityExpression *dynamicCast(const Abstract_Object *o) const override;

    virtual std::string ToString() const override;

    virtual bool ToObject(const std::string &text, std::size_t &cursor) override;
    virtual bool ToObject(const std::string &text) override;

    QuantityExpression(std::map<std::string,int> expression);


    QuantityExpression();

    virtual std::map<std::string, int> value()const;

  private:
    std::map<std::string, int> expr_;


  };

  QuantityExpression operator*(const QuantityExpression& one,int n);


  QuantityExpression operator+(const QuantityExpression& one,const QuantityExpression& other);
}





#ifdef MACRO_TEST


#include "Tests/MultipleTests.h"
namespace Markov_Test
{
  namespace Markov_Object_Test
  {

    using namespace Markov_Object;



    class QuantityExpression_Test:public Abstract_Object_Test
    {
    public:

      virtual MultipleTests classInvariant()const;

      QuantityExpression_Test(const std::set<const QuantityExpression*>& object);

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
      std::set<const QuantityExpression*> qe_;
    };





  }
}

#endif //MACRO_TEST





#endif // QUANTITYEXPRESSION_H
