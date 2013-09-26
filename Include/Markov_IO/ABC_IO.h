#ifndef ABC_IO_H
#define ABC_IO_H
#include <string>

namespace Markov_IO
{

class ABC_IO
{
public:
    /// get a string from the input source
    virtual std::string getline()=0;

    /// put a string to the output source
    virtual void put(const std::string&)=0;

};

}
#endif // ABC_IO_H
