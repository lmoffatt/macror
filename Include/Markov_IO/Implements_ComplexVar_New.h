#ifndef IMPLEMENTS_COMPLEXVAR_NEW_H
#define IMPLEMENTS_COMPLEXVAR_NEW_H



#include "Markov_IO/Var.h"
#include "Markov_IO/buildByToken.h"
#include "Markov_LA/matrixSum.h"

#include <cmath>

namespace Markov_IO_New {

  class ABC_Output
  {
  public:
    template<typename T>
    void put(const T& x, std::string* error)
    {
      *error=Cls<T>::name()+ "is not supported";
    }

    virtual void put(const std::string& s)=0;
    virtual void put(double x)=0;
    virtual void put(int n)=0;
    virtual void put(std::size_t n)=0;
    virtual void put(char c)=0;

    /*

    template<typename T>
    void put(const std::vector<T>& v)
    {
      put('[');
      for (auto& e:v)
        { put(e); put('\t');}
      put(']');
    }
    
    template<typename T>
    void put(const std::set<T>& v)
    {
      put('{');
      for (auto& e:v)
        { put(e); put('\t');}
      put('}');
    }
    
    template<typename K,typename T>
    void put(const std::map<K,T>& v)
    {
      put('{');
      for (auto& e:v)
        { put(e.first); put('\t:\t'); put(e.second);}
      put('}');
    }
    
    
    
    template<typename T>
    void put(const Markov_LA::M_Matrix<T>& v)
    {
      put('\n');
      for (std::size_t i=0; i<nrows(v);++i )
        {
          for (std::size_t j=0; j<Markov_LA::ncols(v); ++j)
            { put(v(i,j)); put('\t');}
          put('\n');
        }
      put('\n');
    }
    
*/


    virtual ~ABC_Output(){}
  };

  class ABC_Input
  {
  public:
    virtual bool getLine(std::string& line,std::string* whyNot,const std::string& masterObjective)=0;

    virtual  bool get( std::string& s,std::string* whyNot,const std::string& masterObjective)=0;
    virtual  bool get(double& x,std::string* whyNot,const std::string& masterObjective)=0;
    virtual  bool get(int& n,std::string* whyNot,const std::string& masterObjective)=0;
    virtual  bool get(std::size_t& n,std::string* whyNot,const std::string& masterObjective)=0;
    virtual  bool get(char& c,std::string* whyNot,const std::string& masterObjective)=0;
    virtual  bool get(char& c)=0;
    virtual bool nextCharIs(char c,char& found)=0;

    virtual bool nextCharIs(char c,bool advanceInFailure)=0;


    virtual ~ABC_Input(){}
  };


  class Implements_Command_Type_New;



  class StructureEnv_New: public ABC_Data_New
  {
    // ABC_Value_New interface
  public:
    static std::string ClassName(){return "StructureEnv_New";}

    // no me queda claro
    StructureEnv_New(const StructureEnv_New& other):
      p_(other.p_),
      structType_(other.structType_),
      ids_(other.ids_),
      all_(other.all_),
      allId_(other.allId_),
      vars_(other.vars_),
      types_(other.types_),
      cmds_(other.cmds_),
      idTipWt_(other.idTipWt_){}

    virtual bool empty() const override {return ids_.empty();}

    virtual void reset() override;
    virtual std::__cxx11::string myType() const override;

  public:

    const StructureEnv_New* parent()const;

    const ABC_Data_New* idToValue
    (const std::string& name
     , const std::string & typeName
     ,std::string* whyNot=nullptr, const std::string& masterObjective="")const;


    const ABC_Data_New* idToValue(const std::string& name, std::string *whyNot=nullptr)const;

    ABC_Data_New* idToValue(const std::string& name, std::string* whyNot=nullptr, const std::string & masterObective="");

    virtual const ABC_Type_of_Value* idToType(const std::string& name, std::string *whyNot=nullptr, const std::string& masterObjective="")const;

    virtual ABC_Type_of_Value* idToType(const std::string& name, std::string *whyNot=nullptr,const std::string& masterObjective="");


    const Implements_Command_Type_New* idToCommand(const std::string& name, std::string *whyNot, const std::string& masterobjective)const;

    template<typename T>
    const Implements_Data_Type_New<T>* idToTyped(
        const std::string& name
        , std::string *whyNot=nullptr
        , const std::string& masterObjective="")const
    {
      const std::string objective
          =masterObjective
          +": "+name+ "is not a "+ Cls<T>::name();
      auto it=types_.find(name);
      if (it!=types_.end())
        {
          return dynamic_cast<Implements_Data_Type_New<T>*>(
                it->second);
        }
      else if (parent()!=nullptr)
        return  parent()->idToTyped<T>(name, whyNot,objective);
      else
        {   if (whyNot!=nullptr)
            *whyNot=objective+": name not found in type list";
          return nullptr;
        }

    }


    template<typename T>
    bool getValueFromId(const std::string& name
                        , T& value
                        ,std::string* whyNot=nullptr, const std::string& masterObjective="")const
    {

      std::string objective;
      if (whyNot!=nullptr)
        objective=masterObjective+": "+ name+" is not a "+Cls<T>::name();

      auto it=vars_.find(name);
      const ABC_Data_New* var=it->second;
      if (it!=vars_.end())
        {
          auto v=dynamic_cast<
              const Implements_Value_New<T>*>(var);
          if (v==nullptr)
            {
              return false;
            }
          else if (v->empty())
            {
              if (whyNot!=nullptr)
                *whyNot=objective+": varType not found";
              return false;
            }
          else
            {
              value=v->getValue();
              return true;
            }
        }

      else if (parent()!=nullptr)
        return  parent()->getValueFromId(name,value,whyNot,objective);
      else
        {
          if (whyNot!=nullptr)
            *whyNot=objective+": does not have it and it has no parent";
          return false;
        }
    }



    template<typename T>
    bool setValueToId(const std::string& name
                      ,const T& value
                      ,std::string* whyNot=nullptr, const std::string& masterObjective="")
    {

      std::string objective;
      if (whyNot!=nullptr)
        objective=masterObjective+": "+ name+" is not a "+Cls<T>::name();

      auto it=vars_.find(name);
      ABC_Data_New* var=it->second;
      if (it!=vars_.end())
        {
          auto v=dynamic_cast<
              Implements_Value_New<T>*>(var);
          if (v==nullptr)
            {
              return false;
            }
          else if (v->empty())
            {
              if (whyNot!=nullptr)
                *whyNot=objective+": varType not found";
              return false;
            }
          else
            {
              v->getValue()=value;
              return true;
            }
        }

      else
        {
          if (whyNot!=nullptr)
            *whyNot=objective+": does not have it and it has no parent";
          return false;
        }
    }






    bool hasName(const std::string& name
                 , std::string* whyNot
                 ,const std::string &masterObjective,
                 bool recursive)const;



    bool hasNameofType(const std::string& name, const std::string& type,
                       std::string* whyNot
                       ,const std::string &masterObjective,
                       bool recursive)const;



    bool hasCmdofType(const std::string &name, const std::string &type, std::string *whyNot, const std::string &masterObjective, bool recursive) const;


    bool hasTypeofType(const std::string& name, const std::string& type,
                       std::string* whyNot
                       , const std::string &masterObjective, bool recursive)const;



    bool isNameUnOcuppied(const std::string& name,std::string* whyNot,const std::string &masterObjective, bool recursive)const;


    bool hasType(const std::string& name
                 , std::string* whyNot=nullptr
                 ,const std::string &masterObjective="",
                 bool recursive=false)const;



    bool hasCommand(const std::string& name,   std::string* whyNot
                    ,const std::string &masterObjective,
                    bool recursive)const;



    void pushVar(Implements_Var v)
    {
      pushVar(v.id,v.data,v.Tip,v.WhatThis);
    }

    Implements_Var popVar();


    void pushVar(const std::string& id
                 ,ABC_Data_New* var
                 , std::string tip
                 , std::string whatthis);


    template<class Field>
    void pushVar(typename Field::myC val={}
        , const std::string myId=Field::myId()
        , const std::string& myTip=Field::myTip()
        , const std::string& myWhatThis=Field::myWhatThis()  )
    {
      pushVar(myId
              ,new Implements_Value_New<typename Field::myC>(Field::myIdType(),val)
              ,myTip,myWhatThis);
    }

    template<class Field>
    bool getDataValue(typename Field::myC &val,std::string* whyNot=nullptr,const std::string &masterObjective="")const
    {
      return getValueFromId(Field::myId(),val,whyNot,masterObjective);
    }

    template<class Field>
    typename Field::myC getDataValueS(std::string* whyNot=nullptr,const std::string &masterObjective="")const
    {
      typename Field::myC val;
      getValueFromId(Field::myId(),val,whyNot,masterObjective);
      return val;
    }




    template<class Field>
    bool setDataValue(const typename Field::myC &val,std::string* whyNot=nullptr,const std::string &masterObjective="")
    {
      return setValueToId<typename Field::myC>
          (Field::myId(),val,whyNot,masterObjective);
    }




    void pushType(const std::string& id
                  ,ABC_Type_of_Value* var
                  , std::string tip
                  , std::string whatthis);


    template<class Type>
    void pushType(const std::string& name)
    {
      if (!hasType(Type::myId(name)))
      pushType(Type::myId(name)
               ,Type::varType(name)
               ,Type::myTip(),Type::myWhatThis());
    }






    template<class Type>
    void pushType()
    {
      if (!hasType(Type::myId()))
      pushType(Type::myId()
               ,Type::varType()
               ,Type::myTip()
               ,Type::myWhatThis());
    }

    template<class T>
    void pushRegularType()
    {
      if (!hasType(Cls<T>::name()))
      pushType(Cls<T>::name()
               , new Implements_Data_Type_New<T>(),"a "+Cls<T>::name(),"");
    }




    void pushCommand(const std::string& id
                     ,Implements_Command_Type_New* var
                     , std::string tip
                     , std::string whatthis);


    template<class Type>
    void pushCommand()
    {
      pushCommand(Type::myId()
               ,Type::cmdType()
               ,Type::myTip()
               ,Type::myWhatThis());
    }


    StructureEnv_New(const StructureEnv_New* parent,const std::string& myType);

    StructureEnv_New()=default;


    std::set<std::string> getIdsOfVarType(const std::string& varType, bool recursive)const;





    // Implements_Value_New interface

    std::set<std::string> getIdsOfTypeType(const std::string &typeType, bool recursive) const;
    std::string defaultIdOfVarType(const std::string &varType, bool recursive) const;
    std::string defaultIdOfTypeType(const std::string &typeType, bool recursive) const;
    std::string defaultIdOfCommand(const std::string &typeType, bool recursive) const;


    std::string defaultIdOfCmdType(const std::string &cmdType, bool recursive) const;
    std::set<std::string> getIdsOfCmdType(const std::string &cmdType, bool recursive) const;

    friend class buildByToken<std::map<std::string, ABC_Data_New *> >;


    std::map<std::string,ABC_Data_New*>& getVars();
    const std::map<std::string,ABC_Data_New*>& getVars()const;
    std::map<std::string,ABC_Type_of_Value*>& getTypes();
    const std::map<std::string,ABC_Type_of_Value*>& getTypes()const;
    std::map<std::string,Implements_Command_Type_New*>& getCommands();
    const std::map<std::string,Implements_Command_Type_New*>& getCommands()const;



    // ABC_Data_New interface
  public:
    virtual StructureEnv_New *clone() const override
    {
      return new StructureEnv_New(*this);
    }
    virtual ABC_Data_New *create() const override
    {
      return new StructureEnv_New(parent(),myType());
    }
    virtual bool isOfThisType(const StructureEnv_New *cm, const std::__cxx11::string &generalType, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const override;

    std::string dataToId(const ABC_Data_New *data, std::__cxx11::string *whyNot=nullptr, const std::string &objective="") const;

    std::string Tip(const std::string& id)const ;
    std::string WhatThis(const std::string& id) const;





  private:
    const StructureEnv_New* p_;
    std::string structType_;
    std::vector<std::string> ids_;
    std::map<std::string,ABC_Data_New*> all_;
    std::map<const ABC_Data_New*, std::string> allId_;
    std::map<std::string,ABC_Data_New*> vars_;
    std::map<std::string,ABC_Type_of_Value*> types_;
    std::map<std::string,Implements_Command_Type_New*> cmds_;
    std::map<std::string,std::pair<std::string,std::string>> idTipWt_;




  };




  template<typename T>
  struct a_Type{
    typedef  T myC;
    static std::string myId();
    static std::string myIdType(){return Cls<myC>::name();}
    static std::string myTip();
    static std::string myWhatThis();
    static bool comply(const StructureEnv_New* cm
                       ,const myC& x
                       ,const StructureEnv_New*
                       ,std::string *WhyNot
                       , const std::string& objective);



    static Implements_Data_Type_New<myC>*
    varType(const StructureEnv_New* cm);

  };
  template<typename T,typename Type>
  struct a_Field  {
    typedef T myC;
    typedef Type myType;
    static std::string myId();
    static std::string myIdType(){return myType::myId();}
    static std::string myTip();
    static std::string myWhatThis();
  };



  namespace alternatives
  {

    template<typename T>
    inline std::string element(const StructureEnv_New* cm,   const T* dataType)
    {
      return "<"+dataType->getElementDataType(cm)->Tip()+">";}


    static
    void insert(std::set<std::string>& alt,const std::string& id, const std::string myType)
    {
      alt.insert(id+" : "+myType);
    }

    static
    void insert(std::set<std::string>& alt,const std::string& id,const ABC_Data_New* v)
    {
      insert(alt,id,v->myType());
    }


    static std::set<std::string> getIdofVar(const std::map<std::string, ABC_Data_New*> m)
    {
      std::set<std::string> o;
      for (auto& e:m)
        insert(o,e.first,e.second);
      return o;

    }
  };







  class ABC_BuildByToken;



  class Implements_Identifier;


  class ABC_Type_of_Value:public ABC_Data_New
  {
  public:
    ABC_Type_of_Value();
    virtual ~ABC_Type_of_Value(){}
    virtual bool putData(const StructureEnv_New* cm
                         ,const ABC_Data_New* v
                         ,ABC_Output* ostream
                         ,std::string* error,
                         const std::string& masterObjective)const=0;

