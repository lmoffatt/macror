#include <cassert>
#include <sstream>

#include "Markov_IO/ClassDescription.h"
#include "Markov_IO/auxiliarIO.h"
#include "Markov_LA/Matrix.h"
#include "Markov_LA/auxiliarMath.h"
#include "Markov_IO/ABC_Experiment.h"
#include "Markov_Mol/ABC_MarkovModel.h"
#include "Markov_Mol/ABC_Noise.h"
#include "Markov_Mol/PatchModel.h"
#include "Markov_Mol/PatchModelNormalDistribution.h"

#include "Markov_Bay/ABC_Result.h"

#include "Markov_Bay/LikelihoodEvaluation.h"
#include "Markov_Bay/SingleOptimizationResult.h"
#include "Markov_Bay/OptimizationResult.h"



#include "Markov_IO/PulsesTrace.h"
#include "Markov_IO/PulsesProgram.h"
#include "Markov_IO/Trace.h"
#include "Tests/AssertPlain.h"
#include "Markov_IO/Object.h"



namespace Markov_IO
{

  namespace {

    std::istream& extractClassName(std::string &line,
                                   std::istream &stream,
                                   std::string &className
                                   );

    std::istream& extractElementName(std::string &line,
                                     std::istream &stream,
                                     std::string &name);

    std::istream& extractElementValue(std::string &line,
                                      std::istream &stream,
                                      std::string &value);

    bool isClassEnd(std::string& line,
                    std::istream& stream,
                    const std::string& className);

    std::string beginLabel();

    std::string endLabel();

    ABC_Saveable* getDescriptible(const std::string & classname);


    bool toElementNameZero(std::string& elementName);


  }



  ClassDescription* ClassDescription::create()const
  {
    return new ClassDescription();
  }

  ClassDescription* ClassDescription::clone() const{
    return new ClassDescription(*this);
  }


  ///  formated output
  std::ostream& ClassDescription::put(std::ostream& stream) const{
    switch (getOutputFormat())
      {
      case ClassDescription::FORMAT_BEGIN:
        {
          if (ClassName().empty()) return stream;

          stream<<ClassName()<<" "<<beginLabel()<<"\n";

          for (std::size_t i=0;i<size();++i)
            {
              stream<<ElementName(i)<<"\n";
              stream<<ElementValue(i)<<"\n";
            }
          stream<<ClassName()<<" "<<endLabel()<<"\n";

        }
      }
    return stream;

  }





  /// Copy Constructor
  ClassDescription::ClassDescription(const ClassDescription& other):
    E_(other.E_),
    className_(other.className_),
    superClass_(other.superClass_),
    values_(other.values_),
    names_(other.names_),
    tips_(other.tips_),
    whatThis_(other.whatThis_),
    units_(other.units_),
    map_(other.map_),
    outputFormat_(FORMAT_BEGIN),
    null_(0),
    nullSaveable_(0)
  {
  }

  /// Default Constructor
  ClassDescription::ClassDescription():
    E_(nullptr),
    className_(),
    superClass_(),
    values_(),
    names_(),
    map_(),
    outputFormat_(FORMAT_BEGIN),
    null_(0),
    nullSaveable_(0)
  {}

  /// Destructor
  ClassDescription::~ClassDescription()
  {
  }


  void swap(ClassDescription& one, ClassDescription& other)
  {
    std::swap(one.E_,other.E_);
    std::swap(one.className_,other.className_);
    std::swap(one.superClass_,other.superClass_);
    std::swap(one.map_,other.map_);
    std::swap(one.names_, other.names_);
    std::swap(one.values_,other.values_);
    std::swap(one.tips_,other.tips_);
    std::swap(one.whatThis_,other.whatThis_);
    std::swap(one.units_,other.units_);
    std::swap(one.outputFormat_,other.outputFormat_);
  }



  /// Assigment operator
  ClassDescription& ClassDescription::operator=(const ClassDescription& other)
  {
    if (this != &other)
      {
        ClassDescription tmp(other);
        swap(*this, tmp);
      }
    return *this;
  }

  /**
Initial Constructor. It is the only way to set a new name of the class.
@param className
@post no other information besides the class name
*/
  ClassDescription::ClassDescription(const std::string& className,
                                     const std::string& superClass):
    E_(nullptr),
    className_(className),
    superClass_(superClass),
    values_(),
    names_(),
    tips_(),
    whatThis_(),
    units_(),
    map_(),
    outputFormat_(FORMAT_BEGIN),
    null_(0),
    nullSaveable_(0)
  {}

  bool ClassDescription::operator ==(const ClassDescription& other)const
  {
    if (ClassName()!=other.ClassName())
      return false;
    if (size()!=other.size())
      return false;
    for (std::size_t i=0; i<size(); ++i)
      {
        if (!other.HasElementName(ElementName(i)))
          return false;
        if (!((*other[ElementName(i)])==(*(*this)[ElementName(i)])))
          return false;
      }
    return true;
  }






