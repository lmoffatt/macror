#ifndef ABC_OPTIONS_H
#define ABC_OPTIONS_H
#include "Markov_IO/ABC_Saveable.h"


namespace Markov_IO
{
class ABC_Options: 	public ABC_Saveable

{
public:

    static std::string ClassName();
    virtual std::string mySuperClass()const;

    static std::vector<std::string> parentClasses();
    static std::vector<std::string> childClasses();
    virtual bool amIAbstract()const;
    virtual std::vector<std::string>  myParentClasses()const;
    virtual std::vector<std::string>  myChildClasses()const;

    virtual ~ABC_Options();

    virtual bool boolean(const std::string& option)const=0;
    virtual std::size_t count(const std::string& option)const=0;
    virtual double  real(const std::string& option)const=0;
    virtual std::string name(const std::string& option)const=0;

    virtual  bool set(const std::string& option,bool abool)=0;
    virtual  bool set(const std::string& option,std::size_t acount)=0;
    virtual  bool set(const std::string& option,double areal)=0;
    virtual  bool set(const std::string& option,std::string astring)=0;

};


//std::ostream& operator<<(std::ostream& stream, const ABC_Options&  E );

bool LoadFromDescription(ABC_Options*& e,
			 const ClassDescription& classDes);



bool  create(ABC_Options*& e,const std::string& childClass);

std::istream& operator>> (std::istream& stream,ABC_Options*& e);

}


#endif // ABC_OPTIONS_H
