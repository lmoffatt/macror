#ifndef CLS_H
#define CLS_H

#include "Markov_LA/Matrix.h"

#include <string>
#include <set>
#include <map>
#include <vector>
#include <limits>

namespace Markov_IO_New {

   inline
   std::set<std::string>& operator+=(std::set<std::string>& one, std::set<std::string> two)
  {
     one.insert(two.begin(),two.end());
     return one;
   }

   inline
   std::pair<std::string,std::set<std::string>>& operator+=(std::pair<std::string,std::set<std::string>>& one, std::pair<std::string,std::set<std::string>> two)
  {
     one.first+="  ";
     one.first+=two.first;

      one.second.insert(two.second.begin(),two.second.end());
     return one;
   }


   template<typename T>
    T* clone(T const* x)
    {
      return x->clone();
    }


 namespace Num
{
   template<typename T>
    T empty()
   {
     return std::numeric_limits<T>::max();
   }

   template<typename T>
    bool isEmpty(T x)
   {
     return x==std::numeric_limits<T>::max();
   }

 };




  template<typename C>
  struct Cls
  {
    static std::string name() { return C::ClassName() ;}

  };

  template<typename C>
  struct Cls<C*>
  {
    static std::string name() { return C::ClassName()+"ptr" ;}
  };


  template<typename T>
  struct Cls<std::vector<T>>
  {
    static std::string name() { return "vector_of_"+Cls<T>::name() ;}
  };

  template<typename T>
  struct Cls<std::set<T>>
  {
    static std::string name() {return "set_of_"+Cls<T>::name();}
  };

  template<typename K,typename T>
  struct Cls<std::pair<K,T>>
  {
    static std::string name() { return "pair_of_"+Cls<K>::name()+"_and_"+Cls<T>::name() ;}
  };

  template<typename K,typename T>
  struct Cls<std::map<K,T>>
  {
    static std::string name(){return "map_of_"+Cls<K>::name()+"_on_"+Cls<T>::name();}
  };


  template<typename T>
  struct Cls<Markov_LA::M_Matrix<T>>
  {
    static std::string name() { return "matrix_of_"+Cls<T>::name() ;}
  };


  template<>
  struct Cls<int>
  {
    static std::string name() {return "integer";}
  };

  template<>
  struct Cls<double>
  {
    static std::string name(){return "double";}
  };

  template<>
  struct Cls<std::string>
  {
    static std::string name(){return "string";}
  };

  template<>
  struct Cls<std::size_t>
  {
    static std::string name(){return "count";}
  };

  template<>
  struct Cls<bool>
  {
    static std::string name(){return "boolean";}
  };



  template<typename T>
  std::set<std::string> getMapKeys(const std::map<std::string,T>& m)
  {
    std::set<std::string> o;
    for (auto& e:m)
      o.insert(e.first);
    return o;
  }


  template<>
  inline
  int *clone<int>(int const * x)
  {
    return new int(*x);
  }

  template<>
  inline
  double *clone<double>(double const * x)
  {
    return new double(*x);
  }

  template<>
  inline
  std::size_t *clone<std::size_t>(std::size_t const * x)
  {
    return new std::size_t(*x);
  }

  template<>
  inline
  std::string *clone<std::string>(std::string const * x)
  {
    return new std::string(*x);
  }


}
#endif // CLS_H
