#ifndef ABSTRACT_OBJECT_H
#define ABSTRACT_OBJECT_H

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <memory>


#include <limits>

//#include "Markov_LA/Matrix.h"



namespace Macror_Var
{

  class Abstract_Object
  {
  public:

    // static
    static std::string ClassName()
    {
      return "Abstract_Object";
    }

    static std::set<std::string> SuperClasses()
    {
      std::set<std::string> mySC;
      mySC.insert(ClassName());
      return mySC;
    }


    //virtual implemented reflection
    virtual std::set<std::string> mySuperClasses()const
    {
      return SuperClasses();
    }
    virtual std::string myClass()const
    {
      return ClassName();
    }

    // virtual abstract
    virtual bool empty()const=0;


    /// creates a object of current Class
    virtual Abstract_Object* create()const=0;


    /// returns enough information to make an InternallyValid copy of the object.
    /// if is an empty object it returns enough information to make another empty object
    virtual std::string ToString()const=0;

    // if the object is not of myClass, it returns nullptr
    // if the object is of myClass, it returns true and it uses the text to
    // build an object
    virtual Abstract_Object*
    CreateObject(const std::string& text, std::size_t &cursor)const =0;




    //implemented helper methods
    virtual bool belongsTo(const std::string classname)const
    {
      return mySuperClasses().count(classname)!=0;
    }
    //constructors destructors

    virtual ~Abstract_Object()
    {}

  protected:
    virtual Abstract_Object*
    ToObject(const std::string& text, std::size_t &cursor) =0;

  };


  



#endif // ABSTRACT_OBJECT_H
