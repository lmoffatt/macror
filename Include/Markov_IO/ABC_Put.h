#ifndef ABC_Put_H
#define ABC_Put_H

/// Abstract Base Class of Objects with copy and default constructors, destructors and formated output
#include <string>

#include <ostream>
namespace Markov_IO
{


// TODO: replace ABC_Put hierarchy with  ABC_var hierarchy
class ABC_Put
{
public:
    /// virtual copy constructors
    virtual ABC_Put* clone() const=0;
    /// virtual default constructors
    virtual ABC_Put* create() const=0;
    /// virtual destructor
    virtual ~ABC_Put();
    /// virtual formated output
    virtual std::ostream& put(std::ostream& s) const=0;




    virtual bool operator==(const ABC_Put& other)const;

    /// hint about of the class nature
    virtual std::string Tip()const;

    /// a short description of the class
    virtual std::string WhatThis()const;
};
inline
std::ostream& operator<< (std::ostream& s,const ABC_Put& x)
{
    return x.put(s);
}

}
#endif // ABC_Put_H
