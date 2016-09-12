#ifndef IMPLEMENTS_CLOSURES_H
#define IMPLEMENTS_CLOSURES_H

#include "Markov_IO/Var.h"
#include "Markov_IO/buildClosureByToken.h"
#include "Markov_LA/matrixSum.h"

//#include "Markov_IO/Implements_function.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <tuple>
#include <type_traits>

namespace Markov_IO_New {

  class ABC_Fn_Argument
  {
  public:
    static std::string ClassName(){return "Implements_Fn_Argument";}
    virtual void clear()=0;

    virtual std::string id()const=0;
    virtual const ABC_Type_of_Closure* closureType(const StructureEnv_New* cm)const=0;
    virtual std::string Tip()const=0;
    virtual std::string WhatThis()const=0;

    virtual bool isMandatory()const =0;

    virtual bool isDefaulted()const=0;
    virtual ~ABC_Fn_Argument(){}
  };


  template<typename T>
  class Implements_Fn_Argument: public ABC_Fn_Argument
  {
  public:
    typedef T myC;

    typedef Implements_Fn_Argument<T> selfType;

    virtual void clear()
    {
      id_.clear();closureType_=nullptr; isDefaulted_=true;whatThis_.clear(); tip_.clear();
    }

    virtual std::string id()const
    {
      return id_;
    }



    Implements_Fn_Argument(std::string id
                           ,const Implements_Closure_Type<T>* datatype
                           ,ABC_R_Closure<T>* defaultValue
                           ,const std::string& tip
                           ,const std::string& whatthis):
      id_(id),closureType_(datatype),defaultValue_(defaultValue),isDefaulted_(false),tip_(tip),whatThis_(whatthis){}


    Implements_Fn_Argument(ABC_R_Closure<T>* defaultValue
                           ):
      id_(""),closureType_(nullptr),defaultValue_(defaultValue),isDefaulted_(true)
    ,tip_(""),whatThis_(""){}


    Implements_Fn_Argument():
      id_(""),closureType_(nullptr),defaultValue_(nullptr),isDefaulted_(false)
    ,tip_(""),whatThis_(""){}


    Implements_Fn_Argument(const Implements_Fn_Argument& other):
      id_(other.id_),closureType_(other.closureType_)
    ,defaultValue_(other.defaultValue_->clone()),isDefaulted_(other.isDefaulted_),
      tip_(other.tip_),whatThis_(other.whatThis_){}
    Implements_Fn_Argument( Implements_Fn_Argument&& other)=default;
    Implements_Fn_Argument& operator=(const Implements_Fn_Argument& other)=default;
    Implements_Fn_Argument& operator=(Implements_Fn_Argument&& other)=default;



    Implements_Fn_Argument(const StructureEnv_New *cm,
                           std::string id
                           ,const std::string& tip
                           ,const std::string& whatthis):
      Implements_Fn_Argument(id,
                             cm->idToTypeC<T>(Cls<T>::name()),
                             nullptr,tip,whatthis){}

    Implements_Fn_Argument(const StructureEnv_New *cm
                           ,std::string id
                           ,T defaultValue
                           ,const std::string& tip
                           ,const std::string& whatthis):
      Implements_Fn_Argument(id,
                             cm->idToTypeC<T>(Cls<T>::name()),
                             new Implements_Closure_Value<T,int>
                             (defaultValue)
                             ,tip,whatthis){}





    virtual ABC_R_Closure<T>* defaultValue()const {return defaultValue_->clone();}

    virtual bool isMandatory()const{return defaultValue_==nullptr;}

    virtual bool isDefaulted()const{return isDefaulted_;}



    virtual const Implements_Closure_Type<T>* closureType(const StructureEnv_New * cm)const override
    {
      if (closureType_!=nullptr)
        return closureType_;
      else
        return cm->idToTypeC<T>(Cls<T>::name());
    }
    virtual std::string Tip()const {return tip_;}
    virtual std::string WhatThis()const override{return whatThis_;}
    virtual ~Implements_Fn_Argument(){}
    virtual selfType* clone(){return new selfType(*this);}
  private:
    std::string id_;
    const Implements_Closure_Type<T>* closureType_;
    std::unique_ptr<ABC_R_Closure<T>> defaultValue_;
    bool isDefaulted_;
    std::string tip_;
    std::string whatThis_;
  };


  template<>
  class Implements_Fn_Argument<void>: public ABC_Fn_Argument
  {
  public:
    typedef void myC;
    virtual void clear() override
    {
    }

    virtual std::string id()const override
    {
      return "void";
    }

    Implements_Fn_Argument(){}


    virtual void defaultValue()const {}

    virtual bool isMandatory()const override {return false;}

    virtual bool isDefaulted()const override {return true;}


    virtual const ABC_Type_of_Closure* closureType(const StructureEnv_New* cm)const override {return nullptr;}



    virtual std::string Tip()const  override {return "void";}
    virtual std::string WhatThis() const override {return "returns nothing";}
    virtual ~Implements_Fn_Argument(){}

  };


  template<typename...Args, std::size_t...Is>
  std::string getId(const std::tuple<Implements_Fn_Argument<Args>...>& arg,
                    std::index_sequence<Is...>)
  {

    return sum_pack("_"+std::get<Is>(arg).id()...);

  }


  class ABC_BuildClosure;

  class ABC_Type_of_Closure //: public ABC_Type_of_Value
  {
    // ABC_Value_New interface
  public:

    typedef ABC_Type_of_Closure selfType;

    virtual bool empty()const =0;

    virtual void reset()=0;

    virtual ABC_Type_of_Closure* clone()const=0;
    virtual ABC_Type_of_Closure* create()const=0;


    virtual ~ABC_Type_of_Closure()
    {
    }


    virtual const ABC_Type_of_Value *  myResultType(const StructureEnv_New* cm)const=0;

    virtual ABC_BuildClosure* getBuildClosureByToken(
        const StructureEnv_New* cm)const=0;


  };










  class ABC_Type_of_Function : public ABC_Type_of_Closure
  {
    // ABC_Value_New interface
  public:


    virtual ABC_Type_of_Function* clone()const=0;
    virtual ABC_Type_of_Function* create()const=0;


    virtual const Implements_Identifier* myFunctionIdentifier(const StructureEnv_New* )const=0;

    virtual Implements_Closure_Type<void*> const* myFunctionType(const StructureEnv_New * cm)const=0;



    virtual ~ABC_Type_of_Function()
    {
    }


  };

  class ABC_Function_Overload: public ABC_Type_of_Function
  {
  public:

    virtual ~ABC_Function_Overload(){}
    virtual   void setFunction(const Implements_Closure_Type<void*>* f)=0;
    virtual ABC_Function_Overload* clone()const=0;
    virtual ABC_Function_Overload* create()const=0;

  };

  class ABC_Type_of_Method: public ABC_Type_of_Closure
  {
  public:
    virtual ABC_Type_of_Value const * typeOfObject(const StructureEnv_New* cm)const=0;

