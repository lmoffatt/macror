# Specification #
> It implements Recursive and non-Recursive approximations to the likelihood function of Hidden Markov process of multiple identical components, i.e., to ensembles of ion channels.
> It implements the algorithms Macroscopic Recursive, the Integrated Macroscopic Recursive, the Integrated Macroscopic non Recursive.

> It also has to implement Quasi-Newton algorithms for maximization of the likelihood function by searching in the parameters space (comprised by the kinetic rates, the number of channels and the unitary conductance). Implements different approximations to the Hessian: BFGS, a 2nd order taylor approximation to the LogLikelihood function and using the Fisher Information Matrix as an approximation to the Hessian.

_(Planned) Nonlinear Conjugate Gradient, Simulated annealing, Nelder-Mead, Microscopic Recursive and Integrated Microscopic Recursive._

_(Planned) Minimum finding warrantied (i.e, no initial value provided)._

_(Planned) provide prior for the distribution of the parameters._

_(Planned) allow for multi-modal  distribution of the parameters_




# Design #

# Implementation #