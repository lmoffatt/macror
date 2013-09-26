#include <iostream>
#include "Markov_IO/STD_IO.h"


namespace Markov_IO
{

    /// get a string from the input source
    std::string STD_IO::getline()
    {
        std::string out;
        std::getline(*is_, out);
        return out;
    }

    /// put a string to the output source
    void STD_IO::put(const std::string& something)
    {
        for (std::size_t i=0; i<os_.size();++i)
        {
            *(os_[i])<<something;
            os_[i]->flush();
         }
    }

    STD_IO::STD_IO():
        is_(&std::cin),
        os_()
    {os_.push_back(&std::cout);}

    STD_IO::STD_IO(std::istream* is,std::ostream* os):
        is_(is),
        os_()
    {os_.push_back(os);}

     void STD_IO::addOutputStream(std::ostream* os)
     {
         os_.push_back(os);
     }

     STD_IO::~STD_IO(){}

}




