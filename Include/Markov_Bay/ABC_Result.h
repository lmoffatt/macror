#ifndef ABC_RESULT_H
#define ABC_RESULT_H
#include "Markov_IO/ABC_Saveable.h"

namespace Markov_Bay
{

class ABC_Result:public Markov_IO::ABC_Saveable
{
public:
       ///virtual copy constructors
       virtual ABC_Result* clone() const=0;
       ///virtual default constructors
       virtual ABC_Result* create() const=0;

       virtual ~ABC_Result();

    virtual std::string mySuperClass()const;

    static std::string ClassName();

};


bool LoadFromDescription(ABC_Result*& result,
			 const Markov_IO::ClassDescription& classDes);

std::istream& operator>> (std::istream& stream,ABC_Result*& result);

bool  create(ABC_Result*& r,const std::string& childClass);






}
#endif // ABC_RESULT_H