    virtual const Implements_Identifier* myMethodIdentifier(const StructureEnv_New* cm)const=0;

    virtual ABC_Type_of_Method const* myMethodType(const StructureEnv_New* cm)const=0;
    virtual ABC_Type_of_Method* clone()const=0;
    virtual ABC_Type_of_Method* create()const=0;

    virtual ~ABC_Type_of_Method(){}
  };

  template<class C>
  class ABC_Type_of_C_Method: ABC_Type_of_Method
  {

    virtual Implements_Data_Type_New<C> const * typeOfObject(const StructureEnv_New* cm)const=0;

    virtual Implements_Closure_Type<C,std::string> const * myObjectIdentifier(const StructureEnv_New* cm)const =0;

    virtual Implements_Closure_Type<void*,C> const* myMethodType(const StructureEnv_New* cm)const=0;


    virtual ~ABC_Type_of_C_Method(){}

  };



  template <typename R>
  class ABC_Type_of_R_Closure: public ABC_Type_of_Closure
  {
  public:

    virtual ABC_Type_of_R_Closure* clone()const=0;
    virtual ABC_Type_of_R_Closure* create()const=0;

    virtual ~ABC_Type_of_R_Closure()
    {
    }

    virtual Implements_Data_Type_New<R> const *
    myResultType(const StructureEnv_New* cm)const=0;

  };


  template <class...T> class buildClosureByToken;


  namespace _private
  {

    template <typename T>
    class Implements_Closure_Type_T_Identifier: public ABC_Type_of_Closure
    {


      // ABC_Data_New interface
    public:
      typedef Implements_Closure_Value<T, std::string> myC;


      typedef Implements_Closure_Type<T,std::string> selfType;

      typedef buildClosureByToken<T,std::string> buildType;


      virtual bool empty() const override
      {
        return resultType_==nullptr;
      }
      virtual void reset() override{
        resultType_=nullptr;

      }

      virtual bool putClosure(const StructureEnv_New* cm
                              ,const myC* v
                              ,ABC_Output* ostream
                              ,std::string* error,
                              const std::string& masterObjective)const
      {
        return getIdentifierType(cm)
            ->putValue(cm,v->getIdentifier(),ostream,error,masterObjective);

      }

      virtual bool getClosure(const StructureEnv_New* cm
                              ,myC*& v
                              , ABC_Input* istream
                              ,std::string* error
                              , const std::string& masterObjective)const
      {
        std::string id;
        if (getIdentifierType(cm)->getValue(cm,id,istream,error,masterObjective))
          {
            v=new myC(this,id);
            return true;
          }
        else
          return false;
      }



      virtual buildType* getBuildClosureByToken(
          const StructureEnv_New* cm)const override
      {
        return new buildType(cm,this);
      }


      const Implements_Identifier* getIdentifierType(const StructureEnv_New* cm) const
      {return myResultType(cm)->getVarIdType(cm);}

      Implements_Data_Type_New<T> const * myResultType(const StructureEnv_New* cm)const override
      {
        if (resultType_==nullptr)
          return cm->idToTyped<T>(Cls<T>::name());
        else
          return resultType_;
      }

      Implements_Closure_Type_T_Identifier(const Implements_Data_Type_New<T>* myresultType=nullptr)
        :
          resultType_(myresultType){}


      virtual selfType* clone()const override{return new selfType(*this);}
      virtual selfType* create()const override {return new selfType();}

    private:
      const Implements_Data_Type_New<T>* resultType_;
    };


    template <typename T>
    class Implements_Closure_Type_T_Constant: public ABC_Type_of_Closure
    {


      // ABC_Data_New interface
    public:
      typedef Implements_Closure_Value<T,int> myC;

      typedef Implements_Closure_Type<T,int> selfType;

      typedef buildClosureByToken<T,int> buildType;


      virtual bool empty() const override{
        return (varType_==nullptr)||(varType_->empty());
      }
      virtual void reset() override{
        varType_=nullptr;
      }

      virtual selfType *clone() const override{ return new selfType(*this);}
      virtual selfType *create() const override{ return new selfType();}


      virtual bool putClosure(const StructureEnv_New* cm
                              ,const myC* v
                              ,ABC_Output* ostream
                              ,std::string* error,
                              const std::string& masterObjective)const
      {
        return myResultType(cm)->putValue(cm,v->getData(),ostream,error,masterObjective);
      }

      virtual bool getClosure(const StructureEnv_New* cm
                              ,myC*& v
                              , ABC_Input* istream
                              ,std::string* error
                              , const std::string& masterObjective)const
      {
        T x;
        if (myResultType(cm)->getValue(cm,x,istream,error,masterObjective))
          {
            v=new myC(this,x);
            return true;
          }
        else return false;


      }

      virtual const Implements_Data_Type_New<T> *  myResultType(const StructureEnv_New* cm)const override
      {
        if (varType_==nullptr)
          return cm->idToTyped<T>(Cls<T>::name());
        else
          return varType_;
      }



      virtual buildType* getBuildClosureByToken(
          const StructureEnv_New* cm)const override
      {
        return new buildType(cm,this);
      }

      Implements_Closure_Type_T_Constant(const Implements_Data_Type_New<T>* varType)
        :varType_(varType){}

      Implements_Closure_Type_T_Constant()
        :varType_(nullptr){}

    private:
      const Implements_Data_Type_New<T>* varType_;
    };



    template<typename... Args>
    class Implements_Closure_Value_tuple: public ABC_R_Closure<std::tuple<Args...>>
    {
      // ABC_Closure interface
    public:
      typedef Implements_Closure_Value<std::tuple<Args...>> selfType;
      typedef std::tuple<Args...> myC;



      virtual Implements_Closure_Type<myC> const* closureType(const StructureEnv_New* cm)const
      {
        return clType_;
      }


      const std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>& getTuple() const
      {
        return clData_;
      }
      std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>& getTuple()
      {
        return clData_;
      }


      virtual bool putMe(const StructureEnv_New* cm
                         ,ABC_Output* ostream
                         ,std::string* error,
                         const std::string& masterObjective)const
      {
        return closureType(cm)->putClosure(cm,this,ostream,error,masterObjective);
      }



      virtual bool empty() const override
      {
        return empty_imp(clData_,std::index_sequence_for<Args...>());

      }
      virtual void reset() override{

        return reset_imp(clData_,std::index_sequence_for<Args...>());

      }
      virtual selfType *clone() const override {
        return new selfType(*this);
      }
      virtual selfType *create() const override {return new selfType();}


      virtual const Implements_Data_Type_New<myC> *resultType(const StructureEnv_New * cm) const override
      {
        return closureType(cm)->myResultType(cm);
      }
      virtual Implements_Value_New<myC> *evalData(Markov_CommandManagerVar *cm) const  override
      {
        return new Implements_Value_New<myC>(resultType(cm),eval(cm));
      }

      Implements_Closure_Value_tuple
      ( const Implements_Closure_Type<myC> * clType,
        std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...> clData)
        : clType_(clType),clData_(clData){}