  /**
Name of the described class
@returns a copy of the name of the described class
@warning It should be exactly the name
*/
  std::string ClassDescription::ClassName()const
  {
    return className_;
  }

  ABC_Environment* ClassDescription::getEnvironment()const
  {
    return E_;
  }

void ClassDescription::setEnvironment(ABC_Environment* e)
  {
    E_=e;
  }


  std::string ClassDescription::SuperClass()const
  {
    return superClass_;
  }



  /**
Adds a new element to the Class Description.
@param elementName The name of the element of the described class.
@param value Value of the element. It is formatted by the function
@post assert that the elementName is really new.
@post the pair elementName value is added to the description
@post The order of addition is remembered by the indexed access
*/
  template<typename T>
  void ClassDescription::push_back_regular(const std::string& elementName,
                                           const T& value)
  {
    std::map<std::string, ABC_Object*>::const_iterator it;
    it=map_.find(elementName);
    assert(it==map_.end());
    names_.push_back(elementName);
    ABC_Object* object=new Object<T>(value);
    values_.push_back(object);
    map_[elementName]=object;
  }

  template<typename T>
  void ClassDescription::push_back_object(const std::string& elementName,
                                          const T& value)
  {
    std::map<std::string, ABC_Object*>::const_iterator it;
    it=map_.find(elementName);
    assert(it==map_.end());
    names_.push_back(elementName);
    ABC_Object* object;
    if (&value!=0)
      {
        if ((value.myClass()!=value.mySuperClass()))
          {
            object=value.clone();
          }
        else
          {
            object=0;
          }
      }
    else
      object=0;

    values_.push_back(object);
    map_[elementName]=object;
  }


  template<typename T>
  void ClassDescription::push_back_regular(const std::string& elementName,
                                           const T& value,
                                           const std::string& elementTip,
                                           const std::string& elementWhatThis
                                           ){
    std::map<std::string, ABC_Object*>::const_iterator it;
    it=map_.find(elementName);
    assert(it==map_.end());
    names_.push_back(elementName);
    ABC_Object* object=new Object<T>(value);
    values_.push_back(object);
    map_[elementName]=object;
    tips_[elementName]=elementTip;
    whatThis_[elementName]=elementWhatThis;
  }

  template<typename T>
  void ClassDescription::push_back_object(const std::string& elementName,
                                          const T& value,
                                          const std::string& elementTip,
                                          const std::string& elementWhatThis
                                          ){
    std::map<std::string, ABC_Object*>::const_iterator it;
    it=map_.find(elementName);
    assert(it==map_.end());
    names_.push_back(elementName);
    ABC_Object* object;
    if (&value!=0)
      {
        if ((value.myClass()!=value.mySuperClass()))
          {
            object=value.clone();
          }
        else
          {
            object=0;
          }
      }
    else
      object=0;

    values_.push_back(object);
    map_[elementName]=object;
    tips_[elementName]=elementTip;
    whatThis_[elementName]=elementWhatThis;
  }



  void ClassDescription::push_back(const std::string& elementName,
                                   double value,
                                   const std::string elemetUnit,
                                   const std::string& elementTip,
                                   const std::string& elementWhatThis
                                   ){
    std::map<std::string, ABC_Object*>::const_iterator it;
    it=map_.find(elementName);
    assert(it==map_.end());
    names_.push_back(elementName);
    ABC_Object* object=new Object<double>(value);
    values_.push_back(object);
    map_[elementName]=object;
    units_[elementName]=elemetUnit;
    tips_[elementName]=elementTip;
    whatThis_[elementName]=elementWhatThis;
  }


  void ClassDescription::push_back(const std::string& elementName,
                                   std::size_t value,
                                   const std::string elemetUnit,
                                   const std::string& elementTip,
                                   const std::string& elementWhatThis
                                   ){
    std::map<std::string, ABC_Object*>::const_iterator it;
    it=map_.find(elementName);
    assert(it==map_.end());
    names_.push_back(elementName);
    ABC_Object* object=new Object<std::size_t>(value);
    values_.push_back(object);
    map_[elementName]=object;
    units_[elementName]=elemetUnit;
    tips_[elementName]=elementTip;
    whatThis_[elementName]=elementWhatThis;
  }


  void ClassDescription::push_back(const std::string& elementName,
                                   const Markov_LA::M_Matrix<double>& value,
                                   const std::string elemetUnit,
                                   const std::string& elementTip,
                                   const std::string& elementWhatThis
                                   ){
    std::map<std::string, ABC_Object*>::const_iterator it;
    it=map_.find(elementName);
    assert(it==map_.end());
    names_.push_back(elementName);
    ABC_Object* object=new Object<Markov_LA::M_Matrix<double> >(value);
    values_.push_back(object);
    map_[elementName]=object;
    units_[elementName]=elemetUnit;
    tips_[elementName]=elementTip;
    whatThis_[elementName]=elementWhatThis;
  }



