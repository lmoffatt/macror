#ifndef ABC_PARAMETRIZABLE_H
#define ABC_PARAMETRIZABLE_H
#include <iostream>

#include "Markov_IO/ABC_Put.h"
#include "Markov_IO/ABC_Saveable.h"
//#include "Markov_IO/Parameters.h"

namespace Markov_IO
{
 class Parameters;

/// Abstract Base Class of parametricized objects

class ABC_Parametrizable: public ABC_Saveable
{
public:
    ///virtual copy constructors
    virtual ABC_Parametrizable* clone() const=0;
    ///virtual default constructors
    virtual ABC_Parametrizable* create() const=0;

    virtual ~ABC_Parametrizable(){}


    static std::string ClassName();
    std::string myClass()const;

    static std::vector<std::string> parentClasses();
    static std::vector<std::string> childClasses();
    virtual bool amIAbstract()const;
    virtual std::vector<std::string>  myParentClasses()const;
    virtual std::vector<std::string>  myChildClasses()const;


    //virtual std::ostream& put(std::ostream&) const=0;

    /// Apply the matching parameters
    virtual int apply_parameters(const Parameters& p)=0;
    // object inspectors


    /// Returns the parameters of the object
    virtual const Parameters& get_parameters()const=0;

    /*    /// It returns a name for the object that identifies its architecture
	virtual std::string name()const=0; */
};

bool  create(ABC_Parametrizable*& v,const std::string& childClass);

bool LoadFromDescription(ABC_Parametrizable*& v,
             const Markov_IO::ClassDescription& classDesc);


}

#endif // ABC_PARAMETRIZABLE_H
