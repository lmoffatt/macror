#ifndef CLS_H
#define CLS_H

#include "Markov_LA/Matrix.h"

#include <string>
#include <set>
#include <map>
#include <vector>

namespace Markov_IO_New {


   template<typename T>
    T* clone(T const* x)
    {
      return x->clone();
    }



  template<typename C>
  struct Cls
  {
    static std::string name() { return C::ClassName() ;}
  };

  template<typename C>
  struct Cls<C*>
  {
    static std::string name() { return C::ClassName() ;}
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
