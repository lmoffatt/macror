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
    ,defaultValue_(other.defaultValue_?other.defaultValue_->clone():nullptr),isDefaulted_(other.isDefaulted_),
      tip_(other.tip_),whatThis_(other.whatThis_){}
    Implements_Fn_Argument( Implements_Fn_Argument&& other)=default;
    Implements_Fn_Argument& operator=(const Implements_Fn_Argument& other)=default;
    Implements_Fn_Argument& operator=(Implements_Fn_Argument&& other)=default;



    template <class argType>
    Implements_Fn_Argument(const argType& a,const StructureEnv_New *cm,
                           std::string id,
                           const std::string& tip
                           ,const std::string& whatthis):
      Implements_Fn_Argument(id,
                             cm->idToTypeC<T>(argType::myId()),
                             nullptr,tip,whatthis){}




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

    typedef ABC_Closure returnedClosure;

    typedef ABC_Type_of_Closure selfType;

    typedef ABC_BuildClosure buildType;

    virtual bool empty()const =0;

    virtual void reset()=0;

    virtual ABC_Type_of_Closure* clone()const=0;
    virtual ABC_Type_of_Closure* create()const=0;


    virtual ~ABC_Type_of_Closure()
    {
    }


    virtual bool getClosure(const StructureEnv_New* cm
                            ,ABC_Closure*& cl
                            , ABC_Input* istream
                            ,std::string* whyNot
                            ,const std::string& masterObjective )const=0;



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
    typedef ABC_BuildClosure buildClosure;
    typedef ABC_Type_of_Value myType_of_Value;
    virtual ~ABC_Function_Overload(){}
    virtual   void setFunction(const Implements_Closure_Type<void*>* f)=0;
    virtual bool fillArguments(const StructureEnv_New* cm
                               ,ABC_Closure*& cl
                               , ABC_Input* istream
                               ,std::string* whyNot
                               ,const std::string& masterObjective )const=0;

    virtual ABC_Function_Overload* clone()const=0;
    virtual ABC_Function_Overload* create()const=0;

  };

  template <typename R>
  class ABC_Function_R_Overload: public ABC_Function_Overload
  {
  public:
    typedef ABC_BuildClosure_R<R> buildClosure;
    typedef Implements_Data_Type_New<R> myType_of_Value;
    typedef ABC_R_Closure<R> returnedClosure;


    virtual ~ABC_Function_R_Overload(){}
    virtual ABC_Function_R_Overload* clone()const=0;
    virtual ABC_Function_R_Overload* create()const=0;
    virtual const Implements_Data_Type_New<R> *  myResultType(const StructureEnv_New* cm)const=0;
    virtual bool getClosure_R(const StructureEnv_New* cm
                              ,ABC_R_Closure<R>*& cl
                              , ABC_Input* istream
                              ,std::string* whyNot
                              ,const std::string& masterObjective )const=0;

    virtual bool fillArguments_R(const StructureEnv_New* cm
                                 ,ABC_R_Closure<R>*& cl
                                 , ABC_Input* istream
                                 ,std::string* whyNot
                                 ,const std::string& masterObjective )const=0;


    virtual buildClosure *getBuildClosureByToken(const StructureEnv_New *cm) const override=0;

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

    virtual bool getClosure_R(const StructureEnv_New* cm
                              ,ABC_R_Closure<R>*& cl
                              , ABC_Input* istream
                              ,std::string* whyNot
                              ,const std::string& masterObjective )const=0;

  };





  template <class...T> class buildClosureByToken;


  namespace _private
  {

    template <typename T>
    class Implements_Closure_Type_T_Identifier: public ABC_Type_of_R_Closure<T>
    {


      // ABC_Data_New interface
    public:
      typedef Implements_Closure_Value<T, std::string> myC;


      typedef Implements_Closure_Type<T,std::string> selfType;

      typedef buildClosureByToken<T,std::string> buildClosure;


      virtual bool empty() const override
      {
        return resultType_==nullptr;
      }
      virtual void reset() override{
        resultType_=nullptr;

      }

      virtual bool putClosureValue(const StructureEnv_New* cm
                                   ,const myC* v
                                   ,ABC_Output* ostream
                                   ,std::string* error,
                                   const std::string& masterObjective)const
      {
        return getIdentifierType(cm)
            ->putValue(cm,v->getIdentifier(),ostream,error,masterObjective);

      }

      virtual bool getClosureValue(const StructureEnv_New* cm
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

      virtual bool getClosure(const StructureEnv_New* cm
                              ,ABC_Closure*& cl
                              , ABC_Input* istream
                              ,std::string* whyNot
                              ,const std::string& masterObjective )const override
      {
        myC* v;
        if (getClosureValue(cm,v,istream,whyNot,masterObjective))
          {
            cl=v;
            return true;
          }
        else return false;
      }
      virtual bool getClosure_R(const StructureEnv_New* cm
                                ,ABC_R_Closure<T>*& cl
                                , ABC_Input* istream
                                ,std::string* whyNot
                                ,const std::string& masterObjective )const override
      {
        myC* v;
        if (getClosureValue(cm,v,istream,whyNot,masterObjective))
          {
            cl=v;
            return true;
          }
        else return false;
      }



      virtual buildClosure* getBuildClosureByToken(
          const StructureEnv_New* cm)const override
      {
        return new buildClosure(cm,this);
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





    template <typename R>
    class Implements_Closure_Type_T_Constant:  public ABC_Type_of_R_Closure<R>
    {


      // ABC_Data_New interface
    public:
      typedef Implements_Closure_Value<R,int> myC;

      typedef Implements_Closure_Type<R,int> selfType;

      typedef buildClosureByToken<R,int> buildClosure;


      virtual bool empty() const override{
        return (varType_==nullptr)||(varType_->empty());
      }
      virtual void reset() override{
        varType_=nullptr;
      }

      virtual selfType *clone() const override{ return new selfType(*this);}
      virtual selfType *create() const override{ return new selfType();}


      virtual bool putClosureValue(const StructureEnv_New* cm
                                   ,const myC* v
                                   ,ABC_Output* ostream
                                   ,std::string* error,
                                   const std::string& masterObjective)const
      {
        return myResultType(cm)->putValue(cm,v->getData(),ostream,error,masterObjective);
      }

      virtual bool getClosureValue(const StructureEnv_New* cm
                                   ,myC*& v
                                   , ABC_Input* istream
                                   ,std::string* error
                                   , const std::string& masterObjective)const
      {
        R x;
        if (myResultType(cm)->getValue(cm,x,istream,error,masterObjective))
          {
            v=new myC(this,x);
            return true;
          }
        else return false;
      }

      virtual bool getClosure(const StructureEnv_New* cm
                              ,ABC_Closure*& cl
                              , ABC_Input* istream
                              ,std::string* whyNot
                              ,const std::string& masterObjective )const override
      {
        myC* v;
        if (getClosureValue(cm,v,istream,whyNot,masterObjective))
          {
            cl=v;
            return true;
          }
        else return false;
      }

      virtual bool getClosure_R(const StructureEnv_New* cm
                                ,ABC_R_Closure<R>*& cl
                                , ABC_Input* istream
                                ,std::string* whyNot
                                ,const std::string& masterObjective )const override
      {
        myC* v;
        if (getClosureValue(cm,v,istream,whyNot,masterObjective))
          {
            cl=v;
            return true;
          }
        else return false;
      }


      virtual const Implements_Data_Type_New<R> *  myResultType(const StructureEnv_New* cm)const override
      {
        if (varType_==nullptr)
          return cm->idToTyped<R>(Cls<R>::name());
        else
          return varType_;
      }



      virtual buildClosure* getBuildClosureByToken(
          const StructureEnv_New* cm)const override
      {
        return new buildClosure(cm,this);
      }



      Implements_Closure_Type_T_Constant(const Implements_Data_Type_New<R>* varType)
        :varType_(varType){}

      Implements_Closure_Type_T_Constant()
        :varType_(nullptr){}

    private:
      const Implements_Data_Type_New<R>* varType_;
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


      std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>& getTuple()
      {
        return clData_;
      }
      const std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>& getTuple() const
      {
        return clData_;
      }


      std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...> unloadTuple()
      {
        auto out=std::move(clData_);
        clData_={};
        iArg_=0;
        return std::move(out);
      }


      ///
      /// \brief iArg number of arguments actually filled instead of using default
      /// \return the value of this number
      ///

      std::size_t iArg()const {return iArg_;}


      virtual bool putMe(const StructureEnv_New* cm
                         ,ABC_Output* ostream
                         ,std::string* error,
                         const std::string& masterObjective)const
      {
        return closureType(cm)->putClosureValue(cm,this,ostream,error,masterObjective);
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
        const std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>& clData,
        std::size_t iArg)
        : clType_(clType),clData_(clone_tuple(clData)),iArg_(iArg){}


      Implements_Closure_Value_tuple(const Implements_Closure_Type<myC> * clType)
        : clType_(clType),clData_(),iArg_(0){}

      Implements_Closure_Value_tuple()
        : clType_(),clData_(),iArg_(0){}

      Implements_Closure_Value_tuple(const Implements_Closure_Value_tuple& other)
        : clType_(other.clType_),clData_(clone_tuple(other.clData_)),iArg_(other.iArg_){}

      Implements_Closure_Value_tuple( Implements_Closure_Value_tuple&& other)=default;
      Implements_Closure_Value_tuple& operator=(const Implements_Closure_Value_tuple& other)=default;
      Implements_Closure_Value_tuple& operator=(Implements_Closure_Value_tuple&& other)=default;



      // ABC_R_Closure interface
    public:
      virtual std::tuple<Args...> eval(Markov_CommandManagerVar *cm) const  override
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
      std::size_t iArg_;

    };



    template<typename... Args>
    class Implements_Closure_Type_tuple:public ABC_Type_of_R_Closure<std::tuple<Args...>>
    {
    public:
      typedef Implements_Closure_Value<std::tuple<Args...>> myC;
      typedef Implements_Closure_Type<std::tuple<Args...>> selfType;

      typedef buildClosureByToken<std::tuple<Args...>> buildClosure;

      typedef std::tuple<Implements_Fn_Argument<Args>...> dataArgumentsTuple;



      virtual buildClosure* getBuildClosureByToken(
          const StructureEnv_New* cm)const override
      {
        return new buildClosure(cm,this);
      }


      template <std::size_t D>
      static bool putClosureValue_imp(const StructureEnv_New* cm,
                                      const myC* v
                                      ,const dataArgumentsTuple arg
                                      ,ABC_Output* ostream
                                      ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")
      {
        return true;

      }


      template <std::size_t D,std::size_t I, std::size_t... Is>
      static bool putClosureValue_imp(const StructureEnv_New* cm,
                                      const myC* v
                                      ,const dataArgumentsTuple arg
                                      ,ABC_Output* ostream
                                      ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")
      {

        auto& e=std::get<I>(v->getTuple());

        if (! e->putMe(cm,ostream,whyNot,masterObjective))
          return false;
        else
          return putClosureValue_imp<D,Is...>(cm,v,arg,ostream,whyNot,masterObjective);

      }




      template <std::size_t... Is>
      static bool putClosureValue_imp(std::index_sequence<Is...>,const StructureEnv_New* cm,
                                      const myC* v
                                      ,const dataArgumentsTuple arg
                                      ,ABC_Output* ostream
                                      ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")
      {
        return putClosureValue_imp<0,Is...>(cm,v,arg,ostream,whyNot,masterObjective);
      }


      virtual bool putClosureValue(const StructureEnv_New* cm,
                                   const myC* v
                                   ,ABC_Output* ostream
                                   ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")const
      {

        return putClosureValue_imp
            (std::index_sequence_for<Args...>()
             ,cm,v,getFnArguments(cm),ostream,whyNot,masterObjective);
      }

      virtual void fill(const StructureEnv_New * cm,
                        std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>& v,
                        std::size_t iArg) const
      {
        fill_imp(v,iArg,getFnArguments(cm),std::index_sequence_for<Args...>());
      }


      virtual Implements_Data_Type_New<std::tuple<Args...>>  const *
      myResultType(const StructureEnv_New* cm)const
      {
        return nullptr;
      }


      template<std::size_t D>
      static void fill_imp( std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>& v,
                            const dataArgumentsTuple&)
      {
      }

      template<std::size_t D>
      static void fill_imp( std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>& v,
                            std::size_t iArg, const dataArgumentsTuple&)
      {
      }


      template <std::size_t D,std::size_t I,std::size_t... Is>
      static void fill_imp(
          std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>& v,
          const dataArgumentsTuple& arg)
      {
        std::get<I>(v).reset(std::get<I>(arg).defaultValue()->clone());
        fill_imp<D,Is...>(v,arg);
      }


      template <std::size_t D,std::size_t I,std::size_t... Is>
      static void fill_imp(
          std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>& v,
          std::size_t iArg,const dataArgumentsTuple& arg)
      {
        if (I<iArg)  fill_imp<D,Is...>(v,iArg,arg);
        else
          fill_imp<D,I,Is...>(v,arg);
      }


      template <std::size_t... Is>
      static void fill_imp(
          std::tuple<std::unique_ptr<ABC_R_Closure<Args>>...>& v,
          std::size_t iArg
          ,const dataArgumentsTuple& arg,
          std::index_sequence<Is...>)
      {
        fill_imp<0,Is...>(v,iArg,arg);
      }


      template <std::size_t D>
      static bool getClosureValue_imp(const StructureEnv_New* cm,
                                      myC* v,const dataArgumentsTuple& arg
                                      ,ABC_Input* istream,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")
      {

        return (istream->nextCharIs(')',false)||istream->testIfNextCharIs('\n')
                ||istream->eof());

      }




      template <std::size_t D,std::size_t I,size_t...Is>
      static bool getClosureValue_imp(const StructureEnv_New* cm,
                                      myC* v,const dataArgumentsTuple& arg
                                      ,ABC_Input* istream,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")
      {
        typedef typename std::tuple_element<I,std::tuple<Args...>>::type eType;
        const Implements_Closure_Type<eType>* clType=std::get<I>(arg).closureType(cm);

        Implements_Fn_Argument<eType> aT=std::get<I>(arg);

        if (aT.isDefaulted())
          {
            std::get<I>(v->getTuple()).reset(aT.defaultValue());
            return getClosureValue_imp<0,Is...>
                (cm,v,arg,istream,whyNot,masterObjective);

          }
        else
          {
            bool mandatory=std::get<I>(arg).isMandatory();
            if (clType==nullptr)
              clType=cm->idToTypeC<eType>(Cls<eType>::name());
            ABC_R_Closure<eType>* x;

            if (!mandatory
                &&  (istream->nextCharIs(')',false)||istream->testIfNextCharIs('\n')
                     ||istream->eof()))
              {
                fill_imp<0,I,Is...>(v->getTuple(),arg);
                return true;
              }
            else if (! clType->getClosure_R(cm,x,istream,whyNot,masterObjective))
              return false;
            else
              {
                std::get<I>(v->getTuple()).reset(x);
                return getClosureValue_imp<0,Is...>
                    (cm,v,arg,istream,whyNot,masterObjective);
              }
          }
      }



      template <std::size_t... Is>
      static bool getClosureValue_imp(std::index_sequence<Is...>,const StructureEnv_New* cm,
                                      myC* v
                                      ,const dataArgumentsTuple arg
                                      ,ABC_Input* istream
                                      ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")
      {
        return getClosureValue_imp<0,Is...>(cm,v,arg,istream,whyNot,masterObjective);
      }


      virtual bool getClosureValue(const StructureEnv_New* cm,
                                   myC* v
                                   ,ABC_Input* istream
                                   ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")const
      {
        char c;
        if (!istream->nextCharIs('(',c))
          {
            if (whyNot!=nullptr)
              *whyNot=masterObjective+": expected ( found: "+c;
            return false;
          }
        else
        return getClosureValue_imp
            (std::index_sequence_for<Args...>(),cm,v,getFnArguments(cm)
             ,istream,whyNot,masterObjective);
      }
      virtual bool getClosure(const StructureEnv_New* cm,
                              ABC_Closure*& cl
                              ,ABC_Input* istream
                              ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")const override
      {
        myC* v;
        if (getClosureValue(cm,v,istream,whyNot,masterObjective))
          {
            cl=v;
            return true;
          }
        else
          return false;
      }


      virtual bool getClosure_R(const StructureEnv_New* cm,
                                ABC_R_Closure<std::tuple<Args...>>*& cl
                                ,ABC_Input* istream
                                ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")const override
      {
        myC* v=new myC;
        if (getClosureValue(cm,v,istream,whyNot,masterObjective))
          {
            cl=v;
            return true;
          }
        else
          return false;
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
    class Implements_Closure_Value_R_Fn_Args_Function: public ABC_R_Closure<R>
    {
      // ABC_Value_New interface
    public:

      typedef R returnType;

      typedef  mp_list<Args...> argumentTypes;

      typedef Implements_Closure_Value<R,void,Fn,Args...> selfType;

      virtual Implements_Closure_Type_R_Fn_Args_Function<R,Fn,Args...> const * closureType(const StructureEnv_New* cm)const override
      {
        return fnType_;
      }

      virtual Implements_Data_Type_New<R> const * resultType(const StructureEnv_New* cm)const override
      {
        return closureType(cm)->myResultType(cm);
      }

      virtual bool putMe(const StructureEnv_New* cm
                         ,ABC_Output* ostream
                         ,std::string* error,
                         const std::string& masterObjective)const
      {
        return closureType(cm)->putClosureValue(cm,this,ostream,error,masterObjective);
      }


      returnType eval(Markov_CommandManagerVar* cm)const override
      {
        return mp_apply<R,Fn,Args...>(f_,inputTu_->eval(cm));
      }

      const Implements_Closure_Value<std::tuple<Args...>>* getArgumentsValue()const

      {return inputTu_.get();}

      Implements_Closure_Value<std::tuple<Args...>>* getArgumentsValue()
      {return inputTu_.get();}


      Implements_Closure_Value<std::tuple<Args...>>* unload()
      {return inputTu_.release();}


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
        inputTu_->reset();
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
       Implements_Closure_Value<std::tuple<Args...>>* vars):
        fnType_(idtype),f_(idtype->f()),inputTu_(vars){}


      Implements_Closure_Value_R_Fn_Args_Function(const selfType& other):
        fnType_(other.fnType_),f_(other.f_),inputTu_(other.inputTu_->clone()){}


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

      std::string getFunctionId(const StructureEnv_New * cm) const
      {
        return closureType(cm)->myFunctionType(cm)->getFunctionId();
      }
    protected:
      const Implements_Closure_Type_R_Fn_Args_Function<R,Fn,Args...>  * fnType_;
      Fn f_;
      std::unique_ptr<Implements_Closure_Value<std::tuple<Args...>>> inputTu_;
    };



    template<typename Fn, typename...Args>
    class Implements_Closure_Value_R_Fn_Args_Function<void,Fn,Args...>: public ABC_R_Closure<void>
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

      Implements_Closure_Value<std::tuple<Args...>>* unload()
      {return inputTu_.release();}


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
        inputTu_->reset();
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
        return closureType(cm)->putClosureValue(cm,this,ostream,error,masterObjective);
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


    /// auxiliar functions so we can have all methods implemented inline.








    class Implements_Closure_Type_Function: public ABC_Type_of_Function
    {
    public:
      typedef ABC_Closure  myC;
      typedef Implements_Closure_Type<void*> selfType;
      typedef buildClosureByToken<void*> buildClosure;
      typedef ABC_Function_Overload myOverload;
      typedef ABC_Type_of_Value myType_of_Value;

      typedef ABC_Closure returnedClosure;

      virtual bool empty() const override{
        return functionName_.empty();
      }
      virtual void reset() override{}
      virtual selfType *clone() const override
      {
        return new selfType(*this);
      }
      virtual selfType *create() const override
      {
        return new selfType();
      }
      virtual Implements_Closure_Type<void*> const*
      myFunctionType(const StructureEnv_New * cm)const override
      {
        return this;
      }


      virtual const Type_Union<myType_of_Value> *  myResultType(const StructureEnv_New* cm)const override;

      const ClosureType_Union<ABC_Function_Overload>*
      getOverloadsTypes (const StructureEnv_New * cm) const
      {
        return overloadTypes_.get();
      };


      virtual buildClosure* getBuildClosureByToken(
          const StructureEnv_New* cm)const override
      {
        return new buildClosure(cm,this);
      }




      virtual const Implements_Identifier* myFunctionIdentifier(const StructureEnv_New* )const override
      {
        return funIdType_.get();
      }





      std::string getFunctionId()const
      {
        return functionName_;
      }


      virtual ~Implements_Closure_Type_Function(){};


      Implements_Closure_Type_Function();

      Implements_Closure_Type_Function
      (   const std::string functionName
          ,Implements_Identifier* idType
          );

      Implements_Closure_Type_Function(const Implements_Closure_Type_Function& other);


      Implements_Closure_Type_Function( Implements_Closure_Type_Function&& other)=default;

      Implements_Closure_Type_Function& operator=
      (const  Implements_Closure_Type_Function& other)=default;

      Implements_Closure_Type_Function& operator=
      ( Implements_Closure_Type_Function&& other)=default;

      virtual bool putClosureValue(const StructureEnv_New* cm
                                   ,const myC* v
                                   ,ABC_Output* ostream
                                   ,std::string* error,
                                   const std::string& masterObjective)const
      {
        return v
            ->putMe(cm,ostream,error,masterObjective);

      }

      virtual bool getClosure(const StructureEnv_New* cm
                              ,ABC_Closure*& v
                              , ABC_Input* istream
                              ,std::string* error
                              , const std::string& masterObjective)const override;


      void push_overload(const StructureEnv_New* cm,
                         ABC_Function_Overload* g);


    private:
      std::string functionName_;
      std::unique_ptr<Implements_Identifier>  funIdType_;
      std::unique_ptr<ClosureType_Union<ABC_Function_Overload>> overloadTypes_;
      // ABC_Data_New interface
    };





    class Implements_Data_Type_New_Implements_Var_Closure:
        public Implements_Base_Type_New<Implements_Var_Closure>
    {

    public:
      typedef Implements_Var_Closure myC;
      typedef Implements_Closure_Type<void*> clType;
      typedef Implements_Data_Type_New_Implements_Var_Closure selfType;

      using typePredicate=bool (*)
      (const StructureEnv_New * cm, const const_Implements_Var_Closure& iv,
      const Implements_Data_Type_New_Implements_Var_Closure* self
      , std::string * whyNot,const std::string& masterObjective);

      using  keyType= Implements_Identifier* (*)
      (const StructureEnv_New * cm, const const_Implements_Var_Closure& iv,
      const Implements_Data_Type_New_Implements_Var* self
      , std::string * whyNot,const std::string& masterObjective
      ,Implements_Identifier* source);

      using  elemType= clType* (*)
      (const StructureEnv_New * cm, const const_Implements_Var_Closure& iv,
      const selfType* self
      , std::string * whyNot,const std::string& masterObjective
      ,clType* source);


      virtual bool putValue(const StructureEnv_New* cm
                            ,const const_Implements_Var_Closure& v
                            ,ABC_Output* ostream
                            ,std::string* whyNot=nullptr,
                            const std::string& masterObjective="")const
      {
        if ((whyNot==nullptr)||(this->isValueInDomain(cm,v,whyNot,masterObjective)))
          {
            const Implements_Identifier* ktype=this->getKeyType(cm);

            const clType* etype=this->getElementType(cm);

            if (!v.Tip.empty())
              {
                ostream->put("#");
                ostream->put(v.Tip);
                ostream->put("\n");
                if (!v.WhatThis.empty())
                  {
                    ostream->put("##");
                    ostream->put(v.WhatThis);
                    ostream->put("\n");

                  }
              }
            if (!ktype->putValue(cm,v.id,ostream,whyNot,masterObjective))
              return false;
            ostream->put(":");
            if(!v.closure->putMe
               (cm,ostream,whyNot,masterObjective))
              {
                return false;
              }
            return true;


          }
        return false;
      }


      virtual bool putValue(const StructureEnv_New* cm
                            ,const Implements_Var_Closure& v
                            ,ABC_Output* ostream
                            ,std::string* whyNot=nullptr,
                            const std::string& masterObjective="")const override
      {
        const_Implements_Var_Closure cv(v);
        return putValue(cm,cv,ostream,whyNot,masterObjective);
      }


      virtual bool getValue(const StructureEnv_New* cm
                            ,Implements_Var_Closure& v, ABC_Input* istream,std::string* whyNot
                            ,const std::string& masterObjective)const override
      {
        std::string tip;
        std::string whatthis;
        char c;

        auto kType=getKeyType(cm);
        auto eType=getElementType(cm)->clone();
        if (istream->nextCharIs('#',false))
          {
            if (!istream->getLine(v.Tip,whyNot,masterObjective))
              return false;
            std::string wline;
            while ((istream->nextCharIs('#',false))&&(istream->nextCharIs('#',false)))
              {
                if (!istream->getLine(wline,whyNot,masterObjective))
                  return false;
                else
                  v.WhatThis+=wline;
              }
          }
        if (!kType->getValue(cm,v.id,istream,whyNot,masterObjective))
          return false;
        else
          {
            char c;
            ABC_Closure* cl;
            eType=getElementType(cm,v,whyNot,masterObjective,eType);
            if (eType==nullptr)
              {
                istream->put_back(v.id);
                return false;
              }
            else if (!istream->nextCharIs('=',c))
              {
                istream->put_back(v.id);
                *whyNot=masterObjective+": assign (=) missing, found "+c;
                return false;
              }
            else if(! eType->getClosure(cm,cl,istream,whyNot,masterObjective))
              {
                istream->put_back(v.id+" =");

                return false;
              }
            else
              {
                v.closure.reset(cl);
                if ((whyNot==nullptr)||isValueInDomain(cm,v,whyNot,masterObjective))
                  return true;
                else
                  {
                    return false;
                  }

              }

          }

      }


      virtual ~Implements_Data_Type_New_Implements_Var_Closure(){}


      virtual const Implements_Identifier* getKeyType(const StructureEnv_New* cm)const
      {
        return idType_;
      }


      //      virtual Implements_Identifier* getKeyType
      //      (const StructureEnv_New* cm
      //       , const const_Implements_Var& v, std::string* whyNot, const std::string& masterObjective,
      //       Implements_Identifier* source)const
      //      {
      //        if (getKey_==nullptr)
      //          {
      //            return source;
      //          }
      //        else return (*getKey_)(cm,v,this,whyNot,masterObjective,source);
      //      }

      virtual const clType* getElementType(const StructureEnv_New* cm)const
      {
        return clType_;
      }


      virtual clType* getElementType
      (const StructureEnv_New* cm, const const_Implements_Var_Closure& v,
       std::string* whyNot,
       const std::string& masterObjective,clType* source)const
      {
        if (getElement_==nullptr)
          return source;
        else return (*getElement_)(cm,v,this,whyNot,masterObjective,source);
      }

      typedef buildByToken<myC> myBuild;
      virtual buildByToken<Implements_Var_Closure>* getBuildByToken(const StructureEnv_New* cm)const override
      {
        return new buildByToken<Implements_Var_Closure>(cm,this);
      }




      virtual bool empty()const override
      {
        return idType_==nullptr
            &&clType_==nullptr
            &&comply_==nullptr
            &&getKey_==nullptr
            &&getElement_==nullptr;

      }

      virtual void reset() override
      {
        idType_=nullptr;
        clType_=nullptr;
        comply_=nullptr;
        getKey_=nullptr;
        getElement_=nullptr;

      }

      virtual selfType* clone()const override
      {
        return new Implements_Data_Type_New_Implements_Var_Closure(*this);
      }
      virtual selfType* create()const override
      {
        return new selfType();
      }
      Implements_Data_Type_New_Implements_Var_Closure():
        typeId_(""),
        typeType_(nullptr),
        idType_(),
        clType_(new Implements_Closure_Type<void*>()),
        comply_(nullptr),
        getElement_(nullptr),
        getKey_(nullptr){}




      virtual bool getData(const StructureEnv_New* cm
                           ,ABC_Data_New*& v
                           , ABC_Input* istream
                           ,std::string* error
                           , const std::string& masterObjective)const override
      {
        return false;
      }


      virtual ABC_Type_of_Value const* myType()const override {return typeType_;}
      virtual Implements_Data_Type_New<myC> const * myTypeD()const {return typeType_;}

      std::string typeId()const override {return typeId_;}

      std::string myTypeId()const override  {
        if (myType()==nullptr)
          return Cls<myC>::name();
        else
          return myType()->typeId();
      }




      virtual bool isValueInDomain(const StructureEnv_New* cm
                                   ,const const_Implements_Var_Closure &val
                                   , std::string *whyNot
                                   ,const std::string& masterObjective ) const
      {
        if (comply_==nullptr)
          return true;
        else
          return (*comply_)(cm,val,this,whyNot,masterObjective);
      }

      virtual bool isValueInDomain(const StructureEnv_New* cm
                                   ,const Implements_Var_Closure &val
                                   , std::string *whyNot
                                   ,const std::string& masterObjective ) const override
      {
        if (comply_==nullptr)
          return true;
        else
          return (*comply_)(cm,val,this,whyNot,masterObjective);
      }

      virtual const Implements_Identifier* getVarIdType(const StructureEnv_New* cm)const override
      {
        return nullptr;
      }
      virtual const Implements_Identifier* getTypeIdType(const StructureEnv_New* cm)const override
      {
        return nullptr;
      }




      Implements_Data_Type_New_Implements_Var_Closure
      ( const std::string& id, selfType* const typeType,
        Implements_Identifier* idType,
        clType* clType,
        typePredicate comply=nullptr,
        elemType getElement=nullptr,
        keyType getKey=nullptr);

    private:
      std::string typeId_;
      selfType const * typeType_;
      Implements_Identifier* idType_;
      clType* clType_;
      typePredicate comply_;
      elemType getElement_;
      keyType getKey_;


    };



    template <typename R>
    class Implements_Closure_Type_R_function: public ABC_Function_R_Overload<R>
    {
    public:
      typedef ABC_R_Closure<R>  myC;
      typedef Implements_Closure_Type<R,void*> selfType;
      typedef buildClosureByToken<R,void*> buildClosure;
      typedef ABC_Function_R_Overload<R> myOverload;


      virtual bool empty() const override{
      }
      virtual void reset() override{}
      virtual selfType *clone() const override
      {
        return new selfType(*this);
      }
      virtual selfType *create() const override
      {
        return new selfType();
      }
      virtual Implements_Closure_Type<void*> const*
      myFunctionType(const StructureEnv_New * cm)const override
      {
        return functionType_;
      }

      virtual const Implements_Data_Type_New<R>*  myResultType(const StructureEnv_New* cm)const override
      {
        return resultType_;
      }

      const ClosureType_Union<ABC_Function_R_Overload<R>>*
      getOverloadsTypes (const StructureEnv_New * cm) const
      {
        return overloadTypes_.get();
      };




      virtual buildClosure* getBuildClosureByToken(
          const StructureEnv_New* cm)const override
      {
        return new buildClosure(cm,this);
      }




      virtual const Implements_Identifier* myFunctionIdentifier(const StructureEnv_New* )const override
      {
        return R_Funct_Identifier_;
      }



      virtual ~Implements_Closure_Type_R_function(){};


      Implements_Closure_Type_R_function():
        overloadTypes_()
      {}

      Implements_Closure_Type_R_function
      (const Implements_Identifier* R_Funct_Identifier,
       const Implements_Data_Type_New<R>* resultType,
       const Implements_Closure_Type<void*>* functionType,
       std::unique_ptr<ClosureType_Union<ABC_Function_R_Overload<R>>> overloadTypes)
        :
          R_Funct_Identifier_(R_Funct_Identifier),resultType_(resultType)
        ,functionType_(functionType),overloadTypes_(overloadTypes.release()){}

      Implements_Closure_Type_R_function
      (const Implements_Data_Type_New<R>* resultType)
        : Implements_Closure_Type_R_function(
            Identifier::types::idFunct::varType(resultType->typeId()),
            resultType,nullptr,nullptr){}



      Implements_Closure_Type_R_function(const Implements_Closure_Type_R_function& other):
        R_Funct_Identifier_(other.R_Funct_Identifier_),resultType_(other.resultType_)
      ,functionType_(other.functionType_),overloadTypes_(other.overloadTypes_->clone()){}



      Implements_Closure_Type_R_function( Implements_Closure_Type_R_function&& other)=default;

      Implements_Closure_Type_R_function& operator=
      (const  Implements_Closure_Type_R_function& other)=default;

      Implements_Closure_Type_R_function& operator=
      ( Implements_Closure_Type_R_function&& other)=default;


      virtual bool putClosureValue(const StructureEnv_New* cm
                                   ,const myC* v
                                   ,ABC_Output* ostream
                                   ,std::string* error,
                                   const std::string& masterObjective)const
      {
        return v
            ->putMe(cm,ostream,error,masterObjective);

      }


      virtual bool getClosure(const StructureEnv_New* cm
                              ,ABC_Closure*& cl
                              , ABC_Input* istream
                              ,std::string* whyNot
                              ,const std::string& masterObjective )const override
      {
        myC* v;
        if (getClosure_R(cm,v,istream,whyNot,masterObjective))
          {
            cl=v;
            return true;
          }
        else return false;
      }
      virtual bool getClosure_R(const StructureEnv_New* cm
                                ,ABC_R_Closure<R>*& cl
                                , ABC_Input* istream
                                ,std::string* whyNot
                                ,const std::string& masterObjective )const override
      {

        std::string id;
        if (myFunctionIdentifier(cm)->getValue(cm,id,istream,whyNot,masterObjective))
          {
            return fillArguments_R(cm,cl,istream,whyNot,masterObjective);
          }
        else
          return false;
      }

      virtual bool fillArguments_R(const StructureEnv_New* cm
                                   ,ABC_R_Closure<R>*& cl
                                   , ABC_Input* istream
                                   ,std::string* whyNot
                                   ,const std::string& masterObjective )const
      {
        return getOverloadsTypes(cm)->fillArguments_R(cm,cl,istream,whyNot,masterObjective);
      }


      virtual bool fillArguments(const StructureEnv_New* cm
                                 ,ABC_Closure*& cl
                                 , ABC_Input* istream
                                 ,std::string* whyNot
                                 ,const std::string& masterObjective )const
      {
        myC* v;
        if (fillArguments_R(cm,v,istream,whyNot,masterObjective))
          {
            cl=v;
            return true;
          }
        else return false;

      }



      void push_overload(const StructureEnv_New* cm,
                         ABC_Function_R_Overload<R>* g);

    public:
      virtual void setFunction(const Implements_Closure_Type<void *> *f) override
      {
        functionType_=f;
      }


    private:
      const Implements_Identifier* R_Funct_Identifier_;
      const Implements_Data_Type_New<R>* resultType_;
      const Implements_Closure_Type<void*> *functionType_;
      std::unique_ptr<ClosureType_Union<ABC_Function_R_Overload<R>>> overloadTypes_;
    };




    template<class R,typename C,typename...Args>
    class Implements_Closure_Value_R_C_Args_Method: public ABC_R_Closure<R>
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
    class Implements_Closure_Type_R_Fn_Args_Function: public ABC_Function_R_Overload<R>
    {

      // ABC_Value_New interface
    public:
      typedef Implements_Closure_Value<R,void,Fn,Args...> myC;

      typedef Fn functionType;
      typedef Implements_Data_Type_New<R> resultType;

      typedef buildClosureByToken<R,void,Fn,Args...> buildClosure;
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
      virtual buildClosure *getBuildClosureByToken(const StructureEnv_New *cm) const override
      {
        return new buildClosure(cm,this);

      }


      virtual const Implements_Closure_Type<std::tuple<Args...>>*
      getArgumentsType(const StructureEnv_New * cm)const
      {
        return argType_;
      }



      virtual bool putClosureValue(const StructureEnv_New* cm
                                   ,const myC* c
                                   ,ABC_Output* ostream
                                   ,std::string* whyNot
                                   , const std::string& masterObjective)const
      {
        if (! getFnIdType(cm)->putValue(cm,c->getFunctionId(cm),ostream,whyNot,masterObjective))
          return false;
        else if (!getArgumentsType(cm)->putClosureValue
                 (cm,c->getArgumentsValue(),ostream,whyNot,masterObjective))
          {
            return false;
          }
        else return true;
      }


      virtual bool fillArguments(const StructureEnv_New* cm
                                 ,ABC_Closure*& cl
                                 , ABC_Input* istream
                                 ,std::string* whyNot
                                 ,const std::string& masterObjective )const
      {
        ABC_R_Closure<R>* v;
        if (fillArguments_R(cm,v,istream,whyNot,masterObjective))
          {
            cl=v;
            return true;
          }
        else return false;

      }

      virtual bool fillArguments_R(const StructureEnv_New* cm
                                   ,ABC_R_Closure<R>*& v
                                   , ABC_Input* istream
                                   ,std::string* whyNot
                                   ,const std::string& masterObjective )const
      {
        Implements_Closure_Value<std::tuple<Args...>>* args=new Implements_Closure_Value<std::tuple<Args...>>(getArgumentsType(cm));
        if (!getArgumentsType(cm)->getClosureValue
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





      virtual bool getClosure(const StructureEnv_New* cm
                              ,ABC_Closure*& cl
                              , ABC_Input* istream
                              ,std::string* whyNot
                              ,const std::string& masterObjective )const override
      {
        ABC_R_Closure<R>* v;
        if (getClosure_R(cm,v,istream,whyNot,masterObjective))
          {
            cl=v;
            return true;
          }
        else return false;
      }
      virtual bool getClosure_R(const StructureEnv_New* cm
                                ,ABC_R_Closure<R>*& cl
                                , ABC_Input* istream
                                ,std::string* whyNot
                                ,const std::string& masterObjective )const override
      {
        std::string id;
        // if (!myFunctionIdentifier(cm)->getValue(cm,id,istream,whyNot,masterObjective))
        //   return false;
        // else
        return fillArguments_R(cm,cl,istream,whyNot,masterObjective);

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



      virtual bool putClosureValue(const StructureEnv_New* cm
                                   ,const myC* c
                                   ,ABC_Output* ostream
                                   ,std::string* whyNot
                                   , const std::string& masterObjective)const
      {

        if (! myMethodIdentifier(cm)->putValue
            (cm,c->closureType(cm)->myMetodType(cm)->myMethodName()
             ,ostream,whyNot,masterObjective))
          return false;
        else if (!myArgumentsType(cm)->putClosureValue(cm,c->getArguments(),ostream,whyNot,masterObjective))
          {
            return false;
          }
        else return true;
      }

      virtual bool getClosureValue(const StructureEnv_New* cm
                                   ,myC* v
                                   , ABC_Input* istream
                                   ,std::string* whyNot
                                   ,const std::string& masterObjective )const
      {
        Implements_Closure_Value<C,std::string>* idObj;
        std::string idMethod;
        if (! myObjectIdentifier(cm)->getClosureValue(cm,idObj,istream,whyNot,masterObjective))
          return false;
        else if (!myMethodIdentifier(cm)->getValue(cm,idMethod,istream,whyNot,masterObjective))
          {
            return false;
          }
        else
          {
            Implements_Closure_Value<std::tuple<Args...>>* args;
            if (!myArgumentsType(cm)->getClosureValue(cm,args,istream,whyNot,masterObjective))
              return false;
            else
              {
                v=new myC(this,idObj,args);
                return true;
              }
          }
      }


      virtual bool getClosure(const StructureEnv_New* cm
                              ,ABC_Closure*& cl
                              , ABC_Input* istream
                              ,std::string* whyNot
                              ,const std::string& masterObjective )const override
      {
        myC* v;
        if (getClosureValue(cm,v,istream,whyNot,masterObjective))
          {
            cl=v;
            return true;
          }
        else return false;
      }
      virtual bool getClosure_R(const StructureEnv_New* cm
                                ,ABC_R_Closure<R>*& cl
                                , ABC_Input* istream
                                ,std::string* whyNot
                                ,const std::string& masterObjective )const override
      {
        myC* v;
        if (getClosureValue(cm,v,istream,whyNot,masterObjective))
          {
            cl=v;
            return true;
          }
        else return false;
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

      virtual bool putClosureValue(const StructureEnv_New* cm
                                   ,const myC* v
                                   ,ABC_Output* ostream
                                   ,std::string* error,
                                   const std::string& masterObjective)const
      {
        return v->putMe(cm,ostream,error,masterObjective);

      }

      virtual bool getClosure_R(const StructureEnv_New* cm
                                ,myC*& v
                                , ABC_Input* istream
                                ,std::string* error
                                , const std::string& masterObjective)const override
      {

        Implements_Closure_Value<R, std::string>* idV;
        if (myIdentifierType(cm)->getClosureValue(cm,idV,istream,error,masterObjective))
          {
            v=idV;
            return true;
          }
        else
          {
            Implements_Closure_Value<R, int>* cV;
            if  (myConstantType(cm)->getClosureValue(cm,cV,istream,error,masterObjective))
              {
                v=cV;
                return true;
              }
            else
              {
                ABC_R_Closure<R>* fV;
                if (myFunctionType(cm)->getClosure_R(cm,fV,istream,error,masterObjective))
                  {
                    v=fV;
                    return true;
                  }
                else return false;
              }
          }
      }


      virtual bool getClosure(const StructureEnv_New* cm
                              ,ABC_Closure*& cl
                              , ABC_Input* istream
                              ,std::string* whyNot
                              ,const std::string& masterObjective )const override
      {
        myC* v;
        if (getClosure_R(cm,v,istream,whyNot,masterObjective))
          {
            cl=v;
            return true;
          }
        else return false;
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

      virtual selfType *clone() const override{return new selfType(*this);}
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



  template <class myClosure>
  class ClosureType_Union: public myClosure
  {
  public:
    typedef ClosureType_Union<myClosure> selfType;

    typedef BuildClosure_Union<myClosure> buildClosure;

    typedef typename myClosure::myType_of_Value myType_of_Value;

    typedef typename myClosure::returnedClosure  myReturn_Closure;
    virtual bool empty()const
    {
      for (auto &e:v_)
        {
          if (!e->empty()) return false;
        }
      return true;
    }

    virtual void reset()
    {

    }

    virtual selfType* clone()const { return new selfType(*this);}
    virtual selfType* create()const {return new selfType();}


    virtual ~ClosureType_Union()
    {
    }


    virtual const Type_Union<myType_of_Value> *  myResultType(const StructureEnv_New* cm)const
    {
      return tu_.get();
    }

    virtual buildClosure* getBuildClosureByToken(
        const StructureEnv_New* cm)const
    {
      return new buildClosure(cm,this);
    }


    virtual bool getClosure(const StructureEnv_New* cm,
                            ABC_Closure*& v
                            ,ABC_Input* istream
                            ,std::string* whyNot=nullptr
        ,const std::string& masterObjective="")const
    {
      for (auto &e:v_)
        {
          if (e->getClosure(cm,v,istream,whyNot,masterObjective))
            return true;
        }
      return false;

    }

    bool getClosure_R(const StructureEnv_New* cm,
                      myReturn_Closure*& v
                      ,ABC_Input* istream
                      ,std::string* whyNot=nullptr
        ,const std::string& masterObjective="")const
    {

      return getClosure_R_imp(special_(),v_,cm,v,istream,whyNot,masterObjective);

    }


    bool fillArguments(const StructureEnv_New* cm
                       ,ABC_Closure*& cl
                       , ABC_Input* istream
                       ,std::string* whyNot
                       ,const std::string& masterObjective )const
    {
      return fillArguments_imp(special_(),v_,cm,cl,istream,whyNot,masterObjective);

    }

    virtual bool fillArguments_R(const StructureEnv_New* cm
                                 ,myReturn_Closure*& v
                                 , ABC_Input* istream
                                 ,std::string* whyNot
                                 ,const std::string& masterObjective )const
    {
      return fillArguments_R_imp(special_(),v_,cm,v,istream,whyNot,masterObjective);

    }



    std::vector<std::unique_ptr<myClosure>>& getAllClosures(){return  v_;}

    const std::vector<std::unique_ptr<myClosure>>& getAllClosures()const {return  v_;}


    ClosureType_Union* create_SubSet_Returning(const StructureEnv_New* cm,
                                               const ABC_Type_of_Value* t)
    {
      std::vector<std::unique_ptr<myClosure>> o;
      for (auto &e:v_)
        {
          if (e->myResultType(cm)->isOfThisType(cm,t->typeId()))
            o.emplace_back(e->clone());
        }
      return new ClosureType_Union(cm,std::move(o));
    }

    void push_Closure(const StructureEnv_New* cm,myClosure* c){
      v_.emplace_back(c);
      if (tu_==nullptr)
        {
          tu_.reset(new Type_Union<myType_of_Value>);
          Iu_.reset(new Identifier_Union );
          Fu_.reset(new ClosureType_Union<const Implements_Closure_Type<void*>>);

        }
      tu_->push_Type(c->myResultType(cm));
      push_Identifier_imp(cm,Iu_,c);
      push_Function_imp(cm,Fu_,c);
    }

    ClosureType_Union():v_()
    ,tu_(nullptr)
    ,Iu_(nullptr)
    ,Fu_(nullptr){}



    ClosureType_Union(const StructureEnv_New* cm,
                      std::vector<std::unique_ptr<myClosure>>&& v)
      :v_(v),tu_(generateUnion(cm,v))
      ,Iu_(generate_IdentifierUnion(cm,v))
      ,Fu_(generate_FunctionUnion(cm,v))
    {}

    ClosureType_Union(const ClosureType_Union& other):v_(clone_vector(other.v_))
    ,tu_(other.tu_->clone()),Iu_(other.Iu_->clone()),Fu_(other.Fu_->clone()){}

    ClosureType_Union( ClosureType_Union&& other)=default;
    ClosureType_Union& operator=(const ClosureType_Union& other)=default;
    ClosureType_Union& operator=(ClosureType_Union&& other)=default;


    const Implements_Identifier* myFunctionIdentifier(const StructureEnv_New* cm)const
    {
      return Iu_.get();
    }

    void setFunction(const Implements_Closure_Type<void*>* f)
    {
      setFunction_imp(f,v_);
    }





    ClosureType_Union<const Implements_Closure_Type<void*>> const* myFunctionType(const StructureEnv_New * cm)const
    {
      return Fu_.get();
    }

    void push_overload(const StructureEnv_New* cm,
                       ABC_Function_Overload* g)
    {
      push_overload_imp(cm,g);
    }

  protected:
    std::vector<std::unique_ptr<myClosure>> v_;
    std::unique_ptr<Type_Union<myType_of_Value>> tu_;
    std::unique_ptr<Identifier_Union> Iu_;
    std::unique_ptr<ClosureType_Union<const Implements_Closure_Type<void*>>> Fu_;

    static Type_Union<myType_of_Value>* generateUnion
    (const StructureEnv_New* cm,const std::vector<std::unique_ptr<myClosure>>& v)
    {
      std::vector<const myType_of_Value*> o;
      for (auto& e:v)
        o.push_back(e->myResultType(cm));
      return new Type_Union<myType_of_Value>(std::move(o));
    }

    //---

    template<class Q = myClosure>
    static typename std::enable_if<std::is_base_of<ABC_Type_of_Function,Q>::value, const Identifier_Union*>::type generate_IdentifierUnion
    (const StructureEnv_New* cm,const std::vector<std::unique_ptr<myClosure>>& v)
    {
      std::vector<const Implements_Identifier*> o;
      for (auto& e:v)
        o.push_back(e->myFunctionIdentifier(cm));
      return new Identifier_Union(std::move(o));

    }

    template<class Q = myClosure>
    static typename std::enable_if<!std::is_base_of<ABC_Type_of_Function,Q>::value, const Identifier_Union*>::type generate_IdentifierUnion
    (const StructureEnv_New* cm,const std::vector<std::unique_ptr<myClosure>>& v)
    {
      return new Identifier_Union();
    }




    //---

    template<class Q = myClosure>
    static typename std::enable_if<std::is_base_of<ABC_Type_of_Function,Q>::value,
    void
    >::type
    push_Identifier_imp
    (const StructureEnv_New* cm,std::unique_ptr<Identifier_Union>& u,myClosure* c)
    {
      u->push_Identifier(c->myFunctionIdentifier(cm)->clone());
    }

    template<class Q = myClosure>
    static typename std::enable_if<!std::is_base_of<ABC_Type_of_Function,Q>::value,
    void
    >::type
    push_Identifier_imp
    (const StructureEnv_New* cm,std::unique_ptr<Identifier_Union>& u,myClosure* c)
    {
    }


    //--
    template<class Q = myClosure>
    static typename std::enable_if<std::is_base_of<ABC_Function_Overload,Q>::value
    ,ClosureType_Union<const Implements_Closure_Type<void*>>*
    >::type
    generate_FunctionUnion
    (const StructureEnv_New* cm,const std::vector<std::unique_ptr<myClosure>>& v)
    {
      std::vector<std::unique_ptr<const Implements_Closure_Type<void*>>> o;
      for (auto& e:v)
        o.emplace_back(e->myFunctionType(cm)->clone());
      return new ClosureType_Union<const Implements_Closure_Type<void*>>(cm,std::move(o));

    }

    template<class Q = myClosure>
    static typename std::enable_if<!std::is_base_of<ABC_Function_Overload,Q>::value
    ,ClosureType_Union<const Implements_Closure_Type<void*>>*
    >::type
    generate_FunctionUnion
    (const StructureEnv_New* cm,const std::vector<std::unique_ptr<myClosure>>& v)
    {
      return new ClosureType_Union<const Implements_Closure_Type<void*>>();
    }


    ///-----

    template<class Q = myClosure>
    static typename std::enable_if<std::is_base_of<ABC_Function_Overload,Q>::value,
    void
    >::type
    push_Function_imp
    (const StructureEnv_New* cm
     ,std::unique_ptr<ClosureType_Union<const Implements_Closure_Type<void*>>>& u
     ,myClosure* c)
    {
      u->push_Closure(cm,c->myFunctionType(cm));
    }

    template<class Q = myClosure>
    static typename std::enable_if<!std::is_base_of<ABC_Function_Overload,Q>::value,
    void
    >::type
    push_Function_imp
    (const StructureEnv_New* cm
     ,std::unique_ptr<ClosureType_Union<const Implements_Closure_Type<void*>>>& u
     ,myClosure* c)
    {
    }


    //--

    template<class Q = myClosure>
    static typename std::enable_if<std::is_base_of<ABC_Function_Overload,Q>::value
    ,void
    >::type
    setFunction_imp
    (const Implements_Closure_Type<void*>* f
     ,const std::vector<std::unique_ptr<myClosure>>& v)
    {
      for (auto& e:v)
        e->setFunction(f);
    }

    template<class Q = myClosure>
    static typename std::enable_if<!std::is_base_of<ABC_Function_Overload,Q>::value
    ,void
    >::type
    setFunction_imp
    (const Implements_Closure_Type<void*>* f
     ,const std::vector<std::unique_ptr<myClosure>>& v)
    {
    }


    ///---
    ///
    template<class Q = myClosure>
    static typename std::enable_if<std::is_base_of<ABC_Function_Overload,Q>::value
    ,void
    >::type
    push_overload_imp
    (const Implements_Closure_Type<void*>* f
     ,const std::vector<std::unique_ptr<myClosure>>& v)
    {
      for (auto& e:v)
        e->setFunction(f);
    }

    template<class Q = myClosure>
    static typename std::enable_if<!std::is_base_of<ABC_Function_Overload,Q>::value
    ,void
    >::type
    push_overload_imp
    (const Implements_Closure_Type<void*>* f
     ,const std::vector<std::unique_ptr<myClosure>>& v)
    {
    }



    //--//---

    template<class Q=myClosure,typename int_<decltype(Q::getClosure_R)>::type=0>
    static bool
    getClosure_R_imp
    (special_,const std::vector<std::unique_ptr<myClosure>>& ve,
     const StructureEnv_New* cm,
     myReturn_Closure*& v
     ,ABC_Input* istream
     ,std::string* whyNot=nullptr
        ,const std::string& masterObjective="")
    {
      for (auto &e:ve)
        {
          if (e->getClosure_R(cm,v,istream,whyNot,masterObjective))
            return true;
        }
      return false;

    }

    template<class Q=myClosure>
    static bool
    getClosure_R_imp
    (general_,const std::vector<std::unique_ptr<myClosure>>& ve,
     const StructureEnv_New* cm,
     myReturn_Closure*& v
     ,ABC_Input* istream
     ,std::string* whyNot=nullptr
        ,const std::string& masterObjective="")
    {
      return false;
    }




    //--//---

    template<class Q=myClosure,typename int_<decltype(Q::fillArguments)>::type=0>
    static bool
    fillArguments_imp
    (special_,const std::vector<std::unique_ptr<myClosure>>& ve,
     const StructureEnv_New* cm,
     ABC_Closure*& v
     ,ABC_Input* istream
     ,std::string* whyNot=nullptr
        ,const std::string& masterObjective="")
    {
      for (auto &e:ve)
        {
          if (e->fillArguments(cm,v,istream,whyNot,masterObjective))
            return true;
        }
      return false;

    }

    template<class Q=myClosure>
    static bool
    fillArguments_imp
    (general_,const std::vector<std::unique_ptr<myClosure>>& ve,
     const StructureEnv_New* cm,
     ABC_Closure*& v
     ,ABC_Input* istream
     ,std::string* whyNot=nullptr
        ,const std::string& masterObjective="")
    {
      return false;
    }


    //--//---

    template<class Q=myClosure,typename int_<decltype(Q::fillArguments_R)>::type=0>
    static bool
    fillArguments_R_imp
    (special_,const std::vector<std::unique_ptr<myClosure>>& ve,
     const StructureEnv_New* cm,
     myReturn_Closure*& v
     ,ABC_Input* istream
     ,std::string* whyNot=nullptr
        ,const std::string& masterObjective="")
    {
      for (auto &e:ve)
        {
          if (e->fillArguments_R(cm,v,istream,whyNot,masterObjective))
            return true;
        }
      return false;

    }

    template<class Q=myClosure>
    static bool
    fillArguments_R_imp
    (general_,const std::vector<std::unique_ptr<myClosure>>& ve,
     const StructureEnv_New* cm,
     myReturn_Closure*& v
     ,ABC_Input* istream
     ,std::string* whyNot=nullptr
        ,const std::string& masterObjective="")
    {
      return false;
    }




  };

  template <class myClosure>
  std::vector<std::unique_ptr<typename myClosure::buildClosure>>
  getBuildVector(const StructureEnv_New* cm
                 , const ClosureType_Union<myClosure>* t)
  {
    std::vector<std::unique_ptr<typename myClosure::buildClosure>>  out(t->getAllClosures().size());
    for (std::size_t i=0; i<t->getAllClosures().size(); ++i)
      {
        out[i].reset(t->getAllClosures()[i]->getBuildClosureByToken(cm));
      }
    return out;

  }

  inline
  void push_overload_imp( std::unique_ptr<ClosureType_Union<ABC_Function_Overload>>& overloadTypes
                          ,const StructureEnv_New* cm,
                          ABC_Function_Overload* g)
  {
    overloadTypes->push_Closure(cm,g);
  }

  inline
  const Type_Union<typename ABC_Function_Overload::myType_of_Value> *  myResultType_imp
  (const  std::unique_ptr<ClosureType_Union<ABC_Function_Overload>>& overloadTypes
   ,const StructureEnv_New* cm)
  {
    return overloadTypes->myResultType(cm);
  }
  inline
  ClosureType_Union<ABC_Function_Overload>*
  clone_imp
  (const std::unique_ptr<ClosureType_Union<ABC_Function_Overload>>& overloadTypes)
  {
    return overloadTypes->clone();
  }

  namespace _private
  {
    inline
    bool Implements_Closure_Type_Function::getClosure(const StructureEnv_New *cm, ABC_Closure *&v, ABC_Input *istream, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const
    {

      std::string id;
      const Implements_Closure_Type<void*>* ct;
      if (myFunctionIdentifier(cm)->getValue(cm,id,istream,whyNot,masterObjective))
        {
          ct=cm->idToCmd(id,whyNot,masterObjective);
          if ((ct!=nullptr)&& (ct->getOverloadsTypes(cm)->getClosure(cm,v,istream,whyNot,masterObjective)))
            return true;
          else
            {
              istream->put_back(id);
              return false;
            }
        }
      else  return false;

    }
  }

};



#endif // IMPLEMENTS_CLOSURES_H
