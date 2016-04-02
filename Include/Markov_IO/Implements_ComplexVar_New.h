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

  template<typename T>
  class ABC_Typed_Value;


  class Implements_ComplexVar_New: public Implements_Var_New<std::map<std::string,ABC_Var_New*>>
  {
  public:

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
          +": "+name+ "is not a "+ Implements_Data_Type_New<T>::ClassName()+" in "+ id()+" namespece";
      auto it=types_->find(name);
      if (it!=types_->end())
        {
          return dynamic_cast<Implements_Data_Type_New<T>*>(
                it->second);
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
                 ,const std::string &masterObjective,
                 bool recursive)const
    {
      const std::string objective=masterObjective+ ": "+name+"is not in "+id();
      if (vars_->find(name)!=vars_->end())
        {
          return true;
        }
      else if ((!recursive)|| (parent()==nullptr))
        {
          *whyNot=objective;
          return false;
        }
      else return parent()->hasName(name, whyNot,objective,recursive);
    }



    bool hasNameofType(const std::string& name, const std::string& type,
                       std::string* whyNot
                       ,const std::string &masterObjective,
                       bool recursive)const;


    bool hasTypeofType(const std::string& name, const std::string& type,
                       std::string* whyNot
                       , const std::string &masterObjective, bool recursive)const;



    bool isNameUnOcuppied(const std::string& name,std::string* whyNot,const std::string &masterObjective, bool recursive)const
    {
      auto it=vars_->find(name);
      if (it!=vars_->end())
        {
          const ABC_Var_New* v=it->second;
          *whyNot=masterObjective+": "+name+" is currently a"+v->myType()+" in "+id();
        }
      else if (recursive&&(parent()!=nullptr))
        return parent()->isNameUnOcuppied(name,whyNot,masterObjective,recursive);
      else
        return true;
    }


    bool hasType(const std::string& name
                 , std::string* whyNot
                 ,const std::string &masterObjective,
                 bool recursive)const
    {
      const std::string objective=masterObjective+ ": "+name+"is not in "+id();
      if (types_->find(name)!=types_->end())
        {
          return true;
        }
      if (!recursive||(parent()==nullptr))
        {
          *whyNot=objective;
          return false;
        }
      else return parent()->hasType(name, whyNot,objective,recursive);
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
      if (isNameUnOcuppied(idN,whyNot,objective,false))
        {
          auto v=idToTyped<T>(var,whyNot,objective);
          if (v==nullptr)
            return false;
          else
            {
              if (!v->isVarInDomain(this,value,whyNot,objective))
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
                     , std::string *whyNot, const std::string &masterObjective);





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

    Implements_ComplexVar_New(const Implements_ComplexVar_New* parent,
                              const std::string& id
                              ,const std::string& var
                              ,std::map<std::string,ABC_Var_New*> m
                              ,const std::string& tip
                              ,const std::string& whatthis):
      Implements_Var_New(parent,
                         id,var,m,tip,whatthis)
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


    std::set<std::string> getIdsOfVarType(const std::string& varType, bool recursive)const;





    // Implements_Value_New interface

    std::set<std::string> getIdsOfTypeType(const std::string &typeType, bool recursive) const;
    std::string defaultIdOfVarType(const std::string &varType, bool recursive) const;
    std::string defaultIdOfTypeType(const std::string &typeType, bool recursive) const;
  private:
    std::map<std::string,ABC_Var_New*>* vars_;
    std::map<std::string,ABC_Type_of_Value*>* types_;
    std::map<std::string,Implements_Command_Type_New*>* cmds_;



  };





  class ABC_BuildByToken;

  class ABC_Type_of_Value:public Implements_ComplexVar_New
  {
  public:
    class F
    {
    public:

      static std::string varType() { return "varType";}

      static std::string idProposed(){return "idProposed";}

      static std::string elementType(){return "elementType";}

      static std::string keyType(){return "keyType";}


      static std::string idOfComplexVar(){return "idOfComplexVar";}
    };

    class V
    {
    public:
      static std::string identifier(){return "identifier";}

      static std::string identifierNewVar(){return "identifierNewVar";}

      static std::string identifierNewType(){return "identifierNewType";}

      static std::string identifierOfVar(){return "identifierOfVar";}

      static std::string identifierField(){return "identifierField";}

      static std::string identifierOfType(){return "identifierOfType";}
    };



    class G
    {
    public:
      static std::string gettypeOfId(const Implements_ComplexVar_New* self)
      {
        std::string belongType;
        std::string whyNot;
        if (self->getValueFromId(F::varType(),belongType,&whyNot,""))
          return belongType;
        else
          {
            return "";
          }

      }
      static void pushTypeOfId(Implements_ComplexVar_New* self,
                               std::string belongType)
      {
        self->pushChild(new Implements_Var_New<std::string>(
                          self,F::varType()
                          ,V::identifierOfType(),
                          std::move(belongType),
                          "",""));

      }






      static std::string getComplexVarId(const Implements_ComplexVar_New* self)
      {
        std::string idCV;
        std::string whyNot;
        if (self->getValueFromId(F::idOfComplexVar(),idCV,&whyNot,""))
          return idCV;
        else
          {
            return "";
          }

      }


      static void pushComplexVarId(Implements_ComplexVar_New* self,
                                   std::string fieldId)
      {
        self->pushChild(new Implements_Var_New<std::string>(
                          self,F::idOfComplexVar()
                          ,V::identifierOfVar(),
                          fieldId,
                          "",""));

      }


      static std::string getProposedId(const Implements_ComplexVar_New* self)
      {
        std::string proposedId;
        std::string whyNot;
        if (self->getValueFromId(F::idProposed(),proposedId,&whyNot,""))
          return proposedId;
        else
          {
            return "";
          }

      }


      static void pushProposedId(Implements_ComplexVar_New* self,
                                 std::string propId)
      {
        self->pushChild(new Implements_Var_New<std::string>(self,F::idProposed(),V::identifierNewVar(),propId,"tip","whatthis"));
      }



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
      return "ABC_Type_of_Value";
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    virtual bool put(const Implements_ComplexVar_New* cm
                     ,const ABC_Value_New* v
                     ,ABC_Output* ostream
                     ,std::string* error,
                     const std::string& masterObjective)const=0;

    virtual bool get(const Implements_ComplexVar_New* cm
                     ,ABC_Value_New*& v
                     , ABC_Input* istream
                     ,std::string* error
                     , const std::string& masterObjective)const=0;

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

    virtual ABC_Var_New* getVar( const Implements_ComplexVar_New* parent,
                                 const std::string& id,
                                 const std::string& mytype,
                                 const std::string& tip,
                                 const std::string& whathis,
                                 ABC_Value_New* v)const=0;



    const Implements_Data_Type_New<std::string>* getSelfIdType()const
    {
      return idSelfType_;
    }


    virtual std::set<std::string> alternativeNext(const Implements_ComplexVar_New* cm)const=0;


    virtual bool isVarInDomain(const Implements_ComplexVar_New* cm
                               ,const ABC_Value_New* v
                               , std::string *whyNot
                               , const std::string& masterObjective)const=0;


    virtual bool isTypeInDomain(const Implements_ComplexVar_New* cm
                                ,const ABC_Type_of_Value* t
                                , std::string *whyNot
                                , const std::string& masterObjective)const=0;



    virtual bool includesThisType(const Implements_ComplexVar_New* cm
                                  ,const std::string& childType
                                  ,std::string *whyNot
                                  , const std::string &masterObjective)const=0;








    virtual Implements_ComplexVar_New* getComplexVarRep(const ABC_Var_New* var,std::string* whyNot,const std::string& masterObjective)const=0;

    virtual ABC_Var_New* getClassRep(const Implements_ComplexVar_New* cvar  ,std::string* whyNot)const=0;

    ABC_Type_of_Value (const Implements_ComplexVar_New* parent,
                       const std::string& id
                       ,const std::string& var
                       ,const std::string& tip
                       ,const std::string& whatthis);
  private:
    Implements_Data_Type_New<std::string>* idSelfType_;
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

    virtual bool isVarInDomain(const Implements_ComplexVar_New* cm,const ABC_Value_New* v, std::string *whyNot, const std::string& masterObjective)const override
    {
      const std::string objective=masterObjective+": "+id()+ "do not has it in domain";
      auto x=dynamicCast<const Implements_Value_New<T>* >(v,whyNot,objective);
      if (x==nullptr)
        {
          return false;
        }
      else
        return isVarInDomain(cm,x->getValued(),whyNot,objective);
    }

    virtual bool isTypeInDomain(const Implements_ComplexVar_New* cm,const ABC_Type_of_Value* v, std::string *whyNot, const std::string& masterObjective)const override
    {
      const std::string objective=masterObjective+": "+id()+ "do not has it in domain";
      auto x=dynamic_cast<const Implements_Data_Type_New<T>* >(v);
      if (x==nullptr)
        {
          return false;
        }
      else
        return isTypeInDomain(cm,x,whyNot,objective);
    }





    virtual bool put(const Implements_ComplexVar_New* cm
                     ,const ABC_Value_New* v
                     ,ABC_Output* ostream
                     ,std::string* whyNot, const std::string& masterObjective)
    const override
    {
      const Implements_Value_New<T>* val=dynamic_cast<const Implements_Value_New<T>*>(v);
      if (val==nullptr)
        {
          *whyNot=masterObjective+": "+v->storedClass()+" is not a"+Cls<T>::name();
          return false;
        }
      else
        return put(cm,val->getValued(),ostream,whyNot,masterObjective);
    }

    virtual bool get(const Implements_ComplexVar_New* cm,ABC_Value_New*& v, ABC_Input* istream,std::string* whyNot , const std::string& masterObjective)const override
    {
      T x;
      if (this->get(cm,x,istream,whyNot,masterObjective))
        {
          v=new Implements_Value_New<T>(x);
          return true;
        }
      else return false;
    }





    virtual bool put(const Implements_ComplexVar_New* cm,
                     const T& v,ABC_Output* ostream,std::string* error, const std::string& masterObjective)const=0;

    virtual bool get(const Implements_ComplexVar_New* cm,
                     T& v, ABC_Input* istream,std::string* whyNot,
                     const std::string& masterObjective)const=0;


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


    virtual bool isVarInDomain(const Implements_ComplexVar_New* cm,const T &val, std::string *whyNot
                               ,const std::string& masterObjective ) const=0;


    virtual bool isTypeInDomain(const Implements_ComplexVar_New* cm
                                ,const Implements_Data_Type_New<T>* val
                                , std::string *whyNot
                                ,const std::string& masterObjective ) const=0;

    virtual Implements_Var_New<T>* getVar( const Implements_ComplexVar_New* parent,
                                           const std::string& id,
                                           const std::string& mytype,
                                           const std::string& tip,
                                           const std::string& whathis,
                                           ABC_Value_New* v)const override
    {
      Implements_Value_New<T>* val=dynamic_cast<Implements_Value_New<T>*>(v);
      if (val==nullptr)
        return nullptr;
      else
        return new Implements_Var_New<T>(parent,id,mytype
                                         ,tip,whathis,val);
    }


    virtual ~ABC_Typed_Value(){}


    ABC_Typed_Value(const Implements_ComplexVar_New* parent,
                    const std::string& id
                    ,const std::string& var
                    ,const std::string& tip
                    ,const std::string& whatthis):
      ABC_Type_of_Value(parent,id,var,tip,whatthis){}



  };


  template<typename T>
  class ABC_Typed_Value<T*>:public ABC_Type_of_Value
  {
  public:
    static std::string ClassName()
    {
      return "ABC_Typed_Var_of_"+Cls<T>::name()+"ptr";
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    virtual bool isVarInDomain(const Implements_ComplexVar_New* cm,const ABC_Value_New* v, std::string *whyNot, const std::string& masterObjective)const override
    {
      const std::string objective=masterObjective+": "+id()+ "do not has it in domain";
      auto x=dynamicCast<const Implements_Value_New<T*>* >(v,whyNot,objective);
      if (x==nullptr)
        {
          return false;
        }
      else
        return isVarInDomain(cm,x->getValued(),whyNot,objective);
    }



    virtual bool isTypeInDomain(const Implements_ComplexVar_New* cm,const ABC_Type_of_Value* v, std::string *whyNot, const std::string& masterObjective)const override
    {
      const std::string objective=masterObjective+": "+id()+ "do not has it in domain";
      auto x=dynamicCast<const Implements_Data_Type_New<T*>* >(v,whyNot,objective);
      if (x==nullptr)
        {
          return false;
        }
      else
        return isTypeInDomain(cm,x,whyNot,objective);
    }




    virtual bool put(const Implements_ComplexVar_New* cm
                     ,const ABC_Value_New* v
                     ,ABC_Output* ostream
                     ,std::string* whyNot, const std::string& masterObjective)
    const override
    {
      const Implements_Value_New<T*>* val=dynamic_cast<const Implements_Value_New<T*>*>(v);
      if (val==nullptr)
        {
          *whyNot=masterObjective+": "+v->storedClass()+" is not a"+Cls<T>::name();
          return false;
        }
      else
        return put(cm,val->getValued(),ostream,whyNot,masterObjective);
    }

    virtual bool get(const Implements_ComplexVar_New* cm,ABC_Value_New*& v, ABC_Input* istream,std::string* whyNot , const std::string& masterObjective)const override
    {
      T* p;
      if (this->get(cm,p,istream,whyNot,masterObjective))
        {
          v=new Implements_Value_New<T*>(p);
          return true;
        }
      else return false;
    }





    virtual bool put(const Implements_ComplexVar_New* cm,
                     const T* v,ABC_Output* ostream,std::string* error, const std::string& masterObjective)const=0;

    virtual bool get(const Implements_ComplexVar_New* cm,
                     T*& v, ABC_Input* istream,std::string* whyNot,
                     const std::string& masterObjective)const=0;


    virtual Implements_ComplexVar_New* getComplexVarRep(const ABC_Var_New* var,std::string* whyNot, const std::string& masterObjective)const override
    {
      auto varT=dynamicCast<const Implements_Var_New<T*>*>(var,whyNot,masterObjective);
      if (varT!=nullptr)
        return getComplexVarTyeped_Rep(varT,whyNot,masterObjective);
      else
        return nullptr;
    }

    virtual Implements_ComplexVar_New* getComplexVarTyeped_Rep(const Implements_Var_New<T*>* var,std::string* whyNot,const std::string& masterObjective)const=0;

    virtual Implements_Var_New<T*>* getClassRep(const Implements_ComplexVar_New* cvar  ,std::string* whyNot)const override=0;

    virtual T* getDefault_Valued(const Implements_ComplexVar_New* cm)const=0;


    virtual bool isVarInDomain(const Implements_ComplexVar_New* cm,const T *val, std::string *whyNot
                               ,const std::string &masterObjective ) const=0;



    virtual bool isTypeInDomain(const Implements_ComplexVar_New* cm
                                ,const Implements_Data_Type_New<T*>* val
                                , std::string *whyNot
                                ,const std::string& masterObjective ) const=0;

    virtual Implements_Var_New<T*>* getVar( const Implements_ComplexVar_New* parent,
                                            const std::string& id,
                                            const std::string& mytype,
                                            const std::string& tip,
                                            const std::string& whathis,
                                            ABC_Value_New* v)const
    {
      Implements_Value_New<T*>* val=dynamic_cast<Implements_Value_New<T*>*>(v);
      if (val==nullptr)
        return nullptr;
      else
        return new Implements_Var_New<T*>(parent,id,mytype
                                          ,tip,whathis,val);
    }


    virtual ~ABC_Typed_Value(){}


    ABC_Typed_Value(const Implements_ComplexVar_New* parent,
                    const std::string& id
                    ,const std::string& var
                    ,const std::string& tip
                    ,const std::string& whatthis):
      ABC_Type_of_Value(parent,id,var,tip,whatthis){}



  };



  namespace _private {



  template<typename T>
  class Implements_Base_Type_New:public ABC_Typed_Value<T>
  {
  public:

    using typePredicate= bool(*)(const Implements_ComplexVar_New*
    ,const T&,const Implements_ComplexVar_New*,
    std::string *WhyNot, const std::string& objective);

    using typetypePredicate= bool(*)(const Implements_ComplexVar_New*
    ,const Implements_Data_Type_New<T>*
    ,const Implements_ComplexVar_New*,
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


    virtual bool isVarInDomain(const Implements_ComplexVar_New* cm,const T &val, std::string *whyNot,const std::string& masterObjective ) const override
    {
      if (comply_!=nullptr)
        return (*comply_)(cm,val,this,whyNot,masterObjective);
      else return true;
    }


    virtual bool isTypeInDomain(const Implements_ComplexVar_New* cm
                                ,const Implements_Data_Type_New<T>* val
                                , std::string *whyNot
                                ,const std::string& masterObjective ) const override
    {
      if (typeComply_!=nullptr)
        return (*typeComply_)(cm,val,this,whyNot,masterObjective);
      else return true;
    }





    virtual std::set<std::string> alternativeNext(const Implements_ComplexVar_New* cm)const
    {
      if (alternativeNext_!=nullptr)
        return (*alternativeNext_)(cm,this);
      else return {};
    }

    virtual bool includesThisType(const Implements_ComplexVar_New* cm,
                                  const std::string& childType,
                                  std::string *whyNot
                                  , const std::string &masterObjective)const override;






    virtual Implements_ComplexVar_New* getComplexVarTyeped_Rep(const Implements_Var_New<T>* ,std::string* ,const std::string& )const
    {
      return nullptr;
    }

    virtual Implements_Var_New<T>* getClassRep(const Implements_ComplexVar_New*   ,std::string* )const override
    {
      return nullptr;
    }




    virtual ~Implements_Base_Type_New(){}


    Implements_Base_Type_New(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis
                             ,const T& unknownVal
                             ,typePredicate complyPred
                             ,typetypePredicate complyType
                             ,typeValue  defaultValue
                             ,getSet alterNext):
      ABC_Typed_Value<T>(parent,id,var,tip,whatthis)
    , unknownVaL_(unknownVal)
    ,comply_(complyPred)
    ,typeComply_(complyType)
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
    ,[](const Implements_ComplexVar_New*,const Implements_Data_Type_New<T>*
    ,const Implements_ComplexVar_New*,
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
      return new Implements_Value_New<T>(unknownVaL_);
    }


    virtual Implements_Var_New<T> *empty_Var(const Implements_ComplexVar_New *parent, const std::string &idN, const std::string &tip, const std::string &whathis) const override
    {
      return new Implements_Var_New<T>(
            parent,idN,this->id(),tip,whathis,empty_Value());
    }


    virtual Implements_Value_New<T> *default_Value(const Implements_ComplexVar_New* cm) const override
    {
      return new Implements_Value_New<T>(getDefault_Valued(cm));
    }

    virtual Implements_Var_New<T> *default_Var(const Implements_ComplexVar_New *parent, const std::string &idN, const std::string &tip, const std::string &whathis) const override
    {
      return new Implements_Var_New<T>(
            parent,idN,this->id(),tip,whathis,default_Value(parent));
    }



    // ABC_Typed_Value interface
  public:
    virtual T getDefault_Valued(const Implements_ComplexVar_New* cm) const override
    {
      return (*default_)(cm,this);
    }


  protected:
    T unknownVaL_;
    typePredicate comply_;
    typetypePredicate typeComply_;
    typeValue default_;
    getSet alternativeNext_;


  };


  template<typename T>
  class Implements_Base_Type_New<T*>:public ABC_Typed_Value<T*>
  {
  public:

    using typePredicate= bool(*)(const Implements_ComplexVar_New*
    ,const T*,const Implements_ComplexVar_New*,
    std::string *WhyNot, const std::string& objective);

    using typetypePredicate= bool(*)(const Implements_ComplexVar_New*
    ,const Implements_Data_Type_New<T*>*,
    const Implements_ComplexVar_New*,
    std::string *WhyNot, const std::string& objective);


    using typeValue=T*(*)(const Implements_ComplexVar_New*,const Implements_ComplexVar_New*);


    using getSet=std::set<std::string>(*)(const Implements_ComplexVar_New*,
    const Implements_ComplexVar_New*);

    static std::string ClassName()
    {
      return "Implements_Base_Type_New"+Cls<T>::name()+"ptr";
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }


    virtual bool isVarInDomain(const Implements_ComplexVar_New* cm,const T *val, std::string *whyNot,const std::string &masterObjective ) const override
    {
      return (*comply_)(cm,val,this,whyNot,masterObjective);
    }

    virtual bool isTypeInDomain(const Implements_ComplexVar_New* cm
                                ,const Implements_Data_Type_New<T*>* val
                                , std::string *whyNot
                                ,const std::string &masterObjective ) const override
    {
      return (*typeComply_)(cm,val,this,whyNot,masterObjective);
    }



    virtual std::set<std::string> alternativeNext(const Implements_ComplexVar_New* cm)const
    {
      return (*alternativeNext_)(cm,this);
    }

    virtual bool includesThisType(const Implements_ComplexVar_New* cm,
                                  const std::string& childType,
                                  std::string *whyNot
                                  , const std::string &masterObjective)const;




    virtual Implements_ComplexVar_New* getComplexVarTyeped_Rep(const Implements_Var_New<T*>* ,std::string* ,const std::string& )const override
    {
      return nullptr;
    }

    virtual Implements_Var_New<T*>* getClassRep(const Implements_ComplexVar_New*   ,std::string* )const override
    {
      return nullptr;
    }




    virtual ~Implements_Base_Type_New(){
      delete unknownVaL_;
    }


    Implements_Base_Type_New(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis
                             ,const T* unknownVal
                             ,typePredicate complyPred
                             ,typetypePredicate typeComply
                             ,typeValue  defaultValue
                             ,getSet alterNext):
      ABC_Typed_Value<T*>(parent,id,var,tip,whatthis)
    , unknownVaL_(unknownVal)
    ,comply_(complyPred)
    ,typeComply_(typeComply)
    ,default_(defaultValue)
    ,alternativeNext_(alterNext)
    {}


    Implements_Base_Type_New(const Implements_ComplexVar_New *parent):
      Implements_Base_Type_New(
        parent,Cls<T>::name()
        ,ClassName()
        ,"regular "+Cls<T>::name()
        ,"just a "+Cls<T>::name()+ "nothing special"
        ,new T{}
        ,[](const Implements_ComplexVar_New*,const T*&,const Implements_ComplexVar_New*,
        std::string *, const std::string&)
    {return true;}
    ,[](const Implements_ComplexVar_New*,const Implements_Data_Type_New<T*>*
    ,const Implements_ComplexVar_New*,
    std::string *, const std::string&)
    {return true;}
    ,[](const Implements_ComplexVar_New*,const Implements_ComplexVar_New*)
    {return new T{};}
    ,[](const Implements_ComplexVar_New*, const Implements_ComplexVar_New*)
    {return std::set<std::string>();})
    {}

    // ABC_Type_of_Value interface
  public:
    virtual Implements_Value_New<T*>* empty_Value()const override
    {
      return new Implements_Value_New<T*>(nullptr);
    }


    virtual Implements_Var_New<T*> *empty_Var(const Implements_ComplexVar_New *parent, const std::string &idN, const std::string &tip, const std::string &whathis) const override
    {
      return new Implements_Var_New<T*>(
            parent,idN,this->id(),tip,whathis,empty_Value());
    }


    virtual Implements_Value_New<T*> *default_Value(const Implements_ComplexVar_New* cm) const override
    {
      return new Implements_Value_New<T*>(getDefault_Valued(cm));
    }

    virtual Implements_Var_New<T*> *default_Var(const Implements_ComplexVar_New *parent, const std::string &idN, const std::string &tip, const std::string &whathis) const override
    {
      return new Implements_Var_New<T*>(
            parent,idN,this->id(),tip,whathis,default_Value(parent));
    }



    // ABC_Typed_Value interface
  public:
    virtual T* getDefault_Valued(const Implements_ComplexVar_New* cm) const override
    {
      return (*default_)(cm,this);
    }


  protected:
    const T* unknownVaL_;
    typePredicate comply_;
    typetypePredicate typeComply_;
    typeValue default_;
    getSet alternativeNext_;


  };


  template<typename T, template<typename> class C>
  class Implements_Container_Type_New:public Implements_Base_Type_New<C<T>>
  {
  public:
    using typePredicate=typename Implements_Base_Type_New<C<T>>::typePredicate;
    using typetypePredicate=typename Implements_Base_Type_New<C<T>>::typetypePredicate;
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
        , std::string *whyNot
        ,const std::string& masterObjective ) const
    {
      return (*elemComply_)(cm,val,elem,this,whyNot,masterObjective);
    }

    virtual buildByToken<T>* getElementBuildByToken(const Implements_ComplexVar_New* cm)const
    {
      return ABC_Type_of_Value::G::getElementBuildByToken<T>(cm,this);
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
                                  ,typetypePredicate typeComply                                 ,typeElementPredicate elemeComply
                                  ,typeValue  defaultValue
                                  ,getSet alternN):
      Implements_Base_Type_New<C<T>>(parent,id,var,tip,whatthis,C<T>()
                                     ,complyPred,typeComply,defaultValue,alternN),
      elemComply_(elemeComply)
    {
      ABC_Type_of_Value::G::pushTypeOfElement(this,elementVar);

    }


  protected:
    typeElementPredicate elemComply_;
  };


  template<typename T>
  using My_vec = std::vector<T>;  // to fake that vector takes only one template argument


  template<typename T>
  class Implements_Data_Type_New_vector:public Implements_Container_Type_New<T,My_vec>
  {
  public:
    using typePredicate=typename Implements_Base_Type_New<std::vector<T>>::typePredicate;
    using typetypePredicate=typename Implements_Base_Type_New<std::vector<T>>::typetypePredicate;
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

    virtual bool put(const Implements_ComplexVar_New* cm,const std::vector<T>& v,ABC_Output* ostream,std::string* whyNot,const std::string& masterObjective)const override
    {
      if (this->isVarInDomain(cm,v,whyNot,masterObjective))
        {
          const Implements_Data_Type_New<T>* etype=this->getElementDataType(cm);
          ostream->put("\n[");
          for (auto& e: v)
            {
              if (!this->isElementInDomain(cm,v,e,whyNot,masterObjective))
                return false;
              if(!etype->put(cm,e,ostream,whyNot,masterObjective))
                {
                  ostream->put(*whyNot);
                  return false;
                }
            }
          ostream->put("]");
          return true;
        }
      else
        return false;
    }
    virtual bool get(const Implements_ComplexVar_New* cm
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
          std::size_t i=0;
          std::size_t n=v.size();
          while ((i<n)&&(!istream->nextCharIs(']',false)))
            {
              T d;
              if (etype->get(cm,d,istream,whyNot,masterObjective))
                {
                  if (this->isElementInDomain(cm,v,d,whyNot,masterObjective))
                    {
                      v[i]=std::move(d);
                      ++i;
                    }
                  else return false;

                }
              else
                return false;

            }
          while ((!istream->nextCharIs(']',false)))
            {
              T d;
              if (etype->get(cm,d,istream,whyNot,masterObjective))
                {
                  if (this->isElementInDomain(cm,v,d,whyNot,masterObjective))
                    {
                      v.push_back(std::move(d));
                    }
                  else return false;
                }
              else
                return false;

            }
          if (this->isVarInDomain(cm,v,whyNot,masterObjective))
            return true;
          else
            return false;
        }

    }



    virtual buildByToken<std::vector<T>>* getBuildByToken(
        const Implements_ComplexVar_New* cm)const
    {
      return new buildByToken<std::vector<T>>(cm,this);
    }



    virtual ~Implements_Data_Type_New_vector(){}




    Implements_Data_Type_New_vector(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis
                             , const std::string elementVar
                             ,typePredicate complyPred
                             ,typetypePredicate typeComply
                             ,typeElementPredicate elemeComply
                             ,typeValue  defaultValue
                             ,getSet alternN):
      Implements_Container_Type_New<T,My_vec>(
        parent,id,var,tip,whatthis,elementVar,complyPred,typeComply,elemeComply
        ,defaultValue,alternN){}
  };



  template<typename T>
  class Implements_Data_Type_New_regular:public Implements_Base_Type_New<T>
  {
  public:
    using typePredicate=typename Implements_Base_Type_New<T>::typePredicate;
    using typetypePredicate=typename Implements_Base_Type_New<T>::typetypePredicate;

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
        const Implements_ComplexVar_New* cm)const override
    {
      return new buildByToken<T>(cm,this);
    }

    virtual bool put(const Implements_ComplexVar_New* cm,
                     const T& v,ABC_Output* ostream,std::string* whyNot
                     ,const std::string& masterObjective)const override
    {
      if (this->isVarInDomain(cm,v,whyNot,masterObjective))
        {
          ostream->put(v);
          return true;
        }
      else return false;
    }


    virtual bool get(const Implements_ComplexVar_New* cm
                     ,T& v, ABC_Input* istream,std::string* whyNot
                     ,const std::string& masterObjective)const override
    {

      if (!istream->get(v,whyNot,masterObjective))
        return false;
      else
        return this->isVarInDomain(cm,v,whyNot,masterObjective);
    }



    virtual ~Implements_Data_Type_New_regular(){}



    Implements_Data_Type_New_regular(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis
                             ,const T& unknownVal
                             ,typePredicate complyPred
                             ,typetypePredicate typeComply
                             ,typeValue  defaultValue
                             ,getSet alterNext):
      Implements_Base_Type_New<T>(parent,id,var,tip,whatthis,unknownVal
                                  ,complyPred,typeComply,defaultValue,alterNext){}


    Implements_Data_Type_New_regular(const Implements_ComplexVar_New *parent):
      Implements_Base_Type_New<T>(parent){}

  };


  template<typename T>
  using My_set = std::set<T>;  // to fake that set takes only one template argument

  template<typename T>
  class Implements_Data_Type_New_set:public Implements_Container_Type_New<T,My_set>
  {
  public:
    using typePredicate=typename Implements_Base_Type_New<std::set<T>>::typePredicate;
    using typetypePredicate=typename Implements_Base_Type_New<std::set<T>>::typetypePredicate;
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




    virtual ~Implements_Data_Type_New_set(){}




    virtual bool put(const Implements_ComplexVar_New* cm
                     ,const std::set<T>& v
                     ,ABC_Output* ostream
                     ,std::string* whyNot
                     ,const std::string& masterObjective)const override
    {
      if (this->isVarInDomain(cm,v,whyNot,masterObjective))
        {
          const Implements_Data_Type_New<T>* etype=this->getElementDataType(cm);
          ostream->put("\n{");
          for (auto& e: v)
            {
              if (!this->isElementInDomain(cm,v,e,whyNot,masterObjective))
                return false;
              if(!etype->put(cm,e,ostream,whyNot,masterObjective))
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
    virtual bool get(const Implements_ComplexVar_New* cm,std::set<T>& v, ABC_Input* istream,std::string* whyNot ,const std::string& masterObjective)const override
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
                  if (this->isElementInDomain(cm,v,d,whyNot,masterObjective))
                    {
                      v.insert(std::move(d));
                    }
                  else return false;
                }
              else
                return false;
            }
          if (this->isVarInDomain(cm,v,whyNot,masterObjective))
            return true;
          else
            return false;
        }

    }




    virtual buildByToken<std::set<T>>*
    getBuildByToken(const Implements_ComplexVar_New* cm)const
    {
      return new buildByToken<std::set<T>>(cm,this);
    }




    Implements_Data_Type_New_set(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis
                             , const std::string elementVar
                             ,typePredicate complyPred
                             ,typetypePredicate typeComply
                             ,typeElementPredicate elemeComply
                             ,typeValue  defaultValue
                             ,getSet alternN):
      Implements_Container_Type_New<T,My_set>(
        parent,id,var,tip,whatthis,elementVar,complyPred,typeComply,elemeComply
        ,defaultValue,alternN){}



  };



  template<typename T>
  class Implements_Data_Type_New_M_Matrix:public Implements_Container_Type_New<T,Markov_LA::M_Matrix>
  {
  public:
    using typePredicate=typename Implements_Base_Type_New<Markov_LA::M_Matrix<T>>::typePredicate;
    using typetypePredicate=typename Implements_Base_Type_New<Markov_LA::M_Matrix<T>>::typetypePredicate;
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




    virtual ~Implements_Data_Type_New_M_Matrix(){}


    virtual buildByToken<Markov_LA::M_Matrix<T>>* getBuildByToken(
        const Implements_ComplexVar_New* cm)const
    {
      return new buildByToken<Markov_LA::M_Matrix<T>>(cm,this);
    }

    bool get(const Implements_ComplexVar_New *cm, Markov_LA::M_Matrix<T> &v, ABC_Input *istream, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const{

    }

    bool put(const Implements_ComplexVar_New *cm, const Markov_LA::M_Matrix<T> &v, ABC_Output *ostream, std::__cxx11::string *error, const std::__cxx11::string &masterObjective) const
    {

    }


    Implements_Data_Type_New_M_Matrix(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis
                             , const std::string elementVar
                             ,typePredicate complyPred
                             ,typetypePredicate typeComply
                             ,typeElementPredicate elemeComply
                             ,typeValue  defaultValue
                             ,getSet alternN):
      Implements_Container_Type_New<T,Markov_LA::M_Matrix>(
        parent,id,var,tip,whatthis,elementVar,complyPred,typeComply,elemeComply
        ,defaultValue,alternN){}
  };


  template<typename K,typename T, template<typename,typename> class D>
  class Implements_Dictionary_Type_New:public Implements_Base_Type_New<D<K,T>>
  {
  public:
    using typePredicate=typename Implements_Base_Type_New<D<K,T>>::typePredicate;
    using typetypePredicate=typename Implements_Base_Type_New<D<K,T>>::typetypePredicate;
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
        , std::string *whyNot
        ,const std::string& masterObjective ) const
    {
      return (*elemComply_)(cm,val,elem,this,whyNot,masterObjective);
    }



    virtual buildByToken<T>* getElementBuildByToken(const Implements_ComplexVar_New* cm)const
    {
      return ABC_Type_of_Value::G::getElementBuildByToken<T>(cm,this);
    }

    virtual const Implements_Data_Type_New<T>* getElementDataType(const Implements_ComplexVar_New* cm)const
    {
      return ABC_Type_of_Value::G::getElementType<T>(cm,this);
    }


    virtual bool isKeyInDomain(
        const Implements_ComplexVar_New* cm,
        const D<K,T> &val
        ,const K& elem
        , std::string *whyNot
        ,const std::string& masterObjective ) const
    {
      return (*keyComply_)(cm,val,elem,this,whyNot,masterObjective);
    }

    virtual buildByToken<K>* getKeyBuildByToken(const Implements_ComplexVar_New* cm)const
    {
      return ABC_Type_of_Value::G::getKeyBuildByToken<K>(cm,this);
    }

    virtual const Implements_Data_Type_New<K>* getKeyDataType(const Implements_ComplexVar_New* cm)const
    {
      return ABC_Type_of_Value::G::getKeyType<K>(cm,this);
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
        ,typetypePredicate typeComply
        ,typeKeyPredicate keyComply
        ,typeElementPredicate elemeComply
        ,typeValue  defaultValue
        ,getSet alternN):
      Implements_Base_Type_New<D<K,T>>(parent,id,var,tip,whatthis
                                       ,D<K,T>(),complyPred,typeComply,defaultValue,alternN),
      elemComply_(elemeComply)
    ,keyComply_(keyComply)
    {
      ABC_Type_of_Value::G::pushTypeOfKey(this,keyVar);
      ABC_Type_of_Value::G::pushTypeOfElement(this,elementVar);
    }


  protected:
    typeElementPredicate elemComply_;
    typeKeyPredicate keyComply_;

    // ABC_Type_of_Value interface
  public:

    // ABC_Typed_Value interface
  public:
    virtual bool put(const Implements_ComplexVar_New *cm, const std::pair<K,T> &v, ABC_Output *ostream, std::__cxx11::string *error, const std::__cxx11::string &masterObjective) const
    {

    }
    virtual bool get(const Implements_ComplexVar_New *cm, std::pair<K,T> &v, ABC_Input *istream, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const
    {

    }
  };



  template<typename K, typename T>
  class Implements_Data_Type_New_pair
      :public Implements_Dictionary_Type_New<K,T,std::pair>
  {
  public:

    using typePredicate=typename Implements_Base_Type_New<std::pair<K,T>>::typePredicate;

    using typetypePredicate=typename Implements_Base_Type_New<std::pair<K,T>>::typetypePredicate;
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


    virtual ~Implements_Data_Type_New_pair(){}

    virtual buildByToken<std::pair<K,T>> *getBuildByToken(const Implements_ComplexVar_New *cm) const override
    {
      return new buildByToken<std::pair<K,T>>(cm,this);
    }

    Implements_Data_Type_New_pair(const Implements_ComplexVar_New* parent,
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
                             ,getSet alternN):
      Implements_Dictionary_Type_New<K,T,std::pair>
      (parent,id,var,tip,whatthis,keyVar,elementVar,complyPred,typeComply,keyComply
       ,elemeComply,defaultValue,alternN)
    {
    }
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

    using typePredicate=typename Implements_Base_Type_New<std::map<K,T>>::typePredicate;
    using typetypePredicate=typename Implements_Base_Type_New<std::map<K,T>>::typetypePredicate;
    using typeValue=typename Implements_Base_Type_New<std::map<K,T>>::typeValue;
    using getSet=typename Implements_Base_Type_New<std::set<T>>::getSet;

    using typeElementPredicate= typename Implements_Dictionary_Type_New<K,T,My_map>::typeElementPredicate;

    using typeKeyPredicate= typename Implements_Dictionary_Type_New<K,T,My_map>::typeKeyPredicate;

    using pairPredicate= bool(*)(const Implements_ComplexVar_New*,const std::map<K,T> &,const std::pair<K,T>&,const Implements_ComplexVar_New*, std::string *WhyNot, const std::string& objective);




    virtual bool put(const Implements_ComplexVar_New* cm,const std::map<K,T>& v,ABC_Output* ostream,std::string* whyNot,const std::string &masterObjective)const override
    {
      if (this->isVarInDomain(cm,v,whyNot,masterObjective))
        {
          const Implements_Data_Type_New<K>* ktype=this->getKeyDataType(cm);

          const Implements_Data_Type_New<T>* etype=this->getElementDataType(cm);
          ostream->put("\n{");
          for (auto& e: v)
            {
              if(!ktype->put(cm,e.first,ostream,whyNot,masterObjective))
                {
                  ostream->put(*whyNot);
                  return false;
                }
              ostream->put(":\t");
              if(!etype->put(cm,e.second,ostream,whyNot,masterObjective))
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
    virtual bool get(const Implements_ComplexVar_New* cm,std::map<K,T>& v, ABC_Input* istream,std::string* whyNot ,const std::string &masterObjective)const override
    {
      char c;
      const Implements_Data_Type_New<K>* ktype=this->getKeyDataType(cm);

      const Implements_Data_Type_New<T>* etype=this->getElementDataType(cm);
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
              if (!ktype->get(cm,k,istream,whyNot,masterObjective))
                return false;
              else if (!istream->nextCharIs(':',c))
                {
                  *whyNot=masterObjective+ ": expected \":\" found: "+c;
                }
              else if (!etype->get(cm,d,istream,whyNot,masterObjective))
                return false;
              else
                {
                  v.insert({std::move(k),std::move(d)});
                }
            }
          if (!this->isVarInDomain(cm,v,whyNot,masterObjective))
            return false;
          else
            return true;
        }

    }




    static std::string ClassName()
    {
      return "Implements_Data_Type_New_of_"+Cls<std::map<K,T>>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }



    virtual buildByToken<std::map<K,T>>* getBuildByToken(
        const Implements_ComplexVar_New* cm)const
    {
      return new buildByToken<std::map<K,T>>(cm,this);
    }

    virtual ~Implements_Data_Type_New_map(){}

    Implements_Data_Type_New_map(const Implements_ComplexVar_New* parent,
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
                             ,getSet alternN):
      Implements_Dictionary_Type_New<K,T,My_map>
      (parent,id,var,tip,whatthis,keyVar,elementVar,complyPred,typeComply,keyComply
       ,elemeComply,defaultValue,alternN)
    {
    }

  };


  class Implements_Data_Type_New_string
      : public Implements_Base_Type_New<std::string>
  {
  public:


    static void push_VarTypes(Implements_ComplexVar_New* cm)
    {
      cm->pushType(new Implements_Data_Type_New_string(cm));

    }

    using typePredicate=typename Implements_Base_Type_New<std::string>::typePredicate;
    using typetypePredicate=typename Implements_Base_Type_New<std::string>::typetypePredicate;
    using typeValue=typename Implements_Base_Type_New<std::string>::typeValue;
    using getSet=typename Implements_Base_Type_New<std::string>::getSet;

    //    using V=typename Implements_ComplexVar_New::V;


    static std::string ClassName()
    {
      return "Implements_Data_Type_New"+Cls<std::string>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }


    virtual buildByToken<std::string>* getBuildByToken(
        const Implements_ComplexVar_New* cm)const;


    virtual ~Implements_Data_Type_New_string(){}

    virtual bool put(const Implements_ComplexVar_New* cm,
                     const std::string& v,ABC_Output* ostream,std::string* whyNot
                     ,const std::string& masterObjective)const override
    {
      if (isVarInDomain(cm,v,whyNot,masterObjective))
        {
          ostream->put(v);
          return true;
        }
      else return false;
    }
    virtual bool get(const Implements_ComplexVar_New* cm
                     ,std::string& v, ABC_Input* istream,std::string* whyNot
                     ,const std::string& masterObjective)const override
    {

      if (!istream->get(v,whyNot,masterObjective))
        return false;
      else
        return isVarInDomain(cm,v,whyNot,masterObjective);
    }


    Implements_Data_Type_New_string(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis
                             ,const std::string& unknownVal
                             ,typePredicate complyPred
                             ,typetypePredicate typeComply
                             ,typeValue  defaultValue
                             ,getSet alterNext):
      Implements_Base_Type_New<std::string>(parent,id,var,tip,whatthis,unknownVal
                                            ,complyPred,typeComply,defaultValue,alterNext){}


    Implements_Data_Type_New_string(const Implements_ComplexVar_New *parent):
      Implements_Base_Type_New<std::string>(parent){}






  };


  class Implements_Data_Type_New_ABC_Var_New:
      public Implements_Base_Type_New<ABC_Var_New*>

  {

  public:
    using typetypePredicate=typename Implements_Base_Type_New<ABC_Var_New*>::typetypePredicate;
    using typeValue=typename Implements_Base_Type_New<ABC_Var_New*>::typeValue;


    static std::string ClassName()
    {
      return "Implements_Data_Type_New_of"+ABC_Var_New::ClassName();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }


    virtual bool isVarInDomain(const Implements_ComplexVar_New* cm,const ABC_Var_New* const val, std::string *whyNot,const std::string& masterObjective ) const override;



    virtual bool put(const Implements_ComplexVar_New* cm,
                     const ABC_Var_New* v,ABC_Output* ostream
                     ,std::string* whyNot
                     ,const std::string& masterObjective)const override
    {
      if (isVarInDomain(cm,v,whyNot,masterObjective))
        {
          ostream->put(v->id()+":"+v->myType()+"=");
          const ABC_Type_of_Value* t=cm->idToType(v->myType(),whyNot,masterObjective);
          if (t==nullptr)
            return false;
          else
            {
              return t->put(cm,v->value(),ostream,whyNot,masterObjective);
            }
        }
      else return false;
    }
    virtual bool get(const Implements_ComplexVar_New* cm
                     ,ABC_Var_New*& v, ABC_Input* istream,std::string* whyNot
                     ,const std::string& masterObjective)const override;


    virtual ~Implements_Data_Type_New_ABC_Var_New(){}


    Implements_Data_Type_New_ABC_Var_New(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis
                             , const Implements_Data_Type_New<std::string>* idType
                             , const Implements_Data_Type_New<std::string>* varType
                             ,typetypePredicate typeComply):
      Implements_Base_Type_New<ABC_Var_New*>(
        parent,id,var,tip,whatthis,nullptr,
        nullptr,typeComply,nullptr,nullptr),
      idType_(idType),varType_(varType)
    {
    }

    virtual buildByToken<std::string>*
    getNewIdentifierBuildByToken(const Implements_ComplexVar_New* cm)const
    {

      return new buildByToken<std::string> (cm,idType_);
    }


    virtual buildByToken<std::string>* getVarIdentifierBuildByToken(const Implements_ComplexVar_New* cm, const std::string id)const
    {
      std::string whyNot;

      const ABC_Type_of_Value * t=cm->idToType(id,&whyNot,"");
      if (t!=nullptr)
        {
          const Implements_Data_Type_New<std::string>* vt=t->getSelfIdType();

          return new buildByToken<std::string> (cm,vt);
        }
      else
        return nullptr;
    }
    virtual buildByToken<std::string>* getVarIdentifierBuildByToken(const Implements_ComplexVar_New* cm)const
    {
      return new buildByToken<std::string>(cm,varType_);
    }

    virtual buildByToken<ABC_Var_New*>* getBuildByToken(const Implements_ComplexVar_New* cm)const override
    {
      return new buildByToken<ABC_Var_New*>(cm,this);
    }

  private:
    const Implements_Data_Type_New<std::string>* idType_;
    const Implements_Data_Type_New<std::string>* varType_;

  };


  class Implements_Data_Type_New_map_string_ABC_Var_New
      :public Implements_Container_Type_New<ABC_Var_New*,String_map>
  {
  public:

    using typePredicate=typename Implements_Base_Type_New<std::map<std::string,ABC_Var_New*>>::typePredicate;

    using typetypePredicate=typename Implements_Base_Type_New<std::map<std::string,ABC_Var_New*>>::typetypePredicate;
    using typeValue=typename Implements_Base_Type_New<std::map<std::string,ABC_Var_New*>>::typeValue;
    using getSet=typename Implements_Base_Type_New<std::set<std::string>>::getSet;

    using typeElementPredicate= typename Implements_Container_Type_New<ABC_Var_New*,String_map>::typeElementPredicate;



    virtual bool put(const Implements_ComplexVar_New* cm,const std::map<std::string,ABC_Var_New*>& v,ABC_Output* ostream,std::string* whyNot,const std::string &masterObjective)const override
    {
      if (this->isVarInDomain(cm,v,whyNot,masterObjective))
        {
          const Implements_Data_Type_New<ABC_Var_New*>* etype
              =this->getElementDataType(cm);
          ostream->put("\n{");
          for (auto& e: v)
            {
              if(!etype->put(cm,e.second,ostream,whyNot,masterObjective))
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
    virtual bool get(const Implements_ComplexVar_New* cm,std::map<std::string,ABC_Var_New*>& v, ABC_Input* istream,std::string* whyNot ,const std::string &masterObjective)const override
    {
      char c;

      const Implements_Data_Type_New<ABC_Var_New*>* etype=this->getElementDataType(cm);
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
              ABC_Var_New* d;
              if (!etype->get(cm,d,istream,whyNot,masterObjective))
                return false;
              else
                {
                  v.insert({d->id(),d});
                }
            }
          if (!this->isVarInDomain(cm,v,whyNot,masterObjective))
            return false;
          else
            return true;
        }

    }




    static std::string ClassName()
    {
      return "Implements_Data_Type_New_of_"+Cls<std::map<std::string,ABC_Var_New*>>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }



    virtual buildByToken<std::map<std::string,ABC_Var_New*>>* getBuildByToken(
        const Implements_ComplexVar_New* cm)const override
    {
      return new buildByToken<std::map<std::string,ABC_Var_New*>>(cm,this);
    }

    virtual ~Implements_Data_Type_New_map_string_ABC_Var_New(){}

    Implements_Data_Type_New_map_string_ABC_Var_New(const Implements_ComplexVar_New* parent,
                             const std::string& id
                             ,const std::string& var
                             ,const std::string& tip
                             ,const std::string& whatthis
                             , const std::string vartype
                             ,typePredicate complyPred
                             ,typetypePredicate typeComply
                             ,typeElementPredicate elemeComply
                             ,typeValue  defaultValue
                             ,getSet alternN):
      Implements_Container_Type_New<Markov_IO_New::ABC_Var_New *, String_map>
      (parent,id,var,tip,whatthis,vartype,complyPred,typeComply
       ,elemeComply,defaultValue,alternN)
    {
    }

  };


  };

  class Identifier{
    class S {
    public:

      static bool comply_id_valid(const Implements_ComplexVar_New* p,
                                  const std::string& idCandidate,
                                  const Implements_ComplexVar_New* self,
                                  std::string *WhyNot, const std::string& objective)
      {
        if (Token_New::toKeyword(idCandidate)!=Token_New::IDENTIFIER)
          {
            *WhyNot=objective+": "+idCandidate+" is not an identifier";
            return false;
          }
        else
          return true;
      }



      static bool comply_id_New(const Implements_ComplexVar_New* p,
                                const std::string& idCandidate,
                                const Implements_ComplexVar_New* self,
                                std::string *WhyNot, const std::string &objective)
      {
        return p->isNameUnOcuppied(idCandidate,WhyNot,objective,true);
      }

      static bool comply_id_Used(const Implements_ComplexVar_New* p,
                                 const std::string& idCandidate,
                                 const Implements_ComplexVar_New* self,
                                 std::string *WhyNot, const std::string &objective)
      {
        return p->hasName(idCandidate,WhyNot,objective,true);
      }

      static bool comply_id_Var(const Implements_ComplexVar_New* p,
                                const std::string& idCandidate,
                                const Implements_ComplexVar_New* self,
                                std::string *WhyNot, const std::string &objective)
      {
        return p->hasName(idCandidate,WhyNot,objective,true);
      }

      static bool comply_id_Type(const Implements_ComplexVar_New* p,
                                 const std::string& idCandidate,
                                 const Implements_ComplexVar_New* self,
                                 std::string *WhyNot, const std::string &objective)
      {
        return p->hasType(idCandidate,WhyNot,objective,true);
      }

      static bool comply_id_Var_T(const Implements_ComplexVar_New* p,
                                  const std::string& idCandidate,
                                  const Implements_ComplexVar_New* self,
                                  std::string *WhyNot, const std::string &objective)
      {
        std::string varType=G::gettypeOfId(self);
        return p->hasNameofType(idCandidate,varType,WhyNot,objective,true);
      }

      static bool comply_id_Type_T(const Implements_ComplexVar_New* p,
                                   const std::string& idCandidate,
                                   const Implements_ComplexVar_New* self,
                                   std::string *WhyNot, const std::string &objective)
      {
        std::string typeType=G::gettypeOfId(self);
        return p->hasTypeofType(idCandidate,typeType,WhyNot,objective,true);
      }

      static bool comply_id_Field(const Implements_ComplexVar_New* p,
                                  const std::string& idCandidate,
                                  const Implements_ComplexVar_New* self,
                                  std::string *WhyNot
                                  , const std::string &objective)
      {
        std::string cvname=G::getComplexVarId(self);
        const Implements_ComplexVar_New* cm
            =dynamic_cast<const Implements_ComplexVar_New*>(p->idToVar(cvname,WhyNot));
        if (cm==nullptr)
          {
            *WhyNot=objective+": "+cvname+ "is not an "+Implements_ComplexVar_New::ClassName();

            return false;
          }

        return cm->hasName(idCandidate,WhyNot,objective,false)&&
            p->hasName(idCandidate,WhyNot,objective,false);
      }


      static bool comply_id_New_Field(const Implements_ComplexVar_New* p,
                                      const std::string& idCandidate,
                                      const Implements_ComplexVar_New* self,
                                      std::string *WhyNot
                                      , const std::string& objective)
      {
        std::string cvname=G::getComplexVarId(self);
        const Implements_ComplexVar_New* cm
            =dynamic_cast<const Implements_ComplexVar_New*>(p->idToVar(cvname,WhyNot));
        if (cm==nullptr)
          {
            *WhyNot=objective+": "+cvname+ "is not an "+Implements_ComplexVar_New::ClassName();

            return false;
          }

        return cm->hasName(idCandidate,WhyNot,objective,false)&&
            p->isNameUnOcuppied(idCandidate,WhyNot,objective,false);
      }



      static bool typeComply_id_valid(
          const Implements_ComplexVar_New* p,
          const Implements_Data_Type_New<std::string>* idtype,
          const Implements_ComplexVar_New* self,
          std::string *WhyNot,
          const std::string& objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::idValid())==0)
          return true;
        else
          {
            *WhyNot=objective+": "+idtype->myType()+" is not "+V::idValid();

            return false;
          }
      }
      static bool typeComply_id_Used(const Implements_ComplexVar_New* p,
                                     const Implements_Data_Type_New<std::string>* idtype,
                                     const Implements_ComplexVar_New* self,
                                     std::string *WhyNot,
                                     const std::string& objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::idUsed())==0)
          return true;
        else
          {
            *WhyNot=objective+": "+idtype->myType()+" is not "+V::idUsed();

            return false;
          }
      }

      static bool typeComply_id_New(const Implements_ComplexVar_New* p,
                                    const Implements_Data_Type_New<std::string>* idtype,
                                    const Implements_ComplexVar_New* self,
                                    std::string *WhyNot, const std::string &objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::idNew())==0)
          return true;
        else
          {
            *WhyNot=objective+": "+idtype->myType()+" is not "+V::idNew();

            return false;
          }
      }

      static bool typeComply_id_New_Var(const Implements_ComplexVar_New* p,
                                        const Implements_Data_Type_New<std::string>* idtype,
                                        const Implements_ComplexVar_New* self,
                                        std::string *WhyNot, const std::string &objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::idNewVar())==0)
          return true;
        else
          {
            *WhyNot=objective+": "+idtype->myType()+" is not "+V::idNewVar();

            return false;
          }
      }

      static bool typeComply_id_New_Type(const Implements_ComplexVar_New* p,
                                         const Implements_Data_Type_New<std::string>* idtype,
                                         const Implements_ComplexVar_New* self,
                                         std::string *WhyNot, const std::string &objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::idNewType())==0)
          return true;
        else
          {
            *WhyNot=objective+": "+idtype->myType()+" is not "+V::idNewType();

            return false;
          }
      }



      static bool typeComply_id_Var(const Implements_ComplexVar_New* p,
                                    const Implements_Data_Type_New<std::string>* idtype,
                                    const Implements_ComplexVar_New* self,
                                    std::string *WhyNot, const std::string &objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::idVar())==0)
          return true;
        else
          {
            *WhyNot=objective+": "+idtype->myType()+" is not "+V::idVar();

            return false;
          }
      }
      static bool typeComply_id_Type(const Implements_ComplexVar_New* p,
                                     const Implements_Data_Type_New<std::string>* idtype,
                                     const Implements_ComplexVar_New* self,
                                     std::string *WhyNot, const std::string &objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::idType())==0)
          return true;
        else
          {
            *WhyNot=objective+": "+idtype->myType()+" is not "+V::idType();

            return false;
          }
      }
      static bool typeComply_id_Var_T(const Implements_ComplexVar_New* p,
                                      const Implements_Data_Type_New<std::string>* idtype,
                                      const Implements_ComplexVar_New* self,
                                      std::string *WhyNot, const std::string &objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::idVar())==0)
          {
            std::string varself=G::gettypeOfId(self);
            std::string vartest=G::gettypeOfId(idtype);

            const ABC_Type_of_Value *tself=p->idToType(varself,WhyNot,objective);
            return tself->includesThisType(p,vartest,WhyNot,objective);
          }
        else
          {
            *WhyNot=objective+": "+idtype->myType()+ "is not a "+V::idVar();
            return false;
          }
      }


      static bool typeComply_id_Type_T(const Implements_ComplexVar_New* p,
                                       const Implements_Data_Type_New<std::string>* idtype,
                                       const Implements_ComplexVar_New* self,
                                       std::string *WhyNot, const std::string &objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::idType())==0)
          {
            std::string varself=G::gettypeOfId(self);
            std::string vartest=G::gettypeOfId(idtype);

            const ABC_Type_of_Value *tself=p->idToType(varself,WhyNot,objective);
            return tself->includesThisType(p,vartest,WhyNot,objective);
          }
        else
          {
            *WhyNot=objective+": "+idtype->myType()+ "is not a "+V::idType();
            return false;
          }
      }

      static bool typeComply_id_Field(const Implements_ComplexVar_New* p,
                                      const Implements_Data_Type_New<std::string>* idtype,
                                      const Implements_ComplexVar_New* self,
                                      std::string *WhyNot, const std::string &objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::idField())==0)
          {
            std::string varself=G::getComplexVarId(self);
            std::string vartest=G::getComplexVarId(idtype);

            const ABC_Type_of_Value *tself=p->idToType(varself,WhyNot,objective);
            return tself->includesThisType(p,vartest,WhyNot,objective);
          }
        else
          {
            *WhyNot=objective+": "+idtype->myType()+ "is not a "+V::idField();
            return false;
          }
      }







      static bool typeComply_id_New_Var_T(const Implements_ComplexVar_New* p,
                                          const Implements_Data_Type_New<std::string>* idtype,
                                          const Implements_ComplexVar_New* self,
                                          std::string *WhyNot, const std::string &objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::idNewVar())==0)
          {
            std::string varself=G::gettypeOfId(self);
            std::string vartest=G::gettypeOfId(idtype);

            const ABC_Type_of_Value *tself=p->idToType(varself,WhyNot,objective);
            return tself->includesThisType(p,vartest,WhyNot,objective);
          }
        else
          {
            *WhyNot=objective+": "+idtype->myType()+ "is not a "+V::idNewVar();
            return false;
          }
      }


      static bool typeComply_id_New_Type_T(const Implements_ComplexVar_New* p,
                                           const Implements_Data_Type_New<std::string>* idtype,
                                           const Implements_ComplexVar_New* self,
                                           std::string *WhyNot, const std::string &objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::idNewType())==0)
          {
            std::string varself=G::gettypeOfId(self);
            std::string vartest=G::gettypeOfId(idtype);

            const ABC_Type_of_Value *tself=p->idToType(varself,WhyNot,objective);
            return tself->includesThisType(p,vartest,WhyNot,objective);
          }
        else
          {
            *WhyNot=objective+": "+idtype->myType()+ "is not a "+V::idNewType();
            return false;
          }
      }

      static bool typeComply_id_New_Field(const Implements_ComplexVar_New* p,
                                          const Implements_Data_Type_New<std::string>* idtype,
                                          const Implements_ComplexVar_New* self,
                                          std::string *WhyNot
                                          , const std::string &objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::idNewField())==0)
          {
            std::string varself=G::getComplexVarId(self);
            std::string vartest=G::getComplexVarId(idtype);

            const ABC_Type_of_Value *tself=p->idToType(varself,WhyNot,objective);
            return tself->includesThisType(p,vartest,WhyNot,objective);
          }
        else
          {
            *WhyNot=objective+": "+idtype->myType()+ "is not a "+V::idNewField();
            return false;
          }
      }


      static std::set<std::string> suggested_id_Valid(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        return suggested_id_Used(cm,self)+
            suggested_id_New_Var(cm,self);
      }


      static std::set<std::string> suggested_id_Var(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        return cm->getIdsOfVarType("",true);
      }



      static std::set<std::string> suggested_id_Type(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        return cm->getIdsOfTypeType("",true);
      }


      static std::set<std::string> suggested_id_Used(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        return suggested_id_Var(cm,self)+
            suggested_id_Type(cm,self);
      }



      static std::set<std::string> suggested_id_Type_T(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        std::string typeType=G::gettypeOfId(self);
        return cm->getIdsOfTypeType(typeType,true);
      }

      static std::set<std::string> suggested_id_Var_T(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        std::string varType=G::gettypeOfId(self);
        return cm->getIdsOfVarType(varType,true);
      }



      static std::set<std::string> suggested_id_New_Var(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        auto sv= cm->getIdsOfVarType("",false);
        auto st=cm->getIdsOfTypeType("",true);
        std::set<std::string> o;
        for (auto& e:sv)
          {
            o.insert(nextId(e));
          }
        for (auto& e:st)
          {
            std::string s="my"+e;
            std::string w;
            if (cm->isNameUnOcuppied(s,&w,"",true))
              o.insert(s);
          }
        return o;
      }

      static std::set<std::string> suggested_id_New_Type(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        auto st=cm->getIdsOfTypeType("",false);
        std::set<std::string> o;
        for (auto& e:st)
          {
            o.insert(nextId(e));
          }
        return o;
      }


      static std::set<std::string> suggested_id_New(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        return suggested_id_New_Var(cm,self)+suggested_id_New_Type(cm,self);
      }




      static std::set<std::string> suggested_id_New_Var_T(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        std::string varType=G::gettypeOfId(self);
        auto sv= cm->getIdsOfVarType(varType,false);
        auto st=cm->getIdsOfTypeType(varType,true);
        std::set<std::string> o;
        for (auto& e:sv)
          {
            o.insert(nextId(e));
          }
        for (auto& e:st)
          {
            std::string s="my"+e;
            std::string w;
            if (cm->isNameUnOcuppied(s,&w,"",true))
              o.insert(s);
          }
        return o;
      }

      static std::set<std::string> suggested_id_New_Type_T(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        std::string typetype=G::gettypeOfId(self);

        auto st=cm->getIdsOfTypeType(typetype,false);
        std::set<std::string> o;
        for (auto& e:st)
          {
            o.insert(nextId(e));
          }
        return o;
      }

      static std::set<std::string> suggested_id_Field(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        std::string cvname=G::getComplexVarId(self);
        std::string WhyNot;
        const Implements_ComplexVar_New* cv
            =dynamic_cast<const Implements_ComplexVar_New*>(self->idToVar(cvname,&WhyNot));
        if (cv==nullptr)
          {
            return {};
          }
        else
          {
            std::set<std::string> o;
            auto s=cv->getIdsOfTypeType("",false);
            std::string w;
            for (auto &e: s)
              {

                if (cm->hasName(e,&w,"",false))
                  o.insert(e);
              }
            return o;
          }
      }

      static std::set<std::string> suggested_id_New_Field(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        std::string cvname=G::getComplexVarId(self);
        std::string WhyNot;
        const Implements_ComplexVar_New* cv
            =dynamic_cast<const Implements_ComplexVar_New*>(self->idToVar(cvname,&WhyNot));
        if (cv==nullptr)
          {
            return {};
          }
        else
          {
            std::set<std::string> o;
            auto s=cv->getIdsOfTypeType("",false);
            std::string w;
            for (auto &e: s)
              {

                if (!cm->hasName(e,&w,"",false))
                  o.insert(e);
              }
            return o;
          }
      }



      static std::string default_id_Used(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        return cm->defaultIdOfVarType("",true);
      }

      static std::string default_id_Var(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        return cm->defaultIdOfVarType("",true);
      }

      static std::string default_id_Type(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        return cm->defaultIdOfTypeType("",true);
      }

      static std::string default_id_Type_T(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        std::string typeType=G::gettypeOfId(self);
        return cm->defaultIdOfTypeType(typeType,true);
      }

      static std::string default_id_Var_T(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        std::string varType=G::gettypeOfId(self);
        return cm->defaultIdOfVarType(varType,true);
      }



      static std::string default_id_New_Var(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        std::string s= cm->defaultIdOfVarType("",false);
        if (s.empty())
          {
            s="my"+cm->defaultIdOfTypeType("",true);
            return s;

          }
        else
          {
            return nextId(s);
          }
      }

      static std::string default_id_New_Type(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        auto st=cm->defaultIdOfTypeType("",false);
        return nextId(st);
      }




      static std::string default_id_New_Var_T(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        std::string varType=G::gettypeOfId(self);
        auto sv= cm->defaultIdOfVarType(varType,true);
        if (sv.empty())
          {
            auto st=cm->defaultIdOfTypeType(varType,true);
            return "my"+st;
          }
        else
          return nextId(sv);
      }

      static std::string default_id_New_Type_T(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        std::string typetype=G::gettypeOfId(self);

        auto st=cm->defaultIdOfTypeType(typetype,false);
        return nextId(st);
      }

      static std::string default_id_Field(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        auto s=suggested_id_Field(cm,self);
        if (s.empty())
          return {};
        else return *s.begin();
      }

      static std::string default_id_New_Field(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* self)
      {
        auto s=suggested_id_New_Field(cm,self);
        if (s.empty())
          return {};
        else return *s.begin();

      }

    };

  public:
    using G=ABC_Type_of_Value::G;

    class V
    {
    public:
      static std::string idValid(){return "_id";}
      static std::string idNew(){return idValid()+"New";}
      static std::string idNewVar(){return idNew()+"Var";}
      static std::string idNewType(){return idNew()+"Type";}
      static std::string idNewField(){return idNew()+"Field";}
      static std::string idUsed(){return idValid()+"Used";}
      static std::string idVar(){return idUsed()+"Var";}
      static std::string idType(){return idUsed()+"Type";}

      static std::string idField(){return idUsed()+"Field";}

    };


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


    static Implements_Data_Type_New<std::string>*
    create_IdValid(const Implements_ComplexVar_New* parent)
    {
      return new Implements_Data_Type_New<std::string>(
            parent,
            V::idValid()
            ,"_string"
            ,"valid identifier"
            ,"any valid identifier used or not"
            ,""
            ,&S::comply_id_valid
            ,&S::typeComply_id_valid
            ,&S::default_id_Used
            ,&S::suggested_id_Used);
    }

    static Implements_Data_Type_New<std::string>*
    create_IdUsed(const Implements_ComplexVar_New* parent)
    {
      return new Implements_Data_Type_New<std::string>(
            parent,
            V::idUsed()
            ,V::idValid()
            ,"valid identifier"
            ,"any valid identifier used or not"
            ,""
            ,&S::comply_id_Used
            ,&S::typeComply_id_Used
            ,&S::default_id_Used
            ,&S::suggested_id_Used);
    }


    static Implements_Data_Type_New<std::string>*
    create_IdVar(const Implements_ComplexVar_New* parent)
    {
      return new Implements_Data_Type_New<std::string>(
            parent,
            V::idVar()
            ,V::idUsed()
            ,"used identifier for a variable"
            ,"any valid identifier used or not"
            ,""
            ,&S::comply_id_Var
            ,&S::typeComply_id_Var
            ,&S::default_id_Var
            ,&S::suggested_id_Var);
    }

    static Implements_Data_Type_New<std::string>*
    create_IdVar(const Implements_ComplexVar_New* parent,const std::string& varType)
    {
      auto o= new Implements_Data_Type_New<std::string>(
            parent,
            V::idVar()+varType
            ,V::idVar()
            ,"used identifier for a variable of type "+varType
            ,"any valid identifier used or not"
            ,""
            ,&S::comply_id_Var_T
            ,&S::typeComply_id_Var_T
            ,&S::default_id_Var_T
            ,&S::suggested_id_Var_T);

      G::pushTypeOfId(o,varType);
    }

    static Implements_Data_Type_New<std::string>*
    create_IdType(const Implements_ComplexVar_New* parent)
    {
      return new Implements_Data_Type_New<std::string>(
            parent,
            V::idType()
            ,V::idUsed()
            ,"used identifier for a variable"
            ,"any valid identifier used or not"
            ,""
            ,&S::comply_id_Type
            ,&S::typeComply_id_Type
            ,&S::default_id_Type
            ,&S::suggested_id_Type);
    }

    static Implements_Data_Type_New<std::string>*
    create_IdType(const Implements_ComplexVar_New* parent,
                  const std::string& varType)
    {
      auto o= new Implements_Data_Type_New<std::string>(
            parent,
            V::idType()+varType
            ,V::idType()
            ,"used identifier for a type of type "+varType
            ,"any valid identifier used or not"
            ,""
            ,&S::comply_id_Type_T
            ,&S::typeComply_id_Type_T
            ,&S::default_id_Type_T
            ,&S::suggested_id_Type_T);
      G::pushTypeOfId(o,varType);
    }

    static Implements_Data_Type_New<std::string>*
    create_IdField(const Implements_ComplexVar_New* parent,
                   const std::string& complexVar)
    {
      auto o= new Implements_Data_Type_New<std::string>(
            parent,
            V::idField()+complexVar
            ,V::idUsed()
            ,"used identifier for a type of type "+complexVar
            ,"any valid identifier used or not"
            ,""
            ,&S::comply_id_Field
            ,&S::typeComply_id_Field
            ,&S::default_id_Field
            ,&S::suggested_id_Field);
      G::pushComplexVarId(o,complexVar);
    }



    static Implements_Data_Type_New<std::string>*
    create_IdNew(const Implements_ComplexVar_New* parent)
    {
      return new Implements_Data_Type_New<std::string>(
            parent,
            V::idNew()
            ,V::idValid()
            ,"unused identifier"
            ,"any valid identifier used or not"
            ,""
            ,&S::comply_id_New
            ,&S::typeComply_id_New
            ,&S::default_id_New_Var
            ,&S::suggested_id_New);
    }


    static Implements_Data_Type_New<std::string>*
    create_IdNewVar(const Implements_ComplexVar_New* parent)
    {
      return new Implements_Data_Type_New<std::string>(
            parent,
            V::idNewVar()
            ,V::idNew()
            ,"used identifier for a variable"
            ,"any valid identifier used or not"
            ,""
            ,&S::comply_id_New
            ,&S::typeComply_id_New_Var
            ,&S::default_id_New_Var
            ,&S::suggested_id_New_Var);
    }

    static Implements_Data_Type_New<std::string>*
    create_IdNewVar(const Implements_ComplexVar_New* parent
                    ,const std::string& varType)
    {
      auto o= new Implements_Data_Type_New<std::string>(
            parent,
            V::idNewVar()+varType
            ,V::idNewVar()
            ,"used identifier for a variable of type "+varType
            ,"any valid identifier used or not"
            ,""
            ,&S::comply_id_New
            ,&S::typeComply_id_New_Var_T
            ,&S::default_id_New_Var_T
            ,&S::suggested_id_New_Var_T);

      G::pushTypeOfId(o,varType);
    }

    static Implements_Data_Type_New<std::string>*
    create_IdNewType(const Implements_ComplexVar_New* parent)
    {
      return new Implements_Data_Type_New<std::string>(
            parent,
            V::idNewType()
            ,V::idNew()
            ,"unused identifier for a variable"
            ,"any valid identifier used or not"
            ,""
            ,&S::comply_id_New
            ,&S::typeComply_id_New_Type
            ,&S::default_id_New_Type
            ,&S::suggested_id_New_Type);
    }

    static Implements_Data_Type_New<std::string>*
    create_IdNewType(const Implements_ComplexVar_New* parent,
                     const std::string& varType)
    {
      auto o= new Implements_Data_Type_New<std::string>(
            parent,
            V::idNewType()+varType
            ,V::idNewType()
            ,"used identifier for a type of type "+varType
            ,"any valid identifier used or not"
            ,""
            ,&S::comply_id_New
            ,&S::typeComply_id_New_Type_T
            ,&S::default_id_New_Type_T
            ,&S::suggested_id_New_Type_T);
      G::pushTypeOfId(o,varType);
    }

    static Implements_Data_Type_New<std::string>*
    create_IdNewField(const Implements_ComplexVar_New* parent,
                      const std::string& complexVar)
    {
      auto o= new Implements_Data_Type_New<std::string>(
            parent,
            V::idNewField()+complexVar
            ,V::idNew()
            ,"used identifier for a type of type "+complexVar
            ,"any valid identifier used or not"
            ,""
            ,&S::comply_id_New_Field
            ,&S::typeComply_id_New_Field
            ,&S::default_id_New_Field
            ,&S::suggested_id_New_Field);
      G::pushComplexVarId(o,complexVar);
    }




  };




  class Variable {
    class S {
    public:


      static bool typeComply_var_valid(
          const Implements_ComplexVar_New* p,
          const Implements_Data_Type_New<ABC_Var_New*>* idtype,
          const Implements_ComplexVar_New* self,
          std::string *WhyNot,
          const std::string& objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::varValid())==0)
          return true;
        else
          {
            *WhyNot=objective+": "+idtype->myType()+" is not "+V::varValid();

            return false;
          }
      }
      static bool typeComply_vard_Used(
          const Implements_ComplexVar_New* p,
          const Implements_Data_Type_New<ABC_Var_New*>* idtype,
          const Implements_ComplexVar_New* self,
          std::string *WhyNot,
          const std::string& objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::varUsed())==0)
          return true;
        else
          {
            *WhyNot=objective+": "+idtype->myType()+" is not "+V::varUsed();

            return false;
          }
      }

      static bool typeComply_var_New(const Implements_ComplexVar_New* p,
                                     const Implements_Data_Type_New<ABC_Var_New*>* idtype,
                                     const Implements_ComplexVar_New* self,
                                     std::string *WhyNot, const std::string &objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::varNew())==0)
          return true;
        else
          {
            *WhyNot=objective+": "+idtype->myType()+" is not "+V::varNew();

            return false;
          }
      }

      static bool typeComply_var_New_Var(const Implements_ComplexVar_New* p,
                                         const Implements_Data_Type_New<ABC_Var_New*>* idtype,
                                         const Implements_ComplexVar_New* self,
                                         std::string *WhyNot, const std::string &objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::varNewVar())==0)
          return true;
        else
          {
            *WhyNot=objective+": "+idtype->myType()+" is not "+V::varNewVar();

            return false;
          }
      }




      static bool typeComply_var_Var(const Implements_ComplexVar_New* p,
                                     const Implements_Data_Type_New<ABC_Var_New*>* idtype,
                                     const Implements_ComplexVar_New* self,
                                     std::string *WhyNot, const std::string &objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::varVar())==0)
          return true;
        else
          {
            *WhyNot=objective+": "+idtype->myType()+" is not "+V::varVar();

            return false;
          }
      }
      static bool typeComply_var_Var_T(
          const Implements_ComplexVar_New* p,
          const Implements_Data_Type_New<ABC_Var_New*>* idtype,
          const Implements_ComplexVar_New* self,
          std::string *WhyNot, const std::string &objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::varVar())==0)
          {
            std::string varself=G::gettypeOfId(self);
            std::string vartest=G::gettypeOfId(idtype);

            const ABC_Type_of_Value *tself=p->idToType(varself,WhyNot,objective);
            return tself->includesThisType(p,vartest,WhyNot,objective);
          }
        else
          {
            *WhyNot=objective+": "+idtype->myType()+ "is not a "+V::varVar();
            return false;
          }
      }



      static bool typeComply_var_Field(
          const Implements_ComplexVar_New* p,
          const Implements_Data_Type_New<ABC_Var_New*>* idtype,
          const Implements_ComplexVar_New* self,
          std::string *WhyNot, const std::string &objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::varField())==0)
          {
            std::string varself=G::getComplexVarId(self);
            std::string vartest=G::getComplexVarId(idtype);

            const ABC_Type_of_Value *tself=p->idToType(varself,WhyNot,objective);
            return tself->includesThisType(p,vartest,WhyNot,objective);
          }
        else
          {
            *WhyNot=objective+": "+idtype->myType()+ "is not a "+V::varField();
            return false;
          }
      }







      static bool typeComply_var_New_Var_T(
          const Implements_ComplexVar_New* p,
          const Implements_Data_Type_New<ABC_Var_New*>* idtype,
          const Implements_ComplexVar_New* self,
          std::string *WhyNot, const std::string &objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::varNewVar())==0)
          {
            std::string varself=G::gettypeOfId(self);
            std::string vartest=G::gettypeOfId(idtype);

            const ABC_Type_of_Value *tself=p->idToType(varself,WhyNot,objective);
            return tself->includesThisType(p,vartest,WhyNot,objective);
          }
        else
          {
            *WhyNot=objective+": "+idtype->myType()+ "is not a "+V::varNewVar();
            return false;
          }
      }



      static bool typeComply_var_New_Field(
          const Implements_ComplexVar_New* p,
          const Implements_Data_Type_New<ABC_Var_New*>* idtype,
          const Implements_ComplexVar_New* self,
          std::string *WhyNot
          , const std::string &objective)
      {
        if (idtype->id()==self->id())
          return true;
        else if( idtype->myType().find(V::varNewField())==0)
          {
            std::string varself=G::getComplexVarId(self);
            std::string vartest=G::getComplexVarId(idtype);

            const ABC_Type_of_Value *tself=p->idToType(varself,WhyNot,objective);
            return tself->includesThisType(p,vartest,WhyNot,objective);
          }
        else
          {
            *WhyNot=objective+": "+idtype->myType()+ "is not a "+V::varNewField();
            return false;
          }
      }



    };

  public:
    using G=ABC_Type_of_Value::G;

    class V
    {
    public:
      static std::string varValid(){return "_var";}
      static std::string varNew(){return varValid()+"New";}
      static std::string varUsed(){return varValid()+"Used";}
      static std::string varVar(){return varUsed()+"Var";}
      static std::string varField(){return varUsed()+"Field";}
      static std::string varNewVar(){return varNew()+"Var";}
      static std::string varNewField(){return varNew()+"Field";}

    };



    static Implements_Data_Type_New<ABC_Var_New*>*
    create_varValid(const Implements_ComplexVar_New* parent)
    {
      return new Implements_Data_Type_New<ABC_Var_New*>(
            parent,
            V::varValid()
            ,V::varValid()
            ,"valid variable"
            ,"any valid variable existant or new"
            ,Identifier::create_IdValid(parent)
            ,Identifier::create_IdType(parent)
            ,&S::typeComply_var_valid);
    }


    static Implements_Data_Type_New<ABC_Var_New*>*
    create_varNew(const Implements_ComplexVar_New* parent)
    {
      return new Implements_Data_Type_New<ABC_Var_New*>(
            parent,
            V::varNew()
            ,V::varValid()
            ,"new variable"
            ,"any valid variable existant or new"
            ,Identifier::create_IdNewVar(parent)
            ,Identifier::create_IdType(parent)
            ,&S::typeComply_var_New);
    }

    static Implements_Data_Type_New<ABC_Var_New*>*
    create_varUsed(const Implements_ComplexVar_New* parent)
    {
      return new Implements_Data_Type_New<ABC_Var_New*>(
            parent,
            V::varUsed()
            ,V::varValid()
            ,"existant variable"
            ,"any existant variable"
            ,Identifier::create_IdVar(parent)
            ,Identifier::create_IdType(parent)
            ,&S::typeComply_vard_Used);
    }

    static Implements_Data_Type_New<ABC_Var_New*>*
    create_varVar(const Implements_ComplexVar_New* parent)
    {
      return new Implements_Data_Type_New<ABC_Var_New*>(
            parent,
            V::varVar()
            ,V::varUsed()
            ,"existant variable"
            ,"any existant variable"
            ,Identifier::create_IdVar(parent)
            ,Identifier::create_IdType(parent)
            ,&S::typeComply_var_Var);
    }

  };

  namespace _private {



  template<typename T>
  class Implements_Data_Type_class:public ABC_Typed_Value<T*>
  {
  public:

    using typePredicate= bool(*)(const Implements_ComplexVar_New*,const T&,const Implements_Data_Type_class<T>*, std::string*);

    using getEmptyObject=T*(*)(const Implements_Data_Type_class<T>*, std::string*);

    using plainPredicate
    = bool(*)(const std::map<std::string,ABC_Var_New*>*,const Implements_Data_Type_class<T>*, std::string*);

    using getEmptyMap=std::map<std::string,ABC_Var_New*>* (*)(const Implements_Data_Type_class<T>*, std::string*);

    using getCVMap=std::map<std::string,ABC_Var_New*>* (*)
    (const Implements_ComplexVar_New* cm,
    const T*
    , const Implements_Data_Type_class<T>*
    , std::string*, const std::string&);

    using getObject= T* (*)(const Implements_ComplexVar_New* cm,
    const std::map<std::string,ABC_Var_New*>&
    ,const Implements_Data_Type_class<T>*
    ,std::string*,
    const std::string& );


    static std::string ClassName()
    {
      return "Implements_Class_Type_New_of"+Cls<T>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }


    virtual bool put(const Implements_ComplexVar_New* cm
                     ,const T*& v,ABC_Output* ostream
                     ,std::string* error)const override
    {

      const Implements_ComplexVar_New* cv=this->
          ostream->put(*v);
      return true;
    }

    virtual bool get(Implements_ComplexVar_New* cm,T*& v, ABC_Input* istream,std::string* whyNot, std::string& MasterObjective )const;

    virtual std::set<std::string> alternativeNext(const Implements_ComplexVar_New* cm)const
    {
      return {};
    }

    virtual buildByToken<std::map<std::string,ABC_Var_New*>>* getBuildByToken(const Implements_ComplexVar_New* cm)const
    {
      return new buildByToken<std::map<std::string,ABC_Var_New*>>(cm,CVtype_);
    }


    virtual ~Implements_Data_Type_class(){}


    Implements_Data_Type_class(const Implements_ComplexVar_New* parent,
                              const std::string& id
                              ,const std::string& var
                              ,const std::string& tip
                              ,const std::string& whatthis
                              ,typePredicate complyPred
                              ,plainPredicate mapComply
                              ,getEmptyObject  defaultValue
                              ,getEmptyMap eMap
                              ,getCVMap map
                              ,getObject obj):
      ABC_Typed_Value<T>(parent,id,var,tip,whatthis)
    ,comply_(complyPred)
    ,mapComply_(mapComply)
    ,default_(defaultValue)
    ,toEMap_(eMap)
    ,toMap_(map)
    ,toObj_(obj)
    {}




    // ABC_Type_of_Value interface
  public:
    virtual Implements_Value_New<T>* empty_Value()const override
    {
      return new Implements_Value_New<T>();
    }


    virtual Implements_Var_New<T> *empty_Var(const Implements_ComplexVar_New *parent, const std::string &idN, const std::string &tip, const std::string &whathis) const override
    {
      return new Implements_Var_New<T>(parent,idN,this->id(),tip,whathis,empty_Value());
    }


    virtual Implements_Value_New<T> *default_Value(const Implements_ComplexVar_New* cm) const override
    {
      return Implements_Value_New<T>(getDefault_Valued(cm));
    }

    virtual Implements_Var_New<T> *default_Var(const Implements_ComplexVar_New *parent, const std::string &idN, const std::string &tip, const std::string &whathis) const override
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
    virtual Implements_Var_New<T>* getClassRep(
        const Implements_ComplexVar_New* cm,
        const Implements_ComplexVar_New *m
        , std::string *whyNot,
        const std::string& masterObjective) const override
    {
      T* o=getClass(cm,m->value()->getValued(),whyNot,masterObjective);
      if (o!=nullptr)
        return Implements_Var_New<T>
            (m->parent(),m->id(),m->myType(),o,m->Tip(),m->WhatThis());
      else
        return nullptr;

    }

    T* getClass(const Implements_ComplexVar_New* cm
                , std::map<std::string,ABC_Var_New*>  m
                ,std::string *WhyNot,const std::string& masterObjective)
    {
      return (*toObj_)(cm,m,this,WhyNot,masterObjective);
    }

    std::map<std::string,ABC_Var_New*>* getComplexMap(
        const Implements_ComplexVar_New* cm,
        const T* v,std::string *WhyNot,const std::string & masterObjective)
    {
      return (toMap_)(cm,v,this,WhyNot,masterObjective);
    }


    // ABC_Typed_Value interface
  public:
    virtual Implements_ComplexVar_New *getComplexVarTyeped_Rep(
        const Implements_ComplexVar_New* cm,
        const Implements_Var_New<T> *var, std::string *whyNot, const std::string& masterObjective) const override
    {
      std::map<std::string,ABC_Var_New*>* o=getComplexMap(cm,var->value()->getValued(),whyNot,masterObjective);
      return new Implements_ComplexVar_New
          (var->parent(),var->id(),var->myType(),*o,var->Tip(),var->WhatThis());
    }

  protected:
    typePredicate comply_;
    plainPredicate mapComply_;
    getEmptyObject default_;
    getEmptyMap toEMap_;
    getObject toObj_;
    getCVMap toMap_;
    Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>>* CVtype_;



  };

}
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

    using getObject= T (*)(const std::map<std::string,ABC_Var_New*>*,const _private::Implements_Data_Type_class<T>*,std::string*);


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
        return isVarInDomain(*v,whyNot);
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


    virtual Implements_Var_New<T> *empty_Var(const Implements_ComplexVar_New *parent, const std::string &idN, const std::string &tip, const std::string &whathis) const override
    {
      return new Implements_Var_New<T>(parent,idN,this->id(),tip,whathis,empty_Value());
    }


    virtual Implements_Value_New<T> *default_Value(const Implements_ComplexVar_New* cm) const override
    {
      return Implements_Value_New<T>(getDefault_Valued(cm));
    }

    virtual Implements_Var_New<T> *default_Var(const Implements_ComplexVar_New *parent, const std::string &idN, const std::string &tip, const std::string &whathis) const override
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
    virtual Implements_Var_New<T>* getClassRep(const Implements_ComplexVar_New *m, std::string *whyNot) const override
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
    virtual Implements_ComplexVar_New *getComplexVarTyeped_Rep(const Implements_Var_New<T> *var, std::string *whyNot) const override
    {

    }
  };

  class Markov_CommandManagerVar;



  class Implements_Command_Arguments: public Implements_ComplexVar_New
  {

  private:
    Implements_Command_Arguments(const Implements_ComplexVar_New* parent,
                              const std::string& id
                              ,const std::string& var
                              ,std::map<std::string,ABC_Var_New*> m
                                 ,const std::string& tip
                              ,const std::string& whatthis):
    Implements_ComplexVar_New(parent,id,var,m,tip,whatthis){}

  };


  class Implements_Command_Type_New:public ABC_Type_of_Value
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
      ABC_Type_of_Value
      (parent,id,var,tip,whatthis)
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


    Implements_Command_Arguments* getCommandField()const
    {

    }

    virtual Implements_Command_Arguments *empty_Var(const Implements_ComplexVar_New *parent, const std::string &idN, const std::string &tip, const std::string &whathis) const override
    {
    }


    virtual ABC_Value_New *default_Value(const Implements_ComplexVar_New* cm) const override
    {
    }

    virtual Implements_Command_Arguments *default_Var(const Implements_ComplexVar_New *parent, const std::string &idN, const std::string &tip, const std::string &whathis) const override
    {

    }




    // ABC_Type_of_Value interface
  public:
    virtual ABC_BuildByToken *getBuildByToken(const Implements_ComplexVar_New *cm) const override
    {

    }

    virtual std::set<std::__cxx11::string> alternativeNext(const Implements_ComplexVar_New *cm) const override{
      return {};
    }

    virtual bool includesThisType(const Implements_ComplexVar_New *cm, const std::__cxx11::string &childType, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const override;



    virtual ABC_Var_New *getClassRep(const Implements_ComplexVar_New *cvar, std::__cxx11::string *whyNot) const override
    {
      return nullptr;
    }



    // ABC_Type_of_Value interface
  public:
    virtual bool put(const Implements_ComplexVar_New *cm, const ABC_Value_New *v, ABC_Output *ostream, std::__cxx11::string *error, const std::__cxx11::string &masterObjective) const override;
    virtual bool get(const Implements_ComplexVar_New *cm, ABC_Value_New *&v, ABC_Input *istream, std::__cxx11::string *error, const std::__cxx11::string &masterObjective) const override;
     virtual ABC_Var_New *getVar(const Implements_ComplexVar_New *parent, const std::__cxx11::string &id, const std::__cxx11::string &mytype, const std::__cxx11::string &tip, const std::__cxx11::string &whathis, ABC_Value_New *v) const override;
    virtual bool isVarInDomain(const Implements_ComplexVar_New *cm, const ABC_Value_New *v, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const override;
    virtual bool isTypeInDomain(const Implements_ComplexVar_New *cm, const ABC_Type_of_Value *t, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const override;
    virtual Implements_ComplexVar_New *getComplexVarRep(const ABC_Var_New *var, std::__cxx11::string *whyNot, const std::__cxx11::string &masterObjective) const override;
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
  bool Implements_ComplexVar_New::insertChild(const std::string &id, const std::string &var, const std::string &tip, const std::string &whatthis, std::string *whyNot, const std::string& masterObjective)
  {
    if (!this->isNameUnOcuppied(id,whyNot,masterObjective,false))
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

  namespace _private {



  template<typename T, template<typename> class C>
  const Implements_Data_Type_New<T> *Implements_Container_Type_New<T,C>::getElementDataType(const Implements_ComplexVar_New *cm) const
  {
    const Implements_ComplexVar_New* self=this;
    return dynamic_cast<const Implements_Data_Type_New<T>*>(
          ABC_Type_of_Value::G::getElementType<T>(cm,self));
  }

  template<typename T>
  bool Implements_Base_Type_New<T>::includesThisType(const Implements_ComplexVar_New *cm, const std::string &childType, std::string *whyNot, const std::string &masterObjective) const
  {
    const ABC_Type_of_Value* ctype=cm->idToType(childType,whyNot,masterObjective);
    if (ctype==nullptr)
      return false;
    else
      {
        const Implements_Data_Type_New<T>*
            c=dynamic_cast<const Implements_Data_Type_New<T>*>(ctype);
        if (c==nullptr)
          {
            *whyNot=masterObjective+": "+ctype->id()+"is not a"+ this->id();
          }
        else
          return isTypeInDomain(cm,c,whyNot,masterObjective);

      }

  }


  template<typename T>
  bool Implements_Base_Type_New<T*>::includesThisType(const Implements_ComplexVar_New *cm, const std::string &childType, std::string *whyNot, const std::string &masterObjective) const
  {
    const ABC_Type_of_Value* ctype=cm->idToType(childType,whyNot,masterObjective);
    if (ctype==nullptr)
      return false;
    else
      {
        const Implements_Data_Type_New<T*>*
            c=dynamic_cast<const Implements_Data_Type_New<T*>*>(ctype);
        if (c==nullptr)
          {
            *whyNot=masterObjective+": "+ctype->id()+"is not a"+ this->id();
          }
        else
          return isTypeInDomain(cm,c,whyNot,masterObjective);

      }

  }


};



}

#include "Markov_IO/buildByToken.h"
namespace Markov_IO_New {
  template<typename T>
  buildByToken<T> *ABC_Type_of_Value::G::getElementBuildByToken(const Implements_ComplexVar_New *cm, const Implements_ComplexVar_New *self)
  {
    const Implements_Data_Type_New<T>* v= getElementType<T>(cm,self);
    if (v!=nullptr)
      return new buildByToken<T>(cm,v);
    else return nullptr;
  }


  template<typename T>
  buildByToken<T> *ABC_Type_of_Value::G::getKeyBuildByToken(const Implements_ComplexVar_New *cm, const Implements_ComplexVar_New *self)
  {
    const Implements_Data_Type_New<T>* v= getKeyType<T>(cm,self);
    if (v!=nullptr)
      return new buildByToken<T>(cm,v);
    else return nullptr;
  }


}





#endif // IMPLEMENTS_COMPLEXVAR_NEW_H
