#ifndef A0_MACRORDOXY_H
#define A0_MACRORDOXY_H

/**

  \mainpage  MacroR HELP

 MacroR provides the means to fit arbitrary
 \ref Kinetic_Models_definition "Kinetic Models" to
 \ref Electrophysiological_Recording_definition  "electrophysiological recordings" made on
 \ref Ion_Channels_Preparations_definition "Ion Channels Preparations". It does that by applying a
 \ref bay_stat_definition "Bayesian Statistical Analysis" of a
 \ref Hidden_Markov_Models_definition "Hidden Markov Modelling" of
 \ref mol_kinetics_definition "Molecular Kinetics".
 \n \n

    MacroR provides the first implementation of the
    \ref MacroR-TA_definition "Macroscopic Recursive Time Averaged Algorithm" (
    \ref MacroR-TA_definition "MacroR-TA"), a newly developed
    \ref Bayesian_Algorithm_definition "Bayesian Algorithm" that approximates in an efficient way the
    \ref Likelihood_Function_definition "Likelihood function" of a particular
    \ref Kinetic_Models_definition "Kinetic Model" over a particular set of
    \ref Electrophysiological_Recording_definition "Electrophysiology Recordings".
    \ref MacroR-TA_definition "MacroR-TA" uses the
    \ref Kinetic_Information_definition "Kinetic Information present on the
    \ref Random_Fluctuations_definition "Random Fluctuations in the Number of Open Channels"  and it takes as the input a
    \ref time_averaged_signal_definition "Time Averaged Signal".
    \n \n

    MacroR can is made of a Library, a Console Interface and a Graphic Interface:
     *-#  The Library \ref Markov_Lib, was written in C++. It applyies the
     \ref bay_stat_definition "Bayesian Statistical"approach to
     \ref  Hidden_Markov_Models_definition  "Hidden Markov Models" of
     \ref mol_kinetics_definition "Molecular Kinetics", specifically
     \ref ion_channel_kinetics_definition  "Ion Channel Kinetics". The main
users of the library are people interested on either linking it to other
applications of people interested on extend its functionality. \n
     *-#  The Console Application \ref Macro_Console gives access to
\ref Markov_Lib routines in a simple way and have the advantage that it can be
easily used on a remote cluster without administrative access. \n
     *-#  The Graphic Application \ref Macro_GUI ,implements in an intuitively
way \ref Macro_Console and provides functions (like graphic representations of
models, data and statistical analysis) not available in the console
application.  \n \n

As it is likely that this library might be relevant on other
\ref Hidden_Markov_Models_definition "Hidden Markov Modeling" problems. You are welcome to contact \ref us_page "us"
 if you think that it might be the case on your particular problem.
 \n \n

This manual is divided into three parts:

*  - A \subpage user_guide_page "User Guide" that explains what Macro_Console
and Macro_GUI do and how to put them to work. \n

*  - A \subpage theory_page "Theory" that explains the theoretical basis of
MacroR. \n

*   - A \subpage reference_manual_page "Reference Manual" that gives the
specifications of all the components of Macro_Console and Macro_GUI \n

*   - A \subpage developers_guide_page "Developers Guide" that orient people to
report bugs, request new features or participate in the development of MacroR.
It also provides a reference manual for using Markov_Lib as an
Application Programmers Interface. MacroR and all its components is distributed
under the GPL licence. Commercial lincences are on the table. \n
*/


#endif // A0_MACRORDOXY_H
