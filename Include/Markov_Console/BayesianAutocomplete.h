#ifndef BAYESIANAUTOCOMPLETE_H
#define BAYESIANAUTOCOMPLETE_H

#include "Markov_Console/Autocomplete.h"

namespace  Markov_Console {


/*!
   *Class support for bayesian autocompletion.

   @invariant it holds a list of possible strings with their updated frequency

   @invariant it can add more items through a push_back method

   @invariant it offers the method complete to provide a vector with strings whose
              first characters match the provided sample. The vector is ordered by the
              posterior probability of the items.

    @invariant it offers a function to incorporate the information that a particular item has been chosen.


 */


class BayesAutocomplete
{
public:

  std::vector<std::string> complete(std::string hint) const;

  void chosenOne(std::string item);


  void push_back(std::string newItem, double likelihood);
private:
  std::map<std::string, double >  items;

};

}



#ifdef MACRO_TEST


#include "Tests/MultipleTests.h"
#include "Tests/Markov_IO/ABC_Put_Test.h"
namespace Markov_Test
{
namespace Markov_MacroConsele_Test
{

using namespace Markov_Console;



class BayesAutocomplete_Test: public All_Tests
{
public:
  virtual MultipleTests AllTests(Markov_Console::Markov_CommandManager*, const std::string);
  virtual std::string testedClass()const;

    virtual MultipleTests classInvariant()const;
  virtual ~BayesAutocomplete_Test(){}
  static std::string TestName();
  virtual std::string myTest()const;

};

}
}

#endif //MACRO_TEST




#endif // BAYESIANAUTOCOMPLETE_H
