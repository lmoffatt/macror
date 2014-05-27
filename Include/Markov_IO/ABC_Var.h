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

#include <limits>
namespace  Markov_IO {

  class ABC_Complex_Var;

  class ABC_Environment_Var;



  class ABC_Var
  {
  public:
    static std::string alfaChars();
    static std::string alfaNumChars();

    static std::string spaceChars();

    static std::string numChars();
    static std::string numRChars();
    static bool isValidId(const std::string& idC);

    static std::string getId(const std::string& text,
                             std::size_t&  pos);

    static ABC_Var* getFromString(const std::string& text, std::size_t &pos);


    virtual std::string id()const=0;
    virtual std::string refId()const=0;

    virtual const ABC_Var* refVar()const=0;
    virtual ABC_Var* refVar()=0;

    virtual std::string myKindId()const=0;

    virtual std::string myClass()const=0;

    virtual const ABC_Var* myKind()const=0;
    virtual  ABC_Var* myKind()=0;


    virtual std::string toString()const=0;

    //virtual bool loadFromString(const std::string& text,std::size_t& pos)=0;

    virtual std::size_t numChildVars()const=0;

    // virtual ABC_Var* create()const=0;

    virtual ABC_Complex_Var* parentVar()const =0;

    virtual void setParent(ABC_Complex_Var* par)=0;

    virtual ~ABC_Var(){}

  };


  class ABC_Complex_Var:virtual public ABC_Var
  {
  public:

    std::string BeginLabel()const;
    std::string EndLabel()const;

    virtual std::string ith_Var(std::size_t i)const=0;

    virtual const ABC_Var* getVarId(const std::string& name)const=0;
    virtual ABC_Var* getVarId(const std::string &name)=0;

    virtual const ABC_Var* getVarId(const std::string& name,const std::string& kind)const=0;
    virtual ABC_Var* getVarId(const std::string &name, const std::string &kind) =0;

    virtual bool addVar(ABC_Var* var)=0;

    virtual ABC_Environment_Var* getEnvironment()const=0;

    virtual ~ABC_Complex_Var(){}
  };




  class ABC_Environment_Var:public ABC_Complex_Var
  {
  public:
    virtual std::size_t numClasses()const=0;
    virtual  std::string classId(std::size_t i)const=0;
    virtual  const ABC_Var* getClassId(std::string name)const=0;
    virtual   ABC_Var* getClassId(std::string name)=0;

    virtual  std::string varKindId(std::size_t i)const=0;
    virtual  const ABC_Var* getKind(std::string name)const=0;
    virtual   ABC_Var* getKind(std::string name)=0;

  };

  
  class Implements_VarId: virtual public ABC_Var
  { // ABC_Var interface
  public:
    virtual std::string myKindId()const override
    {
      return kind_;
    }
    virtual ABC_Var* myKind() override
    {
      return parentVar()->getEnvironment()->getKind(myKindId());
    }
    virtual const ABC_Var* myKind()const override
    {
      return parentVar()->getEnvironment()->getKind(myKindId());
    }

    virtual std::string id()const override;
    virtual std::size_t numChildVars() const override;
    virtual ABC_Complex_Var *parentVar()const override;

    virtual std::string refId()const override;

    virtual ABC_Var* refVar() override;

    virtual const ABC_Var* refVar() const override;

    Implements_VarId(ABC_Complex_Var* parent,
                     const std::string& className,
                     const std::string& name);

    Implements_VarId();


    virtual void setParent(ABC_Complex_Var *par)override;

    virtual ~Implements_VarId(){}
  protected:
    std::string kind_;
    std::string id_;
    ABC_Complex_Var* p_;
  };



  template<typename T>
  class Implements_Simple_Var:virtual public ABC_Var, public Implements_VarId
  {
    // ABC_Var interface
  public:
    static std::string ClassName();


    virtual std::string myClass()const override
    {
      return ClassName();
    }

    virtual std::string toString()  const;
    T value()const;

    void setValue(T val);
    /*
    virtual bool loadFromString(const std::string text, std::size_t &pos)
    {
      std::size_t pos0=pos;
      std::size_t pos1=text.find_first_not_of(spaceChars(),pos0);
      if (alfaChars().find(text[pos1])==alfaChars().npos)
        {
          std::string error="invalid starting char for identifier: "+text[pos];
          throw std::logic_error(error);
        }
      pos=text.find_first_not_of(alfaNumChars());

      std::string idN=text.substr(pos0,pos-pos0);

      //if it has already an identifier, check it!
      if (!id().empty())
        {
          if (id()!=idN)
            {
              pos=pos0;
              return false;
            }
        }
      pos=text.find_first_not_of(spaceChars(),pos);
      if (text[pos]!='=')
        return false;
      pos++;
      pos=text.find_first_not_of(spaceChars(),pos);
      pos1=pos;
      pos=text.find_first_not_of(numRChars(),pos);
      std::string num=text.substr(pos1,pos-pos1);
      double d;
      try
      {
        d=std::stod(num);
      }
      catch (std::invalid_argument)
      {
        pos=pos0;
        return false;
      }
      // if we got here, we have id and value rights
      id_=idN;
      value_=d;
      return true;
    }

   */

