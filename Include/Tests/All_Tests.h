#ifndef ALL_TESTS_H

#define ALL_TESTS_H


#include "MultipleTests.h"

namespace Markov_Console {
  class Markov_CommandManager;

}

namespace Markov_Test
{

class All_Tests
{
public:

  virtual MultipleTests AllTests(Markov_Console::Markov_CommandManager* cm, const std::string varNameTested)=0;
 // virtual MultipleTests AllTests()=0;
  static std::string TestName();

  virtual std::string myTest()const=0;

  virtual std::string testedClass()const=0;


  virtual ~All_Tests();


};

inline std::string All_Tests::TestName(){
  return "All_Tests";}

}
#endif // ALL_TESTS_H
