#ifndef VAR_H
#define VAR_H

#include "Markov_LA/Matrix.h"


#include <string>
#include <map>
#include <set>
#include <vector>

#include "Markov_IO/Token_New.h"
#include "Markov_IO/Cls.h"
#include "Markov_IO/buildByToken.h"

namespace Markov_IO_New {



  class ABC_Var_New;
  class ABC_Value_New;


  template<class T>
  T dynamicCast(ABC_Var_New* v, std::string* whyNot,const std::string& masterObjective);

  template<class T>
  const T dynamicCast(const ABC_Var_New* v, std::string* whyNot,const std::string& masterObjective);


  template<class T>
  T dynamicCast(ABC_Value_New* v, std::string* whyNot,const std::string& masterObjective);

  template<class T>
  const T dynamicCast(const ABC_Value_New* v, std::string* whyNot,const std::string& masterObjective);


  std::set<std::string> operator+(std::set<std::string>&& tok1,
                                  std::string &&s);


  std::set<std::string> operator+(std::set<std::string> &&ss1,
                                  std::set<std::string> &&ss2);



  class ABC_Value_New
  {
  public:
    static std::string ClassName()
    {
      return "ABC_Value_New";
    }

    virtual std::string myClass()const
    {
      return ClassName();
    }

    virtual std::string storedClass() const=0;

    virtual bool empty()const =0;

    virtual void reset()=0;

    virtual ABC_Value_New* clone()const=0;
    virtual ABC_Value_New* create()const=0;



    virtual ~ABC_Value_New(){}



    /// template methods
    ///

    //TODO: ver cual es la forma mas conveniente de manejar la propiedad de T, especialmente si esgrand

    template<typename T>
    const T *getValue()const;

    template<typename T>
    T* getValue();

    template<typename T>
    bool setValue(const T& val);


  };

  template <typename T>
  void reset(T& x)
  {
    x=T{};
  }




  template <typename T>
  class ABC_Typed_Value;




  template<typename T>
  class Implements_Value_New: public ABC_Value_New
  {
  public:
    static std::string ClassName()
    {
      return "Implements_Value_Typed"+Cls<T>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    virtual std::string storedClass() const override
    {
      return Cls<T>::name();

    }

    // ABC_Value_New interface
  public:
    virtual bool empty() const override
    {
      return empty_;
    }

    virtual void reset() override
    {
      data_=T{};
      empty_=true;
    }



    // Implements_Value_New interface
  public:
    virtual Implements_Value_New<T>* clone() const override
    {
      return new Implements_Value_New(data_);

    }

    virtual Implements_Value_New<T>* create() const override
    {
      return new Implements_Value_New();

    }


    virtual const T& getValued() const
    {
      return data_;
    }
    virtual T& getValued()
    {
      return data_;
    }
    virtual bool setValue(T val,std::string *whyNot, const std::string& masterObjective)
    {
      data_=std::move(val);
      empty_=false;
      return true;
    }



    Implements_Value_New():
      data_{}, empty_(true){}
    Implements_Value_New(T datum):
      data_(std::move(datum)), empty_(false){}

    ~Implements_Value_New(){}

  protected:

    T data_;
    bool empty_;
  };



  class Implements_ComplexVar_New;


  struct type_tip_Whatthis
  {
    std::string varType;
    std::string tip;
    std::string whatthis;
  };


  struct Var_id
  {
    std::string idName;
    std::string var;
    std::string tip;
    std::string whathis;
    static std::string ClassName(){return "Var_id";}
    std::string id()const {return idName;}
  };




  class ABC_Type_of_Value;
  template <typename T>
  class ABC_Typed_Value;

  class ABC_Var_New//: public ABC_Value_New
  {

    // ABC_Value_New interface
  public:
    static std::string ClassName()
    {
      return "ABC_Value_New";
    }

    virtual std::string myClass()const
    {
      return ClassName();
    }

    virtual ABC_Value_New* value()=0;

    virtual const ABC_Value_New* value()const=0;

    virtual const Implements_ComplexVar_New* parent()const =0;
    virtual void setParentValue(const Implements_ComplexVar_New* par)=0;

    virtual std::string id()const=0;


    virtual std::string Tip()const=0;
    virtual std::string WhatThis()const=0;

    virtual void setId(const std::string& idName)=0;


    virtual std::string refId()const=0;

    virtual std::string myType()const=0;

    bool isOfThisType(const Implements_ComplexVar_New* cm,
                              const std::string generalType,
                              std::string* whyNot
                              ,const std::string masterObjective)const;


    virtual ~ABC_Var_New(){}

  };

  template<typename T>
  class Implements_Var_New: public ABC_Var_New
  {
    // ABC_Value_New interface
  public:
    static std::string ClassName()
    {
      return "Implements_Var_New_of"+Cls<T>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    virtual const Implements_ComplexVar_New* parent()const override
    {
      return p_;
    }
    virtual void setParentValue(const Implements_ComplexVar_New* par) override
    {
      p_=par;
    }

    virtual std::string id()const override
    {
      return id_;
    }


    virtual std::string Tip()const override
    {
      return tip_;
    }
    virtual std::string WhatThis()const override
    {
      return whatthis_;
    }

    virtual void setId(const std::string& idName) override
    {
      id_=idName;
    }


    virtual std::string refId()const override
    {
      return id();
    }

    virtual std::string myType()const override
    {
      return var_;
    }

    virtual Implements_Value_New<T>* value()
    {
      return x_;
    }

    virtual const Implements_Value_New<T>* value()const
    {
      return x_;
    }


    virtual Implements_Value_New<T>* clone()const
    {
      return x_->clone();
    }

    virtual Implements_Value_New<T>* create()const
    {
      return x_->create();
    }



    virtual ~Implements_Var_New()
    {
      delete x_;
    }





    // Implements_Value_New interface
  public:

    Implements_Var_New(const Implements_ComplexVar_New* parent,
                       const std::string& id,
                       const std::string& var,
                       const std::string& tip,
                       const std::string& whatthis
                       ,Implements_Value_New<T>* data=new Implements_Value_New<T>):
      p_(parent),
      id_(id),var_(var),tip_(tip),whatthis_(whatthis),
      x_(data)
    {}
    Implements_Var_New(const Implements_ComplexVar_New* parent,
                       const std::string& id,
                       const std::string& var,
                       T x,
                       const std::string& tip,
                       const std::string& whatthis):
      p_(parent),
      id_(id),var_(var),tip_(tip),whatthis_(whatthis),
      x_(new Implements_Value_New<T>(std::move(x)))
    {}

    Implements_Var_New(const Implements_ComplexVar_New* parent,
                       const std::string& id,
                       const type_tip_Whatthis& ttw,
                       T x):
      Implements_Var_New(parent,id,ttw.varType,x,ttw.tip,ttw.whatthis){}


  protected:
    const Implements_ComplexVar_New* p_;
    std::string id_;
    std::string var_;
    std::string tip_;
    std::string whatthis_;
    Implements_Value_New<T>* x_;
  };



}





#endif // VAR_H
