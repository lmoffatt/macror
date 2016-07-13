#ifndef IMPLEMENTS_FUNCTION_H
#define IMPLEMENTS_FUNCTION_H

#include "Markov_IO/Var.h"

#include <type_traits>

namespace Markov_IO_New
{



  class ABC_Fn_Argument
  {
  public:
    static std::string ClassName(){return "Implements_Fn_Argument";}
    virtual void clear()=0;

    virtual std::string id()const=0;
    virtual const ABC_Type_of_Value* dataType()const=0;
    virtual std::string Tip()const=0;
    virtual std::string WhatThis()const=0;

    virtual bool isMandatory()const =0;
    virtual ~ABC_Fn_Argument(){}
  };

  template<typename T>
  class Implements_Fn_Argument: public ABC_Fn_Argument
  {
  public:
    virtual void clear()
    {
      id_.clear();dataType_=nullptr; whatThis_.clear(); tip_.clear();
    }

    virtual std::string id()const
    {
      return id_;
    }

    Implements_Fn_Argument(std::string id
                           ,const Implements_Data_Type_New<T>* datatype
                           ,const T& defaultValue
                           ,bool isMandatory
                           ,const std::string& tip
                           ,const std::string& whatthis):
      id_(id),dataType_(datatype),defaultValue_(defaultValue),isMandatory_(isMandatory),tip_(tip),whatThis_(whatthis){}


    virtual T defaultValue()const {return defaultValue_;}

   virtual bool isMandatory()const{return isMandatory_;}

    virtual const Implements_Data_Type_New<T>* dataType()const override {return dataType_;}
    virtual std::string Tip()const {return tip_;}
    virtual std::string WhatThis()const{return whatThis_;}
    virtual ~Implements_Fn_Argument(){}
  private:
    std::string id_;
    const Implements_Data_Type_New<T>* dataType_;
    T defaultValue_;
    bool isMandatory_;
    std::string tip_;
    std::string whatThis_;


  };






  class ABC_Closure:   public ABC_Data_New
  {
    // ABC_Value_New interface
  public:

    typedef ABC_Closure selfType;

    virtual ABC_Data_New* evalData(const StructureEnv_New* cm)=0;

    virtual const std::vector<const ABC_Data_New*>& inputArguments()const=0;


    virtual  const void* getFunction()const =0;


    virtual std::size_t numArguments()const =0;


    virtual ABC_Data_New* operator()(std::vector<ABC_Data_New*> var)const=0;


    virtual selfType* clone()const =0;

    virtual ~ABC_Closure()
    {
    }
  };

 


  template<typename Fn, typename...Args>
  class Implements_FnClosure: public ABC_Closure
  {
    // ABC_Value_New interface
  public:

    typedef  typename std::result_of<Fn(Args...)>::type R;
    typedef R returnType;

    typedef  mp_list<Args...> argumentTypes;

    typedef std::tuple<Args...>  argumentTuple;

    typedef Implements_FnClosure<Fn,Args...> selfType;

    virtual std::string myType()const override
    {
      return fnType_;
    }

    template <int I>
    typename std::tuple_element<I,argumentTuple>::type inputArgument()const
    {
      return std::get<I>(inputTu_);
    }

    Fn f()
    {
      return f_;
    }

    returnType operator()(Args... vars)
    {
      return f_(vars...);
    }


    virtual selfType* clone()const
    {
      return new selfType(*this);
    }

    virtual ~Implements_FnClosure()
    {
    }

    virtual bool isOfThisType(const StructureEnv_New* cm,
                              const std::string& generalType,
                              std::string* whyNot
                              ,const std::string &masterObjective)const override;


    Implements_FnClosure(const std::string& id,
                        Fn value
                        ,Args... vars):
      fnType_(id),f_(value),inputTu_(vars...){}


    Implements_FnClosure(const selfType& other)=default;

    Implements_FnClosure(Implements_FnClosure&& other)=default;

    Implements_FnClosure& operator=(const Implements_FnClosure& other)=default;

    Implements_FnClosure& operator=(Implements_FnClosure&& other)=default;

    Implements_FnClosure()=default;


    virtual bool empty() const override
    {
      return f_==nullptr;
    }

    virtual void reset() override
    {
      f_=nullptr;
      inputTu_=argumentTuple{};
    }

    virtual selfType* create() const override
    {
      return new selfType();
    }

    returnType eval()
    {
       return f_(std::get<std::integer_sequence<Args...>>(inputTu_));
  }

  protected:
    std::string fnType_;
    Fn f_;
    std::tuple<Args...> inputTu_;

    // ABC_Closure interface
  public:
    virtual ABC_Data_New *evalData(const StructureEnv_New* cm) override
    {

      return Implements_Value_New<returnType>("",eval());
    }
    virtual const std::vector<const ABC_Data_New *> &inputArguments() const override;

    virtual std::size_t numArguments()const override
    {
      return std::tuple_size<argumentTuple>::value;
    }
    virtual const void *getFunction() const override
    {
      if (std::is_pointer<Fn>::value)
        return f_;
      else
        return &f_;
    }
    virtual ABC_Data_New *operator ()(std::vector<ABC_Data_New *> var) const override;
  };





}


#endif // IMPLEMENTS_FUNCTION_H
