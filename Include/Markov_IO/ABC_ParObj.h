#ifndef ABC_PAROBJ_H
#define ABC_PAROBJ_H

#include <iostream>

#include "Markov_IO/ABC_put.h"
#include "Markov_IO/Parameters.h"

namespace Markov_IO
{


/// Abstract Base Class of parametricized objects

class ABC_Par_Obj: public Markov_IO::ABC_put{
    public:
    ///virtual copy constructors
    virtual ABC_Par_Obj* clone() const=0;
    ///virtual default constructors
    virtual ABC_Par_Obj* create() const=0;

    virtual ~ABC_Par_Obj(){}

    virtual std::ostream& put(std::ostream&) const=0;

    /// Apply the matching parameters and returns the unused ones
    virtual void apply_parameters(const Parameters& p)=0;
    // object inspectors


    /// Returns the parameters of the object
    virtual const Parameters& get_parameters()const=0;

    /*    /// It returns a name for the object that identifies its architecture
	virtual std::string name()const=0; */
};
};
#endif // ABC_PAROBJ_H
