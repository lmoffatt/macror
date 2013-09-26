#ifndef ABC_IO_DESCRIPTIBLE_H
#define ABC_IO_DESCRIPTIBLE_H

#include "Markov_IO/ABC_O_Descriptible.h"
#include "Markov_IO/ClassDescription.h"

namespace Markov_IO
{


/// Abstract base class of objects that can be read from input stream
class ABC_IO_Descriptible: public ABC_O_Descriptible
{
public:
    ///virtual copy constructors
    virtual ABC_IO_Descriptible* clone() const=0;
    ///virtual default constructors
    virtual ABC_IO_Descriptible* create() const=0;

    virtual ~ABC_IO_Descriptible();


    virtual ClassDescription GetDescription()const=0;
    virtual ClassDescription GetState()const;

    virtual bool LoadFromDescription(const ClassDescription& classDes)=0;
    static std::string ClassName();
    virtual std::string myName()const=0;
    virtual std::string myClass()const=0;
    virtual std::string mySuperClass()const;



 };

std::istream& operator>> (std::istream& s,ABC_IO_Descriptible& F);

bool LoadFromDescription(ABC_IO_Descriptible*& t,
			 const Markov_IO::ClassDescription& classDes);



}





#endif // ABC_IO_DESCRIPTIBLE_H
