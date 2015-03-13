Currently Macro-R is able to do the following tasks:

  * It can create an Ion Channel Model from a user input .

  * _It does not respond multiple agonists nor to changes in membrane potential, nor temperature._

  * It implements three Experimental protocols: single pulses, random pulses and custom pulses. It distinguishes traces where recordings are made and changes in agonist concentration occur and intervals where not. Classes **`Single_Pulses, Random_Pulses and Pulses_Program.`**

  * _It does not read write now experimental protocols from text files._

  * It simulates recordings with customizable time grain. It uses the Mersenne Twister random number generator. Class **`Markov_Simulator`**.

  * _We do not have not standardized the exportation of simulated recordings so we can read them later._

  * It implements Macroscopic Recursive (**`Macro_R_step, Macro_DR_step`**)and Non-Recursive (**`Macro_NR_step`**) approximations to the Likelihood function, both for instantaneous and time averaged measurements. We implement two corrections in the likelihood function for the fact that real measurements are never instantaneous but are always the average over a period of time (usually long enough for many channels to open and/or close). One correction takes into account the state at the beginning of the measurement step  (**`Macro_R_step`** with isaveraging true), the other takes into account also the state of the channel at the end of the interval (**`Macro_DR_step`**).

  * _We do not have implemented the Microscopic Recursive algorithm which gives exact values of the Likelihood function._

  * Class (**`Markov_Optim`**) implements three algorithms for optimizing the likelihood that differs in the method for approximating the Hessian: the Broyden–Fletcher–Goldfarb–Shanno approximation(**`BFGS`**), a 2nd order Taylor approximation to Hessian (**`TaylorLL`**) and taking the Fisher Information Matrix as an approximation (**`FIM`**).

  * _We have not implemented non-gradient algorithms for optimizing the likelihood as the simplex, Nelder-Mead nor Rosenbrock algorithms, nor simulated annealing._
