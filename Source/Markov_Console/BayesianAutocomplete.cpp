#include "Include/Markov_Console/BayesianAutocomplete.h"

namespace Markov_Console {






/*!
 * \brief BayesAutocomplete::complete returns the list of matches ordered by their likelihood
 * \param hint  a string containing the characters to be match
 * \return a vector of the matched items ordered by their likelihood
 */


std::vector<std::string> BayesAutocomplete::complete(std::string hint) const{
  auto lo=items.lower_bound(hint);
  std::string hintend(hint);
  hintend.back()++;
  auto up=items.upper_bound(hintend);
  if (hint.empty())
    {lo=items.begin();
      up=items.end();}

  std::multimap<double, std::string> mm;
  for (auto it=lo; it!=up; ++it)
    mm.insert({(*it).second,(*it).first});

  std::vector<std::string> res(mm.size());
  std::size_t i=mm.size();
  for (auto it=mm.begin(); it!=mm.end();  ++it)
    {
      --i;
      res[i]=it->second;

  }
  return res;

}

/*!
 * \brief BayesAutocomplete::chosenOne tells the class that an item has been selected
 * \param item the selected item
 * \post the likelihood of the item is increased by one unit
 */

void BayesAutocomplete::chosenOne(std::string item)
{
  items[item]++;
  return;

}

/*!
 * \brief BayesAutocomplete::push_back adds a new possible item with its likelihood
 * \param newItem  the new possible item
 * \param likelihood  the initial likelihood of the added item
 */

void BayesAutocomplete::push_back(std::string newItem, double likelihood)
{
  items[newItem]=likelihood;
}

}

#ifdef MACRO_TEST


#include "Tests/MultipleTests.h"
#include "Tests/ElementaryTest.h"
#include "Tests/Markov_IO/ABC_Put_Test.h"
namespace Markov_Test
{
namespace Markov_MacroConsele_Test
{

using namespace Markov_Console;

  MultipleTests BayesAutocomplete_Test::AllTests(Markov_Console::Markov_CommandManager* , const std::string )
  {
    return classInvariant();
  }

   std::string BayesAutocomplete_Test::testedClass()const
  {
    return "";
  }
   std::string BayesAutocomplete_Test::TestName()
  {
    return "BayesAutocomplete_Test";
  }

   std::string BayesAutocomplete_Test::myTest()const
   {
     return TestName();
   }


     MultipleTests BayesAutocomplete_Test::classInvariant()const
  {
       MultipleTests results("BayesAutocomplete ",
                             "Class Invariant");

       BayesAutocomplete sample;
       sample.push_back("experiment", 10);
       sample.push_back("model", 10);
       sample.push_back("model patch", 14);
       sample.push_back("model channel", 11);

       std::vector<std::string> subsample={"model patch","model channel","model"};


       auto r=sample.complete("m");
       results.push_back(ElementaryTest("complete()","should return the ordered subset",
                                         r==subsample));


       sample.push_back("experiment2",11);
       auto r2=sample.complete("e");
       std::vector<std::string> er2={"experiment2","experiment"};
       results.push_back(ElementaryTest("push_back() and complete()","acknowledges new item",
                                         r2==er2));


       sample.chosenOne("experiment");
       sample.chosenOne("experiment");

       auto r3=sample.complete("e");
       std::vector<std::string> er3={"experiment","experiment2"};
       results.push_back(ElementaryTest("chosenOne() and complete()","acknowledges new item",
                                         r3==er3));


       return results;



  }

}
}

#endif //MACRO_TEST