      Implements_Closure_Value_tuple()
        : clType_(),clData_(){}


      Implements_Closure_Value_tuple(const Implements_Closure_Value_tuple& other)
        : clType_(other.clType_),clData_(clone_tuple(other.clData_)){}

      Implements_Closure_Value_tuple( Implements_Closure_Value_tuple&& other)=default;
      Implements_Closure_Value_tuple& operator=(const Implements_Closure_Value_tuple& other)=default;
      Implements_Closure_Value_tuple& operator=(Implements_Closure_Value_tuple&& other)=default;



      // ABC_R_Closure interface
    public:
      virtual myC eval(Markov_CommandManagerVar *cm) const  override
      {
        return eval_imp(cm,clData_,std::index_sequence_for<Args...>());
      }
      ~Implements_Closure_Value_tuple(){}

    protected:

      template<std::size_t... Is>
      static  myC eval_imp(Markov_CommandManagerVar *cm
                           ,const std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>& clData
                           ,std::index_sequence<Is...>)
      {
        return {std::get<Is>(clData)->eval(cm)...};
      }

      template<std::size_t... Is>
      static  bool empty_imp(const std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>& clData
                             ,std::index_sequence<Is...>)
      {
        return and_pack(std::get<Is>(clData)->empty()...);
      }



      template<std::size_t... Is>
      static  void reset_imp(std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>& clData
                             ,std::index_sequence<Is...>)
      {
        auto a= {(std::get<Is>(clData)->reset(),0)...};
      }
    private:
      const Implements_Closure_Type<myC> * clType_;
      std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...> clData_;

    };



    template<typename... Args>
    class Implements_Closure_Type_tuple:public ABC_Type_of_R_Closure<std::tuple<Args...>>
    {
    public:
      typedef Implements_Closure_Value<std::tuple<Args...>> myC;
      typedef Implements_Closure_Type<std::tuple<Args...>> selfType;

      typedef buildClosureByToken<std::tuple<Args...>> buildType;

      typedef std::tuple<Implements_Fn_Argument<Args>...> dataArgumentsTuple;



      virtual buildType* getBuildClosureByToken(
          const StructureEnv_New* cm)const override
      {
        return new buildType(cm,this);
      }


