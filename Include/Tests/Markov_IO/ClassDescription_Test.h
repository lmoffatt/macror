#ifndef CLASSDESCRIPTION_TEST_H
#define CLASSDESCRIPTION_TEST_H
#include "Markov_IO/ClassDescription.h"

#include "Tests/MultipleTests.h"
#include "Tests/Markov_IO/ABC_Put_Test.h"
namespace Markov_Test
{
namespace Markov_IO_Test
{

using namespace Markov_IO;

class ClassDescription_Test:public ABC_Put_Test
{
public:

    virtual MultipleTests classInvariant()const;
  virtual std::string testedClass()const;

    ClassDescription_Test(const ClassDescription& sample);

    virtual~ClassDescription_Test();

    static std::string TestName();

    virtual std::string myTest()const;


private:
    const ClassDescription* classDes_;
};

}
}



#endif // CLASSDESCRIPTION_TEST_H
