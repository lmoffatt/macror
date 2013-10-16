#include "Markov_IO/ABC_MeasurePoint.h"

namespace Markov_IO
{

 ABC_measure_point::~ABC_measure_point() {}

 std::ostream& ABC_measure_point::put(std::ostream& s) const
{
    s<<dt()<<"  "<<x()<<"  "<<y()<<"\n";
    return s;
}

}



#ifdef MACRO_TEST



#include "Tests/ElementaryTest.h"
#include "Tests/Markov_IO/ClassDescription_Test.h"


namespace Markov_Test
{
namespace Markov_IO_Test
{

   std::string ABC_measure_point_Test::testedClass()const
  {
    return "";
  }


  std::string ABC_measure_point_Test::TestName()
  {
    return "measure_point_Test";
  }

   std::string ABC_measure_point_Test::myTest()const
  {
    return TestName();
  }


MultipleTests ABC_measure_point_Test::classInvariant()const
{
    MultipleTests results("ABC_measure_point ",
                          "Class Invariant");

    results.push_back(ABC_Put_Test::classInvariant());


    results.push_back(ElementaryTest("dt()",
                                 "positive",
                                 measure_point->dt()>0.0));
   results.push_back(ElementaryTest("x()",
                                     "positive",
                                     measure_point->x()>0.0));

    return results;
}

ABC_measure_point_Test::ABC_measure_point_Test(const ABC_measure_point& sample):
    ABC_Put_Test(sample),
    measure_point(dynamic_cast<const ABC_measure_point*>(sample_))
{

}

ABC_measure_point_Test::~ABC_measure_point_Test()
{

}

}
}


#endif //MACRO_TEST

