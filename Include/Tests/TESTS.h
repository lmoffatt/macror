#ifndef TESTS_H
#define TESTS_H


#include "Markov_IO/auxiliarIO.h"
#include "ElementaryTest.h"

#define  TEST_EQ(functionality,expected,found)  \
         ElementaryTest(functionality,std::string("")+ \
        #expected+"\t ["+Markov_IO::ToString(expected)+"] =="+ \
        #found+"\t ["+Markov_IO::ToString(found)+"]", \
          expected==found)

//std::string(functionality,std::string(rationality)+  \
//          "expected:" +#expected+"="+Markov_IO::ToString(expected))+ \
//          "found:" +#found+"="+Markov_IO::ToString(found)), \
//           expected==found)


#define  TEST_NEQ(functionality,expected,found)  \
         ElementaryTest(functionality,std::string("")+ \
        #expected+"\t ["+Markov_IO::ToString(expected)+"] !="+ \
        #found+"\t ["+Markov_IO::ToString(found)+"]", \
          expected!=found)



#endif // TESTS_H
