#ifndef TOBEUSED_H
#define TOBEUSED_H

/**
Although both terms Kinetic Scheme and Kinetic Model are used almost interchangeable in the literature, in MacroR we will
use the term Scheme for the topology of the model removing all the kinetic parameters, and Kinetic Model for a particular
realization of a Kinetic Model wiht all its kinetic parameters determined. \n
The Scheme thus includes the number
 of states, the conections between them, the dependance of the different rates on external parameters as well as the pattern
 of conductance of the different states. Therefore the Kinetic Scheme does not include any physical magnitude. \n
 The Model is an specifyic realization of a Kinetic Scheme, where all the physical magnitudes have
 numbers on them, defined upon a particular combination of Kinetic Paramenters. \n \n

Subset of Kinetic Parameters= MacroR (Kinetic Scheme, Experimental data, Experiment Protocol) \n
The main purpose of MacroR is to determine the subset of Kinetic Parameters of a given Kinetic Scheme that
accumulate most of the Likelihood that a given Sample of a Channel Preparation generates the measured Expermiental Data
after being exposed to a particular Experiment Protocol. \n
The Experimental Data usually consists of the time course of the current that pass through the channel preparation. \n
The Experimental Protocol defines the timing of the exposure of the Channel Preparation to different concentrations of the
agonist(s) or different Membrane Potentials. \n
The Kinetic Scheme describes how the Kinetics is affected by the parameters described in the Experiment Protocol.
All the experimental conditions not included in the Kinetic Scheme but that are potentially needed to replicate the results
 found i.e., temperature, that potentially would affect the kinetics are listed on the description of the Channel
 Preparation. Those details would include things like Temperature, pH and composition of Internal and External Solution,
 Expression System, Membrane preparation, Transfection Protocol, etc. \n
Some of this factors should certainly alter the kinetics (Temperature, for instance), other factors are likely to affect
the kinetics too (like the different compounds of the internal and Extarnal solutions or the Expression System),
while other factors might not have any particular effect (like sucrose concentration). Factors that alter the
kinetics should be incorporated on more more Comprehensive Kinetic Schemes and therefore we would expect that gradually
all the experiment conditions described in the Channel Preparation would be parametrisized and migrate to the Experiment
Protocol.



As kinetic properties might vary from Sample to Sample for Known (pipete resistance, Tip diameter,  Tunknown reasons,
								  each set of Experiment Data taken on the same
Sample (cell or patch) should be properly given a unique identifier label. We suggest to use as an unique identifier the
name of the Experimenter followed by the date and time, Moffatt_2004_Jan_25_02:40:40.

Model that better fit a set of Experimental Results all
obtained on the same Channel Preparation, given a Kinetic Scheme.

Moreover,
So, a kinetic scheme can be considered a function that is fed with some kinetic parameters and its output
is a full determined kinetic model.
In MacroR we distinguish a kinetic scheme from a kinetic model in the following way: we say that the call a kinetic
scheme describes only the
topology of a

*/
//-------------------------------------------------------------------------------------------------------
/**
*  \page how_kinetic_model How to specify a kinetic scheme and a kinetic model
A kinetic model has to describe two things
-# How the internal hypothetical state of the state of the channel evolves in time
-# How is the internal state of the channel related to some observable signal, usually but not necessary, the current that
flows through the channel.

The first is described by the matrix \ref Q_definition, the second by the vector \ref g_page that states the conductance of each
state. \n
For referencing purposes, MacroR also ask for a unique name identifier and in the case the model has been published, its
digital object identifier. \n




For instance

Model_Scheme begin

Name
rP2X2_Moffatt_Hume_2007_1

reference
doi:10.1085/jgp.200709779 Table Ib

Q matrix
    -      3*kon*x        0              0              0
  koff          -        2*kon*x         0              0
    0          2*koff       -         kon*x             0
    0           0         3*koff         -            beta
    0           0           0            alpha          -

g vector
    0           0           0              0           gamma

Model_Scheme end


kon
6.73

koff
166

alpha
45.3

beta
743


isfixed
5  0  5  2  0  2  0  0

number of channels
100

*/
//-------------------------------------------------------------------------------------------------------
/**
 \anchor Vr Vr is the reversal potential for the particular combination of external and internal solution;
 \anchor p \b p is the state probability vector and \anchor g \b g is the state conductance vector.

The evolution of p,\ref p_page,  is governed by the equation

dp/dt=p*Q(x)

where the derivative of \ref p_page is equal to matrix product of p_page and \b Q, Q_definition.

*/
//-------------------------------------------------------------------------------------------------------
/**

\page Theory_page THEORY AND ALGORITHM
The Markov approach provides a simplified model of ion channel kinetics.
the continuum of structural conformations of ion channels is partitioned
on a finite number k of conformational states,  \n \n
	 s(t)=si, \n
0= <i < k. Each conformational state may have different
physicochemical properties; the easiest to measure is the conductance
through the pore. The k x 1 column vector g with
elements gi represents the amount of current that crosses
through a channel that is currently in the state si. In the simplest
kinetic scheme, there are two states: one that conducts
ions (open) and another that does not (closed). More sophisticated
schemes consider multiple closed states and multiple
open states of the same or different conductance.
Channels are dynamic and change their state at random.
Those conformational changes are usually modeled by the
simplest stochastic mechanism: a Markov process. In a Markov
process, at each time interval there is a constant probability
that the channel will change from one state to another. This
probability is dependent only on the current state of the channel,
no matter how long the channel has been in the present
state. It is the perfect memoryless system; the system instantaneously
forgets all its past. \n
The probability of each one of the possible transitions between
the different states that the channel might undergo is
described by a different rate constant, \n \n
qij= Lim[1/dt*Pr(s(t+dt)=sj|s(t)=si),dt->0] \n \n
where qij is the probability rate that the channel will change
from the state i to the state j*

Since Markov processes are stochastic, we need to introduce
the use of probabilities for ion channel kinetics.
We define then the (13k) state probability vector \n
 p(t) =(p0(t),. . .,pk-1(t)) \n
with state probabilities pi(t) =Pr(s(t)= si),
which denotes at a particular time the probability of the channel
being in each one of the k conformational states.

The evolution of the state probability vector \b p in the
absence of further observations is thus determined by the
Kolmogorov differential equation
dp/dt=p*Q
where Q is an n x n rate matrix, with off-diagonal elements
qij being the rate constants of the transition between states
i->j. Each diagonal element qii is equal to qii=Sum[qij,i,i!=j],
the negative sum of the off-diagonal elements of the ith row.
In this way the sum of each row is zero, and therefore the
sum of probabilities is kept constant at one. When there is no
direct transition between states i->j, qij==0. The Matrix Q
summarizes the kinetic properties of the channel itself.

For t>=0, the solution of Eq. 2 is given by the Chapman-
Kolmogorov solution:
p(t)=p(0)*exp(Q*t) (3)
This equation allows us to estimate the probability state
vector as a function of time, given the fact that no more observations
are made on the channel state. There are two ways
to define the exponential of a matrix: in terms of a Taylor
series, \n \n
exp(Qt)=I+Q*t+1/2 Q^2 t^2 +1/3! Q^3t^3+... \n \n
or by decomposing Q into its vector of eigenvalues l and
matrix of eigenvectors V, \n \n
exp(Qt)=exp(V L^D t V^-1)=D exp(L^D t) V^-1 \n
where the notation L^D indicates the diagonal operator, which
builds a diagonal matrix with the vector L. The exponential
of a diagonal matrix is equal to the diagonal of the exponential
of each element of the diagonal.

Markov modeling of an ensemble of channels
In this section, I will define, for an ensemble of channels, the
same elements of the Markov approach that I have defined
for a single channel: the definition of the state of the system,

*/
//-------------------------------------------------------------------------------------------------------
/**

 \page Freq_Bay Frequuentist vs Bayesian approaches
There are two main approaches
to probabilities. In the frequentist approach, we think about a
population of channels evolving stochastically from a given
starting point; the state probability vector indicates the probability
that a randomly chosen channel from an infinite population
of channels is in a given state. This approach is useful
for describing a system that is evolving by itself without any
perturbations from the observer. In the Bayesian approach,
the key concept is that the state probability vector is not a
property of the channel itself (the channel is at a single conformational
state at each time); it is a measure of the uncertainty
that the observer has about the channel state. Therefore,
we do not have to refer to a hypothetical population of channels,
but to the channel we are studying and the information
we have as observers of the channel. The advantage of doing
that (see below) is that we can use the concept of the state
probability vector in the deduction of the recursive likelihood.

*/
//-------------------------------------------------------------------------------------------------------
/**

\page p_definition  State Probability Vector

*/
//-------------------------------------------------------------------------------------------------------
/**
\page Q_definition


*/

