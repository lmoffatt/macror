#include "Markov_Object/Category.h"
#include "Markov_Object/IdentifierName.h"
#include "Markov_Object/Environment.h"


namespace Markov_Object {

  std::string Category::ClassName()
  {
    return "Category";
  }

  std::string Category::myClass() const
  {
    return ClassName();
  }



  std::set<std::string> Category::mySuperClasses() const
  {
    return SuperClasses();
  }

  std::set<std::string> Category::SuperClasses()
  {
    auto mySC=Abstract_Named_Object::SuperClasses();
    mySC.insert(ClassName());
    return mySC;

  }

  const Category *Category::dynamicCast(const Abstract_Object *o) const
  {
    return dynamic_cast<Category const *>(o);
  }

  Category *Category::dynamicCast(Abstract_Object *o) const
  {
    return dynamic_cast<Category*>(o);
  }

  Category *Category::create() const
  {
    return new Category;
  }

  std::string Category::ToString() const
  {
    if (Abstract_Named_Object::idName().empty())
      return "";
    else
      {
        std::string o=ClassName()+" "+ Abstract_Named_Object::ToString();
        return o;
      }
  }

  Category *Category::CreateObject(const std::string &text, std::size_t &cursor) const
  {
    auto tmp=create();
    auto out=tmp->ToObject(text,cursor);
    if (out==nullptr)
      delete tmp;
    return out;
  }



  Category *Category::ToObject(const std::string &text, std::size_t &cursor)
  {
    std::size_t cursor0=cursor;
    IdentifierName::skipSpaces(text,cursor);
    auto clsnms=ClassName().size();

    // it should have the classname
    if ((!text.empty())&&(text.substr(cursor,clsnms)==ClassName()))
      {
        cursor+=clsnms;
        if (Abstract_Named_Object::ToObject(text,cursor))
          {
                return this;
          }
      }
    cursor=cursor0;
    return nullptr;

  }



  std::set<std::string> Category::referencedObjects() const
  {
    std::set<std::string> out;
    return out;
  }


 Category::Category():
    Abstract_Object(),
    Abstract_Named_Object(){}

  Category::Category(Environment*  e):
    Abstract_Object(e),
    Abstract_Named_Object(e){}

  Category::Category(Environment*  e,
                     std::string CategoryName,
                     std::string tip, std::string whatthis)
    :
      Abstract_Object(e),
      Abstract_Named_Object(e,CategoryName,tip,whatthis)
  {

  }



  bool Category::operator<( const Category &rh)const
  {
    return idName()<rh.idName();
  }




}


