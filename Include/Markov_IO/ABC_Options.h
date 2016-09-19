#ifndef ABC_OPTIONS_H
#define ABC_OPTIONS_H

#include <string>
namespace Markov_IO_New
{
class ABC_Options

{
public:

    static std::string ClassName();
    virtual std::string myClass()const=0;

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


}





#endif // ABC_OPTIONS_H
