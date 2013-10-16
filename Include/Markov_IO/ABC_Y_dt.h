#ifndef ABC_Y_DT_H
#define ABC_Y_DT_H
namespace Markov_IO
{

class ABC_Y_dt:public ABC_Put
{
public:
    virtual ABC_Y_dt* clone() const=0;
    ///virtual default constructors
    virtual ABC_Y_dt* create() const=0;

    virtual ~ABC_Y_dt();

    //    virtual size_t nsamples()const=0;
    virtual double dt()const=0;
    virtual double y(const std::string& measuredVarName)const=0;

    virtual std::vector<std::string> measVariables()const=0;

    virtual std::ostream& put(std::ostream& s) const;

};
}

#ifdef MACRO_TEST


#include "Tests/MultipleTests.h"
#include "Tests/Markov_IO/ABC_Put_Test.h"
namespace Markov_Test
{
namespace Markov_IO_Test
{

using namespace Markov_IO;

class ABC_Y_dt_Test:public ABC_Put_Test
{
public:

    virtual MultipleTests classInvariant()const;
  virtual std::string testedClass()const;

    ABC_Y_dt_Test(const ABC_Y_dt& sample);
    static std::string TestName();
    virtual std::string myTest()const;

    virtual~ABC_Y_dt_Test();

protected:
    const ABC_Y_dt* measure_point;
};

}
}

#endif //MACRO_TEST



#endif // ABC_Y_DT_H
