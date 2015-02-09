#ifndef ABC_Q_H
#define ABC_Q_H
#include "Markov_LA/Matrix.h"


namespace Markov_Mol2
{

  template<typename D,typename I>
  class Vector_i
  {
     D& operator()(I i);
     D const& operator()(I i)const ;


  };

  template<typename D,typename I,typename J>
  class Matrix_ij
  {
     D& operator()(I i,J j);
     D const& operator()(I i, J j)const ;

  };



  class state_probability
  {
    Markov_LA::M_Matrix<double> p();
  };

  class state_count
  {
    Markov_LA::M_Matrix<std::size_t> N();
  };



  class Enviromental_Conditions
  {
    double value(const std::string& name);
  };




  class physicochemical_state
  {
    Markov_LA::M_Matrix<double> g(std::string name);
  };

  template<typename T>
  class evolution<T>
  {
    std::size_t nsteps();
    std::pair<double,T> operator[](std::size_t i);
  };






  class Transition_Probability_Rate
  {
  public:

      Markov_LA::M_Matrix<double>const & Q()const
      {
        return Q_;
      }// transition rate matrix at time zero

      Markov_LA::M_Matrix<double>const & V()const
      {
        return V_;
        }// eigenvector of Qrun
      Markov_LA::M_Matrix<double>const & W()const
      {
        return W_;
        }// eigenvector of Qrun
      Markov_LA::M_Matrix<double>const & landa()const
      {
        return landa_;
       }
      // eigenvalues

       Markov_LA::M_Matrix<double> Peq()const;

  private:
      Markov_LA::M_Matrix<double> Q_;
      Markov_LA::M_Matrix<double> V_;
      Markov_LA::M_Matrix<double> W_;
      Markov_LA::M_Matrix<double> landa_;

  };


  class Transition_probability
{
  public:
    const Markov_LA::M_Matrix<double>& P()const;

  };


  class Model_Instantaneous_State
  {
    Transition_Probability_Rate Q();
    physicochemical_state g();
  };

  class Sample_Instantaneous_State
  {
    state_count N();
    physicochemical_state g();
  };



  class Model_Interval_State
  {
  public:
       Transition_probability P();

      Markov_LA::M_Matrix<double> gmean_i; // conductance matrix

      ///total conductance for each starting state i and ending state j
      Markov_LA::M_Matrix<double> gtotal_ij; // conductance matrix
      ///mean conductance for each starting state i and ending state j
      Markov_LA::M_Matrix<double> gmean_ij; // conductance matrix

      /// squared mean conductance for each starting state i and ending state j
      Markov_LA::M_Matrix<double> gtotal_sqr_ij; // conductance matrix

      /// squared mean conductance for each starting state i
      Markov_LA::M_Matrix<double> gsqr_i; // conductance matrix

      /// variance of the mean conductance for each starting state i
      Markov_LA::M_Matrix<double> gvar_i; //variance of the conductance matrix
      /// variance of the mean conductance for each starting state i contributed by the ones ending at state j
      Markov_LA::M_Matrix<double> gtotal_var_ij; //variance of the conductance matrix

      /// variance of the mean conductance for each starting state i summed all over  j
      Markov_LA::M_Matrix<double> gtotal_var_i; //variance of the conductance matrix

      /// variance of the mean conductance for each starting state i and ending state j
      Markov_LA::M_Matrix<double> gvar_ij; //variance of the conductance matrix

      Model_Interval_State(ABC_Q Q, Experiment_step e, bool is_averaging,bool two_anchor);


    };







  class Markov_state {
  public:
      const M_Matrix<std::size_t>& N()const;

      double ymean();


  private:
      M_Matrix<std::size_t> N_;
      double ymean_;
      M_Matrix<double> p_;

  };


  class Markov_Simulator
  {
      start( t, )
  };








/**

    ABC_Markov_Model is the Base class for Kinetic Models of Ion Channels.

ABC_Markov_Model stores all the necessary kinetic information needed to
simulate electrophysiological recordings and to calculate the likelihood
function of experimental and simulated currents against a given kinetic model.

*/

class ABC_Q
{
public:

     /**
       Transition rate Matrix, for a concentration of  micromolar agonist.
       @returns a constant reference to the internal representation of
      this matrix (a k() x k() matrix).
       @attention needs the information present in  n_bound_agonists to fully
     describe the kinetics
      */
    virtual Model_Instantaneous_State Q(Enviromental_Conditions e) const=0;






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


bool LoadFromDescription(ABC_Markov_Model*& x,
                         const Markov_IO::ClassDescription& classDes);
bool LoadFromStringDescription(ABC_Markov_Model*& x,
                         const Markov_IO::ClassDescription& classDes);


std::istream& operator>> (std::istream& stream,ABC_Markov_Model*& model);

bool  create(ABC_Markov_Model*& e,const std::string& childClass);



}



#endif // ABC_Q_H