    virtual bool getData(const StructureEnv_New* cm
                         ,ABC_Data_New*& v
                         , ABC_Input* istream
                         ,std::string* error
                         , const std::string& masterObjective)const=0;

    virtual ABC_BuildByToken* getBuildByToken(
        const StructureEnv_New* cm)const=0;


    virtual bool isDataInDomain(const StructureEnv_New* cm
                                ,const ABC_Data_New* v
                                , std::string *whyNot
                                , const std::string& masterObjective)const=0;

    virtual bool includesThisType(const StructureEnv_New* cm
                                  ,const std::string& childType
                                  ,std::string *whyNot
                                  , const std::string &masterObjective)const=0;

    virtual StructureEnv_New* getComplexVarRep(
        const StructureEnv_New* cm,
        const ABC_Data_New* var
        ,std::string* whyNot
        ,const std::string& masterObjective)const=0;

    virtual ABC_Data_New* getClassRep(const StructureEnv_New* cm,
                                      const StructureEnv_New* cvar,
                                      std::string* whyNot,
                                      const std::string& masterObjective)const=0;



    virtual StructureEnv_New* getEnv(){return env_;}
    virtual const StructureEnv_New* getEnv()const {return env_;}


  private:
    StructureEnv_New* env_;


  };


  namespace Real
  {
    struct types;
  }


  namespace _private {


    template<typename T>
    class Implements_Base_Type_New:public ABC_Type_of_Value
    {
    public:

      virtual bool putData(const StructureEnv_New* cm
                           ,const ABC_Data_New* v
                           ,ABC_Output* ostream
                           ,std::string* error,
                           const std::string& masterObjective)const override
      {
        auto data=dynamic_cast<const Implements_Value_New<T>* >(v);
        if (data==nullptr)
          {
            *error=masterObjective+ ": "+data->myType()+" is not a "+myType();
            return false;
          }
        else return putValue(cm,data->getValue(),ostream,error,masterObjective);
      }

      virtual bool getData(const StructureEnv_New* cm
                           ,ABC_Data_New*& v
                           , ABC_Input* istream
                           ,std::string* error
                           , const std::string& masterObjective)const override
      {
        T data;
        if (!getValue(cm,data,istream,error,masterObjective))
          return false;
        else
          {
            std::string id=cm->dataToId(v,error,masterObjective);
            if (id.empty()) return false;
            else{
                v= new Implements_Value_New<T>(id,data);
                return true;
              }
          }
      }

      virtual bool putValue(const StructureEnv_New* cm
                            ,const T& v
                            ,ABC_Output* ostream
                            ,std::string* error,
                            const std::string& masterObjective)const=0;

      virtual bool getValue(const StructureEnv_New* cm
                            ,T& v
                            , ABC_Input* istream
                            ,std::string* error
                            , const std::string& masterObjective)const =0;


      virtual bool isDataInDomain(const StructureEnv_New* cm,const ABC_Data_New* v
                                  , std::string *whyNot, const std::string& masterObjective)const override
      {
        auto x=dynamic_cast<const Implements_Value_New<T>* >(v);
        if (x==nullptr)
          {
            if (whyNot!=nullptr)
            *whyNot=masterObjective+": is not a "+Cls<T>::name();
            return false;
          }
        else
          return isValueInDomain(cm,x->getValue(),whyNot,masterObjective);

      }

      virtual bool isValueInDomain(const StructureEnv_New* cm
                                   ,const T &val
                                   , std::string *whyNot
                                   ,const std::string& masterObjective ) const=0;


      virtual bool includesThisType(const StructureEnv_New* cm,
                                    const std::string& childType,
                                    std::string *whyNot
                                    , const std::string &masterObjective)const override;

      virtual StructureEnv_New* getComplexVarRep(
          const StructureEnv_New* cm,
          const ABC_Data_New* ,std::string* ,const std::string& )const override
      {
        return nullptr;
      }

      virtual Implements_Value_New<T>* getClassRep(
          const StructureEnv_New* cm,
          const StructureEnv_New*   ,std::string*, const std::string& )const override
      {
        return nullptr;
      }



      virtual ~Implements_Base_Type_New(){}


      virtual bool isOfThisType
      (const StructureEnv_New *cm
       , const std::__cxx11::string &generalType
       , std::__cxx11::string *whyNot
       , const std::__cxx11::string &masterObjective) const override
      {

        if (myType()==generalType)
          return true;
        else
          {
            auto gTp
                =cm->idToTyped<T>(generalType,whyNot,masterObjective);
            std::string id=cm->dataToId(this,whyNot,masterObjective);
            if ((id.empty())||(gTp==nullptr))
              return false;
            else
              return gTp->includesThisType(cm,id,whyNot,masterObjective);
          }

      }

      // ABC_Data_New interface
    public:
      virtual std::__cxx11::string myType() const override
      {
        return Cls<T>::name();
      }
    };


    template<typename T>
    class Implements_Base_Type_New<T*>:public ABC_Type_of_Value
    {
    public:

      virtual bool isDataInDomain
      (const StructureEnv_New* cm
       ,const ABC_Data_New* v
       , std::string *whyNot
       , const std::string& masterObjective)const override
      {
        const std::string objective=masterObjective+": do not has it in domain";
        auto x=dynamic_cast<const Implements_Value_New<T*>* >(v);
        if (x==nullptr)
          {
            return false;
          }
        else
          return isValueInDomain(cm,x->getValue(),whyNot,objective);
      }

      virtual bool isValueInDomain(const StructureEnv_New* cm
                                   ,const T *val
                                   , std::string *whyNot
                                   ,const std::string& masterObjective ) const=0;

      virtual bool isOfThisType
      (const StructureEnv_New *cm
       , const std::__cxx11::string &generalType
       , std::__cxx11::string *whyNot
       , const std::__cxx11::string &masterObjective) const override
      {
        if (myType()==generalType)
          return true;
        else
          {
            auto gTp
                =cm->idToTyped<T*>(generalType,whyNot,masterObjective);
            std::string id=cm->dataToId(this,whyNot,masterObjective);
            if ((id.empty())||(gTp==nullptr))
              return false;
            else
              return gTp->includesThisType(cm,id,whyNot,masterObjective);
          }

      }

      virtual std::__cxx11::string myType() const override
      {
        return Cls<T*>::name();
      }

      virtual bool putData(const StructureEnv_New* cm
                           ,const ABC_Data_New* v
                           ,ABC_Output* ostream
                           ,std::string* error,
                           const std::string& masterObjective)const override
      {
        auto data=dynamic_cast<const Implements_Value_New<T*>* >(v);
        if (data==nullptr)
          {
            *error=masterObjective+ ": "+data->myType()+" is not a "+Cls<T>::name();
            return false;
          }
        else return putValue(cm,data->getValue(),ostream,error,masterObjective);
      }

      virtual bool getData(const StructureEnv_New* cm
                           ,ABC_Data_New*& v
                           , ABC_Input* istream
                           ,std::string* error
                           , const std::string& masterObjective)const override
      {
        T* data;
        if (!getValue(cm,data,istream,error,masterObjective))
          return false;
        else
          {
            std::string id=cm->dataToId(v,error,masterObjective);
            if (id.empty()) return false;
            else
              {
                v= new Implements_Value_New<T*>(id,data);
                return true;
              }
          }
      }

      virtual bool putValue(const StructureEnv_New* cm
                            ,const T* v
                            ,ABC_Output* ostream
                            ,std::string* error,
                            const std::string& masterObjective)const=0;

      virtual bool getValue(const StructureEnv_New* cm
                            ,T*& v
                            , ABC_Input* istream
                            ,std::string* error
                            , const std::string& masterObjective)const =0;



      virtual bool includesThisType(const StructureEnv_New* cm,
                                    const std::string& childType,
                                    std::string *whyNot
                                    , const std::string &masterObjective)const override;


      StructureEnv_New* getComplexVarRep(const StructureEnv_New* cm,
                                         const ABC_Data_New*
                                         ,std::string*
                                         ,const std::string& )const override

      {
        return nullptr;
      }

      virtual Implements_Value_New<T*>* getClassRep(const StructureEnv_New* cm,
                                                    const StructureEnv_New*   ,std::string*, const std::string& )const override
      {
        return nullptr;
      }


      virtual ~Implements_Base_Type_New(){
      }



    };


    class Implements_Data_Type_New_string
        : public Implements_Base_Type_New<std::string>
    {
    public:
      using typePredicate= bool(*) (const StructureEnv_New* cm,const std::string& val,
      const Implements_Data_Type_New_string* self, std::string* error,const std::string& obj);

      using getSet=std::set<std::string>(*)(const StructureEnv_New*,
      const Implements_Data_Type_New_string*);

      virtual buildByToken<std::string>* getBuildByToken(
          const StructureEnv_New* cm)const override;


      virtual std::set<std::string> alternativeNext(const StructureEnv_New* cm)const
      {
        return (*alternativeNext_)(cm,this);
      }

      virtual ~Implements_Data_Type_New_string(){}

      virtual bool putValue(const StructureEnv_New* cm,
                            const std::string& v,ABC_Output* ostream,std::string* whyNot
                            ,const std::string& masterObjective)const override
      {
        if (isValueInDomain(cm,v,whyNot,masterObjective))
          {
            ostream->put(v);
            return true;
          }
        else return false;
      }
      virtual bool getValue(const StructureEnv_New* cm
                            ,std::string& v, ABC_Input* istream,std::string* whyNot
                            ,const std::string& masterObjective)const override
      {

        if (!istream->get(v,whyNot,masterObjective))
          return false;
        else
          return isValueInDomain(cm,v,whyNot,masterObjective);
      }


      virtual bool isValueInDomain(const StructureEnv_New* cm
                                   ,const std::string &val
                                   , std::string *whyNot
                                   ,const std::string& masterObjective ) const override
      {
        if (comply_!=nullptr)
          return (*comply_)(cm,val,this,whyNot,masterObjective);
        else return true;
      }


      Implements_Data_Type_New_string(typePredicate complyPred=nullptr
          ,getSet alterNext=nullptr):
        comply_(complyPred),
        alternativeNext_(alterNext)

      {}
      Implements_Data_Type_New_string(const Implements_Data_Type_New_string& other)=default;

      Implements_Data_Type_New_string( Implements_Data_Type_New_string&& other)=default;

      Implements_Data_Type_New_string& operator=(const Implements_Data_Type_New_string& other)=default;
      Implements_Data_Type_New_string& operator=(Implements_Data_Type_New_string&& other)=default;


      // ABC_Data_New interface
    public:
      virtual bool empty() const override
      {
        return comply_==nullptr;
      }
      virtual void reset() override
      {
        comply_=nullptr;
        alternativeNext_=nullptr;
      }
      virtual Implements_Data_Type_New_string *clone() const override
      {
        return new Implements_Data_Type_New_string(*this);}

      virtual Implements_Data_Type_New_string *create() const override
      {return new Implements_Data_Type_New_string();}

    protected:
      typePredicate comply_;
      getSet alternativeNext_;
    };


  };

  namespace Identifier
  {
    inline
    std::size_t  getVersionNumber(const std::string &id)
    {
      auto m=id.find_last_of('_');
      if (m!=id.npos)
        {
          std::stringstream ss(id.substr(m));
          std::size_t n;
          if (ss>>n)
            return n;
          else
            return std::string::npos;
        }
      return std::string::npos;
    }
    void push_Types(Markov_CommandManagerVar* cm);


    inline
    std::pair<std::string,std::string> getId_Type(const std::string& idtype)
    {
      auto n=idtype.find(':');
      if (n!=idtype.npos)
        return {idtype.substr(0,n),idtype.substr(n)};
      else
        return {idtype,""};
    }


    inline
    std::string nextId(const std::string &id_typeTemplate)
    {
      auto p=getId_Type(id_typeTemplate);
      auto idT=p.first;

      auto n=getVersionNumber(idT);

      if (n!=std::string::npos)
        {
          ++n;
          idT= idT.substr(0,idT.find_last_of('_')+1)+std::to_string(n);
        }
      else
        idT= idT+"_0";
      if (!p.second.empty())
        return idT+" : "+p.second;
      else return idT;
    }


    class types;
  };


  class Implements_Identifier: public Implements_Data_Type_New<std::string>
  {
  public:

    friend class Identifier::types;
    static std::string ClassName(){return "Identifier";}

    virtual std::string myType()const override {return ClassName();}

    virtual std::set<std::string> alternativeNext(const StructureEnv_New* cm)const override;

    virtual bool isValueInDomain(const StructureEnv_New* cm,const std::string &idCandidate, std::string *whyNot,const std::string& objective ) const override;


    std::string getName()const {return name_;}

    void setName(const std::string& name){name_=name;}


    Implements_Identifier* clone()const override
    {
      return new Implements_Identifier(*this);
    }

    Implements_Identifier* create()const override
    {
      return new Implements_Identifier();
    }

    Implements_Identifier(){}

  private:
    static std::string toId
    (const std::string& name,
     bool isFixed,bool isVar, bool isType,
     bool isCommand,bool isNew, bool isUsed);

    Implements_Identifier
    (const std::string& name,
     bool isFixed,bool isVar, bool isType,
     bool isCommand,bool isNew, bool isUsed):
      Implements_Data_Type_New_string
      (nullptr,nullptr
       ),
      name_(name),isFixed_(isFixed)
    , isVar_(isVar), isType_(isType),isCommand_(isCommand)
    ,isNew_(isNew),isUsed_(isUsed)
    {}
    std::string name_;
    bool isFixed_;
    bool isVar_;
    bool isType_;
    bool isCommand_;
    bool isField_;
    bool isNew_;
    bool isUsed_;
  };

  namespace Identifier {

    struct types {
      template <class T>
      static Implements_Identifier* getVarType
      (const std::string& idName="")
      {
        return new Implements_Identifier
            (idName,T::isFixed,T::isVar
             ,T::isType,T::isCommand,T::isNew,T::isUsed);
      }




      template <class T>
      static std::string toId(const std::string& idName="")
      {
        return Implements_Identifier::toId
            (idName,T::isFixed,T::isVar
             ,T::isType,T::isCommand,T::isNew,T::isUsed);

      }


      struct idVar{
        typedef  std::string myC;
        typedef idVar selfType;

        static std::string myId(const std::string& varTypeName=""){return toId<selfType>(varTypeName );}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "Variable indentifer";}
        static std::string myWhatThis(){return "an identifier to a Variable";}

