#ifndef SIMPLEVARIABLE_H
#define SIMPLEVARIABLE_H
#include "Markov_Object/Abstract_Named_Object.h"
#include "Markov_Object/Abstract_Variable_Object.h"
#include "Markov_Object/SimpleVariableValue.h"

namespace Markov_Object {

  template<typename T>
  class SimpleVariable: public Abstract_Variable_Object
  {
  public:

    static std::string ClassName();
    virtual std::string myClass()const override;

    virtual std::set<std::string> mySuperClasses()const override;

    static std::set<std::string> SuperClasses();


    virtual bool empty()const override
     {
       return Abstract_Variable_Object::empty()&&
           unitId_.empty()&&
           defautValue_==T();

     }




    virtual std::string myUnit()const ;

    virtual std::string ToString()const override;
    virtual SimpleVariable<T>*
    CreateObject(const std::string& text,std::size_t& cursor) const override
    {
      auto tmp=create();
      auto out=tmp->ToObject(text,cursor);
      if (out==nullptr)
        delete tmp;
      return out;
    }


    virtual SimpleVariableValue<T>* defaultValue()const override;

    virtual SimpleVariableValue<T>* unKnownValue()const override;


    virtual std::set<std::string> referencedObjects()const;

      virtual bool isValidValue(const Abstract_Value_Object* ob)const;

    virtual bool isCreateable()const;
    virtual SimpleVariable<T>* create()const;

    SimpleVariable( Environment*  e);


    SimpleVariable();

    SimpleVariable(const SimpleVariable<T>& other):
      Abstract_Object(),
      Abstract_Variable_Object(other),
      defautValue_(other.defautValue_),
      unitId_(other.unitId_){}






    SimpleVariable(std::string name,
                   T defaultValue,
                   std::string unit,
                   Environment* E,
                   std::string tip,
                   std::string whatthis);
    ~SimpleVariable();
  protected:
    virtual SimpleVariable<T>*
    ToObject(const std::string& multipleLines,std::size_t& pos) override;


  private:
    T defautValue_;
    std::string unitId_;

    // Abstract_Object interface
  public:
    virtual std::size_t numFields() const
    {
      return 0;
    }

  };



}



#endif // SIMPLEVARIABLE_H
