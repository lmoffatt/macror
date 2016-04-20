#include "Markov_Mol/MarkovState.h"
#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixSum.h"
#include "Markov_LA/matrixAritmetic.h"

namespace Markov_Mol_New
{

   /**
      Copy Constructor
     @returns a pointer with allocated memory
     @warning should be deallocated manually
     */

   Markov_state* Markov_state::clone() const
{
    return new Markov_state(*this);
};
/// default constructors

   /**
      Default Constructor
     */

 Markov_state* Markov_state::create() const
{
    return new Markov_state();
}

 ///  destructor.
 Markov_state::~Markov_state()
 {}


/**
  Copy Constructor
  @param other Another Markov_state object
  */
Markov_state::Markov_state(const Markov_state& other):
	N_(other.N_),
	ymean_(other.ymean_),
	P_(other.P_)
{}


/**
  Object Constructor.
  @param Nchannels A vector with the number of channels for each state
  @param ymean Instantaneous mean current
  */
Markov_state::Markov_state(M_Matrix<std::size_t> NChannels,
			   double ymean):
N_(NChannels),
ymean_(ymean),
P_(NChannels/totalsum(NChannels))
{}


/**
  Constructor of defined size, allocates memory, values not initialized.
@param size The number of states.
@post memory allocated, left assigment allowed but the values are undefined
for all the components
*/
Markov_state::Markov_state(std::size_t n):
	N_(M_Matrix<size_t>(1,n)),
	ymean_(),
	P_(M_Matrix<double>(1,n))
{}


/// Default constructor
Markov_state::Markov_state():
	N_(M_Matrix<size_t>()),
	ymean_(),
	P_(M_Matrix<double>())
{}

/// Regular Asignment
Markov_state& Markov_state::operator=(const Markov_state& other)
		       {
    if (this != &other)
    {
	Markov_state tmp(other);
	swap(*this, tmp);
    }
    return *this;

}


void swap(Markov_state& one, Markov_state& other)
{
    std::swap(one.N_,other.N_);
    std::swap(one.P_,other.P_);
    std::swap(one.ymean_,other.ymean_);
}



/**
  Access to the Number of channels in each state
  @returns a (1 x k) Matrix with the number of channels in each state
 */
M_Matrix<std::size_t>& Markov_state::N()
{
    return this->N_;
}

/**
  Inpects the Number of channels in each state
  @returns a (1 x k) Matrix with the number of channels in each state
 */
const M_Matrix<std::size_t>& Markov_state::N()const
{
    return N_;
}

/**
  Access to the mean current produced by the N channels
  @returns the value of the current of the open channels
 */
double& Markov_state::ymean()
{
    return ymean_;
}


/**
  Inspects to the mean current produced by the N channels
  @returns the value of the current of the open channels
 */
const double& Markov_state::ymean()const
{
    return ymean_;
}

/**
  Access the expected probability of being in each state
  @returns a (1 x k) Matrix with each probability
*/

M_Matrix<double>& Markov_state::P()
{
    return P_;
}


/**
  Inspects the expected probability of being in each state
  @returns a (1 x k) Matrix with each probability
*/
const M_Matrix<double>& Markov_state::P()const
{
    return P_;
}





/// Put operator
 std::ostream& Markov_state::put(std::ostream& s) const
{
    s<<"\n Markov_state \n";
    s<<N_;
    s<<ymean_<<"\n";
    s<<P_;
    return s;
}
}





#include "Markov_Mol/MarkovState.h"
#include "Markov_LA/Matrix.h"
#include "Markov_LA/matrixSum.h"
#include "Markov_LA/matrixAritmetic.h"

namespace Markov_Mol
{

   /**
      Copy Constructor
     @returns a pointer with allocated memory
     @warning should be deallocated manually
     */

   Markov_state* Markov_state::clone() const
{
    return new Markov_state(*this);
};
/// default constructors

   /**
      Default Constructor
     */

 Markov_state* Markov_state::create() const
{
    return new Markov_state();
}

 ///  destructor.
 Markov_state::~Markov_state()
 {}


/**
  Copy Constructor
  @param other Another Markov_state object
  */
Markov_state::Markov_state(const Markov_state& other):
	N_(other.N_),
	ymean_(other.ymean_),
	P_(other.P_)
{}


/**
  Object Constructor.
  @param Nchannels A vector with the number of channels for each state
  @param ymean Instantaneous mean current
  */
Markov_state::Markov_state(M_Matrix<std::size_t> NChannels,
                           double ymean):
N_(NChannels),
ymean_(ymean),
P_(NChannels/totalsum(NChannels))
{}


/**
  Constructor of defined size, allocates memory, values not initialized.
@param size The number of states.
@post memory allocated, left assigment allowed but the values are undefined
for all the components
*/
Markov_state::Markov_state(std::size_t n):
	N_(M_Matrix<size_t>(1,n)),
	ymean_(),
	P_(M_Matrix<double>(1,n))
{}


/// Default constructor
Markov_state::Markov_state():
	N_(M_Matrix<size_t>()),
	ymean_(),
	P_(M_Matrix<double>())
{}

/// Regular Asignment
Markov_state& Markov_state::operator=(const Markov_state& other)
                       {
    if (this != &other)
    {
        Markov_state tmp(other);
        swap(*this, tmp);
    }
    return *this;

}


void swap(Markov_state& one, Markov_state& other)
{
    std::swap(one.N_,other.N_);
    std::swap(one.P_,other.P_);
    std::swap(one.ymean_,other.ymean_);
}



/**
  Access to the Number of channels in each state
  @returns a (1 x k) Matrix with the number of channels in each state
 */
M_Matrix<std::size_t>& Markov_state::N()
{
    return this->N_;
}

/**
  Inpects the Number of channels in each state
  @returns a (1 x k) Matrix with the number of channels in each state
 */
const M_Matrix<std::size_t>& Markov_state::N()const
{
    return N_;
}

/**
  Access to the mean current produced by the N channels
  @returns the value of the current of the open channels
 */
double& Markov_state::ymean()
{
    return ymean_;
}


/**
  Inspects to the mean current produced by the N channels
  @returns the value of the current of the open channels
 */
const double& Markov_state::ymean()const
{
    return ymean_;
}

/**
  Access the expected probability of being in each state
  @returns a (1 x k) Matrix with each probability
*/

M_Matrix<double>& Markov_state::P()
{
    return P_;
}


/**
  Inspects the expected probability of being in each state
  @returns a (1 x k) Matrix with each probability
*/
const M_Matrix<double>& Markov_state::P()const
{
    return P_;
}





/// Put operator
 std::ostream& Markov_state::put(std::ostream& s) const
{
    s<<"\n Markov_state \n";
    s<<N_;
    s<<ymean_<<"\n";
    s<<P_;
    return s;
}
}
