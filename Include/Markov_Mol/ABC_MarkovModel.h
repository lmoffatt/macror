#ifndef ABC_MARKOVMODEL_H
#define ABC_MARKOVMODEL_H

#include <cstddef>  //std::size_t
#include <string>

//#include "Markov_IO/ABC_Get.h"
#include "Markov_LA/Matrix.h"
#include "Markov_Mol/MarkovTransitionRate.h"
#include "Markov_Mol/MarkovTransitionStep.h"
#include "Markov_Mol/MarkovState.h"
#include "Markov_Mol/MarkovStateExt.h"

#include "Markov_IO/ABC_MeasureStep.h"

#include "Markov_IO/ABC_Saveable.h"
#include "Markov_IO/ABC_Parametrizable.h"
#include "Markov_IO/Parameters.h"

#include "Borrowed/MersenneTwister.h"

/**

    Markov_Mol models the kinetics of a group of ion channels.

    Marko_Mol responsibilities are organized in the following way.
The base classes ABC_Markov_Model and ABC_Noise model respectively a generic
kinetic model of an ion channel population and a generic noise source. They set
the interface for the  interaction of different kinetic models (currently only
QMarkovModel)and noise sources (currently only GaussianNoise) with the
Experimental conditions implemented on  Markov_IO and the Bayesian analysis
implemented on Markov_Bay.
They are also used by ExperimentSimulation to generate simulations of real
experiments. The structures MarkovState, MarkovTransitionRate and
MarkovTransitionStep models the different grades of knowledge about the state of
an ion channel population. Publication is a class for storing bibliografic data
 and BufferedFunction is a helper class for buffering results.
 *
 */
namespace Markov_Bay{
    class ABC_Markov_Likelihood_step;
}

namespace Markov_Mol
{
using Markov_LA::M_Matrix;


std::string num_channels_label();

class ABC_PatchModel;


/**

    ABC_Markov_Model is the Base class for Kinetic Models of Ion Channels.

ABC_Markov_Model stores all the necessary kinetic information needed to
simulate electrophysiological recordings and to calculate the likelihood
function of experimental and simulated currents against a given kinetic model.

*/

class ABC_Markov_Model: virtual public Markov_IO::ABC_Data{
public:
    /** virtual copy constructor
       @returns a pointer to a copy of the object
       @post memory is allocated
       @warning has to be removed with delete at the end of the scope
    */
    virtual ABC_Markov_Model* clone() const override=0;

    /** virtual default constructors
	@return a pointer to an empty model
      */

    virtual ABC_Markov_Model* create() const=0;



    static std::string ClassName();
    virtual std::string id()const=0;
    virtual std::string myClass()const=0;
    virtual std::string mySuperClass()const;



    /**
     Patch that owns this model
     */

    virtual const ABC_PatchModel* patch()const=0;

    virtual void setPatch(const ABC_PatchModel* newPatch)=0;






   /**
     Parametrized Modifier of the Model.
     Modifies all the parameters of the model accordingly with the listed
     parameters
     @param parameters contains the numeric values of the parameters to be
	    changed
     @post The model is reinitialize after changing the values of the parameters
     @see MarkovOptim.h
    */
    virtual int apply_parameters(const Markov_IO::Parameters& parameters)=0;

    /**
      Returns all the parametriziced values of the Model.
      @returns A Parameter object that can be fed on optimization algoritms
    */
    virtual const Markov_IO::Parameters& get_parameters()const=0;



    //virtual bool LoadFromStringDescription(const Markov_IO::ClassDescription& classDes)=0;





    /**
     Number of states.
     @return the number of states that the model consider for the channel to be.
    */
    virtual std::size_t k()const=0;


//    /**
//      Author of the last modification of the model.
//      The author of the model is defined as either the first author of the
//      original publication from where the model have been taken verbatim, or
//      just the operator the program. If the model is modified somehow (by the
//      function setParameters the author is then the operator of the program.
//      @returns a string with the last name of the author of the model
//      */
//    virtual std::string author()const=0;


//    /**
//      Date of the last modification to the model.
//      If the model follows exactly a published model, we take the earliest date
//      of reception of the paper. If the model does not follow strictly the
//      published model, it returns the earliest date with the same parameters.
//      If the model is modified, the date is updated.
//      @returns the date in the format YYYYMMDD
//     */
//    virtual std::string date()const=0;



//    /** Publication where the model is based on.
//      @returns an Object Publication with links to the publication of the
//      original model.
//      */
//    virtual const Publication& pub()const=0;



    /**
       Transition rate Matrix, for a concentration of  micromolar agonist.
       @returns a constant reference to the internal representation of
      this matrix (a k() x k() matrix).
       @attention needs the information present in  n_bound_agonists to fully
     describe the kinetics
      */
    virtual const M_Matrix<double>& Q() const=0;

    /**
      Transition rate Matrix at zero Agonist.
      @returns a constant reference to the internal representation of this
     matrix.
     */
     virtual const M_Matrix<double>& Q0() const=0;

