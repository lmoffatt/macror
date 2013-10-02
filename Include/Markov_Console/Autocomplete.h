#ifndef AUTOCOMPLETE_H
#define AUTOCOMPLETE_H
#include <vector>
#include <string>
#include <set>
#include <map>

namespace  Markov_Console {


  /*!
 * \brief The Autocomplete class provides support for autocompletition
   \invariant it holds a list of possible strings

   \invariant it can add more items through a push_back method

   \invariant it offers the method complete to provide an ordered vector with strings whose
              first characters match the provided sample
 */
class Autocomplete
{
public:

  Autocomplete(std::vector<std::string> itemslist);
  Autocomplete(){}

  template<class T>
  Autocomplete(std::map<std::string, T> itemsMap);

  std::vector<std::string> complete(std::string hint) const;

  void push_back(std::string newItem);
private:
  std::set<std::string> items;

};

template<class T>
Autocomplete::Autocomplete(std::map<std::string, T> itemsMap)
{
  for (auto it=itemsMap.begin(); it!=itemsMap.end(); ++it)
    {
      items.insert((*it).first);
    }
}


}
#ifdef MACRO_TEST


#include "Tests/MultipleTests.h"
#include "Tests/Markov_IO/ABC_Put_Test.h"
namespace Markov_Test
{
namespace Markov_MacroConsele_Test
{

using namespace Markov_Console;

class Autocomplete_Test
{
public:

    virtual MultipleTests classInvariant()const;
};

}
}

#endif //MACRO_TEST


#endif // AUTOCOMPLETE_H
