#ifndef ABC_PARAMETRICDISTRIBUTABLE_H
#define ABC_PARAMETRICDISTRIBUTABLE_H

#include <string>

namespace Markov_Bay
{
class ABC_ParametricDistributable//: public Markov_IO::ABC_Parametrizable
{
public:
    ///virtual copy constructors
    virtual ABC_ParametricDistributable* clone() const=0;
    ///virtual default constructors
    virtual ABC_ParametricDistributable* create() const=0;

    virtual ~ABC_ParametricDistributable();

    static std::string ClassName();
    virtual std::string myClass()const;

    //virtual std::ostream& put(std::ostream&) const=0;


    /*    /// It returns a name for the object that identifies its architecture
	virtual std::string name()const=0; */


    virtual Markov_IO::ABC_Parametrizable* Sample()const=0;

    virtual Markov_IO::ABC_Parametrizable* Mean()const=0;

    virtual Markov_IO::ABC_Parametrizable* Mode()const=0;

    virtual double Probability(const Markov_IO::ABC_Parametrizable& sample)const=0;

    virtual double Density(const Markov_IO::ABC_Parametrizable& sample)const=0;

};

bool  create(ABC_ParametricDistributable*& v,const std::string& childClass);

bool LoadFromDescription(ABC_ParametricDistributable*& v,
             const Markov_IO::ClassDescription& classDesc);



}








#endif // ABC_PARAMETRICDISTRIBUTABLE_H
