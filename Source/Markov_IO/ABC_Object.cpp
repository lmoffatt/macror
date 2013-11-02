#include "Markov_IO/ABC_Object.h"
#include "Markov_IO/ABC_Saveable.h"
#include "Markov_LA/Matrix.h"
#include "Markov_IO/Object.h"

namespace Markov_IO{

 ABC_Object::~ABC_Object()
 {}

 std::string ABC_Object::mySuperClass()const
 {
     return ClassName();
 }

 std::string ABC_Object::ClassName()
 {
     return "Object_Base";
 }

  std::vector<std::string> ABC_Object::parentClasses()
 {
     std::vector<std::string> list;
    return list;
 }

  std::vector<std::string> ABC_Object::childClasses()
 {
     std::vector<std::string> list;
     list.push_back(Object<double>::ClassName());
     list.push_back(Object<std::string>::ClassName());
     list.push_back(Object<std::size_t>::ClassName());
     list.push_back(Object<bool>::ClassName());
     list.push_back(Object<Markov_LA::M_Matrix<double> >::ClassName());
     list.push_back(Object<Markov_LA::M_Matrix<std::size_t> >::ClassName());

     return list;
 }

  bool  create(ABC_Object*& o,const std::string& childClass)
  {
      ABC_Saveable* adesc;

      if (create (adesc,childClass))
      {
          o=adesc;
          return true;
      }
      if (childClass==Object<double>::ClassName())
      {
          o= new Object<double>;
          return true;
      }
      if (childClass==Object<std::string>::ClassName())
      {
          o= new Object<std::string>;
          return true;
      }
      if (childClass==Object<std::size_t>::ClassName())
      {
          o= new Object<std::size_t>;
          return true;
      }
      if (childClass==Object<bool>::ClassName())
      {
          o= new Object<bool>;
          return true;
      }
      if (childClass==Object<Markov_LA::M_Matrix<double> >::ClassName())
      {
          o= new Object<Markov_LA::M_Matrix<double> >;
          return true;
      }
      if (childClass==Object<Markov_LA::M_Matrix<std::size_t> >::ClassName())
      {
          o= new Object<Markov_LA::M_Matrix<std::size_t> >;
          return true;
      }
      return false;
  }




  bool ABC_Object::amIAbstract()const
  {
          return true;
  }
  std::vector<std::string>  ABC_Object::myParentClasses()const
  {
      return parentClasses();
  }
  std::vector<std::string>  ABC_Object::myChildClasses()const
  {
      return childClasses();
  }






 template<typename T>
 std::string ClassName(const T* x)
 {
     return x->ClassName();
 }

 template<>
 std::string ClassName(const double* )
 {
   return "double";
 }

 template<>
 std::string ClassName(const std::string* )
 {
     return "string";
 }

 template<>
 std::string ClassName(const std::size_t* )
 {
     return "size_t";
 }

 template<>
 std::string ClassName(const Markov_LA::M_Matrix<double>* )
 {
     return "Matrix_of_double";
 }

 std::ostream& operator <<(std::ostream& s,ABC_Object& o)
 {
     if (o.mySuperClass()==ABC_Object::ClassName())
	 return o.put(s);
     else
     {
     ABC_Saveable*p= dynamic_cast<ABC_Saveable*> (&o);
	 s<<p->GetDescription();
	 return s;
     }
 }

 bool ABC_Object::operator ==(const ABC_Object& other)const
 {
     if (myClass()!=other.myClass())
	 return false;
     return ABC_Put::operator ==(other);
 }


 bool IsChildOf(const ABC_Object* parent,const ABC_Object* child)
 {

 }


  ABC_Object* ABC_Object::create(const std::string& childClass)
 {
     ABC_Object* o;
     if (Markov_IO::create(o,childClass))
         return o;
     else
         return 0;
 }





}


