#ifndef OPTIONS_H
#define OPTIONS_H
#include <string>

#include "Markov_IO/ABC_Options.h"
#include "Markov_IO/ABC_Saveable.h"


namespace Markov_IO
{
class BaseOptions: public ABC_Options
{
public:
    virtual BaseOptions* clone() const;
    ///virtual default constructors
    virtual BaseOptions* create() const;





    BaseOptions(const std::string& name);
    BaseOptions();

    BaseOptions(const BaseOptions& other);

    virtual ~BaseOptions();

    BaseOptions& operator=(const BaseOptions& other);

    BaseOptions& operator+=(const BaseOptions& other);

    friend void swap(BaseOptions& one, BaseOptions& other);

    virtual ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const ClassDescription& classDes);

    static std::string ClassName();
    virtual std::string myName()const;
    virtual std::string myClass()const;


    virtual bool boolean(const std::string& option)const;
    virtual std::size_t count(const std::string& option)const;



    virtual double  real(const std::string& option)const;
    virtual std::string name(const std::string& option)const;

    virtual  bool set(const std::string& option,bool abool);
    virtual  bool set(const std::string& option,std::size_t acount);
    virtual  bool set(const std::string& option,double areal);
    virtual  bool set(const std::string& option,std::string astring);


protected:
    void push_back(const std::string& option,bool abool);
    void push_back(const std::string& option,std::size_t acount);
    void push_back(const std::string& option,double areal);
    void push_back(const std::string& option,const std::string& astring);
    void push_back(const std::string& option,bool abool,const std::string& tip, const std::string& whatThis);
    void push_back(const std::string& option,std::size_t acount,const std::string& tip, const std::string& whatThis);
    void push_back(const std::string& option,double areal,const std::string& tip, const std::string& whatThis);
    void push_back(const std::string& option,const std::string& astring,const std::string& tip, const std::string& whatThis);
    std::string name_;
    std::map<std::string,bool> booleans_;
    std::map<std::string,std::size_t> counts_;
    std::map<std::string,double> reals_;
    std::map<std::string,std::string> names_;
    std::map<std::string,std::string> tips_;
    std::map<std::string,std::string> whatThis_;
};

bool LoadFromDescription(BaseOptions*& e,
             const ClassDescription& classDes);


bool  create(BaseOptions*& e,const std::string& childClass);

std::istream& operator>> (std::istream& stream,BaseOptions*& e);


}

#endif // OPTIONS_H
