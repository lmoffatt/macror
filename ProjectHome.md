# Mission statement #
> ### _**To provide the ion channels community with a simple way to do theoretically sound             kinetic analysis of macroscopic recordings**_ ###

Macro-R is open source software. It is written in C++ and it is distributed under GPL licence. Anyone can review the algorithms its implements, post a public comment on them, suggest or implements modifications and develop new applications.

Macro-R implements the Macroscopic Recursive algorithm for Ion Channels kinetics.

There are two versions:
  * MacroConsole (**current version 0.01** http://code.google.com/p/macror/downloads/list): a command line application easy to install from binaries or compile it in remote clusters (Makefile for that coming soon).

  * MacroR: (**current version 0.012** http://code.google.com/p/macror/downloads/list) a GUI application more user friendly that wraps the console application.



# [Features](Features.md) #
  * Simulate data for arbitrary changes in agonist concentration given a kinetic model.

  * Calculate rate constants, number of channels and the unitary conductance given real or simulated data and a kinetic scheme.

  * Provides the standard error of all the calculated parameters.

  * Macroscopic Recursive and Macroscopic non Recursive algorithms.

  * Missing events correction.

  * _(Planned)_ Compares the relative evidence of alternative kinetic schemes.

  * _(Planned)_ Voltage jumps and multiple agonist.

  * _(Planned)_ Distribute remotely the intensive calculations demanded for fitting the models.

  * _(Planned)_ Import ABF and ABF 2.0 data.

  * _(Planned)_ Build kinetic schemes based on molecular mechanisms

  * _(Planned)_ Microscopic Recursive algorithm.

# [Example](Example.md) #



# Requirements #
Macro-R is written in C++ and it is multi-platform.
> Binaries run on Windows. Source code should be compilable on any pĺatform.



# [Development Status](DevelopmentStatus.md) #

MacroRConsole alpha version 0.01

MacroR is written in C++ and it is multi-platform.

MacroR is on its early stages of development, Collaborators are welcome.
