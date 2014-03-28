#ifndef SCALEDEXPRESSION_H
#define SCALEDEXPRESSION_H


#include <cmath>
#include "Markov_Object/QuantityExpression.h"

namespace Markov_Object {



  class ScaledExpression: public Abstract_Object
  {
    // Abstract_Object interface
  public:
    static  std::string ClassName();
    static
    std::set<std::string> SuperClasses();


    ScaledExpression dimensionless();


    //overrides

    virtual std::set<std::string> mySuperClasses() const override;
    virtual std::string myClass() const override;

    virtual bool empty() const override;
    virtual ScaledExpression *create() const override;
    virtual std::string ToString() const override;

    virtual std::set<std::string> referencedObjects() const override;




    virtual ScaledExpression *
    CreateObject(const std::string &text, std::size_t &cursor) const override;


    //new methods

    virtual double scale()const;

    virtual void setScale(double newScale);

    // regular methods
    // new methods non virtual
    ScaledExpression &operator+=(const ScaledExpression& other);

    ScaledExpression& operator*=(int n);

    bool operator<(const ScaledExpression& other)const;

    virtual std::map<std::string, int> value() const;



    // constructors and destructors
    ScaledExpression();

    ScaledExpression(Environment *E);



    ScaledExpression(double scale,
                     QuantityExpression def);

    ScaledExpression(Environment *E,
                     double scale,
                     std::string def);


    ~ScaledExpression();


    ScaledExpression(const ScaledExpression& other);




    ScaledExpression baseDefinition() const;

    QuantityExpression QuantityDefinition()const;
  protected:
    virtual ScaledExpression *ToObject(const std::string &text, std::size_t &cursor) override;


  private:
    QuantityExpression ex_;
    double scale_;
  };


  ScaledExpression operator*(const ScaledExpression &one, int n);

  ScaledExpression operator+(const ScaledExpression &one, const ScaledExpression &other);

}



#ifdef MACRO_TEST


#include "Tests/MultipleTests.h"
namespace Markov_Test
{
  namespace Markov_Object_Test
  {

    using namespace Markov_Object;



    class ScaledExpression_Test:public QuantityExpression_Test
    {
    public:

      virtual MultipleTests classInvariant()const;

      ScaledExpression_Test(const std::set<std::shared_ptr<ScaledExpression>>& object);

      virtual~ScaledExpression_Test(){}
      static std::string TestName()
      {
        return "ScaledExpression_Test";
      }

      virtual std::string myTest()const
      {
        return TestName();
      }


    protected:
      std::set<std::shared_ptr<ScaledExpression> > se_;
    };





  }
}

#endif //MACRO_TEST






#endif // SCALEDEXPRESSION_H
