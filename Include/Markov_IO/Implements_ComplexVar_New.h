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
    
    const ABC_Var_New* idToVar(const std::string& name, const std::string & typeName,std::string* whyNot, const std::string& masterObjective)const
    {
      auto it=vars_.find(name);
      if (it!=vars_.end())
        {
          ABC_Var_New* v=it->second;
          if (v->isOfThisType(this,typeName,whyNot,masterObjective))
            return v;
          else return nullptr;
        }
      else if (parent()!=nullptr)
        return  parent()->idToVar(name, typeName,whyNot,masterObjective);
      else
        {
          *whyNot=masterObjective+": "+name+" is not a var of "+id();
          return nullptr;
        }
    }
    
    
    const ABC_Var_New* idToVar(const std::string& name, std::string *whyNot)const
    {
      auto it=vars_.find(name);
      if (it!=vars_.end())
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
      auto it=vars_.find(name);
      if (it!=vars_.end())
        return it->second;
      else
        {
          *whyNot=masterObective+": "+name+" is not a var of "+id();
          return nullptr;
        }
    }
    
    virtual const ABC_Type_of_Value* idToType(const std::string& name, std::string *whyNot, const std::string& masterObjective)const
    {
      auto it=types_.find(name);
      if (it!=types_.end())
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
      auto it=types_.find(name);
      if (it!=types_.end())
        return it->second;
      else
        {
          *whyNot=objective;
          return nullptr;
        }
      
    }
    
    
    const Implements_Command_Type_New* idToCommand(const std::string& name, std::string *whyNot, const std::string& masterobjective)const
    {
      auto it=cmds_.find(name);
      if (it!=cmds_.end())
        return it->second;
      else if (this->parent()!=nullptr)
        return  parent()->idToCommand(name, whyNot,masterobjective);
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
      auto it=types_.find(name);
      if (it!=types_.end())
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
      
      auto it=vars_.find(name);
      const ABC_Var_New* var=it->second;
      if (it!=vars_.end())
        {
          auto v=dynamic_cast<
              const Implements_Value_New<T>*>(var->value());
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
      if (all_.find(name)!=all_.end())
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
    
    
    
    bool hasCmdofType(const std::string &name, const std::string &type, std::string *whyNot, const std::string &masterObjective, bool recursive) const;
    
    
    
    
    
    
    bool hasTypeofType(const std::string& name, const std::string& type,
                       std::string* whyNot
                       , const std::string &masterObjective, bool recursive)const;
    
    
    
    bool isNameUnOcuppied(const std::string& name,std::string* whyNot,const std::string &masterObjective, bool recursive)const
    {
      auto it=all_.find(name);
      if (it!=all_.end())
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
      if (types_.find(name)!=types_.end())
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
    
    
    
    bool hasCommand(const std::string& name,   std::string* whyNot
                    ,const std::string &masterObjective,
                    bool recursive)const
    {if (cmds_.find(name)!=cmds_.end())
        {
          return true;
        }
      if (!recursive||(parent()==nullptr))
        {
          *whyNot=masterObjective;
          return false;
        }
      else return parent()->hasCommand(name,whyNot,masterObjective,recursive);
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
      auto it =all_.find(name);
      if (it!=all_.end())
        {
          delete it->second;
          all_.erase(it);
          auto itVar =vars_.find(name);
          if (itVar!=vars_.end())
            {
              delete itVar->second;
              vars_.erase(itVar);
              return true;

            }
          auto itType =types_.find(name);
          if (itType!=types_.end())
            {
              delete itType->second;
              types_.erase(itType);
              return true;

            }
          auto itCmd =cmds_.find(name);
          if (itCmd!=cmds_.end())
            {
              delete itCmd->second;
              cmds_.erase(itCmd);
              return true;

            }
          return true;

        }
      else
        return false;
    }
    
    void pushChild(ABC_Var_New* var)
    {
      all_[var->id()]=var;
      vars_[var->id()]=var;
    }
    
    template<class Field>
    void pushVar(typename Field::myC val={}
        , const std::string myId=Field::myId()
        , const std::string& myTip=Field::myTip()
        , const std::string& myWhatThis=Field::myWhatThis()  )
    {
      push_var<Field>(vars_,val,myId,myTip,myWhatThis);
    }

    template<typename T>
    void push_backVal(const std::string& name,
                      T value,
                      const std::string& classname="",
                      const std::string& tip="",
                      const std::string & whatthis="")
    {
      pushChild(new Implements_Var_New<T>(this,name,classname,value,tip,whatthis));
    }
    

    template <class Field>
    bool getVar(typename Field::myC& val
                ,std::string* whyNot
                ,const std::string& masterObjective )const
    {
      return get_var(vars_,val,whyNot,masterObjective);
    }

    template <class Field>
    typename Field::myC  get_Value()const
    {
      typedef typename Field::myC T;
      T val;
      std::string whyNot;
      if (get_var<Field>(vars_,val,&whyNot,""))
        return val;
      else
        return T{};
    }

    
    void pushType(ABC_Type_of_Value* varT);
    void pushCommand(Implements_Command_Type_New* cmd);
    
    
    Implements_ComplexVar_New(const Implements_ComplexVar_New* parent
                              ):
      Implements_Var_New(parent,"","","",""),
      all_((this->value()->getValued())),vars_(),types_(),cmds_()
    {

    }



    
    Implements_ComplexVar_New(const Implements_ComplexVar_New* parent,
                              const std::string& id
                              ,const std::string& var
                              ,const std::string& tip
                              ,const std::string& whatthis):
      Implements_Var_New(parent,
                         id,var,tip,whatthis),
      all_((this->value()->getValued())),vars_(),types_(),cmds_()
    {
      
    }
    
    Implements_ComplexVar_New(const Implements_ComplexVar_New* parent,
                              const std::string& id
                              ,const std::string& var
                              ,std::map<std::string,ABC_Var_New*> m
                              ,const std::string& tip
                              ,const std::string& whatthis):
      Implements_Var_New(parent,
                         id,var,m,tip,whatthis),
      all_(this->value()->getValued()),vars_(),types_(),cmds_()
    {
      
      
    }
    

    std::set<std::string> getIdsOfVarType(const std::string& varType, bool recursive)const;
    
    
    
    
    
    // Implements_Value_New interface
    
    std::set<std::string> getIdsOfTypeType(const std::string &typeType, bool recursive) const;
    std::string defaultIdOfVarType(const std::string &varType, bool recursive) const;
    std::string defaultIdOfTypeType(const std::string &typeType, bool recursive) const;
    std::string defaultIdOfCommand(const std::string &typeType, bool recursive) const;
    
    
    std::string defaultIdOfCmdType(const std::string &cmdType, bool recursive) const;
    std::set<std::string> getIdsOfCmdType(const std::string &cmdType, bool recursive) const;
    
    friend class buildByToken<std::map<std::string, ABC_Var_New *> >;



  private:
    std::map<std::string,ABC_Var_New*>& getMap()
    {
      return all_;
    }
    const std::map<std::string,ABC_Var_New*>& getMap()const
    {
      return all_;
    }

    std::map<std::string,ABC_Var_New*> popmap()
    {
      std::map<std::string,ABC_Var_New*> out(all_);
      all_.clear();
      vars_.clear();
      types_.clear();
      cmds_.clear();
      return out;
    }



    std::map<std::string,ABC_Var_New*> &all_;
    std::map<std::string,ABC_Var_New*> vars_;
    std::map<std::string,ABC_Type_of_Value*> types_;
    std::map<std::string,Implements_Command_Type_New*> cmds_;
    
    
    
  };
  template<typename T>
  struct a_Type{
    typedef  T myC;
    static std::string myId();
    static std::string myIdType(){return Cls<myC>::name();}
    static std::string myTip();
    static std::string myWhatThis();
    static bool comply(const Implements_ComplexVar_New* cm
                       ,const myC& x
                       ,const Implements_ComplexVar_New*
                       ,std::string *WhyNot
                       , const std::string& objective);



    static Implements_Data_Type_New<myC>*
    varType(const Implements_ComplexVar_New* cm);

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
    inline std::string element(const Implements_ComplexVar_New* cm,   const T* dataType)
    {
      return "<"+dataType->getElementDataType(cm)->Tip()+">";}


    static
    void insert(std::set<std::string>& alt,const std::string& id, const std::string myType)
    {
      alt.insert(id+" : "+myType);
    }

    static
    void insert(std::set<std::string>& alt,const ABC_Var_New* v)
    {
      insert(alt,v->id(),v->myType());
    }


    static std::set<std::string> getIdofVar(const std::map<std::string, ABC_Var_New*> m)
    {
      std::set<std::string> o;
      for (auto& e:m)
        insert(o,e.second);
      return o;

    }
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
    
    
    
    virtual Implements_ComplexVar_New* getComplexVarRep(
        const Implements_ComplexVar_New* cm,
        const ABC_Var_New* var,std::string* whyNot,const std::string& masterObjective)const=0;
    
    virtual ABC_Var_New* getClassRep(const Implements_ComplexVar_New* cm,
                                     const Implements_ComplexVar_New* cvar,
                                     std::string* whyNot,
                                     const std::string& masterObjective)const=0;
    
    
    virtual Implements_ComplexVar_New* getComplexVarofTypeRep(
        const Implements_ComplexVar_New* cm,
        const ABC_Type_of_Value* var,std::string* whyNot,const std::string& masterObjective)const=0;
    
    virtual ABC_Type_of_Value* getTypeClassRep(const Implements_ComplexVar_New* cm,
                                               const Implements_ComplexVar_New* cvar,
                                               std::string* whyNot,
                                               const std::string& masterObjective)const=0;
    
    
    
    
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
    
    ABC_Typed_Value(const Implements_ComplexVar_New* parent):
      ABC_Type_of_Value(parent,Cls<T>::name(),Cls<T>::name(),"",""){}
    
    
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
                                            ABC_Value_New* v)const override
    
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
    
    ABC_Typed_Value(const Implements_ComplexVar_New* parent):
      ABC_Type_of_Value(parent,Cls<T*>::name(),Cls<T*>::name(),"",""){}
    
    
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
      
      
      
      
      
      
      
      virtual bool includesThisType(const Implements_ComplexVar_New* cm,
                                    const std::string& childType,
                                    std::string *whyNot
                                    , const std::string &masterObjective)const override;
      
      virtual Implements_ComplexVar_New* getComplexVarRep(
          const Implements_ComplexVar_New* cm,
          const ABC_Var_New* var,std::string* whyNot,const std::string& masterObjective)const override
      {
        return nullptr;
      }
      
      virtual Implements_Var_New<T>* getClassRep(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New*   ,std::string*, const std::string& )const override
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
                               ):
        ABC_Typed_Value<T>(parent,id,var,tip,whatthis)
      , unknownVaL_(unknownVal)
      ,comply_(complyPred)
      ,typeComply_(complyType)
      ,default_(defaultValue)
      
      {}
      
      
      Implements_Base_Type_New(const Implements_ComplexVar_New *parent):
        Implements_Base_Type_New(
          parent,Cls<T>::name()
          ,Cls<T>::name()
          ,"regular "+Cls<T>::name()
          ,"just a "+Cls<T>::name()+ "nothing special"
          ,T{}
          ,nullptr,nullptr,nullptr)
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
        if (default_==nullptr)
          return {};
        else
          return (*default_)(cm,this);
      }
      
      
    protected:
      T unknownVaL_;
      typePredicate comply_;
      typetypePredicate typeComply_;
      typeValue default_;
      
      
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
        if (comply_==nullptr)
          return true;
        else
          return (*comply_)(cm,val,this,whyNot,masterObjective);
      }
      
      virtual bool isTypeInDomain(const Implements_ComplexVar_New* cm
                                  ,const Implements_Data_Type_New<T*>* val
                                  , std::string *whyNot
                                  ,const std::string &masterObjective ) const override
      {
        if (typeComply_==nullptr)
          return true;
        else
          
          return (*typeComply_)(cm,val,this,whyNot,masterObjective);
      }
      
      
      
      
      
      virtual bool includesThisType(const Implements_ComplexVar_New* cm,
                                    const std::string& childType,
                                    std::string *whyNot
                                    , const std::string &masterObjective)const override;
      
      
      
      
      Implements_ComplexVar_New* getComplexVarRep(const Implements_ComplexVar_New* cm,
                                                  const ABC_Var_New*
                                                  ,std::string*
                                                  ,const std::string& )const override
      
      {
        return nullptr;
      }
      
      virtual Implements_Var_New<T*>* getClassRep(const Implements_ComplexVar_New* cm,
                                                  const Implements_ComplexVar_New*   ,std::string*, const std::string& )const override
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
                               ,typetypePredicate complyType
                               ,typeValue  defaultValue
                               ):
        ABC_Typed_Value<T*>(parent,id,var,tip,whatthis)
      , unknownVaL_(unknownVal)
      ,comply_(complyPred)
      ,typeComply_(complyType)
      ,default_(defaultValue)
      
      {}
      
      
      
      Implements_Base_Type_New(const Implements_ComplexVar_New *parent):
        Implements_Base_Type_New(
          parent,Cls<T*>::name()
          ,Cls<T>::name()
          ,"regular "+Cls<T*>::name()
          ,"just a "+Cls<T*>::name()+ "nothing special"
          ,new T{}
          ,nullptr,nullptr,nullptr)
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
      
      
    };


    class Implements_Data_Type_New_string
        : public Implements_Base_Type_New<std::string>
    {
    public:



      using typePredicate=typename Implements_Base_Type_New<std::string>::typePredicate;
      using typetypePredicate=typename Implements_Base_Type_New<std::string>::typetypePredicate;
      using typeValue=typename Implements_Base_Type_New<std::string>::typeValue;
      using getSet=std::set<std::string>(*)(const Implements_ComplexVar_New*,
      const Implements_ComplexVar_New*);

      using cvToType=Implements_Data_Type_New_string* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_ComplexVar_New* cv,
      std::string* whyNot,const std::string& masterObjective);

      using typeToCv= Implements_ComplexVar_New* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_Data_Type_New_string* classType,
      std::string* whyNot,const std::string& masterObjective);





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
          const Implements_ComplexVar_New* cm)const override;


      virtual std::set<std::string> alternativeNext(const Implements_ComplexVar_New* cm)const
      {
        return (*alternativeNext_)(cm,this);
      }

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

      virtual Implements_ComplexVar_New* getComplexVarofTypeRep(
          const Implements_ComplexVar_New* cm,
          const ABC_Type_of_Value* var,std::string* whyNot,const std::string& masterObjective)const override
      {
        if (getCvFromType_==nullptr)
          return nullptr;
        else
          {
            auto v=dynamic_cast<const Implements_Data_Type_New_string*>(var);
            if (v==nullptr)
              return nullptr;
            else
              return (*getCvFromType_)(cm,v,whyNot,masterObjective);
          }
      }

      virtual Implements_Data_Type_New_string* getTypeClassRep(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* cvar,
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



      Implements_Data_Type_New_string(const Implements_ComplexVar_New* parent,
                                      const std::string& id
                                      ,const std::string& var
                                      ,const std::string& tip
                                      ,const std::string& whatthis
                                      ,const std::string& unknownVal
                                      ,typePredicate complyPred
                                      ,typetypePredicate typeComply
                                      ,typeValue  defaultValue
                                      ,getSet alterNext
                                      , cvToType getTypeFromCV,
                                      typeToCv getCvFromType):
        Implements_Base_Type_New<std::string>(parent,id,var,tip,whatthis,unknownVal
                                              ,complyPred,typeComply,defaultValue)
      ,alternativeNext_(alterNext),getTypeFromCV_(getTypeFromCV),getCvFromType_(getCvFromType)

      {}


      Implements_Data_Type_New_string(const Implements_ComplexVar_New *parent):
        Implements_Base_Type_New<std::string>(parent),
        alternativeNext_(nullptr),getTypeFromCV_(nullptr),getCvFromType_(nullptr)

      {}


    protected:
      getSet alternativeNext_;
      cvToType getTypeFromCV_;
      typeToCv getCvFromType_;
    };


  };

  namespace Identifier
  {
    inline
    std::size_t  getVersionNumber(const std::string &id)
    {
      std::stringstream ss(id.substr(id.find_last_of('_')));
      std::size_t n;
      if (ss>>n)
        return n;
      else
        return std::string::npos;
    }

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
    static std::string ClassName(){return "Implements_Identifier";}

    virtual std::set<std::string> alternativeNext(const Implements_ComplexVar_New* cm)const override;

    virtual bool isVarInDomain(const Implements_ComplexVar_New* cm,const std::string &idCandidate, std::string *whyNot,const std::string& objective ) const override;



    virtual bool isTypeInDomain(const Implements_ComplexVar_New* cm
                                ,const Implements_Data_Type_New<std::string>* val
                                , std::string *whyNot
                                ,const std::string& masterObjective ) const override
    {
      auto t=dynamic_cast<const Implements_Identifier*>(val);
      if (t==nullptr)
        {
          *whyNot=masterObjective+": "+ val->id()+ "is not an identifier";
          return false;
        }
      else
        return isTypeIdentifierInDomain(cm,t,whyNot,masterObjective);

    }

    virtual bool isTypeIdentifierInDomain(const Implements_ComplexVar_New* cm
                                          ,const Implements_Identifier* val
                                          , std::string *whyNot
                                          ,const std::string& masterObjective ) const;




    virtual std::string getDefault_Valued(const Implements_ComplexVar_New* cm) const override
    {
      return (*default_)(cm,this);
    }



    const ABC_Type_of_Value* getType(){return type_;}



  private:
    static std::string toId
    (const ABC_Type_of_Value* type,
     const _private::Implements_Data_Type_New_map_string_ABC_Var_New* fieldType,
     bool isVar, bool isType,bool isCommand,bool isNew, bool isUsed);





    Implements_Identifier(const Implements_ComplexVar_New* cm,
                          const ABC_Type_of_Value* type,
                          const _private::Implements_Data_Type_New_map_string_ABC_Var_New* fieldType,
                          bool isVar, bool isType,bool isCommand,bool isNew, bool isUsed):
      Implements_Data_Type_New_string(cm
                                      ,toId(type,fieldType,isVar,isType,isCommand,isNew,isUsed)
                                      ,Implements_Identifier::ClassName()
                                      ,"identifier of a "
                                      ,"blablbb identifier"
                                      ,""
                                      ,nullptr
                                      ,nullptr
                                      ,nullptr
                                      ,nullptr
                                      ,nullptr,nullptr)
    ,type_(type), fieldType_(fieldType), isVar_(isVar), isType_(isType),isCommand_(isCommand)
    ,isNew_(isNew),isUsed_(isUsed)
    {}
    const ABC_Type_of_Value* type_;
    const _private::Implements_Data_Type_New_map_string_ABC_Var_New* fieldType_;
    bool isVar_;
    bool isType_;
    bool isCommand_;
    bool isNew_;
    bool isUsed_;

  };

  namespace Identifier {

    struct types {

      static Implements_Identifier* create_Id_Var(const Implements_ComplexVar_New* cm)
      {
        return new Implements_Identifier(cm,nullptr,nullptr,true,false,false,true,true);
      }

      static Implements_Identifier* create_Id_Var_New(const Implements_ComplexVar_New* cm)
      {
        return new Implements_Identifier(cm,nullptr,nullptr,true,false,false,true,false);
      }

      static Implements_Identifier* create_Id_Var_Used(const Implements_ComplexVar_New* cm)
      {
        return new Implements_Identifier(cm,nullptr,nullptr,true,false,false,false,true);
      }

      template <class T>
      static Implements_Identifier* getVarType(const Implements_ComplexVar_New* cm)
      {
        return new Implements_Identifier
            (cm,T::typeV,T::fieldType,T::isVar
             ,T::isType,T::isCommand,T::isNew,T::isUsed);

      }

      template <class T>
      static Implements_Identifier* getVarType(const Implements_ComplexVar_New* cm
                                               ,const ABC_Type_of_Value*t)
      {
        return new Implements_Identifier
            (cm,t,T::fieldType,T::isVar
             ,T::isType,T::isCommand,T::isNew,T::isUsed);

      }


      template <class T>
      static Implements_Identifier* getVarType(const Implements_ComplexVar_New* cm
                                               ,const _private::Implements_Data_Type_New_map_string_ABC_Var_New* f )
      {
        return new Implements_Identifier
            (cm,T::typeV,f,T::isVar
             ,T::isType,T::isCommand,T::isNew,T::isUsed);

      }





      template <class T>
      static std::string toId()
      {
        return Implements_Identifier::toId
            (T::typeV,T::fieldType,T::isVar, T::isType,T::isCommand,T::isNew,T::isUsed);

      }

      template <class T>
      static std::string toId(const ABC_Type_of_Value* t)
      {
        return Implements_Identifier::toId
            (t,T::fieldType,T::isVar, T::isType,T::isCommand,T::isNew,T::isUsed);

      }

      template <class T>
      static std::string toId(const _private::Implements_Data_Type_New_map_string_ABC_Var_New* f)
      {
        return Implements_Identifier::toId
            (T::typeV,f,T::isVar, T::isType,T::isCommand,T::isNew,T::isUsed);

      }


      struct idVar{
        typedef  std::string myC;
        typedef idVar selfType;

        static std::string myId(){return toId<selfType>();}
        static std::string myId(const ABC_Type_of_Value* t){toId<selfType>(t);}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "Variable indentifer";}

        static std::string myWhatThis(){return "an identifier to a Variable";}


        static Implements_Identifier*
        varType(const Implements_ComplexVar_New* cm)
        {return getVarType<selfType>(cm);}


        static Implements_Identifier*
        varType(const Implements_ComplexVar_New* cm
                ,const ABC_Type_of_Value* t)
        {return getVarType<selfType>(cm,t);}


        constexpr static const ABC_Type_of_Value* const typeV=nullptr;
        constexpr static
        const _private::Implements_Data_Type_New_map_string_ABC_Var_New*
        fieldType =nullptr;
        constexpr static  bool isVar=true;
        constexpr static  bool isType=false;
        static constexpr bool isCommand=false;
        static constexpr bool isNew=true;
        static constexpr bool isUsed=true;

      };

      struct idVarNew{
        typedef  std::string myC;
        typedef idVarNew selfType;

        static std::string myId(){return toId<selfType>();}
        static std::string myId(const ABC_Type_of_Value* t){toId<selfType>(t);}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "New Variable indentifer";}
        static std::string myWhatThis(){return "an unused identifier to a Variable";}


        static Implements_Identifier*
        varType(const Implements_ComplexVar_New* cm)
        {return getVarType<selfType>(cm);}



        static Implements_Identifier*
        varType(const Implements_ComplexVar_New* cm
                ,const ABC_Type_of_Value* t)
        {return getVarType<selfType>(cm,t);}



        constexpr static const ABC_Type_of_Value* const typeV=nullptr;
        constexpr static
        const _private::Implements_Data_Type_New_map_string_ABC_Var_New*
        fieldType =nullptr;
        constexpr static  bool isVar=true;
        constexpr static  bool isType=false;
        static constexpr bool isCommand=false;
        static constexpr bool isNew=true;
        static constexpr bool isUsed=false;

      };





      struct idVarUsed{
        typedef  std::string myC;
        typedef idVarUsed selfType;

        static std::string myId(){return toId<selfType>();}
        static std::string myId(const ABC_Type_of_Value* t)
        {return toId<selfType>(t);}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "An existing Variable indentifer";}
        static std::string myWhatThis(){return "an identifier to a Variable";}


        static Implements_Identifier*
        varType(const Implements_ComplexVar_New* cm)
        {return getVarType<selfType>(cm);}

        static Implements_Identifier*
        varType(const Implements_ComplexVar_New* cm,
                const ABC_Type_of_Value* t)
        {return getVarType<selfType>(cm,t);}



        constexpr static const ABC_Type_of_Value* const typeV=nullptr;
        constexpr static
        const _private::Implements_Data_Type_New_map_string_ABC_Var_New*
        fieldType =nullptr;
        constexpr static  bool isVar=true;
        constexpr static  bool isType=false;
        static constexpr bool isCommand=false;
        static constexpr bool isNew=false;
        static constexpr bool isUsed=true;

      };


      struct idType{
        typedef  std::string myC;
        typedef idType selfType;

        static std::string myId(){return toId<selfType>();}
        static std::string myId(const ABC_Type_of_Value* t){toId<selfType>(t);}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "a typeindentifer";}
        static std::string myWhatThis(){return "an identifier to a type";}


        static Implements_Identifier*
        varType(const Implements_ComplexVar_New* cm)
        {return getVarType<selfType>(cm);}


        static Implements_Identifier*
        varType(const Implements_ComplexVar_New* cm
                ,const ABC_Type_of_Value* t)
        {return getVarType<selfType>(cm,t);}


        constexpr static const ABC_Type_of_Value* const typeV=nullptr;
        constexpr static
        const _private::Implements_Data_Type_New_map_string_ABC_Var_New*
        fieldType =nullptr;
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
        static std::string myId(const ABC_Type_of_Value* t){toId<selfType>(t);}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "a typeindentifer";}
        static std::string myWhatThis(){return "an identifier to a type";}


        static Implements_Identifier*
        varType(const Implements_ComplexVar_New* cm)
        {return getVarType<selfType>(cm);}


        static Implements_Identifier*
        varType(const Implements_ComplexVar_New* cm
                ,const ABC_Type_of_Value* t)
        {return getVarType<selfType>(cm,t);}


        constexpr static const ABC_Type_of_Value* const typeV=nullptr;
        constexpr static
        const _private::Implements_Data_Type_New_map_string_ABC_Var_New*
        fieldType =nullptr;
        constexpr static  bool isVar=false;
        constexpr static  bool isType=false;
        static constexpr bool isCommand=true;
        static constexpr bool isNew=false;
        static constexpr bool isUsed=true;

      };




      struct idField{
        typedef  std::string myC;
        typedef idField selfType;

        static std::string myId(const _private::Implements_Data_Type_New_map_string_ABC_Var_New* f){toId<selfType>(f);}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "Variable indentifer";}

        static std::string myWhatThis(){return "an identifier to a Variable";}




        static Implements_Identifier*
        varType(const Implements_ComplexVar_New* cm
                ,const _private::Implements_Data_Type_New_map_string_ABC_Var_New* f)
        {return getVarType<selfType>(cm,f);}


        constexpr static const ABC_Type_of_Value* const typeV=nullptr;
        constexpr static
        const _private::Implements_Data_Type_New_map_string_ABC_Var_New*
        fieldType =nullptr;
        constexpr static  bool isVar=true;
        constexpr static  bool isType=false;
        static constexpr bool isCommand=false;
        static constexpr bool isNew=true;
        static constexpr bool isUsed=true;

      };

      struct idFieldNew{
        typedef  std::string myC;
        typedef idFieldNew selfType;

        static std::string myId(const _private::Implements_Data_Type_New_map_string_ABC_Var_New* f){toId<selfType>(f);}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "Unfilled Field identifer";}

        static std::string myWhatThis(){return "an identifier to a Variable";}




        static Implements_Identifier*
        varType(const Implements_ComplexVar_New* cm
                ,const _private::Implements_Data_Type_New_map_string_ABC_Var_New* f)
        {return getVarType<selfType>(cm,f);}


        constexpr static const ABC_Type_of_Value* const typeV=nullptr;
        constexpr static
        const _private::Implements_Data_Type_New_map_string_ABC_Var_New*
        fieldType =nullptr;
        constexpr static  bool isVar=true;
        constexpr static  bool isType=false;
        static constexpr bool isCommand=false;
        static constexpr bool isNew=true;
        static constexpr bool isUsed=false;

      };

      struct idFieldUsed{
        typedef  std::string myC;
        typedef idFieldUsed selfType;

        static std::string myId(const _private::Implements_Data_Type_New_map_string_ABC_Var_New* f){toId<selfType>(f);}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){return "Variable indentifer";}

        static std::string myWhatThis(){return "an identifier to a Variable";}




        static Implements_Identifier*
        varType(const Implements_ComplexVar_New* cm
                ,const _private::Implements_Data_Type_New_map_string_ABC_Var_New* f)
        {return getVarType<selfType>(cm,f);}


        constexpr static const ABC_Type_of_Value* const typeV=nullptr;
        constexpr static
        const _private::Implements_Data_Type_New_map_string_ABC_Var_New*
        fieldType =nullptr;
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
      using typePredicate=typename Implements_Base_Type_New<C<T>>::typePredicate;
      using typetypePredicate=typename Implements_Base_Type_New<C<T>>::typetypePredicate;
      using typeValue=typename Implements_Base_Type_New<C<T>>::typeValue;
      
      
      using typeElementPredicate = bool(*)
      (const Implements_ComplexVar_New* cm
      ,const C<T> & c
      , typename C<T>::const_iterator iter
      ,const T& elem
      ,const Implements_Container_Type_New<T,C>* v
      , std::string *WhyNot
      , const std::string& objective);
      
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
          ,typename C<T>::const_iterator iter
          , const T& elem
          , std::string *whyNot
          ,const std::string& masterObjective) const
      {
        return (*elemComply_)(cm,val,iter,elem,this,whyNot,masterObjective);
      }
      
      virtual buildByToken<T>* getElementBuildByToken(const Implements_ComplexVar_New* cm)const
        {
          const Implements_Data_Type_New<T>* v= getElementDataType(cm);
          if (v!=nullptr)
            return new buildByToken<T>(cm,v);
          else return nullptr;
        }

      virtual const Implements_Data_Type_New<T>* getElementDataType(const Implements_ComplexVar_New* cm)const;
      
      
      
      
      virtual ~Implements_Container_Type_New(){}
      
      
      Implements_Container_Type_New(
          const Implements_ComplexVar_New* parent,
          const std::string& id
          ,const std::string& var
          ,const std::string& tip
          ,const std::string& whatthis
          , const std::string elementVar
          ,typePredicate complyPred
          ,typetypePredicate typeComply                                 ,typeElementPredicate elemeComply
          ,typeValue  defaultValue
          
          ):
        Implements_Base_Type_New<C<T>>(parent,id,var,tip,whatthis,C<T>()
                                       ,complyPred,typeComply,defaultValue),
        elemComply_(elemeComply)
      {
        this->template pushVar<fields::elementType_Field>(elementVar);
       }
      
      Implements_Container_Type_New(
          const Implements_ComplexVar_New* parent):
        Implements_Base_Type_New<C<T>>(
          parent,Cls<C<T>>::name(),Cls<C<T>>::name(),"","",C<T>()
          ,nullptr,nullptr,nullptr),
        elemComply_(nullptr)
      {
        this->template pushVar<fields::elementType_Field>(Cls<T>::name());

      }
      
      
    protected:
      typeElementPredicate elemComply_;
      
      
    };
    
    
    
    template<typename T, template<typename> class C>
    class Implements_Container_Type_New<T*,C> :public Implements_Base_Type_New<C<T*>>
    {
    public:
      using typePredicate=typename Implements_Base_Type_New<C<T*>>::typePredicate;
      using typetypePredicate=typename Implements_Base_Type_New<C<T*>>::typetypePredicate;
      using typeValue=typename Implements_Base_Type_New<C<T*>>::typeValue;
      
      
      using typeElementPredicate = bool(*)
      (const Implements_ComplexVar_New* cm
      ,const C<T*> & c
      , typename C<T*>::const_iterator iter
      ,const T*& elem
      ,const Implements_Container_Type_New<T*,C>* v
      , std::string *WhyNot
      , const std::string& objective);
      
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
          const C<T*> &val
          ,typename C<T*>::const_iterator iter
          ,const T*& elem
          , std::string *whyNot
          ,const std::string& masterObjective) const
      {
        return (*elemComply_)(cm,val,iter,elem,this,whyNot,masterObjective);
      }
      
      virtual buildByToken<T*>* getElementBuildByToken(const Implements_ComplexVar_New* cm)const
      {
        const Implements_Data_Type_New<T*>* v= getElementDataType(cm);
        if (v!=nullptr)
          return new buildByToken<T*>(cm,v);
        else return nullptr;
      }

      
      virtual const Implements_Data_Type_New<T*>* getElementDataType(const Implements_ComplexVar_New* cm)const;
      
      
      
      
      virtual ~Implements_Container_Type_New(){}
      
      
      Implements_Container_Type_New(
          const Implements_ComplexVar_New* parent,
          const std::string& id
          ,const std::string& var
          ,const std::string& tip
          ,const std::string& whatthis
          , const std::string elementVar
          ,typePredicate complyPred
          ,typetypePredicate typeComply                                 ,typeElementPredicate elemeComply
          ,typeValue  defaultValue
          
          ):
        Implements_Base_Type_New<C<T*>>(parent,id,var,tip,whatthis,C<T*>()
                                        ,complyPred,typeComply,defaultValue),
        elemComply_(elemeComply)
      {
        this->template pushVar<fields::elementType_Field>(elementVar);

      }
      
      Implements_Container_Type_New(const Implements_ComplexVar_New* parent):
        Implements_Base_Type_New<C<T*>>(parent),
        elemComply_(nullptr)
      {
        this->template pushVar<fields::elementType_Field>(Cls<T*>::name());

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
      
      using typeElementPredicate= typename Implements_Container_Type_New<T,My_vec>::typeElementPredicate;
      
      using cvToType=Implements_Data_Type_New_vector<T>* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_ComplexVar_New* cv,
      std::string* whyNot,const std::string& masterObjective);
      
      using typeToCv= Implements_ComplexVar_New* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_Data_Type_New_vector<T>* classType,
      std::string* whyNot,const std::string& masterObjective);
      
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
            for (auto it=v.begin(); it!=v.end(); ++it)
              {
                if (!this->isElementInDomain(cm,v,it,*it,whyNot,masterObjective))
                  return false;
                if(!etype->put(cm,*it,ostream,whyNot,masterObjective))
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
            auto iter=v.begin();
            while ((iter<v.end())&&(!istream->nextCharIs(']',false)))
              {
                T d;
                if (etype->get(cm,d,istream,whyNot,masterObjective))
                  {
                    if (this->isElementInDomain(cm,v,iter,d,whyNot,masterObjective))
                      {
                        *iter=std::move(d);
                        ++iter;
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
                    if (this->isElementInDomain(cm,v,v.end(),d,whyNot,masterObjective))
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
      
      
      virtual Implements_ComplexVar_New* getComplexVarofTypeRep(
          const Implements_ComplexVar_New* cm,
          const ABC_Type_of_Value* var,std::string* whyNot,const std::string& masterObjective)const override
      {
        if (getCvFromType_==nullptr)
          return nullptr;
        else
          {
            auto v=dynamic_cast<const Implements_Data_Type_New_vector<T>*>(var);
            if (v==nullptr)
              return nullptr;
            else
              return (*getCvFromType_)(cm,v,whyNot,masterObjective);
          }
      }
      
      virtual Implements_Data_Type_New_vector<T>* getTypeClassRep(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* cvar,
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
                                      ,cvToType getTypeFromCV
                                      ,typeToCv getCvFromType
                                      ):
        Implements_Container_Type_New<T,My_vec>(
          parent,id,var,tip,whatthis,elementVar,complyPred,typeComply,elemeComply
          ,defaultValue)
      ,getTypeFromCV_(getTypeFromCV),getCvFromType_(getCvFromType)
      {}
      
      
      Implements_Data_Type_New_vector(const Implements_ComplexVar_New* parent):
        Implements_Container_Type_New<T,My_vec>(parent)
      ,getTypeFromCV_(nullptr),getCvFromType_(nullptr)
      {}
      
      
    protected:
      cvToType getTypeFromCV_;
      typeToCv getCvFromType_;
      
      
    };
    
    
    
    template<typename T>
    class Implements_Data_Type_New_regular:public Implements_Base_Type_New<T>
    {
    public:
      using typePredicate=typename Implements_Base_Type_New<T>::typePredicate;
      using typetypePredicate=typename Implements_Base_Type_New<T>::typetypePredicate;
      
      using typeValue=typename Implements_Base_Type_New<T>::typeValue;
      
      using cvToType=Implements_Data_Type_New_regular<T>* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_ComplexVar_New* cv,
      std::string* whyNot,const std::string& masterObjective);
      
      using typeToCv= Implements_ComplexVar_New* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_Data_Type_New_regular<T>* classType,
      std::string* whyNot,const std::string& masterObjective);
      
      
      
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
      virtual Implements_ComplexVar_New* getComplexVarofTypeRep(
          const Implements_ComplexVar_New* cm,
          const ABC_Type_of_Value* var,std::string* whyNot,const std::string& masterObjective)const override
      {
        if (getCvFromType_==nullptr)
          return nullptr;
        else
          {
            auto v=dynamic_cast<const Implements_Data_Type_New_regular<T>*>(var);
            if (v==nullptr)
              return nullptr;
            else
              return (*getCvFromType_)(cm,v,whyNot,masterObjective);
          }
      }
      
      virtual Implements_Data_Type_New_regular<T>* getTypeClassRep(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* cvar,
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
                                       ,cvToType getTypeFromCV
                                       ,typeToCv getCvFromType
                                       ):
        Implements_Base_Type_New<T>(parent,id,var,tip,whatthis,unknownVal
                                    ,complyPred,typeComply,defaultValue)
      ,getTypeFromCV_(getTypeFromCV),getCvFromType_(getCvFromType)
      {}
      
      
      Implements_Data_Type_New_regular(const Implements_ComplexVar_New *parent):
        Implements_Base_Type_New<T>(parent){}
      
    protected:
      cvToType getTypeFromCV_;
      typeToCv getCvFromType_;
      
      
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
      
      using typeElementPredicate= typename Implements_Container_Type_New<T,My_set>::typeElementPredicate;
      
      using cvToType=Implements_Data_Type_New_set<T>* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_ComplexVar_New* cv,
      std::string* whyNot,const std::string& masterObjective);
      
      using typeToCv= Implements_ComplexVar_New* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_Data_Type_New_set<T>* classType,
      std::string* whyNot,const std::string& masterObjective);
      
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
            for (auto it=v.begin(); it!=v.end(); ++it)
              {
                if (!this->isElementInDomain(cm,v,it,*it,whyNot,masterObjective))
                  return false;
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
                    if (this->isElementInDomain(cm,v,v.end(),d,whyNot,masterObjective))
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
      
      virtual Implements_ComplexVar_New* getComplexVarofTypeRep(
          const Implements_ComplexVar_New* cm,
          const ABC_Type_of_Value* var,std::string* whyNot,const std::string& masterObjective)const override
      {
        if (getCvFromType_==nullptr)
          return nullptr;
        else
          {
            auto v=dynamic_cast<const Implements_Data_Type_New_set<T>*>(var);
            if (v==nullptr)
              return nullptr;
            else
              return (*getCvFromType_)(cm,v,whyNot,masterObjective);
          }
      }
      
      virtual Implements_Data_Type_New_set<T>* getTypeClassRep(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* cvar,
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
                                   ,cvToType getTypeFromCV
                                   ,typeToCv getCvFromType
                                   ):
        Implements_Container_Type_New<T,My_set>(
          parent,id,var,tip,whatthis,elementVar,complyPred,typeComply,elemeComply
          ,defaultValue)
      ,getTypeFromCV_(getTypeFromCV),getCvFromType_(getCvFromType)
      {}
      
      Implements_Data_Type_New_set(const Implements_ComplexVar_New* parent):
        Implements_Container_Type_New<T,My_set>(
          parent)
      ,getTypeFromCV_(nullptr),getCvFromType_(nullptr)
      {}
      
      
    protected:
      cvToType getTypeFromCV_;
      typeToCv getCvFromType_;
      
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
      using typePredicate=typename Implements_Base_Type_New<Markov_LA::M_Matrix<T>>::typePredicate;
      using typetypePredicate=typename Implements_Base_Type_New<Markov_LA::M_Matrix<T>>::typetypePredicate;
      using typeValue=typename Implements_Base_Type_New<Markov_LA::M_Matrix<T>>::typeValue;
      
      using typeElementPredicate= typename Implements_Container_Type_New<T,Markov_LA::M_Matrix>::typeElementPredicate;
      
      using cvToType=Implements_Data_Type_New_M_Matrix* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_ComplexVar_New* cv,
      std::string* whyNot,const std::string& masterObjective);
      
      using typeToCv= Implements_ComplexVar_New* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_Data_Type_New_M_Matrix* classType,
      std::string* whyNot,const std::string& masterObjective);
      
      
      using getNumber= std::size_t (*)  (const Implements_ComplexVar_New* cm
      ,const Implements_ComplexVar_New* cv);



      
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
      
      virtual Implements_ComplexVar_New* getComplexVarofTypeRep(
          const Implements_ComplexVar_New* cm,
          const ABC_Type_of_Value* var,std::string* whyNot,const std::string& masterObjective)const override
      {
        if (getCvFromType_==nullptr)
          return nullptr;
        else
          {
            auto v=dynamic_cast<const Implements_Data_Type_New_M_Matrix<T>*>(var);
            if (v==nullptr)
              return nullptr;
            else
              return (*getCvFromType_)(cm,v,whyNot,masterObjective);
          }
      }
      
      virtual Implements_Data_Type_New_M_Matrix<T>* getTypeClassRep(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* cvar,
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
      
      
      
      
      
      
      bool get(const Implements_ComplexVar_New *cm, Markov_LA::M_Matrix<T> &v, ABC_Input *istream, std::string *whyNot, const std::string &masterObjective) const{
        
      }
      
      bool put(const Implements_ComplexVar_New *cm, const Markov_LA::M_Matrix<T> &v, ABC_Output *ostream, std::string *error, const std::string &masterObjective) const
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
                                        ,cvToType getTypeFromCV
                                        ,typeToCv getCvFromType
                                        ,getNumber getNumCols
                                        ,getNumber getNumRows
                                        ,bool areColsFixed
                                        ,bool areRowsFixed):
        Implements_Container_Type_New<T,Markov_LA::M_Matrix>(
          parent,id,var,tip,whatthis,elementVar,complyPred,typeComply,elemeComply
          ,defaultValue)
      ,getTypeFromCV_(getTypeFromCV),getCvFromType_(getCvFromType)
      ,getNumCols_(getNumCols),getNumRows_(getNumRows)
      {
        this->template pushVar<fields::isNumColsFixed_Field>(areColsFixed);
        this->template pushVar<fields::isNumRowsFixed_Field>(areRowsFixed);

      }
      
      Implements_Data_Type_New_M_Matrix(const Implements_ComplexVar_New* parent)
        :Implements_Container_Type_New<T,Markov_LA::M_Matrix>(
           parent)
        ,getTypeFromCV_(nullptr)
        ,getCvFromType_(nullptr)
        ,getNumCols_(nullptr)
        ,getNumRows_(nullptr)
      {}
      
      std::size_t getNumberOfCols(const Implements_ComplexVar_New* cm)const
      {
        if (getNumCols_==nullptr)
          return 0;
        else
          return (*getNumCols_)(cm,this);
      }

      std::size_t getNumberOfRows(const Implements_ComplexVar_New* cm)const
      {
        if (getNumRows_==nullptr)
          return 0;
        else
          return (*getNumRows_)(cm,this);
      }



    protected:
      cvToType getTypeFromCV_;
      typeToCv getCvFromType_;
      getNumber getNumCols_;
      getNumber getNumRows_;
    };
    
    
    template<typename K,typename T, template<typename,typename> class D>
    class Implements_Dictionary_Type_New:public Implements_Base_Type_New<D<K,T>>
    {
    public:
      using typePredicate=typename Implements_Base_Type_New<D<K,T>>::typePredicate;
      using typetypePredicate=typename Implements_Base_Type_New<D<K,T>>::typetypePredicate;
      using typeValue=typename Implements_Base_Type_New<D<K,T>>::typeValue;
      
      
      
      using typeElementPredicate = bool(*)(
      const Implements_ComplexVar_New*
      ,const D<K,T> &
      ,typename D<K,T>::const_iterator
      ,const K&
      ,const T&
      ,const Implements_Dictionary_Type_New<K,T,D>*
      , std::string *WhyNot
      , const std::string& objective);
      
      
      using typeKeyPredicate = bool(*)(
      const Implements_ComplexVar_New*
      ,const D<K,T> &
      ,typename D<K,T>::const_iterator
      ,const K&
      ,const Implements_ComplexVar_New*
      , std::string *WhyNot
      , const std::string& objective);
      
      
      
      static std::string ClassName()
      {
        return "Implements_Dictionary_Type_New_of_"+Cls<D<K,T>>::name();
      }
      
      virtual std::string myClass()const override
      {
        return ClassName();
      }
      
      virtual bool isKeyInDomain(
          const Implements_ComplexVar_New* cm,
          const D<K,T> &val
          ,typename D<K,T>::const_iterator iter
          ,const K& elem
          , std::string *whyNot
          ,const std::string& masterObjective ) const
      {
        if (keyComply_==nullptr)
          return true;
        else
          return (*keyComply_)(cm,val,iter,elem,this,whyNot,masterObjective);
      }
      
      
      
      virtual bool isElementInDomain
      (const Implements_ComplexVar_New* cm
       ,const D<K,T> &val
       ,typename D<K,T>::const_iterator iter
       ,const K& key
       ,T& elem
       , std::string *whyNot
       ,const std::string& masterObjective) const
      {
        if (elemComply_==nullptr)
          return true;
        else
          return (*elemComply_)(cm,val,iter,key,elem,this,whyNot,masterObjective);
      }
      
      
      
      virtual buildByToken<T>* getElementBuildByToken(const Implements_ComplexVar_New* cm)const
      {
        const Implements_Data_Type_New<T>* v= getElementDataType(cm);
        if (v!=nullptr)
          return new buildByToken<T>(cm,v);
        else return nullptr;

      }
      
      virtual const Implements_Data_Type_New<T>* getElementDataType(const Implements_ComplexVar_New* cm)const
      {

        std::string eletype=this->template get_Value<fields::elementType_Field>();
        if (!eletype.empty())
          {
            std::string whynot;
            return cm->idToTyped<T>(eletype,&whynot,"");
          }
        else return nullptr;

      }
      
      virtual buildByToken<K>* getKeyBuildByToken(const Implements_ComplexVar_New* cm)const
      {
        const Implements_Data_Type_New<K>* v= getKeyDataType(cm);
        if (v!=nullptr)
          return new buildByToken<K>(cm,v);
        else return nullptr;

      }

      virtual const Implements_Data_Type_New<K>* getKeyDataType(const Implements_ComplexVar_New* cm)const
      {

        std::string keytype=this->template get_Value<fields::keyType_Field>();
        if (!keytype.empty())
          {
            std::string whynot;
            return cm->idToTyped<K>(keytype,&whynot,"");
          }
        else return nullptr;

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
          ):
        Implements_Base_Type_New<D<K,T>>(parent,id,var,tip,whatthis
                                         ,D<K,T>(),complyPred,typeComply,defaultValue),
        elemComply_(elemeComply)
      ,keyComply_(keyComply)
      {

        this->template pushVar<fields::keyType_Field>(keyVar);
        this->template pushVar<fields::elementType_Field>(elementVar);

      }
      
      Implements_Dictionary_Type_New(const Implements_ComplexVar_New* parent):
        Implements_Base_Type_New<D<K,T>>(parent),
        elemComply_(nullptr)
      ,keyComply_(nullptr)
      {
        this->template pushVar<fields::keyType_Field>(Cls<K>::name());
        this->template pushVar<fields::elementType_Field>(Cls<T>::name());

      }
      
    protected:
      typeElementPredicate elemComply_;
      typeKeyPredicate keyComply_;
      
      // ABC_Type_of_Value interface
    public:
      
      // ABC_Typed_Value interface
    public:
      virtual bool put(const Implements_ComplexVar_New *cm, const std::pair<K,T> &v, ABC_Output *ostream, std::string *error, const std::string &masterObjective) const
      {
        
      }
      virtual bool get(const Implements_ComplexVar_New *cm, std::pair<K,T> &v, ABC_Input *istream, std::string *whyNot, const std::string &masterObjective) const
      {
        
      }
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
      const Implements_ComplexVar_New*
      ,const std::pair<K,T> & p
      ,const T& x
      ,const Implements_Data_Type_New_pair<K,T>* v
      , std::string *WhyNot
      , const std::string& objective);
      
      using typeKeyPredicate = bool(*)(
      const Implements_ComplexVar_New*
      ,const std::pair<K,T> & p
      ,const K& k
      ,const Implements_Data_Type_New_pair<K,T>* v
      , std::string *WhyNot
      , const std::string& objective);
      
      
      using cvToType=Implements_Data_Type_New_pair<K,T>* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_ComplexVar_New* cv,
      std::string* whyNot,const std::string& masterObjective);
      
      using typeToCv= Implements_ComplexVar_New* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_Data_Type_New_pair<K,T>* classType,
      std::string* whyNot,const std::string& masterObjective);
      
      
      virtual bool put(const Implements_ComplexVar_New *cm, const std::pair<K,T> &v, ABC_Output *ostream, std::string *error, const std::string &masterObjective) const
      {
        
      }
      virtual bool get(const Implements_ComplexVar_New *cm, std::pair<K,T> &v, ABC_Input *istream, std::string *whyNot, const std::string &masterObjective) const
      {
        
      }
      
      
      virtual buildByToken<T>* getElementBuildByToken(const Implements_ComplexVar_New* cm)const
      {
        const Implements_Data_Type_New<T>* v= getElementDataType(cm);
        if (v!=nullptr)
          return new buildByToken<T>(cm,v);
        else return nullptr;
      }

      
      virtual const Implements_Data_Type_New<T>* getElementDataType(const Implements_ComplexVar_New* cm)const
      {
        std::string eletype=this->template get_Value<fields::elementType_Field>();
        if (!eletype.empty())
          {
            std::string whynot;
            return cm->idToTyped<T>(eletype,&whynot,"");
          }
        else return nullptr;

      }

      
      
      virtual buildByToken<K>* getKeyBuildByToken(const Implements_ComplexVar_New* cm)const
      {
        const Implements_Data_Type_New<K>* v= getKeyDataType(cm);
        if (v!=nullptr)
          return new buildByToken<K>(cm,v);
        else return nullptr;
      }

      virtual const Implements_Data_Type_New<K>* getKeyDataType(const Implements_ComplexVar_New* cm)const
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
          const Implements_ComplexVar_New* cm,
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
      (const Implements_ComplexVar_New* cm
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
      
      
      
      
      
      virtual buildByToken<std::pair<K,T>> *getBuildByToken(const Implements_ComplexVar_New *cm) const override
      {
        return new buildByToken<std::pair<K,T>>(cm,this);
      }
      
      
      virtual Implements_ComplexVar_New* getComplexVarofTypeRep(
          const Implements_ComplexVar_New* cm,
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
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* cvar,
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
                                    ):
        Implements_Base_Type_New<std::pair<K, T> >         (parent,id,var,tip,whatthis,{},complyPred,typeComply,defaultValue)
      ,keyComply_(keyComply),elemeComply_(elemeComply)
      {
        this->template pushVar<fields::keyType_Field>(keyVar);
        this->template pushVar<fields::elementType_Field>(elementVar);
      }
      
      
      Implements_Data_Type_New_pair(const Implements_ComplexVar_New* parent):
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
      
      using typePredicate=typename Implements_Base_Type_New<std::map<K,T>>::typePredicate;
      using typetypePredicate=typename Implements_Base_Type_New<std::map<K,T>>::typetypePredicate;
      using typeValue=typename Implements_Base_Type_New<std::map<K,T>>::typeValue;
      
      using typeElementPredicate= typename Implements_Dictionary_Type_New<K,T,My_map>::typeElementPredicate;
      
      using typeKeyPredicate= typename Implements_Dictionary_Type_New<K,T,My_map>::typeKeyPredicate;
      
      using pairPredicate= bool(*)(const Implements_ComplexVar_New*,const std::map<K,T> &,const std::pair<K,T>&,const Implements_ComplexVar_New*, std::string *WhyNot, const std::string& objective);
      
      
      
      using cvToType=Implements_Data_Type_New_map<K,T>* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_ComplexVar_New* cv,
      std::string* whyNot,const std::string& masterObjective);
      
      using typeToCv= Implements_ComplexVar_New* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_Data_Type_New_map<K,T>* classType,
      std::string* whyNot,const std::string& masterObjective);
      
      
      
      
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
      
      virtual Implements_ComplexVar_New* getComplexVarofTypeRep(
          const Implements_ComplexVar_New* cm,
          const ABC_Type_of_Value* var,std::string* whyNot,const std::string& masterObjective)const override
      {
        if (getCvFromType_==nullptr)
          return nullptr;
        else
          {
            auto v=dynamic_cast<const Implements_Data_Type_New_map<K,T>*>(var);
            if (v==nullptr)
              return nullptr;
            else
              return (*getCvFromType_)(cm,v,whyNot,masterObjective);
          }
      }
      
      virtual Implements_Data_Type_New_map<K,T>* getTypeClassRep(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* cvar,
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
                                   ,cvToType getTypeFromCV
                                   ,typeToCv getCvFromType
                                   ):
        Implements_Dictionary_Type_New<K,T,My_map>
        (parent,id,var,tip,whatthis,keyVar,elementVar,complyPred,typeComply,keyComply
         ,elemeComply,defaultValue)
      ,getTypeFromCV_(getTypeFromCV),getCvFromType_(getCvFromType)
      {
      }
      
      Implements_Data_Type_New_map(const Implements_ComplexVar_New* parent
                                   ):
        Implements_Dictionary_Type_New<K,T,My_map>
        (parent)
      ,getTypeFromCV_(nullptr),getCvFromType_(nullptr)
      {
      }
      
      
    private:
      cvToType getTypeFromCV_;
      typeToCv getCvFromType_;
      
      
    };
    
    

    
  }




  namespace Variable {
    struct types;
  }




  namespace _private {
    
    
    
    class Implements_Data_Type_New_ABC_Var_New:
        public Implements_Base_Type_New<ABC_Var_New*>
        
    {
      
    public:
      using typetypePredicate=typename Implements_Base_Type_New<ABC_Var_New*>::typetypePredicate;
      using typeValue=typename Implements_Base_Type_New<ABC_Var_New*>::typeValue;
      
      using cvToType=Implements_Data_Type_New_ABC_Var_New* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_ComplexVar_New* cv,
      std::string* whyNot,const std::string& masterObjective);
      
      using typeToCv= Implements_ComplexVar_New* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_Data_Type_New_ABC_Var_New* classType,
      std::string* whyNot,const std::string& masterObjective);

      static std::string ClassName();
      
      virtual std::string myClass()const override;
      
      virtual bool isVarInDomain(const Implements_ComplexVar_New* cm,const ABC_Var_New* const val, std::string *whyNot,const std::string& masterObjective ) const override;
      virtual bool put(const Implements_ComplexVar_New* cm,
                       const ABC_Var_New* v,ABC_Output* ostream
                       ,std::string* whyNot
                       ,const std::string& masterObjective)const override;
      virtual bool get(const Implements_ComplexVar_New* cm
                       ,ABC_Var_New*& v, ABC_Input* istream,std::string* whyNot
                       ,const std::string& masterObjective)const override;
      
      
      virtual Implements_ComplexVar_New* getComplexVarofTypeRep(
          const Implements_ComplexVar_New* cm,
          const ABC_Type_of_Value* var,std::string* whyNot,const std::string& masterObjective)const override;
      
      virtual Implements_Data_Type_New_ABC_Var_New* getTypeClassRep(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* cvar,
          std::string* whyNot,
          const std::string& masterObjective)const override;
      
      
      virtual ~Implements_Data_Type_New_ABC_Var_New();
      
      
      
      static Implements_Data_Type_New_ABC_Var_New*
      makeABC_Var_Type_Of_CV(
          const Implements_ComplexVar_New* cm,
          const Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>>* varMap
          );
      
      
      virtual buildByToken<std::string>*
      getNewIdentifierBuildByToken(const Implements_ComplexVar_New* cm)const;
      
      
      const Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>> *
      getParentType()const;
      
      
      virtual buildByToken<std::string>* getVarIdentifierBuildByToken(const Implements_ComplexVar_New* cm, const std::string id)const;
      
      virtual buildByToken<std::string>* getVarIdentifierBuildByToken(const Implements_ComplexVar_New* cm)const;
      
      virtual buildByToken<ABC_Var_New*>* getBuildByToken(const Implements_ComplexVar_New* cm)const override;
      
      friend class Variable::types;
      
    private:
      
      Implements_Data_Type_New_ABC_Var_New(
          const Implements_ComplexVar_New* parent,
          const std::string& id
          ,const std::string& var
          ,const std::string& tip
          ,const std::string& whatthis
          , const Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>>* varMap
          , const Implements_Identifier* idType
          , const Implements_Identifier* varType
          ,typetypePredicate typeComply
          ,cvToType getTypeFromCV
          ,typeToCv getCvFromType
          );
      
      const Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>>* varMap_;
      const Implements_Identifier* idType_;
      const Implements_Identifier* varType_;
    protected:
      cvToType getTypeFromCV_;
      typeToCv getCvFromType_;
      
    };
    
    inline
    bool includesVar(
        const Implements_ComplexVar_New* cm
        ,const std::map<std::string,ABC_Var_New*>&val
        ,const std::map<std::string,ABC_Var_New*>& valTemplate
        ,std::string *whyNot,const std::string& masterObjective )
    {
      for (auto& e:valTemplate)
        {
          auto it=val.find(e.first);
          if (it==val.end())
            {
              *whyNot=masterObjective+": "+e.first+" not found";
              return false;
            }
          else
            {
              if (e.second==nullptr)
                {
                  *whyNot=masterObjective+": "+"invalid template: "+e.first+ "is null";
                  return false;
                }
              else{
                  const ABC_Type_of_Value *t=
                      cm->idToType(e.second->myType(),whyNot,masterObjective);
                  if(t==nullptr)
                    return false;
                  else
                    {
                      const ABC_Var_New* o=it->second;
                      if (o==nullptr)
                        {
                          *whyNot=masterObjective+": "+"invalid value: "+e.first+ "is null";
                          return false;
                        }
                      else if(!t->isVarInDomain(cm,o->value(),whyNot,masterObjective))
                        {
                          return false;
                        }
                      
                    }
                  
                }
            }
        }
      return true;
      
    }
    inline
    bool includesType(
        const Implements_ComplexVar_New* cm
        ,const std::map<std::string,ABC_Var_New*>&val
        ,const std::map<std::string,ABC_Var_New*>& valTemplate
        ,std::string *whyNot,const std::string& masterObjective )
    {
      for (auto& e:valTemplate)
        {
          auto it=val.find(e.first);
          if (it==val.end())
            {
              *whyNot=masterObjective+": "+e.first+" not found";
              return false;
            }
          else
            {
              if (e.second==nullptr)
                {
                  *whyNot=masterObjective+": "+"invalid template: "+e.first+ "is null";
                  return false;
                }
              else{
                  const ABC_Type_of_Value *t=
                      cm->idToType(e.second->myType(),whyNot,masterObjective);
                  if(t==nullptr)
                    return false;
                  else
                    {
                      const ABC_Var_New* o=it->second;
                      if (o==nullptr)
                        {
                          *whyNot=masterObjective
                              +": "+"invalid value: "+e.first+ "is null";
                          return false;
                        }
                      else
                        {
                          const ABC_Type_of_Value *tv=
                              cm->idToType(o->myType(),whyNot,masterObjective);
                          if (tv==nullptr)
                            return false;
                          else if(!t->isTypeInDomain(cm,tv,whyNot,masterObjective))
                            {
                              return false;
                            }
                        }
                    }
                  
                }
            }
        }
      return true;
      
    }
    
    
    
    
    class Implements_Data_Type_New_map_string_ABC_Var_New
        :public Implements_Container_Type_New<ABC_Var_New*,String_map>
    {
    public:

      using typePredicate= bool (*)(const Implements_ComplexVar_New* cm
      ,const std::map<std::string,ABC_Var_New*>&val
      ,const Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>>* valtype
      ,std::string *whyNot,const std::string& masterObjective );
      
      using typetypePredicate= bool (*)(const Implements_ComplexVar_New* cm
      ,const Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>>* val
      ,const Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>>* valtype
      , std::string *whyNot
      ,const std::string& masterObjective );
      
      using typeValue=std::map<std::string,ABC_Var_New*>(*)(const Implements_ComplexVar_New*
      ,const Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>>* valtype
      );
      
      
      
      using typeElementPredicate = bool(*)(
      const Implements_ComplexVar_New*
      ,const std::map<std::string,ABC_Var_New*> &
      ,ABC_Var_New*const&
      ,const Implements_Data_Type_New_map_string_ABC_Var_New*
      , std::string *WhyNot, const std::string& objective);
      
      
      using cvToType=Implements_Data_Type_New_map_string_ABC_Var_New* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_ComplexVar_New* cv,
      std::string* whyNot,const std::string& masterObjective);
      
      using typeToCv= Implements_ComplexVar_New* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_Data_Type_New_map_string_ABC_Var_New* classType,
      std::string* whyNot,const std::string& masterObjective);
      
      
      virtual bool isVarInDomain(const Implements_ComplexVar_New* cm,const std::map<std::string,ABC_Var_New*>&val, std::string *whyNot,const std::string& masterObjective ) const override
      {
        if (comply_!=nullptr)
          return (*comply_)(cm,val,this,whyNot,masterObjective);
        else return true;
      }
      
      
      virtual bool isTypeInDomain(const Implements_ComplexVar_New* cm
                                  ,const Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>>* val
                                  , std::string *whyNot
                                  ,const std::string& masterObjective ) const override
      {
        if (typeComply_!=nullptr)
          return (*typeComply_)(cm,val,this,whyNot,masterObjective);
        else return true;
      }
      
      
      
      
      virtual Implements_ComplexVar_New* getComplexVarofTypeRep(
          const Implements_ComplexVar_New* cm,
          const ABC_Type_of_Value* var,std::string* whyNot,const std::string& masterObjective)const override
      {
        return nullptr;
      }
      
      virtual ABC_Type_of_Value* getTypeClassRep
      (const Implements_ComplexVar_New* cm,
       const Implements_ComplexVar_New* cvar,
       std::string* whyNot,
       const std::string& masterObjective)const
      {
        return nullptr;
      }
      
      
      bool hasFieldName(const std::string& idCandidate,std::string *WhyNot,const std::string& objective)const
      {
        auto it=fields_.find(idCandidate);
        if(it==fields_.end())
          {
            *WhyNot=objective+": "+idCandidate+ "is not a field of"+id();
            return false;
          }
        else
          return true;
      }
      
      const std::map<std::string,ABC_Var_New*> &getFields()const
      {
        return fields_;
      }
      
      
      const ABC_Var_New* getFieldVar(const std::string& idCandidate,std::string *WhyNot,const std::string& objective)const
      {
        auto it=fields_.find(idCandidate);
        if(it==fields_.end())
          {
            *WhyNot=objective+": "+idCandidate+ "is not a field of"+id();
            return nullptr;
          }
        else
          return it->second;
        
      }
      
      
      virtual const Implements_Data_Type_New<ABC_Var_New*>* getElementDataType(const Implements_ComplexVar_New *cm) const override
      {
        return varEType_;
      }
      
      virtual buildByToken<ABC_Var_New*>* getElementBuildByToken(const Implements_ComplexVar_New* cm)const override
      {
        return new buildByToken<ABC_Var_New*>(cm,getElementDataType(cm));
      }

      
      
      
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
      
      Implements_Data_Type_New_map_string_ABC_Var_New(
          const Implements_ComplexVar_New* parent,
          const std::string& id
          ,const std::string& var
          ,const std::string& tip
          ,const std::string& whatthis
          , const std::map<std::string,ABC_Var_New*> fields
          ,typePredicate complyPred
          ,typetypePredicate typeComply
          ,typeElementPredicate elemeComply
          ,typeValue  defaultValue);
      
      

      
      
    private:
      typePredicate comply_;
      typetypePredicate typeComply_;
      typeElementPredicate elemComply_;
      typeValue default_;
      
      
      const Implements_Data_Type_New<ABC_Var_New*>* varEType_;
      std::map<std::string,ABC_Var_New*> fields_;
      
    };
    
    
    
    
    
  };
  
  namespace Real
  {
    struct types
    {
      struct nonZero
      {
        typedef  double myC;
        static std::string idVar(){return "real_nonZero";}
        static std::string idType(){return Cls<myC>::name();}
        static std::string Tip(){return "any non zero real number";}
        static std::string WhatThis() {return "";}

        static bool comply
        (const Implements_ComplexVar_New*
         ,const myC& x
         ,const Implements_ComplexVar_New* ,
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

        static Implements_Data_Type_New<myC>*
        varType(const Implements_ComplexVar_New* cm)
        {
          return new Implements_Data_Type_New<myC>
              (cm,idVar(),idType(),Tip(),WhatThis(),std::numeric_limits<double>::quiet_NaN()
               ,&comply,nullptr,nullptr,nullptr,nullptr);
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
  
  
  namespace Variable {
     typedef Implements_Data_Type_New<ABC_Var_New*> vType;

    struct types
    {

      struct varNew{
        typedef  ABC_Var_New* myC;
        static std::string myId(){return "_varNew";}
        static std::string myId(const ABC_Type_of_Value* t){return myId()+t->id();}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){ return "tip";}
        static std::string myWhatThis() {return "aht";}
        static bool comply(
            const Implements_ComplexVar_New* p,
            const Implements_Data_Type_New<myC>* idtype,
            const Implements_ComplexVar_New* self,
            std::string *WhyNot, const std::string &objective)
        {
          if (idtype->id()==self->id())
            return true;
          else
            {

              return false;
            }
        }


        static Implements_Data_Type_New<myC>*
        varType(const Implements_ComplexVar_New* cm)
        {

          return new Implements_Data_Type_New<ABC_Var_New*>(
                cm,
                myId()
                ,myIdType()
                ,myTip()
                ,myWhatThis()
                ,nullptr
                ,Identifier::types::idVarUsed::varType(cm)
                ,Identifier::types::idType::varType(cm)
                ,&comply,nullptr,nullptr);
        }

        static Implements_Data_Type_New<myC>*
        varType(const Implements_ComplexVar_New* cm,
                const ABC_Type_of_Value* t)
        {

          return new Implements_Data_Type_New<ABC_Var_New*>(
                cm,
                myId(t)
                ,myIdType()
                ,myTip()
                ,myWhatThis()
                ,nullptr
                ,Identifier::types::idVarUsed::varType(cm,t)
                ,Identifier::types::idType::varType(cm)
                ,&comply,nullptr,nullptr);
        }

      };

      struct varUsed{
        typedef  ABC_Var_New* myC;
        static std::string myId(){return "_varUsed";}
        static std::string myId(const ABC_Type_of_Value* t){return myId()+t->id();}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){ return "tip";}
        static std::string myWhatThis() {return "aht";}
        static bool comply(
            const Implements_ComplexVar_New* p,
            const Implements_Data_Type_New<myC>* idtype,
            const Implements_ComplexVar_New* self,
            std::string *WhyNot, const std::string &objective)
        {
          if (idtype->id()==self->id())
            return true;
          else
            {

              return false;
            }
        }


        static Implements_Data_Type_New<myC>*
        varType(const Implements_ComplexVar_New* cm,
                const ABC_Type_of_Value* t)
        {

          return new Implements_Data_Type_New<ABC_Var_New*>(
                cm,
                myId(t)
                ,myIdType()
                ,myTip()
                ,myWhatThis()
                ,nullptr
                ,Identifier::types::idVarNew::varType(cm,t)
                ,Identifier::types::idType::varType(cm,t)
                ,&comply,nullptr,nullptr);
        }

        static Implements_Data_Type_New<myC>*
        varType(const Implements_ComplexVar_New* cm)
        {

          return new Implements_Data_Type_New<ABC_Var_New*>(
                cm,
                myId()
                ,myIdType()
                ,myTip()
                ,myWhatThis()
                ,nullptr
                ,Identifier::types::idVarNew::varType(cm)
                ,Identifier::types::idType::varType(cm)
                ,&comply,nullptr,nullptr);
        }


      };


      struct varField{
        typedef  ABC_Var_New* myC;
        static std::string myId(const Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>>* varMap){return "_varField"+varMap->id();}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(){ return "tip";}
        static std::string myWhatThis() {return "aht";}
        static bool comply(
            const Implements_ComplexVar_New* p,
            const Implements_Data_Type_New<myC>* idtype,
            const Implements_ComplexVar_New* self,
            std::string *WhyNot, const std::string &objective)
        {
          if (idtype->id()==self->id())
            return true;
          else
            {
              return false;
            }
        }


        static Implements_Data_Type_New<myC>*
        varType(const Implements_ComplexVar_New* cm,
                const Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>>* varMap)
        {

          return new Implements_Data_Type_New<ABC_Var_New*>(
                cm,
                myId(varMap)
                ,myIdType()
                ,myTip()
                ,myWhatThis()
                ,varMap
                ,Identifier::types::idField::varType(cm,varMap)
                ,Identifier::types::idType::varType(cm)
                ,&comply,nullptr,nullptr);
        }


      };




    };
  };


  namespace ComplexVar
  {
    typedef std::map<std::string,ABC_Var_New*> myC;

    namespace types
    {

      struct ClassDescript
      {
        static std::string myId(const std::string& id){return "_CV"+id;}
        static std::string myIdType(){return Cls<myC>::name();}
        static std::string myTip(const std::string& id){return "fields map of "+id;}
        static std::string myWhatThis();




        static bool varComply(const Implements_ComplexVar_New* cm
                              ,const myC &val
                              ,const Implements_Data_Type_New<myC>* valtype
                              ,std::string *whyNot,const std::string& masterObjective)
        {
          return _private::includesVar(cm,val,valtype->getFields(),whyNot,masterObjective);
        }
        static bool typeComply(
            const Implements_ComplexVar_New* cm
            ,const Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>>* val
            ,const Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>>* valtype
            ,std::string *whyNot,const std::string& masterObjective )
        {
          return _private::includesType(
                cm,val->getFields(),valtype->getFields(),whyNot,masterObjective);
        }

        static bool typeElementComply(
            const Implements_ComplexVar_New* cm
            ,const std::map<std::string,ABC_Var_New*> & m
            ,ABC_Var_New*const& v
            ,const Implements_Data_Type_New<myC>* t
            , std::string *WhyNot, const std::string& objective)
        {
          if (v==nullptr)
            {
              *WhyNot=objective+": invalid var provided";
              return false;
            }
          else
            {
              auto& f=t->getFields();
              auto it=f.find(v->id());
              if (it==f.end())
                {
                  *WhyNot=objective+": "+v->id()+" is not a field of "+t->id();
                  return false;
                }
              else
                {
                  auto it2=m.find(v->id());
                  if (it2!=m.end())
                    {
                      ABC_Value_New* val=it2->second->value();
                      if (!val->empty())
                        {
                          *WhyNot=objective+": "+v->id()+" is already filled";
                          return false;
                        }

                    }
                  const ABC_Type_of_Value *t=
                      cm->idToType(it->second->myType(),WhyNot,objective);
                  if(t==nullptr)
                    return false;
                  else
                    return t->isVarInDomain(cm,v->value(),WhyNot,objective);
                }

            }
        }

        static myC getDefault(
            const Implements_ComplexVar_New* cm
            ,const Implements_Data_Type_New<myC>* valtype
            )
        {
          std::map<std::string,ABC_Var_New*> out;
          auto &m=valtype->getFields();
          for (auto &e:m)
            {
              ABC_Var_New* o=e.second->create(cm);
              out.insert({o->id(),o});
            }
          return out;
        }


        static  Implements_Data_Type_New<myC>* varType(
            const Implements_ComplexVar_New* cm
            , const std::string& id,
            const std::map<std::string,ABC_Var_New*>& fields)
        {

          return new Implements_Data_Type_New<myC>
              (cm
               ,myId(id)
               ,myIdType()
               ,myTip(id)
               ,""
               ,fields
               ,&varComply
               ,&typeComply
               ,&typeElementComply
               ,&getDefault);
        };

      };


    };
  };


  namespace _private {



    template<typename T>
    class Implements_Data_Type_class:public ABC_Typed_Value<T>
    {
    public:

      using typePredicate= bool(*)(const Implements_ComplexVar_New*,const T&,const Implements_Data_Type_class<T>*, std::string*,const std::string& );


      using typetypePredicate= bool (*)(const Implements_ComplexVar_New* cm,const Implements_Data_Type_New<T>* x, Implements_Data_Type_class<T>*v, std::string *whyNot, const std::string& masterObjective);

      using getEmptyObject=T(*)(const Implements_Data_Type_class<T>*, std::string*);

      using cvToType=Implements_Data_Type_class<T>* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_ComplexVar_New* cv,
      std::string* whyNot,const std::string& masterObjective);

      using typeToCv= Implements_ComplexVar_New* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_Data_Type_class<T>* classType,
      std::string* whyNot,const std::string& masterObjective);




      static std::string ClassName()
      {
        return "Implements_Class_Type_New_of"+Cls<T>::name();
      }

      virtual std::string myClass()const override
      {
        return ClassName();
      }



      virtual bool isVarInDomain(const Implements_ComplexVar_New* cm,const ABC_Value_New* v, std::string *whyNot, const std::string& masterObjective)const override
      {
        const std::string objective=masterObjective+": "+this->id()+ "do not has it in domain";
        auto x=dynamicCast<const Implements_Value_New<T>* >(v,whyNot,objective);
        if (x==nullptr)
          {
            return false;
          }
        else
          return isVarInDomain(cm,x->getValued(),whyNot,objective);
      }



      virtual bool isVarInDomain(const Implements_ComplexVar_New* cm,const T& v, std::string *whyNot, const std::string& masterObjective)const override
      {

        if (comply_==nullptr)
          return true;
        else
          return  (*comply_) (cm,v,this,whyNot,masterObjective);
      }




      virtual bool isTypeInDomain(const Implements_ComplexVar_New* cm,const ABC_Type_of_Value* v, std::string *whyNot, const std::string& masterObjective)const override
      {
        const std::string objective=masterObjective+": "+this->id()+ "do not has it in domain";
        auto x=dynamic_cast<const Implements_Data_Type_New<T>* >(v);
        if (x==nullptr)
          {
            return false;
          }
        else
          return isTypeInDomain(cm,x,whyNot,objective);
      }


      virtual bool isTypeInDomain(const Implements_ComplexVar_New* cm,const Implements_Data_Type_New<T>* v, std::string *whyNot, const std::string& masterObjective)const
      {
        if (typeComply_==nullptr)
          return true;
        else
          return (*typeComply_)(cm,v,this,whyNot,masterObjective);
      }




      bool includesThisType(const Implements_ComplexVar_New *cm, const std::string &childType, std::string *whyNot, const std::string &masterObjective) const
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




      virtual bool put(const Implements_ComplexVar_New* cm
                       ,const T& c
                       ,ABC_Output* ostream
                       ,std::string* whyNot
                       , const std::string& masterObjective)const override
      {
        std::map<std::string,ABC_Var_New*> m
            =getComplexMap(cm,c,whyNot,masterObjective);
        if (m.empty())
          return false;
        else
          return CVtype_->put
              (cm,m,ostream,whyNot,masterObjective);
      }

      virtual bool get(const Implements_ComplexVar_New* cm
                       ,T& v
                       , ABC_Input* istream
                       ,std::string* whyNot
                       , std::string& MasterObjective )const
      {
        std::map<std::string,ABC_Var_New*> m;
        if (!CVtype_->get(cm,m,istream,whyNot,MasterObjective))
          return false;
        else
          {
            auto x=getClass(cm,m,whyNot,MasterObjective);
            if (! this->
                isVarInDomain(cm,v,whyNot,MasterObjective))
              return false;
            else
              {
                v=std::move(x);
                return true;
              }
          }
      }



      virtual buildByToken<std::map<std::string,ABC_Var_New*>>* getBuildByToken(const Implements_ComplexVar_New* cm)const
      {
        return new buildByToken<std::map<std::string,ABC_Var_New*>>(cm,CVtype_);
      }


      virtual ~Implements_Data_Type_class(){}


      Implements_Data_Type_class(
          const Implements_ComplexVar_New* parent,
          const std::string& id
          ,const std::string& var
          ,const std::string& tip
          ,const std::string& whatthis
          , const std::map<std::string,ABC_Var_New*> fields
          ,typePredicate complyPred
          ,typetypePredicate typeComply

          ,getEmptyObject  defaultValue
          ,cvToType getTypeFromCV
          ,typeToCv getCvFromType
          ):
        ABC_Typed_Value<T>(parent,id,var,tip,whatthis)
      ,comply_(complyPred)
      ,typeComply_(typeComply)
      ,default_(defaultValue)
      ,CVtype_(nullptr)
      ,getTypeFromCV_(getTypeFromCV),getCvFromType_(getCvFromType)
      {
        CVtype_=ComplexVar::types::ClassDescript::varType(parent,id,fields);
      }


      Implements_Data_Type_class(
          const Implements_ComplexVar_New* parent
          , const std::map<std::string,ABC_Var_New*> fields
          ):
        ABC_Typed_Value<T>(parent)
      ,comply_(nullptr)
      ,typeComply_(nullptr)
      ,default_(nullptr)
      ,CVtype_(nullptr)
      ,getTypeFromCV_(nullptr),getCvFromType_(nullptr)
      {
        CVtype_=ComplexVar::types::ClassDescript::varType(parent,Cls<T>::name(),fields);
      }




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
      virtual Implements_Var_New<T*>* getClassRep(
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

      T getClass(const Implements_ComplexVar_New* cm
                 , std::map<std::string,ABC_Var_New*>  m
                 ,std::string *WhyNot,const std::string& masterObjective)=0;

      std::map<std::string,ABC_Var_New*> getComplexMap(
          const Implements_ComplexVar_New* cm,
          const T* v,std::string *WhyNot,const std::string & masterObjective)=0;


      // ABC_Typed_Value interface
    public:
      virtual Implements_ComplexVar_New *getComplexVarRep(
          const Implements_ComplexVar_New* cm,
          const ABC_Var_New *var, std::string *whyNot, const std::string& masterObjective) const override
      {
        const T* d=var->value()->getValue<T*>();

        std::map<std::string,ABC_Var_New*>* o=getComplexMap(cm,d,whyNot,masterObjective);
        return new Implements_ComplexVar_New
            (var->parent(),var->id(),var->myType(),*o,var->Tip(),var->WhatThis());
      }


      virtual Implements_ComplexVar_New* getComplexVarofTypeRep(
          const Implements_ComplexVar_New* cm,
          const ABC_Type_of_Value* var,std::string* whyNot,const std::string& masterObjective)const override
      {
        if (getCvFromType_==nullptr)
          return nullptr;
        else
          {
            auto v=dynamic_cast<const Implements_Data_Type_class<T>*>(var);
            if (v==nullptr)
              return nullptr;
            else
              return (*getCvFromType_)(cm,v,whyNot,masterObjective);
          }
      }

      virtual Implements_Data_Type_class<T>* getTypeClassRep(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* cvar,
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




    protected:
      typePredicate comply_;
      typetypePredicate typeComply_;
      getEmptyObject default_;
      const Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>>* CVtype_;
    protected:
      cvToType getTypeFromCV_;
      typeToCv getCvFromType_;



    };

    template<typename T>
    class Implements_Data_Type_class<T*>:public ABC_Typed_Value<T*>
    {
    public:

      using typePredicate= bool(*)(const Implements_ComplexVar_New*,const T*
      ,const  Implements_Data_Type_class<T*>*, std::string*, const std::string& );

      using typetypePredicate= bool (*)(const Implements_ComplexVar_New* cm
      ,const Implements_Data_Type_New<T*>* x,const Implements_Data_Type_class<T*>* v, std::string *whyNot, const std::string& masterObjective);


      using getEmptyObject=T*(*)(const Implements_ComplexVar_New*,
      const Implements_Data_Type_class<T*>*);


      using cvToType=Implements_Data_Type_class<T*>* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_ComplexVar_New* cv,
      std::string* whyNot,const std::string& masterObjective);

      using typeToCv= Implements_ComplexVar_New* (*)
      (const Implements_ComplexVar_New* cm
      ,const Implements_Data_Type_class<T*>* classType,
      std::string* whyNot,const std::string& masterObjective);



      static std::string ClassName()
      {
        return "Implements_Class_Type_New_of"+Cls<T>::name()+"ptr";
      }

      virtual std::string myClass()const override
      {
        return ClassName();
      }





      virtual bool isVarInDomain(const Implements_ComplexVar_New* cm,const ABC_Value_New* v, std::string *whyNot, const std::string& masterObjective)const override
      {
        const std::string objective=masterObjective+": "+this->id()+ "do not has it in domain";
        auto x=dynamicCast<const Implements_Value_New<T*>* >(v,whyNot,objective);
        if (x==nullptr)
          {
            return false;
          }
        else
          return isVarInDomain(cm,x->getValued(),whyNot,objective);
      }
      virtual bool isVarInDomain(const Implements_ComplexVar_New* cm,const T* v, std::string *whyNot, const std::string& masterObjective)const
      {
        return  (*comply_) (cm,v,this,whyNot,masterObjective);
      }




      virtual bool isTypeInDomain(const Implements_ComplexVar_New* cm,const ABC_Type_of_Value* v, std::string *whyNot, const std::string& masterObjective)const override
      {
        const std::string objective=masterObjective+": "+this->id()+ "do not has it in domain";
        auto x=dynamic_cast<const Implements_Data_Type_New<T*>* >(v);
        if (x==nullptr)
          {
            return false;
          }
        else
          return isTypeInDomain(cm,x,whyNot,objective);
      }


      virtual bool isTypeInDomain(const Implements_ComplexVar_New* cm,const Implements_Data_Type_New<T*>* v, std::string *whyNot, const std::string& masterObjective)const
      {
        if (typeComply_==nullptr)
          return true;
        else
          return (*typeComply_)(cm,v,this,whyNot,masterObjective);
      }





      bool includesThisType(const Implements_ComplexVar_New *cm, const std::string &childType, std::string *whyNot, const std::string &masterObjective) const
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






      virtual bool put(const Implements_ComplexVar_New* cm
                       ,const T* c
                       ,ABC_Output* ostream
                       ,std::string* whyNot, const std::string& masterObjective)const override
      {

        std::map<std::string,ABC_Var_New*> m
            =getComplexMap(cm,c,whyNot,masterObjective);
        if (m.empty())
          return false;
        else
          return CVtype_->put
              (cm,m,ostream,whyNot,masterObjective);
      }

      virtual bool get(const Implements_ComplexVar_New* cm
                       ,T*& v
                       , ABC_Input* istream
                       ,std::string* whyNot
                       , const std::string& MasterObjective )const override
      {
        std::map<std::string,ABC_Var_New*> m;
        if (!CVtype_->get(cm,m,istream,whyNot,MasterObjective))
          return false;
        else
          {
            v=getClass(cm,m,whyNot,MasterObjective);
            if (v==nullptr)
              return false;
            else return true;
          }
      }



      virtual buildByToken<std::map<std::string,ABC_Var_New*>>* getBuildByToken(const Implements_ComplexVar_New* cm)const
      {
        return new buildByToken<std::map<std::string,ABC_Var_New*>>(cm,CVtype_);
      }


      virtual ~Implements_Data_Type_class(){}


      Implements_Data_Type_class(
          const Implements_ComplexVar_New* parent,
          const std::string& id
          ,const std::string& var
          ,const std::string& tip
          ,const std::string& whatthis
          , const std::map<std::string,ABC_Var_New*> fields
          ,typePredicate complyPred
          ,typetypePredicate typeComply
          ,getEmptyObject  defaultValue
          ,cvToType getTypeFromCV
          ,typeToCv getCvFromType
          ):
        ABC_Typed_Value<T*>(parent,id,var,tip,whatthis)
      ,comply_(complyPred)
      ,typeComply_(typeComply)
      ,default_(defaultValue)
      ,CVtype_(nullptr)
      ,getTypeFromCV_(getTypeFromCV),getCvFromType_(getCvFromType)
      {
        CVtype_=ComplexVar::types::ClassDescript::varType(parent,id,fields);

      }


      Implements_Data_Type_class(
          const Implements_ComplexVar_New* parent
          , const std::map<std::string,ABC_Var_New*> fields
          ):
        ABC_Typed_Value<T*>(parent)
      ,comply_(nullptr)
      ,typeComply_(nullptr)
      ,default_(nullptr)
      ,CVtype_(nullptr)
      ,getTypeFromCV_(nullptr),getCvFromType_(nullptr)
      {
        CVtype_=ComplexVar::types::ClassDescript::varType(parent,Cls<T*>::name(),fields);
      }


      // ABC_Type_of_Value interface
    public:
      virtual Implements_Value_New<T*>* empty_Value()const override
      {
        return new Implements_Value_New<T*>();
      }


      virtual Implements_Var_New<T*> *empty_Var(const Implements_ComplexVar_New *parent, const std::string &idN, const std::string &tip, const std::string &whathis) const override
      {
        return new Implements_Var_New<T*>(parent,idN,this->id(),tip,whathis,empty_Value());
      }


      virtual Implements_Value_New<T*> *default_Value(const Implements_ComplexVar_New* cm) const override
      {
        return new Implements_Value_New<T*>(getDefault_Valued(cm));
      }

      virtual Implements_Var_New<T*> *default_Var(const Implements_ComplexVar_New *parent, const std::string &idN, const std::string &tip, const std::string &whathis) const override
      {
        return new Implements_Var_New<T*>(parent,idN,this->id(),tip,whathis,default_Value(parent));
      }



      // ABC_Typed_Value interface
    public:
      virtual T* getDefault_Valued(const Implements_ComplexVar_New* cm) const override
      {
        if (default_!=nullptr)
          return (*default_)(cm,this);
        else
          return nullptr;
      }

      // ABC_Type_of_Value interface
    public:
      virtual Implements_Var_New<T*>* getClassRep(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New *m
          , std::string *whyNot,
          const std::string& masterObjective) const override
      {
        T* o=getClass(cm,m->value()->getValued(),whyNot,masterObjective);
        if (o!=nullptr)
          return new Implements_Var_New<T*>
              (m->parent(),m->id(),m->myType(),o,m->Tip(),m->WhatThis());
        else
          return nullptr;

      }

      virtual T* getClass(const Implements_ComplexVar_New* cm
                          ,std::map<std::string,ABC_Var_New*>  m
                          ,std::string *WhyNot,const std::string& masterObjective)const
      {
        return nullptr;
      }
      ;

      virtual std::map<std::string,ABC_Var_New*> getComplexMap(
          const Implements_ComplexVar_New* cm,
          const T* v,std::string *WhyNot,const std::string & masterObjective)const
      {
        return {};
      }


      virtual Implements_ComplexVar_New* getComplexVarofTypeRep(
          const Implements_ComplexVar_New* cm,
          const ABC_Type_of_Value* var,std::string* whyNot,const std::string& masterObjective)const override
      {
        if (getCvFromType_==nullptr)
          return nullptr;
        else
          {
            auto v=dynamic_cast<const Implements_Data_Type_class<T*>*>(var);
            if (v==nullptr)
              return nullptr;
            else
              return (*getCvFromType_)(cm,v,whyNot,masterObjective);
          }
      }

      virtual Implements_Data_Type_class<T*>* getTypeClassRep(
          const Implements_ComplexVar_New* cm,
          const Implements_ComplexVar_New* cvar,
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



      // ABC_Typed_Value interface
    public:
      virtual Implements_ComplexVar_New *getComplexVarRep(
          const Implements_ComplexVar_New* cm,
          const ABC_Var_New *var, std::string *whyNot, const std::string& masterObjective) const override
      {
        if (var==nullptr)
          return nullptr;
        const T* d=var->value()->getValue<T*>();

        std::map<std::string,ABC_Var_New*> o=getComplexMap(cm,d,whyNot,masterObjective);
        return new Implements_ComplexVar_New
            (var->parent(),var->id(),var->myType(),o,var->Tip(),var->WhatThis());
      }

    protected:
      typePredicate comply_;
      typetypePredicate typeComply_;
      getEmptyObject default_;
      const Implements_Data_Type_New<std::map<std::string,ABC_Var_New*>>* CVtype_;
      cvToType getTypeFromCV_;
      typeToCv getCvFromType_;

    };




  }





  template<typename T>
  class Implements_Parameters_Type_New:public ABC_Typed_Value<T*>
  {
  public:

    using typePredicate= bool(*)(const Implements_ComplexVar_New*,const T*&,const Implements_Parameters_Type_New<T>*, std::string*);

    using getEmptyObject=T*(*)(const Implements_Parameters_Type_New<T>*, std::string*);

    using plainPredicate
    = bool(*)(const std::map<std::string,Implements_Value_New<double>*>*,const Implements_Parameters_Type_New<T>*, std::string*);

    using getEmptyMap=std::map<std::string,ABC_Var_New*> (*)(const Implements_Parameters_Type_New<T>*, std::string*);

    using getMap=std::map<std::string,ABC_Var_New*> (*)(const T*&, const Implements_Parameters_Type_New<T>*, std::string*);

    using getObject= T* (*)(const std::map<std::string,ABC_Var_New*>*,const _private::Implements_Data_Type_class<T>*,std::string*);


    static std::string ClassName()
    {
      return "Implements_Class_Type_New_of"+Cls<T*>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }


    virtual bool put(const Implements_ComplexVar_New* cm,const T*& v,ABC_Output* ostream,std::string* error)const
    {

      ostream->put(v);
      return true;
    }

    virtual bool get(const Implements_ComplexVar_New* cm,T*& v, ABC_Input* istream,std::string* whyNot )const
    {

      if (!istream->get(v,whyNot))
        return false;
      else
        return isVarInDomain(*v,whyNot);
    }



    virtual buildByToken<T*>* getBuildByToken(const Implements_ComplexVar_New* cm)const
    {
      return new buildByToken<T*>(cm,this->id());
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
      ABC_Typed_Value<T*>(parent,id,var,tip,whatthis)
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
    virtual Implements_Value_New<T*>* empty_Value()const override
    {
      return new Implements_Value_New<T*>();
    }


    virtual Implements_Var_New<T*> *empty_Var(const Implements_ComplexVar_New *parent, const std::string &idN, const std::string &tip, const std::string &whathis) const override
    {
      return new Implements_Var_New<T*>(parent,idN,this->id(),tip,whathis,empty_Value());
    }


    virtual Implements_Value_New<T*> *default_Value(const Implements_ComplexVar_New* cm) const override
    {
      return Implements_Value_New<T*>(getDefault_Valued(cm));
    }

    virtual Implements_Var_New<T*> *default_Var(const Implements_ComplexVar_New *parent, const std::string &idN, const std::string &tip, const std::string &whathis) const override
    {
      return new Implements_Var_New<T*>(parent,idN,this->id(),tip,whathis,default_Value(parent));
    }



    // ABC_Typed_Value interface
  public:
    virtual T* getDefault_Valued(const Implements_ComplexVar_New* cm) const override
    {
      if (default_!=nullptr)
        return (*default_)(this,this);
      else
        return new T*{};
    }

    // ABC_Type_of_Value interface
  public:
    virtual Implements_Var_New<T*>* getClassRep(const Implements_ComplexVar_New *m, std::string *whyNot) const override
    {
      auto o=(*toObj_)(m->value()->getValued(),this,whyNot);
      if (o!=nullptr)
        return Implements_Var_New<T*>
            (m->parent(),m->id(),m->myType(),m->Tip(),m->WhatThis()
             ,new Implements_Value_New<T*>(o));
      else
        return nullptr;

    }


    // ABC_Typed_Value interface
  public:
    virtual Implements_ComplexVar_New *getComplexVarTyeped_Rep(const Implements_Var_New<T*> *var, std::string *whyNot) const override
    {

    }
  };

  class Markov_CommandManagerVar;



  class Implements_Command_Arguments: public Implements_ComplexVar_New
  {
  public:
    constexpr static auto OP="Op_";

    static bool isMandatory(const std::string field)
    {
      if (field.find(OP,0)==0)
        return false;
      else return true;
    }
    virtual ~Implements_Command_Arguments(){}




    Implements_Command_Arguments(const Implements_ComplexVar_New* parent,
                                 const std::string& id
                                 ,const std::string& var
                                 ,std::map<std::string,ABC_Var_New*> m
                                 ,const std::string& tip
                                 ,const std::string& whatthis):
      Implements_ComplexVar_New(parent,id,var,m,tip,whatthis){}

  };


  class Implements_Command_Type_New:
      public _private::Implements_Data_Type_New_map_string_ABC_Var_New
  {
  public:
    using plainPredicate
    = bool(*)
    (const Implements_ComplexVar_New* cm,
    const std::map<std::string,ABC_Var_New*>,
    const Implements_Command_Type_New*
    , std::string*
    , const std::string&);

    using getEmptyMap
    =std::map<std::string,ABC_Var_New*> (*)
    (const Implements_Command_Type_New*, std::string*, const std::string&);

    using runCommand
    = bool  (*)
    (Markov_CommandManagerVar* cm
    , const std::map<std::string,ABC_Var_New*>& arguments
    ,const Implements_Command_Type_New* self
    ,std::string* WhyFail, const std::string& masterObjective);


    static std::string ClassName()
    {
      return "Implements_Command_Type_New";
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    buildByToken<std::string>* getBuildIdCommand(const Implements_ComplexVar_New* cm)const
    {

      return new buildByToken<std::string>(cm,this->getSelfIdType());

    }

    virtual ABC_Var_New* nextField(const Implements_ComplexVar_New* cm,
                                   const Implements_Command_Arguments* current)const
    {
      return nullptr;
    }

    virtual ~Implements_Command_Type_New(){}


    Implements_Command_Type_New(const Implements_ComplexVar_New* parent,
                                const std::string& id
                                ,const std::string& var
                                ,const std::string& tip
                                ,const std::string& whatthis
                                ,plainPredicate hasAllI
                                ,plainPredicate mandatoryInp
                                ,getEmptyMap toEmMap
                                ,runCommand run_):
      _private::Implements_Data_Type_New_map_string_ABC_Var_New      (parent,id,var,tip,whatthis,{},nullptr,nullptr,nullptr,nullptr)
    ,hasAllInputs_(hasAllI)
    ,hasMandatoryInputs_(mandatoryInp)
    ,toEmMap_(toEmMap)
    ,run_(run_)
    {}

  protected:
    plainPredicate hasAllInputs_;
    plainPredicate hasMandatoryInputs_;


    getEmptyMap toEmMap_;
    runCommand run_;

    // ABC_Type_of_Value interface
  public:
    virtual Implements_Value_New<std::map<std::string,ABC_Var_New*>>* empty_Value()const override
    {
      return nullptr;
    }


    Implements_Command_Arguments* getCommandField(
        const Implements_ComplexVar_New* cm )const
    {
      return new Implements_Command_Arguments(
            cm,"",this->id(),{},this->Tip(),this->WhatThis());
    }

    virtual bool hasAllInputs(const Implements_ComplexVar_New* cm,
                              const Implements_Command_Arguments* a)const
    {
      if (hasAllInputs_== nullptr)
        return true;
      else
        {
          std::string whyNot;
          return (*hasAllInputs_)(cm,a->value()->getValued()
                                  ,this,&whyNot,"");
        }
    }

    virtual bool hasAllMandatoryInputs(
        const Implements_ComplexVar_New* cm,
        const Implements_Command_Arguments* a)const
    {
      if (hasMandatoryInputs_==nullptr)
        return true;
      else
        {
          std::string whyNot;
          return (*hasMandatoryInputs_)(cm,a->value()->getValued()
                                        ,this,&whyNot,"");
        }
    }

    virtual bool run(Markov_CommandManagerVar* cm,
                     const std::map<std::string,ABC_Var_New*>& m,
                     std::string *WhyNot, const std::string& masterObjective)const
    {
      return (*run_)(cm,m,this,WhyNot,masterObjective);
    }



    virtual Implements_Command_Arguments *empty_Var(const Implements_ComplexVar_New *parent, const std::string &idN, const std::string &tip, const std::string &whathis) const override
    {
      return nullptr;
    }


    virtual Implements_Value_New<std::map<std::string,ABC_Var_New*>> *default_Value(const Implements_ComplexVar_New* cm) const override
    {
      return  nullptr;
    }

    virtual Implements_Command_Arguments *default_Var(const Implements_ComplexVar_New *parent, const std::string &idN, const std::string &tip, const std::string &whathis) const override
    {
      return nullptr;
    }




    // ABC_Type_of_Value interface
  public:
    virtual build_Command_Input *getBuildByToken(const Implements_ComplexVar_New *cm) const override
    {
      return new build_Command_Input(cm,this->getSelfIdType());

    }


    virtual bool includesThisType(const Implements_ComplexVar_New *cm, const std::string &childType, std::string *whyNot, const std::string &masterObjective) const override
    {
      return false;
    }




    // ABC_Type_of_Value interface
  public:
    virtual Implements_ComplexVar_New *getComplexVarRep(const Implements_ComplexVar_New *cm, const ABC_Var_New *var, std::string *whyNot, const std::string &masterObjective) const override
    {
      return nullptr;
    }
    virtual Implements_Command_Arguments *getClassRep(const Implements_ComplexVar_New *cm, const Implements_ComplexVar_New *cvar, std::string *whyNot, const std::string &masterObjective) const override
    {
      return nullptr;
    }


    virtual Implements_ComplexVar_New* getComplexVarofTypeRep(
        const Implements_ComplexVar_New* cm,
        const ABC_Type_of_Value* var,std::string* whyNot,const std::string& masterObjective)const override
    {
      return nullptr;
    }

    virtual Implements_Command_Type_New*
    getTypeClassRep(const Implements_ComplexVar_New* cm,
                    const Implements_ComplexVar_New* cvar,
                    std::string* whyNot,
                    const std::string& masterObjective)const override
    {
      return nullptr;
    }


    // ABC_Typed_Value interface
  public:
    virtual bool put(const Implements_ComplexVar_New *cm, const std::map<std::string,ABC_Var_New*> &v, ABC_Output *ostream, std::string *error, const std::string &masterObjective) const override
    {
      return false;
    }
    virtual bool get(const Implements_ComplexVar_New *cm, std::map<std::string,ABC_Var_New*> &v, ABC_Input *istream, std::string *whyNot, const std::string &masterObjective) const override
    {
      return false;
    }
    virtual std::map<std::string,ABC_Var_New*> getDefault_Valued(const Implements_ComplexVar_New *cm) const override
    {
      return {};
    }
    virtual bool isVarInDomain(const Implements_ComplexVar_New *cm, const std::map<std::string,ABC_Var_New*> &val, std::string *whyNot, const std::string &masterObjective) const override
    {
      return false;
    }
    virtual bool isTypeInDomain(const Implements_ComplexVar_New *cm, const _private::Implements_Data_Type_New_map_string_ABC_Var_New *val, std::string *whyNot, const std::string &masterObjective) const override
    {
      return false;
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
  const T ABC_Value_New::getValue()const
  {
    if (storedClass()==Cls<T>::name())
      {
        auto v =dynamic_cast<const Implements_Value_New<T>*>(this);
        return v->getValued();
      }
    else
      return {};
  }

  template<typename T>
  T ABC_Value_New::getValue()
  {
    if (storedClass()==Cls<T>::name())
      {
        auto v =dynamic_cast< Implements_Value_New<T>*>(this);
        return v->getValued();
      }
    else
      return {};

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
    all_[varT->id()]=varT;
    types_[varT->id()]=varT;
    varT->getSelfIdType();
  }



  namespace _private {



    template<typename T, template<typename> class C>
    const Implements_Data_Type_New<T> *Implements_Container_Type_New<T,C>::getElementDataType(const Implements_ComplexVar_New *cm) const
    {

      std::string eletype=this->template get_Value<fields::elementType_Field>();
      if (!eletype.empty())
        {
          std::string whynot;
          return cm->idToTyped<T>(eletype,&whynot,"");
        }
      else return nullptr;

    }

    template<typename T, template<typename> class C>
    const Implements_Data_Type_New<T*> *Implements_Container_Type_New<T*,C>::getElementDataType(const Implements_ComplexVar_New *cm) const
    {

      std::string eletype=this->template get_Value<fields::elementType_Field>();
      if (!eletype.empty())
        {
          std::string whynot;
          return cm->idToTyped<T*>(eletype,&whynot,"");
        }
      else return nullptr;

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




#endif // IMPLEMENTS_COMPLEXVAR_NEW_H
