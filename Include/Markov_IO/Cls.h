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
   std::vector<std::string>& operator+=(std::vector<std::string>& one, std::vector<std::string> two)
  {
     one.insert(one.end(),two.begin(),two.end());
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


  inline std::string ClsPtr(){return "ptr";}


  template<typename C>
  struct Cls
  {
    static std::string name() { return C::ClassName() ;}

  };



  template<typename C>
  struct Cls<C*>
  {
    static std::string name() { return C::ClassName()+ClsPtr() ;}
  };


  template <typename T>
  T sum_pack(T x)
  {
    return x;
  }


  template<typename T,typename...As>
  auto sum_pack(T x,As...as)
  {
     return x+sum_pack(as...);
  }


  template<typename T>
  bool and_pack(T x)
  {
    return bool(x);
  }

  template <typename T,typename... Ts>
  bool and_pack(T x,Ts... xs)
  {
     return bool(x)&& and_pack(xs...);
  }

  template<typename T>
  bool or_pack(T x)
  {
    return bool(x);
  }

  template <typename T,typename... Ts>
  bool or_pack(T x,Ts... xs)
  {
     return bool(x)&& or_pack(xs...);
  }



  template<typename...Args>
  std::string Cls_name_imp()
  {
      return sum_pack(Cls<Args>::name()...);
  };


  template<typename... Ts>
  struct Cls<std::tuple<Ts...>>
  {
    static std::string name() { return "tuple_of_"+Cls_name_imp<Ts...>() ;}
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

  template<>
  struct Cls<void>
  {
    static std::string name(){return "void";}
  };


  template <typename T>
  std::string Cls_name(T x)
  {
    return Cls<T>::name();
  }


  template<typename T>
  std::set<std::string> getMapKeys(const std::map<std::string,T>& m)
  {
    std::set<std::string> o;
    for (auto& e:m)
      o.insert(e.first);
    return o;
  }


  template<typename T>
   auto clone_impl(const T* x,int)->decltype (x->clone())
   {
     if (x!=nullptr)
     return x->clone();
     else return nullptr;
   }

   template<typename T>
   T* clone_impl(const T*x, long )
   {
     return new T(x);
   }


   template<typename T>
   T* cloneThis(const T* x)
   {
     return clone_impl(x,0);  // 0 is int so chooses x->clone if exists
   }


}
#endif // CLS_H
