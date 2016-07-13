#ifndef MP_FUNCTION_H
#define MP_FUNCTION_H

#include "Markov_IO/Var.h"

namespace Markov_IO_New
{
  template <typename R, typename...Args>
  struct mp_arguments
  {
      typedef R returnType;
      typedef mp_list<Args...> argumentTypes;
      using function=R(*)(Args...);
      mp_arguments(function f){}
  };





}


#endif // MP_FUNCTION_H