        static Implements_Identifier*
        varType(const std::string& varTypeName="")
        {return getVarType<selfType>(varTypeName);}


        constexpr static  bool isFixed=false;
        constexpr static  bool isVar=true;
        constexpr static  bool isType=false;
        static constexpr bool isCommand=false;
        static constexpr bool isNew=true;
        static constexpr bool isUsed=true;

      };

      struct idVarNew{
        typedef  std::string myC;
        typedef idVarNew selfType;

        static std::string myId(const std::string& varTypeName=""){return toId<selfType>(varTypeName );}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "New Variable indentifer";}
        static std::string myWhatThis(){return "an unused identifier to a Variable";}


        static Implements_Identifier*
        varType(const std::string& varTypeName="")
        {return getVarType<selfType>(varTypeName);}


        static constexpr bool isFixed=false;
        constexpr static  bool isVar=true;
        constexpr static  bool isType=false;
        static constexpr bool isCommand=false;
        static constexpr bool isNew=true;
        static constexpr bool isUsed=false;

      };





      struct idVarUsed{
        typedef  std::string myC;
        typedef idVarUsed selfType;

        static std::string myId(const std::string& varTypeName=""){return toId<selfType>(varTypeName );}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "An existing Variable indentifer";}
        static std::string myWhatThis(){return "an identifier to a Variable";}


        static Implements_Identifier*
        varType(const std::string& varTypeName="")
        {return getVarType<selfType>(varTypeName);}


        static constexpr bool isFixed=false;
        constexpr static  bool isVar=true;
        constexpr static  bool isType=false;
        static constexpr bool isCommand=false;
        static constexpr bool isNew=false;
        static constexpr bool isUsed=true;

      };


      struct idType{
        typedef  std::string myC;
        typedef idType selfType;

        static std::string myId(const std::string& varTypeName=""){return toId<selfType>(varTypeName );}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "a typeindentifer";}
        static std::string myWhatThis(){return "an identifier to a type";}


        static Implements_Identifier*
        varType(const std::string& varTypeName="")
        {return getVarType<selfType>(varTypeName);}


