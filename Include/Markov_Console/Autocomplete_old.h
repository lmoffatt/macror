#ifndef AUTOCOMPLETE_OLD_H
#define AUTOCOMPLETE_OLD_H

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
    Autocomplete():items{}{}
    Autocomplete(const Autocomplete& other):items(other.items){}




    Autocomplete& operator=(const Autocomplete& other)
    {
      if(this!=&other)
        {
          Autocomplete tmp(other);
          swap(*this,tmp);
        }
      return *this;
    }

    friend void swap(Autocomplete& one, Autocomplete &other)
    {
      std::swap(one.items,other.items);
    }

    ~Autocomplete(){}

    template<class T>
    Autocomplete(const std::map<std::string, T>& itemsMap);

    std::vector<std::string> complete(const std::string &hint) const;

    bool has(const std::string& item) const;


    void push_back(std::string newItem);
    void clear();

    static std::string suggestedCharacters(const std::vector<std::string>& autocompleteList, const std::string& hint);
  private:
    std::set<std::string> items;

  };

  template<class T>
  Autocomplete::Autocomplete(const std::map<std::string, T>& itemsMap)
  {
    for (auto it=itemsMap.begin(); it!=itemsMap.end(); ++it)
      {
        items.insert((*it).first);
      }
  }


}


#endif // AUTOCOMPLETE_OLD_H
