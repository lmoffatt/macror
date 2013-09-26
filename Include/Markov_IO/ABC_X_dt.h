#ifndef ABC_X_DT_H
#define ABC_X_DT_H
#include <iostream>

#include "Markov_IO/ABC_Put.h"

namespace Markov_IO
{

class ABC_X_dt:public ABC_Put
{
public:
    virtual ABC_X_dt* clone() const=0;
    ///virtual default constructors
    virtual ABC_X_dt* create() const=0;

    virtual ~ABC_X_dt();

    //    virtual size_t nsamples()const=0;
    virtual double dt()const=0;
    virtual double x(const std::string& variableName)const=0;

    virtual std::vector<std::string> getVariables()const=0;

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

class ABC_X_dt_Test:public ABC_Put_Test
{
public:

    virtual MultipleTests classInvariant()const;

    ABC_X_dt_Test(const ABC_X_dt& sample);

    virtual~ABC_X_dt_Test();

protected:
    const ABC_X_dt* measure_point;
};

}
}

#endif //MACRO_TEST




#endif // ABC_X_DT_H
