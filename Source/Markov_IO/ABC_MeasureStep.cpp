#include "Markov_IO/ABC_MeasureStep.h"

namespace Markov_IO
{

ABC_measure_step::~ABC_measure_step() {}

std::ostream& ABC_measure_step::put(std::ostream& s) const
{
  return printSelf(s);
  }

std::ostream& ABC_measure_step::printSelf(std::ostream& s)const
{
  for (std::size_t i=0; i<num_steps(); i++)
  {
      s<<"("<<i<<")"<<sub_step(i).dt()<<"  "<<x()<<"  "<<y()<<"\t";
  };
  s<<"\n";
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

  std::string ABC_measure_step_Test::TestName()
  {
    return "measure_step_Test";
  }

   std::string ABC_measure_step_Test::myTest()const
  {
    return TestName();
  }
    std::string ABC_measure_step_Test::testedClass()const
   {
      return "";
   }



MultipleTests ABC_measure_step_Test::classInvariant()const
{
    MultipleTests results("ABC_measure_step ",
                          "Class Invariant");

    results.push_back(ABC_measure_point_Test::classInvariant());

    MultipleTests pSteps("num_steps() and sub_step()",
                         "invariants");




    return results;
}

ABC_measure_step_Test::ABC_measure_step_Test(const ABC_measure_step& sample):
    ABC_measure_point_Test(sample),
    step_(dynamic_cast<const ABC_measure_step*>(sample_))
{

}

ABC_measure_step_Test::~ABC_measure_step_Test()
{

}

}
}


#endif //MACRO_TEST

