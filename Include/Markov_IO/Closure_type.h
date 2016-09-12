#ifndef CLOSURE_TYPE_H
#define CLOSURE_TYPE_H



#include "Markov_IO/Var.h"



namespace Markov_IO_New {

  class ABC_Closure;
  class ABC_Type_of_Closure;

  class ABC_Type_of_Function;

  class ABC_Type_of_Method;

  template<typename R>
  class ABC_R_Closure;

  template<typename R>
  class ABC_R_function;

  namespace _private
  {
  template<typename Fn, typename R,typename...Args>
  class Implements_Closure_Value_R_Fn_Args_Function;


  template<typename Fn, typename R,typename...Args>
  class Implements_Closure_Type_R_Fn_Args_Function;

  template<class C>
  class Implements_Closure_Type_C_Method;

  template<class C,typename R,typename...Args>
  class Implements_Closure_Value_R_C_Args_Method;

  template<class C,typename R,typename...Args>
  class Implements_Closure_Type_R_C_Args_Method;


  class Implements_Closure_Type_Function;

  template<typename R> class Implements_Data_Type_R_Function;

}
  template<typename Fn,typename... Args, size_t... I>
  void
  apply_void_Impl(Markov_CommandManagerVar* cm,Fn f, std::tuple<ABC_R_Closure<Args>*...> args,std::index_sequence<I...>)
  {
    f(std::get<I>(args)->eval(cm)...);
  }

  template<typename Fn, typename...Args>
  void
  mp_apply_void(Markov_CommandManagerVar* cm,Fn f, std::tuple<ABC_R_Closure<Args>*...> args)
  {
    return apply_void_Impl(cm,f, args,
                           std::index_sequence_for<Args...>());
  }


  template<typename Fn,typename R,typename... Args, size_t... I>
  R
  apply_cm_Impl(Markov_CommandManagerVar* cm,Fn f, std::tuple<ABC_R_Closure<Args>*...> args,std::index_sequence<I...>)
  {
    f(std::get<I>(args)->eval(cm)...);
  }

  template<typename Fn, typename R, typename...Args>
  R
  mp_apply_cm(Markov_CommandManagerVar* cm,Fn f, std::tuple<ABC_R_Closure<Args>*...> args)
  {
    return apply_cm_Impl(cm,f, args,
                           std::index_sequence_for<Args...>());
  }







  namespace _private
  {

    template<typename T> class Implements_Closure_Value_Base_T_Identifier;
    template<typename T> class Implements_Closure_Value_Base_T_Constant;
    template <typename T> class Implements_Closure_Type_T_Identifier;
    template <typename T> class Implements_Closure_Type_T_Constant;

    template<typename R> class Implements_Closure_Type_ABC_R;
    template<typename R> class Implements_Closure_Type_R_function;

    template<typename... Args> class Implements_Closure_Type_tuple;
    template<typename... Args> class Implements_Closure_Value_tuple;


    template<typename T,typename... Ts>
    struct mp_ClosureType_Imp
    {

    };


    template<>
    struct mp_ClosureType_Imp<void*>{
      using type=Implements_Closure_Type_Function;
      using value=ABC_Closure;
    };

    template<class C>
    struct mp_ClosureType_Imp<void*,C>{
      using type=Implements_Closure_Type_C_Method<C>;
      using value=ABC_Closure;
    };


    template<typename R>
    struct mp_ClosureType_Imp<R>{
      using type=Implements_Closure_Type_ABC_R<R>;
      using value=ABC_R_Closure<R>;
    };

    template<typename R>
    struct mp_ClosureType_Imp<R,void*>{
      using type=Implements_Closure_Type_R_function<R>;
      using value=ABC_R_function<R>;
    };

    template<typename R>
    struct mp_ClosureType_Imp<R,std::string>{
      using type=Implements_Closure_Type_T_Identifier<R>;
      using value=Implements_Closure_Value_Base_T_Identifier<R>;
    };
    template<typename R>
    struct mp_ClosureType_Imp<R,int>{
      using type=Implements_Closure_Type_T_Constant<R>;
      using value=Implements_Closure_Value_Base_T_Constant<R>;
    };

    template<typename... Ts>
    struct mp_ClosureType_Imp<std::tuple<Ts...>>{
      using type=Implements_Closure_Type_tuple<Ts...>;
      using value=Implements_Closure_Value_tuple<Ts...>;
    };
    template<typename C,typename R,typename...Args>
    struct mp_ClosureType_Imp<R,C,void,Args...>
    {
      using type=Implements_Closure_Type_R_C_Args_Method<R,C,Args...>;
      using value=Implements_Closure_Value_R_C_Args_Method<R,C,Args...>;
    };


    template<typename Fn, typename R,typename...Args>
    struct mp_ClosureType_Imp<R,void,Fn,Args...>
    {
      using type=Implements_Closure_Type_R_Fn_Args_Function<R,Fn,Args...>;
      using value=Implements_Closure_Value_R_Fn_Args_Function<R,Fn,Args...>;
    };

    template<typename Fn,typename...Args>
    struct mp_ClosureType_Imp<void,void,Fn,Args...>
    {
      using type=Implements_Closure_Type_R_Fn_Args_Function<void,Fn,Args...>;
      using value=Implements_Closure_Value_R_Fn_Args_Function<void,Fn,Args...>;
    };





    template<class... T>
    struct mp_Closure_Type
    {
      using type=typename mp_ClosureType_Imp<T...>::type;
      using valueType=typename mp_ClosureType_Imp<T...>::value;
    };


  };


  template <class... T>
  using Implements_Closure_Type=typename _private::mp_Closure_Type<T...>::type;


  template <class... T>
  using Implements_Closure_Value=typename _private::mp_Closure_Type<T...>::valueType;


}




#endif // CLOSURE_TYPE_H
