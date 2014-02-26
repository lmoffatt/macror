#ifndef TESTS_H
#define TESTS_H


#include "Markov_IO/auxiliarIO.h"
#include "ElementaryTest.h"

#define  TEST_EQ(functionality,expected,found)  \
         ElementaryTest(functionality,std::string("")+ \
        #expected+"\t ["+Markov_IO::ToString(expected)+"] =="+ \
        #found+"\t ["+Markov_IO::ToString(found)+"]", \
          (expected)==(found))

//std::string(functionality,std::string(rationality)+  \
//          "expected:" +#expected+"="+Markov_IO::ToString(expected))+ \
//          "found:" +#found+"="+Markov_IO::ToString(found)), \
//           expected==found)


#define  TEST_NEQ(functionality,expected,found)  \
         ElementaryTest(functionality,std::string("")+ \
        #expected+"\t ["+Markov_IO::ToString(expected)+"] !="+ \
        #found+"\t ["+Markov_IO::ToString(found)+"]", \
          (expected)!=(found))


#define  TEST_EQ_xi(xi,expected,found)  \
         ElementaryTest(std::string("") +  \
        #xi +"="+Markov_IO::ToString(xi),std::string("")+ \
        #expected+"\t ["+Markov_IO::ToString(expected)+"] =="+ \
        #found+"\t ["+Markov_IO::ToString(found)+"]", \
          (expected)==(found))


#define  TEST_EQ_xi_xj(xi,xj,expected,found)  \
         ElementaryTest(std::string("")+ \
        #xi+"="+Markov_IO::ToString(xi)+", "+std::string("")+ \
        #xj+"="+Markov_IO::ToString(xj),\
        std::string(""#expected"")+"\t ["+Markov_IO::ToString(expected)+"] =="+ \
        #found+"\t ["+Markov_IO::ToString(found)+"]", \
          (expected)==(found))

#define  TEST_EQ_xi_xj_xk(xi,xj,xk,expected,found)  \
         ElementaryTest(std::string("")+ \
        #xi+"="+Markov_IO::ToString(xi)+", "+std::string("")+ \
        #xj+"="+Markov_IO::ToString(xj)+", "+std::string("")+ \
        #xk+"="+Markov_IO::ToString(xk),\
        std::string(""#expected"")+"\t ["+Markov_IO::ToString(expected)+"] =="+ \
        #found+"\t ["+Markov_IO::ToString(found)+"]", \
          (expected)==(found))




#endif // TESTS_H
