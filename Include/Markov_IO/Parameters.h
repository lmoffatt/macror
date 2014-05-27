#ifndef PARAMETERS_H
#define PARAMETERS_H
#include "Markov_IO/ABC_Put.h"
#include "Markov_IO/ABC_Parametrizable.h"
#include "Markov_IO/ABC_Saveable.h"

#include "Markov_LA/Matrix.h"
namespace Markov_IO
{
class Parameters : public ABC_Parametrizable

{
public:
    virtual Parameters* clone() const;

    virtual Parameters* create() const;

    virtual ~Parameters();

    virtual ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const ClassDescription& classDes);

    static std::string ClassName();

    virtual std::string myName()const;
    virtual std::string myClass()const;
    virtual std::string mySuperClass()const;


    /// Apply the matching parameters
    virtual int apply_parameters(const Parameters& p);
    // object inspectors


    /// Returns the parameters of the object
    virtual const Parameters& get_parameters()const;


    enum TRANSFORMATION {LINEAR,LOG,SQUARE,FISHER,ERROR};

    static const std::string TransfLabel [5];

    static std::map<std::string,TRANSFORMATION> LabelTransf;

    Parameters(const Parameters&other);

    Parameters();

    Parameters& operator=(const Parameters& other);

    bool isValid()const;

    Parameters(const std::string& name,
	       const std::vector<std::string>& names,
	       const Markov_LA::M_Matrix<double>& values,
	       const std::vector<Parameters::TRANSFORMATION> transf=
	       std::vector<Parameters::TRANSFORMATION>());

    Parameters(const std::string& name);


    friend void swap(Parameters& one, Parameters& two);

    TRANSFORMATION Transform(std::string s)const;
    Parameters& Transform(std::string s,TRANSFORMATION tr);

    TRANSFORMATION Transform(std::size_t i)const;
    Parameters& Transform(std::size_t i,TRANSFORMATION tr);



    double& operator[](std::string s);

    const double& operator[](std::string s) const;

    double & operator[] (std::size_t i);

    const double & operator[] (std::size_t i) const;

    std::string Name(std::size_t i) const;

    int Index(const std::string& name) const;


    bool HasName(std::string s) const;

    bool push_back(std::string s, double x,TRANSFORMATION tr);

    Parameters& Erase(std::string s);

    std::size_t size()const;

    /// incorporates the unshared parameters of a second list

    Parameters& operator+=(const Parameters& other);

    Markov_LA::M_Matrix<double> transformed_values()const;

    Parameters& transformed_values(const Markov_LA::M_Matrix<double>& new_values);


    /// it gives the list of parameters
    //    vector<std::string> shared_par(const Parameters& other)const;



private:
    static std::map<std::string, TRANSFORMATION> create_LabelTransf();
    std::string name_;
    std::vector<double> values_vec;
    std::vector<std::string> name_vec;
    std::map<std::string, std::size_t> name_map;
    std::vector<TRANSFORMATION> trans_vec;
};

std::map<std::string, std::size_t>
name_map_build(const std::vector<std::string>& names);


std::istream& operator>>(std::istream& s,Parameters*& p);

std::ostream& operator<<(std::ostream& stream, const Parameters&  E );

bool LoadFromDescription(Parameters*& p,
			 const Markov_IO::ClassDescription& classDes);


bool  create(Parameters*& e,const std::string& childClass);


bool operator==(const Parameters& one, const Parameters& two);




}
#endif // PARAMETERS_H
