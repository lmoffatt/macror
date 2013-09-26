#include "Markov_IO/ABC_O_Descriptible.h"
#include "Markov_IO/ABC_Saveable.h"

namespace Markov_IO
{
std::ostream& operator<< (std::ostream& s,
			  const Markov_IO::ABC_O_Descriptible& x)
{
    return s<<x.GetState();
 }

std::ostream& ABC_O_Descriptible::put(std::ostream& s)const
{
    s<<GetState();
    return s;
}

 ABC_O_Descriptible::~ABC_O_Descriptible()
 {}

 std::string ABC_O_Descriptible::mySuperClass()const
 {
     return ClassName();
 }

 std::string ABC_O_Descriptible::ClassName()
 {
     return "ABC_O_Descriptible";
 }

  bool ABC_O_Descriptible::operator ==(const ABC_O_Descriptible& other)
  {
      if (myClass()!=other.myClass())
	  return false;
      if (myName()!=other.myName())
	  return false;
      if (!(GetState()==other.GetState()))
	  return false;
      return true;
  }

  bool  create(ABC_O_Descriptible*& o,const std::string& childClass)
  {
      ABC_Saveable* v;
      if (create(v,childClass))
      {
          o=v;
          return true;
      }
      return false;
  }
   ABC_O_Descriptible* ABC_O_Descriptible::create(const std::string& childClass)
  {
      ABC_O_Descriptible* o;
      if (Markov_IO::create(o,childClass))
          return o;
      else
          return 0;
  }



}
