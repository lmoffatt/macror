#ifndef ABC_VAR_H
#define ABC_VAR_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <deque>
#include <sstream>
#include <iostream>
#include <limits>
#include <utility>
#include "Markov_LA/Matrix.h"
#include "Markov_IO/ABC_Put.h"
#include "Markov_IO/Token_New.h"





namespace  Markov_IO {


  template<class C,typename T>
  using setter=void (C::*)(T);

  template<class C,typename T>
  using getter=T(C::*)()const;

  template<class C,typename T>
  using refgetter=const T&(C::*)()const;

  template<class C,typename T>
  using refsetter=T&(C::*)();















  std::set<std::string> operator+(std::set<std::string>&& tok1,
                                  std::string &&s);


  std::set<std::string> operator+(std::set<std::string> &&ss1,
                                  std::set<std::string> &&ss2);



  class ABC_TokenProcessor
  {
  public:



    virtual void setTokenStream(Token_Stream* t)=0;
    virtual bool processTokens(Token_Stream& t)
    {

    }

    virtual bool processTokens()=0;

    virtual std::set<std::string> getNextInputCategories()const=0;
    virtual bool pushToken(Markov_IO::Token_New t)=0;
  };





  class ABC_Value;


  /// Variables store all the context information that give meaning to the values.
  /// Unfortunatelly it was cumbersome to create a proper class for variables,
  /// it is distinguished by a the method ABC_Val::isValue()
  typedef ABC_Value ABC_Var;

  /// Measures have actual access to the variables so they have all the information
  /// necessary to give meaning to its values. Besides they might have a custum structure.
  typedef ABC_Value ABC_Measure;


  class ABC_Simple: public ABC_Put
  {
  public:


    static std::string ClassName();

    static std::set<std::string> SuperClasses();




    /// si myClass==SomeClass::ClassName()  => static_cast<SomeClass*>(this)!=nullptr
    virtual std::string myClass() const
    {
      return ClassName();
    }



    virtual std::set<std::string> mySuperClasses() const
    {
      return {ClassName()};
    }


    /// creates an empty object of the same class
    virtual ABC_Simple * create()const=0;  // ABC_Put::create() // same myClass?

    /// creates a stand alone copy of the object,
    /// however it does not have the same parent
    virtual ABC_Simple* clone()const=0;   //






    virtual std::string toString()const;   //

    virtual std::ostream& put(std::ostream& s) const
    {
      s<<toString();
      return s;
    }


    virtual Token_Stream toTokens()const=0;



    virtual bool processTokens(Token_Stream& t)=0;


  };






   class ABC_Base
   {
   public:
     static std::string ClassName()
     {
       return "ABC_Base";
     }

     static std::set<std::string> SuperClasses()
     {
       return {ClassName()};
     }

     virtual std::string myClass() const
     {
       return ClassName();
     }

     virtual std::set<std::string> mySuperClasses() const
     {
       return SuperClasses();
     }

   };








  class ABC_Value: public ABC_Put, public ABC_Base
  {
  public:

    //*****************************************************************
    //                          Static methods
    //*****************************************************************


    static bool isValidId(std::string name);

    static std::string ClassName();

    static std::set<std::string> SuperClasses();

    /// creates an ABC_Value of the right kind of within Complex_Value/Simple_Value
    /// No parent, it should be either deleted or rooted
    static ABC_Value* getValueFromStream(Token_Stream &t);



    //******************************************************************
    //                      Abstract methods
    //******************************************************************

    /// it returns a copy of the value representation of the object
    /// it works as a Parameter
    virtual ABC_Value* to_PlainValue() const =0;

    virtual ABC_Value* to_PlainValue(const ABC_Measure* measure)const =0;


    virtual Token_Stream toTokens()const=0;

    virtual std::string Tip()const=0;
    virtual std::string WhatThis()const=0;

    /// creates an empty object of the same class
    virtual ABC_Value* create()const=0;  // ABC_Put::create() // same myClass?

    /// creates a stand alone copy of the object,
    /// however it does not have the same parent
    virtual ABC_Value* clone()const=0;   //

    virtual std::string id()const=0;
    virtual void setId(const std::string& idName)=0;


    virtual std::string refId()const=0;

    virtual std::string myVar()const=0;



    virtual void setVar(const std::string& varname)=0;

    virtual bool isRootedVariable()const=0;



    ///FIXME: see what to to with it
    virtual const ABC_Var* myVarPtr()const=0;

    virtual ABC_Var* myVarPtr()=0;

    virtual std::set<std::string> modes()const =0;
    virtual bool complyModes(const std::string mode) const=0;





    // invariant varCreate()->processTokens(toTokens())=true


    virtual std::size_t numChilds()const=0;

    virtual ABC_Value* parentValue()=0;
    virtual const ABC_Value* parentValue()const =0;

    virtual void setParentValue(ABC_Value* par)=0;

    virtual std::string ith_ChildName(std::size_t i)const=0;
    virtual std::string childVar(const std::string& idName)const=0;

    virtual const ABC_Value* getChild(const std::string& name)const=0;
    virtual ABC_Value* getChild(const std::string &name)=0;
    virtual void removeChild(const std::string& name)=0;


    virtual const ABC_Value* getChild(const std::string& name,const std::string& kind)const=0;
    virtual ABC_Value* getChild(const std::string &name, const std::string &kind) =0;

    virtual void pushChild(ABC_Value* var)=0;


    virtual void putOut(const std::string& m)const=0;
    virtual void putErrorOut(const std::string& m)const=0;


    virtual ~ABC_Value(){}
    virtual bool isInDomain(const ABC_Value* value)const=0;

    virtual void reset()=0;

    virtual void setTip(const std::string& tip)=0;
    virtual void setWhatThis(const std::string& whatThis)=0;



    //*****************************************************************
    //                        virtual methods
    //******************************************************************

    virtual bool processTokens(Token_Stream& t)=0;
    /// si myClass==SomeClass::ClassName()  => static_cast<SomeClass*>(this)!=nullptr
    virtual std::string myClass() const
    {
      return ClassName();
    }



    virtual std::set<std::string> mySuperClasses() const
    {
      return {ClassName()};
    }

    /// si complyClass(SomeClass::ClassName())  => static_cast<SomeClass*>(this)!=nullptr
    virtual bool complyClass(const std::string classname)const ;


    virtual std::string toString()const;   //

    virtual std::ostream& put(std::ostream& s) const
    {
      s<<toString();
      return s;
    }



    //*****************************************************************
    //                    non-virtual methods
    //******************************************************************



    bool push_current_token(const Token_Stream &tok);

    const std::map<Token_New::Value,std::pair<int,int>>& currentDFAMap();


    /// it uses the information in source to build a fully formed
    /// object
    /// Invariant *this==parentValue()->getChild(myVar())->cloneFromValue(getValueFromStream(this->toTokens));
    ///
    Markov_IO::ABC_Value* toIndicatedVar(const ABC_Value *source) const
    {
      if (source->myVar()==id())
        return toMeasure(source);
      else if (source->myVar()==myClass())
        return toSameVar(source);
      else return nullptr;
    }



    ABC_Measure* getMeasureFromValue(ABC_Value * v)
    {
      if (v)
        {
          auto m=getChild(v->myVar());
          if (m)
            return m->toIndicatedVar(v);
          else
            return nullptr;
        }
      else
        return nullptr;
    }

    bool has_child(const std::string& name)const
    {
      return getChild(name)!=nullptr;
    }


    std::vector<std::string> getChildList()const
    {
      std::vector<std::string> out(numChilds());
      for (std::size_t i=0; i<numChilds(); i++)
        out[i]=ith_ChildName(i);
      return out;
    }

    void pushIdChild(const std::string& id,ABC_Value* var);

    bool sameFields(const ABC_Value* other)const
    {
      if ((other==nullptr)||(numChilds()!=other->numChilds()))
        return false;
      for (std::size_t i=0; i<numChilds(); ++i)
        {
          auto name=ith_ChildName(i);
          auto cl=childVar(name);
          auto o=other->getChild(name,cl);
          if (o==nullptr)
            return false;
        }
      return true;
    }