  void ClassDescription::push_back(const std::string& elementName,
                                   const Markov_LA::M_Matrix<std::size_t>& value,
                                   const std::string elemetUnit,
                                   const std::string& elementTip,
                                   const std::string& elementWhatThis
                                   ){
    std::map<std::string, ABC_Object*>::const_iterator it;
    it=map_.find(elementName);
    assert(it==map_.end());
    names_.push_back(elementName);
    ABC_Object* object=new Object<Markov_LA::M_Matrix<std::size_t> >(value);
    values_.push_back(object);
    map_[elementName]=object;
    units_[elementName]=elemetUnit;
    tips_[elementName]=elementTip;
    whatThis_[elementName]=elementWhatThis;
  }




  template<> void ClassDescription::push_back(const std::string& elementName,
                                              const double& value){push_back_regular(elementName,value);}

  template<> void ClassDescription::push_back(const std::string& elementName,
                                              const std::size_t& value){push_back_regular(elementName,value);}

  template<> void ClassDescription::push_back(const std::string& elementName,
                                              const Markov_LA::M_Matrix<double>& value){push_back_regular(elementName,value);}


  template<> void ClassDescription::push_back(const std::string& elementName,
                                              const Markov_LA::M_Matrix<std::size_t>& value){push_back_regular(elementName,value);}

  template<> void ClassDescription::push_back(const std::string& elementName,
                                              const std::string& value){push_back_regular(elementName,value);}

