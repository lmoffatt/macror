#ifndef ABC_OPERATOR_H
#define ABC_OPERATOR_H

#include "Markov_IO/ABC_Saveable.h"

namespace Markov_IO
{

class ABC_Operator: public ABC_Saveable
{


public:


    ///virtual copy constructors
    virtual ABC_Operator* clone() const=0;
    ///virtual default constructors
    virtual ABC_Operator* create() const=0;

    /// Virtual child constructor
    virtual ABC_Operator* create(const std::string& childClass);


    virtual ClassDescription GetDescription()const=0;
    virtual ClassDescription GetState()const;

    virtual bool operator ==(const ABC_Operator& other)const;

    virtual bool LoadFromDescription(const ClassDescription& classDes)=0;


    virtual std::string myName()const=0;
    virtual std::string myClass()const=0;
    virtual std::string mySuperClass()const;
   static std::string ClassName();
    virtual bool Save(const std::string& path);

    virtual bool Load(const std::string& path);




};


bool  create(ABC_Operator*& v,const std::string& childClass);

bool LoadFromDescription(ABC_Operator*& v,
             const Markov_IO::ClassDescription& classDesc);



}


#endif // ABC_OPERATOR_H
