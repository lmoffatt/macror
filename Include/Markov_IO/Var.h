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
namespace Markov_Mol_New
{
  class ABC_Markov_Model;
  class Q_Markov_Model;
}

namespace Markov_Mol_New
{
  class ABC_Markov_Model;
  class Q_Markov_Model;
}

namespace Markov_IO_New {

  class ABC_Experiment;
  class Single_Pulses;

  class Pulses_program;

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
    struct mp_Value
    {
      using v=Implements_Base_Value_New<T>;
    };


    template<typename T>
    struct mp_DataType
    {
      using type=typename    std::conditional<std::is_arithmetic<T>::value,
      Implements_Data_Type_New_regular<T>,
      Implements_Data_Type_class<T>>::type;

      using buildType=typename    std::conditional<std::is_arithmetic<T>::value,
      T,
      StructureEnv_New*>::type;

    };

    template<typename T>
    struct mp_DataType<std::vector<T>>
    {
      using type=Implements_Data_Type_New_vector<T>;
      using buildType=std::vector<T>;
    };

    template<typename T>
    struct mp_DataType<std::set<T>>
    {
      using type=Implements_Data_Type_New_set<T>;
      using buildType=std::set<T>;
    };

    template<typename T>
    struct mp_DataType<Markov_LA::M_Matrix<T>>
    {
      using type=Implements_Data_Type_New_M_Matrix<T>;
      using buildType=Markov_LA::M_Matrix<T>;
    };

    template<typename K,typename T>
    struct mp_DataType<std::map<K,T>>
    {
      using type=Implements_Data_Type_New_map<K,T>;
      using buildType=std::map<K,T>;
    };

    template<typename K,typename T>
    struct mp_DataType<std::pair<K,T>>
    {
      using type=Implements_Data_Type_New_pair<K,T>;
      using buildType=std::pair<K,T>;
    };



    template<>
    struct mp_DataType<std::string>
    {
      using type=Implements_Data_Type_New_string;
      using buildType=std::string;
    };
    template<>
    struct mp_DataType<ABC_Data_New*>{
      using type=Implements_Data_Type_New_ABC_Data_New;
      using buildType=ABC_Data_New*;
    };

    template<>
    struct mp_DataType<Implements_Var>{
      using type=Implements_Data_Type_New_Implements_Var;
      using buildType=Implements_Var;
    };


    template<>
    struct mp_DataType<StructureEnv_New*>{
      using type=Implements_Data_Type_New_StructureEnv;
      using buildType=StructureEnv_New*;
    };

    template<>
    struct mp_DataType<Markov_Mol_New::ABC_Markov_Model*>
    {
      using type=Implements_Data_Type_class<Markov_Mol_New::ABC_Markov_Model*>;
      using buildType=StructureEnv_New*;
    };

    template<>
    struct mp_DataType<Markov_Mol_New::Q_Markov_Model*>
    {
      using type=Implements_Data_Type_derived_class
      <Markov_Mol_New::Q_Markov_Model,Markov_Mol_New::ABC_Markov_Model>;
      using buildType=StructureEnv_New*;
      };

    template<>
    struct mp_Value<Markov_Mol_New::Q_Markov_Model*>
    {
      using v=Implements_Derived_Value_New
      <Markov_Mol_New::Q_Markov_Model,Markov_Mol_New::ABC_Markov_Model>;
      using buildType=StructureEnv_New*;
    };


    template<>
    struct mp_DataType<ABC_Experiment*>
    {
      using type=Implements_Data_Type_class<ABC_Experiment*>;
      using buildType=StructureEnv_New*;
    };

    template<>
    struct mp_DataType<Single_Pulses*>
    {
      using type=Implements_Data_Type_derived_class
      <Single_Pulses,ABC_Experiment>;
      using buildType=StructureEnv_New*;
      };

    template<>
    struct mp_DataType<Pulses_program*>
    {
      using type=Implements_Data_Type_derived_class
      <Pulses_program,ABC_Experiment>;
      using buildType=StructureEnv_New*;
      };


    template<>
    struct mp_DataType<ABC_trace*>
    {
      using type=Implements_Data_Type_class<ABC_trace*>;
      using buildType=StructureEnv_New*;
    };

    template<>
    struct mp_DataType<Pulses_trace*>
    {
      using type=Implements_Data_Type_derived_class
      <Pulses_trace,ABC_trace>;
      using buildType=StructureEnv_New*;
      };

    template<>
    struct mp_Value<Single_Pulses*>
    {
      using v=Implements_Derived_Value_New
      <Single_Pulses,ABC_Experiment>;
      using buildType=StructureEnv_New*;
    };

    template<>
    struct mp_Value<Pulses_program*>
    {
      using v=Implements_Derived_Value_New
      <Pulses_program,ABC_Experiment>;
      using buildType=StructureEnv_New*;
    };


    template<>
    struct mp_Value<Pulses_trace*>
    {
      using v=Implements_Derived_Value_New
      <Pulses_trace,ABC_trace>;
      using buildType=StructureEnv_New*;
    };







  };
  template <class T>
  using Implements_Data_Type_New=typename _private::mp_DataType<T>::type;

  template <class T>
  using Implements_Value_New=typename _private::mp_Value<T>::v;

  template <class T>
  using buildType=typename _private::mp_DataType<T>::buildType;



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
