#include "Markov_IO/ABC_Put.h"
#include <sstream>
namespace Markov_IO
{

 ABC_Put::~ABC_Put() {}


 std::string ABC_Put::Tip()const
 {
     return "clones itself, generates string output";
 }



 std::string ABC_Put::WhatThis()const
 {
     return "Base of all classes with the following things\n "
             "-  copy constructor,  default constuctor\n"
             "-  formatted output\n"
             "-  destructor\n";
 }


  bool ABC_Put::operator==(const ABC_Put& other)const
 {
     std::stringstream ss;
     put(ss);
     std::string me=ss.str();
     ss.str("");
     other.put(ss);
     std::string you=ss.str();
     return me==you;
 }
}