    // ********************************************************
    //                Template public methods
    //***********************************************************


  public:

    template<typename T>
    bool getVal(const std::string& name, T& value)const;


    template<typename T>
    bool moveVal(const std::string& name, T& value);


    template<typename T>
    bool hasVal(const std::string& name, T& value)const;


    template<typename T>
    T& getReference(const std::string& name, T& value);

    template<typename T>
    void push_backVal(const std::string& name,
                      T value,
                      const std::string& classname="",
                      const std::string& tip="",
                      const std::string & whatthis="");

    void push_backVarRef(const std::string& name,
                         const std::string& idRef,
                         const std::string& classname="",
                         const std::string& tip="",
                         const std::string & whatthis="");



    template<typename T>
    bool replaceValue(const std::string& name, const T& value);

    template<typename Enum>
    void push_back_CategoryItem(const std::string & name,
                                Enum i,
                                const std::string& tip="",
                                const std::string & whatthis="");



    //******************************************************************
    //              protected Abstract methods
    //******************************************************************


  protected:
    virtual ABC_Var* toSameVar(const ABC_Value* source)const=0;


    virtual ABC_Measure* toMeasure(const ABC_Value* source)const=0;



    //******************************************************************
    //              protected static members
    //******************************************************************



  protected:



  };






  class Implements_ValueId: virtual public ABC_Value
  { // ABC_Var interface
  public:

    virtual ABC_Value* create()const override
    {
      return new Implements_ValueId;
    }

    virtual Implements_ValueId* clone() const override
    {
      return new Implements_ValueId(*this);
    }
    virtual void reset() override
    {
      if ((parentValue()!=nullptr)&&(!isRootedVariable()))
        {
          auto s=dynamic_cast<Implements_ValueId*>(parentValue()->getChild(id()));
          if (s!=nullptr)
            *this=*s;

        }

    }






    virtual std::string myVar() const override;
    virtual void setVar(const std::string& varname)override;

    virtual Token_Stream toTokens() const override;

    virtual bool processTokens( Token_Stream& tok) override;




    virtual std::string id()const override;
    virtual void setId(const std::string& IdName)override;

    virtual std::string Tip()const override;
    virtual std::string WhatThis()const override;
    virtual void setTip(const std::string& tip)override;
    virtual void setWhatThis(const std::string& whatThis)override;


    bool isRootedVariable()const override;

    ABC_Value *parentValue() override;
    const ABC_Value *parentValue() const override;
    virtual std::size_t numChilds() const override;
    virtual std::string ith_ChildName(std::size_t) const override;
    virtual std::string childVar(const std::string &) const override;
    virtual const ABC_Value* getChild(const std::string&)const override;
    virtual ABC_Value* getChild(const std::string &) override;

    virtual void removeChild(const std::string& ) override;
    virtual const ABC_Value* getChild(const std::string&, const std::string&)const  override;
    virtual ABC_Value* getChild(const std::string &, const std::string &) override;
    virtual void pushChild(ABC_Value *) override;

    virtual std::string refId()const override;

    //TODO: there are two concepts here: the current holder of the id in parent and the var that is pointed by myVar
    virtual ABC_Var* myVarPtr() override;
    virtual const ABC_Value* myVarPtr() const  override;


    virtual bool complyModes(const std::string m)const override
    {
      if ((parentValue()!=nullptr)
          &&(parentValue()->getChild(myVar())!=nullptr))
        {
          auto const mo=parentValue()->getChild(myVar())->modes();
          if(mo.find(m)!=mo.end())
            return true;
          else
            return false;
        }
      else return false;
    }
    virtual std::set<std::string> modes()const override
    {

      return {};
    }
  protected:
    virtual void setParentValue(ABC_Value *par)override;
  public:
    virtual bool isInDomain(const ABC_Value* value)const override;
    Implements_ValueId(const std::string& name,
                       const std::string& className,
                       const std::string &tip,
                       const std::string &whatthis);

    Implements_ValueId(const ABC_Value& other);

    Implements_ValueId()=default;
    Implements_ValueId(const Implements_ValueId& other)=default;
    Implements_ValueId& operator=(const Implements_ValueId& other)=default;

    Implements_ValueId(Implements_ValueId&& other)=default;
    Implements_ValueId& operator=(Implements_ValueId&& other)=default;

    virtual ~Implements_ValueId(){}


    virtual void putOut(const std::string& m)const;
    virtual void putErrorOut(const std::string& m)const;





    virtual ABC_Value* to_PlainValue() const override;
    virtual ABC_Value* to_PlainValue(const ABC_Measure* )const override
    {
      return nullptr;
    }

    virtual ABC_Value* toMeasure(const ABC_Value* )const override
    {
      return nullptr;
    }


    virtual ABC_Var* toSameVar(const ABC_Value* )const override
    {
      return nullptr;
    }

  protected:

    std::string id_;
    std::string var_;
    ABC_Value* p_;
    std::string tip_;
    std::string whatThis_;



  };








  template<typename T>
  class Implements_Simple_Class;



  template<typename T>
  class ABC_Simple_Value;

  template<typename T>
  class ABC_Simple_Class:  public  virtual Implements_ValueId
  {
  public:

    static std::string ClassName();

    static std::set<std::string> SuperClasses()
    {
      return ABC_Value::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    virtual T defaultValue()const=0;
    virtual T minValue()const=0;
    virtual T maxValue()const=0;
    virtual T emptyValue()const=0;
    virtual T unknownValue()const=0;
    virtual void setDefaultValue(T val)=0;
    virtual void setminValue(T val)=0;
    virtual void setmaxValue(T val)=0;

    virtual std::string units()const=0;
    virtual void setUnits(std::string newunits)=0;



    virtual bool complyModes(const std::string mode)const override=0;

    virtual std::set<std::string> modes()const override=0;
    virtual ~ABC_Simple_Class(){}
  };




  template<typename T>
  class ABC_Simple_Value: public virtual Implements_ValueId
  {
    // ABC_Var interface
  public:
    virtual T value()const=0;
    virtual void setValue(T val)=0;
    virtual void moveVal(T& ){}

    virtual const T& refval()const=0;

    virtual T& refval()=0;

    static std::set<std::string> SuperClasses()
    {
      return ABC_Value::SuperClasses()+ClassName();
    }

    static std::string ClassName()
    {
      return "Simple_Value";
    }




    virtual const ABC_Simple_Class<T>* motherClassType()const
    {
      return dynamic_cast<const ABC_Simple_Class<T>*> (myVarPtr());
    }

    virtual  ABC_Simple_Class<T>* motherClassType()
    {
      return dynamic_cast<ABC_Simple_Class<T>*> (myVarPtr());
    }


    virtual ~ABC_Simple_Value(){}

  };






  template<typename T>
  class Implements_Simple_Value: public ABC_Simple_Value<T>
  {
    // ABC_Var interface
  public:
    static std::string ClassName();

