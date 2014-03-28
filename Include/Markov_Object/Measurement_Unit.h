#ifndef MEASUREMENT_UNIT_H
#define MEASUREMENT_UNIT_H
#include "Markov_Object/Abstract_Named_Object.h"
#include "Markov_Object/ScaledExpression.h"

namespace Markov_Object {


  template<typename T>
  class Measurement;

  class Measurement_Unit:public Abstract_Named_Object
  {
  public:
    static
    int abbrToN(char c);
    static
    std::string nToFullName(int n);

    static char nToAbbr(int n);


    static std::string ClassName();

    static Class_info classInfo();

    static std::set<std::string> SuperClasses();



    virtual std::string myClass()const override;
    virtual Class_info myClassInfo()const override;

    /// cast an Abstract_Object to Base_Unit
    virtual Measurement_Unit * dynamicCast(Abstract_Object* o)const override;
    virtual const Measurement_Unit * dynamicCast(const Abstract_Object* o)const override;


    static
    Measurement_Unit DerivedUnit(Environment*  E,
                                 std::string idName,
                                 double scale,
                                 std::string definition,
                                 std::string fullname,
                                 std::string whatthis);



    ScaledExpression self()const;

    virtual ScaledExpression definition()const;


    virtual ScaledExpression baseDefinition()const;


    virtual bool empty()const override
    {
      return  Abstract_Named_Object::empty()&&def_.empty();

    }

    virtual TestResult test()const override
    {


    }

    ///
    /// \brief ToString
    /// \return
    ///
    ///
    ///

    virtual std::string ToString()const override;

    virtual Measurement_Unit *
    CreateObject(const std::string &text, std::size_t &cursor) const override;


    virtual Measurement_Unit* create()const override;

    virtual std::set<std::string> referencedObjects()const override;


    virtual std::shared_ptr<const Quantity> getQuantity()const;

    virtual QuantityExpression getQuantityDefinition()const;

    Measurement_Unit operator /(const Measurement_Unit &rh) const;
    Measurement_Unit operator *(const Measurement_Unit &rh) const;

    Measurement_Unit pow(int n)const;

    bool operator<(const Measurement_Unit& rh)const;





    Measurement_Unit();



    Measurement_Unit(Environment*  E,
                     std::string idName,
                     ScaledExpression definition,
                     QuantityExpression qdefinition,
                     std::string fullname,
                     std::string whatthis);

    Measurement_Unit(Environment*  E,
                     std::string idName,
                     double scale,
                     std::string definition,
                     std::string qdefinition,
                     std::string fullname,
                     std::string whatthis);


    Measurement_Unit( Environment*  e);

  protected:
    virtual Measurement_Unit *
    ToObject(const std::string& multipleLines,std::size_t& pos) override;


  private:
    QuantityExpression qdef_;
    ScaledExpression def_;

    ScaledExpression baseDefinition(std::set<std::string> upstream) const;
  };








}








#ifdef MACRO_TEST

#include "Tests/MultipleTests.h"
namespace Markov_Test
{
  namespace Markov_Object_Test
  {

    using namespace Markov_Object;



    class Measurement_Unit_Test:public Abstract_Named_Object_Test
    {
    public:

      virtual MultipleTests classInvariant()const;

      Measurement_Unit_Test(const std::set<std::shared_ptr<Measurement_Unit >> &object);

      virtual~Measurement_Unit_Test(){}
      static std::string TestName()
      {
        return "Measurement_Unit_Test";
      }

      virtual std::string myTest()const
      {
        return TestName();
      }


    protected:
      std::set<std::shared_ptr< Measurement_Unit>> mue_;
    };





  }
}

#endif //MACRO_TEST




#endif // MEASUREMENT_UNIT_H
