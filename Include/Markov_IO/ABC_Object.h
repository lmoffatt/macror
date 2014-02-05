#ifndef ABC_OBJECT_H
#define ABC_OBJECT_H

#include <vector>
#include "Markov_IO/ABC_Put.h"


namespace Markov_IO
{


/** Abstract base class of objects that generate a Class Description object
*/
    class ABC_Object: public ABC_Put
{
public:
    /// Virtual Copy Constructors
    virtual ABC_Object* clone() const=0;

    /// Virtual Default Constructors
    virtual ABC_Object* create() const=0;

    /// Virtual child constructor
     virtual ABC_Object* create(const std::string& childClass);

    /// Virtual Destructor
    virtual ~ABC_Object();

    virtual bool operator ==(const ABC_Object& other)const;
    std::ostream& put(std::ostream& s)const=0;


    static std::string ClassName();
    virtual std::string myClass()const=0;
    virtual std::string mySuperClass()const;
 };

  template<typename T>
  std::string ClassName(const T* x);

  std::ostream& operator <<(std::ostream& s,ABC_Object& o);

  bool  create(ABC_Object*& o,const std::string& childClass);


 // bool IsChildOf(const ABC_Object* parent,const ABC_Object* child);




}


#endif // ABC_OBJECT_H