    /**
    Increase in the State Transition Matrix comparing zero to 1 microMolar
     Agonist. It can be seen as the association rate for the agonist.
     @returns (k x k) Matrix constant
     */
    virtual const M_Matrix<double>& Q1() const=0;

    /**
    Number of bound agonist at each state.
    @returns the constant reference to a (k x 1) Matrix of positive integers
    */
    virtual const M_Matrix<size_t>& n_bound_agonists() const=0;

    /**
     Conductance of each state.
     @returns a constant reference to a (k x 1) Matrix of doubles
     */
    virtual const M_Matrix<double>& g() const=0;

//    /**
//     Inserts the formatted output in the stream.
//    @post It sould be possible to build a copy of the model with the information
//    provided in the output. The copy should be equal to the original.
//    */
//    virtual std::ostream& put(std::ostream& s) const=0;



//    /** Extracts an ABC_MarkovModel from stream.
//    @pre a valid ABC_MarkovModel of the same class or descendent of *this and
//    with all its components is formatted in the sum of the string and the istream.
//    @post If the format is valid it returns true and the values of current
//    object changes accordingly with the formated input. If the format is invalid,
//    the bu
//    or incomplete nothing happends and it returns false. All the read values
//    from istream are stored in the bufferstream.
//    @param[in] buffer First look here for valid input
//    @param[in] input Stream where the model might be. On success the formatted
//    model is removed. On failure, a single line is removed and stored on buffer.
//    @param[out] buffer Stores invalid input read from istream. Empty on succes.

//    @retval true if a valid object is formed
//    @retval false otherwise
//    */
//    virtual std::istream& get(std::string& buffer,std::istream& input)=0;


//    /**
//      Name of the file for saving the model
//      @returns Author+data+id_number
//      It forms a string with the Author(),date() and an idnumer()
//      */
//    virtual std::string fname()const=0;




//    /** Reads from file
//    @param fileName the complete address to reach a file where a rigthly
//    formatted complete ABC_Markov_Model is.
//    @post asserts on openning the file
//    @post if a valid object can be constructed, it is loaded
//    otherwise, no changes in the object. The format of the file is detected
//    automatically
//    @retval true if a new object could be build from the file
//    @retval false otherwise
//    */
//    virtual bool Load(const std::string& fileName)=0;


    /**  Saves the model with an specified format
	 @param dirName the complete address of the directory where the model is
	 to be saved. The model name is generated by the function fname.
	 containing the object is to be written.
	 @param extension indicates the format of the file
	 @post the model is written in the file in such a way that it can be
	 reconstructed, so it can be written
	       @verbatim
	       // ABC_Markov_Model is abstract, so we need a derived class
	       Class_Derived_From_ABC_Markov_Model modelAlreadyThere;
	       //save on any place
	       std::string fname=model.save("C:\myDir", "xml");
	       // it will create a filename based on
	       Class_Derived_From_ABC_Markov_Model emptyModel;
	       emptyModel.load("C:\myDir\Myself_20110226_1.model.xml");
	       assert(emptyModel==model);
	       @endverbatim
	  @returns a string with the name of the file where the model was saved
	  or an empty string if failed.
      */
//    virtual std::string save(const std::string& dirName,
//			     const std::string& extension)=0;

    /**
      Regular function that computes the equilibrium probability of each state for a given
     concentration of agonist.
      @param[in] agonist_concentration Concentration of agonist in micromolar.
      @returns by value a (1 x k) Matrix with the probabilities of being in each
      @todo consider changing  the name to computePeq (the value might be buffered)
     */
    virtual M_Matrix<double> Peq(double agonist_concentration)const=0;



    /**
      Regular function that computes the Transition probability for a given
      interval of measurements.
      This function is used  to update the knowledge of the distribution of
      states.
      @param xdt is a valid measurment step that contains the evolution of the
      agonist concentration during a given interval of time.
      @param likelihood depending on the bayesian likelihood algorithm different aspects
      of the transition probability are calculated
      @returns an valued object with all the necessary information to perform
	different bayesian analysis during the time interval.
     */
//    virtual Markov_Transition_step  Q_step (
//	    const Markov_IO::ABC_measure_step& xdt ,
//	    const Markov_Bay::ABC_Markov_Likelihood_step& likelihood)const=0;

    virtual  Markov_Transition_step Q_step(const Markov_IO::ABC_measure_step& ,
					   bool is_averaging,
					   bool two_anchor=false)const=0;



    /**
      Regular Function that computes the Transition probability for a given interval of measurements.
      This function is used  to update the knowledge of the distribution of
      states.
      @param xdt is a valid measurment point, that is a step where the agonist
      concentration remained constant
      @returns an object with all the necessary information to perform different
      bayesian analysis during the time interval.
      @todo consider for removal from the interface
    */

//    virtual  Markov_Transition_step Q_dt(
//	    const Markov_IO::ABC_measure_point& xdt,
//	    const Markov_Bay::ABC_Markov_Likelihood_step& likelihood)const=0;

