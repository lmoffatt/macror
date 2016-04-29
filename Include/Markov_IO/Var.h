#ifndef VAR_H
#define VAR_H

#include "Markov_LA/Matrix.h"


#include <string>
#include <map>
#include <set>
#include <vector>

#include "Markov_IO/Token_New.h"
#include "Markov_IO/Cls.h"
//#include "Markov_IO/buildByToken.h"

#include "type_traits"
namespace Markov_Mol_New
{
  class ABC_Markov_Model;
  class Q_Markov_Model;
}

namespace Markov_IO_New {

  namespace alternatives
  {
    inline
    std::string endOfLine() {return "<Return>";}

    inline
    std::string newIdentifier() {return "<Unoccupied Identifier>";}

    inline std::string tip(){return "#<Tip text>";}
    inline std::string whatthis(){return "##<WhatThis text>";}




  };
  class ABC_Var_New;

  inline
  std::string removeHint(const std::string& alter)
  {
    auto out=alter.substr(0,alter.find('<'));
    if (std::isalpha(out.back()))
      out.push_back(' ');
    return out;
  }



  namespace _private
  {

    class Implements_Data_Type_New_string;
    class Implements_Data_Type_New_ABC_Var_New;
    class Implements_Data_Type_New_map_string_ABC_Var_New;

    namespace _model {
      class Implements_Data_Type_class_ABC_Markov_Model;
      class Implements_Data_Type_class_Q_Markov_Model;
    }


    template<typename T> class Implements_Data_Type_New_vector;
    template<typename T> class Implements_Data_Type_New_set;
    template<typename T> class Implements_Data_Type_New_M_Matrix;
    template<typename K,typename T> class Implements_Data_Type_New_pair;
    template<typename K,typename T> class Implements_Data_Type_New_map;


    template<typename T> class Implements_Data_Type_New_regular;
    template<class C> class Implements_Data_Type_class;

    template<typename T>
    struct Helper_Type
    {
      using t=typename    std::conditional<std::is_arithmetic<T>::value,
      Implements_Data_Type_New_regular<T>,
      Implements_Data_Type_class<T>>::type;
    };

    template<typename T>
    struct Helper_Type<std::vector<T>>
    {
      using t=Implements_Data_Type_New_vector<T>;
    };

    template<typename T>
    struct Helper_Type<std::set<T>>
    {
      using t=Implements_Data_Type_New_set<T>;
    };

    template<typename T>
    struct Helper_Type<Markov_LA::M_Matrix<T>>
    {
      using t=Implements_Data_Type_New_M_Matrix<T>;
    };

    template<typename K,typename T>
    struct Helper_Type<std::map<K,T>>
    {
      using t=Implements_Data_Type_New_map<K,T>;
    };

    template<typename K,typename T>
    struct Helper_Type<std::pair<K,T>>
    {
      using t=Implements_Data_Type_New_pair<K,T>;
    };



    template<>
    struct Helper_Type<std::string>
    {
      using t=Implements_Data_Type_New_string;
    };
    template<>
    struct Helper_Type<ABC_Var_New*>{
      using t=Implements_Data_Type_New_ABC_Var_New;
    };
    template<>
    struct Helper_Type<std::map<std::string,ABC_Var_New*>>{
      using t=Implements_Data_Type_New_map_string_ABC_Var_New;
    };

    template<>
    struct Helper_Type<Markov_Mol_New::ABC_Markov_Model*>
    {
      using t=_model::Implements_Data_Type_class_ABC_Markov_Model;
    };

    template<>
    struct Helper_Type<Markov_Mol_New::Q_Markov_Model*>
    {
      using t=_model::Implements_Data_Type_class_Q_Markov_Model;
    };

  };
  template <class T>
  using Implements_Data_Type_New=typename _private::Helper_Type<T>::t;




  class ABC_Var_New;
  class ABC_Value_New;


  template<class T>
  T dynamicCast(ABC_Var_New* v, std::string* whyNot,const std::string& masterObjective);

