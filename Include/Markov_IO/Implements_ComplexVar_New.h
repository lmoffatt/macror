#ifndef IMPLEMENTS_COMPLEXVAR_NEW_H
#define IMPLEMENTS_COMPLEXVAR_NEW_H



#include "Markov_IO/Var.h"
#include "Markov_IO/buildByToken.h"

//#include "Markov_IO/Closure.h"
#include "Markov_LA/matrixSum.h"
#include "Markov_IO/StructureEnv.h"

//#include "Markov_IO/Implements_function.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <tuple>
#include <type_traits>



namespace Markov_IO_New {







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
      insert(alt,id,v->myTypeId());
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

  class ABC_Type_of_Value //: public ABC_Data_New
  {
  public:
    typedef ABC_BuildByToken myBuild;
    virtual bool empty()const =0;

    virtual void reset()=0;

    virtual ABC_Type_of_Value* clone()const=0;
    virtual ABC_Type_of_Value* create()const=0;



    virtual ABC_Type_of_Value const* myType()const=0;

    virtual std::string myTypeId()const=0;

    virtual bool isOfThisType(const StructureEnv_New* cm,
                              const std::string& generalType,
                              std::string* whyNot=nullptr
                              ,const std::string &masterObjective="")const=0;

    virtual bool includesThisType(const StructureEnv_New* cm
                                  ,const std::string& childType
                                  ,std::string *whyNot=nullptr
                                  , const std::string &masterObjective="")const=0;



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


    virtual StructureEnv_New* getComplexVarRep(
        const StructureEnv_New* cm,
        const ABC_Data_New* var
        ,std::string* whyNot
        ,const std::string& masterObjective)const=0;

    virtual ABC_Data_New* getClassRep(const StructureEnv_New* cm,
                                      const StructureEnv_New* cvar,
                                      std::string* whyNot,
                                      const std::string& masterObjective)const
    {
      return nullptr;
    }



    virtual StructureEnv_New* getEnv(){return env_;}
    virtual const StructureEnv_New* getEnv()const {return env_;}


    virtual std::string typeId()const =0;

    virtual const Implements_Identifier* getVarIdType(const StructureEnv_New* cm)const=0;
    virtual const Implements_Identifier* getTypeIdType(const StructureEnv_New* cm)const=0;



  private:
    StructureEnv_New* env_;

  };






  template <class myType_of_Value>
  class Type_Union : public myType_of_Value
  {
  public:

    virtual bool empty()const{return s_.empty();}

    virtual void reset(){s_.clear();}

    virtual Type_Union* clone()const{return new Type_Union(*this);}
    virtual Type_Union* create()const {return new Type_Union();}


    virtual myType_of_Value const* myType()const{return nullptr;}

    virtual std::string myTypeId()const
    {
      std::set<std::string> s;
      for (auto e:s_)
        s.insert(e->myTypeId());
      std::string out;
      for (auto e:s)
        out+=e+"_";
      return out;
    }

    virtual bool isOfThisType(const StructureEnv_New* cm,
                              const std::string& generalType,
                              std::string* whyNot
                              ,const std::string &masterObjective)const
    {
      for (const myType_of_Value* e:s_)
        {
          if (!e->isOfThisType(cm,generalType,whyNot,masterObjective))
            return false;
        }
       return true;
    }




    Type_Union(){}
    Type_Union(const Type_Union&)=default;
    Type_Union(Type_Union&&)=default;
    Type_Union& operator=(const Type_Union&)=default;
    Type_Union& operator=(Type_Union&&)=default;


    Type_Union(std::vector<const myType_of_Value*> v):s_(v){}
    virtual ~Type_Union(){}
    virtual bool putData(const StructureEnv_New* cm
                         ,const ABC_Data_New* v
                         ,ABC_Output* ostream
                         ,std::string* error,
                         const std::string& masterObjective)const
    {
      if (isDataInDomain(cm,v,error,masterObjective))
       return v->myType()->putData(cm,v,ostream,error,masterObjective);
      else return false;
    }

    virtual bool getData(const StructureEnv_New* cm
                         ,ABC_Data_New*& v
                         , ABC_Input* istream
                         ,std::string* error
                         , const std::string& masterObjective)const
    {
      for (const myType_of_Value* t:s_)
        {
          if (t->getData(cm,v,istream,error,masterObjective))
            return true;
        }
      return false;
    }

    typedef  BuildByToken_Union<myType_of_Value> myBuild;

    virtual myBuild* getBuildByToken(
        const StructureEnv_New* cm)const
    {
      return new myBuild(cm,this);
    }


    virtual bool isDataInDomain(const StructureEnv_New* cm
                                ,const ABC_Data_New* v
                                , std::string *whyNot
                                , const std::string& masterObjective)const
    {
      for (const myType_of_Value* t:s_)
        {
          if (t->isDataInDomain(cm,v,whyNot,masterObjective))
            return true;
        }
      return false;

    }

    virtual bool includesThisType(const StructureEnv_New* cm
                                  ,const std::string& childType
                                  ,std::string *whyNot=nullptr
                                  , const std::string &masterObjective="")const
    {
      for (const myType_of_Value* t:s_)
        {
          if (t->includesThisType(cm,childType,whyNot,masterObjective))
            return true;
        }
      return false;

    }

    virtual StructureEnv_New* getComplexVarRep(
        const StructureEnv_New* cm,
        const ABC_Data_New* var
        ,std::string* whyNot
        ,const std::string& masterObjective)const
    {
      return nullptr;
    }




    virtual std::string typeId()const
    {
      std::string out;
      for (const myType_of_Value* t:s_)
        {
          out+=t->typeId()+"_";
        }

    }

    virtual const Implements_Identifier* getVarIdType(const StructureEnv_New* cm)const {return nullptr;}
    virtual const Implements_Identifier* getTypeIdType(const StructureEnv_New* cm)const {return nullptr;}

   const std::vector<const myType_of_Value*>&
     getAllTypes()const
   {
     return s_;
   }

   void push_Type(const myType_of_Value* t)
   {
     if (names_.find(t->typeId())==names_.end())
       {
       s_.push_back(t);
       names_.insert(t->typeId());
       }
   }

  private:
    std::set<std::string> names_;
    std::vector<const myType_of_Value*> s_;
  };




  template <typename myType_of_Value>
  inline std::vector<typename myType_of_Value::myBuild*>
  getBuildByTokenVector(const StructureEnv_New* cm,const Type_Union<myType_of_Value>* t)
  {
      std::vector<typename myType_of_Value::myBuild*> out(t->getAllTypes().size());
     for (std::size_t i=0; i<t->getAllTypes().size(); ++i)
       out[i]=t->getAllTypes()[i]->getBuildByToken(cm);
     return out;
  }




  namespace Real
  {
    struct types;
  }


  namespace _private {


    template<typename T>
    class Implements_Base_Type_New:public ABC_Type_of_Value
    {
    public:






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



      virtual bool isValueInDomain(const StructureEnv_New* cm
                                   ,const T &val
                                   , std::string *whyNot
                                   ,const std::string& masterObjective ) const=0;






      virtual ~Implements_Base_Type_New(){}

      virtual bool putData(const StructureEnv_New* cm
                           ,const ABC_Data_New* v
                           ,ABC_Output* ostream
                           ,std::string* error,
                           const std::string& masterObjective)const override
      {
        auto data=dynamic_cast<const Implements_Value_New<T>* >(v);
        if (data==nullptr)
          {
            *error=masterObjective+ ": "+data->myTypeId()+" is not a "+this->myTypeId();
            return false;
          }
        else return putValue(cm,data->getValue(),ostream,error,masterObjective);
      }


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


      virtual bool isOfThisType
      (const StructureEnv_New *cm
       , const std::__cxx11::string &generalType
       , std::__cxx11::string *whyNot
       , const std::__cxx11::string &masterObjective) const override
      {

        if ((generalType.empty()||myTypeId()==generalType))
          return true;
        else
          {
            auto gTp
                =cm->idToTyped<T>(generalType,whyNot,masterObjective);
            std::string id=typeId();
            if ((id.empty())||(gTp==nullptr))
              return false;
            else
              return gTp->includesThisType(cm,id,whyNot,masterObjective);
          }

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
        if ((generalType.empty()||myTypeId()==generalType))
          return true;
        else
          {
            auto gTp
                =cm->idToTyped<T*>(generalType,whyNot,masterObjective);
            std::string id=typeId();
            if ((id.empty())||(gTp==nullptr))
              return false;
            else
              return gTp->includesThisType(cm,id,whyNot,masterObjective);
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
            *error=masterObjective+ ": "+data->myTypeId()+" is not a "+myTypeId();
            return false;
          }
        else return putValue(cm,data->getValue(),ostream,error,masterObjective);
      }


      virtual bool putValue(const StructureEnv_New* cm
                            ,const T* v
                            ,ABC_Output* ostream
                            ,std::string* error=nullptr,
                            const std::string& masterObjective="")const=0;

      virtual bool getValue(const StructureEnv_New* cm
                            ,T*& v
                            , ABC_Input* istream
                            ,std::string* error=nullptr
          , const std::string& masterObjective="")const =0;



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
      typedef Implements_Data_Type_New_string selfType;
      typedef std::string myC;
      static std::string myId() {return Cls<myC>::name();}
      static selfType* varType(const StructureEnv_New* )
      {return new selfType{myId(),nullptr};}
      static std::string myTip(){return "a regular string of characters";}
      static std::string myWhatThis(){return "";}
      typedef mp_list<> dependsOn;
      typedef mp_list<> fieldList;


      using typePredicate= bool(*) (const StructureEnv_New* cm,const std::string& val,
      const Implements_Data_Type_New_string* self, std::string* error,const std::string& obj);


      using getSet=std::set<std::string>(*)(const StructureEnv_New*,
      const Implements_Data_Type_New_string*);

      typedef buildByToken<myC> myBuild;

      virtual buildByToken<std::string>* getBuildByToken(
          const StructureEnv_New* cm)const override;


      virtual std::set<std::string> alternativeNext(const StructureEnv_New* cm)const
      {
        return (*alternativeNext_)(cm,this);
      }

      virtual ~Implements_Data_Type_New_string(){}