    static std::set<std::string> SuperClasses()
    {
      return ABC_Simple_Value<T>::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    virtual Implements_Simple_Value<T>* create() const override
    {
      return new Implements_Simple_Value<T>();
    }

    virtual Implements_Simple_Value<T>* clone() const override
    {
      return new Implements_Simple_Value<T>(*this);
    }

    virtual void reset() override
    {
      if ((this->parentValue()!=nullptr)&&(!this->isRootedVariable()))
        {
          auto s=dynamic_cast<Implements_Simple_Value<T>*>(this->parentValue()->getChild(this->id()));
          if (s!=nullptr)
            *this=*s;

        }
    }
    virtual  T value()const override
    {
      return value_;
    }

    virtual void moveVal(T& val)
    {
      val=std::move(value_);
    }

    virtual void setValue(T val) override
    {
      value_=std::move(val);
    }
    virtual const T& refval()const override
    {
      return value_;
    }
    virtual T& refval() override
    {
      return value_;
    }

    virtual Token_Stream toTokens() const override
    {
      Token_Stream out=Implements_ValueId::toTokens();
      out.getToken()<<"="<<value()<<"\n";
      return out;
    }



    bool processTokens( Token_Stream& t) override
    {
      bool out=Implements_ValueId::processTokens(t);
      if (!out)
        return out;
      else
        {
          t.tokenAdvance(2);
          if (t.currToken().tok()!=Token_New::ASSIGN)
            {
              return false;
            }
          ++t;
          T val;
          if (!toValue(t,val))
            {
              return false;
            }
          else
            {
              setValue(val);
              if (t.currToken().tok()==Token_New::EOL)
                ++t;
              return true;
            }
        }
    }
    // ABC_Var interface


    Implements_Simple_Value(std::string id,
                            T val,
                            std::string className=ClassName(),
                            const std::string& tip="",
                            const std::string& whatthis=""):
      Implements_ValueId(id,className,tip,whatthis),
      value_(val){}





    Implements_Simple_Value()=default;


    Implements_Simple_Value(const Implements_ValueId& id):
      Implements_ValueId(id.id(),id.myVar(),id.Tip(),id.WhatThis()),
      value_(){}


    Implements_Simple_Value(const Implements_Simple_Value<T>& other)=default;

    Implements_Simple_Value(Implements_Simple_Value<T>&& other)=default;

    Implements_Simple_Value& operator=(const Implements_Simple_Value<T>& other)=default;
    /* {
      if (this!=&other)
        *this=Implements_Simple_Value<T>(other);
      return *this;
    }
*/
    Implements_Simple_Value& operator=(Implements_Simple_Value<T>&& other)=default;

    virtual ~Implements_Simple_Value(){}

    virtual Implements_Simple_Value<T>* to_PlainValue()const  override
    {
      return clone();
    }


  protected:


    T value_;

  };







  template<typename T>
  class Implements_Simple_Measure: public  Implements_Simple_Value<T>, public ABC_Measure
  {


  };




  class Implements_Complex_Value: virtual public  Implements_ValueId
  {
    // ABC_Var interface
  public:
    static std::string ClassName();
    virtual Implements_Complex_Value* create() const override
    {
      return new Implements_Complex_Value;
    }
    virtual Implements_Complex_Value* clone() const override
    {
      return new Implements_Complex_Value(*this);
    }
    virtual void reset() override
    {
      if ((parentValue()!=nullptr)&&(!isRootedVariable()))
        {
          auto s=dynamic_cast<Implements_Complex_Value*>(parentValue()->getChild(id()));
          if (s!=nullptr)
            *this=*s;

        }

    }

    virtual std::size_t numChilds() const override;
    virtual std::string ith_ChildName(std::size_t i) const override;
    virtual std::string childVar(const std::string &idName) const override;
    virtual const ABC_Value* getChild(const std::string& name)const override;


    virtual ABC_Value* popLastChild()
    {
      if (!ids_.empty())
        {
          std::string lastChild=ids_.back();
          ABC_Value* out=getChild(lastChild);
          removeChild(lastChild);
          return out;
        }
      else
        return nullptr;
    }

    std::vector<std::string> getChildList(const std::string& className="")const
    {
      if (className.empty())
        return ids_;
      else
        {
          std::vector<std::string> out;
          for (std::string s:ids_)
            {
              auto it=vars_.find(s);
              if (it!=vars_.end())
                {
                  ABC_Value* v=it->second;
                  if (v->complyClass(className))
                    out.push_back(s);
                }
            }
          return out;
        }
    }


    virtual void removeChild(const std::string& name)override;

    virtual  ABC_Value* getChild(const std::string& name)override;
    virtual const ABC_Value* getChild(const std::string& name,
                                      const std::string &myclass)const override;
    virtual ABC_Value* getChild(const std::string& name, const std::string &myclass) override;
    virtual void pushChild(ABC_Value *var) override;



    Implements_Complex_Value(
        const std::string& id,
        const std::string className,
        const std::string & tip,
        const std::string& whatthis,
        const std::vector<std::pair<std::string,std::string>>& childsNameClass={});


    Implements_Complex_Value(const ABC_Value& other):
      Implements_ValueId(other)
    {

      for (std::size_t i=0; i<other.numChilds(); ++i)
        {
          std::string name=other.ith_ChildName(i);
          auto o=other.getChild(name);
          if (o!=nullptr)
            pushChild(o->clone());
          childclss_[name]=other.childVar(name);
        }
    }



    Implements_Complex_Value()=default;


    Implements_Complex_Value(const Implements_Complex_Value& other)
      :
        Implements_ValueId(other),
        ids_(other.ids_),
        childclss_(other.childclss_),
        vars_(other.vars_)
    {
      cloneChids();
      resetChildsParent();
    }

    Implements_Complex_Value(Implements_Complex_Value&& other):
      Implements_ValueId(std::move(other)),
      ids_(std::move(other.ids_)),
      childclss_(std::move(other.childclss_)),
      vars_(std::move(other.vars_))
    {
      resetChildsParent();
    }

    Implements_Complex_Value& operator=(Implements_Complex_Value&& other)
    {
      if (this!=&other)
        {
          privateDelete();
          Implements_ValueId::operator =(std::move(other));
          ids_=std::move(other.ids_);
          childclss_=std::move(other.childclss_);
          vars_=std::move(other.vars_);
          resetChildsParent();
        }
      return *this;
    }




    Implements_Complex_Value& operator=(const Implements_Complex_Value& other)
    {
      if (this!=&other)
        {
          *this=Implements_Complex_Value(other);
          resetChildsParent();

        }
      return *this;
    }

    void privateDelete()
    {
      for (auto& id:vars_)
        {
          auto o=id.second;
          delete o;
        }
    }


    virtual ~Implements_Complex_Value(){
      privateDelete();
    }

    virtual Token_Stream toTokens() const override;

    virtual bool processTokens( Token_Stream& t) override;






    virtual ABC_Value* to_PlainValue()const override
    {
      return new Implements_Complex_Value(*this);
    }
    //    virtual bool loadFromObjectValue(const ABC_Value* source)override
    //    {
    //      if (sameFields(source))
    //        {
    //          *this=Implements_Complex_Value(*source);
    //          return true;
    //        }
    //      else
    //        return false;
    //    }

  protected:
    void cloneChids()
    {
      for (auto& it:vars_)
        {
          if (it.second!=nullptr)
            {
              ABC_Value* n=it.second->clone();

              it.second=n;
            }
        }
    }

    void resetChildsParent()
    {
      for (auto& it:vars_)
        {
          if (it.second!=nullptr)
            {
              it.second->setParentValue(this);
            }
        }
    }
    std::vector<std::string> ids_;
    std::map<std::string, std::string> childclss_;
    std::map<std::string,ABC_Value*> vars_;

  };





  template<class C>
  class ABCObject:  virtual public Implements_ValueId
  {
    // ABC_Var interface
  public:
    virtual C* getObject() =0;

    virtual const C* getObject()const =0;
    virtual void setObject(C** obj)=0;


    virtual ~ABCObject(){}
  };



