# Specification #
**Simulates an electrophysiological recording based on arbitrary programs of stimulation to an ensemble of ion channels whose behavior follows an arbitrary kinetic model.**

**Calculates the transition probability matrix and different expected mean conductance and variance as a function of the time intervals. It also do those calculations over intervals of variable agonist concentration**


**_(Planned) Multimodal stimulation: multiple agonist, blockers, antagonist, modulation by membrane potential, force, temperature. Covalent modifications (phosphorylation). Mutations._**

**_(Planned) Alosteric models._**

# Design #
The class **`ABC_Markov_Model`** should implement most of the work: read the model parameters, calculate the transition probabilities and the probability rates.

Concrete Class **`Markov_Transition_rate`** stores the probability transition rate matrix for a given concentration of the agonist. **`Markov_Transition_Step` stores the probability transition matrix for a given time interval and also the mean conductance and its standard deviation.**

# Implementation #
Implemented in Markov\_Mol.cpp