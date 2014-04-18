#ifndef SIMPLEVARIABLE_H
#define SIMPLEVARIABLE_H
#include "Macror_Var/Abstract_Named_Object.h"
#include "Macror_Var/Abstract_Variable_Object.h"

namespace Macror_Var {

  template<typename T>
  class SimpleVariable: public Abstract_Variable_Object,
      public Implement_Named_Object,
      public Implement_Refer_Environment
  {
  public:

    class Data: public Abstract_Variable_Object::Abstract_Data,
        public Implement_Refer_Environment
    {


      // Abstract_Object interface
    public:

      static std::string ClassName();

      virtual std::string myClass()const override;

      virtual std::set<std::string> mySuperClasses()const override;

      static std::set<std::string> SuperClasses();

      static T unknown();

      static bool isUnknown(const T& value);

      static T get(const std::string& singleLine,std::size_t* pos);

      static bool is(const std::string& singleLine);


      virtual bool empty() const override;
      virtual Data *create() const override;
      virtual std::string ToString() const override;
    virtual std::deque<Token> toTokens() const override;

      virtual Data *CreateObject(const std::string &text, std::size_t &cursor) const override;


      virtual std::string variableName() const override;

      // Abstract_Data interface
      virtual Data *CreateUnknown() const
      {
        return new Data(getEnvironment(),variableName(),unknown());
      }
      virtual std::string printData() const;
      virtual bool readPrintData(const std::string &printedData);


      const T& getValue()const;

      void setValue(T value);


      Data();

      Data(Environment* E, std::string varName, T value);

    protected:
      virtual Data *ToObject(const std::string &text, std::size_t &cursor);

    private:
      std::string varName_;
      T data_;

    };

    static std::string ClassName();
    virtual std::string myClass()const override;

    virtual std::set<std::string> mySuperClasses()const override;

    static std::set<std::string> SuperClasses();


    virtual bool empty()const override;



    virtual std::string myQuantity()const ;

    virtual std::string ToString()const override;


    virtual SimpleVariable<T>*
    CreateObject(const std::string& text,std::size_t& cursor) const;

    // Abstract_Variable_Object interface
    virtual Data *emptyValue() const override;

    virtual Data* defaultValue()const override;

    virtual Data* unKnownValue()const override;


    virtual std::set<std::string> referencedObjects()const;

    virtual bool isValidValue(const Abstract_Data *ob)const;

    virtual bool isCreateable()const;
    virtual SimpleVariable<T>* create()const;



    SimpleVariable();

    SimpleVariable(const SimpleVariable<T>& other):
       Implement_Named_Object(other),
       Implement_Refer_Environment(other),
      defautValue_(other.defautValue_),
      quantityId_(other.quantityId_){}






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

    virtual std::deque<Token> BodyTokens()const override;


  private:
    T defautValue_;
    std::string quantityId_;

  };



}



#endif // SIMPLEVARIABLE_H
