#ifndef CLOSURE_H
#define CLOSURE_H

#include "Markov_IO/StructureEnv.h"
#include "Markov_IO/Var.h"
#include "Markov_IO/Closure_type.h"
#include "Markov_IO/Implements_ComplexVar_New.h"
namespace Markov_IO_New {



  class ABC_Closure //:   public ABC_Data_New
  {
    // ABC_Value_New interface
  public:

    typedef ABC_Closure selfType;

    virtual bool empty()const =0;

    virtual void reset()=0;

    virtual ABC_Closure* clone()const=0;
    virtual ABC_Closure* create()const=0;

    virtual bool putMe(const StructureEnv_New* cm
                          ,ABC_Output* ostream
                          ,std::string* error,
                          const std::string& masterObjective)const=0;

    virtual ABC_Type_of_Closure const* closureType(const StructureEnv_New* cm)const=0;

    virtual ABC_Type_of_Value const * resultType(const StructureEnv_New* cm)const=0;

    virtual ABC_Data_New* evalData(Markov_CommandManagerVar* cm)const =0;

    virtual ~ABC_Closure(){}

  };


  template<typename R>
  class ABC_R_Closure: public ABC_Closure
  {
    // ABC_Value_New interface
  public:

    typedef R returnType;

    virtual ABC_R_Closure* clone()const=0;
    virtual ABC_R_Closure* create()const=0;

    virtual ABC_Type_of_Closure const* closureType(const StructureEnv_New* cm)const=0;

    virtual Implements_Data_Type_New<R> const * resultType(const StructureEnv_New* cm)const=0;


    virtual returnType eval(Markov_CommandManagerVar* cm)const=0;




    virtual ~ABC_R_Closure()
    {
    }

    // ABC_Closure interface
  };








  template <typename T>
  const Implements_Value_New<T>*
  cm_idToValued(const Markov_CommandManagerVar* cm
                , const std::string& id
                ,const std::string & typeId);

  template <typename T>
  Implements_Value_New<T>*
  cm_idToValued( Markov_CommandManagerVar* cm
                , const std::string& id
                ,const std::string & typeId);


  template<typename T>
  bool cm_getDataFromId(const Markov_CommandManagerVar* cm
                        ,const std::string& idname, T& x);


  template <typename T>
  const Implements_Data_Type_New<T> *cm_resultType(const ABC_R_Closure<T> *cl, const Markov_CommandManagerVar *cm);


  namespace _private
  {

    template<typename T>
    class Implements_Closure_Value_Base_T_Identifier: public ABC_R_Closure<T>
    {
      // ABC_Value_New interface
    public:

      typedef T returnType;

      typedef Implements_Closure_Value<T,std::string> selfType;

      virtual Implements_Closure_Type<T,std::string> const* closureType(const StructureEnv_New* cm)const override
      {
        return varType_;
      }

      virtual Implements_Data_Type_New<T> const* resultType(const StructureEnv_New* cm)const override
      {
        return closureType(cm)->myResultType(cm);
      }

      virtual Implements_Value_New<T>* evalData(Markov_CommandManagerVar* cm) const override
      {
        return cm_idToValued<T>(cm,id_,cm_resultType(this,cm)->typeId());
      }


      virtual returnType eval(Markov_CommandManagerVar* cm) const override
      {
        T out;
        if (cm_getDataFromId(cm,id_,out))
        return out;
        else return {};
      }


      virtual std::string getIdentifier()const
      {
        return id_;
      }

      std::string unload()
      {
        std::string out=std::move(id_);
        id_={};
        return std::move(out);

      }


      virtual Implements_Closure_Value_Base_T_Identifier<T>* clone()const
      {
        return new selfType(*this);
      }

      virtual ~Implements_Closure_Value_Base_T_Identifier()
      {
      }


      Implements_Closure_Value_Base_T_Identifier
      (Implements_Closure_Type<T,std::string> const* varType,
          const std::string& id):
        varType_(varType),id_(id){}



      Implements_Closure_Value_Base_T_Identifier(const Implements_Closure_Value_Base_T_Identifier<T>& other)=default;

      Implements_Closure_Value_Base_T_Identifier(Implements_Closure_Value_Base_T_Identifier<T>&& other)=default;

