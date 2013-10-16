#ifndef ABC_MEASUREPOINT_H
#define ABC_MEASUREPOINT_H

#include <iostream>

#include "Markov_IO/ABC_Put.h"

namespace Markov_IO
{

class ABC_measure_point:public ABC_Put
{
public:
    virtual ABC_measure_point* clone() const=0;
    ///virtual default constructors
    virtual ABC_measure_point* create() const=0;

    virtual ~ABC_measure_point();

    //    virtual size_t nsamples()const=0;
    virtual double dt()const=0;
    virtual double x()const=0;
    virtual double y()const=0;
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

class ABC_measure_point_Test:public ABC_Put_Test
{
public:

    virtual MultipleTests classInvariant()const;
  virtual std::string testedClass()const;

    ABC_measure_point_Test(const ABC_measure_point& sample);
    static std::string TestName();
    virtual std::string myTest()const;

    virtual~ABC_measure_point_Test();

protected:
    const ABC_measure_point* measure_point;
};

}
}

#endif //MACRO_TEST



#endif // ABC_MEASUREPOINT_H
