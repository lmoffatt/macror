#ifndef ABC_USE_OPTIONS_H
#define ABC_USE_OPTIONS_H
#include "Markov_IO/ABC_Options.h"
#include "Markov_IO/ABC_Put.h"

namespace Markov_IO
{

/// Abstract Base Class of objects that use options

class ABC_Use_Options: public ABC_Put
{
public:
    /// Apply options
    virtual bool setOptions(const ABC_Options& options)=0;
    // object inspectors

    virtual ~ABC_Use_Options(){}

    /// Returns the parameters of the object
   // virtual const ABC_Options&  getOptions()const=0;
};
}






#endif // ABC_USE_OPTIONS_H
