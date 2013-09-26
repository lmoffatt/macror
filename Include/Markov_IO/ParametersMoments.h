#ifndef PARAMETERSMOMENTS_H
#define PARAMETERSMOMENTS_H

#include <vector>
#include <map>

#include "Markov_LA/Matrix.h"
#include "Markov_IO/Parameters.h"
#include "Markov_IO/ABC_Parametrizable.h"


namespace Markov_IO
{
class ParametersMoments: public Parameters

{
 public:
    virtual ParametersMoments* clone()const;
    virtual ParametersMoments* create()const;

    virtual ClassDescription GetDescription()const;

    virtual bool LoadFromDescription(const ClassDescription& classDes);

    static std::string ClassName();
    static std::vector<std::string> parentClasses();
    static std::vector<std::string> childClasses();
    virtual bool amIAbstract()const;
    virtual std::vector<std::string>  myParentClasses()const;
    virtual std::vector<std::string>  myChildClasses()const;

    virtual std::string myName()const;
	virtual std::string myClass()const;



    /// Apply the matching parameters
    virtual int apply_parameters(const Parameters& p);
    // object inspectors


    /// Returns the parameters of the object
    virtual const Parameters& get_parameters()const;

    Markov_LA::M_Matrix<double> transformed_Cov()const;
    ParametersMoments& transformed_Cov(const Markov_LA::M_Matrix<double>& cov);

    Markov_LA::M_Matrix<double> transformed_CovInv()const;
    bool transformed_CovInv(const Markov_LA::M_Matrix<double>& covinv);

    ParametersMoments(const Parameters par,
		      const Markov_LA::M_Matrix<double>& cov,
		      const Markov_LA::M_Matrix<double>& covinv=
		      Markov_LA::M_Matrix<double>());



    static ParametersMoments getMoments(const std::vector<ABC_Parametrizable*>& samples);

    static ParametersMoments getMoments(const std::vector<Parameters>& samples);


    ParametersMoments();

    ParametersMoments(const ParametersMoments& other);

    ParametersMoments& operator=(const ParametersMoments& other);

    friend void swap(ParametersMoments& one, ParametersMoments& other);


 private:
    Markov_LA::M_Matrix<double> cov_inv_;
    Markov_LA::M_Matrix<double> cov_;
    Parameters allmoments_;

};


std::istream& operator>> (std::istream& stream,ParametersMoments*& x);
}


#endif // PARAMETERSMOMENTS_H