  template<class C,typename T>
  class Implements_ValMethod_Var: public ABC_Simple_Value<T>, public ABCObject<C>
  {
    // ABC_Var interface
  public:
    static std::string ClassName()
    {
      return C::ClassName()+"_method";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Value::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    virtual Implements_ValMethod_Var<C,T>* create() const override
    {
      return new Implements_ValMethod_Var<C,T>;
    }

    virtual Implements_ValMethod_Var<C,T>* clone() const override
    {
      return new Implements_ValMethod_Var<C,T>(*this);
    }




    virtual void reset() override
    {
      if ((this->parentValue()!=nullptr)&&(!this->isRootedVariable()))
        {
          auto s=dynamic_cast<Implements_ValMethod_Var<C,T>*>(this->parentValue()->getChild(this->id()));
          if (s!=nullptr)
            *this=*s;

        }
    }
    virtual C* getObject() override
    {
      if (objectPtr_!=nullptr)
        return *objectPtr_;
      else
        return nullptr;
    }

    virtual const C* getObject()const override
    {
      if (objectPtr_!=nullptr)
        return *objectPtr_;
      else
        return nullptr;
    }
    virtual void setObject(C** obj) override
    {
      objectPtr_=obj;
    }


    virtual T& refval() override
    {
      return empty_;
    }

    virtual const T& refval() const override
    {
      return empty_;
    }

    T value()const override
    {
      if ((this->getObject()==nullptr))
        return empty_;
      if (get_!=nullptr)
        return (this->getObject()->*get_)();
      else
        return empty_;
    }

    void setValue(T val) override
    {
      if ((this->getObject()!=nullptr)&& (set_!=nullptr))
        ((this->getObject()->*set_))(val);

    }



    Token_Stream toTokens() const override
    {
      auto out=Implements_ValueId::toTokens();
      out.getToken()<<"="<<value()<<"\n";
      return out;
    }

    bool processTokens( Token_Stream&  t) override
    {
      if (!Implements_ValueId::processTokens(t))
        return false;
      else
        {
          t.tokenAdvance(2);
          if (t.currToken().tok()!=Token_New::ASSIGN)
            return false;
          ++t;
          T val{};
          if (!toValue(t,val))
            return false;
          else
            {
              setValue(val);
              if (t.currToken().tok()==Token_New::EOL)
                ++t;
              return true;
            }
        }
    }



    // ABC_Var interface

    Implements_ValMethod_Var(std::string id,
                             C** objectPtr,
                             getter<C,T> getterMethod,
                             setter<C,T> setterMethod,
                             std::string className=ClassName(),
                             const std::string& tip="",
                             const std::string& whatthis=""):
      Implements_ValueId(id,className,tip,whatthis),
      objectPtr_(objectPtr),
      get_(getterMethod),
      set_(setterMethod)
    {}



    Implements_ValMethod_Var()=default;


    Implements_ValMethod_Var(const Implements_ValMethod_Var<C,T>& other)=default;


    Implements_ValMethod_Var(Implements_ValMethod_Var<C,T>&& other)=default;




    Implements_ValMethod_Var& operator=( Implements_ValMethod_Var<C,T>&& other)=default;


    Implements_ValMethod_Var& operator=(const Implements_ValMethod_Var<C,T>& other)=default;

    virtual ~Implements_ValMethod_Var(){}

    virtual Implements_Simple_Value<T>* to_PlainValue()const  override
    {
      return new Implements_Simple_Value<T>(this->id(),this->value(),this->myVar(),this->Tip(), this->WhatThis());
    }







    //    virtual bool loadFromObjectValue(const ABC_Value* var) override
    //    {
    //      if ((var!=nullptr)&&(this->id()==var->id()))
    //        {
    //          auto o=dynamic_cast<const ABC_Simple_Value<T>*>(var);
    //          if(o!=nullptr)
    //            {
    //              setValue(o->value());
    //              if (!o->Tip().empty())
    //                this->setTip(o->Tip());
    //              if (!o->WhatThis().empty())
    //                this->setWhatThis(o->WhatThis());
    //              return true;
    //            }
    //          else
    //            return false;
    //        }
    //      else
    //        return false;
    //    }
  protected:
    C** objectPtr_;
    getter<C,T> get_;
    setter<C,T> set_;
    T empty_=T();
  };



  template<class C,typename T>
  class Implements_PointerMember_Var: public ABC_Simple_Value<T>, public ABCObject<C>
  {
    // ABC_Var interface
  public:
    static std::string ClassName()
    {
      return C::ClassName()+"_method";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Value::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    virtual Implements_PointerMember_Var<C,T>* create() const override
    {
      return new Implements_PointerMember_Var<C,T>;
    }

    virtual Implements_PointerMember_Var<C,T>* clone() const override
    {
      return new Implements_PointerMember_Var<C,T>(*this);
    }

    virtual C* getObject() override
    {
      if (objectPtr_!=nullptr)
        return *objectPtr_;
      else
        return nullptr;
    }

    virtual const C* getObject()const override
    {
      if (objectPtr_!=nullptr)
        return *objectPtr_;
      else
        return nullptr;
    }
    virtual void setObject(C** obj) override
    {
      objectPtr_=obj;
    }


    virtual T& refval() override
    {
      return empty_;
    }

    virtual const T& refval() const override
    {
      return empty_;
    }

    T value()const override
    {
      if ((this->getObject()==nullptr))
        return empty_;
      if (m_!=nullptr)
        return this->getObject()->*m_;
      else
        return empty_;
    }

    void moveVal(T &val)  override
    {
      return  val;
    }


    void setValue(T val) override
    {
      if ((this->getObject()!=nullptr)&& (m_!=nullptr))
        (this->getObject()->*m_)=val;

    }



    Token_Stream toTokens() const override
    {
      auto out=Implements_ValueId::toTokens();
      out<<"="<<toToken(value())<<"\n";
      return out;
    }

    bool processTokens(Token_Stream& t) override
    {
      if (!Implements_ValueId::processTokens(t))
        return false;
      else
        {
          if (t.currToken().tok()!=Token_New::ASSIGN)
            return false;
          ++t;
          T val{};
          if (!toValue(t,val))
            return false;
          else
            {
              setValue(val);
              if (t.currToken().tok()==Token_New::EOL)
                ++t;
              return true;
            }
        }
    }



    // ABC_Var interface


    Implements_PointerMember_Var(std::string id,
                                 C** objectPtr,
                                 T C::* memberPointer,
                                 std::string className=ClassName(),
                                 const std::string& tip="",
                                 const std::string& whatthis=""):
      Implements_ValueId(id,className,tip,whatthis),
      objectPtr_(objectPtr),
      m_(memberPointer)
    {}


    Implements_PointerMember_Var()=default;


    Implements_PointerMember_Var(const Implements_PointerMember_Var<C,T>& other)=default;


    Implements_PointerMember_Var(Implements_PointerMember_Var<C,T>&& other)=default;




    Implements_PointerMember_Var& operator=( Implements_PointerMember_Var<C,T>&& other)=default;


    Implements_PointerMember_Var& operator=(const Implements_PointerMember_Var<C,T>& other)=default;

    virtual ~Implements_PointerMember_Var(){}

    virtual Implements_Simple_Value<T>* to_PlainValue()const  override
    {
      return new Implements_Simple_Value<T>(
            nullptr,this->id(),this->value(),this->myVar(),this->Tip(), this->WhatThis());
    }

    //    virtual bool loadFromObjectValue(const ABC_Value* var) override
    //    {
    //      if ((var!=nullptr)&&(this->id()==var->id()))
    //        {
    //          auto o=dynamic_cast<const ABC_Simple_Value<T>*>(var);
    //          if(o!=nullptr)
    //            {
    //              setValue(o->value());
    //              if (!o->Tip().empty())
    //                this->setTip(o->Tip());
    //              if (!o->WhatThis().empty())
    //                this->setWhatThis(o->WhatThis());
    //              return true;
    //            }
    //          else
    //            return false;
    //        }
    //      else
    //        return false;
    //    }
  protected:
    C** objectPtr_;
    T C::* m_;
    T empty_=T();

  };


