#include "Markov_Mol/GaussianNoise.h"
#include "Markov_LA/auxiliarMath.h"
#include "Markov_IO/auxiliarIO.h"

using Markov_IO::ToValue;
namespace Markov_Mol_New
{



///  Copy Constructor
gaussian_noise* gaussian_noise::clone() const
{
    return new gaussian_noise(*this);
};
///  Default Constructor
gaussian_noise* gaussian_noise::create() const
{
    return new gaussian_noise();
};

/// Default constuctor
gaussian_noise::gaussian_noise():
        s_at_1Hz_d(),std_{},fs_{}{}

gaussian_noise::~gaussian_noise() {}




/*
/// Identifies the kind of noise
std::string gaussian_noise::name()const
{
    return "gaussian noise";
};
*/

/** Constructor
  @param s Standard deviation of the noise
  @param fs Frequency of sampling where the noise is s
  @param sto A pointer to a random number generator
  @post gaussian_noise do not own the random number generator.
*/
gaussian_noise::gaussian_noise(double standard_deviation,
                               double frequency_of_sampling):
    s_at_1Hz_d(standard_deviation/sqrt(frequency_of_sampling))
  ,std_(standard_deviation),fs_(frequency_of_sampling)
 {
 };


/** Copy constructor

*/
gaussian_noise::gaussian_noise(const gaussian_noise& other):
    s_at_1Hz_d(other.s_at_1Hz_d)
  ,std_(other.std_),fs_(other.fs_)
    {
};

/// Assigment Operator
gaussian_noise& gaussian_noise::operator=(const gaussian_noise& other)
			 {

    if (this != &other)
    {
	gaussian_noise tmp(other);
	swap(*this, tmp);
    }
    return *this;
};





/**
  Simulates gaussian noise averaged on a given time interval
  @param dt [s] Time interval of the measurement in seconds
*/
double gaussian_noise::sample(double dt, std::mt19937_64 &sto)const
{
    double s=sto.randNorm(0.0,1.0);
	   s*= s_at_1Hz_d/sqrt(dt);
    return s;
}

/**
  Returns the value of the standard deviation of the noise for a given time
  interval.
  @param dt [s] Time interval of the measurement in seconds

*/
double gaussian_noise::std(double dt)const
{
    return s_at_1Hz_d/sqrt(dt);
};


/**
  Returns the value of the variance of the noise for a given time
  interval.
  @param dt [s] Time interval of the measurement in seconds

*/
double gaussian_noise::var(double dt) const
{
    double var=s_at_1Hz_d*s_at_1Hz_d/dt;
    return var;
}


double gaussian_noise::P(double x,double dt)const
{
    return exp(logP(x,dt));
}

double gaussian_noise::logP(double x,double dt)const
{
    return -0.5*log(2*PI*var(dt))-0.5*(x*x)/var(dt);
}




/// Swap operator.
void swap(gaussian_noise& one,gaussian_noise& two)
{
    std::swap(one.s_at_1Hz_d,two.s_at_1Hz_d);
    std::swap(one.std_,two.std_);
    std::swap(one.fs_,two.fs_);

 }





std::string gaussian_noise::ClassName()
{
    return "gaussian_noise";
}











}



#include "Markov_Mol/GaussianNoise.h"
#include "Markov_LA/auxiliarMath.h"
#include "Markov_IO/auxiliarIO.h"

