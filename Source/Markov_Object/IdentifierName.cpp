#include "Markov_Object/IdentifierName.h"

namespace Markov_Object {



  void IdentifierName::
  skipSpaces(const std::string &line,
             std::size_t &n,
             const std::string& mySeparator)
  {
    while((n<line.size())&&(mySeparator.find_first_of(line[n])!=mySeparator.npos))
      ++n;
    if (n==line.size()) n=line.npos;
  }

  std::string IdentifierName::get(const std::string &text,
                                  std::size_t &pos,
                                  std::string myAllowedR,
                                  std::string myAllowed,
                                  std::string mySeparator)

  {
    std::size_t pos0=pos;
    skipSpaces(text,pos,mySeparator);
    if (pos==text.npos)
      {
        pos=pos0;
        return "";
      }
    else
      {
        std::size_t start=pos;
        pos =text.find_first_of(mySeparator,start);


        std::string candidate=text.substr(start,pos-start);
        if (candidate.empty())
          {
            pos=pos0;
            return {};
          }

        if (myAllowed.find_first_of(candidate[0])==candidate.npos)
          {
            pos=pos0;
            return {};
          }
        if ((candidate.size()>1) &&(candidate.find_first_not_of(myAllowedR,1)==candidate.npos))
          {
            pos=pos0;
            return {};
          }
        return candidate;
      }
  }


  std::string IdentifierName::get(const std::string &multiplelines,
                                  std::string myAllowedR,
                                  std::string myAllowed,
                                  std::string mySeparator)
  {
    std::size_t pos=0;
    return get(multiplelines,
               pos,
               myAllowedR,
               myAllowed,
               mySeparator);
  }

  IdentifierName::IdentifierName():
    name_{}{}

  IdentifierName::IdentifierName(const std::string &text,
                                 std::string myAllowedR,
                                 std::string myAllowed,
                                 std::string mySeparator):
    name_(get(text,myAllowedR,myAllowed,mySeparator)){}

  IdentifierName::IdentifierName(const std::string &text, std::size_t &cursor,
                                 std::string myAllowedR,
                                 std::string myAllowed,
                                 std::string mySeparator):
    name_(get(text,cursor,myAllowedR,myAllowed,mySeparator)){}
}
