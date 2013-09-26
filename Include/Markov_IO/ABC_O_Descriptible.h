#ifndef ABC_O_DESCRIPTIBLE_H
#define ABC_O_DESCRIPTIBLE_H

#include "Markov_IO/ABC_Object.h"
#include "Markov_IO/ClassDescription.h"


namespace Markov_IO
{
class ClassDescription;

/** Abstract base class of objects that generate a Class Description object
*/
    class ABC_O_Descriptible: public ABC_Object
{
public:
    /// Virtual Copy Constructors
    virtual ABC_O_Descriptible* clone() const=0;

    /// Virtual Default Constructors
    virtual ABC_O_Descriptible* create() const=0;

   /// Virtual child constructor
  virtual ABC_O_Descriptible* create(const std::string& childClass);


        /// Virtual Destructor
    virtual ~ABC_O_Descriptible();


    std::ostream& put(std::ostream& s)const;

     /**
     Gets a ClassDescription object that describe the object
     @returns a ClassDescription object.
    */
    virtual ClassDescription GetState()const=0;

    virtual bool operator ==(const ABC_O_Descriptible& other);

    static std::string ClassName();
    virtual std::string myName()const=0;
    virtual std::string myClass()const=0;
    virtual std::string mySuperClass()const;


   };

std::ostream& operator<<(std::ostream&, const ABC_O_Descriptible& desc);

bool  create(ABC_O_Descriptible*& o,const std::string& childClass);


}


#endif // ABC_O_DESCRIPTIBLE_H
