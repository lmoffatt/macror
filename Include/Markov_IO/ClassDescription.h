#ifndef CLASSDESCRIPTION_H
#define CLASSDESCRIPTION_H
#include <map>
#include <string>
#include <vector>

#include "Markov_IO/ABC_Object.h"
#include "Markov_LA/Matrix.h"
#include "Markov_IO/ABC_Environment.h"
//#include "Markov_IO/ABC_Saveable.h"

namespace Markov_IO
{

class ABC_Saveable;
/**
  A human readable description of the contents of a given class.
  It provides the name of the class, and human readable values for each one of
  the elements necessary to build up the class and enough to determine it
  uniquely.
  It should be possible to build a class only from the ClassDescription.
  Here is some fake code showing the rationale of ClassDescrition
  @verbatim
       // MyClass should have a method that builds the classDescrition instance
       // of  ClassDescription
       ClassDescription classDescription=myClass.getDescription();


       // Now it should be possible to build a new object just from its
      // classDescription
       MyClass other=build(classDescription);

       // Both classes should be equal
       assert(other==myClass);

   @endverbatim

   Descriptible classes are classes that

  */

//TODO: replace ClassDescription with a ABC_var derived class.
class ClassDescription: public ABC_Put
{
public:
    virtual ClassDescription* create()const;
    virtual ClassDescription* clone() const;

    virtual ~ClassDescription();
    /// virtual formated output
    virtual std::ostream& put(std::ostream& s) const;

    virtual bool operator==(const ClassDescription& other)const;


    ClassDescription(const ClassDescription& other);
    ClassDescription();

    ClassDescription& operator=(const ClassDescription& other);

    ClassDescription(const std::string& className,
                     const std::string& superClass);

    std::string  ClassName()const;
    std::string SuperClass()const;


    template<typename T>
    void push_back(const std::string& elementName,const T& value);

    template<typename T>
    void push_back(const std::string& elementName,
                   const T& value,
                   const std::string& elementTip,
                   const std::string& elemetWhatThis
                   );
    void push_back(const std::string& elementName,
                   double value,
                   const std::string elemetUnit,
                   const std::string& elementTip,
                   const std::string& elementWhatThis
                   );

    void push_back(const std::string& elementName,
                   const Markov_LA::M_Matrix<double>& value,
                   const std::string elemetUnit,
                   const std::string& elementTip,
                   const std::string& elementWhatThis
                   );

    void push_back(const std::string& elementName,
                   std::size_t value,
                   const std::string elemetUnit,
                   const std::string& elementTip,
                   const std::string& elementWhatThis
                   );

    void push_back(const std::string& elementName,
                   const Markov_LA::M_Matrix<std::size_t>& value,
                   const std::string elemetUnit,
                   const std::string& elementTip,
                   const std::string& elementWhatThis
                   );

    std::string ElementName(std::size_t i)const;

    std::string ElementValue(std::size_t i)const;

    std::string Tip(std::size_t i)const;

    std::string WhatThis(std::size_t i)const;

    std::string Unit(std::size_t i)const;


    std::size_t NameIndex(const std::string& elementName)const;


    bool ReplaceElement(const std::string& elementName, const ABC_Object& newValue);
    bool ReplaceElement(const std::string& elementName, const std::string& newValue);


    std::size_t size()const;

    bool HasElementName(const std::string& elementName)const;

    bool IsComplexObject(std::size_t i)const;


    const ABC_Object*  operator[](const std::string& elementName)const;

    const ABC_Saveable* ElementClass(const std::string& elementName)const;



    enum OutputFormatType{ FORMAT_BEGIN
                         };


    ClassDescription& setOutputFormat(OutputFormatType);
    OutputFormatType getOutputFormat() const;

    friend void swap(ClassDescription& one, ClassDescription& other);


    void setEnvironment(ABC_Environment *e);
    ABC_Environment *getEnvironment() const;
private:
    ABC_Environment* E_;
    std::string className_;
    std::string superClass_;
    std::vector<ABC_Object*> values_; //owned
    std::vector<std::string> names_;
    std::map<std::string,std::string> tips_;
    std::map<std::string,std::string> whatThis_;
    std::map<std::string,std::string> units_;


    std::map<std::string, ABC_Object*> map_;
    mutable OutputFormatType outputFormat_;
    const ABC_Object* const  null_;
    const ABC_Saveable* const nullSaveable_;

    template<typename T>
    void push_back_regular(const std::string& elementName,const T& value);
    template<typename T>
    void push_back_object(const std::string& elementName,const T& value);

    template<typename T>
    void push_back_regular(const std::string& elementName,
                           const T& value,
                           const std::string& elementTip,
                           const std::string& elemetWhatThis
                           );
    template<typename T>
    void push_back_object(const std::string& elementName,
                          const T& value,
                          const std::string& elementTip,
                          const std::string& elemetWhatThis
                          );
};


std::istream& operator>>(std::istream& s,ClassDescription& classDes);

std::ostream& operator<<(std::ostream& s,const ClassDescription& classDes);

void RemoveComments(std::string& str);







}

#endif // CLASSDESCRIPTION_H