  template<class C,typename T>
  class Implements_RefMethod_Var: public ABC_Simple_Value<T>, public ABCObject<C>
  {
    // ABC_Var interface
  public:
    static std::string ClassName()
    {
      return C::ClassName()+"_method";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Value::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    virtual Implements_RefMethod_Var<C,T>* create() const override
    {
      return new Implements_RefMethod_Var<C,T>;
    }

    virtual Implements_RefMethod_Var<C,T>* clone() const override
    {
      return new Implements_RefMethod_Var<C,T>(*this);
    }

    virtual C* getObject() override
    {
      if (objectPtr_!=nullptr)
        return *objectPtr_;
      else
        return nullptr;
    }

    virtual const C* getObject()const override
    {
      if (objectPtr_!=nullptr)
        return *objectPtr_;
      else
        return nullptr;
    }
    virtual void setObject(C** obj) override
    {
      objectPtr_=obj;
    }


    virtual T& refval() override
    {
      if ((this->getObject()==nullptr))
        return empty_;
      if (rget_!=nullptr)
        return (this->getObject()->*rset_)();
      else
        return empty_;
    }

    virtual const T& refval() const override
    {
      if ((this->getObject()==nullptr))
        return empty_;
      if (rget_!=nullptr)
        return (this->getObject()->*rget_)();
      else
        return empty_;
    }

    T value()const override
    {
      if ((this->getObject()==nullptr))
        return empty_;
      else if (rget_!=nullptr)
        return (this->getObject()->*rget_)();
      else
        return empty_;
    }




    void setValue(T val) override
    {
      if ((this->getObject()!=nullptr)&& (rset_!=nullptr))
        (this->getObject()->*rset_)()=val;

    }


    Token_Stream toTokens() const override
    {
      auto out=Implements_ValueId::toTokens();
      out.getToken()<<"="<<value()<<"\n";
      return out;
    }

    bool processTokens( Token_Stream& t) override
    {
      if (!Implements_ValueId::processTokens(t))
        return false;
      else
        {
          t.tokenAdvance(2);
          if (t.currToken().tok()!=Token_New::ASSIGN)
            return false;
          ++t;
          T val{};
          if (!toValue(t,val))
            return false;
          else
            {
              setValue(val);
              if (t.currToken().tok()==Token_New::EOL)
                ++t;
              return true;
            }
        }
    }



    // ABC_Var interface

    Implements_RefMethod_Var(std::string id,
                             C** object,
                             refgetter<C,T> refgetterMethod,
                             refsetter<C,T> refsetterMethod,
                             std::string className=ClassName(),
                             const std::string& tip="",
                             const std::string& whatthis=""):
      Implements_ValueId(id,className,tip,whatthis),
      objectPtr_(object),
      rget_(refgetterMethod),
      rset_(refsetterMethod){}


    Implements_RefMethod_Var()=default;


    Implements_RefMethod_Var(const Implements_RefMethod_Var<C,T>& other)=default;


    Implements_RefMethod_Var(Implements_RefMethod_Var<C,T>&& other)=default;




    Implements_RefMethod_Var& operator=( Implements_RefMethod_Var<C,T>&& other)=default;


    Implements_RefMethod_Var& operator=(const Implements_RefMethod_Var<C,T>& other)=default;

    virtual ~Implements_RefMethod_Var(){}


    virtual Implements_Simple_Value<T>* to_PlainValue()const  override
    {
      return new Implements_Simple_Value<T>(this->id(),this->value(),this->myVar(),this->Tip(), this->WhatThis());
    }

    //    virtual bool loadFromObjectValue(const ABC_Value* var) override
    //    {
    //      if ((var!=nullptr)&&(this->id()==var->id()))
    //        {
    //          auto o=dynamic_cast<const ABC_Simple_Value<T>*>(var);
    //          if(o!=nullptr)
    //            {
    //              setValue(o->value());
    //              if (!o->Tip().empty())
    //                this->setTip(o->Tip());
    //              if (!o->WhatThis().empty())
    //                this->setWhatThis(o->WhatThis());
    //              return true;
    //            }
    //          else
    //            return false;
    //        }
    //      else
    //        return false;
    //    }


  protected:
    C** objectPtr_;
    refgetter<C,T> rget_;
    refsetter<C,T> rset_;
    T empty_=T();

  };



  template<class C,typename Enum>
  class Implements_EnumMethod_Var: public ABC_Simple_Value<Enum>, public ABCObject<C>
  {
    // ABC_Var interface
  public:
    static std::string ClassName();

    static std::set<std::string> SuperClasses()
    {
      return ABC_Value::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    virtual Implements_EnumMethod_Var<C,Enum>* create() const override
    {
      return new Implements_EnumMethod_Var<C,Enum>;
    }

    virtual Implements_EnumMethod_Var<C,Enum>* clone() const override
    {
      return new Implements_EnumMethod_Var<C,Enum>(*this);
    }

    virtual C* getObject() override
    {
      if (objectPtr_!=nullptr)
        return *objectPtr_;
      else
        return nullptr;
    }

    virtual const C* getObject()const override
    {
      if (objectPtr_!=nullptr)
        return *objectPtr_;
      else
        return nullptr;
    }
    virtual void setObject(C** obj) override
    {
      objectPtr_=obj;
    }


    virtual Enum& refval() override
    {
      return empty_;
    }

    virtual const Enum& refval() const override
    {
      return empty_;
    }

    Enum value()const override
    {
      if ((this->getObject()==nullptr))
        return empty_;
      if (get_!=nullptr)
        return (this->getObject()->*get_)();
      else
        return empty_;
    }

    void setValue(Enum val) override
    {
      if ((this->getObject()!=nullptr)&& (set_!=nullptr))
        ((this->getObject()->*set_))(val);

    }

    bool setCategory(std::string cat)
    {
      auto it=strToEnum.find(cat);
      if (it!=strToEnum.end())
        {
          setValue(it->second);
          return true;
        }
      else
        return false;
    }

    std::string Category()const
    {
      Enum i=value();
      for (auto& e:strToEnum)
        {
          if (e.second==i)
            return e.first;
        }
      return {};
    }


    Token_Stream toTokens() const override
    {
      auto out=Implements_ValueId::toTokens();
      out.getToken()<<"="<<Category()<<"\n";
      return out;
    }

    bool processTokens(Token_Stream& t) override
    {
      if (!Implements_ValueId::processTokens(t))
        return false;
      else
        {
          t.tokenAdvance(2);
          if (t.currToken().tok()!=Token_New::ASSIGN)
            return false;
          ++t;
          std::string val{};
          if (!toValue(t,val))
            return false;
          else if (!setCategory(val))
            return false;
          else
            {
              if (t.currToken().tok()==Token_New::EOL)
                ++t;
              return true;
            }
        }
    }



    // ABC_Var interface

    Implements_EnumMethod_Var(std::string id,
                              C** objectPtr,
                              getter<C,Enum> getterMethod,
                              setter<C,Enum> setterMethod,
                              std::string className=ClassName(),
                              const std::string& tip="",
                              const std::string& whatthis=""):
      Implements_ValueId(id,className,tip,whatthis),
      objectPtr_(objectPtr),
      get_(getterMethod),
      set_(setterMethod)
    {}



    Implements_EnumMethod_Var()=default;


    Implements_EnumMethod_Var(const Implements_EnumMethod_Var<C,Enum>& other)=default;


    Implements_EnumMethod_Var(Implements_EnumMethod_Var<C,Enum>&& other)=default;




    Implements_EnumMethod_Var& operator=( Implements_EnumMethod_Var<C,Enum>&& other)=default;


    Implements_EnumMethod_Var& operator=(const Implements_EnumMethod_Var<C,Enum>& other)=default;

    virtual ~Implements_EnumMethod_Var(){}

    typedef Implements_EnumMethod_Var<C,Enum> CC;
    virtual void reset() override
    {
      if ((this->parentValue()!=nullptr)&&(!this->isRootedVariable()))
        {
          auto s=dynamic_cast<Implements_EnumMethod_Var<C,Enum>*>(this->parentValue()->getChild(this->id()));
          if (s!=nullptr)
            *this=*s;

        }
    }

    virtual Implements_Simple_Value<std::string>* to_PlainValue()const  override
    {
      return new Implements_Simple_Value<std::string>(this->id(),this->Category(),this->myVar(),this->Tip(), this->WhatThis());
    }

    //    virtual bool loadFromObjectValue(const ABC_Value* var) override
    //    {
    //      if ((var!=nullptr)&&(this->id()==var->id()))
    //        {
    //          auto o=dynamic_cast<const ABC_Simple_Value<std::string>*>(var);
    //          if(o!=nullptr)
    //            {

    //              setCategory(o->value());
    //              if (!o->Tip().empty())
    //                this->setTip(o->Tip());
    //              if (!o->WhatThis().empty())
    //                this->setWhatThis(o->WhatThis());
    //              return true;
    //            }
    //          else
    //            return false;
    //        }
    //      else
    //        return false;
    //    }
  protected:
    C** objectPtr_;
    getter<C,Enum> get_;
    setter<C,Enum> set_;
    Enum empty_=Enum();
    static std::map<std::string,Enum> strToEnum;
  };



