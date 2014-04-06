#ifndef CATEGORY_H
#define CATEGORY_H


#include "Macror_Var/Implement_Named_Object.h"
#include "Macror_Var/Quantity.h"

namespace Macror_Var {

  class Category: public Implement_Named_Object,
      public Implement_Refer_Environment

  {
  public:
    // static methods

    static std::string ClassName();

    static std::set<std::string> SuperClasses();
    // virtual methods
    virtual std::string myClass()const override;
    virtual std::set<std::string> mySuperClasses()const override;
    virtual Category *create() const override;

    virtual Category*
    CreateObject(const std::string &text, std::size_t &cursor)const  override;

    /// checks for the existance of all refered objects
    std::set<std::string> referencedObjects() const override;


    // new methods


    bool operator<(const Category& rh)const;



    Category();



    Category(Environment*  e,
             std::string CategoryName,
             std::string tip,
             std::string whatthis);

  protected:
    virtual Category*
    ToObject(const std::string &text, std::size_t &cursor)  override;


    // Abstract_Object interface
  public:
    virtual std::string ToString() const;

    // Abstract_Object interface
  };





}


#endif // CATEGORY_H
