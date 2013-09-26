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
    static std::vector<std::string> parentClasses();
    static std::vector<std::string> childClasses();
    virtual bool amIAbstract()const;
    virtual std::vector<std::string>  myParentClasses()const;
    virtual std::vector<std::string>  myChildClasses()const;

};


bool LoadFromDescription(ABC_Result*& result,
			 const Markov_IO::ClassDescription& classDes);

std::istream& operator>> (std::istream& stream,ABC_Result*& result);

std::vector<std::string> GetChilds(const ABC_Result* r);

bool  create(ABC_Result*& r,const std::string& childClass);






}
#endif // ABC_RESULT_H
