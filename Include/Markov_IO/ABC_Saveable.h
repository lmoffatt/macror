#ifndef ABC_SAVEABLE_H
#define ABC_SAVEABLE_H

#include <string>

#include "Markov_IO/ClassDescription.h"


namespace Markov_IO
{
class ClassDescription;

/// Abstract base class of objects that can be read from input stream
class ABC_Saveable: public ABC_Object
{
public:
    ///virtual copy constructors
    virtual ABC_Saveable* clone() const=0;
    ///virtual default constructors
    virtual ABC_Saveable* create() const=0;

    /// Virtual child constructor
   virtual ABC_Saveable* create(const std::string& childClass);


    virtual ClassDescription GetDescription()const=0;
    virtual ClassDescription GetState()const;


    std::ostream& put(std::ostream& s)const;



    virtual bool operator ==(const ABC_Saveable& other)const;

    virtual bool LoadFromDescription(const ClassDescription& classDes)=0;


    virtual std::string myName()const=0;
    virtual std::string myClass()const=0;
    virtual std::string mySuperClass()const;
    virtual bool amIAbstract()const=0;
    static std::string ClassName();
    static std::vector<std::string> parentClasses();
    static std::vector<std::string> childClasses();
    virtual std::vector<std::string>  myParentClasses()const;
    virtual std::vector<std::string>  myChildClasses()const;
    virtual bool Save(const std::string& path);

    virtual bool Load(const std::string& path);




};

bool  create(ABC_Saveable*& v,const std::string& childClass);

bool LoadFromDescription(ABC_Saveable*& v,
             const Markov_IO::ClassDescription& classDesc);




}



#ifdef MACRO_TEST


#include "Tests/MultipleTests.h"
#include "Tests/Markov_IO/ABC_Put_Test.h"
namespace Markov_Test
{
namespace Markov_IO_Test
{

using namespace Markov_IO;

class ABC_Saveable_Test:public ABC_Put_Test
{
public:

    virtual MultipleTests classInvariant()const;

    ABC_Saveable_Test(const ABC_Saveable& sample);

    virtual~ABC_Saveable_Test();

protected:
    const ABC_Saveable* saveable_;
};

}
}

#endif //MACRO_TEST

#endif // ABC_SAVEABLE_H
