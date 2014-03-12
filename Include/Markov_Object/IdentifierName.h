#ifndef IDENTIFIERNAME_H
#define IDENTIFIERNAME_H

#include <cstring>
#include "Markov_Object/Abstract_Object.h"

namespace Markov_Object
{

  class IdentifierName//: public virtual Abstract_Object
  {
  public:
    static constexpr const char* allowed="abcdefghijklmopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static constexpr const char* allowedR="_0123456789abcdefghijklmopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    static constexpr const char* separator=" \t\n/";

    static void skipSpaces(const std::string& line,
                           std::size_t& n,
                           const std::string& mySeparator=separator);


    static
    std::string get(const std::string& multiplelines,
                    std::size_t& pos,
                    std::string myAllowedR=allowedR,
                    std::string myAllowed=allowed,
                    std::string mySeparator=separator);

    static
    std::string get(const std::string& multiplelines,
                    std::string myAllowedR=allowedR,
                    std::string myAllowed=allowed,
                    std::string mySeparator=separator);


    IdentifierName(const std::string &text,
                   std::size_t &cursor,
                   std::string myAllowedR=allowedR,
                   std::string myAllowed=allowed,
                   std::string mySeparator=separator);

    IdentifierName(const std::string &text,
                   std::string myAllowedR=allowedR,
                   std::string myAllowed=allowed,
                   std::string mySeparator=separator);

    IdentifierName();


   private:

    std::string name_;


  };

}
#endif // IDENTIFIERNAME_H
