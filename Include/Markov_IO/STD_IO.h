#ifndef STD_IO_H
#define STD_IO_H

#include"Markov_IO/ABC_IO.h"

#include <vector>
#include <iostream>

namespace Markov_IO
{

class STD_IO: public ABC_IO

{
public:
    /// get a string from the input source
    std::string getline();

    /// put a string to the output source
    void put(const std::string &something);

    STD_IO();

    STD_IO(std::istream* is,std::ostream* os);

    virtual void addOutputStream(std::ostream* os);

    virtual ~STD_IO();

private:
    std::istream* is_;
    std::vector<std::ostream*> os_;
};

}


#endif // STD_IO_H