  template<typename Enum>
  class Implements_Categorical: public Implements_Simple_Value<std::string>
  {
  public:
    static std::string ClassName()
    {
      return "Category";
    }

    static std::set<std::string> SuperClasses();

    virtual std::set<std::string> mySuperClasses() const override;


    // ABC_Var interface
  public:
    std::string Category()const;

    Enum Rank()const;

    void updateCat();
    void updateRank();

    void setCategory(const std::string& cat);

    void setRank(Enum i);

    Implements_Categorical( const std::string& idName,Enum i,
                            const std::string& tip="",
                            const std::string & whatthis="");
    Implements_Categorical(const std::string& idName,
                           const std::string &cat,
                           const std::string& tip="",
                           const std::string & whatthis="");



    virtual const Implements_Categorical* myVarPtr()const;
    virtual Implements_Categorical* myVarPtr();


    virtual Implements_Categorical<Enum> *to_PlainValue() const override;

    typedef Implements_Categorical<Enum> C;
    virtual void reset() override
    {
      if ((parentValue()!=nullptr)&&(!isRootedVariable()))
        {

          C* r=dynamic_cast<C*>(parentValue()->getChild(id()));
          if (r!=nullptr)
            *this=*r;

        }

    }

  private:
    static std::map<std::string,Enum> strToEnum;
    Enum rank_;
  };






  template <class C>
  class Implements_Class_Reflection: public Implements_Complex_Value, public ABCObject<C>
  {
    // ABC_Var interface
  public:
    static std::string ClassName()
    {
      return C::ClassName()+"_reflection";
    }


    virtual C* getObject() override
    {
      return object_;
    }

    virtual const C* getObject()const override
    {
      return object_;
    }
    virtual void setObject(C** obj) override
    {
      object_=*obj;
    }


    virtual Implements_Class_Reflection<C>* create() const override
    {
      return new Implements_Class_Reflection<C>();
    }

    virtual Implements_Class_Reflection<C>* clone() const override
    {
      return new Implements_Class_Reflection<C>(*this);
    }

    virtual void reset() override
    {
      if ((parentValue()!=nullptr)&&(!isRootedVariable()))
        {
          auto s=dynamic_cast<Implements_Class_Reflection<C>*>(parentValue()->getChild(id()));
          if (s!=nullptr)
            *this=*s;

        }
    }



  protected:
    template<typename T>
    void push_backVarPointer(const std::string& name,
                             T C::* value,
                             const std::string& classname="",
                             const std::string& tip="",
                             const std::string & whatthis="");

    template<typename T>
    void push_backValMethod(const std::string& name,
                            getter<C,T> getmethod,
                            setter<C,T> setmethod,
                            const std::string& classname="",
                            const std::string& tip="",
                            const std::string & whatthis="");

    template<typename Enum>
    void push_backEnumValMethod(const std::string& name,
                                getter<C,Enum> getmethod,
                                setter<C,Enum> setmethod,
                                const std::string& classname="",
                                const std::string& tip="",
                                const std::string & whatthis="");

    template<typename T>
    void push_backRefMethod(const std::string& name,
                            refgetter<C,T> rgetmethod,
                            refsetter<C,T> rsetmethod,
                            const std::string& classname="",
                            const std::string& tip="",
                            const std::string & whatthis="");

  public:

    Implements_Class_Reflection(const std::string& id,
                                const std::string& myVar,
                                C* object,
                                const std::string & tip,
                                const std::string& whatthis):
      Implements_ValueId(id,myVar,tip,whatthis),
      Implements_Complex_Value(id,myVar,tip,whatthis),
      object_(object)
    {}


    Implements_Class_Reflection()=default;

    Implements_Class_Reflection(const Implements_Class_Reflection& other)
      :  Implements_ValueId(other),
        Implements_Complex_Value(other),
        object_(other.object_)
    {
      resetChildsObject();
    }

    Implements_Class_Reflection(Implements_Class_Reflection&& other):
      Implements_ValueId(other),
      Implements_Complex_Value(std::move(other)),
      object_(std::move(other.object_))

    {
      other.object_=nullptr;
      resetChildsObject();
    }

    Implements_Class_Reflection& operator=(Implements_Class_Reflection&& other)
    {
      if (this!=&other)
        {
          Implements_Complex_Value::operator =(std::move(other));
          object_=std::move(other.object_);
          other.object_=nullptr;
          resetChildsObject();
        }
      return *this;
    }

    Implements_Class_Reflection& operator=(const Implements_Class_Reflection& other)
    {
      if (this!=&other)
        {
          operator=(Implements_Class_Reflection(other));
          resetChildsObject();
        }
      return *this;
    }

    virtual ~Implements_Class_Reflection(){}

    virtual ABC_Value* to_PlainValue()const override
    {
      auto out= new Implements_Complex_Value(id(),myVar(),Tip(),WhatThis());
      for (std::size_t i=0; i<numChilds(); ++i)
        {
          auto a=getChild(ith_ChildName(i));
          auto e=a->to_PlainValue();
          out->pushChild(e);
        }
      return out;
    }
    //    virtual bool loadFromObjectValue(const ABC_Value* source)override
    //    {
    //      if (sameFields(source))
    //        {
    //          for (std::size_t i=0; i<this->numChilds(); ++i)
    //            {
    //              auto s=source->getChild(this->ith_ChildName(i));
    //              if (s!=nullptr)
    //                {
    //                  this->getChild(ith_ChildName(i))->loadFromObjectValue(s);
    //                }
    //            }
    //          return true;
    //        }
    //      else
    //        return false;
    //    }



  protected:
    virtual void initComplexVar(){}

    virtual void resetChildsObject()
    {
      for (std::size_t i=0; i<numChilds(); i++)
        {
          ABC_Value* a=this->getChild(ith_ChildName(i));
          ABCObject<C>* c=dynamic_cast<ABCObject<C>*>(a);
          if (c!=nullptr)
            {
              c->setObject(&object_);
            }
        }
    }

    C* object_;


  };





  template<typename T>
  class Implements_Simple_Class:
      public ABC_Simple_Class<T>,
      private Implements_Class_Reflection<Implements_Simple_Class<T>>
  {
    typedef Implements_Simple_Class<T> C;
    // ABC_Var interface
  public:

    static std::string ClassName()
    {
      return Implements_Simple_Value<T>::ClassName()+"_class";
    }

    static std::set<std::string> SuperClasses()
    {
      return ABC_Value::SuperClasses()+ClassName();
    }

    virtual std::set<std::string> mySuperClasses()const override
    {
      return SuperClasses();
    }

    T defaultValue()const override
    {
      return default_;
    }
    T minValue()const override
    {
      return min_;
    }
    T maxValue()const override
    {
      return max_;
    }
    T emptyValue()const override
    {
      return T();
    }
    T unknownValue()const override
    {
      return std::numeric_limits<T>::quiet_NaN();
    }

    void setDefaultValue(T val) override
    {
      default_=val;
    }


    void setminValue(T val) override
    {
      min_=val;
    }

    void setmaxValue(T val) override
    {
      max_=val;
    }

    std::string units()const override
    {
      return units_;

    }

    void setUnits(std::string newunits) override
    {
      units_=newunits;
    }

    virtual bool complyModes(const std::string mode) const override
    {
      return mode_.find(mode)!=mode_.end();
    }

    virtual std::set<std::string> modes()const override
    {
      return mode_;
    }
    Implements_Simple_Class(std::string id,
                            std::string measureunits,
                            std::set<std::string> modes,
                            T defaultValue=T(),
                            T minValue=T(),
                            T maxValue=T(),
                            std::string className=ClassName(),
                            std::string tip="",
                            std::string whatthis=""):
      Implements_ValueId(id,className,tip,whatthis),
      Implements_Class_Reflection<C>(id,className,this,tip,whatthis),
      mode_(modes),
      units_(measureunits),
      default_{defaultValue},
      min_(minValue),
      max_(maxValue)
    {
      this->push_backValMethod("units",&C::units,&C::setUnits,"measure unit",
                               "it does not allow conversions yet");
      this->push_backValMethod("defaultValue",&C::defaultValue,&C::setDefaultValue,"default value",
                               "suggested value, used for default constructor");


      this->push_backValMethod("min",&C::minValue,&C::setminValue,"min value",
                               "mandatory min value, in I/O interaction it enforces it");

      this->push_backValMethod("max",&C::maxValue,&C::setmaxValue,"max value",
                               "mandatory max value, in I/O interaction it enforces it");

    }


    Implements_Simple_Class()=default;

    Implements_Simple_Class(const Implements_Simple_Class& other)=default;
    Implements_Simple_Class(Implements_Simple_Class&& other)=default;

    Implements_Simple_Class& operator=(const Implements_Simple_Class& other)=default;

    Implements_Simple_Class& operator=(Implements_Simple_Class&& other)=default;



    virtual ~Implements_Simple_Class(){}


    virtual bool isInDomain(const ABC_Value *value) const  override
    {
      auto p=dynamic_cast<const ABC_Simple_Value<T>* > (value);
      if (p!=nullptr)
        {
          if ((minValue()!=emptyValue())&&(p->value()<minValue()))
            return false;
          else if ((maxValue()!=emptyValue())&&(p->value()>maxValue()))
            return false;
          else return true;
        }
      else
        return false;
    }


  private:
    std::set<std::string> mode_;
    std::string units_;
    T default_;
    T min_;
    T max_;

  };