      virtual bool putValue(const StructureEnv_New* cm,
                            const std::string& v,ABC_Output* ostream
                            ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")const override
      {

        if ((whyNot==nullptr)||(isValueInDomain(cm,v,whyNot,masterObjective)))
          {
            ostream->put(v);
            return true;
          }
        else return false;
      }


      virtual bool getData(const StructureEnv_New* cm
                           ,ABC_Data_New*& v
                           , ABC_Input* istream
                           ,std::string* error
                           , const std::string& masterObjective)const override
      {
        myC data;
        if (!getValue(cm,data,istream,error,masterObjective))
          return false;
        else
          {
            v= new Implements_Value_New<myC>(this,data);
            return true;
          }
      }




      virtual bool getValue(const StructureEnv_New* cm
                            ,std::string& v, ABC_Input* istream,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")const override
      {

        if (!istream->get(v,whyNot,masterObjective))
          return false;
        else return (whyNot==nullptr)||isValueInDomain(cm,v,whyNot,masterObjective);
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


      Implements_Data_Type_New_string(const std::string id,
                                      selfType const* typeType,
                                      typePredicate complyPred=nullptr
          ,getSet alterNext=nullptr):
        id_(id),
        typeType_(typeType),
        comply_(complyPred),
        alternativeNext_(alterNext)

      {}
      Implements_Data_Type_New_string(const Implements_Data_Type_New_string& other)=default;

      Implements_Data_Type_New_string( Implements_Data_Type_New_string&& other)=default;

      Implements_Data_Type_New_string& operator=(const Implements_Data_Type_New_string& other)=default;
      Implements_Data_Type_New_string& operator=(Implements_Data_Type_New_string&& other)=default;


      Implements_Data_Type_New_string():Implements_Data_Type_New_string(Cls<myC>::name(),nullptr){}

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
      {return new Implements_Data_Type_New_string(Cls<myC>::name(),nullptr);}

      virtual selfType const* myType()const override
      {
        return typeType_;
      }

      std::string myTypeId()const override  {
        if (myType()==nullptr)
          return Cls<myC>::name();
        else
          return myType()->typeId();
      }

      std::string typeId()const override
      {
        return id_;
      }

      virtual const Implements_Identifier* getVarIdType(const StructureEnv_New* cm)const override
      {
        return nullptr;
      }
      virtual const Implements_Identifier* getTypeIdType(const StructureEnv_New* cm)const override
      {
        return nullptr;
      }





    protected:
      std::string id_;
      selfType const * typeType_;
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
    void push_Types(StructureEnv_New *cm);


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

    virtual Implements_Data_Type_New<std::string> const * myType()const override {return typeType_;}

    std::string typeId()const override {return typeId_;}

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

    Implements_Identifier():Implements_Identifier("empty",nullptr,"",false,false,false,false,false,false){}

  private:
    static std::string toId
    (const std::string& name,
     bool isFixed,bool isVar, bool isType,
     bool isCommand,bool isNew, bool isUsed, bool isFunction=false);

    Implements_Identifier
    (const std::string& nameId,
     Implements_Data_Type_New<myC>* const typeType
     ,const std::string& name,
     bool isFixed,bool isVar, bool isType,
     bool isCommand,bool isNew, bool isUsed, bool isFunction=false):
      Implements_Data_Type_New_string
      (nameId,typeType),
      typeId_(nameId),typeType_(typeType),
      name_(name),isFixed_(isFixed)
    , isVar_(isVar), isType_(isType),isCommand_(isCommand)
    ,isNew_(isNew),isUsed_(isUsed),isFunction_(isFunction)
    {}
    std::string typeId_;
    Implements_Data_Type_New<myC> const *typeType_;
    std::string name_;
    bool isFixed_;
    bool isVar_;
    bool isType_;
    bool isCommand_;
    bool isField_;
    bool isNew_;
    bool isUsed_;
    bool isFunction_;

  };


  class Identifier_Union;

  std::vector<buildByToken<std::string>*>
  getBuildByTokenVector(const StructureEnv_New* cm,const Identifier_Union* t);


  class Identifier_Union: public Implements_Identifier

  {
  public:

    static std::string ClassName(){return "Identifier_Union";}

    virtual Identifier_Union const * myType()const override {return nullptr;}

    std::string typeId()const override
    {
      std::string out;
      for (const Implements_Identifier* e:v_)
        {
          out+=e->typeId()+"_";
        }
      return out;


    }

    virtual std::set<std::string> alternativeNext(const StructureEnv_New* cm)const override
    {
      std::set<std::string> out;
      for (const Implements_Identifier* e:v_)
        {
          out+=e->alternativeNext(cm);
        }
      return out;

    }

    virtual bool isValueInDomain(const StructureEnv_New* cm,const std::string &idCandidate, std::string *whyNot,const std::string& objective ) const override
    {
      for (const Implements_Identifier* e:v_)
        {
          if (e->isValueInDomain(cm,idCandidate,whyNot,objective))
            return true;
        }
      return false;
    }

    std::string getName()const {
      std::string out;
      for (const Implements_Identifier* e:v_)
        {
          out+=e->getName()+"_";
        }
      return out;

    }

    void setName(const std::string& name)
    {

    }


    Identifier_Union* clone()const override
    {
      return new Identifier_Union(*this);
    }

    Identifier_Union* create()const override
    {
      return new Identifier_Union();
    }

    Identifier_Union(){}






    virtual BuildByTokenString_Union* getBuildByToken(
        const StructureEnv_New* cm)const override
    {
       return new BuildByTokenString_Union(cm,this);
    }



    virtual ~Identifier_Union (){}

    virtual bool putValue(const StructureEnv_New* cm,
                          const std::string& v
                          ,ABC_Output* ostream
                          ,std::string* whyNot=nullptr
        ,const std::string& masterObjective="")const override
    {

      if ((whyNot==nullptr)||(isValueInDomain(cm,v,whyNot,masterObjective)))
        {
          ostream->put(v);
          return true;
        }
      else return false;
    }


    virtual bool getData(const StructureEnv_New* cm
                         ,ABC_Data_New*& v
                         , ABC_Input* istream
                         ,std::string* error
                         , const std::string& masterObjective)const override
    {
      for (const Implements_Identifier* t:v_)
        {
          if (t->getData(cm,v,istream,error,masterObjective))
            return true;
        }
      return false;
    }




    virtual bool getValue(const StructureEnv_New* cm
                          ,std::string& v, ABC_Input* istream,std::string* whyNot=nullptr
        ,const std::string& masterObjective="")const override
    {
      for (const Implements_Identifier* t:v_)
        {

          if (t->getValue(cm,v,istream,whyNot,masterObjective))
                 return true;

        }
      return false;

    }


    // ABC_Data_New interface
  public:
    virtual bool empty() const override
    {
      return v_.empty();
    }
    virtual void reset() override
    {
      return v_.clear();
    }



    virtual const Implements_Identifier* getVarIdType(const StructureEnv_New* cm)const override
    {
      return nullptr;
    }
    virtual const Implements_Identifier* getTypeIdType(const StructureEnv_New* cm)const override
    {
      return nullptr;
    }

    const std::vector<const Implements_Identifier*>&
    getAllTypes()const {return v_;}
    
    Identifier_Union(std::vector<const Implements_Identifier*>&& v):v_(v){}
    
    void push_Identifier(Implements_Identifier* i){v_.push_back(i);}

    Identifier_Union(const Identifier_Union&)=default;
    Identifier_Union( Identifier_Union&&)=default;
    Identifier_Union& operator=(const Identifier_Union&)=default;
    Identifier_Union& operator=( Identifier_Union&&)=default;

  protected:
   std::vector<const Implements_Identifier*> v_;
  };

  inline std::vector<buildByToken<std::string>*>
  getBuildByTokenVector(const StructureEnv_New* cm,const Identifier_Union* t)
  {
      std::vector<buildByToken<std::string>*> out(t->getAllTypes().size());
     for (std::size_t i=0; i<t->getAllTypes().size(); ++i)
       out[i]=t->getAllTypes()[i]->getBuildByToken(cm);
     return out;
  }


  namespace Identifier {

    struct types {
      template <class T>
      static Implements_Identifier* getVarType
      (const std::string& idName="")
      {
        return new Implements_Identifier
            (toId<T>(idName),nullptr,idName,T::isFixed,T::isVar
             ,T::isType,T::isCommand,T::isNew,T::isUsed, T::isFunction);
      }



      template <class T>
      static std::string toId(const std::string& idName="")
      {
        return Implements_Identifier::toId
            (idName,T::isFixed,T::isVar
             ,T::isType,T::isCommand,T::isNew,T::isUsed, T::isFunction);

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
        static constexpr bool isFunction=false;


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
        static constexpr bool isFunction=false;

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
        static constexpr bool isFunction=false;

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
        static constexpr bool isFunction=false;

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
        static constexpr bool isFunction=false;
      };




      struct idFunct{
        typedef  std::string myC;
        typedef idFunct selfType;

        static std::string myId(const std::string& funName=""){return toId<selfType>(funName);}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "a typeindentifer";}
        static std::string myWhatThis(){return "an identifier to a type";}


        static Implements_Identifier*
        varType(const std::string& funName="")
        {
          return getVarType<selfType>(funName);
        }


        static constexpr bool isFixed=false;
        constexpr static  bool isVar=false;
        constexpr static  bool isType=false;
        static constexpr bool isCommand=false;
        static constexpr bool isNew=false;
        static constexpr bool isUsed=true;
        static constexpr bool isFunction=true;
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
        static constexpr bool isFunction=false;
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



      virtual const Implements_Data_Type_New<T>* getElementDataType(const StructureEnv_New* cm)const=0;

      virtual ~Implements_Container_Type_New(){}
    };



    template<typename T, template<typename> class C>
    class Implements_Container_Type_New<T*,C> :public Implements_Base_Type_New<C<T*>>
    {
    public:




      virtual const Implements_Data_Type_New<T*>* getElementDataType(const StructureEnv_New* cm)const=0;




      virtual ~Implements_Container_Type_New(){}

    };






    template<typename T>
    using My_vec = std::vector<T>;  // to fake that vector takes only one template argument


    template<typename T>
    class Implements_Data_Type_New_vector:public Implements_Container_Type_New<T,My_vec>
    {
    public:
      typedef  Implements_Data_Type_New_vector<T> selfType;
      typedef std::vector<T> myC;
      static std::string myId() {return Cls<myC>::name();}
      static selfType* varType(const StructureEnv_New* cm)
      {return new selfType{myId(),nullptr};}
      static std::string myTip(){return "vector of "+Cls<T>::name();}
      static std::string myWhatThis(){return "";}
      typedef mp_list<Implements_Data_Type_New<T>> dependsOn;
      typedef mp_list<> fieldList;



      using typePredicate=bool(*)(const StructureEnv_New* cm,
      const std::vector<T>& val,const selfType* self,
      std::string *whyNot,const std::string& masterObjective);

      using elementTypeGetter=
      Implements_Data_Type_New<T>* (*)(const StructureEnv_New*cm
      , const std::vector<T>& val,
      typename std::vector<T>::const_iterator
      ,const selfType* self,std::string *whyNot
      ,const std::string& masterObjective
      ,Implements_Data_Type_New<T>* source);


      using getNumber= std::size_t (*)
      (const StructureEnv_New* cm
      ,const selfType* cv);


      virtual bool getData(const StructureEnv_New* cm
                           ,ABC_Data_New*& v
                           , ABC_Input* istream
                           ,std::string* error
                           , const std::string& masterObjective)const override
      {
        myC data;
        if (!getValue(cm,data,istream,error,masterObjective))
          return false;
        else
          {
            v= new Implements_Value_New<myC>(this,data);
            return true;
          }
      }




      virtual bool putValue(const StructureEnv_New* cm,const std::vector<T>& v,ABC_Output* ostream,std::string* whyNot=nullptr,const std::string& masterObjective="")const override
      {
        if ((whyNot==nullptr)||(this->isValueInDomain(cm,v,whyNot,masterObjective)))
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
                            ,std::string* whyNot=nullptr
          ,const std::string& masterObjective=nullptr)const override
      {
        char c;
        const Implements_Data_Type_New<T>* etype=this->getElementDataType(cm);
        if (etype==nullptr)
          return false;
        while (!istream->nextCharIs('\n',true)){}
        if (!istream->nextCharIs('[',c))
          {
            if (whyNot!=nullptr)
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
            if((whyNot==nullptr)|| (this->isValueInDomain(cm,v,whyNot,masterObjective)))
              return true;
            else
              return false;
          }

      }

      typedef buildByToken<myC> myBuild;


      virtual buildByToken<std::vector<T>>* getBuildByToken(
          const StructureEnv_New* cm)const
      {
        return new buildByToken<std::vector<T>>(cm,this);
      }


      virtual std::size_t getSize(const StructureEnv_New* cm)const
      {
        if (getSize_==nullptr)
          return 1;
        else
          return (*getSize_)(cm,this);
      }

      bool hasFixedSize()const {return isSizeFixed_;}

      virtual bool isValueInDomain(const StructureEnv_New* cm
                                   ,const std::vector<T> &val
                                   , std::string *whyNot
                                   ,const std::string& masterObjective ) const
      {
        return (*complyPred_)(cm,val,this,whyNot,masterObjective);
      }

      virtual const Implements_Data_Type_New<T>* getElementDataType(const StructureEnv_New* cm)const
      {
        return elementVar_;
      }


      virtual ~Implements_Data_Type_New_vector(){}

      Implements_Data_Type_New_vector(){}

      Implements_Data_Type_New_vector
      (const std::string& id, selfType const * typeType,
       const Implements_Data_Type_New<T>* elementVar=nullptr
          ,typePredicate complyPred=nullptr
          ,elementTypeGetter elemeComply=nullptr
          ,getNumber getSize=nullptr
          ,bool isSizeFixed=false)
        :typeId_(id)
        ,varIdType_(Identifier::types::idVarUsed::varType(id))
        ,typeIdType_(Identifier::types::idType::varType(id))
        ,typeType_(typeType),
          elementVar_(elementVar)
        ,complyPred_(complyPred)
        ,getElement_(elemeComply)
        ,getSize_(getSize)
        ,isSizeFixed_(isSizeFixed){}


      Implements_Data_Type_New<T>* getElementType
      (const StructureEnv_New*cm, const std::vector<T>& val
       ,typename std::vector<T>::const_iterator it,
       std::string *whyNot,const std::string& masterObjective,
       Implements_Data_Type_New<T>* source=nullptr)
      {
        if (getElement_==nullptr) return source;
        else
          return (*getElement_)(cm,val,it,this,whyNot,masterObjective,source);
      }


      virtual bool empty()const { return complyPred_==nullptr
            && getElement_==nullptr
            && getSize_==nullptr
            &&!isSizeFixed_;}

      virtual void reset() {complyPred_=nullptr; getElement_
            =nullptr; getSize_=nullptr;isSizeFixed_=false;}

      virtual selfType* clone()const { return new selfType(*this);}
      virtual selfType* create()const {return  new selfType(Cls<myC>::name(),nullptr);}







      virtual ABC_Type_of_Value const* myType()const override {return typeType_;}
      virtual Implements_Data_Type_New<myC> const * myTypeD()const {return typeType_;}

      std::string typeId()const override {return typeId_;}

      std::string myTypeId()const override  {
        if (myType()==nullptr)
          return Cls<myC>::name();
        else
          return myType()->typeId();
      }

      virtual const Implements_Identifier* getVarIdType(const StructureEnv_New* cm)const override
      {
        return varIdType_;
      }
      virtual const Implements_Identifier* getTypeIdType(const StructureEnv_New* cm)const override
      {
        return typeIdType_;
      }


    protected:
      std::string typeId_;
      const Implements_Identifier* varIdType_;
      const Implements_Identifier* typeIdType_;
      Implements_Data_Type_New<myC> const * typeType_;
      const Implements_Data_Type_New<T>* elementVar_;
      typePredicate complyPred_;
      elementTypeGetter getElement_;
      getNumber getSize_;
      bool isSizeFixed_;

      // ABC_Data_New interface
    };





    template<typename... Args>
    class Implements_Data_Type_New_tuple:public ABC_Type_of_Value
    {
    public:

      constexpr static std::size_t N=sizeof...(Args);
      typedef  Implements_Data_Type_New_tuple<Args...> selfType;
      typedef std::tuple<Args...> myC;


      typedef std::tuple<const Implements_Data_Type_New<Args>* ...> dataTypesTuple;

      static std::string myId() {return Cls<myC>::name();}
      static selfType* varType(const StructureEnv_New* cm)
      {return new selfType{};}
      static std::string myTip(){return "a regular " +Cls<myC>::name();}
      static std::string myWhatThis(){return "";}
      typedef mp_list<Implements_Data_Type_New<Args>...> dependsOn;
      typedef mp_list<> fieldList;

      using typePredicate=bool (*) (const StructureEnv_New* cm, const myC& data
      ,const selfType* self
      , std::string *whyNot, const std::string& masterObjective);




      virtual bool putData(const StructureEnv_New* cm
                           ,const ABC_Data_New* v
                           ,ABC_Output* ostream
                           ,std::string* error,
                           const std::string& masterObjective)const override
      {
        auto data=dynamic_cast<const Implements_Value_New<std::tuple<Args...>>* >(v);
        if (data==nullptr)
          {
            *error=masterObjective+ ": "+data->myTypeId()+" is not a "+myTypeId();
            return false;
          }
        else return putValue(cm,data->getValue(),ostream,error,masterObjective);
      }


      virtual bool isDataInDomain(const StructureEnv_New* cm,const ABC_Data_New* v
                                  , std::string *whyNot, const std::string& masterObjective)const override
      {
        auto x=dynamic_cast<const Implements_Value_New<std::tuple<Args...>>* >(v);
        if (x==nullptr)
          {
            if (whyNot!=nullptr)
              *whyNot=masterObjective+": is not a "+Cls<myC>::name();
            return false;
          }
        else
          return isValueInDomain(cm,x->getValue(),whyNot,masterObjective);

      }

      virtual bool includesThisType(const StructureEnv_New* cm,
                                    const std::string& childType,
                                    std::string *whyNot
                                    , const std::string &masterObjective)const override{}

      virtual StructureEnv_New* getComplexVarRep(
          const StructureEnv_New* cm,
          const ABC_Data_New* ,std::string* ,const std::string& )const override
      {
        return nullptr;
      }

      virtual ABC_Data_New* getClassRep(
          const StructureEnv_New* cm,
          const StructureEnv_New*   ,std::string*, const std::string& )const override
      {
        return nullptr;
      }


      virtual bool isOfThisType
      (const StructureEnv_New *cm
       , const std::__cxx11::string &generalType
       , std::__cxx11::string *whyNot
       , const std::__cxx11::string &masterObjective) const override
      {

        if ((generalType.empty()||myTypeId()==generalType))
          return true;
        else
          {
            auto gTp
                =cm->idToTyped<myC>(generalType,whyNot,masterObjective);
            std::string id=typeId();
            if ((id.empty())||(gTp==nullptr))
              return false;
            else
              return gTp->includesThisType(cm,id,whyNot,masterObjective);
          }

      }

      typedef buildByToken<myC> myBuild;



      virtual buildByToken<std::tuple<Args...>>* getBuildByToken(
          const StructureEnv_New* cm)const override
      {
        return new buildByToken<std::tuple<Args...>>(cm,this);
      }

      

      
      static constexpr std::size_t num_elements()
      {
        return std::tuple_size<dataTypesTuple>::value;
      }

      template <std::size_t dummy>
      static bool putValue_imp(const StructureEnv_New* cm,
                               const std::tuple<Args...>& v
                               ,const dataTypesTuple& arg
                               ,ABC_Output* ostream
                               ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")
      {
        return true;

      }


      template <std::size_t dummy,std::size_t I, std::size_t... Is>
      static bool putValue_imp(const StructureEnv_New* cm,
                               const std::tuple<Args...>& v
                               ,const dataTypesTuple& arg
                               ,ABC_Output* ostream
                               ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")
      {

        typedef typename std::tuple_element<I,std::tuple<Args...>>::type eType;
        const Implements_Data_Type_New<eType>* vType=std::get<I>(arg);
        if (vType==nullptr)
          vType=cm->idToTyped<eType>(Cls<eType>::name());
        eType x=std::get<I>(v);

        if (! vType->putValue(cm,x,ostream,whyNot,masterObjective))
          return false;
        else return putValue_imp<dummy,Is...>(cm,v,arg,ostream,whyNot,masterObjective);

      }




      template <std::size_t... Is>
      static bool putValue_imp(std::index_sequence<Is...>,const StructureEnv_New* cm,
                               const std::tuple<Args...>& v
                               ,const dataTypesTuple& arg
                               ,ABC_Output* ostream
                               ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")
      {
        return putValue_imp<0,Is...>(cm,v,arg,ostream,whyNot,masterObjective);
      }







      virtual bool putValue(const StructureEnv_New* cm,
                            const myC& v,ABC_Output* ostream
                            ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")const
      {
        if ((whyNot==nullptr)||(this->isValueInDomain(cm,v,whyNot,masterObjective)))
          {
            return putValue_imp(std::index_sequence_for<Args...>(),cm,v,args_,ostream,whyNot,masterObjective);
          }
        else return false;
      }


      template<std::size_t...Is>
      constexpr static std::tuple<const Implements_Data_Type_New<Args>*...>
      getTypesFromArg (const StructureEnv_New* cm,const dataTypesTuple& arg,std::index_sequence<Is...>)
      {
        return {std::get<Is>(arg).dataType(cm)...};
      }

      template<std::size_t D>
      static void fill_imp(myC& , const dataTypesTuple&)
      {
      }

      template <std::size_t D>
      static void fill_imp(myC& v, std::size_t iArg,const dataTypesTuple& arg)
      {}


      template <std::size_t D,std::size_t I,std::size_t... Is>
      static void fill_imp(myC& v, const dataTypesTuple& arg)
      {
        std::get<I>(v)=std::get<I>(arg).defaultValue();
        fill_imp<D,Is...>(v,arg);
      }


      template <std::size_t D,std::size_t I,std::size_t... Is>
      static void fill_imp(myC& v, std::size_t iArg,const dataTypesTuple& arg)
      {
        if (I<iArg)  fill_imp<D,Is...>(v,iArg,arg);
        else
          fill_imp<D,Is...>(v,arg);
      }

      
      template <std::size_t... Is>
      static void fill_imp(myC& v, std::size_t iArg,const dataTypesTuple& arg,
                           std::index_sequence<Is...>)
      {
        fill_imp<0,Is...>(v,iArg,arg);
      }


      template <std::size_t D>
      static bool getValue_imp(const StructureEnv_New* cm,
                               myC& v,const dataTypesTuple& arg
                               ,ABC_Input* istream,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")
      {
        return true;

      }




      template <std::size_t D,std::size_t I,size_t...Is>
      static bool getValue_imp(const StructureEnv_New* cm,
                               myC& v,const dataTypesTuple& arg
                               ,ABC_Input* istream,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")
      {
        typedef typename std::tuple_element<I,myC>::type eType;
        const Implements_Data_Type_New<eType>* vType=std::get<I>(arg);
        bool mandatory=std::get<I>(arg).isMandatory();
        if (vType==nullptr)
          vType=cm->idToTyped<eType>(Cls<eType>::name());
        eType& x=std::get<I>(v);

        if (!mandatory &&  (istream->testIfNextCharIs('\n')||istream->eof()))
          {
            fill_imp<0,Is...>(v,arg);
            return true;
          }
        else if (! vType->getValue(cm,x,istream,whyNot,masterObjective))
          return false;
        else
          return getValue_imp<0,Is...>(cm,v,arg,istream,whyNot,masterObjective);

      }



      virtual bool getValue(const StructureEnv_New* cm
                            ,myC& v, ABC_Input* istream,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")const
      {

        if (!getValue_imp<0>(cm,v,args_,istream,whyNot,masterObjective))
          return false;
        else
          return (whyNot==nullptr)||this->isValueInDomain(cm,v,whyNot,masterObjective);
      }


      const dataTypesTuple& getArguments()const{return args_;}






      virtual std::set<std::string> alternativeNext(const StructureEnv_New* cm)const
      {
        return {"<"+Cls<myC>::name()+">"};
      }

      virtual ~Implements_Data_Type_New_tuple(){}



      Implements_Data_Type_New_tuple(const StructureEnv_New* cm,
                                     dataTypesTuple arg={},
                                     typePredicate complyPred=nullptr)
        :args_(arg),
          comply_(complyPred)
      {}



      Implements_Data_Type_New_tuple(const Implements_Data_Type_New_tuple<myC>& other)
        :args_(other.args_),
          comply_(other.comply_){}




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
      virtual Implements_Data_Type_New_tuple *clone() const override
      {
        return new Implements_Data_Type_New_tuple(*this);
      }
      virtual Implements_Data_Type_New_tuple *create() const override
      {
        return new Implements_Data_Type_New_tuple(nullptr);
      }

      virtual bool isValueInDomain(const StructureEnv_New* cm
                                   ,const myC &val
                                   , std::string *whyNot
                                   ,const std::string& masterObjective ) const
      {
        if (comply_==nullptr)
          return true;
        else
          return (*comply_)(cm,val,this,whyNot,masterObjective);
      }



      virtual ABC_Type_of_Value const* myType()const{return nullptr;}
      virtual std::string myTypeId()const{ return Cls<myC>::name();};

      virtual bool getData(const StructureEnv_New* cm
                           ,ABC_Data_New*& v
                           , ABC_Input* istream
                           ,std::string* error
                           , const std::string& masterObjective)const{}

      virtual std::string typeId()const {return myId();}


      virtual const Implements_Identifier* getVarIdType(const StructureEnv_New* cm)const override
      {
        return nullptr;
      }
      virtual const Implements_Identifier* getTypeIdType(const StructureEnv_New* cm)const override
      {
        return nullptr;
      }


    protected:
      typePredicate comply_;
      dataTypesTuple args_;
    };










  };














  namespace _private
  {


    template<typename T>
    class Implements_Data_Type_New_regular:public Implements_Base_Type_New<T>
    {
    public:
      typedef  Implements_Data_Type_New_regular<T> selfType;
      typedef T myC;
      static std::string myId() {return Cls<myC>::name();}
      static selfType* varType(const StructureEnv_New* cm)
      {return new selfType{};}
      static std::string myTip(){return "a regular " +Cls<T>::name();}
      static std::string myWhatThis(){return "";}
      typedef mp_list<> dependsOn;
      typedef mp_list<> fieldList;

      using typePredicate=bool (*) (const StructureEnv_New* cm, const T& data
      ,const selfType* self
      , std::string *whyNot, const std::string& masterObjective);

      using getSet=std::set<std::string>(*)(const StructureEnv_New* cm,
      const selfType* SELF);


      typedef buildByToken<T> myBuild;


      virtual buildByToken<T>* getBuildByToken(
          const StructureEnv_New* cm)const override
      {
        return new buildByToken<T>(cm,this);
      }

      virtual bool putValue(const StructureEnv_New* cm,
                            const T& v,ABC_Output* ostream,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")const override
      {
        if ((whyNot==nullptr)||(this->isValueInDomain(cm,v,whyNot,masterObjective)))
          {
            ostream->put(v);
            return true;
          }
        else return false;
      }


      virtual bool getValue(const StructureEnv_New* cm
                            ,T& v, ABC_Input* istream,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")const override
      {

        if (!istream->get(v,whyNot,masterObjective))
          return false;
        else
          return (whyNot==nullptr)||this->isValueInDomain(cm,v,whyNot,masterObjective);
      }


      virtual std::set<std::string> alternativeNext(const StructureEnv_New* cm)const
      {
        if (alternativesNext_!=nullptr)
          return (*alternativesNext_)(cm,this);
        else
          return {"<"+Cls<T>::name()+">"};
      }

      virtual ~Implements_Data_Type_New_regular(){}



      Implements_Data_Type_New_regular(const std::string& id,
                                       const Implements_Data_Type_New<myC>*  typeType,
                                       typePredicate complyPred=nullptr,
                                       getSet alternatives=nullptr)
        :typeId_(id)
        ,varIdType_(Identifier::types::idVarUsed::varType(id))
        ,typeIdType_(Identifier::types::idType::varType(id))
        ,typeType_(typeType),
          comply_(complyPred),alternativesNext_(alternatives)

      {}

      Implements_Data_Type_New_regular()
        :Implements_Data_Type_New_regular(Cls<myC>::name(),nullptr){}
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

      static void push_Types(StructureEnv_New *cm)
      {
        cm->pushType<T>(Cls<T>::name()
                     ,new Implements_Data_Type_New_regular<T>()
                     ,Cls<T>::name(),"a regular "+Cls<T>::name());
      }

      friend class Real::types;
      virtual bool getData(const StructureEnv_New* cm
                           ,ABC_Data_New*& v
                           , ABC_Input* istream
                           ,std::string* error
                           , const std::string& masterObjective)const override
      {
        myC data;
        if (!getValue(cm,data,istream,error,masterObjective))
          return false;
        else
          {
            v= new Implements_Value_New<myC>(this,data);
            return true;
          }
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

      virtual const Implements_Identifier* getVarIdType(const StructureEnv_New* cm)const override
      {
        return varIdType_;
      }
      virtual const Implements_Identifier* getTypeIdType(const StructureEnv_New* cm)const override
      {
        return typeIdType_;
      }

    protected:
      std::string typeId_;
      const Implements_Identifier* varIdType_;
      const Implements_Identifier* typeIdType_;
      Implements_Data_Type_New<myC> const * typeType_;
      typePredicate comply_;
      getSet alternativesNext_;
    };




    template<>
    class Implements_Data_Type_New_regular<void> :public ABC_Type_of_Value
    {
    public:
      typedef  void myC;
      typedef Implements_Data_Type_New_regular<void> selfType;
      static std::string myId() {return Cls<myC>::name();}
      static selfType* varType(const StructureEnv_New* cm)
      {return new selfType{};}
      static std::string myTip(){return "a " +Cls<void>::name();}
      static std::string myWhatThis(){return "";}
      typedef mp_list<> dependsOn;
      typedef mp_list<> fieldList;


      virtual bool getData(const StructureEnv_New* cm
                           ,ABC_Data_New*& v
                           , ABC_Input* istream
                           ,std::string* error
                           , const std::string& masterObjective)const override
      {
        v= new Implements_Value_New<void>(this);
        return true;
      }

      virtual bool isDataInDomain(const StructureEnv_New* cm
                                  ,const ABC_Data_New* v
                                  , std::string *whyNot
                                  , const std::string& masterObjective)const override
      {
        return v->myType()->typeId()==typeId();
      }


      virtual bool putData(const StructureEnv_New* cm
                           ,const ABC_Data_New* v
                           ,ABC_Output* ostream
                           ,std::string* whyNot,
                           const std::string& masterObjective)const override
      {
        return isDataInDomain(cm,v,whyNot,masterObjective);
      }
      typedef ABC_BuildByToken myBuild;


      virtual ABC_BuildByToken* getBuildByToken(
          const StructureEnv_New* cm)const override
      {
        return nullptr;
      }


      virtual bool isOfThisType(const StructureEnv_New* cm,
                                const std::string& generalType,
                                std::string* whyNot
                                ,const std::string &masterObjective)const override
      {
        if ((generalType.empty()||myTypeId()==generalType))
          return true;
        else
          return false;

      }

      virtual bool includesThisType(const StructureEnv_New* cm
                                    ,const std::string& childType
                                    ,std::string *whyNot
                                    , const std::string &masterObjective)const override
      {
        return typeId()==childType;
      }



      virtual std::set<std::string> alternativeNext(const StructureEnv_New* cm)const
      {
        return {};
      }

      virtual ~Implements_Data_Type_New_regular(){}



      Implements_Data_Type_New_regular(){}

      virtual StructureEnv_New* getComplexVarRep(
          const StructureEnv_New* cm,
          const ABC_Data_New* var
          ,std::string* whyNot
          ,const std::string& masterObjective)const override {return nullptr;}

      virtual ABC_Data_New* getClassRep(const StructureEnv_New* cm,
                                        const StructureEnv_New* cvar,
                                        std::string* whyNot,
                                        const std::string& masterObjective)const override
      {return nullptr;}




      // ABC_Data_New interface
    public:
      virtual bool empty() const override
      {
        return true;
      }
      virtual void reset() override
      {
      }
      virtual Implements_Data_Type_New_regular *clone() const override
      {
        return new Implements_Data_Type_New_regular(*this);
      }
      virtual Implements_Data_Type_New_regular *create() const override
      {
        return new Implements_Data_Type_New_regular();
      }


      static void push_Types(StructureEnv_New *cm);

      virtual const Implements_Identifier* getVarIdType(const StructureEnv_New* cm)const override
      {
        return nullptr;
      }
      virtual const Implements_Identifier* getTypeIdType(const StructureEnv_New* cm)const override
      {
        return nullptr;
      }


      virtual ABC_Type_of_Value const* myType()const override {return nullptr;}
      virtual Implements_Data_Type_New<myC> const * myTypeD()const {return nullptr;}

      std::string typeId()const override {return  Cls<void>::name();}

      std::string myTypeId()const override  {
        return Cls<void>::name();
      }



    };




    template<typename T>
    using My_set = std::set<T>;  // to fake that set takes only one template argument

    template<typename T>
    class Implements_Data_Type_New_set:public Implements_Container_Type_New<T,My_set>
    {
    public:
      typedef std::set<T> myC;

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
                            ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")const override
      {
        if ((whyNot==nullptr)||(this->isValueInDomain(cm,v,whyNot,masterObjective)))
          {
            const Implements_Data_Type_New<T>* etype=this->getElementDataType(cm);
            ostream->put("\n{");
            for (auto it=v.begin(); it!=v.end(); ++it)
              {
                if(!etype->putValue(cm,*it,ostream,whyNot,masterObjective))
                  {
                    return false;
                  }
              }
            ostream->put("}");
            return true;
          }
        else
          return false;
      }

      virtual bool getData(const StructureEnv_New* cm
                           ,ABC_Data_New*& v
                           , ABC_Input* istream
                           ,std::string* error
                           , const std::string& masterObjective)const override
      {
        myC data;
        if (!getValue(cm,data,istream,error,masterObjective))
          return false;
        else
          {
            v= new Implements_Value_New<myC>(this,data);
            return true;
          }
      }

      virtual bool getValue(const StructureEnv_New* cm
                            ,std::set<T>& v, ABC_Input* istream
                            ,std::string* whyNot=nullptr
          ,const std::string& masterObjective="")const override
      {
        char c;
        const Implements_Data_Type_New<T>* etype=this->getElementDataType(cm);
        if (etype==nullptr)
          return false;
        while (!istream->nextCharIs('\n',true)){}
        if (!istream->nextCharIs('{',c))
          {
            if (whyNot!=nullptr)
              *whyNot= masterObjective+": expected { found"+c;
            return false;
          }
        else
          {
            while (!istream->nextCharIs('}',false))
              {
                T d;
                if (etype->getValue(cm,d,istream,whyNot,masterObjective))
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


      virtual const Implements_Data_Type_New<T>* getElementDataType(const StructureEnv_New* cm)const
      {
        if (elementVar_!=nullptr)
          return elementVar_;
        else
          return cm->idToTyped<T>(Cls<T>::name());
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
      typedef Implements_Data_Type_New_M_Matrix<T> selfType;
      typedef Markov_LA::M_Matrix<T> myC;

      static std::string myId() {return Cls<myC>::name();}
      static selfType* varType(const StructureEnv_New* cm)
      {return new selfType(myId(),nullptr);}
      static std::string myTip(){return "Matrix of "+Cls<T>::name();}
      static std::string myWhatThis(){return "";}
      typedef mp_list<Implements_Data_Type_New<T>> dependsOn;
      typedef mp_list<> fieldList;

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



      typedef buildByToken<myC> myBuild;
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

      virtual bool getData(const StructureEnv_New* cm
                           ,ABC_Data_New*& v
                           , ABC_Input* istream
                           ,std::string* error
                           , const std::string& masterObjective)const override
      {
        myC data;
        if (!getValue(cm,data,istream,error,masterObjective))
          return false;
        else
          {
            v= new Implements_Value_New<myC>(this,data);
            return true;
          }
      }



      bool getValue(const StructureEnv_New *cm, Markov_LA::M_Matrix<T> &v, ABC_Input *istream, std::string *whyNot, const std::string &masterObjective) const
      {
        auto etype=this->getElementDataType(cm)->clone();
        char c;
        while (!istream->nextCharIs('\n',true)){}

        bool fixedCol=hasFixedCols();
        bool fixedRow=hasFixedRows();
        std::size_t nCols=getNumberOfCols(cm);
        std::size_t nRows=getNumberOfRows(cm);
        std::size_t ncells=nCols*nRows;
        std::vector<T> vec(ncells);

        if((nRows==0)&&fixedRow)
          return true;
        else if (nRows==0)
          {
            if (istream->nextCharIs('\n',false))
              return true;
            else
              ++nRows;
          }
        for (std::size_t i=0; i<nRows; ++i)
          {
            for (std::size_t j=0; j<nCols; ++j)
              {
                T d;
                etype=this->getElementType
                    (cm,vec,nRows,nCols,i,j
                     ,whyNot,masterObjective,etype);

                if(!etype->getValue
                   (cm,d,istream,whyNot,masterObjective))
                  {
                    return false;
                  }
                else if (i*nCols+j<ncells)
                  {
                    vec[i*nCols+j]=d;
                  }
                else
                  vec.push_back(d);
              }
            if (!fixedCol)
              {
                while (!istream->nextCharIs('\n',false))
                  {
                    T d;
                    etype=this->getElementType
                        (cm,vec,nRows,nCols,i,nCols
                         ,whyNot,masterObjective,etype);
                    if(!etype->getValue
                       (cm,d,istream,whyNot,masterObjective))
                      {
                        return false;
                      }
                    else if (nCols<ncells)
                      {
                        vec[nCols]=d;
                      }
                    else
                      vec.push_back(d);
                    ++nCols;
                  }
                fixedCol=true;
              }
            else if (!istream->nextCharIs('\n',c))
              {
                if (whyNot!=nullptr)
                  *whyNot=masterObjective+": "+c+" is not an end of line";
                return false;
              }
          }
        if (!fixedRow)
          {
            while (!istream->nextCharIs('\n',false))
              {
                for (std::size_t j=0; j<nCols; ++j)
                  {
                    T d;
                    etype=this->getElementType
                        (cm,vec,nRows,nCols,nRows,j
                         ,whyNot,masterObjective,etype);
                    if(!etype->getValue
                       (cm,d,istream,whyNot,masterObjective))
                      {
                        return false;
                      }
                    else if (nRows*nCols+j<ncells)
                      {
                        vec[nRows*nCols+j]=d;
                      }
                    else
                      vec.push_back(d);
                  }
                if (!istream->nextCharIs('\n',c))
                  {
                    if (whyNot!=nullptr)
                      *whyNot=masterObjective+": "+c+" is not an end of line";
                    return false;
                  }
                ++nRows;
              }
          }
        else if (!istream->nextCharIs('\n',c))
          {
            if (whyNot!=nullptr)
              *whyNot=masterObjective+": "+c+" is not an end of line";
            return false;
          }
        v=Markov_LA::M_Matrix<T>(nRows,nCols,vec);
        return (whyNot==nullptr)
            ||(this->isValueInDomain(cm,v,whyNot,masterObjective));
      }


      bool putValue(const StructureEnv_New *cm, const Markov_LA::M_Matrix<T> &v, ABC_Output *ostream, std::string *whyNot=nullptr, const std::string &masterObjective="") const
      {
        std::vector<T> vec(Markov_LA::size(v),T(0));

        if ((whyNot==nullptr)||(this->isValueInDomain(cm,v,whyNot,masterObjective)))
          {
            Implements_Data_Type_New<T>* etype=
                this->getElementDataType(cm)->clone();
            ostream->put("\n");
            auto nRows=Markov_LA::nrows(v);
            auto nCols=Markov_LA::ncols(v);
            for (std::size_t i=0; i<Markov_LA::nrows(v); ++i)
              {
                for (std::size_t j=0; j<Markov_LA::ncols(v); ++j)
                  {
                    vec[i*nCols+j]=v(i,j);
                    etype=this->getElementType
                        (cm,vec,nRows,nCols,i,j
                         ,whyNot,masterObjective,etype);

                    if(!etype->putValue
                       (cm,v(i,j),ostream,whyNot,masterObjective))
                      {
                        return false;
                      }
                  }
                ostream->put("\n");
              }
            return true;
          }
        else
          return false;
      }

      Implements_Data_Type_New_M_Matrix
      (const std::string& idType, const selfType* typeType,
       const Implements_Data_Type_New<T>* elementVar=nullptr
          ,typePredicate complyPred=nullptr
          ,elementType getElement=nullptr
          ,getNumber getNumCols=nullptr
          ,getNumber getNumRows=nullptr
          ,bool areColsFixed=false
          ,bool areRowsFixed=false):
        typeId_(idType)
      ,varIdType_(Identifier::types::idVarUsed::varType(idType))
      ,typeIdType_(Identifier::types::idType::varType(idType))
      ,typeType_(typeType),
        elementType_(elementVar)
      ,complyPred_(complyPred),getElement_(getElement),
        getNumCols_(getNumCols),getNumRows_(getNumRows),
        areColsFixed_(areColsFixed),areRowsFixed_(areRowsFixed){}

Implements_Data_Type_New_M_Matrix(){}





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
        return new Implements_Data_Type_New_M_Matrix(Cls<myC>::name(),nullptr);
      }

      virtual bool isValueInDomain(const StructureEnv_New* cm
                                   ,const Markov_LA::M_Matrix<T> &val
                                   , std::string *whyNot
                                   ,const std::string& masterObjective ) const
      {
        return (*complyPred_)(cm,val,this,whyNot,masterObjective);
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

      virtual const Implements_Identifier* getVarIdType(const StructureEnv_New* cm)const override
      {
        return varIdType_;
      }
      virtual const Implements_Identifier* getTypeIdType(const StructureEnv_New* cm)const override
      {
        return typeIdType_;
      }


    protected:
      std::string typeId_;
      const Implements_Identifier* varIdType_;
      const Implements_Identifier* typeIdType_;
      Implements_Data_Type_New<myC> const * typeType_;
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


      virtual bool putValue(const StructureEnv_New *cm, const std::pair<K,T> &v, ABC_Output *ostream, std::string *whyNot=nullptr, const std::string &masterObjective="") const
      {
        if ((whyNot==nullptr)||(this->isValueInDomain(cm,v,whyNot,masterObjective)))
          {
            const Implements_Data_Type_New<K>* etype=
                this->getKeyDataType(cm);

            const Implements_Data_Type_New<T>* ktype=
                this->getElementDataType(cm);

            if(!ktype->putValue
               (cm,v.firts,ostream,whyNot,masterObjective))
              {
                return false;
              }
            ostream->put(":");
            if(!etype->putValue
               (cm,v.second,ostream,whyNot,masterObjective))
              {
                return false;
              }
            return true;
          }
        else
          return false;
      }
      virtual bool getValue(const StructureEnv_New *cm, std::pair<K,T> &v, ABC_Input *istream, std::string *whyNot, const std::string &masterObjective) const
      {

        const Implements_Data_Type_New<K>* etype=
            this->getKeyDataType(cm);

        const Implements_Data_Type_New<T>* ktype=
            this->getElementDataType(cm);
        if ((etype==nullptr)||(ktype==nullptr))
          return false;

        if(!ktype->getValue
           (cm,v.first,istream,whyNot,masterObjective))
          {
            return false;
          }
        char c;
        if (!istream->nextCharIs(':',c))
          {
            if (whyNot!=nullptr)
              *whyNot= masterObjective+": expected : found"+c;
            return false;
          }
        if(!etype->getValue
           (cm,v.second,istream,whyNot,masterObjective))
          {
            return false;
          }
        return (whyNot==nullptr)||(this->isValueInDomain(cm,v,whyNot,masterObjective));
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


      typedef std::pair<K,T> myC;

      typedef buildByToken<myC> myBuild;

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
      typedef std::map<K,T>  myC;

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
        if ((whyNot==nullptr)||(this->isValueInDomain(cm,v,whyNot,masterObjective)))
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
            return (whyNot==nullptr)||this->isValueInDomain(cm,v,whyNot,masterObjective);
          }

      }

      typedef buildByToken<myC> myBuild;

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
      virtual selfType *create() const override
      {
        return new selfType();
      }

      virtual bool getData(const StructureEnv_New* cm
                           ,ABC_Data_New*& v
                           , ABC_Input* istream
                           ,std::string* error
                           , const std::string& masterObjective)const override
      {
        myC data;
        if (!getValue(cm,data,istream,error,masterObjective))
          return false;
        else
          {
            v= new Implements_Value_New<myC>(this,data);
            return true;
          }
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
      virtual const Implements_Identifier* getVarIdType(const StructureEnv_New* cm)const override
      {
        return varIdType_;
      }
      virtual const Implements_Identifier* getTypeIdType(const StructureEnv_New* cm)const override
      {
        return typeIdType_;
      }



    protected:
      std::string typeId_;
      const Implements_Identifier* varIdType_;
      const Implements_Identifier* typeIdType_;
      Implements_Data_Type_New<myC> const * typeType_;
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

      typedef ABC_Data_New* myC;
      typedef Implements_Data_Type_New_ABC_Data_New selfType;

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
                            ,const std::string& masterObjective)const override;



      virtual ~Implements_Data_Type_New_ABC_Data_New();



      virtual const Implements_Identifier* getElementType()const
      {
        return idType_;
      }


      //      virtual Implements_Identifier* getElementType
      //      (const StructureEnv_New* cm,
      //       const ABC_Data_New* data
      //       , std::string* whyNot, const std::string& masterObjective
      //       , Implements_Identifier* source) const
      //      {
      //        if (getElement_==nullptr)
      //          return nullptr;
      //        else
      //          return (*getElement_)(cm,data,this,whyNot,masterObjective,source);
      //      }


      typedef buildByToken<myC> myBuild;

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
        return new Implements_Data_Type_New_ABC_Data_New(Cls<myC>::name(),nullptr);
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

      virtual ABC_Type_of_Value const* myType()const override
      {
        return typeType_;
      }

      std::string typeId()const override
      {
        return typeId_;
      }
      std::string myTypeId()const override  {
        if (myType()==nullptr)
          return Cls<myC>::name();
        else
          return myType()->typeId();
      }

      virtual const Implements_Identifier* getVarIdType(const StructureEnv_New* cm)const override
      {
        return nullptr;
      }
      virtual const Implements_Identifier* getTypeIdType(const StructureEnv_New* cm)const override
      {
        return nullptr;
      }

      Implements_Data_Type_New_ABC_Data_New(){}


    private:

      Implements_Data_Type_New_ABC_Data_New
      ( const std::string& id
        , Implements_Data_Type_New<myC> const * typeType,
        Implements_Identifier* idType=nullptr
          , typePredicate typeComply=nullptr
          ,elementType getElement=nullptr
          ,bool convertToClass=true
          ):
        typeId_(id),typeType_(typeType),
        idType_(idType),typeComply_(typeComply),getElement_(getElement),convertToClass_(convertToClass)
      {}

      std::string typeId_;
      Implements_Data_Type_New<myC> const * typeType_;
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
      typedef Implements_Var myC;

      using typePredicate=bool (*)
      (const StructureEnv_New * cm, const const_Implements_Var& iv,
      const Implements_Data_Type_New_Implements_Var* self
      , std::string * whyNot,const std::string& masterObjective);

      using  keyType= Implements_Identifier* (*)
      (const StructureEnv_New * cm, const const_Implements_Var& iv,
      const Implements_Data_Type_New_Implements_Var* self
      , std::string * whyNot,const std::string& masterObjective
      ,Implements_Identifier* source);

      using  elemType= Implements_Data_Type_New<ABC_Data_New*>* (*)
      (const StructureEnv_New * cm, const const_Implements_Var& iv,
      const Implements_Data_Type_New_Implements_Var* self
      , std::string * whyNot,const std::string& masterObjective
      ,Implements_Data_Type_New<ABC_Data_New*>* source);


      virtual bool putValue(const StructureEnv_New* cm
                            ,const const_Implements_Var& v
                            ,ABC_Output* ostream
                            ,std::string* whyNot=nullptr,
                            const std::string& masterObjective="")const
      {
        if ((whyNot==nullptr)||(this->isValueInDomain(cm,v,whyNot,masterObjective)))
          {
            const Implements_Identifier* ktype=this->getKeyType(cm);

            const Implements_Data_Type_New<ABC_Data_New*>* etype=this->getElementType(cm);

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
            if(!etype->putValue
               (cm,v.data,ostream,whyNot,masterObjective))
              {
                return false;
              }
            return true;


          }
        return false;
      }


      virtual bool putValue(const StructureEnv_New* cm
                            ,const Implements_Var& v
                            ,ABC_Output* ostream
                            ,std::string* whyNot=nullptr,
                            const std::string& masterObjective="")const override
      {
        const_Implements_Var cv(v);
        return putValue(cm,cv,ostream,whyNot,masterObjective);
      }


      virtual bool getValue(const StructureEnv_New* cm
                            ,Implements_Var& v, ABC_Input* istream,std::string* whyNot
                            ,const std::string& masterObjective)const override;

      virtual ~Implements_Data_Type_New_Implements_Var(){}


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

      virtual const Implements_Data_Type_New<ABC_Data_New*>* getElementType(const StructureEnv_New* cm)const
      {
        return dataType_;
      }


      virtual Implements_Data_Type_New<ABC_Data_New*>* getElementType
      (const StructureEnv_New* cm, const const_Implements_Var& v,
       std::string* whyNot,
       const std::string& masterObjective,Implements_Data_Type_New<ABC_Data_New*>* source)const
      {
        if (getElement_==nullptr)
          return source;
        else return (*getElement_)(cm,v,this,whyNot,masterObjective,source);
      }

      typedef buildByToken<myC> myBuild;
      virtual buildByToken<Implements_Var>* getBuildByToken(const StructureEnv_New* cm)const override
      {
        return new buildByToken<Implements_Var>(cm,this);
      }

      virtual void setVariable(const Implements_Var& v)
      {
        idType_->setName(v.id);
        dataType_->setDataType(v.data->myTypeId());
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
      Implements_Data_Type_New_Implements_Var():
        Implements_Data_Type_New_Implements_Var(Cls<myC>::name(),nullptr,nullptr,nullptr){}


      virtual bool getData(const StructureEnv_New* cm
                           ,ABC_Data_New*& v
                           , ABC_Input* istream
                           ,std::string* error
                           , const std::string& masterObjective)const override
      {
        myC data;
        if (!getValue(cm,data,istream,error,masterObjective))
          return false;
        else
          {
            v= new Implements_Value_New<myC>(this,data);
            return true;
          }
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
                                   ,const const_Implements_Var &val
                                   , std::string *whyNot
                                   ,const std::string& masterObjective ) const
      {
        if (comply_==nullptr)
          return true;
        else
          return (*comply_)(cm,val,this,whyNot,masterObjective);
      }

      virtual bool isValueInDomain(const StructureEnv_New* cm
                                   ,const Implements_Var &val
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



    private:


      Implements_Data_Type_New_Implements_Var
      ( const std::string& id, Implements_Data_Type_New_Implements_Var* const typeType,
        Implements_Identifier* idType,
        Implements_Data_Type_New<ABC_Data_New*>* dataType,
        typePredicate comply=nullptr,
        elemType getElement=nullptr,
        keyType getKey=nullptr);


      std::string typeId_;
      Implements_Data_Type_New_Implements_Var const * typeType_;
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

      typedef StructureEnv_New*  myC;

      typedef Implements_Data_Type_New_StructureEnv selfType;
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
        if ((whyNot==nullptr)||(this->isValueInDomain(cm,v,whyNot,masterObjective)))
          {
            auto etype=this->getElementType()->clone();
            auto varlis=v->getIdsOfVarType("",false);
            ostream->put("\n{\n");
            std::size_t ifield=0;
            for (auto id:varlis)
              {
                etype=getElementType(cm,v,ifield,whyNot,masterObjective,etype);
                auto iv=v->idToVar(id);
                if(!etype->putValue(cm,iv,ostream,whyNot,masterObjective))
                  {
                    return false;
                  }
                ++ifield;
              }
            ostream->put("}");
            return true;
          }
        else
          return false;
      }



      virtual bool getValue(const StructureEnv_New* cm
                            ,StructureEnv_New*& v
                            , ABC_Input* istream
                            ,std::string* whyNot
                            ,const std::string &masterObjective)const override;


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
        if (elem_!=nullptr)
          return (*elem_)(cm,val,iField,this,whyNot,masterObjective,source);
        else
          return source;
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
      virtual selfType* create()const override
      {
        return new Implements_Data_Type_New<StructureEnv_New*>();
      }

      virtual bool getData(const StructureEnv_New* cm
                           ,ABC_Data_New*& v
                           , ABC_Input* istream
                           ,std::string* error
                           , const std::string& masterObjective)const override
      {
        myC data;
        if (!getValue(cm,data,istream,error,masterObjective))
          return false;
        else
          {
            v= data;
            return true;
          }
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

      virtual const Implements_Identifier* getVarIdType(const StructureEnv_New* cm)const override
      {
        return nullptr;
      }
      virtual const Implements_Identifier* getTypeIdType(const StructureEnv_New* cm)const override
      {
        return nullptr;
      }



typedef buildByToken<myC> myBuild;

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
      Implements_Data_Type_New_StructureEnv(const std::string& idtype,Implements_Data_Type_New_StructureEnv const * typeType,
                                            std::vector<std::pair<Implements_Var,bool>> fields,
                                            const Implements_Data_Type_New<Implements_Var>* elemeType,
                                            typePredicate comply,
                                            typePredicate hasMandatory,
                                            typePredicate hasAll,
                                            elementType elem):
        typeId_(idtype),
        typeType_(typeType),
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

      std::string typeId_;
      Implements_Data_Type_New<myC> const * typeType_;


      std::vector<std::pair<Implements_Var,bool>> fields_;
      const Implements_Data_Type_New<Implements_Var>* elementType_;
      typePredicate comply_;
      typePredicate hasMandatory_;
      typePredicate hasAll_;

      elementType elem_;

    };






  };

  namespace Count
  {
    typedef  std::size_t myC;
    typedef  Implements_Data_Type_New<myC> vType;

    struct types
    {
      template<typename numField>
      struct Given
      {
        typedef  std::size_t myC;
        typedef  Implements_Data_Type_New<myC> vType;
        static std::string myId(myC x){return "Count_given_"+numField::myId();}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string Tip(){return "count exacty equal to "+numField::myId();}
        static std::string WhatThis() {return "";}

        static bool comply
        (const StructureEnv_New* cm
         ,const myC& x
         ,const vType* v,
         std::string *WhyNot
         , const std::string& objective)
        {
          myC value;
          if (!v->getEnv()->getDataValue<numField>(value,WhyNot,objective))
            return false;


          if (x!=value)
            {
              *WhyNot=objective+": x="+std::to_string(x)+"is not equal to "
                  +numField::myId()+" = "+std::to_string(value);
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
          if (!v->getEnv()->getDataValue<numField>(value))
            return {};
          else
            return {std::to_string(value)};
        }



        static Implements_Data_Type_New<myC>*
        varType()
        {
          return new Implements_Data_Type_New<myC>
              (myId(0),nullptr,&comply,&alternativeNext);
        }
        static Implements_Data_Type_New<myC>*
        varType(Implements_Data_Type_New<myC>* source,myC val)
        {
          source->comply_=&comply;
          source->alternativesNext_=&alternativeNext;
          return source;
        }


      };



      template<typename numField>
      struct Index
      {
        typedef  std::size_t myC;
        typedef  Implements_Data_Type_New<myC> vType;
        static std::string myId(){return "index_of_"+numField::myId();}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "index within "+numField::myId();}
        static std::string myWhatThis() {return "";}
        typedef mp_list<> dependsOn;
        typedef mp_list<numField>  fieldList;

        static bool comply
        (const StructureEnv_New* cm
         ,const myC& x
         ,const vType* v,
         std::string *WhyNot
         , const std::string& objective)
        {
          myC value;
          if (!cm->getDataValue<numField>(value,WhyNot,objective))
            return false;


          if (x>=value)
            {
              *WhyNot=objective+": x="+std::to_string(x)+"is greater than "
                  +numField::myId()+" = "+std::to_string(value);
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
          if (!cm->getDataValue<numField>(value))
            return {};
          else
            {

              std::set<std::string> out;
              for (auto i=0; i<value; ++i)
                out.insert(std::to_string(i));
              return out;
            }
        }


        static Implements_Data_Type_New<myC>*
        varType(const StructureEnv_New *)
        {
          return new Implements_Data_Type_New<myC>
              (myId(),nullptr,&comply,&alternativeNext);
        }
        static Implements_Data_Type_New<myC>*
        varType(Implements_Data_Type_New<myC>* source,myC val)
        {
          source->comply_=&comply;
          source->alternativesNext_=&alternativeNext;
          return source;
        }


      };




    };
    void push_Types(StructureEnv_New *cm);

  };



  namespace Real
  {
    typedef  double _myC;
    typedef  Implements_Data_Type_New<_myC> vType;

    struct fields
    {
      struct value  {
        typedef _myC myC;
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
        typedef _myC myC;
        static std::string myId(){return "real_nonZero";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "any non zero real number";}
        static std::string myWhatThis() {return "";}

        typedef mp_list<> dependsOn;
        typedef mp_list<> fieldList;

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
        varType(const StructureEnv_New *cm =nullptr)
        {
          return new Implements_Data_Type_New<myC>
              (myId(),nullptr,&comply,&alternativeNext);
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
        typedef _myC myC;
        static std::string myId(){return "real_positive_or_zero";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "zero or positive real number";}
        static std::string myWhatThis() {return "";}

        typedef mp_list<> dependsOn;
        typedef mp_list<> fieldList;

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
        varType(const StructureEnv_New * cm=nullptr)
        {
          return new Implements_Data_Type_New<myC>
              (myId(),nullptr,&comply,&alternativeNext);
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
        typedef _myC myC;
        static std::string myId(){return "real_positive";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "any postive non zero real number";}
        static std::string myWhatThis() {return "";}

        typedef mp_list<> dependsOn;
        typedef mp_list<> fieldList;


        static bool comply
        (const StructureEnv_New* cm
         ,const myC& x
         ,const vType* ,
         std::string *WhyNot
         , const std::string& objective);

        static std::set<std::string> alternativeNext
        (const StructureEnv_New*
         ,const vType* )
        {
          return {"<positive number>"};
        }



        static Implements_Data_Type_New<myC>*
        varType(const StructureEnv_New* cm=nullptr)
        {
          return new Implements_Data_Type_New<myC>
              (myId(),nullptr,&comply,&alternativeNext);
        }
        static Implements_Data_Type_New<myC>*
        varType(Implements_Data_Type_New<myC>* source)
        {
          source->comply_=&comply;
          source->alternativesNext_=&alternativeNext;
          return source;

        }

        static void push_Types(StructureEnv_New *cm)
        {
          if (!cm->hasType(myId()))
            cm->pushType<myC>(myId(),varType(cm),myTip(),myWhatThis());
        }


      };


      struct valid
      {
        typedef _myC myC;
        static std::string myId(){return "real_valid";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "any valid real number, not infinite or nan";}
        static std::string myWhatThis() {return "";}

        typedef mp_list<> dependsOn;
        typedef mp_list<> fieldList;


        static bool comply
        (const StructureEnv_New* cm
         ,const myC& x
         ,const vType* ,
         std::string *WhyNot
         , const std::string& objective)
        {
          return std::isfinite(x);
        }

        static std::set<std::string> alternativeNext
        (const StructureEnv_New*
         ,const vType* )
        {
          return {"<valid real>"};
        }



        static Implements_Data_Type_New<myC>*
        varType(const StructureEnv_New* cm=nullptr)
        {
          return new Implements_Data_Type_New<myC>
              (myId(),nullptr,&comply,&alternativeNext);
        }
        static Implements_Data_Type_New<myC>*
        varType(Implements_Data_Type_New<myC>* source)
        {
          source->comply_=&comply;
          source->alternativesNext_=&alternativeNext;
          return source;

        }

        static void push_Types(StructureEnv_New *cm)
        {
          if (!cm->hasType(myId()))
            cm->pushType<myC>(myId(),varType(cm),myTip(),myWhatThis());
        }


      };


      struct finite
      {
        typedef _myC myC;
        static std::string myId(){return "real_finite";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "real number, nan for missing values";}
        static std::string myWhatThis() {return "";}

        typedef mp_list<> dependsOn;
        typedef mp_list<> fieldList;


        static bool comply
        (const StructureEnv_New* cm
         ,const myC& x
         ,const vType* ,
         std::string *WhyNot
         , const std::string& objective)
        {
          return std::isfinite(x)||std::isnan(x);
        }

        static std::set<std::string> alternativeNext
        (const StructureEnv_New*
         ,const vType* )
        {
          return {"<valid real>",std::to_string(std::nan(""))};
        }



        static Implements_Data_Type_New<myC>*
        varType(const StructureEnv_New* cm=nullptr)
        {
          return new Implements_Data_Type_New<myC>
              (myId(),nullptr,&comply,&alternativeNext);
        }
        static Implements_Data_Type_New<myC>*
        varType(Implements_Data_Type_New<myC>* source)
        {
          source->comply_=&comply;
          source->alternativesNext_=&alternativeNext;
          return source;

        }

        static void push_Types(StructureEnv_New *cm)
        {
          if (!cm->hasType(myId()))
            cm->pushType<myC>(myId(),varType(cm),myTip(),myWhatThis());
        }


      };


      struct nan
      {
        typedef _myC myC;
        static std::string myId(){return "not_a_number";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "nan for missing values";}
        static std::string myWhatThis() {return "";}

        typedef mp_list<> dependsOn;
        typedef mp_list<> fieldList;


        static bool comply
        (const StructureEnv_New* cm
         ,const myC& x
         ,const vType* ,
         std::string *WhyNot
         , const std::string& objective)
        {
          return std::isnan(x);
        }

        static std::set<std::string> alternativeNext
        (const StructureEnv_New*
         ,const vType* )
        {
          return {std::to_string(std::nan(""))};
        }



        static Implements_Data_Type_New<myC>*
        varType(const StructureEnv_New* cm=nullptr)
        {
          return new Implements_Data_Type_New<myC>
              (myId(),nullptr,&comply,&alternativeNext);
        }
        static Implements_Data_Type_New<myC>*
        varType(Implements_Data_Type_New<myC>* source)
        {
          source->comply_=&comply;
          source->alternativesNext_=&alternativeNext;
          return source;

        }

        static void push_Types(StructureEnv_New *cm)
        {
          if (!cm->hasType(myId()))
            cm->pushType<myC>(myId(),varType(cm),myTip(),myWhatThis());
        }


      };



      struct Zero
      {
        typedef _myC myC;
        typedef  Implements_Data_Type_New<myC> vType;
        static std::string myId(){return "Real_zero";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "zero real number";}
        static std::string myWhatThis() {return "";}

        typedef mp_list<> dependsOn;
        typedef mp_list<> fieldList;

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
        varType(const StructureEnv_New*cm=nullptr )
        {
          return new Implements_Data_Type_New<myC>
              (myId(),nullptr,&comply,&alternativeNext);
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
        typedef _myC myC;
        typedef  Implements_Data_Type_New<myC> vType;
        static std::string myId(myC x){return "Real_given_"+std::to_string(x);}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "given real number";}
        static std::string myWhatThis() {return "";}

        typedef mp_list<> dependsOn;
        typedef mp_list<> fieldList;

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
              (myId(val),nullptr,&comply,&alternativeNext);
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



      struct greaterThan
      {
        typedef _myC myC;
        typedef  Implements_Data_Type_New<myC> vType;
        static std::string myId(myC x){return "Real_GT_"+std::to_string(x);}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(myC x){return "real number greater than"
              +std::to_string(x);}
        static std::string myWhatThis() {return "";}

        typedef mp_list<> dependsOn;
        typedef mp_list<> fieldList;

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

          if (x-value<std::numeric_limits<double>::epsilon())
            {
              *WhyNot=objective+": x="+std::to_string(x)+" has to be greater than "
                  +std::to_string(value);
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
            return {"<more than "+std::to_string(value)+">"};
        }



        static Implements_Data_Type_New<myC>*
        varType(myC val)
        {
          auto out= new Implements_Data_Type_New<myC>
              (myId(val),nullptr,&comply,&alternativeNext);
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
    void push_Types(StructureEnv_New *cm);

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
    void push_Types(StructureEnv_New *cm);
  };



  namespace Vector
  {
    template <typename T>
    using vType=  Implements_Data_Type_New<std::vector<T>>;
    struct Comply
    {
      template<typename T>
      static bool Size(
          const std::vector<T>& x,
          std::size_t numElem,
          std::string* whyNot, const std::string& masterObjective)
      {
        std::string objective=masterObjective+": size mismatch";
        if(x.size()!=numElem)
          {
            *whyNot=objective+": size required: "
                +std::to_string(numElem)+" present:"
                +std::to_string(x.size());
            return false;
          }
        else
          return true;
      }



    };



    template<typename T>
    void push_Types(StructureEnv_New *cm);
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
          return self->getElementType()->isValueInDomain(cm,data->myTypeId(),whyNot,masterObjective);
        }

        static Implements_Data_Type_New<myC>*
        varType(const std::string& nameoftype="")
        {
          return new Implements_Data_Type_New<ABC_Data_New*>(myId(nameoftype),nullptr,
                                                             Identifier::types::idType::varType(nameoftype)
                                                             ,comply, nullptr,true);
        }

      };


    };

    void push_Types(StructureEnv_New *cm);

  };


  namespace Variable {
    typedef Implements_Data_Type_New<Implements_Var> vType;

    struct types
    {

      struct var{
        typedef  Implements_Var myC;
        static std::string myId(){return "_var";}
        static std::string myId(const std::string& name)
        {return myId()+name;}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){ return "tip";}
        static std::string myWhatThis() {return "aht";}


        static Implements_Data_Type_New<myC>*
        varType(const std::string nameoftype="")
        {

          return new Implements_Data_Type_New<Implements_Var>(
                myId(nameoftype),nullptr,
                Identifier::types::idVar::varType(nameoftype)
                ,Data::types::data::varType(nameoftype)
                ,nullptr,nullptr);
        }



      };


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
                myId(nameoftype),nullptr,
                Identifier::types::idVarNew::varType(nameoftype)
                ,Data::types::data::varType(nameoftype)
                ,nullptr,nullptr);
        }

        static Implements_Data_Type_New<myC>*
        varType(Implements_Data_Type_New<myC>* source,
                const std::string nameoftype="")
        {

          return new Implements_Data_Type_New<Implements_Var>(
                myId(nameoftype),nullptr,
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
                myId(nameoftype),nullptr,
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
        (const StructureEnv_New * cm, const const_Implements_Var& iv,
         const vType* self
         , std::string * whyNot,const std::string& masterObjective)
        {
          return true;
        }

        static  Implements_Identifier* nextKey
        (const StructureEnv_New * cm, const const_Implements_Var& iv,
         const vType* self
         , std::string * whyNot,const std::string& masterObjective
         ,Implements_Identifier* source)
        {
          source->setName(self->getKeyType(cm)->getName());
          return source;
        }

        static  Implements_Data_Type_New<ABC_Data_New*>* nextElement
        (const StructureEnv_New * cm, const const_Implements_Var& iv,
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
            varType=var.data->myTypeId();

          return new Implements_Data_Type_New<Implements_Var>(
                myId(),nullptr,
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

    void push_Types(StructureEnv_New *cm);

  };



  namespace ComplexVar
  {

    class types
    {
      typedef StructureEnv_New* myC;
    public:
      template <class T>
      static  Implements_Data_Type_New<myC>* getVarType(const std::string& classId,
                                                        std::vector<std::pair<Implements_Var,bool>> fields)

      {
        Implements_Var firstVar;
        if (fields.size()>0)
          firstVar=fields[0].first;

        return new Implements_Data_Type_New<StructureEnv_New*>
            (T::myId(classId),nullptr,
             fields,
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
              if (!val->hasNameofType(v.id,v.data->myTypeId(),false,error,obj))
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
              if (!val->hasNameofType(v.id,v.data->myTypeId(),false,error,obj))
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


        static  Implements_Data_Type_New<myC>* varType(const std::string& classId,
                                                       std::vector<std::pair<Implements_Var,bool>> fields)
        {
          return getVarType<ClassDescript>(classId,fields);

        }


      };


      struct Var
      {
        typedef StructureEnv_New* myC;

        static std::string myId(){return "_varEnvironment";}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "working variables";}
        static std::string myWhatThis(){return "";}


        static  Implements_Data_Type_New<myC>* varType()
        {

          return new Implements_Data_Type_New<StructureEnv_New*>
              (myId(),nullptr,
          {},
               Variable::types::var::varType()
               ,nullptr,
               nullptr,
               nullptr,
               nullptr);

        }



      };



    };
    void push_Types(StructureEnv_New *cm);


  };


  namespace _private {

    namespace _templates
    {

    }



    template<typename T>
    class Implements_Data_Type_class:public ABC_Type_of_Value
    {
    public:
      typedef  Implements_Data_Type_class<T>  selfType;

      using typePredicate= bool(*)
      (const StructureEnv_New*
      ,const T&
      ,const selfType*
      , std::string*
      ,const std::string& );



      using getClass_type=T (*)(const StructureEnv_New* cm
      ,const StructureEnv_New*  m
      ,bool& success
      ,const selfType* self
      ,std::string *WhyNot,const std::string& masterObjective);

      using getCV=StructureEnv_New* (*)(
      const StructureEnv_New* cm,
      const T& v
      ,const selfType* self,
      std::string *WhyNot,const std::string & masterObjective);



      virtual bool isDataInDomain
      (const StructureEnv_New* cm
       ,const ABC_Data_New* v
       , std::string *whyNot
       , const std::string& masterObjective)const override
      {
        const std::string objective=masterObjective+": "+typeId()+ "do not has it in domain";
        auto x=dynamic_cast<const Implements_Value_New<T>* >(v);
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
        std::string id=typeId();
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
            *error=masterObjective+ ": "+data->myTypeId()+" is not a "+myTypeId();
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
            v= new Implements_Value_New<T>(this,data);
            return true;
          }
      }




      virtual bool putValue(const StructureEnv_New* cm
                            ,const T& c
                            ,ABC_Output* ostream
                            ,std::string* whyNot
                            , const std::string& masterObjective)const
      {
        auto v= cm->idToTyped<T>(myClassOf(c),whyNot,masterObjective);
        if (v==nullptr)
          return false;
        if (v==this)
          {

            StructureEnv_New* m
                =getComplexMap(cm,c,whyNot,masterObjective);
            if (m==nullptr)
              return false;
            else
              return CVtype_->putValue
                  (m,m,ostream,whyNot,masterObjective);
          }
        else
          return v->putValue(cm,c,ostream,whyNot,masterObjective);
      }

      virtual bool getValue(const StructureEnv_New* cm
                            ,T& v
                            , ABC_Input* istream
                            ,std::string* whyNot
                            ,const std::string& MasterObjective )const
      {
        auto m=new StructureEnv_New(cm,Cls<T>::name());
        if (!CVtype_->getValue(m,m,istream,whyNot,MasterObjective))
          return false;
        else
          {
            bool success;
            auto x=getClass(cm,m,success,whyNot,MasterObjective);
            if (!success||!isValueInDomain(cm,x,whyNot,MasterObjective))
              return false;
            else
              {
                v=std::move(x);
                return true;
              }
          }
        delete m;
      }



      typedef buildByToken<T> myBuild;

      virtual buildByToken<T>* getBuildByToken(const StructureEnv_New* cm)const
      {
        return new buildByToken<T>(cm,this);
      }


      virtual const Implements_Data_Type_New<StructureEnv_New*>* getComplexVarType(const StructureEnv_New* cm) const {return CVtype_;}



      virtual ~Implements_Data_Type_class(){}

      Implements_Data_Type_class(){}
      Implements_Data_Type_class(const std::string& idType, selfType* const typeType,
                                 const std::vector<std::pair<Implements_Var,bool>> fields={}
          ,getCV getmyCV=nullptr
          ,getClass_type getClass=nullptr
          ,typePredicate complyPred=nullptr):
        typeId_(idType)
      ,varIdType_(Identifier::types::idVarUsed::varType(idType))
      ,typeIdType_(Identifier::types::idType::varType(idType))
      ,typeType_(typeType),
        comply_(complyPred),getClass_(getClass),getCV_(getmyCV),CVtype_(nullptr)
      {
        if (!fields.empty())
          CVtype_=ComplexVar::types::ClassDescript::varType(typeId(),fields);
        else
          CVtype_=ComplexVar::types::Var::varType();

      }



      virtual selfType* clone()const{return new selfType(*this);}
      virtual selfType* create()const {return new selfType{Cls<T>::name(),nullptr};}


      virtual bool empty()const
      {
        return comply_==nullptr;
      }

      virtual void reset()
      {
        comply_=nullptr;

      }




      virtual bool isOfThisType(const StructureEnv_New* cm,
                                const std::string& generalType,
                                std::string* whyNot
                                ,const std::string &masterObjective)const
      {
        if ((generalType.empty()||myTypeId()==generalType))
          return true;
        else
          {
            auto gTp
                =cm->idToTyped<T>(generalType,whyNot,masterObjective);
            std::string id=typeId();
            if ((id.empty())||(gTp==nullptr))
              return false;
            else
              return gTp->includesThisType(cm,id,whyNot,masterObjective);
          }

      }



      virtual Implements_Value_New<T>* getClassRep(
          const StructureEnv_New* cm,
          const StructureEnv_New* m
          , std::string *whyNot,
          const std::string& masterObjective) const override
      {

        bool success;
        T o=getClass(cm,m,success,whyNot,masterObjective);
        if (success)
          return new Implements_Value_New<T>
              (this,o);
        else
          return nullptr;

      }

      virtual T getClass(const StructureEnv_New* cm
                         ,const StructureEnv_New*  m
                         ,bool &success,std::string *WhyNot,const std::string& masterObjective)const
      {
        if (getClass_==nullptr)
          {
            success=false;
            return T{};

          }
        else
          return (*getClass_)(cm,m,success,this,WhyNot,masterObjective);
      }

      virtual StructureEnv_New* getComplexMap(
          const StructureEnv_New* cm,
          const T& v,std::string *WhyNot,const std::string & masterObjective)const
      {
        if (getCV_==nullptr)
          return nullptr;
        else
          return (*getCV_)(cm,v,this,WhyNot,masterObjective);

      }


      virtual StructureEnv_New* getComplexVarRep(
          const StructureEnv_New* cm,
          const ABC_Data_New *var
          , std::string *whyNot
          , const std::string& masterObjective) const override
      {
        auto v=dynamic_cast<const Implements_Value_New<T>*>(var);

        if (v==nullptr)
          {
            return nullptr;
          }
        else{

            T d=v->getValue();
            return getComplexMap(cm,d,whyNot,masterObjective);
          }
      }




      virtual ABC_Type_of_Value const* myType()const override {return typeType_;}
      virtual selfType const * myTypeD()const {return typeType_;}

      std::string typeId()const override {return typeId_;}

      std::string myTypeId()const override  {
        if (myType()==nullptr)
          return Cls<T>::name();
        else
          return myType()->typeId();
      }

      virtual const Implements_Identifier* getVarIdType(const StructureEnv_New* cm)const override
      {
        return varIdType_;
      }
      virtual const Implements_Identifier* getTypeIdType(const StructureEnv_New* cm)const override
      {
        return typeIdType_;
      }


    protected:
      std::string typeId_;
      const Implements_Identifier* varIdType_;
      const Implements_Identifier* typeIdType_;
      selfType const * typeType_;
      typePredicate comply_;
      getClass_type getClass_;
      getCV getCV_;
      const Implements_Data_Type_New<StructureEnv_New*>* CVtype_;

    };



    template<typename T>
    class Implements_Data_Type_class<T*>:public ABC_Type_of_Value
    {
    public:
      typedef Implements_Data_Type_class<T*> selfType;
      typedef T* myC;
      static std::string myId() {return Cls<myC>::name();}
      static selfType* varType(const StructureEnv_New* cm)
      {return new Implements_Data_Type_class<T*>();}
      static std::string myTip(){return "a "+ Cls<myC>::name();}
      static std::string myWhatThis(){return "";}
      typedef mp_list<> dependsOn;
      typedef mp_list<> fieldList;


      using typePredicate= bool(*)
      (const StructureEnv_New*
      ,const T*
      ,const selfType*
      , std::string*
      ,const std::string& );



      using getClass_type=T* (*)(const StructureEnv_New* cm
      ,const StructureEnv_New*  m
      ,const selfType* self
      ,std::string *WhyNot,const std::string& masterObjective);

      using getCV=StructureEnv_New* (*)(
      const StructureEnv_New* cm,
      const T* v
      ,const selfType* self,
      std::string *WhyNot,const std::string & masterObjective);



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
                                   , std::string *whyNot, const std::string& masterObjective)const
      {

        if (comply_==nullptr)
          return true;
        else
          return  (*comply_) (cm,v,this,whyNot,masterObjective);
      }


      virtual selfType* clone()const{return new selfType(*this);}
      virtual selfType* create()const {return new selfType{};}



      bool includesThisType(const StructureEnv_New *cm, const std::string &childType
                            , std::string *whyNot, const std::string &masterObjective) const override
      {
        std::string id=typeId();
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
            *error=masterObjective+ ": "+data->myTypeId()+" is not a "+Cls<T*>::name();
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
            v= new Implements_Value_New<T*>(this,data);
            return true;
          }
      }




      virtual bool putValue(const StructureEnv_New* cm
                            ,const T* c
                            ,ABC_Output* ostream
                            ,std::string* whyNot
                            , const std::string& masterObjective)const
      {
        auto v= cm->idToTyped<T*>(myClassOf(c),whyNot,masterObjective);
        if (v==nullptr)
          return false;
        else if (v==this)
          {

            StructureEnv_New* m
                =getComplexMap(cm,c,whyNot,masterObjective);
            if (m==nullptr)
              return false;
            else
              return CVtype_->putValue
                  (m,m,ostream,whyNot,masterObjective);
          }
        else return v->putValue(cm,c,ostream,whyNot,masterObjective);
      }

      virtual bool getValue(const StructureEnv_New* cm
                            ,T*& v
                            , ABC_Input* istream
                            ,std::string* whyNot
                            ,const std::string& MasterObjective )const
      {
        auto m=new StructureEnv_New(cm,CVtype_);
        if (!CVtype_->getValue(m,m,istream,whyNot,MasterObjective))
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
        delete m;
      }

      virtual const Implements_Data_Type_New<StructureEnv_New*>* getComplexVarType(const StructureEnv_New* cm) const {return CVtype_;}



      typedef buildByToken<T*> myBuild;

      virtual buildByToken<T*>*
      getBuildByToken(const StructureEnv_New* cm)const override
      {
        return new buildByToken<T*>(cm,this);
      }


      virtual ~Implements_Data_Type_class(){}


      Implements_Data_Type_class(const std::string& idType,selfType* const typeType,
                                 const std::vector<std::pair<Implements_Var,bool>> fields
                                 ,getClass_type getClass
                                 ,getCV getmyCV
                                 ,typePredicate complyPred=nullptr):
        typeId_(idType)
      ,varIdType_(Identifier::types::idVarUsed::varType(idType))
      ,typeIdType_(Identifier::types::idType::varType(idType))
      ,typeType_(typeType),
        comply_(complyPred),getClass_(getClass),getCV_(getmyCV),CVtype_(nullptr)

      {
        if (!fields.empty())
          CVtype_=ComplexVar::types::ClassDescript::varType(typeId(),fields);
        else
          CVtype_=ComplexVar::types::Var::varType();

      }


      Implements_Data_Type_class():
        typeId_(Cls<T*>::name())
      ,varIdType_(Identifier::types::idVarUsed::varType(Cls<T*>::name()))
      ,typeIdType_(Identifier::types::idType::varType(Cls<T*>::name()))
      ,typeType_(nullptr),
        comply_(nullptr),getClass_(nullptr),getCV_(nullptr),CVtype_(ComplexVar::types::Var::varType())
      {
      }
      virtual bool empty()const override
      {
        return comply_==nullptr;
      }

      virtual void reset() override
      {
        comply_=nullptr;

      }




      virtual bool isOfThisType(const StructureEnv_New* cm,
                                const std::string& generalType,
                                std::string* whyNot
                                ,const std::string &masterObjective)const override
      {
        if ((generalType.empty()||myTypeId()==generalType))
          return true;
        else
          {
            auto gTp
                =cm->idToTyped<T*>(generalType,whyNot,masterObjective);
            std::string id=typeId();
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
        T* o=getClass(cm,m,whyNot,masterObjective);
        if (o!=nullptr)
          return new Implements_Value_New<T*>
              (this,o);
        else
          return nullptr;

      }




      virtual T* getClass(const StructureEnv_New* cm
                          ,const StructureEnv_New*  m
                          ,std::string *WhyNot,const std::string& masterObjective)const
      {
        if (getClass_==nullptr)
          return nullptr;
        else
          return (*getClass_)(cm,m,this,WhyNot,masterObjective);
      }

      virtual StructureEnv_New* getComplexMap(
          const StructureEnv_New* cm,
          const T* v,std::string *WhyNot,const std::string & masterObjective)const
      {
        if (getCV_==nullptr)
          return nullptr;
        else
          return (*getCV_)(cm,v,this,WhyNot,masterObjective);

      }


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

      virtual ABC_Type_of_Value const* myType()const override {return typeType_;}
      virtual selfType const * myTypeD()const {return typeType_;}

      std::string typeId()const override {return typeId_;}

      std::string myTypeId()const override  {
        if (myType()==nullptr)
          return Cls<T*>::name();
        else
          return myType()->typeId();
      }
      virtual const Implements_Identifier* getVarIdType(const StructureEnv_New* cm)const override
      {
        return varIdType_;
      }
      virtual const Implements_Identifier* getTypeIdType(const StructureEnv_New* cm)const override
      {
        return typeIdType_;
      }



    protected:
      std::string typeId_;
      const Implements_Identifier* varIdType_;
      const Implements_Identifier* typeIdType_;
      selfType const * typeType_;
      typePredicate comply_;
      getClass_type getClass_;
      getCV getCV_;
      const Implements_Data_Type_New<StructureEnv_New*>* CVtype_;

    };





    template<class D, class B>
    class Implements_Data_Type_derived_class:public Implements_Data_Type_class<B*>
    {


    public:
      typedef  Implements_Data_Type_class<B*> baseType;
      typedef Implements_Data_Type_derived_class<D,B> selfType;



      typedef D* myC;
      static std::string myId() {return Cls<myC>::name();}
      static selfType* varType(const StructureEnv_New* cm)
      {return new selfType{};}
      static std::string myTip(){return "a "+Cls<myC>::name()+" a kind of "+
            baseType::myTip();}
      static std::string myWhatThis(){return "";}
      typedef mp_list<baseType> dependsOn;
      typedef mp_list<> fieldList;


      using derivedPredicate= bool(*)
      (const StructureEnv_New*
      ,const D*
      ,const selfType*
      , std::string*
      ,const std::string& );

      using getDClass_type=D* (*)(const StructureEnv_New* cm
      ,const StructureEnv_New*  m
      ,const selfType* self
      ,std::string *WhyNot,const std::string& masterObjective);

      using getDCV=StructureEnv_New* (*)(
      const StructureEnv_New* cm,
      const D* v
      ,const selfType* self,
      std::string *WhyNot,const std::string & masterObjective);



      virtual bool isDataInDomain
      (const StructureEnv_New* cm
       ,const ABC_Data_New* v
       , std::string *whyNot
       , const std::string& masterObjective)const override
      {
        const std::string objective=masterObjective+": do not has it in domain";
        auto x=dynamic_cast<const Implements_Value_New<D*>* >(v);
        if (x==nullptr)
          {
            return baseType::isDataInDomain(cm,v,whyNot,masterObjective);
          }
        else
          return isValueInDomain(cm,x->getValue(),whyNot,objective);
      }

      virtual bool isValueInDomain(const StructureEnv_New* cm,const B* v
                                   , std::string *whyNot, const std::string& masterObjective)const override
      {
        const std::string objective=masterObjective+": do not has it in domain";
        auto x=dynamic_cast<const D*>(v);
        if (x==nullptr)
          {
            return baseType::isValueInDomain(cm,v,whyNot,masterObjective);
          }
        else
          return isValueInDomain(cm,x,whyNot,objective);

      }


      virtual bool isValueInDomain(const StructureEnv_New* cm,const D* v
                                   , std::string *whyNot, const std::string& masterObjective)const
      {

        if (complyD_==nullptr)
          return true;
        else
          return  (*complyD_) (cm,v,this,whyNot,masterObjective);
      }


      bool includesThisType(const StructureEnv_New *cm, const std::string &childType
                            , std::string *whyNot, const std::string &masterObjective) const
      {
        std::string id=typeId();
        if (id==childType) return true;
        else
          {
            const Implements_Data_Type_New<D*>*
                ctype=cm->idToTyped<D*>(childType,whyNot,masterObjective);
            if (ctype==nullptr)
              {
                return baseType::includesThisType
                    (cm,childType,whyNot,masterObjective);
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
        auto data=dynamic_cast<const Implements_Value_New<D*>* >(v);
        if (data==nullptr)
          {
            std::string Objective= masterObjective+ ": is not a "+Cls<D*>::name();
            return baseType::putData(cm,v,ostream,error,Objective);
          }
        else return putValue(cm,data->getValue(),ostream,error,masterObjective);
      }

      virtual bool getData(const StructureEnv_New* cm
                           ,ABC_Data_New*& v
                           , ABC_Input* istream
                           ,std::string* error
                           , const std::string& masterObjective)const override
      {
        D* data;
        if (!getValue(cm,data,istream,error,masterObjective))
          return baseType::getData(cm,v,istream,error,masterObjective);
        else
          {
            v= new Implements_Value_New<D*>(this,data);
            return true;
          }
      }




      virtual bool putValue(const StructureEnv_New* cm
                            ,const D* c
                            ,ABC_Output* ostream
                            ,std::string* whyNot
                            , const std::string& masterObjective)const
      {
        auto v= cm->idToTyped<D*>(myClassOf(c),whyNot,masterObjective);
        if (v==nullptr)
          return false;
        else
          {
            if (v==this)
              {
                StructureEnv_New* m
                    =getComplexMap(cm,c,whyNot,masterObjective);
                if (m==nullptr)
                  return false;
                else
                  return this->CVtype_->putValue
                      (m,m,ostream,whyNot,masterObjective);
              }
            else return v->putValue(cm,c,ostream,whyNot,masterObjective);
          }
      }

      virtual bool getValue(const StructureEnv_New* cm
                            ,D*& v
                            , ABC_Input* istream
                            ,std::string* whyNot
                            ,const std::string& MasterObjective )const
      {

        auto m=new StructureEnv_New(cm,this->CVtype_);
        if (!this->CVtype_->getValue(m,m,istream,whyNot,MasterObjective))
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
        delete m;
      }


       typedef buildByTokenD<D,B> myBuild;

      virtual buildByTokenD<D,B>* getBuildByToken(const StructureEnv_New* cm)const
      {
        return new buildByTokenD<D,B>(cm,this);
      }


      virtual ~Implements_Data_Type_derived_class(){}


      Implements_Data_Type_derived_class
      (const std::string& idType,selfType* const typeType,

       const std::vector<std::pair<Implements_Var,bool>> fields
       ,getDCV  getDerivedCV
       , getDClass_type getDerClass
       , derivedPredicate comply=nullptr
          ,typename baseType::getCV getBaseCV=nullptr
          ,typename baseType::getClass_type getBClass=nullptr
          ,typename baseType::typePredicate baseComply=nullptr):
        baseType(idType,typeType,fields,getBClass,getBaseCV,baseComply)
      ,typeId_(idType)
      ,typeType_(typeType)
      ,getDClass_(getDerClass),getDCV_(getDerivedCV),
        complyD_(comply)
      {
      }

      Implements_Data_Type_derived_class
      ():
        baseType()
      ,getDClass_(nullptr),getDCV_(nullptr),
        complyD_(nullptr)
      {
      }


      virtual bool empty()const
      {
        return baseType::empty()&&getDClass_==nullptr
            &&complyD_==nullptr&& getDCV_==nullptr;
      }

      virtual void reset()
      {
        complyD_=nullptr;

      }





      virtual bool isOfThisType(const StructureEnv_New* cm,
                                const std::string& generalType,
                                std::string* whyNot
                                ,const std::string &masterObjective)const
      {
        if ((generalType.empty()||myTypeId()==generalType))
          return true;
        else
          {
            auto gTp
                =cm->idToTyped<D*>(generalType,whyNot,masterObjective);
            std::string id=typeId();
            if ((id.empty())||(gTp==nullptr))
              return false;
            else
              return gTp->includesThisType(cm,id,whyNot,masterObjective);
          }

      }



      virtual Implements_Value_New<D*>* getClassRep(
          const StructureEnv_New* cm,
          const StructureEnv_New* m
          , std::string *whyNot,
          const std::string& masterObjective) const override
      {

        D* o=getClass(cm,m,whyNot,masterObjective);
        if (o!=nullptr)
          return new Implements_Value_New<D*>
              (this,o);
        else
          return nullptr;

      }

      virtual D* getClass(const StructureEnv_New* cm
                          ,const StructureEnv_New*  m
                          ,std::string *WhyNot,const std::string& masterObjective)const
      {
        if (getDClass_==nullptr)
          return nullptr;
        else return (*getDClass_)(cm,m,this,WhyNot,masterObjective);

      }

      virtual StructureEnv_New* getComplexMap(
          const StructureEnv_New* cm,
          const D* v,std::string *WhyNot,const std::string & masterObjective)const
      {
        if (getDCV_==nullptr)
          return nullptr;
        else
          return (*getDCV_)(cm,v,this,WhyNot,masterObjective);
      }

      virtual StructureEnv_New* getComplexMap(
          const StructureEnv_New* cm,
          const B* v,std::string *WhyNot,const std::string & masterObjective)const override
      {
        const D* d=dynamic_cast<const D*>(v);
        if (d==nullptr)
          return baseType::getComplexMap(cm,v,WhyNot,masterObjective);
        else
          return getComplexMap(cm,d,WhyNot,masterObjective);
      }




      virtual StructureEnv_New* getComplexVarRep(
          const StructureEnv_New* cm,
          const ABC_Data_New *var
          , std::string *whyNot
          , const std::string& masterObjective) const override
      {

        const D* d;
        auto v=dynamic_cast<const Implements_Value_New<D*>*>(var);

        if (v==nullptr)
          {
            auto b=dynamic_cast<const Implements_Value_New<B*>*>(var);
            if (b==nullptr)
              return baseType::getComplexVarRep(cm,var,whyNot,masterObjective);
            else
              {
                const B* bb=b->getValue();
                d=dynamic_cast<const D*>(bb);
                if (d==nullptr)
                  return baseType::getComplexMap(cm,bb,whyNot,masterObjective);
                else
                  return getComplexMap(cm,d,whyNot,masterObjective);
              }

          }

        else
          {
            d=v->getValue();
            return getComplexMap(cm,d,whyNot,masterObjective);
          }

      }
    public:
      virtual selfType *clone() const override
      {
        return new selfType(*this);
      }
      virtual selfType *create() const override
      {
        return new selfType();
      }


      virtual ABC_Type_of_Value const* myType()const override {return typeType_;}
      virtual selfType const * myTypeD()const {return typeType_;}

      std::string typeId()const override {return typeId_;}

      std::string myTypeId()const override  {
        if (myType()==nullptr)
          return Cls<D*>::name();
        else
          return myType()->typeId();
      }




    protected:
      std::string typeId_;
      selfType const * typeType_;
      derivedPredicate complyD_;
      getDClass_type getDClass_;
      getDCV  getDCV_;
      // ABC_Data_New interface
    };

    template<class Field,class C>
    typename Field::myC getMyField(const C* x);

    template<class Field,class C>
    bool isFieldMandatory();

    //------------------------------------------------------------------------------------


    template <class myType,typename ... Args>
    typename myType::myD map2obj_Impl(const mp_list<>&,
                                      const StructureEnv_New* cm,
                                      const StructureEnv_New* m
                                      ,bool& success
                                      ,const Implements_Data_Type_New<typename myType::myD>* v
                                      ,std::string* WhyNot,
                                      const std::string& masterObjective
                                      ,Args ... restArg)
    {
      success=true;

      return typename myType::myD
          (restArg...);

    }




    template <class myType,typename NextField,typename... Field,typename ... Args>
    typename myType::myD map2obj_Impl(const mp_list<NextField,Field...>&,
                                      const StructureEnv_New* cm,
                                      const StructureEnv_New* m
                                      ,bool &success
                                      ,const Implements_Data_Type_New<typename myType::myD>* v
                                      ,std::string* WhyNot,
                                      const std::string& masterObjective
                                      ,Args ... restArg)
    {

      typename NextField::myC nextArg;
      if (!m->getDataValue<NextField>
          ( nextArg,WhyNot,masterObjective))
        {
          success=false;
          return {};
        }
      else return map2obj_Impl
          <myType>
          (mp_list<Field...>{}
           ,cm,m,success,v,WhyNot,masterObjective,restArg...,nextArg);

    }







    template <class myType,typename FirstField,typename... Field>
    typename myType::myD map2objTempl(const StructureEnv_New* cm,
                                      const StructureEnv_New* m
                                      ,bool &success
                                      ,const Implements_Data_Type_New<typename myType::myD>* v
                                      ,std::string* WhyNot,
                                      const std::string& masterObjective,
                                      const mp_list<FirstField,Field...>&)
    {
      typename FirstField::myC firstArg;

      if (!m->getDataValue<FirstField>
          (firstArg,WhyNot,masterObjective))
        {
          success=false;
          return {};
        }
      else
        return map2obj_Impl<myType>
            (mp_list<Field...>{},
             cm,m,success,v,WhyNot,masterObjective,firstArg);
    }












    //-------------------------------------------------------------------------------------






    template <class myType,typename ... Args>
    typename myType::myD* map2objPtr_Impl(const mp_list<>&,
                                          const StructureEnv_New* cm,
                                          const StructureEnv_New* m
                                          ,const Implements_Data_Type_New<typename myType::myD*>* v
                                          ,std::string* WhyNot,
                                          const std::string& masterObjective
                                          ,Args ... restArg)
    {

      return new typename myType::myD
          (restArg...);

    }




    template <class myType,typename NextField,typename... Field,typename ... Args>
    typename myType::myD* map2objPtr_Impl(const mp_list<NextField,Field...>&,
                                          const StructureEnv_New* cm,
                                          const StructureEnv_New* m
                                          ,const Implements_Data_Type_New<typename myType::myD*>* v
                                          ,std::string* WhyNot,
                                          const std::string& masterObjective
                                          ,Args ... restArg)
    {

      typename NextField::myC nextArg;
      if (!m->getDataValue<NextField>
          ( nextArg,WhyNot,masterObjective))
        return nullptr;
      else return map2objPtr_Impl
          <myType>
          (mp_list<Field...>{}
           ,cm,m,v,WhyNot,masterObjective,restArg...,nextArg);

    }







    template <class myType,typename FirstField,typename... Field>
    typename myType::myD* map2objPtrTempl(const StructureEnv_New* cm,
                                          const StructureEnv_New* m
                                          ,const Implements_Data_Type_New<typename myType::myD*>* v
                                          ,std::string* WhyNot,
                                          const std::string& masterObjective,
                                          const mp_list<FirstField,Field...>&)
    {
      typename FirstField::myC firstArg;

      if (!m->getDataValue<FirstField>
          (firstArg,WhyNot,masterObjective))
        return nullptr;
      else
        return map2objPtr_Impl<myType>
            (mp_list<Field...>{},
             cm,m,v,WhyNot,masterObjective,firstArg);
    }


    //-------------------------------------------------------------------------------

    template <class myType>
    StructureEnv_New* obj2map_Imp
    (const StructureEnv_New* cm,
     const typename myType::myD& x
     ,const Implements_Data_Type_New<typename myType::myD>* v
     , std::string* WhyNot,
     const std::string& masterObjective,StructureEnv_New* f)
    {
      return f;
    }



    template <class myType,typename FirstField,typename... Field>
    StructureEnv_New* obj2map_Imp
    (const StructureEnv_New* cm,
     const typename myType::myD& x
     ,const Implements_Data_Type_New<typename myType::myD>* v
     , std::string* WhyNot,
     const std::string& masterObjective,StructureEnv_New* f)
    {

      f->pushVar< FirstField>(myType::template get<FirstField>(&x));
      return obj2map_Imp<myType,Field...>(cm,x,v,WhyNot,masterObjective,f);

    }


    template <class myType,typename FirstField,typename... Field>
    StructureEnv_New* obj2mapTempl
    (const StructureEnv_New* cm,
     const typename myType::myD& x
     ,const Implements_Data_Type_New<typename myType::myD>* v
     , std::string* WhyNot, const std::string& masterObjective,
     const mp_list<FirstField,Field...>&)
    {
      auto f=new StructureEnv_New(cm,Cls<typename myType::myD>::name());
      f->pushVar< FirstField>(myType::template get<FirstField>(&x));
      return obj2map_Imp<myType,Field...>(cm,x,v,WhyNot,masterObjective,f);
    }

    //-----------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------

    template <class myType>
    StructureEnv_New* objPtr2map_Imp
    (const StructureEnv_New* cm,
     const typename myType::myD* x
     ,const Implements_Data_Type_New<typename myType::myD*>* v
     , std::string* WhyNot,
     const std::string& masterObjective,StructureEnv_New* f)
    {
      return f;
    }



    template <class myType,typename FirstField,typename... Field>
    StructureEnv_New* objPtr2map_Imp
    (const StructureEnv_New* cm,
     const typename myType::myD* x
     ,const Implements_Data_Type_New<typename myType::myD*>* v
     , std::string* WhyNot,
     const std::string& masterObjective,StructureEnv_New* f)
    {

      f->pushVar< FirstField>(myType::template get<FirstField>(x));
      return objPtr2map_Imp<myType,Field...>(cm,x,v,WhyNot,masterObjective,f);

    }


    template <class myType,typename FirstField,typename... Field>
    StructureEnv_New* objPtr2mapTempl
    (const StructureEnv_New* cm,
     const typename myType::myD* x
     ,const Implements_Data_Type_New<typename myType::myD*>* v
     , std::string* WhyNot, const std::string& masterObjective,
     const mp_list<FirstField,Field...>&)
    {
      auto f=new StructureEnv_New(cm,Cls<typename myType::myD*>::name());
      f->pushVar< FirstField>(myType::template get<FirstField>(x));
      return objPtr2map_Imp<myType,Field...>(cm,x,v,WhyNot,masterObjective,f);
    }

    //-----------------------------------------------------------------------------------------

    template <typename myType>
    std::vector<std::pair<Implements_Var,bool>> getFields_Imp(const StructureEnv_New* cm,std::vector<std::pair<Implements_Var,bool>>& f)
    {
      return f;
    }


    template <typename myType,typename FirstField,typename... Field>
    std::vector<std::pair<Implements_Var,bool>> getFields_Imp(const StructureEnv_New* cm,std::vector<std::pair<Implements_Var,bool>>& f)
    {
      f.push_back({getMyVar<FirstField>(cm), myType::template isMandatory<FirstField>()});
      return getFields_Imp<myType,Field...>(cm,f);
    }



    template <typename myType,typename FirstField,typename... Field>
    std::vector<std::pair<Implements_Var,bool>> getFieldsTempl
    (const StructureEnv_New* cm,const mp_list<FirstField,Field...>&)
    {
      std::vector<std::pair<Implements_Var,bool>> f;
      f.push_back({getMyVar<FirstField>(cm),myType::template isMandatory<FirstField>()});
      return getFields_Imp<myType,Field...>(cm,f);
    }

    //-----------------------------------------------------------------------------



    template <typename myType,typename... Field>
    void push_TypesList(StructureEnv_New *cm, const mp_list<Field...>&);

    template <typename myType,typename... Field>
    void push_FieldList(StructureEnv_New *cm, const mp_list<Field...>&);

    template<typename myType>
    void push_Types_Type_impl(StructureEnv_New *cm)
    {
      push_TypesList<myType>(cm,typename myType::dependsOn{});
      push_FieldList<myType>(cm,typename myType::fieldList{});
      if (!cm->hasType(myType::myId()))
        cm->pushType<typename myType::myC>
            (myType::myId()
             ,myType::varType(cm)
             ,myType::myTip(),myType::myWhatThis());

    }





    template<typename myField>
    void push_Types_Field_impl(StructureEnv_New *cm)
    {
      push_Types_Type_impl<typename myField::vType>(cm);
    }



    template <typename myType>
    void push_FieldList(StructureEnv_New *cm)
    {
    }


    template <typename myType,typename FirstField,typename... Field>
    void push_FieldList(StructureEnv_New *cm)
    {
      push_Types_Field_impl<FirstField>(cm);
      push_FieldList<myType,Field...>(cm);
    }

    template <typename myType>
    void push_TypesList(StructureEnv_New *cm)
    {
    }


    template <typename myType,typename FirstField,typename... Field>
    void push_TypesList(StructureEnv_New *cm)
    {
      push_Types_Type_impl<FirstField>(cm);
      push_TypesList<myType,Field...>(cm);
    }


    template <typename myType,typename... Field>
    void push_TypesList(StructureEnv_New *cm, const mp_list<Field...>&)
    {
      push_TypesList<myType,Field...>(cm);
    }

    template <typename myType,typename... Field>
    void push_FieldList(StructureEnv_New *cm, const mp_list<Field...>&)
    {
      push_FieldList<myType,Field...>(cm);
    }



    template <typename myType>
    void push_MyTypes(StructureEnv_New *cm)
    {
      push_Types_Type_impl<myType>(cm);
    }

    //----------------------------------------------------------------------------









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


    typedef buildByToken<T*> myBuild;


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

      auto o=(*toObj_)(cm,this,whyNot);
      if (o!=nullptr)
        return Implements_Value_New<T*>
            (this,o);
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


  namespace _private {



    template<typename Markov_CommandManagerVar>
    class Implements_Data_Type_singleton:public ABC_Type_of_Value
    {
    public:
      typedef Implements_Data_Type_singleton selfType;
      typedef Markov_CommandManagerVar* myC;
      static std::string myId() {return Cls<myC>::name();}
      static selfType* varType(const StructureEnv_New* cm)
      {return new Implements_Data_Type_singleton();}
      static std::string myTip(){return "a "+ Cls<myC>::name();}
      static std::string myWhatThis(){return "";}
      typedef mp_list<> dependsOn;
      typedef mp_list<> fieldList;


      virtual bool isDataInDomain
      (const StructureEnv_New* cm
       ,const ABC_Data_New* v
       , std::string *whyNot
       , const std::string& masterObjective)const override
      {
        return cm==v;
      }

      virtual bool isValueInDomain(const StructureEnv_New* cm,const Markov_CommandManagerVar* v
                                   , std::string *whyNot, const std::string& masterObjective)const
      {

        return  cm==v;
      }


      virtual selfType* clone()const{return new selfType(*this);}
      virtual selfType* create()const {return new selfType{};}



      bool includesThisType(const StructureEnv_New *cm, const std::string &childType
                            , std::string *whyNot, const std::string &masterObjective) const override
      {
        return childType==myId();
      }



      virtual bool putData(const StructureEnv_New* cm
                           ,const ABC_Data_New* v
                           ,ABC_Output* ostream
                           ,std::string* error,
                           const std::string& masterObjective)const override
      {
        if (cm!=v)
          {
            *error=masterObjective+ ": "+v->myTypeId()+" is not a "+Cls<Markov_CommandManagerVar*>::name();
            return false;
          }
        else return true;
      }

      virtual bool getData(const StructureEnv_New* cm
                           ,ABC_Data_New*& v
                           , ABC_Input* istream
                           ,std::string* error
                           , const std::string& masterObjective)const override
      {
        return false;
      }




      virtual bool putValue(const StructureEnv_New* cm
                            ,const Markov_CommandManagerVar* c
                            ,ABC_Output* ostream
                            ,std::string* whyNot
                            , const std::string& masterObjective)const
      {
        return false;
      }


     bool getValue(const StructureEnv_New* cm
                   ,Markov_CommandManagerVar*& c
                   ,ABC_Input* istream
                   ,std::string* whyNot
                   , const std::string& masterObjective) const
     {
        return false;
      }
      virtual const ABC_Type_of_Value* getComplexVarType(const StructureEnv_New* cm) const {return nullptr;}



      typedef buildByToken<Markov_CommandManagerVar*> myBuild;

      virtual buildByToken<Markov_CommandManagerVar*>*
      getBuildByToken(const StructureEnv_New* cm)const override
      {
        return new buildByToken<Markov_CommandManagerVar*>(cm,this);
      }


      virtual ~Implements_Data_Type_singleton(){}


      Implements_Data_Type_singleton(){}

      virtual bool empty()const override
      {
        return false;
      }

      virtual void reset() override
      {

      }




      virtual bool isOfThisType(const StructureEnv_New* cm,
                                const std::string& generalType,
                                std::string* whyNot
                                ,const std::string &masterObjective)const override
      {
        if ((generalType.empty()||myTypeId()==generalType))
          return true;
        else
          {
            return false;
          }

      }



      virtual ABC_Data_New* getClassRep(
          const StructureEnv_New* cm,
          const StructureEnv_New* m
          , std::string *whyNot,
          const std::string& masterObjective) const override
      {
        return nullptr;

      }





      virtual StructureEnv_New* getComplexVarRep(
          const StructureEnv_New* cm,
          const ABC_Data_New *var
          , std::string *whyNot
          , const std::string& masterObjective) const override
      {

        return nullptr;
      }

      virtual ABC_Type_of_Value const* myType()const override {return nullptr;}

      std::string typeId()const override {
        return Cls<Markov_CommandManagerVar*>::name();}

      std::string myTypeId()const override  {
        return typeId();
      }

      virtual const Implements_Identifier* getVarIdType(const StructureEnv_New* cm)const override
      {
        return nullptr;
      }
      virtual const Implements_Identifier* getTypeIdType(const StructureEnv_New* cm)const override
      {
        return nullptr;
      }




    };







  }


  class Implements_Command_Arguments: public StructureEnv_New
  {
  public:

    virtual ~Implements_Command_Arguments(){}

    Implements_Command_Arguments(const StructureEnv_New* parent,
                                 const Implements_Data_Type_New<StructureEnv_New*> *var
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
    (const std::string& id,Implements_Command_Type_New const * typeType,
     std::vector<std::pair<Implements_Var,bool>> argList
     ,runCommand run_,
     const Implements_Data_Type_New<Implements_Var>* elemeType,
     typePredicate comply,
     typePredicate hasMandatory,
     typePredicate hasAll,
     elementType elem):
      _private::Implements_Data_Type_New_StructureEnv
      (id,typeType,argList,elemeType,comply,hasMandatory,hasAll,elem)
    ,idCmd_(id),
      run_(run_)
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
    typedef build_Command_Input myBuild;
    virtual build_Command_Input *getBuildByToken(const StructureEnv_New *cm) const override
    {
      return new build_Command_Input(cm,this);

    }


  protected:
    std::string idCmd_;
    runCommand run_;




    // ABC_Data_New interface
  public:
    virtual std::__cxx11::string myTypeId() const override
    {
      return "command";
    }

    std::string typeId() const override
    {
      return idCmd_;
    }

    // Implements_Base_Type_New<T *> interface
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
    { std::string id=typeId();
      if (childType==id)
        return true;
      else
        {
          auto ctype=cm->idToTyped<T>(childType,whyNot,masterObjective);
          if (ctype==nullptr)
            return false;
          else if ((ctype->myTypeId()==id)||(empty()))
            {
              return true;
            }
          else
            return false;
        }
    }

    template<typename T>
    bool Implements_Base_Type_New<T*>::includesThisType(const StructureEnv_New *cm, const std::string &childType, std::string *whyNot, const std::string &masterObjective) const

    { std::string id=typeId();
      if (childType==id)
        return true;
      else
        {
          auto ctype=cm->idToTyped<T*>(childType,whyNot,masterObjective);
          if (ctype==nullptr)
            return false;
          else if ((ctype->myTypeId()==id)||(empty()))
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
