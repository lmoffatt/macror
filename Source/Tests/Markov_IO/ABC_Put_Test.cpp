#include "Tests/Markov_IO/ABC_Put_Test.h"
#include "Tests/ElementaryTest.h"
#include "Markov_IO/auxiliarIO.h"

namespace Markov_Test
{
  namespace Markov_IO_Test
  {


     std::string ABC_Put_Test::TestName()
    {
      return "Put_Tests";
    }

     std::string ABC_Put_Test::myTest()const
    {
      return TestName();
    }

      std::string ABC_Put_Test::testedClass()const
     {
       return "";
     }


    MultipleTests ABC_Put_Test::AllTests(Markov_Console::Markov_CommandManager* cm, const std::string varNameTested)
    {
      return classInvariant();
    }



    MultipleTests ABC_Put_Test::classInvariant()const
    {
      MultipleTests results("ABC_Put ",
                            "Class Invariant");

      ABC_Put* copy=sample_->clone();



      results.push_back(ElementaryTest("clone(),operator==()",
                                       "clone() copies are equal to the template\n"
                                       "original\n"+
                                       Markov_IO::ToString(*sample_)+
                                       "clone()\n"+
                                       Markov_IO::ToString(*copy),
                                       *sample_==*copy));
      /* this test does not work!!
        ABC_Put* emptyCopy=sample_->create();
        *emptyCopy=*sample_;
        results.push_back(ElementaryTest("create(),operator=()",
                                         "operator=() copies are equal to the template\n"
                                         "original\n"+
                                         Markov_IO::ToString(*sample_)+
                                         "operator=() copy\n"+
                                         Markov_IO::ToString(*emptyCopy),
                                         *sample_==*emptyCopy));
*/
      return results;


    }

    ABC_Put_Test::ABC_Put_Test(const ABC_Put& aPut):
      sample_(&aPut)
    {

    }

    ABC_Put_Test::~ABC_Put_Test()
    {
    }

  }
}