  template<class T>
  const T dynamicCast(const ABC_Var_New* v, std::string* whyNot,const std::string& masterObjective);


  template<class T>
  T dynamicCast(ABC_Value_New* v, std::string* whyNot,const std::string& masterObjective);

  template<class T>
  const T dynamicCast(const ABC_Value_New* v, std::string* whyNot,const std::string& masterObjective);


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


  class ABC_Value_New
  {
  public:
    static std::string ClassName()
    {
      return "ABC_Value_New";
    }

    virtual std::string myClass()const
    {
      return ClassName();
    }

    virtual std::string storedClass() const=0;

    virtual bool empty()const =0;

    virtual void reset()=0;

    virtual ABC_Value_New* clone()const=0;
    virtual ABC_Value_New* create()const=0;



    virtual ~ABC_Value_New(){}



    /// template methods
    ///

    //TODO: ver cual es la forma mas conveniente de manejar la propiedad de T, especialmente si esgrand

    template<typename T>
    const T getValue()const;

    template<typename T>
    T getValue();

    template<typename T>
    bool setValue(const T& val);


  };

  template <typename T>
  void reset(T& x)
  {
    x=T{};
  }




  template <typename T>
  class ABC_Typed_Value;




  template<typename T>
  class Implements_Value_New: public ABC_Value_New
  {
  public:
    static std::string ClassName()
    {
      return "Implements_Value_Typed"+Cls<T>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    virtual std::string storedClass() const override
    {
      return Cls<T>::name();

    }

    // ABC_Value_New interface
  public:
    virtual bool empty() const override
    {
      return empty_;
    }

    virtual void reset() override
    {
      data_=T{};
      empty_=true;
    }



    // Implements_Value_New interface
  public:
    virtual Implements_Value_New<T>* clone() const override
    {
      return new Implements_Value_New(data_);

    }

    virtual Implements_Value_New<T>* create() const override
    {
      return new Implements_Value_New();

    }


    virtual const T& getValued() const
    {
      return data_;
    }
    virtual T& getValued()
    {
      return data_;
    }
    virtual bool setValue(T val,std::string *whyNot, const std::string& masterObjective)
    {
      data_=std::move(val);
      empty_=false;
      return true;
    }



    Implements_Value_New():
      data_{}, empty_(true){}
    Implements_Value_New(T datum):
      data_(std::move(datum)), empty_(false){}

    ~Implements_Value_New(){}

  protected:

    T data_;
    bool empty_;
  };



  class Implements_ComplexVar_New;


  struct type_tip_Whatthis
  {
    std::string varType;
    std::string tip;
    std::string whatthis;
  };






  class ABC_Type_of_Value;
  template <typename T>
  class ABC_Typed_Value;

  class ABC_Var_New//: public ABC_Value_New
  {

    // ABC_Value_New interface
  public:

    static std::string ClassName()
    {
      return "ABC_Value_New";
    }

    virtual std::string myClass()const
    {
      return ClassName();
    }

    virtual ABC_Var_New* create(const Implements_ComplexVar_New* cm)const=0;

    virtual ABC_Value_New* value()=0;

    virtual const ABC_Value_New* value()const=0;

    virtual const Implements_ComplexVar_New* parent()const =0;
    virtual void setParentValue(const Implements_ComplexVar_New* par)=0;

    virtual std::string id()const=0;


    virtual std::string Tip()const=0;
    virtual std::string WhatThis()const=0;

    virtual void setId(const std::string& idName)=0;


    virtual std::string refId()const=0;

    virtual std::string myType()const=0;

    bool isOfThisType(const Implements_ComplexVar_New* cm,
                      const std::string& generalType,
                      std::string* whyNot
                      ,const std::string &masterObjective)const;


    virtual ~ABC_Var_New(){}

  };

  template<typename T>
  class Implements_Var_New: public ABC_Var_New
  {
    // ABC_Value_New interface
  public:
    static std::string ClassName()
    {
      return "Implements_Var_New_of"+Cls<T>::name();
    }

