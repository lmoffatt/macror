#ifndef VAR_H
#define VAR_H

#include "Markov_LA/Matrix.h"


#include <string>
#include <map>
#include <set>
#include <vector>

#include "Markov_IO/Token_New.h"
#include "Markov_IO/Cls.h"

#include "Markov_Mol/QMarkovModel.h"
#include "type_traits"
#include <utility>

namespace Markov_Mol_New
{
  class ABC_Markov_Model;
  class Q_Markov_Model;
}

namespace Markov_Mol_New
{
  class ABC_Markov_Model;
  class Q_Markov_Model;

  class ABC_noise;
  class gaussian_noise;

  class ABC_PatchModel;
  class PatchModel;

}

namespace Markov_IO_New {

  class ABC_Experiment;
  class Single_Pulses;

  class Pulses_program;
  class Experiment;
  class Trace;

  class ABC_trace;
  class Pulses_trace;



  namespace alternatives
  {
    inline
    std::string endOfLine() {return "<Return>";}

    inline
    std::string newIdentifier() {return "<Unoccupied Identifier>";}

    inline std::string tip(){return "#<Tip text>";}
    inline std::string whatthis(){return "##<WhatThis text>";}

  };
  class ABC_Data_New;
  struct Implements_Var;
  class StructureEnv_New;


  inline
  std::string removeHint(const std::string& alter)
  {
    if ((alter=="<")||(alter=="< ")||(alter=="<=")||(alter=="<= "))
      return alter;
    else
      {
        auto out=alter.substr(0,alter.find('<'));
        if (!out.empty()&&(out.back()!=' '))
          out.push_back(' ');
        return out;
      }
  }

  inline
  std::set<std::string> removeHint(const std::set<std::string>& alter)
  {
    std::set<std::string> out;
    for (auto& e:alter)
      {
        std::string r=removeHint(e);
        if(! r.empty())
          out.insert(r);
      }
    return out;
  }


  template<typename... Fields>
  struct mp_list{


  };

  template<class... L> struct mp_append_impl;

  template<class... L> using mp_append = typename mp_append_impl<L...>::type;

  template<> struct mp_append_impl<>
  {
    using type = mp_list<>;
  };

  template<template<class...> class L, class... T>
  struct mp_append_impl<L<T...>>
  {
    using type = L<T...>;
  };

  template<template<class...> class L1, class... T1,
           template<class...> class L2, class... T2, class... Lr>
  struct mp_append_impl<L1<T1...>, L2<T2...>, Lr...>
  {
    using type = mp_append<L1<T1..., T2...>, Lr...>;
  };



