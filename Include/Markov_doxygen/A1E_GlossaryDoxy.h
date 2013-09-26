#ifndef A1E_GLOSSARYDOXY_H
#define A1E_GLOSSARYDOXY_H

/**
 \page glossary_page  Key Concepts


    -#   \subpage bay_stat_definition
    -#   \subpage Bayes_Theorem_definition "Bayes Theorem"
    -#   \subpage Bayesian_Algorithm_definition
    -#   \subpage prior_probability_definition
    -#   \subpage posterior_probability_definition


    -#   \subpage Likelihood_Function_definition
    -#   \subpage MLE_definition
    -#   \subpage approximation_Algorithms_definition
    -#   \subpage MacroR-TA_definition

    -#   \subpage External_Observer_definition
    -#   \subpage Hidden_Markov_Models_definition
    -#   \subpage hidden_state_definition
    -#   \subpage Markovian_System_definition
    -#   \subpage Master_Equation_definition
    -#   \subpage memory_definition
    -#   \subpage memoryless_definition

    -#   \subpage ion_channel_kinetics_definition
    -#   \subpage ion_channel_definition
    -#   \subpage Ion_Channels_Preparations_definition
    -#   \subpage Kinetic_Models_definition
    -#   \subpage Kinetic_Parameters_definition
    -#   \subpage Kinetic_Information_definition
    -#   \subpage mol_kinetics_definition

    -#   \subpage Q_definition
    -#   \subpage g_definition
    -#   \subpage P_definition
    -#   \subpage p_definition



    -#   \subpage Open_Channel_definition

    -#   \subpage Electrophysiological_Recording_definition
    -#   \subpage Experimental_Protocol_definition
    -#   \subpage Experimental_Results_definition



    -#   \subpage Random_Fluctuations_definition
    -#   \subpage observation_definition

    -#   \subpage Simulation_definition
    -#   \subpage state_definition
    -#   \subpage time_averaged_signal_definition
    List of all the concepts in MacroR

 Kinetic Model
 Kinetic Scheme
 Kinetic Parameters

 Mechanism based Scheme
 State based Scheme
 Allosteric Scheme
 Topology of the Scheme
 Conformational state
 Conformational change
 Allosteric coupling
 State Conductance
 Experimental Data
 Experiment Protocol
 Channel Preparation
 Membrane Potential
 Expression System
 Membrane Preparation
 Transfection Protocol
 pH
 Temperature
 Internal Solution Composition
 External Solution Composition
 Time course
 Agonist
 Tip diameter
 Pippete resistance
 Experiment Sample
 Experiment Sample Identifier
 Experimenter
 Rig Identifier
 Observable Signal
 Q Matrix
 g vector
 a vector
Probability Rate (qij)
Reversal Potential
Number of Channels
State Probability Vector
State Conductance Vector
Markov Approach
State Physicochemical Properties
Open
Closed
Bound
Free


*/


/**
 \page Bayes_Theorem_definition Bayes Theorem
 The Bayesian theorem states that
 Prob(Hi | X,D) = Prob(X | Hi,D) / Sum on j {(Prob(X | Hj,D)  * Prob(Hi|D) }
where the prior plausibility of the Hypothesis i given the previous knowledge D changes accordingly with
*/

//-------------------------------------------------------------------------------------------------------
/**
 \page bay_stat_definition Bayesian Statistics
 Bayesian statistics is fundamentally based on the \ref Bayes_Theorem_definition "Bayes theorem" that updates the
 \ref prior_probability_definition "prior probability" to the \ref posterior_probability_definition
  "posterior probability" after the information present in a particular \ref observation_definition
   "observation" is taken into account.

*/
//-------------------------------------------------------------------------------------------------------

/**
 \page ion_channel_kinetics_definition Ion Channel Kinetics
In the particular case of an \ref ion_channel_definition "Ion Channel" \ref ion_channel_kinetics_definition
 kinetics the observations consist on each one of the measurements made over the amount of current that pass
 through a particular ion channel preparation.
* The prior distribution is the knowledge that we as observers have about the probability of the channels of being on each one of the postulated conformational states. The posterior * distribution is the actualization of prior distribution after measuring the current.

*/
//-------------------------------------------------------------------------------------------------------
/**
 \page Hidden_Markov_Models_definition Hidden Markov Modelling
 A Markovian system is characterized by the fact of being \ref memoryless_definition "memoryless", i.e., it has no
 \ref memory_definition "memory" of its previous \ref state_definition "states", all the information needed to predict
 the  future behaviour of the system is located on the present state, irrespective of previous states. \n
 Systems that present \ref memory_definition "memory" to an \ref External_Observer_definition "External observer"
 can  still be modelled  by a \ref Markovian_System_definition "Markovian System" after the External Observer postulates the
 presence of \ref hidden_state_definition "hidden states", i.e., that there are states that are undistinguishable to
 the \ref External_Observer_definition "External Observer". \n
  By using \ref bay_stat_definition the "Baysesian" aproach, it is possible to estimate the
  probability for the Markovian system to be in a given \ref hidden_state_definition "hidden state",
  based on the history of observations on the system combined
  with the knowledge of the \ref Master_Equation_definition "Master Equation" of the Markovian System.

*/

/**
 \page MacroR-TA_definition MacroR-TA
Macroscopic Recursive, Time Averaged, algorithm
*/


/** \page time_averaged_signal_definition Time Averaged Signal
(as opposed to an experimentally imposible but theoretically simpler
    instantaneous signal)

*/


/**
 \page ion_channel_kinetics_definition Markov models of ion channel kinetics
 Ion channel kinetics can be modelled by Markov chains where different conformational states of the ion channel molecule are
 represented by different states

*/

/**

 \page Electrophysiological_Recording_definition Electrophysiological Recording

 An electrophysiological recording usually consists of the time course of the
current (in voltage clamp mode) or the voltage (in current clamp mode) across a
the ionic channels of a celular or artificial membrane. Electrophysiological
recordings are made with voltage clamp amplifiers.


 Mapping the channel state with the current seen at the preparation
The current that flows through an ion channel preparation is equal to

   y(t)= \ref Nch*( \ref Vm - \ref Vr)*\ref p * \b \ref g

where \anchor Nch Nch is the number of channels of the preparation; \anchor Vm  Vm is the membrane potential;

*/



#endif // A1E_GLOSSARYDOXY_H