    //  virtual ABC_Var *create() const;

    Implements_Simple_Var(ABC_Complex_Var* parent,
                          std::string id,
                          T val,
                          std::string kindName=ClassName());


    Implements_Simple_Var();

    virtual ~Implements_Simple_Var(){}

  private:
    T value_;

  };





  class Implements_Refer_Var:public Implements_VarId
  {
    // ABC_Var interface
  public:
    std::string RefLabel()const;

    virtual std::string toString() const;

    virtual std::string refId()const;
    virtual ABC_Var* refVar();

    virtual const ABC_Var* refVar()const ;


    Implements_Refer_Var(ABC_Complex_Var* parent,
                         std::string idName,
                         std::string refKind,
                         std::string refName);
  private:
    std::string refId_;
  };


  class Implements_Complex_Var:public ABC_Complex_Var, public Implements_VarId
  {

    // ABC_Var interface
  public:
    virtual std::string toString() const;

    /*
    virtual bool loadFromString(const std::string text, std::size_t& pos)

    {
      std::size_t pos0=pos;
      std::string idN=getId(text,pos);

      //if it has already an identifier, check it!
      if (!id().empty())
        {
          if (id()!=idN)
            {
              pos=pos0;
              return false;
            }
        }
      pos=text.find_first_not_of(spaceChars(),pos);

      // check the colon
      if ((text.size()<=pos )|| (text[pos]!=':'))
        return false;
      pos++;

      // check the class begin

     std::string beginN=getId(text,pos);
     std::string classN=getId(text,pos);








      pos=text.find_first_not_of(spaceChars(),pos);
      pos1=pos;
      pos=text.find_first_not_of(numRChars(),pos);
      std::string num=text.substr(pos1,pos-pos1);
      double d;
      try
      {
        d=std::stod(num);
      }
      catch (std::invalid_argument)
      {
        pos=pos0;
        return false;
      }
      // if we got here, we have id and value rights
      id_=idN;
      real_=d;
      return true;
    }
*/

    virtual std::size_t numChildVars() const;

    // ABC_Complex_Var interface
  public:

    virtual std::string ith_Var(std::size_t i) const
    {
      return ids_[i];
    }



    virtual const ABC_Var* getVarId(const std::string& name)const override
    {
      auto it=vars_.find(name);
      if (it!=vars_.end())
        return it->second;
      else
        return nullptr;
    }

    virtual  ABC_Var* getVarId(const std::string& name)override
    {
      auto it=vars_.find(name);
      if (it!=vars_.end())
        return it->second;
      else
        return nullptr;
    }

    virtual const ABC_Var* getVarId(const std::string& name,
                                    const std::string &myKind)const override
    {
      const ABC_Var* out=getVarId(name);
      if ((out!=nullptr)&&(out->myKindId()==myKind))
        return out;
      else      return nullptr;
    }
    virtual ABC_Var* getVarId(const std::string& name, const std::string &myKind) override
    {
       ABC_Var* out=getVarId(name);
      if ((out!=nullptr)&&(out->myKindId()==myKind))
        return out;
      else      return nullptr;
    }


    virtual bool addVar(ABC_Var *var);

    virtual ABC_Environment_Var* getEnvironment()const;

    Implements_Complex_Var(ABC_Complex_Var* parent,
                           const std::string& kindId,
                           const std::string& id,
                           const std::vector<ABC_Var*>& childs);

    Implements_Complex_Var(){}

    virtual ~Implements_Complex_Var();


  private:
    std::vector<std::string> ids_;
    std::map<std::string,ABC_Var*> vars_;

  };

  class Categorical_Options: public Implements_Simple_Var<std::vector<std::string> >
  {
    // ABC_Var interface
  public:
    static std::string ClassName()
    {
      return "Categorical_Options";
    }

    virtual std::string toString()  const;

    Categorical_Options(ABC_Complex_Var* parent,
                        std::string id,
                        const std::vector<std::string>& options):
      Implements_Simple_Var<std::vector<std::string> >(parent,id,options,ClassName())
    {}

    Categorical_Options()=default;

    virtual ~Categorical_Options(){}


  };



  class Categorical_Data: public Implements_Simple_Var<std::string>
  {
    // ABC_Var interface
  public:
    static std::string ClassName()
    {
      return "Categorical_Data";
    }


    Categorical_Data(ABC_Complex_Var* parent,
                     std::string categoricalClass,
                     std::string id):
      Implements_Simple_Var<std::string>(parent,id,id,categoricalClass){}

    Categorical_Data();

    virtual ~Categorical_Data(){}


  };



  inline std::ostream& operator<<(std::ostream& os, std::vector<std::string> data )
  {
    for (std::string s:data)
      {
        os<<s<<"\t";
      }
    return os;
  }





}

#endif // ABC_VAR_H
