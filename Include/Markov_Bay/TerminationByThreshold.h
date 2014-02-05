#ifndef TERMINATIONBYTHRESHOLD_H
#define TERMINATIONBYTHRESHOLD_H

#include "Markov_Bay/ABC_Optimization_termination.h"
#include "Markov_IO/Options.h"


namespace Markov_Bay
{
class TerminationByThreshold: public ABC_OptimizationTermination
{
public:
    virtual TerminationByThreshold* clone()const;
    virtual TerminationByThreshold* create()const;

    virtual ~TerminationByThreshold();
    virtual std::ostream& put(std::ostream & s) const;

    virtual bool operator()(const ABC_OptimizationStep& step);
    virtual std::string Message()const;

    class Options: public Markov_IO::BaseOptions
    {
    public:
	Options();
	Options(const std::string& name,
		double resolution_in_x,
		double resolution_in_LogL,
		double resolution_in_step,
		double resolution_in_gradient);
	Options(const Markov_IO::ABC_Options& options);
	virtual std::string myClass()const;
	static std::string ClassName();


    };

    TerminationByThreshold();
    TerminationByThreshold(const Markov_IO::ABC_Options& O);
    TerminationByThreshold(const TerminationByThreshold& other);
    TerminationByThreshold& operator =(const TerminationByThreshold& other);
    friend void swap(TerminationByThreshold& one, TerminationByThreshold& other);



private:
    double resolution_in_LogL_;
    double resolution_in_x_;
    double resolution_in_step_;
    double resolution_in_gradient_;
    std::string termination_;
};

}



#endif // TERMINATIONBYTHRESHOLD_H