  class Implements_Refer_Var:public Implements_ValueId
  {
    // ABC_Var interface
  public:

    static std::string ClassName();

    virtual std::string refId()const override;


    void setRefId(const std::string& ref_id)
    {
      refId_=ref_id;
    }


    Implements_Refer_Var(const std::string &idName,
                         const std::string& refClass,
                         const std::string &refName,
                         const std::string& tip,
                         const std::string& whatthis);


    Implements_Refer_Var(const Implements_ValueId& id):
      Implements_ValueId(id.id(),id.myVar(),id.Tip(),id.WhatThis()),
      refId_(){

    }

    Implements_Refer_Var()=default;

  private:
    ABC_Value* refVar() ;

    const ABC_Value* refVar()const ;
    std::string refId_;
    // ABC_Var interface
  public:
    virtual Token_Stream toTokens() const override;
    virtual bool processTokens(Token_Stream& t)override;


    virtual std::string ith_ChildName(std::size_t i)const  override;

    virtual const ABC_Value* getChild(const std::string& name)const  override;
    virtual ABC_Value* getChild(const std::string &name)  override;

    virtual const ABC_Value* getChild(const std::string& name,const std::string& kind)const  override;
    virtual ABC_Value* getChild(const std::string &name, const std::string &kind)  override;


    virtual void pushChild(ABC_Value* var) override;

  };





  class Implements_Complex_Class: public Implements_Complex_Value
  {
  public:

    struct fieldDef{
      std::string superClass; std::string className; std::string tip; std::string whatthis;

    };

    Implements_Complex_Class(const std::string &id,
                             const std::string &className,
                             const std::string &tip,
                             const std::string &whatthis,
                             const std::map<std::string, fieldDef> m);



    virtual bool isInDomain(const ABC_Value *value) const  override;
    // ABC_Complex_Var interface
  public:
    virtual void push_back(const std::string& idName,
                           const std::string& superclassname,
                           const std::string& classname,
                           const std::string& tip,
                           const std::string& whatthis);


  };





  class Parameters;

  class ABC_Parameterizable: public ABC_Value

  {
  public:
    ///virtual copy constructors
    virtual ABC_Parameterizable* clone() const override=0;
    ///virtual default constructors
    virtual ABC_Parameterizable* create() const override=0;

    virtual ~ABC_Parameterizable(){}


    static std::string ClassName()
    {
      return "Parameterizable";
    }

    std::string myVar()const override;



    //virtual std::ostream& put(std::ostream&) const=0;

    /// Apply the matching parameters
    virtual int apply_parameters(const Parameters& p)=0;
    // object inspectors


    /// Returns the parameters of the object
    virtual const Parameters& get_parameters()const=0;

    /*    /// It returns a name for the object that identifies its architecture
          virtual std::string name()const=0; */



  };








  /*
  class Implements_Categorical;


  template<>
  std::string Implements_Simple_Value<std::map<std::string,int>>::ClassName();


  class Implements_Categorical_Class : public Implements_Simple_Value<std::map<std::string,int>>
  {
  public:

    static std::string ClassName();

    static std::set<std::string> SuperClasses();

    virtual std::set<std::string> mySuperClasses()override;

    virtual std::string Category(int i)const;

    virtual int Rank(const std::string name)const;

    std::string defaultCategory()const;

    // ABC_Var interface
  public:

    Implements_Categorical_Class(ABC_Var* parent,
                                 const std::string& categoryName,
                                 std::vector<std::string> categoriesList ,
                                 const std::string& defaultCategoryName);

    Implements_Categorical_Class(ABC_Var* parent,
                                 const std::string& categoryName,
                                 std::map<std::string,int> categoriesRank,
                                 const std::string& defaultCategoryName);

    Implements_Categorical_Class(ABC_Var* parent,
                                 const std::string& categoryName,
                                 std::map<int,std::string> RankCategories,
                                 const std::string& defaultCategoryName);


    virtual bool isInDomain(const ABC_Var *value) const;
    virtual  ABC_Var *varTemplate() const;
  private:
    std::string default_;
    std::map<int,std::string> revMap_;

  };

*/


  template<>
  std::string Implements_Simple_Value<std::vector<std::string>>::ClassName();

  template<>
  std::string Implements_Simple_Value<std::string>::ClassName();

  template<>
  std::string Implements_Simple_Value<Markov_LA::M_Matrix<double>>::ClassName();



  inline std::ostream& operator<<(std::ostream& os, std::vector<std::string> data )
  {
    for (const auto& s:data)
      {
        os<<s<<"\t";
      }
    return os;
  }

  template<>
  inline bool ABC_Value::getVal(const std::string &name, const ABC_Value  *& value) const
  {
    const ABC_Value* o=getChild(name);
    if (o!=nullptr)
      {
        value=o;
        return true;
      }
    else
      return false;
  }

  template<typename T>
  bool ABC_Value::getVal(const std::string &name, T &value) const
  {
    auto a=getChild(name);
    if (a==nullptr)
      return false;
    const ABC_Simple_Value<T>* o=dynamic_cast<const ABC_Simple_Value<T>*>(a);

    if (o!=nullptr)
      {
        value=o->value();
        return true;
      }
    else
      {
        auto t=a->toTokens();
        Implements_Simple_Value<T> v{};
        if (v.processTokens(t))
          {
            value=v.value();
            return true;
          }
        else
          return false;
      }
  }

  template<typename T>
  bool ABC_Value::moveVal(const std::string &name, T &value)
  {
    auto a=getChild(name);
    if (a==nullptr)
      return false;
    ABC_Simple_Value<T>* o=dynamic_cast<ABC_Simple_Value<T>*>(a);

    if (o!=nullptr)
      {
        o->moveVal(value);
        removeChild(name);
        return true;
      }
    else
      {
        auto t=a->toTokens();
        Implements_Simple_Value<T> v{};
        if (v.processTokens(t))
          {
            v.moveVal(value);
            return true;
          }
        else
          return false;
      }
  }



  template<typename T>
  T& ABC_Value::getReference(const std::string &name, T &value)
  {
    auto a=getChild(name);
    if (a==nullptr)
      return value;

    ABC_Simple_Value<T>* o=dynamic_cast< ABC_Simple_Value<T>*>(a);

    if (o!=nullptr)
      {
        return o->refval();
      }
    else
      {
        auto t=a->toTokens();
        Implements_Simple_Value<T> v{};
        std::size_t pos=0;
        if (v.processTokens(t,pos,nullptr))
          {
            return v.refval();
          }
        else
          return value;
      }
  }

