#include <string>
#include "Include/Markov_Console/Autocomplete.h"
#include "Include/Markov_LA/auxiliarRelational.h"

namespace  Markov_Console {


  Autocomplete::Autocomplete(std::vector<std::string> itemslist):
    items(itemslist.begin(),itemslist.end())
  {}




  /*!
   * \brief Autocomplete::push_back adds a new possible outcome
   * \param newMember the new instance
   */
  void Autocomplete::push_back(std::string newItem)
  {
    this->items.insert(newItem);
  }

  /*!
   * \brief Autocomplete::complete
   * \param hint  a string containing the characters to be match
   * \return a lexicographically ordered vector of the matched items
   */
  std::vector<std::string> Autocomplete::complete(std::string hint) const
  {

    auto lo=items.lower_bound(hint);
    std::string hintup=hint;
    hintup.back()++;
    auto up=items.upper_bound(hintup);
    if (hint.empty())
      {lo=items.begin();
        up=items.end();}

    std::vector<std::string> res(lo,up);
    return res;

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


    MultipleTests Autocomplete_Test::classInvariant()const
    {

      MultipleTests results("Autocomplete ",
                            "Class Invariant");

      std::vector<std::string> sample={"experiment", "model","model patch","model channel"};

      std::vector<std::string> subsample={"model","model channel","model patch"};

      Autocomplete a(sample);

      auto r=a.complete("m");
      results.push_back(ElementaryTest("complete()","should return the ordered subset",
                                       r==subsample));


      a.push_back("experiment2");
      auto r2=a.complete("e");
      std::vector<std::string> er2={"experiment","experiment2"};
      results.push_back(ElementaryTest("push_back() and complete()","acknowledges new item",
                                       r2==er2));

      auto r3=a.complete("");

      std::vector<std::string> sample2={"experiment","experiment2","model","model channel","model patch"};

      results.push_back(ElementaryTest("complete("")","returns whole list",
                                       r3==sample2));


      return results;


    }

  }
}

#endif //MACRO_TEST




