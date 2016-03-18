#ifndef IMPLEMENTS_COMPLEXVAR_NEW_H
#define IMPLEMENTS_COMPLEXVAR_NEW_H

#include "Markov_IO/Var.h"
#include "Markov_IO/buildByToken.h"

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




    virtual ~ABC_Output(){}
  };

  class ABC_Input
  {
  public:

    virtual  bool get( std::string& s,std::string* whyNot,const std::string& masterObjective)=0;
    virtual  bool get(double& x,std::string* whyNot,const std::string& masterObjective)=0;
    virtual  bool get(int& n,std::string* whyNot,const std::string& masterObjective)=0;
    virtual  bool get(std::size_t& n,std::string* whyNot,const std::string& masterObjective)=0;
    virtual  bool get(char& c,std::string* whyNot,const std::string& masterObjective)=0;

    template<typename T>
    bool get(T& x, std::string *whynot, const std::string& masterObjective)
    {
      *whynot=masterObjective+": "+Cls<T>::name()+" not supported. ";
    }

    virtual ~ABC_Input(){}
  };


  class Implements_Command_Type_New;

  template<typename T>
  class ABC_Typed_Value;

  template<typename T>
  class buildByToken;

  class Implements_ComplexVar_New: public Implements_Var_New<std::map<std::string,ABC_Var_New*>>
  {
  public:
    class F
    {
    public:
      static std::string belongingType()
      {
        return "belongingType";
      }

      static std::string elementType(){return "elementType";}

      static std::string keyType(){return "keyType";}

      static std::string fieldName(){return "fieldName";}


    };



    class G
    {
    public:
      static std::string gettypeOfId(const Implements_ComplexVar_New* self)
      {
        std::string belongType;
        std::string whyNot;
        if (self->getValueFromId(F::belongingType(),belongType,&whyNot,""))
          return belongType;
        else
          {
            return "";
          }

      }
      static void pushTypeOfId(Implements_ComplexVar_New* self,
                               std::string belongType);


      static std::string getIdTypeOfElement(const Implements_ComplexVar_New* self)
      {
        std::string elementType;
        std::string whyNot;
        if (self->getValueFromId(F::elementType(),elementType,&whyNot,""))
          return elementType;
        else
          {
            return "";
          }

      }

      static void pushTypeOfElement(Implements_ComplexVar_New* self,
                                    std::string typeOfElement);


      static std::string getFieldId(const Implements_ComplexVar_New* self)
      {
        std::string fdId;
        std::string whyNot;
        if (self->getValueFromId(F::fieldName(),fdId,&whyNot,""))
          return fdId;
        else
          {
            return "";
          }

      }
      static void pushFieldName(Implements_ComplexVar_New* self,
                                std::string fdId);



      template<typename T>
      static const Implements_Data_Type_New<T>* getElementType(const Implements_ComplexVar_New* cm, const Implements_ComplexVar_New* self)
      {
        std::string eletype=getIdTypeOfElement(self);
        if (!eletype.empty())
          {
            std::string whynot;
            return cm->idToTyped<T>(eletype,&whynot,"");
          }
        else return nullptr;

      }

      template<typename T>
      static buildByToken<T> *getElementBuildByToken(const Implements_ComplexVar_New *cm, const Implements_ComplexVar_New *self);


      static std::string getIdTypeOfKey(const Implements_ComplexVar_New* self)
      {
        std::string keyType;
        std::string whyNot;
        if (self->getValueFromId(F::keyType(),keyType,&whyNot,""))
          return keyType;
        else
          {
            return "";
          }

      }

      static void pushTypeOfKey(Implements_ComplexVar_New* self,
                                std::string typeOfKey);


      template<typename T>
      static const Implements_Data_Type_New<T>* getKeyType(const Implements_ComplexVar_New* cm, const Implements_ComplexVar_New* self)
      {
        std::string keytype=getIdTypeOfKey(self);
        if (!keytype.empty())
          {
            std::string whynot;
            return cm->idToTyped<T>(keytype,&whynot,"");
          }
        else return nullptr;

      }





      template<typename T>
      static buildByToken<T> *getKeyBuildByToken(const Implements_ComplexVar_New *cm, const Implements_ComplexVar_New *self);




    };

    static std::string ClassName()
    {
      return "Implements_ComplexVar_New";
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    const ABC_Var_New* idToVar(const std::string& name, std::string *whyNot)const
    {
      auto it=vars_->find(name);
      if (it!=vars_->end())
        return it->second;
      else if (parent()!=nullptr)
        return  parent()->idToVar(name, whyNot);
      else
        {
          *whyNot=name+" is not a var of "+id();
          return nullptr;
        }
    }

    ABC_Var_New* idToVar(const std::string& name, std::string* whyNot, const std::string & masterObective)
    {
      auto it=vars_->find(name);
      if (it!=vars_->end())
        return it->second;
      else
        {
          *whyNot=masterObective+": "+name+" is not a var of "+id();
          return nullptr;
        }
    }

    virtual const ABC_Type_of_Value* idToType(const std::string& name, std::string *whyNot, const std::string& masterObjective)const
    {
      auto it=types_->find(name);
      if (it!=types_->end())
        return it->second;
      else if (parent()!=nullptr)
        return  parent()->idToType(name,whyNot,masterObjective);
      else
        {
          *whyNot=masterObjective+": "+name+" is not a type of "+id();
          return nullptr;
        }

    }

    virtual ABC_Type_of_Value* idToType(const std::string& name, std::string *whyNot,const std::string& masterObjective)
    {
      const std::string objective=masterObjective+": "+name+" is not a type of "+id();
      auto it=types_->find(name);
      if (it!=types_->end())
        return it->second;
      else
        {
          *whyNot=objective;
          return nullptr;
        }

    }


    const Implements_Command_Type_New* idToCommand(const std::string& name, std::string *whyNot)const
    {
      auto it=cmds_->find(name);
      if (it!=cmds_->end())
        return it->second;
      else if (this->parent()!=nullptr)
        return  parent()->idToCommand(name, whyNot);
      else
        {
          *whyNot=name+" is not a command of "+id();
          return nullptr;
        }
    }



    template<typename T>
    const Implements_Data_Type_New<T>* idToTyped(
        const std::string& name
        , std::string *whyNot
        , const std::string& masterObjective)const
    {
      const std::string objective
          =masterObjective
          +": "+name+ "is not a "+ ABC_Typed_Value<T>::ClassName()+" in "+ id()+" namespece";
      auto it=types_->find(name);
      if (it!=types_->end())
        {
          return dynamicCast<Implements_Data_Type_New<T>*>(
                it->second,whyNot,objective);
        }
      else if (parent()!=nullptr)
        return  parent()->idToTyped<T>(name, whyNot,objective);
      else
        {
          *whyNot=objective+": name not found in type list";
        }

    }


    template<typename T>
    bool getValueFromId(const std::string& name
                        , T& value
                        ,std::string* whyNot, const std::string& masterObjective)const
    {

      std::string objective;
      if (whyNot!=nullptr)
        objective=masterObjective+": "+ name+" is not a "+Cls<T>::name();

      auto it=vars_->find(name);
      if (it!=vars_->end())
        {
          auto v=dynamicCast<const Implements_Value_New<T>*>(it->second,whyNot,objective);
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
              value=v->getValued();
              return true;
            }
        }

      else if (parent()!=nullptr)
        return  parent()->getValueFromId(name,value,whyNot,objective);
      else
        {
          *whyNot=objective+": "+id()+" does not have it and it has no parent";
          return false;
        }
    }


    bool hasName(const std::string& name
                 , std::string* whyNot
                 ,const std::string &masterObjective)const
    {
      const std::string objective=masterObjective+ ": "+name+"is not in "+id();
      if (vars_->find(name)!=vars_->end())
        {
          return true;
        }
      if (parent()==nullptr)
        {
          *whyNot=objective;
          return false;
        }
      else return parent()->hasName(name, whyNot,objective);
    }

    bool hasNameofType(const std::string& name, const std::string& type,
                       std::string* whyNot
                       ,const std::string &masterObjective)const;


    bool isNameUnOcuppied(const std::string& name,std::string* whyNot,const std::string masterObjective)const
    {
      auto it=vars_->find(name);
      if (it!=vars_->end())
        {
          const ABC_Var_New* v=it->second;
          *whyNot=masterObjective+": "+name+" is currently a"+v->myType()+" in "+id();
        }
      else if (parent()!=nullptr)
        return parent()->isNameUnOcuppied(name,whyNot,masterObjective);
      else
        return true;
    }


    bool hasCommand(const std::string& name)const
    {if (cmds_->find(name)!=cmds_->end())
        {
          return true;
        }
      if (parent()==nullptr)
        return false;
      else return parent()->hasCommand(name);
    }

    template <typename T>
    bool insertChild(const std::string& idN,
                     const std::string& var,
                     T* value,
                     const std::string& tip
                     ,const std::string& whatthis
                     ,std::string *whyNot
                     , const std::string& masterObjective)
    {
      const std::string objective=masterObjective+": "+id()+"cannot insert"+idN;
      if (isNameUnOcuppied(idN,whyNot,objective))
        {
          auto v=idToTyped<T>(var,whyNot,objective);
          if (v==nullptr)
            return false;
          else
            {
              if (!v->isInDomain(value,whyNot))
                return false;
              else
                {
                  pushChild(new Implements_Var_New(this,{idN,var,value,tip,whatthis}));
                  return true;
                }}
        }
      else
        return false;

    }



    bool insertChild(const std::string& id,
                     const std::string& var,
                     const std::string& tip
                     , const std::string& whatthis
                     , std::string *whyNot, const std::__cxx11::string &masterObjective);





    bool removeChild(const std::string& name)
    {
      auto it =vars_->find(name);
      if (it!=vars_->end())
        {
          delete it->second;
          vars_->erase(it);
          return true;
        }
      else
        return false;
    }

    void pushChild(ABC_Var_New* var)
    {
      (*vars_)[var->id()]=var;
    }



    void pushType(ABC_Type_of_Value* varT);
    void pushCommand(Implements_Command_Type_New* cmd);




    Implements_ComplexVar_New(const Implements_ComplexVar_New* parent,
                              const std::string& id
                              ,const std::string& var
                              ,const std::string& tip
                              ,const std::string& whatthis):
      Implements_Var_New(parent,
                         id,var,tip,whatthis)
    {

      vars_=&(this->value()->getValued());
    }


    bool pushChilds(const std::vector<Var_id>& ids, std::string *whyNot, const std::string& masterObjective)
    {
      for (const Var_id& e:ids)
        {
          if (!insertChild(e.idName,e.var,e.tip,e.whathis,whyNot,masterObjective))
            return false;
        }
      return true;
    }


    std::set<std::string> getIdsOfType(const std::string& varType)const;





    // Implements_Value_New interface

  private:
    std::map<std::string,ABC_Var_New*>* vars_;
    std::map<std::string,ABC_Type_of_Value*>* types_;
    std::map<std::string,Implements_Command_Type_New*>* cmds_;



  };



  class Implements_Command_Fields: public Implements_ComplexVar_New
  {


  };


  class ABC_BuildByToken;

  class ABC_Type_of_Value:public Implements_ComplexVar_New
  {
  public:
    static std::string ClassName()
    {
      return "ABC_Type_of_Value";
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    virtual bool put(Implements_ComplexVar_New* cm,const ABC_Value_New* v,ABC_Output* ostream,std::string* error)const=0;

    virtual bool get(Implements_ComplexVar_New* cm,ABC_Value_New*& v, ABC_Input* istream,std::string* error )const=0;

    virtual ABC_BuildByToken* getBuildByToken(
        const Implements_ComplexVar_New* cm)const=0;

    virtual ABC_Value_New* empty_Value()const=0;

    virtual ABC_Var_New* empty_Var(const Implements_ComplexVar_New* parent,
                                   const std::string& id,
                                   const std::string& tip,
                                   const std::string& whathis)const=0;

    virtual ABC_Value_New* default_Value(const Implements_ComplexVar_New* cm)const=0;

    virtual ABC_Var_New* default_Var(const Implements_ComplexVar_New* parent,
                                     const std::string& id,
                                     const std::string& tip,
                                     const std::string& whathis)const=0;

    virtual std::set<std::string> alternativeNext(const Implements_ComplexVar_New* cm)const=0;


    virtual bool isInDomain(const Implements_ComplexVar_New* domain,const ABC_Value_New* v, std::string *whyNot)const=0;

    virtual Implements_ComplexVar_New* getComplexVarRep(const ABC_Var_New* var,std::string* whyNot,const std::string& masterObjective)const=0;

    virtual ABC_Var_New* getClassRep(const Implements_ComplexVar_New* cvar  ,std::string* whyNot)const=0;

    ABC_Type_of_Value (const Implements_ComplexVar_New* parent,
                       const std::string& id
                       ,const std::string& var
                       ,const std::string& tip
                       ,const std::string& whatthis):
      Implements_ComplexVar_New(parent,id,var,tip,whatthis){}
  };



  template<typename T>
  class ABC_Typed_Value:public ABC_Type_of_Value
  {
  public:
    static std::string ClassName()
    {
      return "ABC_Typed_Var_of_"+Cls<T>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    virtual bool isInDomain(const Implements_ComplexVar_New* cm,const ABC_Value_New* v, std::string *whyNot, const std::string& masterObjective)const
    {
      const std::string objective=masterObjective+": "+id()+ "do not has it in domain";
      auto x=dynamicCast<const Implements_Value_New<T>* >(v,whyNot,objective);
      if (x==nullptr)
        {
          return false;
        }
      else
        return isInDomain(cm,x->getValued(),whyNot,objective);
    }

    virtual bool put(const ABC_Value_New* v,ABC_Output* ostream
                     ,std::string* whyNot, const std::string& masterObjective)const
    {
    }

    virtual bool get(ABC_Value_New*& v, ABC_Input* istream,std::string* whyNot , const std::string& masterObjective)const
    {

    }





    virtual bool put(const T& v,ABC_Output* ostream,std::string* error)const=0;

    virtual bool get(T& v, ABC_Input* istream,std::string* whyNot )const=0;


    virtual Implements_ComplexVar_New* getComplexVarRep(const ABC_Var_New* var,std::string* whyNot, const std::string& masterObjective)const override
    {
      auto varT=dynamicCast<const Implements_Var_New<T>*>(var,whyNot,masterObjective);
      if (varT!=nullptr)
        return getComplexVarTyeped_Rep(varT,whyNot,masterObjective);
      else
        return nullptr;
    }

    virtual Implements_ComplexVar_New* getComplexVarTyeped_Rep(const Implements_Var_New<T>* var,std::string* whyNot,const std::string& masterObjective)const=0;

    virtual Implements_Var_New<T>* getClassRep(const Implements_ComplexVar_New* cvar  ,std::string* whyNot)const override=0;

    virtual T getDefault_Valued(const Implements_ComplexVar_New* cm)const=0;


    virtual bool isInDomain(const Implements_ComplexVar_New* cm,const T &val, std::__cxx11::string *whyNot
                            ,const std::string masterObjective ) const=0;


    virtual ~ABC_Typed_Value(){}


    ABC_Typed_Value(const Implements_ComplexVar_New* parent,
                    const std::string& id
                    ,const std::string& var
                    ,const std::string& tip
                    ,const std::string& whatthis):
      ABC_Type_of_Value(parent,id,var,tip,whatthis){}



  };


  template <typename T>
  class buildByToken;


  template<typename T>
  class Implements_Base_Type_New:public ABC_Typed_Value<T>
  {
  public:

    using typePredicate= bool(*)(const Implements_ComplexVar_New*,const T&,const Implements_ComplexVar_New*,
    std::string *WhyNot, const std::string& objective);

    using typeValue=T(*)(const Implements_ComplexVar_New*,const Implements_ComplexVar_New*);


    using getSet=std::set<std::string>(*)(const Implements_ComplexVar_New*,
    const Implements_ComplexVar_New*);

    static std::string ClassName()
    {
      return "Implements_Base_Type_New"+Cls<T>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }


    virtual bool isInDomain(const Implements_ComplexVar_New* cm,const T &val, std::__cxx11::string *whyNot,const std::string masterObjective ) const
    {
      return (*comply_)(cm,val,this,whyNot,masterObjective);
    }

    virtual bool put(const T& v,ABC_Output* ostream,const Implements_ComplexVar_New* cm,std::string* whyNot,const std::string masterObjective)const
    {
      if (isInDomain(cm,v,whyNot,masterObjective))
        {
          ostream->put(v);
          return true;
        }
      else return false;
    }
    virtual bool get(T& v, ABC_Input* istream,const Implements_ComplexVar_New* cm,std::string* whyNot ,const std::string masterObjective)const
    {

      if (!istream->get(v,whyNot,masterObjective))
        return false;
      else
        return isInDomain(cm,v,whyNot,masterObjective);
    }

    virtual std::set<std::string> alternativeNext(const Implements_ComplexVar_New* cm)const
    {
      return (*alternativeNext_)(cm,this);
    }



    virtual ~Implements_Base_Type_New(){}


    Implements_Base_Type_New(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis
                             ,const T& unknownVal
                             ,typePredicate complyPred
                             ,typeValue  defaultValue
                             ,getSet alterNext):
      ABC_Typed_Value<T>(parent,id,var,tip,whatthis)
    , unknownVaL_(unknownVal)
    ,comply_(complyPred)
    ,default_(defaultValue)
    ,alternativeNext_(alterNext)
    {}


    Implements_Base_Type_New(const Implements_ComplexVar_New *parent):
      Implements_Base_Type_New(
        parent,Cls<T>::name()
        ,ClassName()
        ,"regular "+Cls<T>::name()
        ,"just a "+Cls<T>::name()+ "nothing special"
        ,T{}
        ,[](const Implements_ComplexVar_New*,const T&,const Implements_ComplexVar_New*,
        std::string *, const std::string&)
    {return true;}
    ,[](const Implements_ComplexVar_New*,const Implements_ComplexVar_New*)
    {return T{};}
    ,[](const Implements_ComplexVar_New*, const Implements_ComplexVar_New*)
    {return std::set<std::string>();})
    {}

    // ABC_Type_of_Value interface
  public:
    virtual Implements_Value_New<T>* empty_Value()const override
    {
      return new Implements_Value_New<T>();
    }


    virtual Implements_Var_New<T> *empty_Var(const Implements_ComplexVar_New *parent, const std::__cxx11::string &idN, const std::__cxx11::string &tip, const std::__cxx11::string &whathis) const override
    {
      return new Implements_Var_New<T>(parent,idN,this->id(),tip,whathis,empty_Value());
    }


    virtual Implements_Value_New<T> *default_Value(const Implements_ComplexVar_New* cm) const override
    {
      return new Implements_Value_New<T>(getDefault_Valued(cm));
    }

    virtual Implements_Var_New<T> *default_Var(const Implements_ComplexVar_New *parent, const std::__cxx11::string &idN, const std::__cxx11::string &tip, const std::__cxx11::string &whathis) const override
    {
      return new Implements_Var_New<T>(parent,idN,this->id(),tip,whathis,default_Value(parent));
    }



    // ABC_Typed_Value interface
  public:
    virtual T getDefault_Valued(const Implements_ComplexVar_New* cm) const override
    {
      if (default_!=nullptr)
        return (*default_)(this,this);
      else
        return T{};
    }


  protected:
    T unknownVaL_;
    typePredicate comply_;
    typeValue default_;
    getSet alternativeNext_;


  };





  template<typename T, template<typename> class C>
  class Implements_Container_Type_New:public Implements_Base_Type_New<C<T>>
  {
  public:
    using typePredicate=typename Implements_Base_Type_New<C<T>>::typePredicate;
    using typeValue=typename Implements_Base_Type_New<C<T>>::typeValue;
    using getSet=typename Implements_Base_Type_New<C<T>>::getSet;



    using typeElementPredicate = bool(*)(const Implements_ComplexVar_New*,const C<T> &,const T&,const Implements_ComplexVar_New*, std::string *WhyNot, const std::string& objective);

    static std::string ClassName()
    {
      return "Implements_Container_Type_New_of_"+Cls<C<T>>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    virtual bool isElementInDomain(
        const Implements_ComplexVar_New* cm,
        const C<T> &val
        ,const T& elem
        , std::__cxx11::string *whyNot
        ,const std::string& masterObjective ) const
    {
      return (*elemComply_)(cm,val,elem,this,whyNot,masterObjective);
    }

    virtual buildByToken<T>* getElementBuildByToken(const Implements_ComplexVar_New* cm)const
    {
      return Implements_ComplexVar_New::G::getElementBuildByToken<T>(cm,this);
    }

    virtual const Implements_Data_Type_New<T>* getElementDataType(const Implements_ComplexVar_New* cm)const;




    virtual ~Implements_Container_Type_New(){}


    Implements_Container_Type_New(const Implements_ComplexVar_New* parent,
                                  const std::string& id
                                  ,const std::string& var
                                  ,const std::string& tip
                                  ,const std::string& whatthis
                                  , const std::string elementVar
                                  ,typePredicate complyPred
                                  ,typeElementPredicate elemeComply
                                  ,typeValue  defaultValue
                                  ,getSet alternN);


  protected:
    typeElementPredicate elemComply_;
  };


  template<typename T>
  using My_vec = std::vector<T>;  // to fake that vector takes only one template argument

  template<typename T>
  class Implements_Data_Type_New<std::vector<T>>;


  template<typename T>
  class Implements_Data_Type_New:public Implements_Base_Type_New<T>
  {
  public:
    using typePredicate=typename Implements_Base_Type_New<T>::typePredicate;
    using typeValue=typename Implements_Base_Type_New<T>::typeValue;
    using getSet=typename Implements_Base_Type_New<T>::getSet;



    static std::string ClassName()
    {
      return "Implements_Data_Type_New"+Cls<T>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }


    virtual buildByToken<T>* getBuildByToken(
        const Implements_ComplexVar_New* cm)const
    {
      return new buildByToken<T>(cm,this);
    }


    virtual ~Implements_Data_Type_New(){}



    Implements_Data_Type_New(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis
                             ,const T& unknownVal
                             ,typePredicate complyPred
                             ,typeValue  defaultValue
                             ,getSet alterNext):
      Implements_Base_Type_New<T>(parent,id,var,tip,whatthis,unknownVal
                                  ,complyPred,defaultValue,alterNext){}


    Implements_Data_Type_New(const Implements_ComplexVar_New *parent):
      Implements_Base_Type_New<T>(parent){}

  };




  template<typename T>
  class Implements_Data_Type_New<std::vector<T>>:public Implements_Container_Type_New<T,My_vec>
  {
  public:
    using typePredicate=typename Implements_Base_Type_New<std::vector<T>>::typePredicate;
    using typeValue=typename Implements_Base_Type_New<std::vector<T>>::typeValue;
    using getSet=typename Implements_Base_Type_New<std::vector<T>>::getSet;

    using typeElementPredicate= typename Implements_Container_Type_New<T,My_vec>::typeElementPredicate;


    static std::string ClassName()
    {
      return "Implements_Data_Type_New_of_"+Cls<std::vector<T>>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    virtual buildByToken<std::vector<T>>* getBuildByToken(
        const Implements_ComplexVar_New* cm)const
    {
      return new buildByToken<std::vector<T>>(cm,this);
    }



    virtual ~Implements_Data_Type_New(){}


    Implements_Data_Type_New(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis
                             , const std::string elementVar
                             ,typePredicate complyPred
                             ,typeElementPredicate elemeComply
                             ,typeValue  defaultValue
                             ,getSet alternN):
      Implements_Container_Type_New<T,My_vec>(
        parent,id,var,tip,whatthis,elementVar,complyPred,elemeComply
        ,defaultValue,alternN){}
  };


  template<typename T>
  using My_set = std::set<T>;  // to fake that set takes only one template argument

  template<typename T>
  class Implements_Data_Type_New<std::set<T>>:public Implements_Container_Type_New<T,My_set>
  {
  public:
    using typePredicate=typename Implements_Base_Type_New<std::set<T>>::typePredicate;
    using typeValue=typename Implements_Base_Type_New<std::set<T>>::typeValue;
    using getSet=typename Implements_Base_Type_New<std::set<T>>::getSet;

    using typeElementPredicate= typename Implements_Container_Type_New<T,My_set>::typeElementPredicate;


    static std::string ClassName()
    {
      return "Implements_Data_Type_New_of_"+Cls<std::set<T>>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }




    virtual ~Implements_Data_Type_New(){}


    virtual buildByToken<std::set<T>>*
    getBuildByToken(const Implements_ComplexVar_New* cm)const
    {
      return new buildByToken<std::set<T>>(cm,this);
    }




    Implements_Data_Type_New(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis
                             , const std::string elementVar
                             ,typePredicate complyPred
                             ,typeElementPredicate elemeComply
                             ,typeValue  defaultValue
                             ,getSet alternN):
      Implements_Container_Type_New<T,My_set>(
        parent,id,var,tip,whatthis,elementVar,complyPred,elemeComply
        ,defaultValue,alternN){}
  };



  template<typename T>
  class Implements_Data_Type_New<Markov_LA::M_Matrix<T>>:public Implements_Container_Type_New<T,Markov_LA::M_Matrix>
  {
  public:
    using typePredicate=typename Implements_Base_Type_New<Markov_LA::M_Matrix<T>>::typePredicate;
    using typeValue=typename Implements_Base_Type_New<Markov_LA::M_Matrix<T>>::typeValue;
    using getSet=typename Implements_Base_Type_New<Markov_LA::M_Matrix<T>>::getSet;

    using typeElementPredicate= typename Implements_Container_Type_New<T,Markov_LA::M_Matrix>::typeElementPredicate;


    static std::string ClassName()
    {
      return "Implements_Data_Type_New_of_"+Cls<Markov_LA::M_Matrix<T>>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }




    virtual ~Implements_Data_Type_New(){}


    virtual buildByToken<Markov_LA::M_Matrix<T>>* getBuildByToken(
        const Implements_ComplexVar_New* cm)const
    {
      return new buildByToken<Markov_LA::M_Matrix<T>>(cm,this);
    }




    Implements_Data_Type_New(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis
                             , const std::string elementVar
                             ,typePredicate complyPred
                             ,typeElementPredicate elemeComply
                             ,typeValue  defaultValue
                             ,getSet alternN):
      Implements_Container_Type_New<T,Markov_LA::M_Matrix>(
        parent,id,var,tip,whatthis,elementVar,complyPred,elemeComply
        ,defaultValue,alternN){}
  };





  template<typename K,typename T, template<typename,typename> class D>
  class Implements_Dictionary_Type_New:public Implements_Base_Type_New<D<K,T>>
  {
  public:
    using typePredicate=typename Implements_Base_Type_New<D<K,T>>::typePredicate;
    using typeValue=typename Implements_Base_Type_New<D<K,T>>::typeValue;
    using getSet=typename Implements_Base_Type_New<D<K,T>>::getSet;



    using typeElementPredicate = bool(*)(const Implements_ComplexVar_New*,const D<K,T> &,const T&,const Implements_ComplexVar_New*, std::string *WhyNot, const std::string& objective);


    using typeKeyPredicate = bool(*)(const Implements_ComplexVar_New*,const D<K,T> &,const K&,const Implements_ComplexVar_New*, std::string *WhyNot, const std::string& objective);



    static std::string ClassName()
    {
      return "Implements_Dictionary_Type_New_of_"+Cls<D<K,T>>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    virtual bool isElementInDomain(
        const Implements_ComplexVar_New* cm,
        const D<K,T> &val
        ,const T& elem
        , std::__cxx11::string *whyNot
        ,const std::string& masterObjective ) const
    {
      return (*elemComply_)(cm,val,elem,this,whyNot,masterObjective);
    }



    virtual buildByToken<T>* getElementBuildByToken(const Implements_ComplexVar_New* cm)const
    {
      return Implements_ComplexVar_New::G::getElementBuildByToken<T>(cm,this);
    }

    virtual const Implements_Data_Type_New<T>* getElementDataType(const Implements_ComplexVar_New* cm)const
    {
       return Implements_ComplexVar_New::G::getElementType<T>(cm,this);
    }


    virtual bool isKeyInDomain(
        const Implements_ComplexVar_New* cm,
        const D<K,T> &val
        ,const K& elem
        , std::__cxx11::string *whyNot
        ,const std::string& masterObjective ) const
    {
      return (*keyComply_)(cm,val,elem,this,whyNot,masterObjective);
    }

    virtual buildByToken<K>* getKeyBuildByToken(const Implements_ComplexVar_New* cm)const
    {
      return Implements_ComplexVar_New::G::getKeyBuildByToken<K>(cm,this);
    }

    virtual const Implements_Data_Type_New<K>* getKeyDataType(const Implements_ComplexVar_New* cm)const
    {
      return Implements_ComplexVar_New::G::getKeyType<K>(cm,this);
    }





    virtual ~Implements_Dictionary_Type_New(){}


    Implements_Dictionary_Type_New(
        const Implements_ComplexVar_New* parent,
        const std::string& id
        ,const std::string& var
        ,const std::string& tip
        ,const std::string& whatthis
        , const std::string keyVar
        , const std::string elementVar
        ,typePredicate complyPred
        ,typeKeyPredicate keyComply
        ,typeElementPredicate elemeComply
        ,typeValue  defaultValue
        ,getSet alternN):
      Implements_Base_Type_New<D<K,T>>(parent,id,var,tip,whatthis
                                       ,D<K,T>(),complyPred,defaultValue,alternN),
      elemComply_(elemeComply)
    ,keyComply_(keyComply)
    {
      Implements_ComplexVar_New::G::pushTypeOfKey(this,keyVar);
      Implements_ComplexVar_New::G::pushTypeOfElement(this,elementVar);
    }


  protected:
    typeElementPredicate elemComply_;
    typeKeyPredicate keyComply_;
  };







  template<typename K, typename T>
  class Implements_Data_Type_New<std::pair<K,T>>
      :public Implements_Dictionary_Type_New<K,T,std::pair>
  {
  public:

    using typePredicate=typename Implements_Base_Type_New<std::pair<K,T>>::typePredicate;
    using typeValue=typename Implements_Base_Type_New<std::pair<K,T>>::typeValue;
    using getSet=typename Implements_Base_Type_New<std::set<T>>::getSet;

    using typeElementPredicate= typename Implements_Dictionary_Type_New<K,T,std::pair>::typeElementPredicate;

    using typeKeyPredicate= typename Implements_Dictionary_Type_New<K,T,std::pair>::typeKeyPredicate;


    static std::string ClassName()
    {
      return "Implements_Data_Type_New_of_"+Cls<std::pair<K,T>>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }


    virtual ~Implements_Data_Type_New(){}


    Implements_Data_Type_New(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis
                             , const std::string keyVar
                             , const std::string elementVar
                             ,typePredicate complyPred
                             ,typeKeyPredicate keyComply
                             ,typeElementPredicate elemeComply
                             ,typeValue  defaultValue
                             ,getSet alternN):
      Implements_Dictionary_Type_New<K,T,std::pair>
      (parent,id,var,tip,whatthis,keyVar,elementVar,complyPred,keyComply
       ,elemeComply,defaultValue,alternN)
    {
    }
  };

  template<typename K,typename T>
  using My_map = std::map<K,T>;  // to fake that set takes only one template argument




  template<typename K, typename T>
  class Implements_Data_Type_New<std::map<K,T>>
      :public Implements_Dictionary_Type_New<K,T,My_map>
  {
  public:

    using typePredicate=typename Implements_Base_Type_New<std::map<K,T>>::typePredicate;
    using typeValue=typename Implements_Base_Type_New<std::map<K,T>>::typeValue;
    using getSet=typename Implements_Base_Type_New<std::set<T>>::getSet;

    using typeElementPredicate= typename Implements_Dictionary_Type_New<K,T,My_map>::typeElementPredicate;

    using typeKeyPredicate= typename Implements_Dictionary_Type_New<K,T,My_map>::typeKeyPredicate;


    static std::string ClassName()
    {
      return "Implements_Data_Type_New_of_"+Cls<std::map<K,T>>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }


    virtual ~Implements_Data_Type_New(){}


    Implements_Data_Type_New(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis
                             , const std::string keyVar
                             , const std::string elementVar
                             ,typePredicate complyPred
                             ,typeKeyPredicate keyComply
                             ,typeElementPredicate elemeComply
                             ,typeValue  defaultValue
                             ,getSet alternN):
      Implements_Dictionary_Type_New<K,T,My_map>
      (parent,id,var,tip,whatthis,keyVar,elementVar,complyPred,keyComply
       ,elemeComply,defaultValue,alternN)
    {
    }
  };



  template<>
  class Implements_Data_Type_New<std::map<std::string ,ABC_Var_New*>>:public Implements_Dictionary_Type_New<std::string ,ABC_Var_New*,My_map>
  {
  public:


    static std::string ClassName()
    {
      return "Implements_Data_Type_New_of_"+Cls<std::map<std::string ,ABC_Var_New*>>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }


    virtual ~Implements_Data_Type_New(){}



};





  template<>
  class Implements_Data_Type_New<ABC_Var_New*>:public ABC_Typed_Value<ABC_Var_New*>
  {
  public:

    using typePredicate= bool(*)(const Implements_ComplexVar_New*,
    const ABC_Var_New*&,const Implements_ComplexVar_New*,
    std::string *WhyNot, const std::string objective);

    using typeValue=ABC_Var_New*(*)(const Implements_ComplexVar_New*,
    const Implements_ComplexVar_New*);

    using getSet=std::set<std::string>(*)(const Implements_ComplexVar_New*,
    const Implements_ComplexVar_New*);

    static std::string ClassName()
    {
      return "Implements_Data_Type_New_of_"+ABC_Var_New::ClassName();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }


    virtual bool put(const ABC_Var_New* &v,ABC_Output* ostream,std::string* error)const
    {
      return true;
    }

    virtual bool get(ABC_Var_New*& v, ABC_Input* istream,std::string* whyNot , const std::string& masterObjective)const
    {

      if (!istream->get(v,whyNot, masterObjective))
        return false;
      else
        return isInDomain(v->parent(),v,whyNot,masterObjective);
    }

    virtual std::set<std::string> alternativeNext(const Implements_ComplexVar_New* cm)const
    {
      return (*alterNext_)(cm,this);
    }


    virtual ~Implements_Data_Type_New(){}


    Implements_Data_Type_New(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis
                             ,typePredicate complyPred
                             ,typeValue  defaultValue
                             ,getSet alterativNext):
      ABC_Typed_Value<ABC_Var_New*>(parent,id,var,tip,whatthis)
    ,comply_(complyPred)
    ,default_(defaultValue)
    ,alterNext_(alterativNext)
    {}

    // ABC_Type_of_Value interface
  public:
    virtual ABC_Value_New* empty_Value()const override
    {
    }


    virtual ABC_Var_New *empty_Var(const Implements_ComplexVar_New *parent, const std::__cxx11::string &idN, const std::__cxx11::string &tip, const std::__cxx11::string &whathis) const override
    {
      //    return new Implements_Var_New<T>(parent,idN,this->id(),tip,whathis,empty_Value());
    }


    virtual ABC_Value_New *default_Value(const Implements_ComplexVar_New* cm) const override
    {
      //     return Implements_Value_New<T>(getDefault_Valued(cm));
    }

    virtual ABC_Var_New*default_Var(const Implements_ComplexVar_New *parent, const std::__cxx11::string &idN, const std::__cxx11::string &tip, const std::__cxx11::string &whathis) const override
    {
      //   return new Implements_Var_New<T>(parent,idN,this->id(),tip,whathis,default_Value(parent));
    }



    // ABC_Typed_Value interface
  public:
    virtual ABC_Var_New* getDefault_Valued(const Implements_ComplexVar_New* cm) const override
    {
    }



  protected:

    Implements_Data_Type_New(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis):
      ABC_Typed_Value<ABC_Var_New*>(parent,id,var,tip,whatthis)
    ,comply_(nullptr)
    ,default_(nullptr)
    ,alterNext_(nullptr)
    {}



    typePredicate comply_;
    typeValue default_;
    getSet  alterNext_;
  };





  class Implements_Identifier_Type_New: public Implements_Data_Type_New<std::string>
  {
  public:
  static std::string ClassName()
    {
      return "Implements_Identifier_Type_New";
    }
    virtual std::string myClass()const override
    {
      return ClassName();
    }



    Implements_Identifier_Type_New(const Implements_ComplexVar_New* parent,
                                   const std::string& varTypeOfId
                                   ,typePredicate complyPred
                                   ,typeValue  defaultValue
                                   ,getSet alterNext);

    std::size_t static getVersionNumber(const std::string &id)
    {
      std::stringstream ss(id.substr(id.find_last_of('_')));
      std::size_t n;
      if (ss>>n)
        return n;
      else
        return std::string::npos;
    }

    static std::string nextId(const std::string &idTemplate)
    {
      auto n=getVersionNumber(idTemplate);

      if (n!=std::string::npos)
        {
          ++n;
          return idTemplate.substr(0,idTemplate.find_last_of('_')+1)+std::to_string(n);
        }
      else
        return idTemplate+"_0";
    }
    static bool isNewId(const std::string& idCandidate,
                        const Implements_ComplexVar_New* cm,
                        std::string *WhyNot, const std::string objective)
    {
      return cm->isNameUnOcuppied(idCandidate,WhyNot,objective);
    }



  };

  class Implements_Var_Identifier_Type_New: public Implements_Identifier_Type_New
  {
  public:
    static std::string ClassName()
    {
      return "Implements_Var_Identifier_Type_New";
    }

    std::string myClass()const override
    {
      return ClassName();
    }

    static bool isOfThisType(const Implements_ComplexVar_New* cm,
                             const std::string& name
                             ,const Implements_ComplexVar_New* self,
                             std::string *WhyNot, const std::string& objective)
    {
      std::string varType=G::gettypeOfId(self);
      const ABC_Var_New* v=cm->idToVar(name,WhyNot);
      const ABC_Type_of_Value* t=cm->idToType(varType,WhyNot,objective);
      if ((v==nullptr)||(t==nullptr))
        return false;
      else if (t->isInDomain(cm,v->value(),WhyNot))
        return true;
      else
        return false;
    }

    static std::string getDefaultValue(const Implements_ComplexVar_New* cm,
                                       const Implements_ComplexVar_New* self)
    {
      auto s=suggestedNames(cm,self);
      if (s.empty())
        return "";
      else
        return *s.begin();

    }


    static std::set<std::string> suggestedNames(const Implements_ComplexVar_New* cm,
                                                const Implements_ComplexVar_New* self)
    {
      std::string varType=G::gettypeOfId(self);
      return cm->getIdsOfType(varType);
    }


    Implements_Var_Identifier_Type_New(const Implements_ComplexVar_New* parent,
                                       const std::string varType):
      Implements_Identifier_Type_New(parent,varType,&isOfThisType,&getDefaultValue,&suggestedNames){}

  };

  class Implements_Type_Identifier_Type_New: public Implements_Identifier_Type_New
  {
  public:
    static std::string ClassName()
    {
      return "Implements_Type_Identifier_Type_New";
    }

    std::string myClass()const override
    {
      return ClassName();
    }

  };



  class Implements_New_Identifier_Type_New:public Implements_Identifier_Type_New
  {
  public:

    static std::string ClassName()
    {
      return "Implements_New_Identifier_Type_New";
    }
    virtual std::string myClass()const override
    {
      return ClassName();
    }

    static bool isNewIdentifier(const Implements_ComplexVar_New* cm,
                                const std::string& name
                                ,const Implements_ComplexVar_New*,
                                std::string *WhyNot, const std::string& objective)
    {
      return cm->isNameUnOcuppied(name,WhyNot,objective);
    }

    static std::string getDefaultValue(const Implements_ComplexVar_New* cm
                                       ,const Implements_ComplexVar_New* self)
    {
      std::string typevar=G::gettypeOfId(self);
      if (!typevar.empty())
        return "my"+typevar;
      else
        return {};
    }


    static std::set<std::string> suggestedNames(const Implements_ComplexVar_New* cm,
                                                const Implements_ComplexVar_New* self)
    {

      return {};
    }

    /// precondition: belongingtype has to be a type of parent!!
    /// it does not check that

    Implements_New_Identifier_Type_New(const Implements_ComplexVar_New* parent,
                                       const std::string& belongingtype):
      Implements_Identifier_Type_New(parent,belongingtype,&isNewIdentifier,&getDefaultValue,&suggestedNames)
    {
    }








  };









  class Implements_Var_Data_Type: public Implements_Data_Type_New<ABC_Var_New*>
  {
  public:
    static std::string typeOfId(const Implements_ComplexVar_New* self)
    {
      std::string belongType;
      std::string whyNot;
      if (self->getValueFromId(F::belongingType(),belongType,&whyNot,""))
        return belongType;
      else
        {
          return "";
        }

    }

    static bool isVar(const Implements_ComplexVar_New* cm
                      ,const ABC_Var_New*& v,const Implements_ComplexVar_New* ,
                      std::string *WhyNot, const std::string objective)
    {
      return cm->hasName(v->id(),WhyNot,objective);
    }

    static ABC_Var_New* defaultVar(const Implements_ComplexVar_New*,
                                   const Implements_ComplexVar_New*)
    {
      return nullptr;
    }

    static std::set<std::string> suggestedVars(const Implements_ComplexVar_New* cm,
                                               const Implements_ComplexVar_New* self)
    {

      auto vartype=G::gettypeOfId(self);
      return cm->getIdsOfType(vartype);
    }



    virtual buildByToken<ABC_Var_New *> *getBuildByToken(const Implements_ComplexVar_New* cm, std::string *whyNot, const std::string masterObjective)const;


    virtual buildByToken<std::string>* getNewIdentifierBuildByToken(const Implements_ComplexVar_New* cm)const;

    virtual buildByToken<std::string>* getVarIdentifierBuildByToken(const Implements_ComplexVar_New* cm)const
    {

    }


    virtual buildByToken<ABC_Value_New*>* getValueBuildByToken(const Implements_ComplexVar_New* cm)const
    {

    }


    Implements_Var_Data_Type(const Implements_ComplexVar_New* cm):
      Implements_Data_Type_New<ABC_Var_New*>(cm,
                                             ClassName(),ClassName(),"",""
                                             ,&isVar,&defaultVar,&suggestedVars){}


    Implements_Var_Data_Type(const Implements_ComplexVar_New* cm,
                             const std::string& varType):
      Implements_Data_Type_New<ABC_Var_New*>(cm,"id_"+varType,ClassName(),"","",&isVar,&defaultVar,&suggestedVars){
      this->pushChild(new Implements_Var_New<std::string>(
                        this,F::belongingType()
                        ,Implements_Var_Identifier_Type_New::ClassName()
                        ,varType,"",""));

    }



  };


  class Implements_Field_Data_Type: public Implements_Data_Type_New<ABC_Var_New*>
  {
  public:

    static std::string typeOfId(const Implements_ComplexVar_New* self)
    {
      std::string belongType;
      std::string whyNot;
      if (self->getValueFromId(F::belongingType(),belongType,&whyNot,""))
        return belongType;
      else
        {
          return "";
        }
    }

    static bool isVar(const Implements_ComplexVar_New* cm
                      ,const ABC_Var_New*& v,const Implements_ComplexVar_New* ,
                      std::string *WhyNot, const std::string objective)
    {
      return cm->hasName(v->id(),WhyNot,objective);
    }

    static ABC_Var_New* defaultVar(const Implements_ComplexVar_New*,
                                   const Implements_ComplexVar_New*)
    {
      return nullptr;
    }

    static std::set<std::string> suggestedVars(const Implements_ComplexVar_New* cm,
                                               const Implements_ComplexVar_New* self)
    {

      auto vartype=G::gettypeOfId(self);
      return cm->getIdsOfType(vartype);
    }



    virtual buildByToken<ABC_Var_New *> *getBuildByToken(const Implements_ComplexVar_New* cm, std::string *whyNot, const std::string masterObjective)const;


    virtual buildByToken<std::string>* getNewIdentifierBuildByToken(const Implements_ComplexVar_New* cm)const;

    virtual buildByToken<std::string>* getVarIdentifierBuildByToken(const Implements_ComplexVar_New* cm)const
    {

    }


    virtual buildByToken<ABC_Value_New*>* getValueBuildByToken(const Implements_ComplexVar_New* cm)const
    {

    }


    Implements_Field_Data_Type(const Implements_ComplexVar_New* cm):
      Implements_Data_Type_New<ABC_Var_New*>(cm,
                                             ClassName(),ClassName(),"",""
                                             ,&isVar,&defaultVar,&suggestedVars){}


    Implements_Field_Data_Type(const Implements_ComplexVar_New* cm,
                               const std::string& idName,
                               const std::string& vartype):
      Implements_Data_Type_New<ABC_Var_New*>(cm,"field_"+idName,ClassName(),"","",&isVar,&defaultVar,&suggestedVars){

      G::pushFieldName(this,idName);
      G::pushTypeOfId(this,vartype);

    }
  };





  template<>
  class Implements_Data_Type_New<Implements_ComplexVar_New*>:public Implements_Data_Type_New<ABC_Var_New*>
  {
  public:

    using typePredicate= bool(*)(const Implements_ComplexVar_New*,const Implements_ComplexVar_New*&,const Implements_ComplexVar_New*,
    std::string *WhyNot, const std::string objective);

    using typeValue=Implements_ComplexVar_New*(*)(const Implements_ComplexVar_New*);


    using getSet=std::set<std::string>(*)(const Implements_ComplexVar_New*,
    const Implements_ComplexVar_New*);


    using typeNextField= const Implements_Field_Data_Type* (*)(const Implements_ComplexVar_New*, const std::map<std::string, ABC_Var_New*>&,const Implements_ComplexVar_New*);


    static std::string ClassName()
    {
      return "Implements_Data_Type_New_of_"+Implements_ComplexVar_New::ClassName();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }



    virtual std::set<std::string> alternativeNext(const Implements_ComplexVar_New* cm)const
    {
      return {};
    }

    virtual buildByToken<std::map<std::string, ABC_Var_New*>>* getBuildByToken(const Implements_ComplexVar_New* cm)const
    {
      //return new buildByToken<std::map<std::string, ABC_Var_New*>>(cm,this);
    }


    virtual buildByToken<ABC_Var_New*> getFieldBuildByToken(const Implements_ComplexVar_New* cm, std::map<std::string,ABC_Var_New*> m)const;

    virtual const Implements_Field_Data_Type* nextField(const Implements_ComplexVar_New* cm, const std::map<std::string, ABC_Var_New*>& m)const;



    virtual ~Implements_Data_Type_New(){}


    Implements_Data_Type_New(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis

                             ,typePredicate complyPred
                             ,typeValue  defaultValue
                             ,getSet alterNext
                             , typeNextField nextF):
      Implements_Data_Type_New<ABC_Var_New*>(parent,id,var,tip,whatthis)
    ,comply_(complyPred)
    ,default_(defaultValue)
    ,alternatNext_(alterNext)
    ,nextField_(nextF)
    {

    }







    // ABC_Type_of_Value interface
  public:
    virtual Implements_Value_New<Implements_ComplexVar_New*>* empty_Value()const override
    {
      //return new Implements_Value_New<T>();
    }


    virtual Implements_ComplexVar_New *empty_Var(const Implements_ComplexVar_New *parent, const std::__cxx11::string &idN, const std::__cxx11::string &tip, const std::__cxx11::string &whathis) const override
    {
    }


    virtual Implements_Value_New<Implements_ComplexVar_New *>* default_Value(const Implements_ComplexVar_New* cm) const override
    {
      //return Implements_Value_New<T>(getDefault_Valued(cm));
    }

    virtual Implements_ComplexVar_New *default_Var(const Implements_ComplexVar_New *parent, const std::__cxx11::string &idN, const std::__cxx11::string &tip, const std::__cxx11::string &whathis) const override
    {
      //return new Implements_Var_New<T>(parent,idN,this->id(),tip,whathis,default_Value(parent));
    }



    // ABC_Typed_Value interface
  public:
    virtual Implements_ComplexVar_New* getDefault_Valued(const Implements_ComplexVar_New* cm) const override
    {
      if (default_!=nullptr)
        return (*default_)(this);
      else
        return nullptr;
    }

  protected:
    typePredicate comply_;
    typeValue default_;
    getSet  alternatNext_;
    typeNextField nextField_;
  };





  template<typename T>
  class Implements_Class_Type_New:public ABC_Typed_Value<T>
  {
  public:

    using typePredicate= bool(*)(const Implements_ComplexVar_New*,const T&,const Implements_Class_Type_New<T>*, std::string*);

    using getEmptyObject=T*(*)(const Implements_Class_Type_New<T>*, std::string*);

    using plainPredicate
    = bool(*)(const std::map<std::string,ABC_Var_New*>*,const Implements_Class_Type_New<T>*, std::string*);

    using getEmptyMap=std::map<std::string,ABC_Var_New*>* (*)(const Implements_Class_Type_New<T>*, std::string*);

    using getMap=std::map<std::string,ABC_Var_New*>* (*)(const T&, const Implements_Class_Type_New<T>*, std::string*);

    using getObject= T* (*)(const std::map<std::string,ABC_Var_New*>*,const Implements_Class_Type_New<T>*,std::string*);


    static std::string ClassName()
    {
      return "Implements_Class_Type_New_of"+Cls<T>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }


    virtual bool put(const T& v,ABC_Output* ostream,std::string* error)const
    {

      ostream->put(*v);
      return true;
    }

    virtual bool get(T*& v, ABC_Input* istream,std::string* whyNot )const
    {

      if (!istream->get(v,whyNot))
        return false;
      else
        return isInDomain(*v,whyNot);
    }

    virtual std::set<std::string> alternativeNext(const Implements_ComplexVar_New* cm)const
    {
      return {};
    }

    virtual buildByToken<T>* getBuildByToken(const Implements_ComplexVar_New* cm)const
    {
      return new buildByToken<T>(cm,this->id());
    }


    virtual ~Implements_Class_Type_New(){}


    Implements_Class_Type_New(const Implements_ComplexVar_New* parent,
                              const std::string& id
                              ,const std::string& var
                              ,const std::string& tip
                              ,const std::string& whatthis
                              ,typePredicate complyPred
                              ,plainPredicate mapComply
                              ,getEmptyObject  defaultValue
                              ,getEmptyMap eMap
                              ,getMap map
                              ,getObject obj):
      ABC_Typed_Value<T>(parent,id,var,tip,whatthis)
    ,comply_(complyPred)
    ,mapComply_(mapComply)
    ,default_(defaultValue)
    ,toEMap_(eMap)
    ,toMap_(map)
    ,toObj_(obj)
    {}




  protected:
    typePredicate comply_;
    plainPredicate mapComply_;
    getEmptyObject default_;
    getEmptyMap toEMap_;
    getObject toObj_;
    getMap toMap_;



    // ABC_Type_of_Value interface
  public:
    virtual Implements_Value_New<T>* empty_Value()const override
    {
      return new Implements_Value_New<T>();
    }


    virtual Implements_Var_New<T> *empty_Var(const Implements_ComplexVar_New *parent, const std::__cxx11::string &idN, const std::__cxx11::string &tip, const std::__cxx11::string &whathis) const override
    {
      return new Implements_Var_New<T>(parent,idN,this->id(),tip,whathis,empty_Value());
    }


    virtual Implements_Value_New<T> *default_Value(const Implements_ComplexVar_New* cm) const override
    {
      return Implements_Value_New<T>(getDefault_Valued(cm));
    }

    virtual Implements_Var_New<T> *default_Var(const Implements_ComplexVar_New *parent, const std::__cxx11::string &idN, const std::__cxx11::string &tip, const std::__cxx11::string &whathis) const override
    {
      return new Implements_Var_New<T>(parent,idN,this->id(),tip,whathis,default_Value(parent));
    }



    // ABC_Typed_Value interface
  public:
    virtual T getDefault_Valued(const Implements_ComplexVar_New* cm) const override
    {
      if (default_!=nullptr)
        return (*default_)(this);
      else
        return new T{};
    }

    // ABC_Type_of_Value interface
  public:
    virtual Implements_Var_New<T>* getClassRep(const Implements_ComplexVar_New *m, std::__cxx11::string *whyNot) const override
    {
      auto o=(*toObj_)(m->value()->getValued(),this,whyNot);
      if (o!=nullptr)
        return Implements_Var_New<T>
            (m->parent(),m->id(),m->myType(),m->Tip(),m->WhatThis()
             ,new Implements_Value_New<T>(o));
      else
        return nullptr;

    }


    // ABC_Typed_Value interface
  public:
    virtual Implements_ComplexVar_New *getComplexVarTyeped_Rep(const Implements_Var_New<T> *var, std::__cxx11::string *whyNot) const override
    {

    }


  };


  template<typename T>
  class Implements_Parameters_Type_New:public ABC_Typed_Value<T>
  {
  public:

    using typePredicate= bool(*)(const Implements_ComplexVar_New*,const T&,const Implements_Parameters_Type_New<T>*, std::string*);

    using getEmptyObject=T(*)(const Implements_Parameters_Type_New<T>*, std::string*);

    using plainPredicate
    = bool(*)(const std::map<std::string,Implements_Value_New<double>*>*,const Implements_Parameters_Type_New<T>*, std::string*);

    using getEmptyMap=std::map<std::string,ABC_Var_New*> (*)(const Implements_Parameters_Type_New<T>*, std::string*);

    using getMap=std::map<std::string,ABC_Var_New*> (*)(const T&, const Implements_Parameters_Type_New<T>*, std::string*);

    using getObject= T (*)(const std::map<std::string,ABC_Var_New*>*,const Implements_Class_Type_New<T>*,std::string*);


    static std::string ClassName()
    {
      return "Implements_Class_Type_New_of"+Cls<T>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }


    virtual bool put(const Implements_ComplexVar_New* cm,const T& v,ABC_Output* ostream,std::string* error)const
    {

      ostream->put(v);
      return true;
    }

    virtual bool get(const Implements_ComplexVar_New* cm,T& v, ABC_Input* istream,std::string* whyNot )const
    {

      if (!istream->get(v,whyNot))
        return false;
      else
        return isInDomain(*v,whyNot);
    }

    virtual std::set<std::string> alternativeNext(const Implements_ComplexVar_New* cm)const
    {
      return {};
    }

    virtual buildByToken<T>* getBuildByToken(const Implements_ComplexVar_New* cm)const
    {
      return new buildByToken<T>(cm,this->id());
    }


    virtual ~Implements_Parameters_Type_New(){}


    Implements_Parameters_Type_New(const Implements_ComplexVar_New* parent,
                                   const std::string& id
                                   ,const std::string& var
                                   ,const std::string& tip
                                   ,const std::string& whatthis
                                   ,typePredicate complyPred
                                   ,plainPredicate mapComply
                                   ,getEmptyObject  defaultValue
                                   ,getEmptyMap eMap
                                   ,getMap map
                                   ,getObject obj):
      ABC_Typed_Value<T>(parent,id,var,tip,whatthis)
    ,comply_(complyPred)
    ,mapComply_(mapComply)
    ,default_(defaultValue)
    ,toEMap_(eMap)
    ,toMap_(map)
    ,toObj_(obj)
    {}




  protected:
    typePredicate comply_;
    plainPredicate mapComply_;
    getEmptyObject default_;
    getEmptyMap toEMap_;
    getObject toObj_;
    getMap toMap_;



    // ABC_Type_of_Value interface
  public:
    virtual Implements_Value_New<T>* empty_Value()const override
    {
      return new Implements_Value_New<T>();
    }


    virtual Implements_Var_New<T> *empty_Var(const Implements_ComplexVar_New *parent, const std::__cxx11::string &idN, const std::__cxx11::string &tip, const std::__cxx11::string &whathis) const override
    {
      return new Implements_Var_New<T>(parent,idN,this->id(),tip,whathis,empty_Value());
    }


    virtual Implements_Value_New<T> *default_Value(const Implements_ComplexVar_New* cm) const override
    {
      return Implements_Value_New<T>(getDefault_Valued(cm));
    }

    virtual Implements_Var_New<T> *default_Var(const Implements_ComplexVar_New *parent, const std::__cxx11::string &idN, const std::__cxx11::string &tip, const std::__cxx11::string &whathis) const override
    {
      return new Implements_Var_New<T>(parent,idN,this->id(),tip,whathis,default_Value(parent));
    }



    // ABC_Typed_Value interface
  public:
    virtual T getDefault_Valued(const Implements_ComplexVar_New* cm) const override
    {
      if (default_!=nullptr)
        return (*default_)(this,this);
      else
        return new T{};
    }

    // ABC_Type_of_Value interface
  public:
    virtual Implements_Var_New<T>* getClassRep(const Implements_ComplexVar_New *m, std::__cxx11::string *whyNot) const override
    {
      auto o=(*toObj_)(m->value()->getValued(),this,whyNot);
      if (o!=nullptr)
        return Implements_Var_New<T>
            (m->parent(),m->id(),m->myType(),m->Tip(),m->WhatThis()
             ,new Implements_Value_New<T>(o));
      else
        return nullptr;

    }


    // ABC_Typed_Value interface
  public:
    virtual Implements_ComplexVar_New *getComplexVarTyeped_Rep(const Implements_Var_New<T> *var, std::__cxx11::string *whyNot) const override
    {

    }
  };

  class Markov_CommandManagerVar;


  class Implements_Command_Type_New:public ABC_Typed_Value<Implements_Command_Fields*>
  {
  public:

    using plainPredicate
    = bool(*)
    (const std::map<std::string,ABC_Var_New*>*,const Implements_Command_Type_New*, std::string*, const std::string&);

    using getEmptyMap
    =std::map<std::string,ABC_Var_New*>* (*)
    (const Implements_Command_Type_New*, std::string*, const std::string&);

    using runCommand
    = void (*)
    (Markov_CommandManagerVar* cm
    , const std::map<std::string,ABC_Var_New*>*
    ,const Implements_Command_Type_New*
    ,std::string*, const std::string&);


    static std::string ClassName()
    {
      return "Implements_Command_Type_New";
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    static buildByToken<std::string>* getBuildIdCommand(){}


    virtual ~Implements_Command_Type_New(){}


    Implements_Command_Type_New(const Implements_ComplexVar_New* parent,
                                const std::string& id
                                ,const std::string& var
                                ,const std::string& tip
                                ,const std::string& whatthis
                                ,plainPredicate mapComply
                                ,getEmptyMap toEmMap
                                ,runCommand run_):
      ABC_Typed_Value<Implements_Command_Fields*>(parent,id,var,tip,whatthis)
    ,mapComply_(mapComply)
    ,toEmMap_(toEmMap)
    ,run_(run_)
    {}

  protected:
    plainPredicate mapComply_;
    getEmptyMap toEmMap_;
    runCommand run_;

    // ABC_Type_of_Value interface
  public:
    virtual ABC_Value_New* empty_Value()const override
    {
    }


    Implements_Command_Fields* getCommandField()const
    {

    }

    virtual Implements_Command_Fields *empty_Var(const Implements_ComplexVar_New *parent, const std::__cxx11::string &idN, const std::__cxx11::string &tip, const std::__cxx11::string &whathis) const override
    {
    }


    virtual ABC_Value_New *default_Value(const Implements_ComplexVar_New* cm) const override
    {
    }

    virtual Implements_Command_Fields *default_Var(const Implements_ComplexVar_New *parent, const std::__cxx11::string &idN, const std::__cxx11::string &tip, const std::__cxx11::string &whathis) const override
    {

    }



  };











  ///--------------------------------------------------------------------
  ///-------------------------------------------------------------------
  ///

  /// Template implementations
  ///
  ///






  template<class L>
  L dynamicCast(ABC_Var_New* v, std::string* whyNot, const std::string& masterObective)
  {
    const std::string objective=masterObective+": cannot convert: ";
    auto r=dynamic_cast<L>(v);
    if (r==nullptr)
      {
        *whyNot=objective+v->id()+ "is not a "+Cls<L>::name();
      }
    return r;

  }


  template<class L>
  const L dynamicCast(const ABC_Var_New* v, std::string* whyNot, const std::string& masterObective)
  {
    const std::string objective=masterObective+": cannot convert: ";
    auto r=dynamic_cast<const L>(v);
    if (r==nullptr)
      {
        *whyNot=objective+v->id()+ "is not a "+Cls<L>::name();
      }
    return r;

  }




  template<class L>
  L dynamicCast(ABC_Value_New* v, std::string* whyNot, const std::string& masterObjective)
  {
    const std::string objective
        =masterObjective+": the dynamic cast of a "+ABC_Value_New::ClassName()+ " to a "+Cls<L>::name()+ "failed";
    if (v==nullptr)
      {
        *whyNot=objective+": nullptr input";
        return nullptr;
      }
    else
      {
        auto r=dynamic_cast<L>(v);
        if (r==nullptr)
          {
            *whyNot=objective+": "+v->myClass()+" cannot be casted into a "+Cls<L>::name();
          }
        return r;
      }
  }

  template<class L>
  const L dynamicCast(const ABC_Value_New* v, std::string* whyNot, const std::string& masterObjective)
  {
    const std::string objective
        =masterObjective+": the dynamic cast of a "+ABC_Value_New::ClassName()+ " to a "+Cls<L>::name()+ "failed";
    if (v==nullptr)
      {
        *whyNot=objective+": nullptr input";
        return nullptr;
      }
    else
      {
        auto r=dynamic_cast<const L>(v);
        if (r==nullptr)
          {
            *whyNot=objective+": "+v->myClass()+" cannot be casted into a "+Cls<L>::name();
          }
        return r;
      }
  }

  template<typename T>
  const T* ABC_Value_New::getValue()const
  {
    if (storedClass()==Cls<T>::name())
      {
        auto v =dynamic_cast<const Implements_Value_New<T>*>(this);
        return v->getValued();
      }
    else
      return nullptr;
  }

  template<typename T>
  T *ABC_Value_New::getValue()
  {
    if (storedClass()==Cls<T>::name())
      {
        auto v =dynamic_cast< Implements_Value_New<T>*>(this);
        return v->getValued();
      }
    else
      return nullptr;

  }

  template<typename T>
  bool ABC_Value_New::setValue(const T& val)
  {
    if (storedClass()==Cls<T>::name())
      {
        auto v =dynamic_cast< Implements_Value_New<T>*>(this);
        v->setValue(val);
        return true;
      }
    else
      return false;

  }

  inline
  bool Implements_ComplexVar_New::insertChild(const std::__cxx11::string &id, const std::__cxx11::string &var, const std::__cxx11::string &tip, const std::__cxx11::string &whatthis, std::__cxx11::string *whyNot, const std::string& masterObjective)
  {
    if (!this->isNameUnOcuppied(id,whyNot,masterObjective))
      {
        return false;
      }
    else
      {
        auto v=idToType(var,whyNot,masterObjective);
        if (v==nullptr)
          return false;
        else
          {
            pushChild(v->empty_Var(this,id,tip,whatthis));
            return true;
          }
      }
  }

  inline
  void Implements_ComplexVar_New::pushType(ABC_Type_of_Value *varT)
  {
    (*vars_)[varT->id()]=varT;
    (*types_)[varT->id()]=varT;
  }

  template<typename T, template<typename> class C>
  const Implements_Data_Type_New<T> *Implements_Container_Type_New<T,C>::getElementDataType(const Implements_ComplexVar_New *cm) const
  {
    const Implements_ComplexVar_New* self=this;
    return dynamic_cast<const Implements_Data_Type_New<T>*>(
          Implements_ComplexVar_New::G::getElementType<T>(cm,self));
  }






}

#include "Markov_IO/buildByToken.h"
namespace Markov_IO_New {
  template<typename T>
  buildByToken<T> *Implements_ComplexVar_New::G::getElementBuildByToken(const Implements_ComplexVar_New *cm, const Implements_ComplexVar_New *self)
  {
    const ABC_Typed_Value<T>* v= getElementType<T>(cm,self);
    if (v!=nullptr)
      return new buildByToken<T>(cm,v);
    else return nullptr;
  }


  template<typename T>
  buildByToken<T> *Implements_ComplexVar_New::G::getKeyBuildByToken(const Implements_ComplexVar_New *cm, const Implements_ComplexVar_New *self)
  {
    const ABC_Typed_Value<T>* v= getKeyType<T>(cm,self);
    if (v!=nullptr)
      return new buildByToken<T>(cm,v);
    else return nullptr;
  }


}





#endif // IMPLEMENTS_COMPLEXVAR_NEW_H
