#ifndef ABC_MEASURESTEP_H
#define ABC_MEASURESTEP_H
#include <cstddef> //size_t
#include <iostream>

#include "Markov_IO/ABC_MeasurePoint.h"
namespace Markov_IO
{

class ABC_measure_step: public ABC_measure_point
{
public:
    virtual ABC_measure_step* clone() const=0;
    ///virtual default constructors
    virtual ABC_measure_step* create() const=0;
    virtual ~ABC_measure_step();
//    virtual size_t nsamples()const=0;
    virtual double dt()const=0;
    virtual double x()const=0;
    virtual double y()const=0;

    virtual std::size_t num_steps()const=0;
    virtual const ABC_measure_point&  sub_step(std::size_t i)const=0;

  std::ostream& printSelf(std::ostream& s)const;
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

class ABC_measure_step_Test:public ABC_measure_point_Test
{
public:

    virtual MultipleTests classInvariant()const;

    ABC_measure_step_Test(const ABC_measure_step& sample);

    virtual~ABC_measure_step_Test();

protected:
    const ABC_measure_step* step_;
};

}
}

#endif //MACRO_TEST






#endif // ABC_MEASURESTEP_H
