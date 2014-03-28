#ifndef CATEGORY_H
#define CATEGORY_H


#include "Markov_Object/Abstract_Named_Object.h"
#include "Markov_Object/QuantityExpression.h"

namespace Markov_Object {

  class Category: public Abstract_Named_Object
  {
  public:
    // static methods

    static std::string ClassName();
    static Class_info classInfo();
    static std::set<std::string> SuperClasses();


    virtual Category* dynamicCast(Abstract_Object *o) const override;
    virtual const Category *dynamicCast(const Abstract_Object *o) const override;

    // virtual methods
    virtual std::string myClass()const override;
    virtual Class_info myClassInfo()const override;
    virtual Category *create() const override;

    virtual Category*
    CreateObject(const std::string &text, std::size_t &cursor)const  override;

    /// checks for the existance of all refered objects
    std::set<std::string> referencedObjects() const override;


    // new methods


    bool operator<(const Category& rh)const;



    Category();

    Category( Environment*  e);


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
