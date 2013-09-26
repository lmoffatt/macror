#ifndef ABC_Get_H
#define ABC_Get_H

#include <iostream>

#include "Markov_IO/ABC_Parametrizable.h"
#include "Markov_IO/Parameters.h"

namespace Markov_IO
{


/// Abstract base class of objects that can be read from input stream
class ABC_Get
{
public:
    virtual ~ABC_Get();

      /**
     Buffered extraction virtual operator.
     @param [in,out] line A buffer line that will store on failure
	      the extracted information from the stream. The operator starts
	     looking in this line
    @param [in,out] stream The input stream
    @post no information from the istream is lost: on failure is stored on the
    line.
    @returns the stream. On failure to find a formatted object it sets
    the failbit

      */
    virtual std::istream& get(std::string& line,std::istream& is)=0;

 };


std::istream& operator>> (std::istream& s,ABC_Get& F);
}

#endif // ABC_Get_H