    virtual std::string myClass()const override
    {
      return ClassName();
    }

    virtual Implements_Var_New<T>* create(const Implements_ComplexVar_New* cm)const override
    {
      return new Implements_Var_New(cm,id(),myType(),Tip(),WhatThis(),x_->create());
    }

    virtual const Implements_ComplexVar_New* parent()const override
    {
      return p_;
    }
    virtual void setParentValue(const Implements_ComplexVar_New* par) override
    {
      p_=par;
    }

    virtual std::string id()const override
    {
      return id_;
    }


    virtual std::string Tip()const override
    {
      return tip_;
    }
    virtual std::string WhatThis()const override
    {
      return whatthis_;
    }

    virtual void setId(const std::string& idName) override
    {
      id_=idName;
    }


    virtual std::string refId()const override
    {
      return id();
    }

    virtual std::string myType()const override
    {
      return var_;
    }

    virtual Implements_Value_New<T>* value()
    {
      return x_;
    }

    virtual const Implements_Value_New<T>* value()const
    {
      return x_;
    }


    virtual Implements_Value_New<T>* clone()const
    {
      return x_->clone();
    }




    virtual ~Implements_Var_New()
    {
      delete x_;
    }





    // Implements_Value_New interface
  public:

    Implements_Var_New(const Implements_ComplexVar_New* parent,
                       const std::string& id,
                       const std::string& var,
                       const std::string& tip,
                       const std::string& whatthis
                       ,Implements_Value_New<T>* data=new Implements_Value_New<T>):
      p_(parent),
      id_(id),var_(var),tip_(tip),whatthis_(whatthis),
      x_(data)
    {}
    Implements_Var_New(const Implements_ComplexVar_New* parent,
                       const std::string& id,
                       const std::string& var,
                       T x,
                       const std::string& tip,
                       const std::string& whatthis):
      p_(parent),
      id_(id),var_(var),tip_(tip),whatthis_(whatthis),
      x_(new Implements_Value_New<T>(std::move(x)))
    {}

    Implements_Var_New(const Implements_ComplexVar_New* parent,
                       const std::string& id,
                       const type_tip_Whatthis& ttw,
                       T x):
      Implements_Var_New(parent,id,ttw.varType,x,ttw.tip,ttw.whatthis){}


  protected:
    const Implements_ComplexVar_New* p_;
    std::string id_;
    std::string var_;
    std::string tip_;
    std::string whatthis_;
    Implements_Value_New<T>* x_;
  };



  template<class C>
  void push_var(std::map<std::string,ABC_Var_New*>& m
                ,typename C::myC val={}
      , const std::string myId=C::myId()
      , const std::string& myTip=C::myTip()
      , const std::string& myWhatThis=C::myWhatThis()  )
  {
    m[myId]=new Implements_Var_New<typename C::myC>
        (nullptr,myId,C::myIdType(),val,myTip,myWhatThis);
  }


  template <class Field>
  bool get_var(const std::map<std::string,ABC_Var_New*>& m
               ,typename Field::myC& val
               ,std::string* whyNot
               ,const std::string& masterObjective )
  {
    auto it=m.find(Field::myId());
    if (it==m.end())
      {
        *whyNot=masterObjective+": field "+Field::myId()+" not found";
        return false;
      }
    else
      {
        ABC_Var_New* o=it->second;
        if (o==nullptr)
          {
            *whyNot=masterObjective+": field "+Field::myId()+" is null";
            return false;
          }
        else
          {
            auto v=dynamic_cast<Implements_Var_New<typename Field::myC>*>(o);
            if (v==nullptr)
              {
                *whyNot=masterObjective+": field "+Field::myId()+" is of wrong type: "
                    +o->myType()+" instead of "+ Field::myIdType();
                return false;
              }
            else
              {
                val=v->value()->getValued();
                return true;
              }

          }
      }
  }




}





#endif // VAR_H
