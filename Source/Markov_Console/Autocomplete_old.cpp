#include <string>
#include "Include/Markov_Console/Autocomplete_old.h"
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