using Markov_IO::ToValue;
namespace Markov_Mol
{



///  Copy Constructor
gaussian_noise* gaussian_noise::clone() const
{
    return new gaussian_noise(*this);
};
///  Default Constructor
gaussian_noise* gaussian_noise::create() const
{
    return new gaussian_noise();
};

/// Default constuctor
gaussian_noise::gaussian_noise():
        s_at_1Hz_d(){}

gaussian_noise::~gaussian_noise() {}



/// Set the random number generator
const gaussian_noise& gaussian_noise::set_random_generator(
        Borrowed::MersenneTwister::MTRand* sto)const
{
    sto_Sto=sto;
    return *this;
}

/*
/// Identifies the kind of noise
std::string gaussian_noise::name()const
{
    return "gaussian noise";
};
*/

/** Constructor
  @param s Standard deviation of the noise
  @param fs Frequency of sampling where the noise is s
  @param sto A pointer to a random number generator
  @post gaussian_noise do not own the random number generator.
*/
gaussian_noise::gaussian_noise(const std::string& name,
			       double standard_deviation,
			       double frequency_of_sampling,
			       Borrowed::MersenneTwister::MTRand* sto):
    s_at_1Hz_d(standard_deviation/sqrt(frequency_of_sampling)),
    sto_Sto(sto)
{
    buildParameters();
};


/** Copy constructor

*/
gaussian_noise::gaussian_noise(const gaussian_noise& other):
    name_(other.name_),
    s_at_1Hz_d(other.s_at_1Hz_d),
    sto_Sto(other.sto_Sto),
    parameters_Map(other.parameters_Map)
{
};

/// Assigment Operator
gaussian_noise& gaussian_noise::operator=(const gaussian_noise& other)
                         {

    if (this != &other)
    {
        gaussian_noise tmp(other);
        swap(*this, tmp);
    }
    return *this;
};

/// Returns a Parameter object with the only parameter:
/// the variance of the noise.
const Parameters& gaussian_noise::get_parameters()const
{
    return this->parameters_Map;
};




/**
  Simulates gaussian noise averaged on a given time interval
  @param dt [s] Time interval of the measurement in seconds
*/
double gaussian_noise::sample(double dt)const
{
    double s=sto_Sto->randNorm(0.0,1.0);
           s*= s_at_1Hz_d/sqrt(dt);
    return s;
}

/**
  Returns the value of the standard deviation of the noise for a given time
  interval.
  @param dt [s] Time interval of the measurement in seconds

*/
double gaussian_noise::std(double dt)const
{
    return s_at_1Hz_d/sqrt(dt);
};


/**
  Returns the value of the variance of the noise for a given time
  interval.
  @param dt [s] Time interval of the measurement in seconds

*/
double gaussian_noise::var(double dt) const
{
    double var=s_at_1Hz_d*s_at_1Hz_d/dt;
    return var;
}


double gaussian_noise::P(double x,double dt)const
{
    return exp(logP(x,dt));
}

double gaussian_noise::logP(double x,double dt)const
{
    return -0.5*log(2*PI*var(dt))-0.5*(x*x)/var(dt);
}

/**
 Builds the Parameters object
*/
void gaussian_noise::buildParameters()
{
    parameters_Map=Markov_IO::Parameters(name_+"_parameters");
    parameters_Map.push_back("standard_deviation_at_1_Hz",
                             s_at_1Hz_d,
                              Markov_IO::Parameters::LOG);

}

/**
  Apply the values of the parameters to the object, i.e, sets a new amplitude of
  the noise.
  @param parameters A parameters object with the field
   "standard_deviation_at_1_Hz"
  @post the internal representation of the parameters changes it value
   accordingly
*/
int gaussian_noise::apply_parameters(const Parameters& parameters)//
{
    if (parameters.HasName("standard_deviation_at_1_Hz"))
    {
        s_at_1Hz_d=(parameters["standard_deviation_at_1_Hz"]);
        parameters_Map["standard_deviation_at_1_Hz"]=s_at_1Hz_d;
        return 1;
    };
    return 0;
}





/// Swap operator.
void swap(gaussian_noise& one,gaussian_noise& two)
{
    std::swap(one.name_,two.name_);
    std::swap(one.s_at_1Hz_d,two.s_at_1Hz_d);
    std::swap(one.sto_Sto,two.sto_Sto);
    std::swap(one.parameters_Map,two.parameters_Map);
 }


ClassDescription gaussian_noise::GetDescription()const
{
    ClassDescription desc(myClass(),mySuperClass());

    desc.push_back("name",name_);

    double frequency_of_sampling=1e3;
    desc.push_back("standard_deviation",
           s_at_1Hz_d*sqrt(frequency_of_sampling),
                   "[pA]",
                   "standa",
                   "");
    desc.push_back("frequency_of_sampling",frequency_of_sampling);
    return desc;
}

std::string gaussian_noise::ClassName()
{
    return "gaussian_noise";
}

std::string gaussian_noise::id()const
{
    return name_;
};

std::string gaussian_noise::myClass()const
{
    return ClassName();
}




bool gaussian_noise::LoadFromDescription(const Markov_IO::ClassDescription& classDes)
{
    if (classDes.ClassName()!=myClass())
        return false;

    std::string name;
     if (!ToValue(classDes["name"],name))
         return false;



    double standard_deviation;
    if (!ToValue(classDes["standard_deviation"],standard_deviation))
        return false;

    double frequency_of_sampling;
    if (!ToValue(classDes["frequency_of_sampling"],frequency_of_sampling))
        return false;



    *this=gaussian_noise(name,standard_deviation,frequency_of_sampling,0);

    return true;
}





}