//-------------------------------------------------------------------------------------------------------

/**
the state probability vector is defined as

 \b p=( \e p0, ,..., \e pi, .. , \e pk-1) where \ref k is the number of states.
*/

//-------------------------------------------------------------------------------------------------------

/**
 \page Kinetic_Models_task Kinetics Models Specification

*/
//-------------------------------------------------------------------------------------------------------
/**

 \page Recordings_task
*/
//-------------------------------------------------------------------------------------------------------
/**

 \page Simulations_task
*/
//-------------------------------------------------------------------------------------------------------
/**

  \page Maximum_Likelihood_Estimation_task
*/
//-------------------------------------------------------------------------------------------------------
/**
  \page Models_Search_task
*/
//-------------------------------------------------------------------------------------------------------
/**
  \page Remote_Control_task
*/
//-------------------------------------------------------------------------------------------------------
/**
  \page Graphic_Representation_task
*/
//-------------------------------------------------------------------------------------------------------
/**
  \page Utilities_task
*/
//-------------------------------------------------------------------------------------------------------
/**
  \page FAQ_task
*/
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
/**
 \page approximation_Algorithms_definition

*/
//-------------------------------------------------------------------------------------------------------
/**
 \page Bayesian_Algorithm_definition

*/
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
/**
 \page Experimental_Protocol_definition

*/
//-------------------------------------------------------------------------------------------------------
/**
 \page Experimental_Results_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page External_Observer_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page g_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page Hidden_Markov_Models_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page hidden_state_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page how_read_electrophysiology_data


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page ion_channel_definition


*/
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
/**
 \page key_operations_page


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page Kinetic_Information_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page Kinetic_Parameters_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page Likelihood_Function_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page Markovian_System_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page Master_Equation_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page memory_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page memoryless_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page MLE_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page MLE_fitting


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page observation_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page Open_Channel_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page posterior_probability_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page prior_probability_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page Random_Fluctuations_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page Simulation_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page simulations


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page state_definition


*/
//-------------------------------------------------------------------------------------------------------
/**
 \page Troubleshooting_task



*/
//-------------------------------------------------------------------------------------------------------
/**

 \page second_part Reference Manual

 -  to be done

*/
//-------------------------------------------------------------------------------------------------------
/**

 \page third_part Markov_Lib Reference

 the reference and description of all the components of \subpage Markov_Lib

-   Markov_Mol.h is a library of \ref Hidden_Markov_Models_definition "Hidden Markov Modeling"
of \ref mol_kinetics_definition "Molecular Kinetics".

-   Markov_Bay.h is a library of Bayesian statistics of Hidden Markov Models of molecular kinetics.

-   Markov_Opt.h is a library of Algoritms that find the more plausible model.

-   Markov_IO is a library that imports and exports electrophysiological data, kinetic models and statistical results.

-   Markov_LA.h is a library of Linear Algebra used by Makov_Mol, Markov_Bay and Markov_Opt

-   Markov_Plot is a library of graphic representations of electrophysiological recordings,
kinetic models and statistical results.

-   Markov_Remote is a library that allow the remote management of clusters to delegate the execution of long runs.

*/
//-------------------------------------------------------------------------------------------------------



/**



internal policies

1. const double& x()const
   complex_object& x()

   vs

   double x()const
   obj& x(double new_value)



*/



#endif // TOBEUSED_H
