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
  std::vector<std::string> Autocomplete::complete(const std::string &hint) const
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

std::string Autocomplete::suggestedCharacters(const std::vector<std::string>& list, const std::string& hint)
{
  if (list.empty())
    return "";
  std::size_t i=0;
  while ((i<list.size())&&((list[i][0]=='<')||(list[i][0]=='[')))
    i++;

  if (i==list.size())
    return "";

  std::size_t n=0;


  while((n<hint.size())&&(n<list.back().size())&&(list.back()[n]==hint[n]))
    n++;
  std::size_t m=n;
  while((m<list[i].size())&&(m<list.back().size())&&(list[i][m]==list.back()[m]))
    m++;
  return list[i].substr(n,m-n);
}



  bool Autocomplete::has(const std::string& item)const
  {
    return items.find(item)!=items.end();
  }



   void Autocomplete::clear()
   {
     items.clear();
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
     std::string Autocomplete_Test::TestName()
    {
      return "Autocomplete_Test";
    }

     std::string Autocomplete_Test::myTest()const
     {
       return TestName();
     }


    MultipleTests Autocomplete_Test::AllTests(Markov_Console::Markov_CommandManager* , const std::string )

    {
      return classInvariant();
    }

     std::string Autocomplete_Test::testedClass()const
    {
      return "";
    }


    MultipleTests Autocomplete_Test::classInvariant()const
    {

      MultipleTests results("Autocomplete ",
                            "Class Invariant");

      std::vector<std::string> sample={"experiment", "model","model patch","model channel"};

      std::vector<std::string> subsample={"model","model channel","model patch"};

      Autocomplete a(sample);

      std::string hint="m";

      auto r=a.complete(hint);
      results.push_back(ElementaryTest("complete()","should return the ordered subset",
                                       r==subsample));


      results.push_back(ElementaryTest("complete(hint)","should accomodate the matching characters in hint",
                                       hint=="model"));


      hint="experiment2";
      a.push_back(hint);
      std::string e="e";
      auto r2=a.complete(e);
      std::vector<std::string> er2={"experiment","experiment2"};
      results.push_back(ElementaryTest("push_back() and complete()","acknowledges new item",
                                       r2==er2));

      hint="";
      auto r3=a.complete(hint);

      std::vector<std::string> sample2={"experiment","experiment2","model","model channel","model patch"};

      results.push_back(ElementaryTest("complete("")","returns whole list",
                                       r3==sample2));


      return results;


    }

  }
}

#endif //MACRO_TEST