    virtual  Markov_Transition_step Q_dt (const Markov_IO::ABC_measure_point& xdt,
					  bool is_averaging,
					  bool varyingx,
					  bool two_anchor=false)const=0;


    /**
      Computes the Transition probability rate for a given concentration of
      the agonist. This function is internally used by Q_step. It also provides
      the eigenvaluesa and eigenvectors of this Transition probability matrix.
      @param agonist_concentration. The agonist concentration in micromol.
      @param is_averaging tells to that the average of the conductactance is to
      be calculated (and therefore some more calculus are done).
      @returns an object with the transition probability rate and its
      eigenvalues and eigenvectors.
     */
      virtual Markov_Transition_rate Q_x (double agonist_concentrarion,
					bool isavergaing)const=0;


      /**
       Random Function that simulates a population of channels at kinetic
       equilibrium at a given concentration.
       @param agonist_concentration Indicates the concentration of the agonist
       @param Nchannels Indicates the total number of channels
       @param sto is a reference to a Random number generator
       */
      virtual Markov_state start(double agonist_concentration,
				 std::size_t Nchannels,
				 Borrowed::MersenneTwister::MTRand& sto)const=0;


      /**
       Random Function that starts a detailed simulation of  a population of channels at kinetic
       equilibrium at a given concentration.
       @param agonist_concentration Indicates the concentration of the agonist
       @param Nchannels Indicates the total number of channels
       @param sto is a reference to a Random number generator
       @param dummy A dummy variable to indicate that the simulation is detailed
       */

      virtual Markov_state_ext start(double equilibrium_concentration,
				     std::size_t Nchannels,
				     Borrowed::MersenneTwister::MTRand& sto,
				     bool dummy)const=0;


      /**
       Simulates the evolution of a population of channels during a time step.
       @pre markovState has to be initialized with start
       @param[in] xdt Indicates the concentration of the agonist and the duration
       of the time step.
       @param[in,out] markovState is state of the channel population at the
      start time interval.
       @param[in,out] sto is a reference to a Random number generator
       @retval markovState with its new distribution of channels.
       */
      virtual Markov_state& run(const Markov_IO::ABC_measure_point& xdt,
				Markov_state& markovState,
				std::size_t n_steps,
				Borrowed::MersenneTwister::MTRand& sto)const=0;


      /**
       Random Function that simulates the evolution of a population of channels during a time step
       where the agonist concentration changes.
       @pre markovState has to be initialized with start
       @param[in] xdt Indicates the concentration of the agonist and the duration
       of the time step.
       @param[in,out] markovState is state of the channel population at the
      start time interval.
       @param[in,out] sto is a reference to a Random number generator
       @retval markovState with its new distribution of channels.
       */
      virtual Markov_state& run(const Markov_IO::ABC_measure_step& xdt,
				Markov_state& markovState,
				std::size_t n_steps,
				Borrowed::MersenneTwister::MTRand& sto)const=0;


      /**
       Random Function that simulates the detailed evolution of a population of channels during a
       time step.
       @pre markovState has to be initialized with start with the dummy
       parameter
       @param[in] xdt Indicates the concentration of the agonist and the duration
       of the time step.
       @param[in,out] detailedMarkovState is the detailed state of the channel
	population at the start time interval.
       @param[in,out] sto is a reference to a Random number generator
       @retval markovState with its new distribution of channels.
       */
      virtual Markov_state_ext& run(const Markov_IO::ABC_measure_point& xdt,
				    Markov_state_ext& detailedMarkovState,
				    std::size_t n_steps,
				    Borrowed::MersenneTwister::MTRand& sto
				    )const=0;

      /**
       Random Function that simulates the detailed evolution of a population of channels during a
       where the agonist concentration changes.
       @pre markovState has to be initialized with start with the dummy
       parameter
       @param[in] xdt Indicates the evolution of the concentration of the
       agonist during the duration of the time step.
       @param[in,out] detailedMarkovState is the detailed state of the channel
	population at the start time interval.
       @param[in,out] sto is a reference to a Random number generator
       @retval markovState with its new distribution of channels.
       */
      virtual Markov_state_ext& run(const Markov_IO::ABC_measure_step& xdt,
				    Markov_state_ext& M,
				    std::size_t n_steps,
				    Borrowed::MersenneTwister::MTRand& sto
				    )const=0;
  };


/// Abstract Base class of Kinetic Models.

/**
  Equality operator for ABC_Markov_Model.
  @post If the models are equal, so do all their regular functions.
  */
bool operator==(const ABC_Markov_Model& x,const ABC_Markov_Model& y);




std::istream& operator>> (std::istream& stream,ABC_Markov_Model*& model);

bool  create(ABC_Markov_Model*& e,const std::string& childClass);



}
#endif // ABC_MARKOVMODEL_H