  template<> void ClassDescription::push_back(const std::string& elementName,
                                              const bool& value){push_back_regular(elementName,value);}

  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const ABC_Object& value){push_back_object(elementName,value);}

  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const ABC_Experiment& value){push_back_object(elementName,value);}


  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_Mol::ABC_Markov_Model& value){push_back_object(elementName,value);}

  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_Mol::PatchModelNormalDistribution& value){push_back_object(elementName,value);}

  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_Bay::SingleOptimizationResult& value){push_back_object(elementName,value);}


  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_Bay::OptimizationResult& value){push_back_object(elementName,value);}


  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_Bay::LikelihoodEvaluation& value){push_back_object(elementName,value);}



  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_Mol::ABC_noise& value){push_back_object(elementName,value);}

  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Pulses_trace& value){push_back_object(elementName,value);}

  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Trace& value) {push_back_object(elementName,value);}


  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_Mol::ABC_PatchModel& value){push_back_object(elementName,value);}


  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Parameters& value){push_back_object(elementName,value);}


  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_Mol::PatchModel& value){push_back_object(elementName,value);}

  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_IO::ParametersMoments& value){push_back_object(elementName,value);}


  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_Bay::ABC_Distribution& value){push_back_object(elementName,value);}



  //-------------------------------------------------//



  template<> void ClassDescription::push_back(const std::string& elementName,
                                              const double& value,
                                              const std::string& elementTip,
                                              const std::string& elemetWhatThis
                                              )
  {push_back_regular(elementName,
                     value,
                     elementTip,
                     elemetWhatThis);}

  template<> void ClassDescription::push_back(const std::string& elementName,
                                              const std::size_t& value,
                                              const std::string& elementTip,
                                              const std::string& elemetWhatThis
                                              )
  {push_back_regular(elementName,
                     value,
                     elementTip,
                     elemetWhatThis);
  }

  template<> void ClassDescription::push_back(const std::string& elementName,
                                              const Markov_LA::M_Matrix<double>& value,
                                              const std::string& elementTip,
                                              const std::string& elemetWhatThis
                                              ){
    push_back_regular(elementName,
                      value,
                      elementTip,
                      elemetWhatThis);}


  template<> void ClassDescription::push_back(const std::string& elementName,
                                              const Markov_LA::M_Matrix<std::size_t>& value,
                                              const std::string& elementTip,
                                              const std::string& elemetWhatThis
                                              )
  {
    push_back_regular(elementName,
                      value,
                      elementTip,
                      elemetWhatThis);}

  template<> void ClassDescription::push_back(const std::string& elementName,
                                              const std::string& value,
                                              const std::string& elementTip,
                                              const std::string& elemetWhatThis
                                              ){push_back_regular(elementName,
                                                                  value,
                                                                  elementTip,
                                                                  elemetWhatThis);}

  template<> void ClassDescription::push_back(const std::string& elementName,
                                              const bool& value,
                                              const std::string& elementTip,
                                              const std::string& elemetWhatThis
                                              )
  {push_back_regular(elementName,
                     value,
                     elementTip,
                     elemetWhatThis);
  }
  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const ABC_Object& value,
                              const std::string& elementTip,
                              const std::string& elemetWhatThis
                              ){push_back_object(elementName,
                                                 value,
                                                 elementTip,
                                                 elemetWhatThis);
                               }

  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const ABC_Experiment& value,
                              const std::string& elementTip,
                              const std::string& elemetWhatThis
                              ){push_back_object(elementName,
                                                 value,
                                                 elementTip,
                                                 elemetWhatThis);
                               }


  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_Mol::ABC_Markov_Model& value,
                              const std::string& elementTip,
                              const std::string& elemetWhatThis
                              ){push_back_object(elementName,
                                                 value,
                                                 elementTip,
                                                 elemetWhatThis);
                               }

  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_Mol::PatchModelNormalDistribution& value,
                              const std::string& elementTip,
                              const std::string& elemetWhatThis
                              ){push_back_object(elementName,
                                                 value,
                                                 elementTip,
                                                 elemetWhatThis);}

  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_Bay::SingleOptimizationResult& value,
                              const std::string& elementTip,
                              const std::string& elemetWhatThis
                              ){push_back_object(elementName,
                                                 value,
                                                 elementTip,
                                                 elemetWhatThis);}




  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_Bay::LikelihoodEvaluation& value,
                              const std::string& elementTip,
                              const std::string& elemetWhatThis
                              ){push_back_object(elementName,
                                                 value,
                                                 elementTip,
                                                 elemetWhatThis);}



  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_Mol::ABC_noise& value,
                              const std::string& elementTip,
                              const std::string& elemetWhatThis
                              ){push_back_object(elementName,
                                                 value,
                                                 elementTip,
                                                 elemetWhatThis);}

  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Pulses_trace& value,
                              const std::string& elementTip,
                              const std::string& elemetWhatThis
                              ){push_back_object(elementName,
                                                 value,
                                                 elementTip,
                                                 elemetWhatThis);}

  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Trace& value,
                              const std::string& elementTip,
                              const std::string& elemetWhatThis
                              ) {push_back_object(elementName,
                                                  value,
                                                  elementTip,
                                                  elemetWhatThis);}


  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_Mol::ABC_PatchModel& value,
                              const std::string& elementTip,
                              const std::string& elemetWhatThis
                              ){push_back_object(elementName,
                                                 value,
                                                 elementTip,
                                                 elemetWhatThis);}


  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Parameters& value,
                              const std::string& elementTip,
                              const std::string& elemetWhatThis
                              ){push_back_object(elementName,
                                                 value,
                                                 elementTip,
                                                 elemetWhatThis);}


  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_Mol::PatchModel& value,
                              const std::string& elementTip,
                              const std::string& elemetWhatThis
                              ){push_back_object(elementName,
                                                 value,
                                                 elementTip,
                                                 elemetWhatThis);}

  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_IO::ParametersMoments& value,
                              const std::string& elementTip,
                              const std::string& elemetWhatThis
                              ){push_back_object(elementName,
                                                 value,
                                                 elementTip,
                                                 elemetWhatThis);}


  template<> void
  ClassDescription::push_back(const std::string& elementName,
                              const Markov_Bay::ABC_Distribution& value,
                              const std::string& elementTip,
                              const std::string& elemetWhatThis
                              ){push_back_object(elementName,
                                                 value,
                                                 elementTip,
                                                 elemetWhatThis);}







  //-----------------------------------------------------//



  /**
 Number of elements of the description
*/
  std::size_t ClassDescription::size()const
  {
    return names_.size();
  }

  /**
Indexed constant access to the names of the elements
@param i represent the order in which the description was originally build
@returns only constant access, no way to modify the name.
*/

  std::string ClassDescription::ElementName(std::size_t i)const
  {
    return names_[i];
  }

  /**
      Indexed access to the formatted values of the elements
      @param i order of construction
      @returns value access, the value can be modified.
      @warning there is no check on the validity of the string
      @post assert for out of range access
    */
  std::string ClassDescription::ElementValue(std::size_t i)const
  {
    return ToString(*values_[i]);
  }


  std::string ClassDescription::Tip(std::size_t i)const
  {
    std::map<std::string,std::string>::const_iterator it=tips_.find(ElementName(i));
    if (it!=tips_.end())
      return (*it).second;
    else
      return "";
  }

  std::string ClassDescription::Unit(std::size_t i)const
  {
    std::map<std::string,std::string>::const_iterator it=units_.find(ElementName(i));
    if (it!=units_.end())
      return (*it).second;
    else
      return "";
  }

  std::string ClassDescription::WhatThis(std::size_t i)const
  {
    std::map<std::string,std::string>::const_iterator it=whatThis_.find(ElementName(i));
    if (it!=whatThis_.end())
      return (*it).second;
    else
      return "";
  }


  bool ClassDescription::IsComplexObject(std::size_t i)const
  {
    return (values_[i]->mySuperClass()!= ABC_Object::ClassName());
  }



  /** checks if the element is present
  @param elementName Name of the element
*/

  bool ClassDescription::HasElementName(const std::string& elementName)const
  {
    std::map<std::string, ABC_Object*>::const_iterator it=
        map_.find(elementName);
    return(it!=map_.end());

  }




  std::size_t ClassDescription::NameIndex(const std::string& elementName)const
  {
    for (std::size_t i=0;i<this->size();i++)
      if (this->ElementName(i)==elementName)
        return i;
    return size()+1;
  }





  /**
  Access the value of the element by name
  @param elementName Name of the element
       */
  const ABC_Object * ClassDescription::operator[](
      const std::string& elementName)const
  {
    std::map<std::string, ABC_Object*>::const_iterator it;
    it=map_.find(elementName);
    if (it==map_.end())
      {
        return null_;
      }
    return it->second;
  }

  /**
   Access the value of the element by name
   @param elementName Name of the element
    */
  const ABC_Saveable* ClassDescription::ElementClass(const std::string& elementName)const
  {
    std::map<std::string, ABC_Object*>::const_iterator it;
    it=map_.find(elementName);
    if (it==map_.end()||(it->second->mySuperClass()==ABC_Object::ClassName()))
      {
        return nullSaveable_;
      }
    else
      return dynamic_cast<ABC_Saveable*> (it->second);
  }



  bool ClassDescription::ReplaceElement(const std::string& elementName,
                                        const ABC_Object& newValue)
  {
    if (!this->HasElementName(elementName))
      {
        std::string elementNameZero=elementName;
        if (!toElementNameZero(elementNameZero))
          return false;
        if (!HasElementName(elementNameZero))
          return false;
        std::size_t i=this->NameIndex(elementNameZero);
        if (newValue.mySuperClass()!=values_[i]->mySuperClass())
          {
            return false;
          }
        ABC_Object* tmp=newValue.clone();
        names_.push_back(elementName);
        values_.push_back(tmp);
        map_[elementName]=tmp;
        return true;
      }
    else
      {
        std::size_t i=this->NameIndex(elementName);
        if (newValue.mySuperClass()!=values_[i]->mySuperClass())
          return false;
        ABC_Object* tmp=newValue.clone();
        std::swap(tmp,values_[i]);
        delete tmp;
        map_[names_[i]]=values_[i];
        return true;
      }
  }

  bool ClassDescription::ReplaceElement(const std::string& elementName,
                                        const std::string& newValue)
  {
    if (!this->HasElementName(elementName))
      {
        if (ClassName()==Parameters::ClassName())
          {

            push_back(elementName,newValue);
            return true;

          }
        std::string elementNameZero=elementName;
        if (!toElementNameZero(elementNameZero))
          return false;
        if (!HasElementName(elementNameZero))
          {
            std::cout<<"not recognized:"<<elementNameZero;
            return false;
          }
        std::size_t i=this->NameIndex(elementNameZero);
        ABC_Object* tmp;
        if (values_[i]!=0)
          tmp=values_[i]->clone();
        else
          {
            std::stringstream ss(newValue);
            std::string classname;
            std::string lin;
            extractClassName(lin,ss,classname);
            tmp=getDescriptible(classname);
          }
        if (!ToObject(newValue,tmp))
          return false;
        names_.push_back(elementName);
        values_.push_back(tmp);
        map_[elementName]=tmp;
        return true;

      }
    std::size_t i=this->NameIndex(elementName);
    ABC_Object* tmp;
    if (values_[i]!=0)
      tmp=values_[i]->clone();
    else
      {
        std::stringstream ss(newValue);
        std::string classname;
        std::string lin;
        extractClassName(lin,ss,classname);
        tmp=getDescriptible(classname);
      }
    if (!ToObject(newValue,tmp))
      return false;
    std::swap(tmp,values_[i]);
    delete tmp;
    map_[names_[i]]=values_[i];
    return true;
  }



  ClassDescription::OutputFormatType ClassDescription::getOutputFormat() const
  {return outputFormat_;}



  /**
   Extract operator for ClassDescription objects.
   It looks into the istream for a formated ClassDescription object.
   It identifies the OutputFormatType of the object and extract the name
   of the class and the name and value of all the elements of the
   class description.
   @param[in,out] stream input stream
   @param[in,out] classDes destination of the object

   @returns a reference to the istream
   @post if a className of valid OutputFormatType is identified, classDes now
   holds the values present in the istream.
   If none is found, ClassDescription object is left unaltered and the failbit
   of the istream is set. In this way we can write
   @code
   */
  std::istream& operator>>(std::istream& stream,ClassDescription& classDes)
  {

    std::istream::sentry se(stream, true);
    if(!se) return stream;
    std::string line;
    safeGetline(stream,line);
    std::string className;
    if (!extractClassName(line,stream,className))
      {
        classDes=ClassDescription("Error: invalid Class Name "+line, "");
        return stream;
      }
    std::string name, value;
    // we know the class Name, lets build a default object and get the
    // class description

    ABC_Saveable* des=getDescriptible(className);
    if (des!=0)
      classDes=des->GetDescription();
    else return stream;

    while (!isClassEnd(line,stream,className))
      {
        if (!extractElementName(line,stream,name))
          return stream;
        if (!extractElementValue(line,stream,value))
          {
            if (isClassEnd(line,stream,className))
              {
                if (!classDes.ReplaceElement(name,value))
                  {
                    stream.setstate(stream.rdstate() | std::ios_base::failbit);
                    return stream;
                  }
                stream.clear();
                return stream;
              }
            return stream;
          }
        if (!classDes.ReplaceElement(name,value))
          {
            std::cout<<"Replace element failed!!\n name\t"<<name<<"\nvalue\t"<<value<<std::endl;
            stream.setstate(stream.rdstate() | std::ios_base::failbit);
            return stream;
          }
      }
    return stream;
  }

  /**
 Insert operator for ClassDescription objects.
 It insert all the contents of the ClassDescription: the name of
 the class and the name and value of all the elements of the class
 description.
 The insert oprator supports several formats.
 @param[in,out] stream output stream
 @param[in] classDes the ClassDescription object
 @post the ClassDescription remains the same,
 @post all the contents of the ClassDescription, the name of
 the class and the name and value of all the elements of the class
 description, are inserted in the output stream
 @attention The insert operator supports several formats
    -# FORMAT_BEGIN
    @verbatim
       MyClassName
       NameOfAnItegerElement
       4
       NameOfMatrixElement
       3.536536 9.6345656346 2.4532525
       4.5654 7.5 -2.45643636
       NameOfStringElement
       Luciano Moffatt INQUIMAE
       NameOfDoubleElement
       -1.3545E-5

       // leave an empty line to finish the description
     @endverbatim

     -# FORMAT_BEGIN
     @verbatim
       MyClassName Begin
       NameOfAnItegerElement
       4

       NameOfMatrixElement
       3.536536 9.6345656346 2.4532525
       4.5654 7.5 -2.45643636

       NameOfStringElement
       Luciano Moffatt INQUIMAE

       NameOfDoubleElement
       -1.3545E-5

       MyClassName End

       // leave an empty line to finish the description

     @endverbatim
*/
  std::ostream& operator<<(std::ostream& stream,const ClassDescription& classDes)
  {
    switch (classDes.getOutputFormat())
      {
      case ClassDescription::FORMAT_BEGIN:
        {
          if (classDes.ClassName().empty()) return stream;

          stream<<classDes.ClassName()<<" "<<beginLabel()<<"\n";

          for (std::size_t i=0;i<classDes.size();++i)
            {
              stream<<classDes.ElementName(i)<<"\n";
              stream<<classDes.ElementValue(i)<<"\n";
            }
          stream<<classDes.ClassName()<<" "<<endLabel()<<"\n";

        }
      }
    return stream;
  }

  void RemoveComments(std::string& str)
  {
    const std::string commentMarker="//";
    std::size_t n=str.find(commentMarker);
    str=str.substr(0,n);
  }



  namespace {

    std::string beginLabel()
    {
      return "Begin";
    }

    std::string endLabel()
    {
      return "End";
    }





    bool toElementNameZero(std::string& elementName)
    {

      const std::string numeric="1234567890";
      std::size_t last_char=elementName.find_last_not_of(numeric+"_");
      std::size_t last_underscore=elementName.find_last_of("_");
      std::size_t last_number=elementName.find_last_of(numeric);
      if ((last_char<last_underscore)&&(last_underscore<last_number))
        {
          elementName=elementName.replace(last_underscore,
                                          last_number-last_char,
                                          "_0");
          return true;
        }
      else
        return false;
    }






    ABC_Saveable* getDescriptible(const std::string& classname)
    {
      ABC_Saveable *v;
      if (create(v,classname))
        return v;
      else return 0;
      ABC_Experiment* exp;
      ABC_trace* trac;
      Markov_Mol::ABC_Markov_Model* mod;
      Markov_Mol::ABC_noise* noise;
      Markov_Mol::ABC_PatchModel* patch;
      Markov_IO::ABC_Options* options;
      Markov_Bay::ABC_Result* result;
      Parameters* parameter;
      Markov_Bay::ABC_Distribution* distribution;
      if (create(exp,classname))
        return exp;
      else if (create(trac,classname))
        return trac;
      else if (create(mod,classname))
        return mod;
      else if (create(noise,classname))
        return noise;
      else if (create(patch,classname))
        return patch;
      else if (create(options,classname))
        return options;
      else if (create(result,classname))
        return result;
      else if (create(parameter,classname))
        return parameter;
      else if (create(distribution,classname))
        return distribution;

      else return 0;
    }

    /**
  Extract Class Name and verifies format.
  @param[in]  line String either empty or  containing a class name
  @param[in,out] stream An input stream to look for a line if the line is empty
  @returns the input stream. If an invalid name is found, it sets the failbit
   of the stream (and  therefore the boolean operator applied
  on the stream will return false).

  @pre Expects a two words: the class name and the beginLabel(). It admits
  commenst after the characters //
  @post on success, a goodbit stream, an empty line and the class name in
  the parameter className

 */

    std::istream& extractClassName(
        std::string& line,
        std::istream& stream,
        std::string& className)
    {
      while (line.empty())
        if (!safeGetline(stream,line))
          return stream;

      RemoveComments(line);

      const std::string lower="abcdefghijklmnopqrstuvwxyz";
      const std::string upper="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      const std::string numeric="1234567890";
      const std::string valid=lower+upper+numeric+"_";


      std::vector<std::string> words=LineToWords(line);

      const std::string alpha=lower+upper+"_";

      bool isInvalidCharacter=line.find_first_not_of(valid)==std::string::npos;
      bool isNotStartCharacter=alpha.find(words[0][0])==alpha.npos;

      bool isJustTwoWords=(words.size()!=2);
      bool isLackingBegin=(words.size()<2||words[1]!=beginLabel());

      if (isInvalidCharacter |
          isNotStartCharacter |
          isJustTwoWords |
          isLackingBegin)
        {
          stream.setstate(stream.rdstate() | std::ios_base::failbit);
          return stream;
        }

      className=words[0];
      line.clear();
      return stream;
    }





    bool isClassEnd(std::string& line,
                    std::istream& stream,
                    const std::string& className)
    {
      while (line.empty())
        if (!safeGetline(stream,line))
          return false;
      stream.clear();
      RemoveComments(line);
      std::vector<std::string> words=LineToWords(line);
      if (words.size()!=2)
        return false;
      bool isClassName=words[0]==className;
      bool isEndLabel=words[1]==endLabel();
      return isClassName&&isEndLabel;
    }




    /**
    Extract one element name from a line/stream. Three possible outcomes: a
     valid element name is found, an empty line is found or and invalid name is
     found.

    @param [in] line This buffer line is processed first. If empty, one line is
    taken from the stream. If non-empty but without alphanumeric characters,
    them the line is cleared and the failbit of the stream is set. If it has
    a valid name, it is stored.
    @param [in] stream An input stream to look if the line is empty
    @param [out] line. If valid or empty name are found, it is empty on exit. If
    the name were invalid it is returned here.
    @param [out] name On success it stores the name. If no element is found, it
     it remains unaltered.

     @returns the input stream. If an invalid or empty name is found,
    it sets the failbit of the stream (and  therefore the boolean operator applied
    on the stream will return false).

    @post comments (after "//") are removed
    @post If a valid element name is found, the stream is clear, the name is stored
    and the line cleared. If no element name is found the failbit of the stream
    is set and the line is cleared, the name is left unaltered. If an invalid
    name is found, the failbit is set and the invalid line is returned with the
    comments removed.

    */


    std::istream& extractElementName(std::string& line,
                                     std::istream& stream,
                                     std::string& name)
    {
      while (line.empty())
        if (!safeGetline(stream,line))
          return stream;

      RemoveComments(line);
      const std::string lower="abcdefghijklmnopqrstuvwxyz";
      const std::string upper="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      const std::string numeric="1234567890";
      const std::string valid=lower+upper+numeric+"_";

      std::vector<std::string> words=LineToWords(line);

      const std::string alpha=lower+upper+"_";

      bool isInvalidCharacter=line.find_first_not_of(valid)!=std::string::npos;
      bool isNotStartCharacter=alpha.find(words[0][0])==alpha.npos;

      bool isNotOneWord=(words.size()!=1);

      if (isInvalidCharacter |
          isNotStartCharacter |
          isNotOneWord)
        {
          stream.setstate(stream.rdstate() | std::ios_base::failbit);
          return stream;
        }

      name=words[0];
      line.clear();
      return stream;
    }




    /**
    Value string extraction from line/stream. Four possible outcomes:
    -# a string or a single numeric value is read and stored in value, an empty
    line and a cleared stream are returned.
    -# a matrix is read and stored in value. A line passed the end of the matrix
    is read and it contains a name. The read line is strored in the parameter
    line and a cleared stream is returned.
    -# a matrix is read and stored in value. A line passed the end of the matrix
    is read and it contais nothing or just white spaces. A white spaced line is
    returned in the parameter line and a cleared stream is returned.
    -# a valid string or single or matrix value is read and the end of file is
    reached. The value is returned, the line is returned empty and the stream
    eofbit is cleared.
    -# an invalid or absent value is found in the first line. The parameter
    value is left unaltered, the parameter line is left as it is after reading
    the error line. The stream is returned with the failbit set.



    @param [in,out] stream An input stream that holds the value of an Element.
    @param [in,out] line. Buffer line. If a line is read in the istream surpassing
     the end of the element, this line is returned here.

    @param [out] value on success it returns the formatted value of the element.
    If no element is present it returns itself unaltered.

     @returns the input stream. If an invalid value are found,
    it sets the failbit of the stream (and  therefore the boolean operator applied
    on the stream will return false). The stream state is warrantied to be valid if
    the extraction of the name and values was successful, even in the case that the
    end of file state is reached.


    */
    std::istream& extractElementValue(std::string& line,
                                      std::istream& stream,
                                      std::string& value)
    {
      if (line.empty())
        if (!safeGetline(stream,line))
          return stream;

      RemoveComments(line);
      std::vector<std::string> words=LineToWords(line);

      bool isEmpty=(words.size()==0);
      if (isEmpty)
        {
          stream.setstate(stream.rdstate() | std::ios_base::failbit);
          return stream;
        }


      const std::string lower="abcdefghijklmnopqrstuvwxyz";
      const std::string upper="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      const std::string letters=lower+upper+"_";

      bool startsWithCharacter=letters.find(words[0][0])!=letters.npos;

      if (startsWithCharacter)
        {
          std::string lineCopy=line;
          std::string className;
          bool isClassName=extractClassName(lineCopy,stream,className);
          if (isClassName)
            {
              value="";
              while(!isClassEnd(line,stream,className))
                {
                  value+="\n"+line;
                  if (value.size()>0.9*value.max_size())
                    std::cerr<<"string too big="<<value.size()<<std::endl;
                  line.clear();
                }
              // reach class end or eof
              bool isEndOfFile=!stream;
              if (isEndOfFile)
                return stream;
              value+="\n"+line;
              line.clear();
              return stream;
            }
          // not className, simple string line
          value=line;
          line.clear();
          stream.clear();

          return stream;
        }
      // are them numeric? (this might be removed later)
      for (std::size_t i=0; i<words.size();++i)
        {

          std::stringstream ss(words[i]);

          double x;
          bool isValid=(ss>>x);
          if ((!isValid)&&((words[i]!="nan")&&(words[i]!="-nan")))
            {

              stream.setstate(stream.rdstate() | std::ios_base::failbit);
              return stream;
            }
        }
      // we reach here: yes they are numeric
      value=line;
      line.clear();
      std::string name;

      // now see if there are more values on the next lines

      while(!extractElementName(line,stream,name))
        {
          // iside loop means that there was no valid Name and that the
          // stream is in failed state
          stream.clear();
          words=LineToWords(line);
          bool areMoreValues=(words.size()>0);
          if (!areMoreValues)
            {
              line.clear();
              return stream;
            }
          // is the end?



          // are the values numeric? (this might be removed later)


          for (std::size_t i=0; i<words.size();++i)
            {
              std::stringstream ss(words[i]);
              double x;
              bool isValid=(ss>>x);

              if ((!isValid)&&((words[i]!="nan")&&(words[i]!="-nan")))
                {
                  stream.setstate(stream.rdstate() | std::ios_base::failbit);
                  return stream;
                }
            }
          // the line is numeric, add it
          value+="\n"+line;
          // continue reading
          line.clear();
          stream.clear();
        }
      // we found the new element name
      // we have to put it back in the line
      line=name;
      return stream;
    }


    /**
Extract one element name and value. It first look into a string line and
thereafter from an istream for a name an a value that respond to a particular
ClassDescription::OutputFormatType.

@param [in] line This buffer line is processed first. It would expect a valid
element name, a non-empty string with blank spaces or an empty string.
@param [in] stream An input stream that holds toghether with the line the name
and value of an Element.
@param [out] line. On exit it might return the name of the next element, and
empty string in case nothing is read or and a line containing only whitespaces.
@param [out] name on success it stores the name. If no element is found, it
 returns an empty string. If an invalid name is found it will return the word
 Error: followed by the invalid name and the failbit of the istream is set.
 @param [out] value on success it returns the formatted value of the element.
If no element is present it returns an empty string. If an invalid value is
found it returns the label Error: followed by the invalid value string and the
failbit of the istream is set..
@param [in] format It will read the line and the stream according to the
specified value of the format.


 @returns the input stream. If an invalid name or an invalid value are found,
it sets the failbit of the stream (and  therefore the boolean operator applied
on the stream will return false). The stream state is warrantied to be valid if
the extraction of the name and values was successful, even in the case that the
end of file state is reached.


*/

    std::istream& extractElement(std::string& line,
                                 std::istream& stream,
                                 std::string& name,
                                 std::string& value)
    {

      if (!extractElementName(line,stream,name))
        return stream;
      // name is right go for the data

      if (!extractElementValue(line,stream,value))
        return stream;
      return stream;

    }


  }
}