  template<typename F, typename Tuple, size_t... I>
  auto
  apply_Impl(F&& f, Tuple&& args,std::index_sequence<I...>)
  -> decltype(std::forward<F>(f)(std::get<I>(std::forward<Tuple>(args))...))
  {
    return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(args))...);
  }

  template<typename F, typename Tuple,
           typename Indices = std::make_index_sequence<std::tuple_size<Tuple>::value>>
  auto
  mp_apply(F&& f, Tuple&& args)
  -> decltype(apply_Impl(std::forward<F>(f), std::forward<Tuple>(args), Indices()))
  {
    return apply_Impl(std::forward<F>(f), std::forward<Tuple>(args), Indices());
  }



  template <typename F, typename...Args>
  struct  mp_function
  {
    F f_;
    std::tuple<Args...> args_;
  };




  namespace _private
  {

    class Implements_Data_Type_New_string;
    class Implements_Data_Type_New_ABC_Data_New;
    class Implements_Data_Type_New_Implements_Var;

    class Implements_Data_Type_New_StructureEnv;




    template<typename T> class Implements_Base_Value_New;
    template<typename D,typename B> class Implements_Derived_Value_New;


    template<typename T> class Implements_Data_Type_New_vector;
    template<typename T> class Implements_Data_Type_New_set;
    template<typename T> class Implements_Data_Type_New_M_Matrix;
    template<typename K,typename T> class Implements_Data_Type_New_pair;
    template<typename K,typename T> class Implements_Data_Type_New_map;


    template<typename T> class Implements_Data_Type_New_regular;
    template<class C> class Implements_Data_Type_class;
    template<class D,class B> class Implements_Data_Type_derived_class;




    template<typename T>
    struct mp_DataType_Imp
    {
      using type=typename    std::conditional<std::is_arithmetic<T>::value,
      Implements_Data_Type_New_regular<T>,
      Implements_Data_Type_class<T>>::type;

      using type_Ptr=typename    std::conditional<std::is_arithmetic<T>::value,
      Implements_Data_Type_New_regular<T*>,
      Implements_Data_Type_class<T*>>::type;

      using value=Implements_Base_Value_New<T>;
      using value_Ptr=Implements_Base_Value_New<T*>;

    };

    template<typename T>
    struct mp_DataType_Imp<std::vector<T>>
    {
      using type=Implements_Data_Type_New_vector<T>;
      using value=Implements_Base_Value_New<std::vector<T>>;

    };

    template<typename T>
    struct mp_DataType_Imp<std::set<T>>
    {
      using myC=std::set<T>;
      using type=Implements_Data_Type_New_set<T>;
      using value=Implements_Base_Value_New<myC>;
    };

    template<typename T>
    struct mp_DataType_Imp<Markov_LA::M_Matrix<T>>
    {
      using myC=Markov_LA::M_Matrix<T>;
      using type=Implements_Data_Type_New_M_Matrix<T>;
      using value=Implements_Base_Value_New<myC>;
    };

    template<typename K,typename T>
    struct mp_DataType_Imp<std::map<K,T>>
    {
      using myC=std::map<K,T>;
      using type=Implements_Data_Type_New_map<K,T>;
      using value=Implements_Base_Value_New<myC>;
    };

    template<typename K,typename T>
    struct mp_DataType_Imp<std::pair<K,T>>
    {
      using myC=std::pair<K,T>;
      using type=Implements_Data_Type_New_pair<K,T>;
      using value=Implements_Base_Value_New<myC>;
    };



    template<>
    struct mp_DataType_Imp<std::string>
    {
      using myC=std::string;
      using type=Implements_Data_Type_New_string;
      using value=Implements_Base_Value_New<myC>;
    };
    template<>
    struct mp_DataType_Imp<ABC_Data_New>{
      using type_Ptr=Implements_Data_Type_New_ABC_Data_New;
      using value_Ptr=Implements_Base_Value_New<ABC_Data_New*>;
    };

    template<>
    struct mp_DataType_Imp<Implements_Var>{
      using type=Implements_Data_Type_New_Implements_Var;
      using value=Implements_Base_Value_New<Implements_Var>;
    };


    template<>
    struct mp_DataType_Imp<StructureEnv_New>{
      using myB=ABC_Data_New;
      using myD=StructureEnv_New;
      using type_Ptr=Implements_Data_Type_New_StructureEnv;
      using value_Ptr=Implements_Derived_Value_New<myD,myB>;
    };

    template<>
    struct mp_DataType_Imp<Markov_Mol_New::ABC_Markov_Model>
    {
      using myB=Markov_Mol_New::ABC_Markov_Model;
      using type_Ptr=Implements_Data_Type_class<myB*>;
      using value_Ptr=Implements_Base_Value_New<myB*>;
    };

    template<>
    struct mp_DataType_Imp<Markov_Mol_New::Q_Markov_Model>
    {
      using myB=Markov_Mol_New::ABC_Markov_Model;
      using myD=Markov_Mol_New::Q_Markov_Model;
      using type_Ptr=Implements_Data_Type_derived_class<myD,myB>;
      using type=Implements_Data_Type_class<myD>;
      using value=Implements_Base_Value_New<myD>;
      using value_Ptr=Implements_Derived_Value_New<myD,myB>;
    };

    template<>
    struct mp_DataType_Imp<Markov_Mol_New::ABC_noise>
    {
      using myB=Markov_Mol_New::ABC_noise;
      using type_Ptr=Implements_Data_Type_class<myB*>;
      using value_Ptr=Implements_Base_Value_New<myB*>;
    };

    template<>
    struct mp_DataType_Imp<Markov_Mol_New::gaussian_noise>
    {
      using myB=Markov_Mol_New::ABC_noise;
      using myD=Markov_Mol_New::gaussian_noise;
      using type_Ptr=Implements_Data_Type_derived_class<myD,myB>;
      using type=Implements_Data_Type_class<myD>;
      using value=Implements_Base_Value_New<myD>;
      using value_Ptr=Implements_Derived_Value_New<myD,myB>;
    };


    template<>
    struct mp_DataType_Imp<Markov_Mol_New::ABC_PatchModel>
    {
      using myB=Markov_Mol_New::ABC_PatchModel;
      using type_Ptr=Implements_Data_Type_class<myB*>;
      using value_Ptr=Implements_Base_Value_New<myB*>;
    };

    template<>
    struct mp_DataType_Imp<Markov_Mol_New::PatchModel>
    {
      using myB=Markov_Mol_New::ABC_PatchModel;
      using myD=Markov_Mol_New::PatchModel;
      using type_Ptr=Implements_Data_Type_derived_class<myD,myB>;
      using type=Implements_Data_Type_class<myD>;
      using value=Implements_Base_Value_New<myD>;
      using value_Ptr=Implements_Derived_Value_New<myD,myB>;
    };


    template<>
    struct mp_DataType_Imp<ABC_Experiment>
    {
      using myB=ABC_Experiment;
      using type_Ptr=Implements_Data_Type_class<myB*>;
      using value_Ptr=Implements_Base_Value_New<myB*>;
    };

    template<>
    struct mp_DataType_Imp<ABC_trace>
    {
      using myB=ABC_trace;
      using type_Ptr=Implements_Data_Type_class<myB*>;
      using value_Ptr=Implements_Base_Value_New<myB*>;
    };


    template<>
    struct mp_DataType_Imp<Single_Pulses>
    {

      using myD=Single_Pulses;
      using myB=ABC_Experiment;
      using type_Ptr=Implements_Data_Type_derived_class<myD,myB>;
      using type=Implements_Data_Type_class<myD>;
      using value=Implements_Base_Value_New<myD>;
      using value_Ptr=Implements_Derived_Value_New<myD,myB>;

    };

    template<>
    struct mp_DataType_Imp<Experiment>
    {

      using myD=Experiment;
      using myB=ABC_Experiment;
      using type_Ptr=Implements_Data_Type_derived_class<myD,myB>;
      using type=Implements_Data_Type_class<myD>;
      using value=Implements_Base_Value_New<myD>;
      using value_Ptr=Implements_Derived_Value_New<myD,myB>;

    };

    template<>
    struct mp_DataType_Imp<Pulses_program>
    {

      using myD=Pulses_program;
      using myB=ABC_Experiment;
      using type_Ptr=Implements_Data_Type_derived_class<myD,myB>;
      using type=Implements_Data_Type_class<myD>;
      using value=Implements_Base_Value_New<myD>;
      using value_Ptr=Implements_Derived_Value_New<myD,myB>;

    };

    template<>
    struct mp_DataType_Imp<Trace>
    {

      using myD=Trace;
      using myB=ABC_trace;
      using type_Ptr=Implements_Data_Type_derived_class<myD,myB>;
      using type=Implements_Data_Type_class<myD>;
      using value=Implements_Base_Value_New<myD>;
      using value_Ptr=Implements_Derived_Value_New<myD,myB>;

    };

    template<>
    struct mp_DataType_Imp<Pulses_trace>
    {

      using myD=Pulses_trace;
      using myB=ABC_trace;
      using type_Ptr=Implements_Data_Type_derived_class<myD,myB>;
      using type=Implements_Data_Type_class<myD>;
      using value=Implements_Base_Value_New<myD>;
      using value_Ptr=Implements_Derived_Value_New<myD,myB>;
    };





    template<class T>
    struct mp_Data_Type
    {
      using type=typename mp_DataType_Imp<T>::type;
      using valueType=typename mp_DataType_Imp<T>::value;
    };
    template<class T>
    struct mp_Data_Type<T*>
    {
      using type=typename mp_DataType_Imp<T>::type_Ptr;
      using valueType=typename mp_DataType_Imp<T>::value_Ptr;
    };



  };
  template <class T>
  using Implements_Data_Type_New=typename _private::mp_Data_Type<T>::type;


  template <class T>
  using Implements_Value_New=typename _private::mp_Data_Type<T>::valueType;



  template<typename T>
  auto myCLass_impl(const T& x,long)->decltype (x->myClass())
  {
    return x->myClass()+ClsPtr();
  }
  template<typename T>
  auto myCLass_impl(const T& x,long)->decltype (x.myClass())
  {
    return x.myClass();
  }

  //    template<typename T>
  //    std::string myCLass_impl(const T* x, int )
  //    {
  //      return Cls<T*>::name();
  //    }



  template<typename T>
  std::string myCLass_impl(const T& x, int )
  {
    return Cls<T>::name();
  }

  template<typename T>
  std::string myClassOf(const T& x)
  {
    return myCLass_impl(x,{long(0)});  // 0 is int so chooses x->myClass if exists
  }

  template<typename T>
  std::string myClassOf(const T* x)
  {
    return myCLass_impl(x,long(-1));  // 0 is int so chooses x->myClass if exists
  }




  class ABC_Data_New;
  class ABC_Data_New;


  template<class T>
  T dynamicCast(ABC_Data_New* v, std::string* whyNot,const std::string& masterObjective);

  template<class T>
  const T dynamicCast(const ABC_Data_New* v, std::string* whyNot,const std::string& masterObjective);


  template<class T>
  T dynamicCast(ABC_Data_New* v, std::string* whyNot,const std::string& masterObjective);

  template<class T>
  const T dynamicCast(const ABC_Data_New* v, std::string* whyNot,const std::string& masterObjective);


  inline
  std::set<std::string> operator+(std::set<std::string>&& tok1,
                                  std::string &&s)
  {
    tok1.insert(s);
    return tok1;
  }

  inline std::set<std::string> operator+(std::set<std::string> &&ss1,
                                         std::set<std::string> &&ss2)
  {
    ss1.insert(ss2.begin(),ss2.end());
    return ss1;
  }



  template <typename T>
  void reset(T& x)
  {
    x=T{};
  }







  class StructureEnv_New;








  class ABC_Type_of_Value;

  class ABC_Type_of_Function;


  template<typename Fn, typename...Args>
  class Implements_Data_Type_FnClosure;



  class ABC_Data_New//: public ABC_Value_New
  {

    // ABC_Value_New interface
  public:
    static std::string ClassName(){return "ABC_Data_New";}

    virtual bool empty()const =0;

    virtual void reset()=0;

    virtual ABC_Data_New* clone()const=0;
    virtual ABC_Data_New* create()const=0;

    virtual std::string myType()const=0;


    virtual bool isOfThisType(const StructureEnv_New* cm,
                              const std::string& generalType,
                              std::string* whyNot
                              ,const std::string &masterObjective)const=0;

    virtual ~ABC_Data_New(){}

  };




  namespace _private
  {
    template<typename T>
    class Implements_Base_Value_New: public ABC_Data_New
    {
      // ABC_Value_New interface
    public:

      virtual std::string myType()const override
      {
        return varType_;
      }

      virtual T& getValue()
      {
        return value_;
      }

      virtual const T& getValue()const
      {
        return value_;
      }

      virtual T unloadValue()
      {
        T out=std::move(value_);
        value_={};
        empty_=true;
        return out;
      }

      virtual Implements_Base_Value_New<T>* clone()const
      {
        return new Implements_Base_Value_New<T>(*this);
      }

      virtual ~Implements_Base_Value_New()
      {
      }

      virtual bool isOfThisType(const StructureEnv_New* cm,
                                const std::string& generalType,
                                std::string* whyNot
                                ,const std::string &masterObjective)const override;


      Implements_Base_Value_New(const std::string& var,
                                T value):
        varType_(var),value_(value),empty_(false){}

      Implements_Base_Value_New(const std::string& var):
        varType_(var),value_(),empty_(true)
      {}

      Implements_Base_Value_New(const Implements_Base_Value_New<T>& other)=default;

      Implements_Base_Value_New(Implements_Base_Value_New<T>&& other)=default;

      Implements_Base_Value_New& operator=(const Implements_Base_Value_New<T>& other)=default;

      Implements_Base_Value_New& operator=(Implements_Base_Value_New<T>&& other)=default;

      Implements_Base_Value_New()=default;


      virtual bool empty() const override
      {
        return empty_;
      }

      virtual void reset() override
      {
        value_=T{};
        empty_=true;
      }



      virtual Implements_Base_Value_New<T>* create() const override
      {
        return new Implements_Base_Value_New();

      }
    protected:
      std::string varType_;
      T value_;
      bool empty_;
    };






    template<typename T>
    class Implements_Base_Value_New<T*>: public ABC_Data_New
    {
      // ABC_Value_New interface
    public:

      virtual std::string myType()const override
      {
        return varType_;
      }

      virtual T* getValue()
      {
        return value_;
      }

      virtual const T* getValue()const
      {
        return value_;
      }

      virtual T* unloadValue()
      {
        T* out=std::move(value_);
        value_={};
        empty_=true;
        return out;
      }

      virtual Implements_Base_Value_New<T*>* clone()const
      {
        return new Implements_Base_Value_New<T*>(*this);
      }

      virtual ~Implements_Base_Value_New()
      {
      }

      virtual bool isOfThisType(const StructureEnv_New* cm,
                                const std::string& generalType,
                                std::string* whyNot
                                ,const std::string &masterObjective)const override;


      Implements_Base_Value_New(const std::string& var,
                                T* value):
        varType_(var),value_(value),empty_(false){}

      Implements_Base_Value_New(const std::string& var):
        varType_(var),value_(),empty_(true)
      {}

      Implements_Base_Value_New(const Implements_Base_Value_New<T*>& other)=default;

      Implements_Base_Value_New(Implements_Base_Value_New<T*>&& other)=default;

      Implements_Base_Value_New& operator=(const Implements_Base_Value_New<T*>& other)=default;

      Implements_Base_Value_New& operator=(Implements_Base_Value_New<T*>&& other)=default;

      Implements_Base_Value_New()=default;


      virtual bool empty() const override
      {
        return empty_;
      }

      virtual void reset() override
      {
        value_=nullptr;
        empty_=true;
      }

      virtual Implements_Base_Value_New<T*>* create() const override
      {
        return new Implements_Base_Value_New();

      }
    protected:
      std::string varType_;
      T* value_;
      bool empty_;
    };





    template<typename D,typename B>
    class Implements_Derived_Value_New: public Implements_Value_New<B*>
    {

      // ABC_Value_New interface
    public:
      typedef Implements_Value_New<B*> baseType;

      virtual D* getValue() override
      {
        return value_;
      }

      virtual const D* getValue()const override
      {
        return value_;
      }

      virtual D* unloadValue() override
      {
        D* out=std::move(value_);
        value_={};
        baseType::empty_=true;
        return out;
      }

      virtual Implements_Derived_Value_New<D,B>* clone()const
      {
        return new Implements_Derived_Value_New<D,B>(*this);
      }

      virtual ~Implements_Derived_Value_New()
      {
      }

      virtual bool isOfThisType(const StructureEnv_New* cm,
                                const std::string& generalType,
                                std::string* whyNot
                                ,const std::string &masterObjective)const override;


      Implements_Derived_Value_New(const std::string& var,
                                   D* value):
        Implements_Base_Value_New<B*>(var,value)
      ,value_(value){}

      Implements_Derived_Value_New(const std::string& var):
        Implements_Base_Value_New<B*>(var)
      ,value_(){}


      Implements_Derived_Value_New(const Implements_Derived_Value_New<D,B>& other)=default;

      Implements_Derived_Value_New(Implements_Derived_Value_New<D,B>&& other)=default;

      Implements_Derived_Value_New& operator=(const Implements_Derived_Value_New<D,B>& other)=default;

      Implements_Derived_Value_New& operator=(Implements_Derived_Value_New<D,B>&& other)=default;

      Implements_Derived_Value_New()=default;



      virtual void reset() override
      {
        value_=nullptr;

      }

      virtual Implements_Derived_Value_New<D,B>* create() const override
      {
        return new Implements_Derived_Value_New();

      }


    protected:
      D* value_;
    };

  }

  struct Implements_Var
  {
    static std::string ClassName(){return "Implements_Var";}
    void clear()
    {
      id.clear();
      delete data;
      data=nullptr;
      Tip.clear();
      WhatThis.clear();
    }

    std::string id;
    ABC_Data_New* data;
    std::string Tip;
    std::string WhatThis;
  };

  struct const_Implements_Var
  {
    static std::string ClassName(){return "const_Implements_Var";}
    void clear()
    {
      id.clear();
      data=nullptr;
      Tip.clear();
      WhatThis.clear();
    }

    const_Implements_Var( std::string _id,
                          const ABC_Data_New* _data,
                          std::string _Tip,
                          std::string _WhatThis)
      :id(_id),data(_data),Tip(_Tip),WhatThis(_WhatThis){}

    const_Implements_Var( const Implements_Var& other)
      :id(other.id),data(other.data),Tip(other.Tip),WhatThis(other.WhatThis){}

    std::string id;
    const ABC_Data_New* data;
    std::string Tip;
    std::string WhatThis;
  };


  template<class Field>
  Implements_Var getMyVar()
  {
    Implements_Var iv;
    iv.id=Field::myId();
    iv.Tip=Field::myTip();
    iv.WhatThis=Field::myWhatThis();
    iv.data=new Implements_Value_New<typename Field::myC>(Field::myIdType(),{});
    return iv;
  }






}





#endif // VAR_H