        static constexpr bool isFixed=false;
        constexpr static  bool isVar=false;
        constexpr static  bool isType=true;
        static constexpr bool isCommand=false;
        static constexpr bool isNew=false;
        static constexpr bool isUsed=true;

      };


      struct idCmd{
        typedef  std::string myC;
        typedef idCmd selfType;

        static std::string myId(){return toId<selfType>();}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "a typeindentifer";}
        static std::string myWhatThis(){return "an identifier to a type";}


        static Implements_Identifier*
        varType()
        {return getVarType<selfType>();}


        static constexpr bool isFixed=false;
        constexpr static  bool isVar=false;
        constexpr static  bool isType=false;
        static constexpr bool isCommand=true;
        static constexpr bool isNew=false;
        static constexpr bool isUsed=true;
      };




      struct idVarGiven{
        typedef  std::string myC;
        typedef idVarGiven selfType;

        static std::string myId(const std::string& idName){return toId<selfType>(idName );}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "defined Variable indentifer";}

        static std::string myWhatThis(){return "an identifier to a Variable";}




        static Implements_Identifier*
        varType(const std::string& varTypeName="")
        {return getVarType<selfType>(varTypeName);}


        static constexpr bool isFixed=true;
        constexpr static  bool isVar=true;
        constexpr static  bool isType=false;
        static constexpr bool isCommand=false;
        static constexpr bool isNew=false;
        static constexpr bool isUsed=true;
      };


    };
  }


  namespace fields
  {


    struct varType_Field
    {
      typedef std::string myC;
      typedef Identifier::types::idType myType;
      typedef Implements_Identifier vType;

      static std::string myId(){return "varType";}
      static std::string myIdType(){return myType::myId();}
      static std::string myTip(){return "a type of variable";}
      static std::string myWhatThis() {return "different types of variables";}
    };

    struct elementType_Field
    {
      typedef std::string myC;
      typedef Identifier::types::idType myType;
      typedef Implements_Identifier vType;

      static std::string myId(){return "elementType";}
      static std::string myIdType(){return myType::myId();}
      static std::string myTip(){return "type of element of container";}
      static std::string myWhatThis() {return "different types of variables";}
    };
    struct keyType_Field
    {
      typedef std::string myC;
      typedef Identifier::types::idType myType;
      typedef Implements_Identifier vType;

      static std::string myId(){return "keyType";}
      static std::string myIdType(){return myType::myId();}
      static std::string myTip(){return "type of key of container";}
      static std::string myWhatThis() {return "different types of variables";}
    };

  };


  namespace _private{

    template<typename T, template<typename> class C>
    class Implements_Container_Type_New:public Implements_Base_Type_New<C<T>>
    {
    public:



      virtual buildByToken<T>* getElementBuildByToken(const StructureEnv_New* cm)const
      {
        const Implements_Data_Type_New<T>* v= getElementDataType(cm);
        if (v!=nullptr)
          return new buildByToken<T>(cm,v);
        else return nullptr;
      }

      virtual const Implements_Data_Type_New<T>* getElementDataType(const StructureEnv_New* cm)const=0;

      virtual ~Implements_Container_Type_New(){}
    };



    template<typename T, template<typename> class C>
    class Implements_Container_Type_New<T*,C> :public Implements_Base_Type_New<C<T*>>
    {
    public:




      virtual buildByToken<T*>* getElementBuildByToken(const StructureEnv_New* cm)const
      {
        const Implements_Data_Type_New<T*>* v= getElementDataType(cm);
        if (v!=nullptr)
          return new buildByToken<T*>(cm,v);
        else return nullptr;
      }


      virtual const Implements_Data_Type_New<T*>* getElementDataType(const StructureEnv_New* cm)const=0;




      virtual ~Implements_Container_Type_New(){}

    };






    template<typename T>
    using My_vec = std::vector<T>;  // to fake that vector takes only one template argument


    template<typename T>
    class Implements_Data_Type_New_vector:public Implements_Container_Type_New<T,My_vec>
    {
    public:
      using typePredicate=bool(*)(const StructureEnv_New* cm,
      const std::vector<T>& val,
      std::string *whyNot,const std::string& masterObjective);

      using typeElementPredicate= bool (*)(const StructureEnv_New*cm
      , const std::vector<T>& val,
      typename std::vector<T>::const_iterator it, const T& elval,
      std::string *whyNot,const std::string& masterObjective);


      virtual bool putValue(const StructureEnv_New* cm,const std::vector<T>& v,ABC_Output* ostream,std::string* whyNot,const std::string& masterObjective)const override
      {
        if (this->isValueInDomain(cm,v,whyNot,masterObjective))
          {
            const Implements_Data_Type_New<T>* etype=
                this->getElementDataType(cm);
            ostream->put("\n[");
            for (auto it=v.begin(); it!=v.end(); ++it)
              {
                if(!etype->putValue
                   (cm,*it,ostream,whyNot,masterObjective))
                  {
                    return false;
                  }
              }
            ostream->put("]");
            return true;
          }
        else
          return false;
      }
      virtual bool getValue(const StructureEnv_New* cm
                            ,std::vector<T>& v
                            , ABC_Input* istream
                            ,std::string* whyNot
                            ,const std::string& masterObjective)const override
      {
        char c;
        const Implements_Data_Type_New<T>* etype=this->getElementDataType(cm);
        if (etype==nullptr)
          return false;
        while (!istream->nextCharIs('\n',true)){}
        if (!istream->nextCharIs('[',c))
          {
            *whyNot= masterObjective+": expected [ found"+c;
            return false;
          }
        else
          {
            auto iter=v.begin();
            while ((iter<v.end())&&(!istream->nextCharIs(']',false)))
              {
                T d;
                if (etype->getValue
                    (cm,d,istream,whyNot,masterObjective))
                  {
                    *iter=std::move(d);
                    ++iter;

                  }
                else
                  return false;

              }
            while ((!istream->nextCharIs(']',false)))
              {
                T d;
                if (etype->getValue
                    (cm,d,istream,whyNot,masterObjective))
                  {
                    v.push_back(std::move(d));
                  }
                else
                  return false;

              }
            if (this->isValueInDomain(cm,v,whyNot,masterObjective))
              return true;
            else
              return false;
          }

      }



      virtual buildByToken<std::vector<T>>* getBuildByToken(
          const StructureEnv_New* cm)const
      {
        return new buildByToken<std::vector<T>>(cm,this);
      }



      virtual ~Implements_Data_Type_New_vector(){}

      Implements_Data_Type_New_vector
      (const Implements_Data_Type_New<T>* elementVar=nullptr
          ,typePredicate complyPred=nullptr
          ,typeElementPredicate elemeComply=nullptr
          )
        :elementVar_(elementVar),complyPred_(complyPred),elemeComply_(elemeComply) {}




    protected:
      const Implements_Data_Type_New<T>* elementVar_;
      typePredicate complyPred_;
      typeElementPredicate elemeComply_;
    };



    template<typename T>
    class Implements_Data_Type_New_regular:public Implements_Base_Type_New<T>
    {
    public:
      typedef  Implements_Data_Type_New_regular<T> selfType;

      using typePredicate=bool (*) (const StructureEnv_New* cm, const T& data
      ,const selfType* self
      , std::string *whyNot, const std::string& masterObjective);

      using getSet=std::set<std::string>(*)(const StructureEnv_New* cm,
      const selfType* SELF);




      virtual buildByToken<T>* getBuildByToken(
          const StructureEnv_New* cm)const override
      {
        return new buildByToken<T>(cm,this);
      }

      virtual bool putValue(const StructureEnv_New* cm,
                            const T& v,ABC_Output* ostream,std::string* whyNot
                            ,const std::string& masterObjective)const override
      {
        if (this->isValueInDomain(cm,v,whyNot,masterObjective))
          {
            ostream->put(v);
            return true;
          }
        else return false;
      }


      virtual bool getValue(const StructureEnv_New* cm
                            ,T& v, ABC_Input* istream,std::string* whyNot
                            ,const std::string& masterObjective)const override
      {

        if (!istream->get(v,whyNot,masterObjective))
          return false;
        else
          return this->isValueInDomain(cm,v,whyNot,masterObjective);
      }


      virtual std::set<std::string> alternativeNext(const StructureEnv_New* cm)const
      {
        if (alternativesNext_!=nullptr)
          return (*alternativesNext_)(cm,this);
        else
          return {"<"+Cls<T>::name()+">"};
      }

      virtual ~Implements_Data_Type_New_regular(){}



      Implements_Data_Type_New_regular(typePredicate complyPred=nullptr,
                                       getSet alternatives=nullptr)
        :comply_(complyPred),alternativesNext_(alternatives)

      {}

      Implements_Data_Type_New_regular(const Implements_Data_Type_New_regular<T>& other)=default;
      Implements_Data_Type_New_regular& operator=(const Implements_Data_Type_New_regular<T>& other)=default;
      Implements_Data_Type_New_regular(Implements_Data_Type_New_regular<T>&& other)=default;
      Implements_Data_Type_New_regular& operator=(Implements_Data_Type_New_regular<T>&& other)=default;



      // ABC_Data_New interface
    public:
      virtual bool empty() const override
      {
        return comply_==nullptr;
      }
      virtual void reset() override
      {
        comply_=nullptr;
      }
      virtual Implements_Data_Type_New_regular *clone() const override
      {
        return new Implements_Data_Type_New_regular(*this);
      }
      virtual Implements_Data_Type_New_regular *create() const override
      {
        return new Implements_Data_Type_New_regular();
      }

      virtual bool isValueInDomain(const StructureEnv_New* cm
                                   ,const T &val
                                   , std::string *whyNot
                                   ,const std::string& masterObjective ) const override
      {
        if (comply_==nullptr)
          return true;
        else
          return (*comply_)(cm,val,this,whyNot,masterObjective);
      }

      friend class Real::types;
    protected:
      typePredicate comply_;
      getSet alternativesNext_;
    };


    template<typename T>
    using My_set = std::set<T>;  // to fake that set takes only one template argument

    template<typename T>
    class Implements_Data_Type_New_set:public Implements_Container_Type_New<T,My_set>
    {
    public:
      using typePredicate=bool (*) (const StructureEnv_New* cm
      ,const std::set<T>& val,const Implements_Data_Type_New_set* self
      ,std::string* whyNot, const std::string& masterObjective);

      using typeElementPredicate= bool (*)(const StructureEnv_New*cm
      ,const std::set<T>&val, const T& eVal
      ,const Implements_Data_Type_New_set* self
      ,std::string* whyNot, const std::string& masterObjective);

      virtual ~Implements_Data_Type_New_set(){}

      virtual bool putValue(const StructureEnv_New* cm
                            ,const std::set<T>& v
                            ,ABC_Output* ostream
                            ,std::string* whyNot
                            ,const std::string& masterObjective)const override
      {
        if (this->isValueInDomain(cm,v,whyNot,masterObjective))
          {
            const Implements_Data_Type_New<T>* etype=this->getElementDataType(cm);
            ostream->put("\n{");
            for (auto it=v.begin(); it!=v.end(); ++it)
              {
                if(!etype->put(cm,*it,ostream,whyNot,masterObjective))
                  {
                    ostream->put(*whyNot);
                    return false;
                  }
              }
            ostream->put("}");
            return true;
          }
        else
          return false;
      }

      virtual bool getValue(const StructureEnv_New* cm
                            ,std::set<T>& v, ABC_Input* istream,std::string* whyNot ,const std::string& masterObjective)const override
      {
        char c;
        const Implements_Data_Type_New<T>* etype=this->getElementDataType(cm);
        if (etype==nullptr)
          return false;
        while (!istream->nextCharIs('\n',true)){}
        if (!istream->nextCharIs('{',c))
          {
            *whyNot= masterObjective+": expected { found"+c;
            return false;
          }
        else
          {
            while (!istream->nextCharIs('}',false))
              {
                T d;
                if (etype->get(cm,d,istream,whyNot,masterObjective))
                  {

                    v.insert(std::move(d));
                  }
                else
                  return false;
              }
            if (this->isValueInDomain(cm,v,whyNot,masterObjective))
              return true;
            else
              return false;
          }

      }

      virtual buildByToken<std::set<T>>*
      getBuildByToken(const StructureEnv_New* cm)const
      {
        return new buildByToken<std::set<T>>(cm,this);
      }




      Implements_Data_Type_New_set(const Implements_Data_Type_New<T>* elementVar
                                   ,typePredicate complyPred
                                   ,typeElementPredicate elemeComply
                                   ):
        elementVar_(elementVar),complyPred_(complyPred),elemeComply_(elemeComply)
      {}



    protected:
      const Implements_Data_Type_New<T>* elementVar_;
      typePredicate complyPred_;
      typeElementPredicate elemeComply_;

    };

  };
  namespace fields
  {

    struct numCols_Field  {
      typedef std::size_t myC;

      typedef Implements_Data_Type_New<myC> vType;

      static std::string myId(){return "numCols";}
      static std::string myIdType(){return Cls<myC>::name();}
      static std::string myTip(){return "number of columns";}
      static std::string myWhatThis() {return "";}
    };

    struct isNumColsFixed_Field  {
      typedef bool myC;

      typedef Implements_Data_Type_New<myC> vType;

      static std::string myId(){return "isNumColsFixed";}
      static std::string myIdType(){return Cls<myC>::name();}
      static std::string myTip(){return "if fixed the number of columns";}
      static std::string myWhatThis() {return "";}
    };

    struct numRows_Field  {
      typedef std::size_t myC;

      typedef Implements_Data_Type_New<myC> vType;

      static std::string myId(){return "numRows";}
      static std::string myIdType(){return Cls<myC>::name();}
      static std::string myTip(){return "number of rows";}
      static std::string myWhatThis() {return "";}
    };

    struct isNumRowsFixed_Field  {
      typedef bool myC;

      typedef Implements_Data_Type_New<myC> vType;

      static std::string myId(){return "isNumRowsFixed";}
      static std::string myIdType(){return Cls<myC>::name();}
      static std::string myTip(){return "is fixed the number of rows";}
      static std::string myWhatThis() {return "";}
    };

  };
  namespace _private
  {

    template<typename T>
    class Implements_Data_Type_New_M_Matrix:public Implements_Container_Type_New<T,Markov_LA::M_Matrix>
    {
    public:
      using typePredicate=bool(*) (const StructureEnv_New* cm
      , const Markov_LA::M_Matrix<T>& val,
      const Implements_Data_Type_New_M_Matrix<T>* self
      , std::string * whyNot, const std::string& masterObjective);

      using elementType=Implements_Data_Type_New<T>*
      (*) (const StructureEnv_New* cm
      ,const std::vector<T>& val,
      std::size_t ncol, std::size_t nrow
      ,std::size_t i, std::size_t j,const Implements_Data_Type_New_M_Matrix<T>* self, std::string * whyNot, const std::string& masterObjective,
      Implements_Data_Type_New<T>* source);

      using getNumber= std::size_t (*)
      (const StructureEnv_New* cm
      ,const Implements_Data_Type_New_M_Matrix<T>* cv);

      virtual ~Implements_Data_Type_New_M_Matrix(){}


      virtual buildByToken<Markov_LA::M_Matrix<T>>* getBuildByToken(
          const StructureEnv_New* cm)const
      {
        return new buildByToken<Markov_LA::M_Matrix<T>>(cm,this);
      }


      virtual const Implements_Data_Type_New<T>* getElementDataType(const StructureEnv_New* cm)const
      {
        if (elementType_!=nullptr)
          return elementType_;
        else return cm->idToTyped<T>(Cls<T>::name());
      }

      virtual Implements_Data_Type_New<T>* getElementType(
          const StructureEnv_New* cm
          ,const std::vector<T>& val,
          std::size_t nrows, std::size_t ncols,
          std::size_t i, std::size_t j,std::string* whyNot
          , const std::string & masterObjective,
          Implements_Data_Type_New<T>* source=nullptr)const
      {
        if (getElement_!=nullptr)
        return (*getElement_)(cm,val,nrows,ncols,i,j,this,whyNot,masterObjective,source);
        else return source;
      }


      bool getValue(const StructureEnv_New *cm, Markov_LA::M_Matrix<T> &v, ABC_Input *istream, std::string *whyNot, const std::string &masterObjective) const{

      }

      bool putValue(const StructureEnv_New *cm, const Markov_LA::M_Matrix<T> &v, ABC_Output *ostream, std::string *error, const std::string &masterObjective) const
      {

      }


      Implements_Data_Type_New_M_Matrix
      (const Implements_Data_Type_New<T>* elementVar=nullptr
          ,typePredicate complyPred=nullptr
          ,elementType getElement=nullptr
          ,getNumber getNumCols=nullptr
          ,getNumber getNumRows=nullptr
          ,bool areColsFixed=false
          ,bool areRowsFixed=false):
        elementType_(elementVar)
      ,complyPred_(complyPred),getElement_(getElement),
        getNumCols_(getNumCols),getNumRows_(getNumRows),
        areColsFixed_(areColsFixed),areRowsFixed_(areRowsFixed){}







      std::size_t getNumberOfCols(const StructureEnv_New* cm)const
      {
        if (getNumCols_==nullptr)
          return 0;
        else
          return (*getNumCols_)(cm,this);
      }

      std::size_t getNumberOfRows(const StructureEnv_New* cm)const
      {
        if (getNumRows_==nullptr)
          return 0;
        else
          return (*getNumRows_)(cm,this);
      }

      bool hasFixedCols()const {return areColsFixed_;}
      bool hasFixedRows()const {return areRowsFixed_;}

      virtual bool empty()const
      {
        return elementType_==nullptr;
      }

      virtual void reset()
      {
        elementType_=nullptr;
        complyPred_=nullptr;
        getElement_=nullptr;
        getNumCols_=nullptr;
        getNumRows_=nullptr;
        areColsFixed_=false;
        bool areRowsFixed_=false;

      }

      virtual Implements_Data_Type_New_M_Matrix* clone()const
      {
        return new Implements_Data_Type_New_M_Matrix(*this);
      }
      virtual Implements_Data_Type_New_M_Matrix* create()const
      {
        return new Implements_Data_Type_New_M_Matrix();
      }

      virtual bool isValueInDomain(const StructureEnv_New* cm
                                   ,const Markov_LA::M_Matrix<T> &val
                                   , std::string *whyNot
                                   ,const std::string& masterObjective ) const
      {
        return (*complyPred_)(cm,val,this,whyNot,masterObjective);
      }

    protected:
      const Implements_Data_Type_New<T>* elementType_;
      typePredicate complyPred_;
      elementType getElement_;
      getNumber getNumCols_;
      getNumber getNumRows_;
      bool areColsFixed_;
      bool areRowsFixed_;
    };


    template<typename K,typename T, template<typename,typename> class D>
    class Implements_Dictionary_Type_New:public Implements_Base_Type_New<D<K,T>>
    {
    public:


      virtual const Implements_Data_Type_New<K>* getKeyType
      (const StructureEnv_New* cm)const=0;

      virtual const Implements_Data_Type_New<T>* getElementType
      (const StructureEnv_New* cm)const=0;

      virtual Implements_Data_Type_New<K>* getKeyType(
          const StructureEnv_New* cm
          ,const D<K,T>& val,
          std::string* whyNot
          , const std::string & masterObjective,
          Implements_Data_Type_New<K>* source=nullptr)const=0;


      virtual Implements_Data_Type_New<T>* getElementType(
          const StructureEnv_New* cm
          ,const D<K,T>& val,
          const K& key,
          std::string* whyNot
          , const std::string & masterObjective,
          Implements_Data_Type_New<T>* source=nullptr)const=0;

      virtual buildByToken<T>* getElementBuildByToken(const StructureEnv_New* cm)const
      {
        const Implements_Data_Type_New<T>* v= this->getElementType(cm);
        if (v!=nullptr)
          return new buildByToken<T>(cm,v);
        else return nullptr;
      }


      virtual buildByToken<K>* getKeyBuildByToken(const StructureEnv_New* cm)const
      {
        const Implements_Data_Type_New<K>* v= this->getKeyType(cm);
        if (v!=nullptr)
          return new buildByToken<K>(cm,v);
        else return nullptr;
      }



      virtual ~Implements_Dictionary_Type_New(){}
    };



    template<typename K, typename T>
    class Implements_Data_Type_New_pair
        :public Implements_Base_Type_New<std::pair<K,T>>
    {
    public:

      using typePredicate=typename Implements_Base_Type_New<std::pair<K,T>>::typePredicate;

      using typetypePredicate=typename Implements_Base_Type_New<std::pair<K,T>>::typetypePredicate;
      using typeValue=typename Implements_Base_Type_New<std::pair<K,T>>::typeValue;

      using typeElementPredicate = bool(*)(
      const StructureEnv_New*
      ,const std::pair<K,T> & p
      ,const T& x
      ,const Implements_Data_Type_New_pair<K,T>* v
      , std::string *WhyNot
      , const std::string& objective);

      using typeKeyPredicate = bool(*)(
      const StructureEnv_New*
      ,const std::pair<K,T> & p
      ,const K& k
      ,const Implements_Data_Type_New_pair<K,T>* v
      , std::string *WhyNot
      , const std::string& objective);


      using cvToType=Implements_Data_Type_New_pair<K,T>* (*)
      (const StructureEnv_New* cm
      ,const StructureEnv_New* cv,
      std::string* whyNot,const std::string& masterObjective);

      using typeToCv= StructureEnv_New* (*)
      (const StructureEnv_New* cm
      ,const Implements_Data_Type_New_pair<K,T>* classType,
      std::string* whyNot,const std::string& masterObjective);


      virtual bool putValue(const StructureEnv_New *cm, const std::pair<K,T> &v, ABC_Output *ostream, std::string *error, const std::string &masterObjective) const
      {

      }
      virtual bool getValue(const StructureEnv_New *cm, std::pair<K,T> &v, ABC_Input *istream, std::string *whyNot, const std::string &masterObjective) const
      {

      }


      virtual buildByToken<T>* getElementBuildByToken(const StructureEnv_New* cm)const
      {
        const Implements_Data_Type_New<T>* v= getElementDataType(cm);
        if (v!=nullptr)
          return new buildByToken<T>(cm,v);
        else return nullptr;
      }


      virtual const Implements_Data_Type_New<T>* getElementDataType(const StructureEnv_New* cm)const
      {
        std::string eletype=this->template get_Value<fields::elementType_Field>();
        if (!eletype.empty())
          {
            std::string whynot;
            return cm->idToTyped<T>(eletype,&whynot,"");
          }
        else return nullptr;

      }



      virtual buildByToken<K>* getKeyBuildByToken(const StructureEnv_New* cm)const
      {
        const Implements_Data_Type_New<K>* v= getKeyDataType(cm);
        if (v!=nullptr)
          return new buildByToken<K>(cm,v);
        else return nullptr;
      }

      virtual const Implements_Data_Type_New<K>* getKeyDataType(const StructureEnv_New* cm)const
      {
        std::string keytype=this->template get_Value<fields::keyType_Field>();
        if (!keytype.empty())
          {
            std::string whynot;
            return cm->idToTyped<K>(keytype,&whynot,"");
          }
        else return nullptr;

      }


      virtual bool isKeyInDomain(
          const StructureEnv_New* cm,
          const std::pair<K,T> &val
          ,K& elem
          , std::string *whyNot
          ,const std::string& masterObjective ) const
      {
        if (keyComply_==nullptr)
          return true;
        else
          return (*keyComply_)(cm,val,elem,this,whyNot,masterObjective);
      }



      virtual bool isElementInDomain
      (const StructureEnv_New* cm
       ,const std::pair<K,T> &val
       ,T& elem
       , std::string *whyNot
       ,const std::string& masterObjective) const
      {
        if (elemeComply_==nullptr)
          return true;
        else
          return (*elemeComply_)(cm,val,elem,this,whyNot,masterObjective);
      }






      static std::string ClassName()
      {
        return "Implements_Data_Type_New_of_"+Cls<std::pair<K,T>>::name();
      }

      virtual std::string myClass()const override
      {
        return ClassName();
      }


      virtual ~Implements_Data_Type_New_pair(){}





      virtual buildByToken<std::pair<K,T>> *getBuildByToken(const StructureEnv_New *cm) const override
      {
        return new buildByToken<std::pair<K,T>>(cm,this);
      }


      virtual StructureEnv_New* getComplexVarofTypeRep(
          const StructureEnv_New* cm,
          const ABC_Type_of_Value* var,std::string* whyNot,const std::string& masterObjective)const override
      {
        if (getCvFromType_==nullptr)
          return nullptr;
        else
          {
            auto v=dynamic_cast<const Implements_Data_Type_New_pair<K,T>*>(var);
            if (v==nullptr)
              return nullptr;
            else
              return (*getCvFromType_)(cm,v,whyNot,masterObjective);
          }
      }

      virtual Implements_Data_Type_New_pair<K,T>* getTypeClassRep(
          const StructureEnv_New* cm,
          const StructureEnv_New* cvar,
          std::string* whyNot,
          const std::string& masterObjective)const override
      {
        {
          if (getTypeFromCV_==nullptr)
            return nullptr;
          else
            {
              return (*getTypeFromCV_)(cm,cvar,whyNot,masterObjective);
            }
        }
      }


      Implements_Data_Type_New_pair(const StructureEnv_New* parent,
                                    const std::string& id
                                    ,const std::string& var
                                    ,const std::string& tip
                                    ,const std::string& whatthis
                                    , const std::string keyVar
                                    , const std::string elementVar
                                    ,typePredicate complyPred
                                    ,typetypePredicate typeComply
                                    ,typeKeyPredicate keyComply
                                    ,typeElementPredicate elemeComply
                                    ,typeValue  defaultValue
                                    ):
        Implements_Base_Type_New<std::pair<K, T> >         (parent,id,var,tip,whatthis,{},complyPred,typeComply,defaultValue)
      ,keyComply_(keyComply),elemeComply_(elemeComply)
      {
        this->template pushVar<fields::keyType_Field>(keyVar);
        this->template pushVar<fields::elementType_Field>(elementVar);
      }


      Implements_Data_Type_New_pair(const StructureEnv_New* parent):
        Implements_Base_Type_New<std::pair<K,T>>(parent)
      ,keyComply_(nullptr),elemeComply_(nullptr)
      {
        this->template pushVar<fields::keyType_Field>(Cls<K>::name());
        this->template pushVar<fields::elementType_Field>(Cls<T>::name());

      }
    private:
      typeKeyPredicate keyComply_;
      typeElementPredicate elemeComply_;
      cvToType getTypeFromCV_;
      typeToCv getCvFromType_;



    };

    template<typename K,typename T>
    using My_map = std::map<K,T>;  // to fake that set takes only one template argument


    template <class E>
    using String_map=std::map<std::string,E>;


    template<typename K, typename T>
    class Implements_Data_Type_New_map
        :public Implements_Dictionary_Type_New<K,T,My_map>
    {
    public:
      typedef Implements_Data_Type_New_map<K,T> selfType;

      using typePredicate=bool (*) (const StructureEnv_New* cm, const std::map<K,T>& data
      ,const selfType* self
      , std::string *whyNot, const std::string& masterObjective);

      using keyTypeGetter= const Implements_Data_Type_New<K>* (*)
      (const StructureEnv_New* cm,const selfType* self);

      using elementTypeGetter=const Implements_Data_Type_New<T>* (*)
      (const StructureEnv_New* cm,const selfType* self) ;


      using nextKeyType=Implements_Data_Type_New<K>* (*)(
          const StructureEnv_New* cm
          ,const std::map<K,T>& val,
          const selfType* self,
          std::string* whyNot
          , const std::string & masterObjective,
          Implements_Data_Type_New<K>* source);



      using nextElementType= Implements_Data_Type_New<T>* (*)(
          const StructureEnv_New* cm
          ,const std::map<K,T>& val,
          const K& key,
          const selfType* self,
          std::string* whyNot
          , const std::string & masterObjective,
          Implements_Data_Type_New<T>* source);



      virtual bool putValue(const StructureEnv_New* cm,const std::map<K,T>& v,ABC_Output* ostream,std::string* whyNot,const std::string &masterObjective)const override
      {
        if (this->isValueInDomain(cm,v,whyNot,masterObjective))
          {
            const Implements_Data_Type_New<K>* ktype=this->getKeyType(cm);

            const Implements_Data_Type_New<T>* etype=this->getElementType(cm);
            ostream->put("\n{");
            for (auto& e: v)
              {
                if(!ktype->putValue(cm,e.first,ostream,whyNot,masterObjective))
                  {
                    ostream->put(*whyNot);
                    return false;
                  }
                ostream->put(":\t");
                if(!etype->putValue(cm,e.second,ostream,whyNot,masterObjective))
                  {
                    ostream->put(*whyNot);
                    return false;
                  }
              }
            ostream->put("}");
            return true;
          }
        else
          return false;
      }
      virtual bool getValue(const StructureEnv_New* cm,std::map<K,T>& v, ABC_Input* istream,std::string* whyNot ,const std::string &masterObjective)const override
      {
        char c;
        const Implements_Data_Type_New<K>* ktype=this->getKeyType(cm);

        const Implements_Data_Type_New<T>* etype=this->getElementType(cm);
        if ((etype==nullptr)||(ktype==nullptr))
          return false;
        while (!istream->nextCharIs('\n',true)){}
        if (!istream->nextCharIs('{',c))
          {
            *whyNot= masterObjective+": expected { found"+c;
            return false;
          }
        else
          {
            while (!istream->nextCharIs('}',false))
              {
                K k;
                T d;
                if (!ktype->getValue
                    (cm,k,istream,whyNot,masterObjective))
                  return false;
                else if (!istream->nextCharIs(':',c))
                  {
                    *whyNot=masterObjective+ ": expected \":\" found: "+c;
                  }
                else if (!etype->getValue
                         (cm,d,istream,whyNot,masterObjective))
                  return false;
                else
                  {
                    v.insert({std::move(k),std::move(d)});
                  }
              }
            if (!this->isValueInDomain(cm,v,whyNot,masterObjective))
              return false;
            else
              return true;
          }

      }


      virtual buildByToken<std::map<K,T>>* getBuildByToken(
          const StructureEnv_New* cm)const override
      {
        return new buildByToken<std::map<K,T>>(cm,this);
      }


      virtual ~Implements_Data_Type_New_map(){}

      Implements_Data_Type_New_map()
      {
      }


      virtual const Implements_Data_Type_New<K>* getKeyType
      (const StructureEnv_New* cm)const
      {
        if (keyType_!=nullptr)
          return (*keyType_)(cm,this);
        else
          return cm->idToTyped<K>(Cls<K>::name());
      }

      virtual const Implements_Data_Type_New<T>* getElementType
      (const StructureEnv_New* cm)const
      {
        if (elementType_!=nullptr)
          return (*elementType_)(cm,this);
        else
          return cm->idToTyped<T>(Cls<T>::name());
      }



      virtual Implements_Data_Type_New<K>* getKeyType(
          const StructureEnv_New* cm
          ,const std::map<K,T>& val,
          std::string* whyNot
          , const std::string & masterObjective,
          Implements_Data_Type_New<K>* source)const
      {
        if (nextKey_==nullptr)
          return source;
        else
          return (*nextKey_)(cm, val,this,whyNot,masterObjective,source);
      }



      virtual Implements_Data_Type_New<T>* getElementType(
          const StructureEnv_New* cm
          ,const std::map<K,T>& val,
          const K& key,
          std::string* whyNot
          , const std::string & masterObjective,
          Implements_Data_Type_New<T>* source=nullptr)const
      {
        if (nextElement_==nullptr)
          return source;
        else
          return (*nextElement_)(cm, val,key,this,whyNot,masterObjective,source);
      }



      virtual bool empty() const override
      {
        return comply_==nullptr
            && keyType_==nullptr
            &&elementType_==nullptr
            &&nextKey_==nullptr
            &nextElement_==nullptr;
      }
      virtual void reset() override
      {
         comply_=nullptr;
             keyType_=nullptr;
            elementType_=nullptr;
            nextKey_=nullptr;
            nextElement_=nullptr;

      }

      virtual bool isValueInDomain(const StructureEnv_New* cm
                                   ,const std::map<K,T> &val
                                   , std::string *whyNot
                                   ,const std::string& masterObjective ) const
      {
         if (comply_==nullptr)
           return true;
         else return (*comply_)(cm,val,this,whyNot,masterObjective);
      }

      virtual selfType *clone() const override
      {
        return new selfType(*this);
      }
      virtual ABC_Data_New *create() const override
{
        return new selfType();
      }
    private:
      typePredicate comply_;
      keyTypeGetter keyType_;
      elementTypeGetter elementType_;
      nextKeyType nextKey_;
      nextElementType nextElement_;


      // ABC_Data_New interface
    };




  }

  namespace Variable {
    struct types;
  }

  namespace Data {
    struct types;
  }

  namespace _private {



    class Implements_Data_Type_New_ABC_Data_New:
        public Implements_Base_Type_New<ABC_Data_New*>

    {

    public:

      using typePredicate=bool (*) (const StructureEnv_New* cm, const ABC_Data_New* data,
      const Implements_Data_Type_New_ABC_Data_New * self
      , std::string* whyNot, const std::string& masterObjective);


      using elementType=Implements_Identifier* (*) (const StructureEnv_New* cm,
      const ABC_Data_New* data,const Implements_Data_Type_New_ABC_Data_New* self
      , std::string* whyNot, const std::string& masterObjective, Implements_Identifier* source);


      virtual bool isDataInDomain
      (const StructureEnv_New* cm
       ,const ABC_Data_New* v
       , std::string *whyNot
       ,const std::string& masterObjective ) const override
      {return isValueInDomain(cm,v,whyNot,masterObjective);}


      virtual bool putData(const StructureEnv_New* cm
                           ,const ABC_Data_New* v
                           ,ABC_Output* ostream
                           ,std::string* error,
                           const std::string& masterObjective)const override
      {
        return putValue(cm,v,ostream,error,masterObjective);
      }

      virtual bool getData(const StructureEnv_New* cm
                           ,ABC_Data_New*& v
                           , ABC_Input* istream
                           ,std::string* error
                           , const std::string& masterObjective)const override
      {
        return getValue(cm,v,istream,error,masterObjective);
      }


      virtual bool putValue(const StructureEnv_New* cm,
                            const ABC_Data_New* v,ABC_Output* ostream
                            ,std::string* whyNot
                            ,const std::string& masterObjective)const override;
      virtual bool getValue(const StructureEnv_New* cm
                            ,ABC_Data_New*& v, ABC_Input* istream,std::string* whyNot
                            ,const std::string& masterObjective)const override
      {

      }




      virtual ~Implements_Data_Type_New_ABC_Data_New();



      virtual const Implements_Identifier* getElementType()const
      {
        return idType_;
      }


      virtual Implements_Identifier* getElementType
      (const StructureEnv_New* cm,
       const ABC_Data_New* data
       , std::string* whyNot, const std::string& masterObjective
       , Implements_Identifier* source) const
      {
        if (getElement_==nullptr)
          return nullptr;
        else
          return (*getElement_)(cm,data,this,whyNot,masterObjective,source);
      }

      virtual buildByToken<ABC_Data_New*>* getBuildByToken(const StructureEnv_New* cm)const override
      {
        return new buildByToken<ABC_Data_New*>(cm,this);
      }

      virtual bool ConvertToClass()const
      {
        return convertToClass_;
      }


      friend class Data::types;

      virtual bool empty() const override
      {
        return idType_==nullptr&&typeComply_==nullptr;
      }
      virtual void reset() override
      {
        idType_=nullptr;
        typeComply_=nullptr;
      }
      virtual Implements_Data_Type_New_ABC_Data_New *clone() const override
      {
        return new Implements_Data_Type_New_ABC_Data_New(*this);
      }
      virtual Implements_Data_Type_New_ABC_Data_New *create() const override
      {
        return new Implements_Data_Type_New_ABC_Data_New();
      }

      // Implements_Base_Type_New<T *> interface
    public:
      virtual bool isValueInDomain
      (const StructureEnv_New *cm
       ,const  ABC_Data_New *val, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const override

      {
        if (typeComply_!=nullptr)
          return (*typeComply_)(cm,val,this,whyNot,masterObjective);
        else return true;
      }

      void setDataType(const std::string& name)
      {
        idType_->setName(name);
      }
      std::string getDataType()const
      {
        return idType_->getName();
      }

    private:

      Implements_Data_Type_New_ABC_Data_New
      (  Implements_Identifier* idType=nullptr
          , typePredicate typeComply=nullptr
          ,elementType getElement=nullptr
          ,bool convertToClass=true
          ):
        idType_(idType),typeComply_(typeComply),getElement_(getElement),convertToClass_(convertToClass)
      {}


      Implements_Identifier* idType_;
      typePredicate typeComply_;
      elementType getElement_;
      bool convertToClass_;
      // ABC_Data_New interface

    };



    class Implements_Data_Type_New_Implements_Var:
        public Implements_Base_Type_New<Implements_Var>
    {

    public:
      using typePredicate=bool (*)
      (const StructureEnv_New * cm, const Implements_Var& iv,
      const Implements_Data_Type_New_Implements_Var* self
      , std::string * whyNot,const std::string& masterObjective);

      using  keyType= Implements_Identifier* (*)
      (const StructureEnv_New * cm, const Implements_Var& iv,
      const Implements_Data_Type_New_Implements_Var* self
      , std::string * whyNot,const std::string& masterObjective
      ,Implements_Identifier* source);

      using  elemType= Implements_Data_Type_New<ABC_Data_New*>* (*)
      (const StructureEnv_New * cm, const Implements_Var& iv,
      const Implements_Data_Type_New_Implements_Var* self
      , std::string * whyNot,const std::string& masterObjective
      ,Implements_Data_Type_New<ABC_Data_New*>* source);


      virtual bool putValue(const StructureEnv_New* cm
                            ,const Implements_Var& v
                            ,ABC_Output* ostream
                            ,std::string* error,
                            const std::string& masterObjective)const override
      {

      }

      virtual bool getValue
      (const StructureEnv_New* cm
       ,Implements_Var& v, ABC_Input* istream,std::string* whyNot
       ,const std::string& masterObjective)const override
      {

      }

      virtual ~Implements_Data_Type_New_Implements_Var(){}


      virtual const Implements_Identifier* getKeyType(const StructureEnv_New* cm)const
      {
        return idType_;
      }


      virtual Implements_Identifier* getKeyType
      (const StructureEnv_New* cm
       , const Implements_Var& v, std::string* whyNot, const std::string& masterObjective,
       Implements_Identifier* source)const
      {
        if (getKey_==nullptr)
          {
            return source;
          }
        else return (*getKey_)(cm,v,this,whyNot,masterObjective,source);
      }

      virtual const Implements_Data_Type_New<ABC_Data_New*>* getElementType(const StructureEnv_New* cm)const
      {
        return dataType_;
      }


      virtual Implements_Data_Type_New<ABC_Data_New*>* getElementType
      (const StructureEnv_New* cm, const Implements_Var& v,
       std::string* whyNot,
       const std::string& masterObjective,Implements_Data_Type_New<ABC_Data_New*>* source)const
      {
        if (getElement_==nullptr)
          return source;
        else return (*getElement_)(cm,v,this,whyNot,masterObjective,source);
      }

      virtual buildByToken<Implements_Var>* getBuildByToken(const StructureEnv_New* cm)const override
      {
        return new buildByToken<Implements_Var>(cm,this);
      }

      virtual void setVariable(const Implements_Var& v)
      {
        idType_->setName(v.id);
        dataType_->setDataType(v.data->myType());
      }


      friend class Variable::types;

      virtual bool empty()const override
      {
        return idType_==nullptr
            &&dataType_==nullptr
            &&comply_==nullptr
            &&getKey_==nullptr
            &&getElement_==nullptr;

      }

      virtual void reset() override
      {
        idType_=nullptr;
        dataType_=nullptr;
        comply_=nullptr;
        getKey_=nullptr;
        getElement_=nullptr;

      }

      virtual Implements_Data_Type_New_Implements_Var* clone()const override
      {
        return new Implements_Data_Type_New_Implements_Var(*this);
      }
      virtual Implements_Data_Type_New_Implements_Var* create()const override
      {
        return new Implements_Data_Type_New_Implements_Var();
      }


      virtual bool isValueInDomain(const StructureEnv_New* cm
                                   ,const Implements_Var &val
                                   , std::string *whyNot
                                   ,const std::string& masterObjective ) const override
      {
        return (*comply_)(cm,val,this,whyNot,masterObjective);
      }



    private:


      Implements_Data_Type_New_Implements_Var
      ( Implements_Identifier* idType=nullptr,
        Implements_Data_Type_New<ABC_Data_New*>* dataType=nullptr,
        typePredicate comply=nullptr,
        elemType getElement=nullptr,
        keyType getKey=nullptr);


      Implements_Identifier* idType_;
      Implements_Data_Type_New<ABC_Data_New*>* dataType_;
      typePredicate comply_;
      elemType getElement_;
      keyType getKey_;

     };



  }

  namespace ComplexVar
  {
    struct types;
  }

  namespace _private {


    class Implements_Data_Type_New_StructureEnv:
        public Implements_Base_Type_New<StructureEnv_New*>
    {
    public:

      using typePredicate= bool(*) (const StructureEnv_New* cm,const StructureEnv_New* val,
      const Implements_Data_Type_New_StructureEnv* self
      , std::string* error,const std::string& obj);


      using elementType=Implements_Data_Type_New<Implements_Var>*
      (*) (const StructureEnv_New* cm
      ,const StructureEnv_New* val,
      std::size_t iField, const Implements_Data_Type_New_StructureEnv* self
      , std::string * whyNot, const std::string& masterObjective,
      Implements_Data_Type_New<Implements_Var>* source);



      virtual bool isDataInDomain(const StructureEnv_New* cm,
                                  const StructureEnv_New *val
                                  , std::string *whyNot
                                  ,const std::string& masterObjective ) const
      {
        return isValueInDomain(cm,val,whyNot,masterObjective);
      }

      virtual bool isDataInDomain(const StructureEnv_New* cm,
                                  const ABC_Data_New* val
                                  , std::string *whyNot
                                  ,const std::string& masterObjective ) const override
      {
        auto s=dynamic_cast<const StructureEnv_New*>(val);
        if (s==nullptr)
          {
            *whyNot=masterObjective+": is not a structureEnv_New";
            return false;
          }
        else return isValueInDomain(cm,s,whyNot,masterObjective);

      }




      virtual bool isValueInDomain (const StructureEnv_New* cm,const StructureEnv_New* val,
                                    std::string* error,const std::string& obj)const override
      {
        if (comply_==nullptr)
          return true;
        else
          return (*comply_)(cm,val,this, error,obj);
      }




      virtual bool putValue(const StructureEnv_New* cm
                            ,const StructureEnv_New* v,
                            ABC_Output* ostream
                            ,std::string* whyNot
                            ,const std::string &masterObjective)const override
      {

      }


      virtual bool getValue(const StructureEnv_New* cm
                            ,StructureEnv_New*& v
                            , ABC_Input* istream
                            ,std::string* whyNot
                            ,const std::string &masterObjective)const override
      {

      }


      virtual bool hasAllFields(const StructureEnv_New* e,const StructureEnv_New *val
                                , std::string *whyNot=nullptr
          ,const std::string& masterObjective="") const
      {
        if (hasAll_!=nullptr)
          return (*hasAll_)(e,val,this,whyNot,masterObjective);
        else
          return false;

      }

      virtual bool hasMandatoryFields(const StructureEnv_New* e,
                                      const StructureEnv_New *val
                                      , std::string *whyNot=nullptr
          ,const std::string& masterObjective="" ) const
      {
          if (hasMandatory_!=nullptr)
            return (*hasMandatory_)(e,val,this,whyNot,masterObjective);
          else
            return true;
      }



      virtual const Implements_Data_Type_New<Implements_Var>*
      getElementType()const
      {
        return  elementType_;
      }

      virtual Implements_Data_Type_New<Implements_Var>*
      getElementType (const StructureEnv_New* cm
                      ,const StructureEnv_New* val,
                      std::size_t iField,
                      std::string * whyNot, const std::string& masterObjective,
                      Implements_Data_Type_New<Implements_Var>* source) const
      {
        return (*elem_)(cm,val,iField,this,whyNot,masterObjective,source);
      }


      virtual bool empty()const override
      {
        return   fields_.empty()
            &&(elementType_==nullptr)
            &&(comply_==nullptr)
            &&(hasMandatory_==nullptr)
            &&(hasAll_==nullptr)
            &&(elem_==nullptr);

      }

      virtual void reset() override
      {
        fields_.clear();
        elementType_=nullptr;
        comply_=nullptr;
        hasMandatory_=nullptr;
        hasAll_=nullptr;
        elem_=nullptr;

      }

      virtual Implements_Data_Type_New<StructureEnv_New*>* clone()const override
      {
        return new Implements_Data_Type_New<StructureEnv_New*>(*this);
      }
      virtual ABC_Data_New* create()const override
      {
        return new Implements_Data_Type_New<StructureEnv_New*>();
      }




      virtual buildByToken<StructureEnv_New*>* getBuildByToken(
          const StructureEnv_New* cm)const override
      {
        return new buildByToken<StructureEnv_New*>(cm,this);
      }

      virtual ~Implements_Data_Type_New_StructureEnv(){}

      friend class Markov_IO_New::ComplexVar::types;

      const std::vector<std::pair<Implements_Var,bool>>&
      getFields()const
      {
        return fields_;
      }

    protected:
      Implements_Data_Type_New_StructureEnv(
          std::vector<std::pair<Implements_Var,bool>> fields,
          const Implements_Data_Type_New<Implements_Var>* elemeType,
          typePredicate comply,
          typePredicate hasMandatory,
          typePredicate hasAll,
          elementType elem):
        fields_(fields),
        elementType_(elemeType),
        comply_(comply),
        hasMandatory_(hasMandatory),
        hasAll_(hasAll),
        elem_(elem)
      {}

      Implements_Data_Type_New_StructureEnv()=default;
      Implements_Data_Type_New_StructureEnv(const Implements_Data_Type_New_StructureEnv& other)=default;

      Implements_Data_Type_New_StructureEnv(Implements_Data_Type_New_StructureEnv&& other)=default;

      Implements_Data_Type_New_StructureEnv& operator=(Implements_Data_Type_New_StructureEnv&& other)=default;
      Implements_Data_Type_New_StructureEnv& operator=(const Implements_Data_Type_New_StructureEnv& other)=default;

      std::vector<std::pair<Implements_Var,bool>> fields_;
      const Implements_Data_Type_New<Implements_Var>* elementType_;
      typePredicate comply_;
      typePredicate hasMandatory_;
      typePredicate hasAll_;

      elementType elem_;

    };






  };

  namespace Real
  {
    typedef  double myC;
    typedef  Implements_Data_Type_New<myC> vType;

    struct fields
    {
      struct value  {
        typedef double myC;
        static std::string myId(){ return "Value";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return " a given value";}
        static std::string myWhatThis(){return "a given "+Cls<myC>::name()+" value";}
      };


    };



    struct types
    {

      struct nonZero
      {
        static std::string myId(){return "real_nonZero";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "any non zero real number";}
        static std::string myWhatThis() {return "";}

        static bool comply
        (const StructureEnv_New* cm
         ,const myC& x
         ,const vType* ,
         std::string *WhyNot
         , const std::string& objective)
        {
          if (std::abs(x)<std::numeric_limits<double>::epsilon())
            {
              *WhyNot=objective+": x="+std::to_string(x)+"is too close to zero";
              return false;
            }
          else
            return true;
        }

        static std::set<std::string> alternativeNext
        (const StructureEnv_New*
         ,const vType* )
        {
          return {"<non zero number>"};
        }



        static Implements_Data_Type_New<myC>*
        varType()
        {
          return new Implements_Data_Type_New<myC>
              (&comply,&alternativeNext);
        }
        static Implements_Data_Type_New<myC>*
        varType(Implements_Data_Type_New<myC>* source)
        {
          source->comply_=&comply;
          source->alternativesNext_=&alternativeNext;
          return source;

        }

      };



      struct nonNegative
      {
        static std::string myId(){return "real_positive_or_zero";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "zero or positive real number";}
        static std::string myWhatThis() {return "";}

        static bool comply
        (const StructureEnv_New* cm
         ,const myC& x
         ,const vType* ,
         std::string *WhyNot
         , const std::string& objective)
        {
          if ( x < 0.0)
            {
              *WhyNot=objective+": x="+std::to_string(x)+"is too close to zero";
              return false;
            }
          else
            return true;
        }

        static std::set<std::string> alternativeNext
        (const StructureEnv_New*
         ,const vType* )
        {
          return {"<zero or positive number>"};
        }



        static Implements_Data_Type_New<myC>*
        varType()
        {
          return new Implements_Data_Type_New<myC>
              (&comply,&alternativeNext);
        }
        static Implements_Data_Type_New<myC>*
        varType(Implements_Data_Type_New<myC>* source)
        {
          source->comply_=&comply;
          source->alternativesNext_=&alternativeNext;
          return source;

        }

      };


      struct positive
      {
        static std::string myId(){return "real_positive";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "any postive non zero real number";}
        static std::string myWhatThis() {return "";}

        static bool comply
        (const StructureEnv_New* cm
         ,const myC& x
         ,const vType* ,
         std::string *WhyNot
         , const std::string& objective)
        {
          if (x < std::numeric_limits<double>::epsilon())
            {
              *WhyNot=objective+": x="+std::to_string(x)+" too small or negative";
              return false;
            }
          else
            return true;
        }

        static std::set<std::string> alternativeNext
        (const StructureEnv_New*
         ,const vType* )
        {
          return {"<positive number>"};
        }



        static Implements_Data_Type_New<myC>*
        varType()
        {
          return new Implements_Data_Type_New<myC>
              (&comply,&alternativeNext);
        }
        static Implements_Data_Type_New<myC>*
        varType(Implements_Data_Type_New<myC>* source)
        {
          source->comply_=&comply;
          source->alternativesNext_=&alternativeNext;
          return source;

        }

      };


      struct Zero
      {
        typedef  double myC;
        typedef  Implements_Data_Type_New<myC> vType;
        static std::string idVar(){return "Real_zero";}
        static std::string idType(){return Cls<myC>::name();}
        static std::string Tip(){return "zero real number";}
        static std::string WhatThis() {return "";}

        static bool comply
        (const StructureEnv_New*
         ,const myC& x
         ,const vType* ,
         std::string *WhyNot
         , const std::string& objective)
        {
          if (std::abs(x)>std::numeric_limits<double>::epsilon())
            {
              *WhyNot=objective+": x="+std::to_string(x)+"is too far from zero";
              return false;
            }
          else
            return true;
        }

        static std::set<std::string> alternativeNext
        (const StructureEnv_New*
         ,const vType* )
        {
          return {"0.0"};
        }



        static Implements_Data_Type_New<myC>*
        varType()
        {
          return new Implements_Data_Type_New<myC>
              (&comply,&alternativeNext);
        }
        static Implements_Data_Type_New<myC>*
        varType(Implements_Data_Type_New<myC>* source)
        {
          source->comply_=&comply;
          source->alternativesNext_=&alternativeNext;
          return source;
        }
      };



      struct Given
      {
        typedef  double myC;
        typedef  Implements_Data_Type_New<myC> vType;
        static std::string idVar(myC x){return "Real_given_"+std::to_string(x);}
        static std::string idType(){return Cls<myC>::name();}
        static std::string Tip(){return "given real number";}
        static std::string WhatThis() {return "";}

        static bool comply
        (const StructureEnv_New* cm
         ,const myC& x
         ,const vType* v,
         std::string *WhyNot
         , const std::string& objective)
        {
          myC value;
          if (!v->getEnv()->getDataValue<typename fields::value>(value,WhyNot,objective))
            return false;


          if (std::abs(x-value)>std::numeric_limits<double>::epsilon())
            {
              *WhyNot=objective+": x="+std::to_string(x)+"is too far from zero";
              return false;
            }
          else
            return true;
        }

        static std::set<std::string> alternativeNext
        (const StructureEnv_New* cm
         ,const vType* v )
        {
          myC value;
          if (!v->getEnv()->getDataValue<typename fields::value>(value))
            return {};
          else
            return {std::to_string(value)};
        }



        static Implements_Data_Type_New<myC>*
        varType(myC val)
        {
          auto out= new Implements_Data_Type_New<myC>
              (&comply,&alternativeNext);
          out->getEnv()->pushVar<typename fields::value>(val);
          return out;
        }
        static Implements_Data_Type_New<myC>*
        varType(Implements_Data_Type_New<myC>* source,myC val)
        {
          source->comply_=&comply;
          source->alternativesNext_=&alternativeNext;
          source->getEnv()->pushVar<typename fields::value>(val);
          return source;
        }


      };



    };
    void push_Types(Markov_CommandManagerVar* cm);

  };


  namespace Matrix
  {
    template <typename T>
    using vType=  Implements_Data_Type_New<Markov_LA::M_Matrix<T>>;
    struct Comply
    {
      template<typename T>
      static bool Size(
          const Markov_LA::M_Matrix<double>& x,
          std::size_t numRows, std::size_t numCols,
          std::string* whyNot, const std::string& masterObjective)
      {
        std::string objective=masterObjective+": size mismatch";
        if (Markov_LA::nrows(x)!=numRows)
          {
            *whyNot=objective+": rows required: "
                +std::to_string(numRows)+" present:"
                +std::to_string(Markov_LA::nrows(x));
            return false;
          }
        else if(Markov_LA::ncols(x)!=numCols)
          {
            *whyNot=objective+": rows required: "+std::to_string(numCols)
                +" present: "+std::to_string(Markov_LA::ncols(x));
            return false;
          }
        return true;
      }


      template<typename T>
      static bool notAllZero(const Markov_LA::M_Matrix<T> &x
                             ,std::string *whyNot
                             , const std::string& masterObjective)
      {
        for (auto it=x.begin(); it!=x.end(); ++it)
          if (*it!=0)
            return true;
        *whyNot=masterObjective+": all values are zero";
        return false;
      }


      template<typename T>
      static bool RowSumIsZero(const Markov_LA::M_Matrix<T> &x
                               ,std::string *whyNot
                               , const std::string& masterObjective)
      {
        auto s=Markov_LA::sum(x);
        for (std::size_t i=0; i<nrows(s); ++i)
          if (s(i,0)!=T(0))
            {
              *whyNot=masterObjective+": sum of "+std::to_string(i)+"th row is not zero: "+std::to_string(s(i,0));
              return false;
            }
        return true;
      }


      template<typename T>
      static bool RowSumIsOne(const Markov_LA::M_Matrix<T> &x
                              ,std::string *whyNot
                              , const std::string& masterObjective)
      {
        auto s=Markov_LA::sum(x);
        for (std::size_t i=0; i<nrows(s); ++i)
          if (std::abs(s(i,0)-T(1))>std::sqrt(std::numeric_limits<T>::epsilon()))
            {
              *whyNot=masterObjective+": sum of "+std::to_string(i)+"th row is not one: "+std::to_string(s(i,0));
              return false;
            }
        return true;
      }


      template<typename T>
      static  bool OffDiagPositive(const Markov_LA::M_Matrix<T> &x, std::string *whyNot, const std::string &masterObjective)
      {
        for (std::size_t i=0; i<nrows(x); ++i)
          for (std::size_t j=0; j<nrows(x); ++j)
            if ((i!=j)&&(x(i,j)<T(0)))
              {
                *whyNot=masterObjective+": negative off diagonal value found: x("  +std::to_string(i)+","+std::to_string(j)+")= "+std::to_string(x(i,j));
                return false;
              }
        return true;
      }


      template<typename T>
      static  bool FiniteEquilibrium(const Markov_LA::M_Matrix<T> &x, std::string *whyNot, const std::string &masterObjective)
      {
        if (nrows(x)==0)
          return true;
        else
          for (std::size_t i=0; i<nrows(x)-1; ++i)
            for (std::size_t j=i+1; j<nrows(x); ++j)
              if ((x(i,j)>0) && (x(j,i)==T(0)))
                {
                  *whyNot=masterObjective+": forward rate positive: x("
                      +std::to_string(i)+","+std::to_string(j)+")= "
                      +std::to_string(x(i,j))
                      + "and reverse rate is zero: "
                      +std::to_string(j)+","+std::to_string(i)+")= "
                      +std::to_string(x(j,i));
                  return false;

                }
              else if((x(j,i)>0) && (x(i,j)==T(0)))
                {
                  *whyNot=masterObjective+": forward rate zero: x("
                      +std::to_string(i)+","+std::to_string(j)+")= "
                      +std::to_string(x(i,j))
                      + "and reverse rate is positive: "
                      +std::to_string(j)+","+std::to_string(i)+")= "
                      +std::to_string(x(j,i));
                  return false;
                }
        return true;

      }



    };
    class ElementComply
    {
    public:

      template<typename T>
      static bool RowSumIsZero
      (const Markov_LA::M_Matrix<T> &x
       ,typename Markov_LA::M_Matrix<T>::const_iterator it
       , T& e
       , std::string *whyNot
       , const std::string &masterObjective)
      {
        std::size_t i=it.iCol();
        std::size_t j=it.jRow();
        if (i==j)
          {
            T sum=T(0);
            for (std::size_t k=0; k<ncols(x); ++k)
              {
                if (k!=i) sum+=x(i,k);
              }
            e=-sum;
            return true;
          }
      }

      template<typename T>
      static  bool OffDiagPositive
      (const Markov_LA::M_Matrix<T> &x
       ,typename Markov_LA::M_Matrix<T>::const_iterator it
       , const T& e
       , std::string *whyNot
       , const std::string &masterObjective)
      {
        std::size_t i=it.iCol();
        std::size_t j=it.jRow();

        if (i==j)
          {
            if (e>0)
              {
                *whyNot=masterObjective+": positive value in diagonal";
                return false;
              }
            else
              return true;
          }
        else if (e<0)
          {
            *whyNot=masterObjective+": negative value off diagonal";
            return false;
          }
        else
          return true;

      }



    };


    template<typename T>
    void push_Types(Markov_CommandManagerVar* cm);
  };


  namespace Data {
    typedef Implements_Data_Type_New<ABC_Data_New*> vType;

    struct types
    {

      struct data{
        typedef  ABC_Data_New* myC;
        static std::string myId(){return "_data";}
        static std::string myId(const std::string& name)
        {return myId()+name;}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){ return "tip";}
        static std::string myWhatThis() {return "aht";}

        static bool comply(const StructureEnv_New* cm,
                           const ABC_Data_New* data,
                           const Implements_Data_Type_New<myC>* self,
                           std::string *whyNot, const std::string& masterObjective)
        {
          return self->getElementType()->isValueInDomain(cm,data->myType(),whyNot,masterObjective);
        }

        static Implements_Data_Type_New<myC>*
        varType(const std::string& nameoftype)
        {
          return new Implements_Data_Type_New<ABC_Data_New*>(
                Identifier::types::idType::varType(nameoftype)
                ,comply, nullptr,true);
        }

      };


    };
  };


  namespace Variable {
    typedef Implements_Data_Type_New<Implements_Var> vType;

    struct types
    {

      struct varNew{
        typedef  Implements_Var myC;
        static std::string myId(){return "_varNew";}
        static std::string myId(const std::string& name)
        {return myId()+name;}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){ return "tip";}
        static std::string myWhatThis() {return "aht";}


        static Implements_Data_Type_New<myC>*
        varType(const std::string nameoftype="")
        {

          return new Implements_Data_Type_New<Implements_Var>(
                Identifier::types::idVarNew::varType(nameoftype)
                ,Data::types::data::varType(nameoftype)
                ,nullptr,nullptr);
        }


      };

      struct varUsed{
        typedef  Implements_Var myC;
        static std::string myId(){return "_varUsed";}
        static std::string myId(const std::string& name)
        {return myId()+name;}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){ return "tip";}
        static std::string myWhatThis() {return "aht";}


        static Implements_Data_Type_New<myC>*
        varType(const std::string nameoftype="")
        {

          return new Implements_Data_Type_New<Implements_Var>(
                Identifier::types::idVarUsed::varType(nameoftype)
                ,Data::types::data::varType(nameoftype)
                ,nullptr,nullptr);
        }



      };



      struct varGiven{
        typedef  Implements_Var myC;
        static std::string myId(){return "_varGiven";}
        static std::string myId(const std::string& name)
        {return myId()+name;}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){ return "tip";}
        static std::string myWhatThis() {return "aht";}

        static bool comply
        (const StructureEnv_New * cm, const Implements_Var& iv,
        const vType* self
        , std::string * whyNot,const std::string& masterObjective)
        {
            return true;
        }

        static  Implements_Identifier* nextKey
        (const StructureEnv_New * cm, const Implements_Var& iv,
        const vType* self
        , std::string * whyNot,const std::string& masterObjective
        ,Implements_Identifier* source)
        {
          source->setName(self->getKeyType(cm)->getName());
          return source;
        }

        static  Implements_Data_Type_New<ABC_Data_New*>* nextElement
        (const StructureEnv_New * cm, const Implements_Var& iv,
        const vType* self
        , std::string * whyNot,const std::string& masterObjective
        ,Implements_Data_Type_New<ABC_Data_New*>* source)
        {
          source->setDataType(self->getElementType(cm)->getDataType());
          return source;
        }



        static Implements_Data_Type_New<myC>*
        varType(const Implements_Var var)
        {
          std::string varType;
          if (var.data!=nullptr)
            varType=var.data->myType();

          return new Implements_Data_Type_New<Implements_Var>(
                Identifier::types::idVarGiven::varType(var.id)
                ,Data::types::data::varType(varType)
                ,&comply,&nextElement,&nextKey);
        }

        static Implements_Data_Type_New<myC>*
        varType(const Implements_Var var,
                Implements_Data_Type_New<myC>* source)
        {
          source->setVariable(var);
          return source;
        }


      };




    };
  };



  namespace ComplexVar
  {
    typedef StructureEnv_New* myC;

    class types
    {
    public:
      template <class T>
      static  Implements_Data_Type_New<myC>* getVarType(
          std::vector<std::pair<Implements_Var,bool>> fields)

      {
        Implements_Var firstVar;
        if (fields.size()>0)
          firstVar=fields[0].first;

        return new Implements_Data_Type_New<StructureEnv_New*>
            (fields,
             Variable::types::varGiven::varType(firstVar)
             ,&T::comply,
             &T::hasMandatory,
             &T::hasAll,
             &T::nextElement);
      };


      struct ClassDescript
      {

        static std::string myId(const std::string& id){return "_CV"+id;}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(const std::string& id){return "fields map of "+id;}
        static std::string myWhatThis();



        static bool comply (const StructureEnv_New* cm,const StructureEnv_New* val,
                            const Implements_Data_Type_New<myC>* self
                            , std::string* error,const std::string& obj)
        {
          return hasMandatory(cm,val,self,error,obj);
        }

        static bool hasAll (const StructureEnv_New* cm,const StructureEnv_New* val,
                            const Implements_Data_Type_New<myC>* self
                            , std::string* error,const std::string& obj)
        {
          auto& fields=self->fields_;

          for (std::size_t i=0; i<fields.size(); ++i)
            {
              const Implements_Var& v=fields[i].first;
              if (!val->hasNameofType(v.id,v.data->myType(),error,obj,false))
                return false;
            }
          return true;

        }

        static bool hasMandatory (const StructureEnv_New* cm,const StructureEnv_New* val,
                                  const Implements_Data_Type_New<myC>* self
                                  , std::string* error,const std::string& obj)
        {
          auto& fields=self->fields_;

          for (std::size_t i=0; i<fields.size(); ++i)
            {
              const Implements_Var& v=fields[i].first;
              if (!val->hasNameofType(v.id,v.data->myType(),error,obj,false))
                return !fields[i].second;
            }
          return true;

        }

        static Implements_Data_Type_New<Implements_Var>*
        nextElement
        (const StructureEnv_New* cm
         ,const StructureEnv_New* val,
         std::size_t iField, const Implements_Data_Type_New<myC>*  self
         , std::string * whyNot, const std::string& masterObjective,
         Implements_Data_Type_New<Implements_Var>* source)
        {
          auto& fields=self->fields_;
          if (iField<fields.size())
            {
              const Implements_Var& v=fields[iField].first;
              if (source!=nullptr)
                {
                  source->setVariable(v);
                  return source;
                }
              else
                return Variable::types::varGiven::varType(v);
            }
          else
            {
              *whyNot=masterObjective+": iField="+std::to_string(iField)
                  +" bigger than fields size()="
                  +std::to_string(fields.size());
              return nullptr;
            }
        }


        static  Implements_Data_Type_New<myC>* varType(
            std::vector<std::pair<Implements_Var,bool>> fields)
        {
          return getVarType<ClassDescript>(fields);

        }


      };


    };
  };


  namespace _private {



    template<typename T>
    class Implements_Data_Type_class:public ABC_Type_of_Value
    {
    public:
      using typePredicate= bool(*)
      (const StructureEnv_New*
      ,const T&
      ,const Implements_Data_Type_New<T>*
      , std::string*
      ,const std::string& );



      virtual bool isDataInDomain
      (const StructureEnv_New* cm
       ,const ABC_Data_New* v
       , std::string *whyNot
       , const std::string& masterObjective)const override
      {
        const std::string objective=masterObjective+": "+this->id()+ "do not has it in domain";
        auto x=dynamicCast<const Implements_Value_New<T>* >(v,whyNot,objective);
        if (x==nullptr)
          {
            return false;
          }
        else
          return isValueInDomain(cm,x->getValue(),whyNot,objective);
      }

      virtual bool isValueInDomain(const StructureEnv_New* cm,const T& v
                                   , std::string *whyNot, const std::string& masterObjective)const
      {

        if (comply_==nullptr)
          return true;
        else
          return  (*comply_) (cm,v,this,whyNot,masterObjective);
      }



      bool includesThisType(
          const StructureEnv_New *cm, const std::string &childType
          , std::string *whyNot, const std::string &masterObjective) const
      {
        std::string id=cm->dataToId(this,whyNot,masterObjective);
        if (id==childType) return true;
        else
          {
            const Implements_Data_Type_New<T>*
                ctype=cm->idToTyped<T>(childType,whyNot,masterObjective);
            if (ctype==nullptr)
              {
                *whyNot=masterObjective+": "+childType+"is not a"+ id;
                return false;
              }
            else return empty();

          }
      }



      virtual bool putData(const StructureEnv_New* cm
                           ,const ABC_Data_New* v
                           ,ABC_Output* ostream
                           ,std::string* error,
                           const std::string& masterObjective)const override
      {
        auto data=dynamic_cast<const Implements_Value_New<T>* >(v);
        if (data==nullptr)
          {
            *error=masterObjective+ ": "+data->myType()+" is not a "+myType();
            return false;
          }
        else return putValue(cm,data->getValue(),ostream,error,masterObjective);
      }

      virtual bool getData(const StructureEnv_New* cm
                           ,ABC_Data_New*& v
                           , ABC_Input* istream
                           ,std::string* error
                           , const std::string& masterObjective)const override
      {
        T data;
        if (!getValue(cm,data,istream,error,masterObjective))
          return false;
        else
          {
            std::string id=cm->dataToId(v,error,masterObjective);
            if (id.empty()) return false;
            else{
                v= new Implements_Value_New<T>(id,data);
                return true;
              }
          }
      }




      virtual bool putValue(const StructureEnv_New* cm
                            ,const T& c
                            ,ABC_Output* ostream
                            ,std::string* whyNot
                            , const std::string& masterObjective)const
      {
        StructureEnv_New* m
            =getComplexMap(cm,c,whyNot,masterObjective);
        if (m==nullptr)
          return false;
        else
          return CVtype_->putValue
              (cm,m,ostream,whyNot,masterObjective);
      }

      virtual bool getValue(const StructureEnv_New* cm
                            ,T& v
                            , ABC_Input* istream
                            ,std::string* whyNot
                            , std::string& MasterObjective )const
      {
        StructureEnv_New* m;
        if (!CVtype_->getValue(cm,m,istream,whyNot,MasterObjective))
          return false;
        else
          {
            auto x=getClass(cm,m,whyNot,MasterObjective);
            if (!isValueInDomain(cm,x,whyNot,MasterObjective))
              return false;
            else
              {
                v=std::move(x);
                return true;
              }
          }
      }



      virtual buildByToken<StructureEnv_New*>* getBuildByToken(const StructureEnv_New* cm)const
      {
        return new buildByToken<StructureEnv_New*>(cm,CVtype_);
      }


      virtual ~Implements_Data_Type_class(){}

      virtual bool empty()const
      {
        return comply_==nullptr&& CVtype_==nullptr;
      }

      virtual void reset()
      {
        comply_=nullptr;
        CVtype_=nullptr;

      }


      virtual std::string myType()const
      {
        return Cls<T>::name();
      }


      virtual bool isOfThisType(const StructureEnv_New* cm,
                                const std::string& generalType,
                                std::string* whyNot
                                ,const std::string &masterObjective)const
      {
        if (myType()==generalType)
          return true;
        else
          {
            auto gTp
                =cm->idToTyped<T>(generalType,whyNot,masterObjective);
            std::string id=cm->dataToId(this,whyNot,masterObjective);
            if ((id.empty())||(gTp==nullptr))
              return false;
            else
              return gTp->includesThisType(cm,id,whyNot,masterObjective);
          }

      }

      Implements_Data_Type_class(
          const std::vector<std::pair<Implements_Var,bool>> fields
          ,typePredicate complyPred
          ):
        comply_(complyPred)
      ,CVtype_(nullptr)
      {
        CVtype_=ComplexVar::types::ClassDescript::varType(fields);
      }


    public:
      virtual Implements_Value_New<T>* getClassRep(
          const StructureEnv_New* cm,
          const StructureEnv_New* m
          , std::string *whyNot,
          const std::string& masterObjective) const override
      {
        std::string id=cm->dataToId(this, whyNot,masterObjective);

        T o=getClass(cm,m,whyNot,masterObjective);
        if (o!=nullptr)
          return Implements_Value_New<T*>
              (id,o);
        else
          return nullptr;

      }

      virtual T getClass(const StructureEnv_New* cm
                         ,const StructureEnv_New*  m
                         ,std::string *WhyNot,const std::string& masterObjective)=0;

      virtual StructureEnv_New* getComplexMap(
          const StructureEnv_New* cm,
          const T& v,std::string *WhyNot,const std::string & masterObjective)=0;


      // ABC_Typed_Value interface
    public:
      virtual StructureEnv_New* getComplexVarRep(
          const StructureEnv_New* cm,
          const ABC_Data_New *var
          , std::string *whyNot
          , const std::string& masterObjective) const override
      {
        auto v=dynamic_cast<Implements_Value_New<T>*>(var);

        T d=v->getValue();

        return getComplexMap(cm,d,whyNot,masterObjective);
      }


    protected:
      typePredicate comply_;
      const Implements_Data_Type_New<StructureEnv_New*>* CVtype_;
    };



    template<typename T>
    class Implements_Data_Type_class<T*>:public ABC_Type_of_Value
    {
    public:
      using typePredicate= bool(*)
      (const StructureEnv_New*
      ,const T*
      ,const Implements_Data_Type_New<T*>*
      , std::string*
      ,const std::string& );



      virtual bool isDataInDomain
      (const StructureEnv_New* cm
       ,const ABC_Data_New* v
       , std::string *whyNot
       , const std::string& masterObjective)const override
      {
        const std::string objective=masterObjective+": do not has it in domain";
        auto x=dynamic_cast<const Implements_Value_New<T*>* >(v);
        if (x==nullptr)
          {
            return false;
          }
        else
          return isValueInDomain(cm,x->getValue(),whyNot,objective);
      }

      virtual bool isValueInDomain(const StructureEnv_New* cm,const T* v
                                   , std::string *whyNot, const std::string& masterObjective)const=0;






      bool includesThisType(const StructureEnv_New *cm, const std::string &childType
                            , std::string *whyNot, const std::string &masterObjective) const
      {
        std::string id=cm->dataToId(this,whyNot,masterObjective);
        if (id==childType) return true;
        else
          {
            const Implements_Data_Type_New<T*>*
                ctype=cm->idToTyped<T*>(childType,whyNot,masterObjective);
            if (ctype==nullptr)
              {
                *whyNot=masterObjective+": "+childType+"is not a"+ id;
                return false;
              }
            else return empty();


          }
      }



      virtual bool putData(const StructureEnv_New* cm
                           ,const ABC_Data_New* v
                           ,ABC_Output* ostream
                           ,std::string* error,
                           const std::string& masterObjective)const override
      {
        auto data=dynamic_cast<const Implements_Value_New<T*>* >(v);
        if (data==nullptr)
          {
            *error=masterObjective+ ": "+data->myType()+" is not a "+Cls<T*>::name();
            return false;
          }
        else return putValue(cm,data->getValue(),ostream,error,masterObjective);
      }

      virtual bool getData(const StructureEnv_New* cm
                           ,ABC_Data_New*& v
                           , ABC_Input* istream
                           ,std::string* error
                           , const std::string& masterObjective)const override
      {
        T* data;
        if (!getValue(cm,data,istream,error,masterObjective))
          return false;
        else
          {
            std::string id=cm->dataToId(v,error,masterObjective);
            if (id.empty()) return false;
            else
              {
                v= new Implements_Value_New<T*>(id,data);
                return true;
              }
          }
      }




      virtual bool putValue(const StructureEnv_New* cm
                            ,const T* c
                            ,ABC_Output* ostream
                            ,std::string* whyNot
                            , const std::string& masterObjective)const
      {
        StructureEnv_New* m
            =getComplexMap(cm,c,whyNot,masterObjective);
        if (m==nullptr)
          return false;
        else
          return CVtype_->putValue
              (cm,m,ostream,whyNot,masterObjective);
      }

      virtual bool getValue(const StructureEnv_New* cm
                            ,T*& v
                            , ABC_Input* istream
                            ,std::string* whyNot
                            ,const std::string& MasterObjective )const
      {
        StructureEnv_New* m;
        if (!CVtype_->getValue(cm,m,istream,whyNot,MasterObjective))
          return false;
        else
          {
            auto x=getClass(cm,m,whyNot,MasterObjective);
            if (!isValueInDomain(cm,x,whyNot,MasterObjective))
              return false;
            else
              {
                v=std::move(x);
                return true;
              }
          }
      }



      virtual buildByToken<StructureEnv_New*>* getBuildByToken(const StructureEnv_New* cm)const
      {
        return new buildByToken<StructureEnv_New*>(cm,CVtype_);
      }


      virtual ~Implements_Data_Type_class(){}


      Implements_Data_Type_class(
          const std::vector<std::pair<Implements_Var,bool>> fields
          ,typePredicate complyPred=nullptr
          ):
        comply_(complyPred)
      ,CVtype_(nullptr)
      {
        CVtype_=ComplexVar::types::ClassDescript::varType(fields);
      }

      virtual bool empty()const
      {
        return comply_==nullptr&& CVtype_==nullptr;
      }

      virtual void reset()
      {
        comply_=nullptr;
        CVtype_=nullptr;

      }


      virtual std::string myType()const
      {
        return Cls<T*>::name();
      }


      virtual bool isOfThisType(const StructureEnv_New* cm,
                                const std::string& generalType,
                                std::string* whyNot
                                ,const std::string &masterObjective)const
      {
        if (myType()==generalType)
          return true;
        else
          {
            auto gTp
                =cm->idToTyped<T*>(generalType,whyNot,masterObjective);
            std::string id=cm->dataToId(this,whyNot,masterObjective);
            if ((id.empty())||(gTp==nullptr))
              return false;
            else
              return gTp->includesThisType(cm,id,whyNot,masterObjective);
          }

      }



    public:
      virtual Implements_Value_New<T*>* getClassRep(
          const StructureEnv_New* cm,
          const StructureEnv_New* m
          , std::string *whyNot,
          const std::string& masterObjective) const override
      {
        std::string id=cm->dataToId(this, whyNot,masterObjective);

        T* o=getClass(cm,m,whyNot,masterObjective);
        if (o!=nullptr)
          return new Implements_Value_New<T*>
              (id,o);
        else
          return nullptr;

      }

      virtual T* getClass(const StructureEnv_New* cm
                          ,const StructureEnv_New*  m
                          ,std::string *WhyNot,const std::string& masterObjective)const =0;

      virtual StructureEnv_New* getComplexMap(
          const StructureEnv_New* cm,
          const T* v,std::string *WhyNot,const std::string & masterObjective)const =0;


      // ABC_Typed_Value interface
    public:
      virtual StructureEnv_New* getComplexVarRep(
          const StructureEnv_New* cm,
          const ABC_Data_New *var
          , std::string *whyNot
          , const std::string& masterObjective) const override
      {
        auto v=dynamic_cast<const Implements_Value_New<T*>*>(var);

        const T* d=v->getValue();

        return getComplexMap(cm,d,whyNot,masterObjective);
      }


    protected:
      typePredicate comply_;
      const Implements_Data_Type_New<StructureEnv_New*>* CVtype_;
    };



  }


  template<typename T>
  class Implements_Parameters_Type_New:public ABC_Type_of_Value
  {
  public:

    using typePredicate= bool(*)(const StructureEnv_New*,const T*,const Implements_Parameters_Type_New<T>*, std::string*);


    using plainPredicate
    = bool(*)(const StructureEnv_New*,const Implements_Parameters_Type_New<T>*, std::string*);

    using getEmptyMap=StructureEnv_New* (*)(const Implements_Parameters_Type_New<T>*, std::string*);

    using getMap=StructureEnv_New* (*)(const T*, const Implements_Parameters_Type_New<T>*, std::string*);

    using getObject= T* (*)(const StructureEnv_New*,const _private::Implements_Data_Type_class<T>*,std::string*);


    static std::string ClassName()
    {
      return "Implements_Class_Type_New_of"+Cls<T*>::name();
    }



    virtual bool put(const StructureEnv_New* cm,const T* v,ABC_Output* ostream,std::string* error)const
    {

      ostream->put(v);
      return true;
    }

    virtual bool get(const StructureEnv_New* cm,T*& v, ABC_Input* istream,std::string* whyNot )const
    {

      if (!istream->get(v,whyNot))
        return false;
      else
        return isValueInDomain(*v,whyNot);
    }



    virtual buildByToken<T*>* getBuildByToken(const StructureEnv_New* cm)const
    {
      return new buildByToken<T*>(cm,this->id());
    }


    virtual ~Implements_Parameters_Type_New(){}


    Implements_Parameters_Type_New(typePredicate complyPred
                                   ,plainPredicate mapComply
                                   ,getEmptyMap eMap
                                   ,getMap map
                                   ,getObject obj):
      comply_(complyPred)
    ,mapComply_(mapComply)
    ,toEMap_(eMap)
    ,toMap_(map)
    ,toObj_(obj)
    {}




  protected:
    typePredicate comply_;
    plainPredicate mapComply_;
    getEmptyMap toEMap_;
    getObject toObj_;
    getMap toMap_;
    // ABC_Type_of_Value interface
  public:


    // ABC_Type_of_Value interface
  public:
    virtual Implements_Value_New<T*>* getClassRep(const StructureEnv_New *cm, std::string *whyNot, const std::string& masterObjective) const override
    {
      std::string id=cm->dataToId(this, whyNot,masterObjective);

      auto o=(*toObj_)(cm,this,whyNot);
      if (o!=nullptr)
        return Implements_Value_New<T*>
            (id,o);
      else
        return nullptr;

    }


    // ABC_Typed_Value interface
  public:
    virtual StructureEnv_New *getComplexVarTyeped_Rep(const Implements_Value_New<T*> *var, std::string *whyNot) const override
    {

    }
  };

  class Markov_CommandManagerVar;



  class Implements_Command_Arguments: public StructureEnv_New
  {
  public:

    virtual ~Implements_Command_Arguments(){}

    Implements_Command_Arguments(const StructureEnv_New* parent,
                                 const std::string& var
                                 ):
      StructureEnv_New(parent,var){}

  };



  class Implements_Command_Type_New:
      public _private::Implements_Data_Type_New_StructureEnv
  {
  public:


    using runCommand
    = bool  (*)
    (Markov_CommandManagerVar* cm
    , const StructureEnv_New* arguments
    ,const Implements_Command_Type_New* self
    ,std::string* WhyFail, const std::string& masterObjective);





    virtual ~Implements_Command_Type_New(){}


    Implements_Command_Type_New
    (std::vector<std::pair<Implements_Var,bool>> argList
     ,runCommand run_,
     const Implements_Data_Type_New<Implements_Var>* elemeType,
     typePredicate comply,
     typePredicate hasMandatory,
     typePredicate hasAll,
     elementType elem):
      _private::Implements_Data_Type_New_StructureEnv
      (argList,elemeType,comply,hasMandatory,hasAll,elem)
    ,run_(run_)
    {
    }





  public:




    virtual bool run(Markov_CommandManagerVar* cm,
                     const StructureEnv_New* m,
                     std::string *WhyNot, const std::string& masterObjective)const
    {
      return (*run_)(cm,m,this,WhyNot,masterObjective);
    }



    // ABC_Type_of_Value interface
  public:
    virtual build_Command_Input *getBuildByToken(const StructureEnv_New *cm) const override
    {
      return new build_Command_Input(cm,this);

    }


  protected:

    runCommand run_;



  };


  ///--------------------------------------------------------------------
  ///-------------------------------------------------------------------
  ///

  /// Template implementations
  ///
  ///












  namespace _private {





    template<typename T>
    bool Implements_Base_Type_New<T>::includesThisType(const StructureEnv_New *cm, const std::string &childType, std::string *whyNot, const std::string &masterObjective) const
    { std::string id=cm->dataToId(this,whyNot,masterObjective);
      if (childType==id)
        return true;
      else
        {
          auto ctype=cm->idToTyped<T>(childType,whyNot,masterObjective);
          if (ctype==nullptr)
            return false;
          else if ((ctype->myType()==id)||(empty()))
            {
              return true;
            }
          else
            return false;
        }
    }

    template<typename T>
    bool Implements_Base_Type_New<T*>::includesThisType(const StructureEnv_New *cm, const std::string &childType, std::string *whyNot, const std::string &masterObjective) const

    { std::string id=cm->dataToId(this,whyNot,masterObjective);
      if (childType==id)
        return true;
      else
        {
          auto ctype=cm->idToTyped<T*>(childType,whyNot,masterObjective);
          if (ctype==nullptr)
            return false;
          else if ((ctype->myType()==id)||(empty()))
            {
              return true;
            }
          else
            return false;
        }
    }


  };



}

//#include "Markov_IO/buildByToken.h"




#endif // IMPLEMENTS_COMPLEXVAR_NEW_H