      template <std::size_t D>
      static bool putClosure_imp(const StructureEnv_New* cm,
                                 const myC* v
                                 ,const dataArgumentsTuple arg
                                 ,ABC_Output* ostream
                                 ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")
      {
        return true;

      }


      template <std::size_t D,std::size_t I, std::size_t... Is>
      static bool putClosure_imp(const StructureEnv_New* cm,
                                 const myC* v
                                 ,const dataArgumentsTuple arg
                                 ,ABC_Output* ostream
                                 ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")
      {

        auto& e=std::get<I>(v->getTuple());

        if (! e->putMe(cm,ostream,whyNot,masterObjective))
          return false;
        else return putClosure_imp<D,Is...>(cm,v,arg,ostream,whyNot,masterObjective);

      }




      template <std::size_t... Is>
      static bool putClosure_imp(std::index_sequence<Is...>,const StructureEnv_New* cm,
                                 const myC* v
                                 ,const dataArgumentsTuple arg
                                 ,ABC_Output* ostream
                                 ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")
      {
        return putClosure_imp<0,Is...>(cm,v,arg,ostream,whyNot,masterObjective);
      }


      virtual bool putClosure(const StructureEnv_New* cm,
                              const myC* v
                              ,ABC_Output* ostream
                              ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")const
      {

        return putClosure_imp
            (std::index_sequence_for<Args...>()
             ,cm,v,getFnArguments(cm),ostream,whyNot,masterObjective);
      }

      virtual Implements_Data_Type_New<std::tuple<Args...>>  const *
      myResultType(const StructureEnv_New* cm)const
      {
        return nullptr;
      }


      template<std::size_t D>
      static void fill_imp(myC* , const dataArgumentsTuple&)
      {
      }

      template<std::size_t D>
      static void fill_imp(myC* ,std::size_t iArg, const dataArgumentsTuple&)
      {
      }


      template <std::size_t D,std::size_t I,std::size_t... Is>
      static void fill_imp(myC* v, const dataArgumentsTuple& arg)
      {
        std::get<I>(v->getTuple()).reset(std::get<I>(arg).defaultValue()->clone());
        fill_imp<D,Is...>(v,arg);
      }


      template <std::size_t D,std::size_t I,std::size_t... Is>
      static void fill_imp(myC* v, std::size_t iArg,const dataArgumentsTuple& arg)
      {
        if (I<iArg)  fill_imp<D,Is...>(v,iArg,arg);
        else
          fill_imp<D,Is...>(v,arg);
      }


      template <std::size_t... Is>
      static void fill_imp(myC* v, std::size_t iArg
                           ,const dataArgumentsTuple& arg,
                           std::index_sequence<Is...>)
      {
        fill_imp<0,Is...>(v,iArg,arg);
      }


      template <std::size_t D>
      static bool getClosure_imp(const StructureEnv_New* cm,
                                 myC* v,const dataArgumentsTuple& arg
                                 ,ABC_Input* istream,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")
      {
        return true;

      }




      template <std::size_t D,std::size_t I,size_t...Is>
      static bool getClosure_imp(const StructureEnv_New* cm,
                                 myC* v,const dataArgumentsTuple& arg
                                 ,ABC_Input* istream,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")
      {
        typedef typename std::tuple_element<I,std::tuple<Args...>>::type eType;
        const Implements_Closure_Type<eType>* clType=std::get<I>(arg).closureType(cm);
        bool mandatory=std::get<I>(arg).isMandatory();
        if (clType==nullptr)
          clType=cm->idToTypeC<eType>(Cls<eType>::name());
        ABC_R_Closure<eType>* x;

        if (!mandatory
            &&  (istream->testIfNextCharIs(')')||istream->testIfNextCharIs('\n')
                 ||istream->eof()))
          {
            fill_imp<0,Is...>(v,arg);
            return true;
          }
        else if (! clType->getClosure(cm,x,istream,whyNot,masterObjective))
          return false;
        else
          {
            std::get<I>(v->getTuple()).reset(x);
            return getClosure_imp<0,Is...>
                (cm,v,arg,istream,whyNot,masterObjective);
          }
      }



      template <std::size_t... Is>
      static bool getClosure_imp(std::index_sequence<Is...>,const StructureEnv_New* cm,
                                 myC* v
                                 ,const dataArgumentsTuple arg
                                 ,ABC_Input* istream
                                 ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")
      {
        return getClosure_imp<0,Is...>(cm,v,arg,istream,whyNot,masterObjective);
      }


      virtual bool getClosure(const StructureEnv_New* cm,
                              myC* v
                              ,ABC_Input* istream
                              ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")const
      {

        return getClosure_imp
            (std::index_sequence_for<Args...>(),cm,v,getFnArguments(cm)
             ,istream,whyNot,masterObjective);
      }


      const dataArgumentsTuple& getFnArguments(const StructureEnv_New * cm)const
      {return args_;}





      virtual ~Implements_Closure_Type_tuple(){}


      Implements_Closure_Type_tuple(Implements_Fn_Argument<Args>&&... arg)
        :args_(arg...)
      {}


      Implements_Closure_Type_tuple(dataArgumentsTuple arg={})
        :args_(arg)
      {}



      Implements_Closure_Type_tuple(const Implements_Closure_Type_tuple<Args...>& other)
        :args_(other.args_){}



      virtual bool empty() const override
      {
      }
      virtual void reset() override
      {
      }
      virtual selfType *clone() const override
      {
        return new selfType(*this);
      }
      virtual selfType *create() const override
      {
        return new selfType();
      }

    protected:
      std::tuple<Implements_Fn_Argument<Args>...>  args_;
    };
















    template<typename R, typename Fn,typename...Args>
    class Implements_Closure_Value_R_Fn_Args_Function: public ABC_R_function<R>
    {
      // ABC_Value_New interface
    public:

      typedef R returnType;

      typedef  mp_list<Args...> argumentTypes;

      typedef Implements_Closure_Value<void,Fn,R,Args...> selfType;

      virtual Implements_Closure_Type_R_Fn_Args_Function<R,Fn,Args...> const * closureType(const StructureEnv_New* cm)const override
      {
        return fnType_;
      }

      virtual Implements_Data_Type_New<R> const * resultType(const StructureEnv_New* cm)const override
      {
        return closureType(cm)->myResultType(cm);
      }

      returnType eval(Markov_CommandManagerVar* cm)const override
      {
        return mp_apply<Fn,R,Args...>(cm,f_,inputTu_->eval(cm));
      }

      const Implements_Closure_Value<std::tuple<Args...>>* getArgumentsValue()const

      {return &inputTu_;}

      Implements_Closure_Value<std::tuple<Args...>>* getArgumentsValue()
      {return &inputTu_;}


      Fn f()
      {
        return f_;
      }


      virtual bool empty() const override
      {
        return f_==nullptr;
      }

      virtual void reset() override
      {
        f_=nullptr;
        inputTu_.reset();
      }

      virtual selfType* create() const override
      {
        return new selfType();
      }
      virtual selfType* clone()const
      {
        return new selfType(*this);
      }

      virtual ~Implements_Closure_Value_R_Fn_Args_Function()
      {
      }



      Implements_Closure_Value_R_Fn_Args_Function
      (const Implements_Closure_Type_R_Fn_Args_Function<R,Fn,Args...> * idtype,
       Implements_Closure_Value<std::tuple<Args...>> vars):
        fnType_(idtype),f_(idtype->f()),inputTu_(vars){}


      Implements_Closure_Value_R_Fn_Args_Function(const selfType& other):
        fnType_(other.fnType_),f_(other.f_),inputTu_(other.inputTu_){}


      Implements_Closure_Value_R_Fn_Args_Function(Implements_Closure_Value_R_Fn_Args_Function&& other)=default;

      Implements_Closure_Value_R_Fn_Args_Function& operator=(const Implements_Closure_Value_R_Fn_Args_Function& other)=default;

      Implements_Closure_Value_R_Fn_Args_Function& operator=(Implements_Closure_Value_R_Fn_Args_Function&& other)=default;

      Implements_Closure_Value_R_Fn_Args_Function()=default;



      // ABC_Closure interface
    public:
      virtual Implements_Value_New<returnType> *evalData(Markov_CommandManagerVar* cm) const override
      {

        return new Implements_Value_New<returnType>
            (resultType(cm),eval(cm));
      }

      std::string getFunctionId(const StructureEnv_New* cm) const override
      {
        return closureType(cm)->getFunctionId();
      }

    protected:
      const Implements_Closure_Type_R_Fn_Args_Function<R,Fn,Args...>  * fnType_;
      Fn f_;
      Implements_Closure_Value<std::tuple<Args...>> inputTu_;
    };



    template<typename Fn, typename...Args>
    class Implements_Closure_Value_R_Fn_Args_Function<void,Fn,Args...>: public ABC_R_function<void>
    {
      // ABC_Value_New interface
    public:

      typedef void returnType;

      typedef  mp_list<Args...> argumentTypes;

      typedef Implements_Closure_Value<std::tuple<Args...>> argumentTuple;

      typedef Implements_Closure_Value<void,void,Fn,Args...> selfType;

      virtual Implements_Closure_Type_R_Fn_Args_Function<void,Fn,Args...> const * closureType(const StructureEnv_New* cm)const
      {
        return fnType_;
      }

      virtual Implements_Data_Type_New<void> const * resultType(const StructureEnv_New* cm)const
      {
        return closureType(cm)->myResultType(cm);
      }

      const argumentTuple* getArgumentsValue()const {return inputTu_.get();}

      argumentTuple* getArgumentsValue() {return inputTu_.get();}



      Fn f()
      {
        return f_;
      }


      virtual selfType* clone()const
      {
        return new selfType(*this);
      }

      virtual ~Implements_Closure_Value_R_Fn_Args_Function()
      {
      }


      Implements_Closure_Value_R_Fn_Args_Function
      (const Implements_Closure_Type<void,void,Fn,Args...> * idtype
       ,Implements_Closure_Value<std::tuple<Args...>>* args ):
        fnType_(idtype),f_(idtype->f()),inputTu_(args){}


      Implements_Closure_Value_R_Fn_Args_Function(const Implements_Closure_Value_R_Fn_Args_Function& other):
        fnType_(other.fnType_),f_(other.f_)
      ,inputTu_(other.inputTu_->clone()){}

      Implements_Closure_Value_R_Fn_Args_Function(Implements_Closure_Value_R_Fn_Args_Function&& other)=default;

      Implements_Closure_Value_R_Fn_Args_Function& operator=(const Implements_Closure_Value_R_Fn_Args_Function& other)=default;

      Implements_Closure_Value_R_Fn_Args_Function& operator=(Implements_Closure_Value_R_Fn_Args_Function&& other)=default;

      Implements_Closure_Value_R_Fn_Args_Function()=default;


      virtual bool empty() const override
      {
        return f_==nullptr;
      }

      virtual void reset() override
      {
        f_=nullptr;
        inputTu_.reset();
      }

      virtual selfType* create() const override
      {
        return new selfType();
      }

      returnType eval(Markov_CommandManagerVar* cm) const override
      {
        mp_apply_void<Fn,Args...>(f_,inputTu_->eval(cm));
      }
      // ABC_Closure interface
    public:
      virtual ABC_Data_New *evalData(Markov_CommandManagerVar* cm) const override
      {
        eval(cm);

        return new Implements_Value_New<void>;
      }
      //    virtual const std::vector<const ABC_Data_New *> &inputArguments() const override;

      virtual bool putMe(const StructureEnv_New* cm
                         ,ABC_Output* ostream
                         ,std::string* error,
                         const std::string& masterObjective)const
      {
        return closureType(cm)->putClosure(cm,this,ostream,error,masterObjective);
      }




      std::string getFunctionId(const StructureEnv_New * cm) const
      {
        return closureType(cm)->myFunctionType(cm)->getFunctionId();
      }







    protected:
      const Implements_Closure_Type<void,void,Fn,Args...>  * fnType_;
      Fn f_;
      std::unique_ptr<Implements_Closure_Value<std::tuple<Args...>>> inputTu_;

    };





    template<typename R,class C,typename... Args, size_t... I>
    R
    apply_Obj_Impl(C* o,R(C::*f)(Args...),
                   const std::tuple<Args...>& args
                   ,std::index_sequence<I...>)
    {
      (o->*f)(std::get<I>(args)...);
    }

    template<typename R, class C,typename...Args>
    R
    mp_apply_Obj(C* o
                 ,R(C::*f)(Args...)
                 ,const std::tuple<Args...>& args)
    {
      return apply_Obj_Impl(o,f, args,
                            std::index_sequence_for<Args...>());
    }



    class Implements_Closure_Type_Function: public ABC_Type_of_Function
    {
    public:
      typedef ABC_Closure  myC;
      typedef Implements_Closure_Type<void*> selfType;
      typedef buildClosureByToken<void*> buildType;

      virtual bool empty() const override{}
      virtual void reset() override{}
      virtual selfType *clone() const override
      {
        return new selfType(*this);
      }
      virtual selfType *create() const override
      {
        return new selfType();
      }
      virtual Implements_Closure_Type<void*> const* myFunctionType(const StructureEnv_New * cm)const override
      {
        return this;
      }

      virtual const Type_Union *  myResultType(const StructureEnv_New* cm)const override
      {
        return resultType_.get();
      }

      const std::vector<std::unique_ptr< ABC_Function_Overload>>& getOverloads (const StructureEnv_New * cm) const
      {
        return overloadTypes_;
      };




      virtual buildType* getBuildClosureByToken(
          const StructureEnv_New* cm)const override
      {
        return new buildType(cm,this);
      }




      virtual const Implements_Identifier* myFunctionIdentifier(const StructureEnv_New* )const override
      {
        return funIdType_.get();
      }

      std::string getFunctionId()const
      {
        return functionName_;
      }


      std::vector<std::unique_ptr<ABC_BuildClosure>> getOverloadBuild
      (const StructureEnv_New* cm,const ABC_Type_of_Value* vt)const;



      virtual ~Implements_Closure_Type_Function(){};


      Implements_Closure_Type_Function():
        functionName_("")
      ,funIdType_(Identifier::types::idFunct::varType("")),
        overloadTypes_()
      {}

      Implements_Closure_Type_Function
      (   const std::string functionName
          ,Implements_Identifier* idType
          )
        : functionName_(functionName)
        ,funIdType_(idType)
        ,resultType_(new Type_Union)
        ,overloadTypes_()
      {

      }

      Implements_Closure_Type_Function(const Implements_Closure_Type_Function& other):
        functionName_(other.functionName_),funIdType_(other.funIdType_->clone()),
        resultType_(other.resultType_->clone()),
        overloadTypes_(clone_vector<ABC_Function_Overload>(other.overloadTypes_)){}



      void push_overload(const StructureEnv_New* cm,
                         ABC_Function_Overload* g)
      {
        g->setFunction(this);
        overloadTypes_.emplace_back(g);
        resultType_->push_Type(g->myResultType(cm));

      }


    private:
      std::string functionName_;
      std::unique_ptr<Implements_Identifier>  funIdType_;
      std::unique_ptr<Type_Union> resultType_;
      std::vector<std::unique_ptr<ABC_Function_Overload>> overloadTypes_;
      // ABC_Data_New interface
    };






    template<class R,typename C,typename...Args>
    class Implements_Closure_Value_R_C_Args_Method: public ABC_R_function<R>
    {
      // ABC_Value_New interface
    public:

      typedef R returnType;
      typedef C objectType;

      typedef R(C::*methodType)(Args...);

      typedef  mp_list<Args...> argumentTypes;

      typedef Implements_Closure_Value<std::tuple<Args...>>  argumentValueType;

      typedef Implements_Closure_Value<R,C,void,Args...> selfType;

      virtual Implements_Closure_Type<R,C,void,Args...> const * closureType(const StructureEnv_New* cm)const
      {
        return fnType_;
      }

      virtual Implements_Data_Type_New<R> const * resultType(const StructureEnv_New* cm)const
      {
        return closureType(cm)->myResultType(cm);
      }

      returnType eval(Markov_CommandManagerVar* cm) const override
      {
        return mp_apply_Obj<R,C,Args...>
            (cm,obj_->eval(cm),f_,inputTu_->eval(cm));
      }



      const argumentValueType* getArguments()const {return inputTu_.get();}


      const Implements_Closure_Value<C,std::string>* getObject()const
      {
        return obj_.get();
      }

      methodType f()
      {
        return f_;
      }


      virtual bool empty() const override
      {
        return f_==nullptr;
      }

      virtual void reset() override
      {
        f_=nullptr;
        inputTu_=argumentValueType{};
      }

      virtual selfType* create() const override
      {
        return new selfType();
      }
      virtual selfType* clone()const
      {
        return new selfType(*this);
      }

      virtual ~Implements_Closure_Value_R_C_Args_Method()
      {
      }



      Implements_Closure_Value_R_C_Args_Method(
          const Implements_Closure_Type_R_C_Args_Method<R,C,Args...> * idtype,
          Implements_Closure_Value<C,std::string>* obj,
          std::tuple<ABC_R_Closure<Args>*... >* vars):
        fnType_(idtype),obj_(obj),f_(idtype->f()),inputTu_(vars){}


      Implements_Closure_Value_R_C_Args_Method(const Implements_Closure_Value_R_C_Args_Method& other)=default;

      Implements_Closure_Value_R_C_Args_Method(Implements_Closure_Value_R_C_Args_Method&& other)=default;

      Implements_Closure_Value_R_C_Args_Method& operator=(const Implements_Closure_Value_R_C_Args_Method& other)=default;

      Implements_Closure_Value_R_C_Args_Method& operator=(Implements_Closure_Value_R_C_Args_Method&& other)=default;

      Implements_Closure_Value_R_C_Args_Method()=default;



      // ABC_Closure interface
    public:
      virtual Implements_Value_New<returnType> *evalData(Markov_CommandManagerVar* cm) const override
      {

        return new Implements_Value_New<returnType>
            (resultType(cm),eval(cm));
      }

      std::string getFunctionId(const StructureEnv_New* cm) const override
      {
        return closureType(cm)->getFunctionId();
      }

    protected:
      const Implements_Closure_Type<C,void,R,Args...>  * fnType_;
      std::unique_ptr<Implements_Closure_Value<C, std::string>> obj_;
      methodType f_;
      std::unique_ptr<Implements_Closure_Value<std::tuple<Args...>>> inputTu_;
    };




    template<typename R, typename Fn,typename...Args>
    class Implements_Closure_Type_R_Fn_Args_Function: public ABC_Function_Overload
    {

      // ABC_Value_New interface
    public:
      typedef Implements_Closure_Value<R,void,Fn,Args...> myC;

      typedef Fn functionType;
      typedef Implements_Data_Type_New<R> resultType;

      typedef buildClosureByToken<R,void,Fn,Args...> buildType;
      typedef  mp_list<Args...> argumentTypes;

      typedef Implements_Closure_Type<R,void,Fn,Args...> selfType;

      virtual const Implements_Data_Type_New<R> *  myResultType(const StructureEnv_New* cm)const
      {
        return resultType_;
      }



      virtual functionType f() const
      {
        return f_;
      }


      virtual selfType* clone()const
      {
        return new selfType(*this);
      }

      virtual ~Implements_Closure_Type_R_Fn_Args_Function()
      {
      }



      Implements_Closure_Type_R_Fn_Args_Function
      (const resultType* resultType,
       Fn f,
       Implements_Closure_Type<std::tuple<Args...>>* argType):
        functionType_(nullptr),resultType_(resultType),f_(f),argType_(argType)
      {}


      void setFunction(const Implements_Closure_Type<void*>* f) override
      {
        functionType_=f;
      }

      Implements_Closure_Type_R_Fn_Args_Function(const Implements_Closure_Type_R_Fn_Args_Function& other)=default;


      Implements_Closure_Type_R_Fn_Args_Function(Implements_Closure_Type_R_Fn_Args_Function&& other)=default;

      Implements_Closure_Type_R_Fn_Args_Function& operator=(const Implements_Closure_Type_R_Fn_Args_Function& other)=default;

      Implements_Closure_Type_R_Fn_Args_Function& operator=(Implements_Closure_Type_R_Fn_Args_Function&& other)=default;



      virtual bool empty() const override
      {
        return f_==nullptr;
      }

      virtual void reset() override
      {
        f_=nullptr;
      }

      virtual selfType* create() const override
      {
        return nullptr;

      }




    public:
      virtual buildType *getBuildClosureByToken(const StructureEnv_New *cm) const override
      {
        return new buildType(cm,this);

      }


      virtual const Implements_Closure_Type<std::tuple<Args...>>*
      getArgumentsType(const StructureEnv_New * cm)const
      {
        return argType_;
      }






      virtual bool putClosure(const StructureEnv_New* cm
                              ,const myC* c
                              ,ABC_Output* ostream
                              ,std::string* whyNot
                              , const std::string& masterObjective)const
      {
        if (! getFnIdType(cm)->putValue(cm,c->getFunctionId(cm),ostream,whyNot,masterObjective))
          return false;
        else if (!getArgumentsType(cm)->putClosure
                 (cm,c->getArgumentsValue(),ostream,whyNot,masterObjective))
          {
            return false;
          }
        else return true;
      }

      virtual bool getClosure(const StructureEnv_New* cm
                              ,myC* v
                              , ABC_Input* istream
                              ,std::string* whyNot
                              ,const std::string& masterObjective )const
      {
        std::string idFn;
        Implements_Closure_Value<std::tuple<Args...>>* args;
        if (! getFnIdType( cm)->getValue(cm,idFn,istream,whyNot,masterObjective))
          return false;
        else if (!getArgumentsType(cm)->getClosure
                 (cm,args,istream,whyNot,masterObjective))
          {
            return false;
          }
        else
          {
            v= new myC(this,args);
            return true;
          }
      }


      virtual const Implements_Identifier *myFunctionIdentifier(const StructureEnv_New * cm) const override
      {
        return myFunctionType(cm)->myFunctionIdentifier(cm);
      }


      const Implements_Closure_Type<void*>*  myFunctionType(const StructureEnv_New * cm) const override
      {
        return functionType_;
      }





      Implements_Identifier const * getFnIdType(const StructureEnv_New* cm)const
      {
        return myFunctionType(cm)->myFunctionIdentifier(cm);
      }



    protected:
      Fn f_;
      const resultType* resultType_;
      Implements_Closure_Type<std::tuple<Args...>>* argType_;
      const Implements_Closure_Type<void*>*  functionType_;

      // ABC_Type_of_Function interface
    };




    template<class R, typename C,typename...Args>
    class Implements_Closure_Type_R_C_Args_Method : public ABC_Type_of_C_Method<C>
    {

      // ABC_Value_New interface
    public:
      typedef Implements_Closure_Value<R,C,void,Args...> myC;

      typedef  R (C::*methodType)(Args...);
      typedef R returnType;
      typedef C objectType;

      typedef buildClosureByToken<C,R,void,Args...> buildType;

      typedef  mp_list<Args...> argumentTypes;


      typedef Implements_Closure_Type<R,C,void,Args...> selfType;

      virtual const Implements_Data_Type_New<returnType>* resultType(const StructureEnv_New* cm)const override
      {
        return resultType_;
      }



      virtual methodType f() const
      {
        return f_;
      }

      virtual const Implements_Identifier* myMethodIdentifier(const StructureEnv_New* cm)const override
      {
        return this->myMethodType(cm)->getMethodIdentifier(cm);
      }

      virtual Implements_Closure_Type<void*,C> const* myMethodType(const StructureEnv_New* cm)const
      {
        return myMethodType_;
      }

      virtual Implements_Closure_Type<C,std::string> const * myObjectIdentifier(const StructureEnv_New* cm)const
      {
        return myMethodType(cm)->myObejectIdentifier(cm);
      }


      virtual Implements_Closure_Type<std::tuple<Args...>> const *
      myArgumentsType(const StructureEnv_New* cm)const
      {
        return myArgumentsType_;
      }


      virtual selfType* clone()const
      {
        return new selfType(*this);
      }

      virtual ~Implements_Closure_Type_R_C_Args_Method()
      {
      }




      Implements_Closure_Type_R_C_Args_Method
      (const StructureEnv_New* cm,
       methodType m
       ,const Implements_Closure_Type<std::tuple<Args...>>* inputArg
       ,Implements_Data_Type_New<returnType>const * myresultType):
        f_(m),resultType_(myresultType)
      ,myArgumentsType_(inputArg)
      {}



      Implements_Closure_Type_R_C_Args_Method(Implements_Closure_Type_R_C_Args_Method&& other)=default;

      Implements_Closure_Type_R_C_Args_Method& operator=(const Implements_Closure_Type_R_C_Args_Method& other)=default;

      Implements_Closure_Type_R_C_Args_Method& operator=(Implements_Closure_Type_R_C_Args_Method&& other)=default;



      virtual bool empty() const override
      {
        return f_==nullptr;
      }

      virtual void reset() override
      {
        f_=nullptr;
      }

      virtual selfType* create() const override
      {
        return new selfType();

      }



    public:
      virtual buildType *getBuildClosureByToken(const StructureEnv_New *cm) const override
      {
        return new buildType(cm,this);

      }



      virtual bool putClosure(const StructureEnv_New* cm
                              ,const myC* c
                              ,ABC_Output* ostream
                              ,std::string* whyNot
                              , const std::string& masterObjective)const
      {

        if (! myMethodIdentifier(cm)->putValue
            (cm,c->closureType(cm)->myMetodType(cm)->myMethodName()
             ,ostream,whyNot,masterObjective))
          return false;
        else if (!myArgumentsType(cm)->putClosure(cm,c->getArguments(),ostream,whyNot,masterObjective))
          {
            return false;
          }
        else return true;
      }

      virtual bool getClosure(const StructureEnv_New* cm
                              ,myC* v
                              , ABC_Input* istream
                              ,std::string* whyNot
                              ,const std::string& masterObjective )const
      {
        Implements_Closure_Value<C,std::string>* idObj;
        std::string idMethod;
        if (! myObjectIdentifier(cm)->getClosure(cm,idObj,istream,whyNot,masterObjective))
          return false;
        else if (!myMethodIdentifier(cm)->getValue(cm,idMethod,istream,whyNot,masterObjective))
          {
            return false;
          }
        else
          {
            Implements_Closure_Value<std::tuple<Args...>>* args;
            if (!myArgumentsType(cm)->getClosure(cm,args,istream,whyNot,masterObjective))
              return false;
            else
              {
                v=new myC(this,idObj,args);
                return true;
              }
          }
      }


    protected:
      const Implements_Closure_Type<void,C>*  myMethodType_;
      const Implements_Data_Type_New<returnType>* resultType_;
      methodType f_;
      Implements_Closure_Type<std::tuple<Args...>> myArgumentsType_;
    };





    template<class C>
    class Implements_Closure_Type_C_Method: public ABC_Type_of_C_Method<C>
    {

      // ABC_Data_New interface
    public:
      typedef ABC_Closure*  myC;

      typedef Implements_Closure_Type<void*,C> selfType;

      typedef buildClosureByToken<void*,C> buildType;

      virtual bool empty() const override{}
      virtual void reset() override{}

      virtual selfType *clone() const override{
        return new selfType(*this);
      }
      virtual selfType *create() const override
      {
        return new selfType();
      }



      virtual Implements_Data_Type_New<C> const * typeOfObject(const StructureEnv_New* cm)const
      {
        return myObjectIdentifier(cm)->resultType(cm);
      }

      virtual Implements_Closure_Type<C,std::string> const * myObjectIdentifier(const StructureEnv_New* cm)const
      {
        return myObjectIdentifier_;
      }

      virtual Implements_Closure_Type<void*,C> const* myMethodType()const
      {
        return this;
      }




      virtual const Implements_Identifier* myMethodIdentifier(const StructureEnv_New* cm)const
      {
        return methodIdentifier_;
      }



      virtual buildType* getBuildClosureByToken(
          const StructureEnv_New* cm)const override
      {
        return new buildType(cm,this);
      }



      std::string myMethodName()const
      {
        return methodName_;
      }


      virtual const std::vector<const ABC_Type_of_C_Method<C>*>& getOverloadMethods()const
      {
        return overloadMethods_;
      }

      virtual std::vector<std::unique_ptr<ABC_BuildClosure>>
      getOverloadBuild(const StructureEnv_New* cm,
                       const ABC_Type_of_Value* vt=nullptr)const
      {
        std::size_t n=getOverloadMethods().size();
        std::vector<std::unique_ptr<ABC_BuildClosure>> out;
        for (std::size_t i=0; i<n; ++i)
          {
            if ((vt==nullptr)
                ||(vt->includesThisType(cm,getOverloadMethods()[i]->myResultType(cm)->myTypeId())))
              out.emplace_back(getOverloadMethods()[i]->getBuildByToken(cm));
          }
        return out;
      }



      virtual ~Implements_Closure_Type_C_Method(){};


      Implements_Closure_Type_C_Method(){}

      Implements_Closure_Type_C_Method (std::string methodName,
                                        Implements_Identifier*  methodIdentifier,
                                        Implements_Closure_Type<C,std::string> const * myObjectIdentifier,
                                        std::vector<const ABC_Type_of_C_Method<C>*> overloadMethods)
        : methodName_(methodName),methodIdentifier_(methodIdentifier)
        ,myObjectIdentifier_(myObjectIdentifier),overloadMethods_(overloadMethods){}




    private:
      std::string methodName_;
      Implements_Identifier*  methodIdentifier_;
      Implements_Closure_Type<C,std::string> const * myObjectIdentifier_;

      std::vector<const ABC_Type_of_C_Method<C>*> overloadMethods_;

      // ABC_Data_New interface
    };





    template<typename R>
    class Implements_Closure_Type_ABC_R_Closure
        : public ABC_Type_of_Function
    {


      // ABC_Data_New interface
    public:
      typedef ABC_R_Closure<R>  myC;

      typedef Implements_Closure_Type<R> selfType;

      virtual bool empty() const override{}
      virtual void reset() override{}




      virtual const std::vector<ABC_Type_of_Function*>& getOverloadTypes()const
      {
        return overrideTypes_;
      }

      virtual std::vector<std::unique_ptr<ABC_BuildClosure>> getOverloadBuild(const StructureEnv_New* cm,
                                                                              const ABC_Type_of_Value* vt=nullptr)const
      {
        std::size_t n=getOverloadTypes().size();
        std::vector<std::unique_ptr<ABC_BuildClosure>> out;
        for (std::size_t i=0; i<n; ++i)
          {
            if ((vt==nullptr)||(vt->includesThisType(getOverloadTypes()[i]->myTypeId())))
              out.push_back(getOverloadTypes()[i]->getBuildByToken(cm));
          }
        return out;

      }



      virtual ~Implements_Closure_Type_ABC_R_Closure(){};


      Implements_Closure_Type_ABC_R_Closure():
        functionName_(""),typeType_(nullptr)
      ,funIdType_(Identifier::types::idFunct::varType("")),overrideTypes_()
      {}
      Implements_Closure_Type_ABC_R_Closure (const std::string functionName,const selfType* typeType,
                                             Implements_Identifier* idType
                                             , std::vector<ABC_Type_of_Function*> overrideTypes
                                             )
        : functionName_(functionName),typeType_(typeType),funIdType_(idType),overrideTypes_(overrideTypes)
      {}



      virtual bool putClosure(const StructureEnv_New* cm
                              ,const myC* c
                              ,ABC_Output* ostream
                              ,std::string* whyNot
                              , const std::string& masterObjective)const
      {

      }





    private:
      std::string functionName_;
      const selfType*  typeType_;
      Implements_Identifier*  funIdType_;
      std::vector<ABC_Type_of_Function*> overrideTypes_;

      // ABC_Data_New interface
    };


    template <typename T>
    class Implements_Closure_Type_R_function: public ABC_Type_of_R_Closure<T>
    {

      // ABC_Data_New interface
    public:
      typedef ABC_R_function<T>  myC;

      typedef Implements_Closure_Type<T,void*> selfType;

      typedef buildClosureByToken<T,void*> buildType;

      virtual bool empty() const override{}
      virtual void reset() override{}
      virtual selfType *clone() const override{
        return new selfType(*this);
      }
      virtual selfType *create() const override
      {
        return new selfType();
      }


      virtual bool putClosure(const StructureEnv_New* cm
                              ,const myC* v
                              ,ABC_Output* ostream
                              ,std::string* error,
                              const std::string& masterObjective)const {

      }

      virtual bool getClosure(const StructureEnv_New* cm
                              ,myC*& v
                              , ABC_Input* istream
                              ,std::string* error
                              , const std::string& masterObjective)const {}


      virtual buildType* getBuildClosureByToken(
          const StructureEnv_New* cm)const override
      {
        return new buildType(cm,this);
      }


      Implements_Closure_Type_R_function(){}

      virtual const Implements_Data_Type_New<T> *myResultType(const StructureEnv_New *cm) const override
      {
        return type_;
      }

      void push_function (const Implements_Closure_Type<void*>* f)
      {
        fns_.push_back(f);
      }

      void push_method (const ABC_Type_of_Method* m)
      {
        mtds_.push_back(m);
      }

      Implements_Closure_Type_R_function(const Implements_Data_Type_New<T>* type)
        : type_(type),fns_(),mtds_(){}

    private:
      const Implements_Data_Type_New<T>* type_;
      std::vector<const Implements_Closure_Type<void*> *> fns_;
      std::vector<const ABC_Type_of_Method*> mtds_;
    };







    template <typename R>
    class Implements_Closure_Type_ABC_R: public ABC_Type_of_R_Closure<R>
    {
      // ABC_Data_New interface
    public:
      typedef ABC_R_Closure<R>  myC;

      typedef Implements_Closure_Type<R> selfType;
      typedef buildClosureByToken<R> buildType;

      virtual bool empty() const override{}
      virtual void reset() override{}
      virtual selfType *clone() const override
      {
        return new selfType(*this);
      }
      virtual selfType *create() const override
      {
        return new selfType();
      }

      virtual bool putClosure(const StructureEnv_New* cm
                              ,const myC* v
                              ,ABC_Output* ostream
                              ,std::string* error,
                              const std::string& masterObjective)const
      {
        return v->putMe(cm,ostream,error,masterObjective);

      }

      virtual bool getClosure(const StructureEnv_New* cm
                              ,myC*& v
                              , ABC_Input* istream
                              ,std::string* error
                              , const std::string& masterObjective)const
      {

        Implements_Closure_Value<R, std::string>* idV;
        if (myIdentifierType(cm)->getClosure(cm,idV,istream,error,masterObjective))
          {
            v=idV;
            return true;
          }
        else
          {
            Implements_Closure_Value<R, int>* cV;
            if  (myConstantType(cm)->getClosure(cm,cV,istream,error,masterObjective))
              {
                v=cV;
                return true;
              }
            else
              {
                Implements_Closure_Value<R, void*>* fV;
                if (myFunctionType(cm)->getClosure(cm,fV,istream,error,masterObjective))
                  {
                    v=fV;
                    return true;
                  }
                else return false;
              }
          }
      }


      virtual buildType* getBuildClosureByToken(
          const StructureEnv_New* cm)const override
      {
        return new buildType(cm,this);
      }

      virtual Implements_Data_Type_New<R>  const *  myResultType(const StructureEnv_New *cm) const override
      {
        return myIdentifierType(cm)->myResultType(cm);
      }


      const Implements_Closure_Type<R,int>*
      myConstantType(const StructureEnv_New* cm)const
      {
        return cType_.get();
      }
      const Implements_Closure_Type<R,std::string>*
      myIdentifierType(const StructureEnv_New* cm)const
      {
        return idtype_.get();
      }
      const Implements_Closure_Type<R,void*>*
      myFunctionType(const StructureEnv_New* cm)const
      {
        return fnType_.get();
      }



      virtual ~Implements_Closure_Type_ABC_R(){};



      Implements_Closure_Type_ABC_R(){}

      Implements_Closure_Type_ABC_R
      ( Implements_Closure_Type<R,int>* cType,
        Implements_Closure_Type<R,std::string>* idtype,
        Implements_Closure_Type<R,void*>* fnType)
        :cType_(cType),idtype_(idtype),fnType_(fnType){}


      Implements_Closure_Type_ABC_R(const Implements_Data_Type_New<R>* dType)
        : Implements_Closure_Type_ABC_R
          (new Implements_Closure_Type<R,int>(dType)
           ,new Implements_Closure_Type<R,std::string>(dType)
           ,new Implements_Closure_Type<R,void*>(dType)){}


      Implements_Closure_Type_ABC_R(const Implements_Closure_Type_ABC_R& other)
        :cType_(other.cType_->clone())
        ,idtype_(other.idtype_->clone())
        ,fnType_(other.fnType_->clone()){}
      Implements_Closure_Type_ABC_R( Implements_Closure_Type_ABC_R&& other)=default;
      Implements_Closure_Type_ABC_R& operator=( Implements_Closure_Type_ABC_R&& other)=default;
      Implements_Closure_Type_ABC_R& operator=(const Implements_Closure_Type_ABC_R& other)=default;


    private:
      std::unique_ptr<Implements_Closure_Type<R,int>> cType_;
      std::unique_ptr<Implements_Closure_Type<R,std::string>> idtype_;
      std::unique_ptr<Implements_Closure_Type<R,void*>> fnType_;


      // ABC_Type_of_Closure interface
    };







    class Implements_Closure_Value_Markov_CommandManagerVar_Self: public ABC_R_Closure<Markov_CommandManagerVar*>

    {
      // ABC_Value_New interface
    public:

      typedef Markov_CommandManagerVar* returnType;

      typedef Implements_Closure_Value_Markov_CommandManagerVar_Self selfType;



      virtual returnType eval(Markov_CommandManagerVar* cm) const override
      {
        return cm;
      }

      virtual ~Implements_Closure_Value_Markov_CommandManagerVar_Self()
      {
      }

      // ABC_Closure interface

      // ABC_Data_New interface
    public:
      virtual bool empty() const override{return false;}
      virtual void reset() override{}

      virtual bool putMe(const StructureEnv_New* cm
                         ,ABC_Output* ostream
                         ,std::string* error,
                         const std::string& masterObjective)const override
      {
        return true;
      }

      virtual selfType *clone() const override{return new selfType();}
      virtual selfType *create() const override {return new selfType();}
      virtual std::string functionId()const{}


      virtual ABC_Data_New *evalData(Markov_CommandManagerVar *cm) const override
      {
        return nullptr;
      }

      virtual ABC_Type_of_Closure const* closureType(const StructureEnv_New* cm)const override
      {
        return nullptr;
      }

      virtual Implements_Data_Type_New<returnType> const * resultType(const StructureEnv_New* cm)const override{
        return nullptr;
      }

    };






  };


};



#endif // IMPLEMENTS_CLOSURES_H