  template<>
  inline ABC_Value*& ABC_Value::getReference(const std::string &name, ABC_Value  *& value)
  {
    ABC_Value* o=getChild(name);
    if (o!=nullptr)
      {
        value=o;
        return value;
      }
    else
      return value;
  }





  template<typename T>
  void ABC_Value::push_backVal(const std::string &name,
                               T value,
                               const std::string &classname,
                               const std::string& tip,
                               const std::string & whatthis)
  {
    std::string c=classname;
    if (c.empty())
      c=Implements_Simple_Value<T>::ClassName();
    Implements_Simple_Value<T>* o=new Implements_Simple_Value<T>(name,value,c,tip,whatthis);
    pushChild(o);

  }

  inline
  void ABC_Value::push_backVarRef(const std::string &name, const std::string &idRef, const std::string &classname, const std::string &tip, const std::string &whatthis)
  {
    std::string c=classname;
    if (c.empty())
      c=Implements_Refer_Var::ClassName();
    auto o=new Implements_Refer_Var(name,c,idRef,tip,whatthis);
    pushChild(o);

  }





  template<class C> template<typename T>
  void Implements_Class_Reflection<C>::push_backVarPointer(const std::string &name,
                                                           T C::* value,
                                                           const std::string &classname,
                                                           const std::string& tip,
                                                           const std::string & whatthis)
  {
    std::string c=classname;
    if (c.empty())
      c=Implements_Simple_Value<T>::ClassName();
    auto o=new Implements_PointerMember_Var<C,T>(name,&object_,value,c,tip,whatthis);
    pushChild(o);
  }


  template<class C> template<typename T>
  void Implements_Class_Reflection<C>::push_backValMethod(const std::string& name,
                                                          getter<C,T> getmethod,
                                                          setter<C,T> setmethod,
                                                          const std::string& classname,
                                                          const std::string& tip,
                                                          const std::string & whatthis)
  {
    std::string c=classname;
    if (c.empty())
      c=Implements_ValMethod_Var<C,T>::ClassName();
    Implements_ValMethod_Var<C,T>* o=new Implements_ValMethod_Var<C,T>(name,&object_,getmethod,setmethod,c,tip,whatthis);
    pushChild(o);

  }






  template<class C>  template<typename Enum>
  void Implements_Class_Reflection<C>::push_backEnumValMethod(const std::string& name,
                                                              getter<C,Enum> getmethod,
                                                              setter<C,Enum> setmethod,
                                                              const std::string& classname,
                                                              const std::string& tip,
                                                              const std::string & whatthis)
  {
    std::string c=classname;
    if (c.empty())
      c=Implements_EnumMethod_Var<C,Enum>::ClassName();
    Implements_EnumMethod_Var<C,Enum>* o=new Implements_EnumMethod_Var<C,Enum>(name,&object_,getmethod,setmethod,c,tip,whatthis);
    pushChild(o);

  }




  template<class C>template<typename T>
  void Implements_Class_Reflection<C>::push_backRefMethod(const std::string& name,
                                                          refgetter<C,T> rgetmethod,
                                                          refsetter<C,T> rsetmethod,
                                                          const std::string& classname,
                                                          const std::string& tip,
                                                          const std::string & whatthis)
  {
    std::string c=classname;
    if (c.empty())
      c=Implements_RefMethod_Var<C,T>::ClassName();
    auto o=new Implements_RefMethod_Var<C,T>(name,&object_,rgetmethod,rsetmethod,c,tip,whatthis);
    pushChild(o);

  }













  template<>
  inline  void ABC_Value::push_backVal(const std::string &name,
                                       ABC_Value* value,
                                       const std::string &classname,
                                       const std::string& tip,
                                       const std::string & whatthis)

  {
    if (value!=nullptr)
      {
        if (!name.empty())
          value->setId(name);
        if (!classname.empty())
          value->setVar(classname);
        if (!tip.empty())
          value->setTip(tip);
        if (!whatthis.empty())
          value->setWhatThis(whatthis);
        pushChild(value);

      }
  }

  template<typename T>
  bool ABC_Value::replaceValue(const std::string &name, const T &value)
  {
    ABC_Value*p=getChild(name);
    Implements_Simple_Value<T>* o=dynamic_cast<Implements_Simple_Value<T>*>(p);

    if (o!=nullptr)
      {
        o->setValue(value);
        return true;
      }
    else
      return false;
  }



  template<>
  inline  bool ABC_Value::replaceValue(const std::string &name, ABC_Value* const& value)
  {
    if ((value==nullptr)||(value->id()!=name)||(getChild(name)==nullptr))
      return false;
    pushChild(value);
    return true;
  }



  template<typename Enum>
  std::set<std::string> Implements_Categorical<Enum>::SuperClasses()
  {
    return Implements_Simple_Value<int>::SuperClasses()+ClassName();
  }

  template<typename Enum>
  std::set<std::string> Implements_Categorical<Enum>::mySuperClasses() const
  {
    return SuperClasses();
  }

  template<typename Enum>
  std::string Implements_Categorical<Enum>::Category() const
  {
    return value();
  }

  template<typename Enum>
  Enum Implements_Categorical<Enum>::Rank() const
  {
    return rank_;
  }

  template<typename Enum>
  void Implements_Categorical<Enum>::updateCat()
  {
    for (auto& p:strToEnum)
      if (p.second==rank_)
        {
          setValue(p.first);
          break;
        }
  }

  template<typename Enum>
  void Implements_Categorical<Enum>::updateRank()
  {
    rank_=strToEnum[value()];
  }

  template<typename Enum>
  void Implements_Categorical<Enum>::setCategory(const std::string &cat)
  {
    push_backVal(cat);
    updateRank();
  }

  template<typename Enum>
  void Implements_Categorical<Enum>::setRank(Enum i)
  {
    rank_=i;
    updateCat();
  }

  template<typename Enum>
  Implements_Categorical<Enum>::Implements_Categorical(const std::string &idName,
                                                       Enum i,
                                                       const std::string& tip,
                                                       const std::string & whatthis):
    Implements_Simple_Value<std::string>(idName,"",ClassName(),tip,whatthis),
    rank_{i}
  {
    updateCat();
  }


  template<typename Enum>
  Implements_Categorical<Enum>::Implements_Categorical(const std::string &idName,
                                                       const std::string & cat,
                                                       const std::string& tip,
                                                       const std::string & whatthis):
    Implements_Simple_Value<std::string>(idName,cat,ClassName(),tip,whatthis),
    rank_{}
  {
    updateRank();
  }



  template<typename Enum>
  const Implements_Categorical<Enum> *Implements_Categorical<Enum>::myVarPtr() const
  {
    return dynamic_cast<const Implements_Categorical<Enum>*>(parentValue()->getChild(myVar()));
  }


  template<typename Enum>
  Implements_Categorical<Enum> *Implements_Categorical<Enum>::myVarPtr()
  {
    return dynamic_cast< Implements_Categorical<Enum>*>(parentValue()->getChild(myVar()));
  }


  template<typename Enum>
  Implements_Categorical<Enum> *Implements_Categorical<Enum>::to_PlainValue()const
  {
    return nullptr;
  }

  template<typename Enum>
  void ABC_Value::push_back_CategoryItem(const std::string &name, Enum i,
                                         const std::string& tip,
                                         const std::string & whatthis)
  {
    pushChild(new Implements_Categorical<Enum>(name,i,tip,whatthis));

  }




  inline
  std::set<std::string> operator+(std::set<std::string>&& tok1,
                                  std::string &&s)
  {
    tok1.insert(s);
    return tok1;
  }

  inline std::set<std::string> operator+(std::set<std::string> &&ss1,
                                         std::set<std::string> &&ss2)
  {
    ss1.insert(ss2.begin(),ss2.end());
    return ss1;
  }






  template<typename T>
  std::string ABC_Simple_Class<T>::ClassName()
  {
    return Implements_Simple_Value<T>::ClassName()+"_abs_SC";
  }


}

#endif // ABC_VAR_H