      Implements_Closure_Value_Base_T_Identifier& operator=(const Implements_Closure_Value_Base_T_Identifier<T>& other)=default;

      Implements_Closure_Value_Base_T_Identifier& operator=(Implements_Closure_Value_Base_T_Identifier<T>&& other)=default;

      Implements_Closure_Value_Base_T_Identifier()=default;


      virtual bool empty() const override
      {
        return id_.empty();
      }

      virtual void reset() override
      {
        id_.clear();
      }

      virtual Implements_Closure_Value_Base_T_Identifier<T>* create() const override
      {
        return new Implements_Closure_Value_Base_T_Identifier();

      }

      virtual bool putMe(const StructureEnv_New* cm
                            ,ABC_Output* ostream
                            ,std::string* error,
                            const std::string& masterObjective)const
      {
        return closureType(cm)->putClosureValue(cm,this,ostream,error,masterObjective);
      }


    protected:
      const Implements_Closure_Type<T,std::string>* varType_;
      std::string id_;
    };

    template<typename T>
    class Implements_Closure_Value_Base_T_Constant: public ABC_R_Closure<T>

        {
          // ABC_Value_New interface
        public:

          typedef T returnType;

          typedef Implements_Closure_Value<T,int> selfType;

          virtual Implements_Closure_Type<T,int> const* closureType(const StructureEnv_New* cm)const override
          {
            return clType_.get();
          }

          virtual Implements_Data_Type_New<T> const* resultType(const StructureEnv_New* cm)const override
          {
            return closureType(cm)->myResultType(cm);
          }

          virtual Implements_Value_New<T>* evalData(Markov_CommandManagerVar* cm) const override
          {
            return new Implements_Value_New<T>(cm_resultType(this,cm),x_);
          }


          virtual returnType eval(Markov_CommandManagerVar* cm)const override
          {
            return x_;
          }




          const returnType getData()const  {return x_;}

          returnType unload(){auto out=std::move(x_); x_={}; return std::move(out);}


          virtual Implements_Closure_Value_Base_T_Constant<T>* clone()const
          {
            return new selfType(*this);
          }

          virtual ~Implements_Closure_Value_Base_T_Constant()
          {
          }


          Implements_Closure_Value_Base_T_Constant
          (const Implements_Closure_Type<T,int> * clType,
              const T& x):
            clType_(clType->clone()),x_(x),empty_(false){}

          Implements_Closure_Value_Base_T_Constant
          (const Implements_Data_Type_New<T> * datType,
              const T& x):
            clType_(new Implements_Closure_Type<T,int>(datType)),x_(x),empty_(false){}

          Implements_Closure_Value_Base_T_Constant
          (const T& x):
            clType_(new Implements_Closure_Type<T,int>),x_(x),empty_(false){}

          Implements_Closure_Value_Base_T_Constant
          ():
            clType_(new Implements_Closure_Type<T,int>),x_(),empty_(true){}





          Implements_Closure_Value_Base_T_Constant(const Implements_Closure_Value_Base_T_Constant<T>& other):
            clType_(other.clType_->clone()),
            x_(other.x_),empty_(other.empty_){}

          Implements_Closure_Value_Base_T_Constant(Implements_Closure_Value_Base_T_Constant<T>&& other)=default;

          Implements_Closure_Value_Base_T_Constant& operator=(const Implements_Closure_Value_Base_T_Constant<T>& other)=default;

          Implements_Closure_Value_Base_T_Constant& operator=(Implements_Closure_Value_Base_T_Constant<T>&& other)=default;



          virtual bool empty() const override
          {
            return empty_;
          }

          virtual void reset() override
          {
            empty_=true;
            x_={};
          }

          virtual Implements_Closure_Value_Base_T_Constant<T>* create() const override
          {
            return new Implements_Closure_Value_Base_T_Constant();

          }

          virtual bool putMe(const StructureEnv_New* cm
                                ,ABC_Output* ostream
                                ,std::string* error,
                                const std::string& masterObjective)const
          {
            return closureType(cm)->putClosureValue(cm,this,ostream,error,masterObjective);
          }



        protected:
          std::unique_ptr<Implements_Closure_Type<T,int>> clType_;
          T x_;
          bool empty_;
    };



  }







}





#endif // CLOSURE_H
